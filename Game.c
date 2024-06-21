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

//플레이어 x축  충돌 처리
bool CheckXCollisionWithPlatform(struct Player* _pPlayer, struct Platform* platform)
{
    if (_pPlayer->body.Pos.x < platform->Pos.x + platform->width &&
        _pPlayer->body.Pos.x + _pPlayer->body.w > platform->Pos.x &&
        _pPlayer->body.Pos.y < platform->Pos.y + platform->height &&
        _pPlayer->body.h + _pPlayer->body.Pos.y > platform->Pos.y)
    {
        return true;
    }
    return false;
}

void PlayerGravity(struct Player* _pPlayer, int _platformNum, bool IsCol)
{
    float t = CP_System_GetDt();
    if (IsCol) // 만약 충돌했다면
    {
        //플랫폼 위에서 점프 시작
        if (_pPlayer->body.Pos.y + _pPlayer->body.h < platforms.platform[_platformNum].Pos.y + 30.f && _pPlayer->JumpKeyPressed == true)
        {
            _pPlayer->velocity = _pPlayer->velocity - _pPlayer->Acceleration * t;
            _pPlayer->IsGrounded = AIR;
            _pPlayer->JumpKeyPressed = false;
        }
        //걍 땅에 정착해있을 경우
        else if (_pPlayer->body.Pos.y + _pPlayer->body.h < platforms.platform[_platformNum].Pos.y + 30.f)
        {
            _pPlayer->IsGrounded = GROUND;
            _pPlayer->velocity = 0.f;
            _pPlayer->Pos.y = platforms.platform[_platformNum].Pos.y - _pPlayer->body.h;
            _pPlayer->body.Pos.y = _pPlayer->Pos.y;
            _pPlayer->JumpKeyPressed = false;
        }
        // 플레이어의 상단이 플랫폼의 하단과 충돌한 경우
        else if (_pPlayer->body.Pos.y < platforms.platform[_platformNum].Pos.y + platforms.platform[_platformNum].height &&
            _pPlayer->body.Pos.y + _pPlayer->body.h > platforms.platform[_platformNum].Pos.y)
        {         
            _pPlayer->velocity = 0.f;
            _pPlayer->Pos.y = platforms.platform[_platformNum].Pos.y + platforms.platform[_platformNum].height;
            _pPlayer->body.Pos.y = _pPlayer->Pos.y;
            _pPlayer->IsGrounded = AIR;
        }        
        else
        {
            _pPlayer->velocity = _pPlayer->velocity - _pPlayer->Acceleration * t;
            _pPlayer->IsGrounded = AIR;
        }
    }
    else // 충돌하지 않았다면 떨어진다
    {
        _pPlayer->velocity = _pPlayer->velocity - _pPlayer->Acceleration * t;
        _pPlayer->IsGrounded = AIR;
        _pPlayer->JumpKeyPressed = false;
    }
    //현재 갖고있는 속도만큼 포지션을 더해준다
    _pPlayer->Pos.y += _pPlayer->velocity * t;
    _pPlayer->body.Pos.y = _pPlayer->Pos.y;
}

void game_init(void)
{
	white = CP_Color_Create(255, 255, 255, 255);	

	bgImg = CP_Image_Load("Assets\\bg.png");
	//플레이어 초기로드
	PlayerInit(&player);
	//플랫폼 초기로드
    InitTileImg(tile);
    Platform_Init(&platforms, tile);
	//샤크 초기로드
	SharkInit(&shark);
	//카메라 초기로드
	Camera_Init(&camera);		

	/*
	for (int i = 0; i < platforms.total; i++)
	{
		printf("n = %d, pos = %f %f, size = %f %f\n",
			platforms.total, platforms.platform[i].Pos.x, platforms.platform[i].Pos.y, platforms.platform[i].width, platforms.platform[i].height);
		
		printf("gap = %f %f, type = %d, color = %d %d %d %d\n",
			platforms.platform[i].gap.x, platforms.platform[i].gap.y, platforms.platform[i].type, platforms.platform[i].color.r, platforms.platform[i].color.g, platforms.platform[i].color.b, platforms.platform[i].color.a);
	}
	*/
}

void game_update(void)
{
    CP_Graphics_ClearBackground(white);
    CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));

    // Delta Time 받기    
    time = CP_System_GetDt();
  
    // Shark Update
    {
        if (sharkCollision(&player, &shark)) // Game over
        {
            if (!CP_Input_KeyTriggered(KEY_0)) // 뭐하는 건지 설명 필요합니다
            {
                time = 0.0;
                CP_Settings_Fill(CP_Color_Create(100, 180, 250, 255));
                CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
                CP_Graphics_DrawRect((WINDOW_WIDTH / 2) - 200, (WINDOW_HEIGHT / 2) - 150, 400, 300);

                CP_Settings_Fill(CP_Color_Create(0, 0, 00, 255));
                CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
                CP_Settings_TextSize(50.0f);
                CP_Font_DrawText("Game Over!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

                CP_Settings_NoStroke();
            }
        }
        if (CP_Input_KeyTriggered(KEY_1))
            SharkSpeedUp(&shark, 30.0f);
    }

    //Render first
    {
        CP_Image_Draw(bgImg, (float)CP_Image_GetWidth(bgImg) / 2, (float)CP_Image_GetHeight(bgImg) / 2, (float)CP_Image_GetWidth(bgImg), (float)CP_Image_GetHeight(bgImg), 255);

        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
        CP_Settings_TextSize(50.0f);
        CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

        for (int i = 0; i < platforms.total; i++)
            Draw_Platform(&platforms.platform[i], tile, &camera);
    }
	

    // Move    
    {
        SharkMove(&shark, time);
        Move_Player(&player, &platforms, time);
    }

    //충돌 및 중력 처리
    {
        bool col = false;
        int platformNum = -1;
        for (int i = 0; i < platforms.total; i++)
        {
            if (IsCollision(&player, &platforms.platform[i]))
            {
                col = true;
                platformNum = i;
                break;
            }
        }
        PlayerGravity(&player, platformNum, col);        
        // X축 충돌 감지
        float dt = CP_System_GetDt();
        for (int i = 0; i < platforms.total; i++)
        {
            if (CheckXCollisionWithPlatform(&player, &platforms.platform[i]))
            {
                // 충돌 시 이동 제한
                if (player.velocityX > 0) // 플레이어가 오른쪽으로 이동 중
                {
                    player.Pos.x = player.Pos.x -=350.f*dt;
                    printf("%d %6.3f %6.3f %6.3f %6.3f\n", i, player.Pos.x, player.Pos.y, platforms.platform[i].Pos.x, platforms.platform[i].Pos.y);
                }
                else if (player.velocityX < 0) // 플레이어가 왼쪽으로 이동 중
                {
                    player.Pos.x = player.Pos.x += 350.f * dt;
                    printf("%d %f %6.3f %6.3f %6.3f %6.3f\n", i, platforms.platform[i].width, player.Pos.x, player.Pos.y, platforms.platform[i].Pos.x, platforms.platform[i].Pos.y);
                }
                player.velocityX = 0; // x축 속도 0으로 설정
                player.body.Pos.x = player.Pos.x;
            }
        }
    }

    // Camera_Update
    CameraUpdate(&camera, &player);

    // Render second
    {
        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
        CP_Settings_TextSize(50.0f);
        CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

        for (int i = 0; i < platforms.total; i++)
            Draw_Platform(&platforms.platform[i], tile, &camera);

        Draw_Player(&player, &camera);
        Draw_PlayerCollision(&player, &camera);
        SharkDraw(&shark, &camera);
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
		}
	}
}

void game_exit(void)
{	
	//struct Platform 동적 할당 시 free
	SharkFree(&shark);
	FreeImg(tile);
}