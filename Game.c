#include "Game.h"
#include "Collision.h"
CP_Color white;

CP_Image bgImg;
CP_Image tile[3];

struct Platforms* mP;
//struct Platforms platforms;
struct Shark shark;
struct Player player;
struct Camera camera;
struct Item item;
float time = 0;
float AccTime = 0.f;
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
//털끝 하나 건들지 말것
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
void handleCollision(struct Player* p, struct Platform* plat)
{
    float dt = CP_System_GetDt();

    // 플레이어가 플랫폼의 윗면에 충돌한 경우
    if (p->velocityY > 0 &&
        p->Pos.y + p->height <= plat->col.Pos.y + p->velocityY * dt &&
        p->Pos.y + p->height > plat->col.Pos.y) 
    {
        p->Pos.y = plat->col.Pos.y - p->height;
        p->velocityY = 0;
        p->IsGrounded = GROUND;
    }
    // 플레이어가 플랫폼의 아랫면에 충돌한 경우
    else if (p->velocityY < 1.f &&
        p->Pos.y >= plat->col.Pos.y + plat->col.h + p->velocityY * dt)
    {
        p->Pos.y = plat->col.Pos.y + plat->col.h;
        p->velocityY = 0;
    }
    // 플레이어가 플랫폼의 오른쪽 면에 충돌한 경우
    else if (p->velocityX < 1.f &&
        p->Pos.x <= plat->col.Pos.x + plat->col.w - p->velocityX * dt)
    {
        p->Pos.x = plat->col.Pos.x + plat->col.w;
        p->velocityX = 0;
    }
    // 플레이어가 플랫폼의 왼쪽 면에 충돌한 경우
    else if (p->velocityX > 0 &&
        p->Pos.x + p->width <= plat->col.Pos.x + p->velocityX * dt)
    {
        p->Pos.x = plat->col.Pos.x - p->width;
        p->velocityX = 0;
    }
}
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
//털끝 하나 건들지 말것
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

void game_init(void)
{
    white = CP_Color_Create(255, 255, 255, 255);
	bgImg = CP_Image_Load("Assets\\bg.png");

    InitTileImg(tile);

    //플레이어 초기로드
    PlayerInit(&player);
    //샤크 초기로드
    SharkInit(&shark);
    //카메라 초기로드
    Camera_Init(&camera);

    //아이템 정보 초기로드
    //InitItem(&item);

    if (mP != NULL)
    {
        DeallocatePlatform(mP);
        free(mP);
    }
    mP = malloc(sizeof(struct Platforms));
    mP->pf = NULL;
    int ch = LoadPlatformFromFile(mP, &player);
    printf("ch = %d\n", ch);
    AccTime = 0.f;
	
	/*for (int i = 0; i < platforms.total; i++)
	{
		printf("n = %d, pos = %f %f, size = %f %f\n",
			platforms.total, platforms.platform[i].Pos.x, platforms.platform[i].Pos.y, platforms.platform[i].width, platforms.platform[i].height);
		
		printf("gap = %f %f, type = %d, color = %d %d %d %d\n",
			platforms.platform[i].gap.x, platforms.platform[i].gap.y, platforms.platform[i].type, platforms.platform[i].color.r, platforms.platform[i].color.g, platforms.platform[i].color.b, platforms.platform[i].color.a);
	}*/
	
}

void PlatColliderDraw()
{
    for (int i = 0; i < mP->total; i++)
    {
        CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
        CP_Graphics_DrawRect(mP->pf[i].col.Pos.x, mP->pf[i].col.Pos.y, mP->pf[i].col.w, mP->pf[i].col.h);
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

    if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
    {
        CP_Engine_SetNextGameState(main_init, main_update, main_exit);
    }    

    // Delta Time 받기    
    time = CP_System_GetDt();
    AccTime += time;
    // Render first
    {
        CP_Image_Draw(bgImg, (float)CP_Image_GetWidth(bgImg) / 2, (float)CP_Image_GetHeight(bgImg) / 2, (float)CP_Image_GetWidth(bgImg), (float)CP_Image_GetHeight(bgImg), 255);

        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
        CP_Settings_TextSize(50.0f);
        CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }

    //카메라 업데이트
    {
        CameraUpdate(&camera, &player);
    }
    
    // 플레이어 이동input 처리와 상어 이동   
    {
        Move_Player(&player, mP, time);
        SharkMove(&shark, time, &player);
    }

    // 중력 처리
    {
        player.velocityY += 981.f * time;
    }
    
    // 위치 업데이트
    {
        player.Pos.x += player.velocityX * time;
        player.Pos.y += player.velocityY * time;
    }
    
    struct Platform* p = GetFirstDeadPlatform(mP);
    if (p != NULL)
        InitPlatformRandom(mP, p, &player, Alive);

    UpdateAllPlatforms(mP,&player);
    DrawAllPlatforms(mP, tile, &camera);
    Draw_Player(&player, &camera);
    SharkDraw(&shark, &camera, &player);

    // 플레이어와 플랫폼 간의 충돌 체크 및 처리
    {
        for (int i = 0; i < mP->total; i++)
        {
            if (checkCollision(&player, &mP->pf[i]))
            {
                handleCollision(&player, &mP->pf[i]);
            }
        }
    }

    
   
    if (AccTime >= 15.f&&AccTime<=30.f)
    {
        shark.speed = 250.f;
        for (int i = 0; i < mP->total; i++)
        {
            mP->pf[i].lifeTime = (mP->pf[i].Pos.x) / 600;
        }
    }
    else if (AccTime >= 30.f && AccTime < 50.f)
    {
        shark.speed = 265.f;
        for (int i = 0; i < mP->total; i++)
        {
            mP->pf[i].lifeTime = (mP->pf[i].Pos.x) / 1000;
        }
    }
    else if (AccTime > 50.f)
    {
        //printf("\n\n\n50second acc\n\n\n");
        shark.speed = 280.f;
        for (int i = 0; i < mP->total; i++)
        {
            mP->pf[i].lifeTime = (mP->pf[i].Pos.x) / 2800;
        }
    }
    else if (AccTime > 120.f)
    {
        //printf("\n\n\n50second acc\n\n\n");
        shark.speed = 300.f;
        for (int i = 0; i < mP->total; i++)
        {
            mP->pf[i].lifeTime = (mP->pf[i].Pos.x) / 2800;
        }
    }


    // 바닥에 떨어지지 않도록 처리 <- 만약 바다를 구현 하면 해당 함수 수정 필요
    /*{
        if (player.Pos.y + player.height > WINDOW_HEIGHT)
        {
            player.Pos.y = WINDOW_HEIGHT - player.height;
            player.velocityY = 0;
            player.IsGrounded = GROUND;
        }
    }*/

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
        CP_Settings_TextSize(20.0f);
        CP_Font_DrawText("Restart Press 'R'Button", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50.f);
        player.IsAlive = false;
    }

	if (sharkCollision(&player, &shark)) //Game over
	{
        if (!CP_Input_KeyTriggered(KEY_0))
        {
            time = 0.0;
            CP_Settings_Fill(CP_Color_Create(100, 180, 250, 255));
            CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
            CP_Graphics_DrawRect((WINDOW_WIDTH / 2) - 200, (WINDOW_HEIGHT / 2) - 150, 400, 300);
            CP_Settings_Fill(CP_Color_Create(0, 0, 00, 255));
            CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
            CP_Settings_TextSize(50.0f);
            CP_Font_DrawText("Game Over!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            CP_Settings_TextSize(20.0f);
            CP_Font_DrawText("Restart Press 'R'Button", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50.f);
            //Collider 그리는 함수 (필요 있을 때 많으니깐 있으니깐 지우지 말것)
            //PlatColliderDraw();
            //PlayerColliderDraw();
            player.IsAlive = false;
        }
    }

    //플레이어가 땅아래로 추락할시 게임 종료
    if ((WINDOW_HEIGHT <= GetRenderPlayerPos(&player,&camera).y)&& player.velocityY>=1000)
    {
        time = 0.0;
        CP_Settings_Fill(CP_Color_Create(100, 180, 250, 255));
        CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
        CP_Graphics_DrawRect((WINDOW_WIDTH / 2) - 200, (WINDOW_HEIGHT / 2) - 150, 400, 300);
        CP_Settings_Fill(CP_Color_Create(0, 0, 00, 255));
        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
        CP_Settings_TextSize(50.0f);
        CP_Font_DrawText("Game Over!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        CP_Settings_TextSize(20.0f);
        CP_Font_DrawText("Restart Press 'R' Button", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50.f);
        player.IsAlive = false;
    }
    if (player.IsAlive == false && CP_Input_KeyTriggered(KEY_R))
    {
        //재시작
        game_init();        
        player.IsAlive = true;
    }
}

void game_exit(void)
{
    if (mP != NULL)
    {
        DeallocatePlatform(mP);
        free(mP);
    }

	SharkFree(&shark);
	FreeImg(tile);
}