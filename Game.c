#include "Game.h"
#include "Collision.h"
CP_Color white;

CP_Image bgImg;
CP_Image tile[3];

struct Platforms platforms;
struct Shark shark;
struct Player player;
struct Camera camera;

float time = 0;

//���������������������
//�г� �ϳ� �ǵ��� ����
//���������������������
void handleCollision(struct Player* p, struct Platform* plat)
{
    float dt = CP_System_GetDt();

    // �÷��̾ �÷����� ���鿡 �浹�� ���
    if (p->velocityY > 0 &&
        p->Pos.y + p->height <= plat->col.Pos.y + p->velocityY * dt &&
        p->Pos.y + p->height > plat->col.Pos.y) 
    {
        p->Pos.y = plat->col.Pos.y - p->height;
        p->velocityY = 0;
        p->IsGrounded = GROUND;
    }
    // �÷��̾ �÷����� �Ʒ��鿡 �浹�� ���
    else if (p->velocityY < 1.f &&
        p->Pos.y >= plat->col.Pos.y + plat->col.h + p->velocityY * dt)
    {
        p->Pos.y = plat->col.Pos.y + plat->col.h;
        p->velocityY = 0;
    }
    // �÷��̾ �÷����� ������ �鿡 �浹�� ���
    else if (p->velocityX < 1.f &&
        p->Pos.x <= plat->col.Pos.x + plat->col.w - p->velocityX * dt)
    {
        p->Pos.x = plat->col.Pos.x + plat->col.w;
        p->velocityX = 0;
    }
    // �÷��̾ �÷����� ���� �鿡 �浹�� ���
    else if (p->velocityX > 0 &&
        p->Pos.x + p->width <= plat->col.Pos.x + p->velocityX * dt)
    {
        p->Pos.x = plat->col.Pos.x - p->width;
        p->velocityX = 0;
    }
}
//���������������������
//�г� �ϳ� �ǵ��� ����
//���������������������

bool checkCollision(struct Player* p, struct Platform* plat) {
    if (p->Pos.x < plat->col.Pos.x + plat->col.w &&
        p->Pos.x + p->width > plat->col.Pos.x &&
        p->Pos.y < plat->col.Pos.y + plat->col.h &&
        p->Pos.y + p->height > plat->col.Pos.y)
    {
        return true;
    }
    return false;
}

void game_init(void)
{
    white = CP_Color_Create(255, 255, 255, 255);

    bgImg = CP_Image_Load("Assets\\bg.png");
    // �÷��̾� �ʱ�ȭ
    PlayerInit(&player);
    // �÷��� �ʱ�ȭ
    InitTileImg(tile);
    Platform_Init(&platforms, tile);
    // ��ũ �ʱ�ȭ
    SharkInit(&shark);
    // ī�޶� �ʱ�ȭ
    Camera_Init(&camera);
}

void PlatColliderDraw()
{
    for (int i = 0; i < platforms.total; i++)
    {
        CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
        CP_Graphics_DrawRect(platforms.platform[i].col.Pos.x, platforms.platform[i].col.Pos.y, platforms.platform[i].col.w, platforms.platform[i].col.h);
    }
}

void PlayerColliderDraw()
{
    CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
    CP_Graphics_DrawRect(player.Pos.x, player.Pos.y, player.width, player.height);
}


void game_update(void)
{
    CP_Graphics_ClearBackground(white);
    CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));

    // Delta Time �ޱ�    
    time = CP_System_GetDt();

    // Render first
    {
        CP_Image_Draw(bgImg, (float)CP_Image_GetWidth(bgImg) / 2, (float)CP_Image_GetHeight(bgImg) / 2, (float)CP_Image_GetWidth(bgImg), (float)CP_Image_GetHeight(bgImg), 255);

        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
        CP_Settings_TextSize(50.0f);
        CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

        for (int i = 0; i < platforms.total; i++)
            Draw_Platform(&platforms.platform[i], tile, &camera);
    }

    //ī�޶� ������Ʈ
    {
        CameraUpdate(&camera, &player);
    }
    

    // �÷��̾� �̵�input ó���� ��� �̵�   
    {
        Move_Player(&player, &platforms, time);
        SharkMove(&shark, time);        
    }

    // �߷� ó��
    {
        player.velocityY += 981.f * time;
    }
    

    // ��ġ ������Ʈ
    {
        player.Pos.x += player.velocityX * time;
        player.Pos.y += player.velocityY * time;
    }
    

    // �÷��̾�� �÷��� ���� �浹 üũ �� ó��
    {
        for (int i = 0; i < platforms.total; i++)
        {
            if (checkCollision(&player, &platforms.platform[i]))
            {
                handleCollision(&player, &platforms.platform[i]);
            }
        }
    }
    

    // �ٴڿ� �������� �ʵ��� ó�� <- ���� �ٴٸ� ���� �ϸ� �ش� �Լ� ���� �ʿ�
    {
        if (player.Pos.y + player.height > WINDOW_HEIGHT)
        {
            player.Pos.y = WINDOW_HEIGHT - player.height;
            player.velocityY = 0;
            player.IsGrounded = GROUND;
        }
    }
    

    if (CP_Input_KeyTriggered(KEY_1))
        SharkSpeedUp(&shark, 100.f);

    if (sharkCollision(&player, &shark)) //Game over
    {
        time = 0.0;
        CP_Settings_Fill(CP_Color_Create(100, 180, 250, 255));
        CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
        CP_Graphics_DrawRect((WINDOW_WIDTH / 2) - 200, (WINDOW_HEIGHT / 2) - 150, 400, 300);
        CP_Settings_Fill(CP_Color_Create(0, 0, 00, 255));
        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
        CP_Settings_TextSize(50.0f);
        CP_Font_DrawText("Game Over!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }


    // Render second
    {        
        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
        CP_Settings_TextSize(50.0f);
        CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

        for (int i = 0; i < platforms.total; i++)
            Draw_Platform(&platforms.platform[i], tile, &camera);

        Draw_Player(&player, &camera);        
        SharkDraw(&shark, &camera);

        //Collider �׸��� �Լ� (�ʿ� ���� �� �����ϱ� �����ϱ� ������ ����)
        //PlatColliderDraw();
        //PlayerColliderDraw();
    }    
}

void game_exit(void)
{
    // �÷��� ����ü ���� �Ҵ� ����
    SharkFree(&shark);
    FreeImg(tile);
}