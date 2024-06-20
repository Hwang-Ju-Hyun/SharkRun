#include "Game.h"

CP_Color white;


struct Platforms platforms;
struct Shark shark;
struct Player player;
struct Camera camera;
float time = 0;


void PlayerGravity(struct Player* _pPlayer,int _platformNum,bool IsCol)
{
	float t = CP_System_GetDt();	
	if (IsCol) //만약 충돌했다면
	{ 		
		if (_pPlayer->body.Pos.y + _pPlayer->body.h < platforms.platform[_platformNum].Pos.y)
		{
			_pPlayer->IsGrounded = GROUND;
			_pPlayer->velocity = 0.f;
		}

		if (_pPlayer->body.Pos.y + _pPlayer->body.h > platforms.platform[_platformNum].Pos.y/* && _pPlayer->goX == true*/)
		{				
			if (_pPlayer->Acceleration > 0)//만약 가속도가 0보다 크면 적용
			{
				_pPlayer->velocity = _pPlayer->velocity - _pPlayer->Acceleration * t;
				_pPlayer->IsGrounded = AIR;
			}
			else
			{
				if (_pPlayer->IsGrounded == AIR)
				{
					_pPlayer->velocity = 0;
					_pPlayer->IsGrounded = GROUND;					
				}			
			}
		}	
		else 
		{								
			_pPlayer->velocity = _pPlayer->velocity - _pPlayer->Acceleration * t;
			_pPlayer->IsGrounded = AIR;			
		}
		_pPlayer->Pos.y += _pPlayer->velocity * t;
		_pPlayer->body.Pos.y += _pPlayer->velocity * t;						
		return;
	}
	//충돌하지 않았다면 떨어진다
	_pPlayer->velocity = _pPlayer->velocity - _pPlayer->Acceleration * t;
	_pPlayer->IsGrounded = AIR;
	
	_pPlayer->Pos.y = _pPlayer->Pos.y + _pPlayer->velocity * t;	
	_pPlayer->body.Pos.y += _pPlayer->velocity * t;
	_pPlayer->goX = true;	
}

void game_init(void)
{
	white = CP_Color_Create(255, 255, 255, 255);	

	//플레이어 초기로드
	PlayerInit(&player);
	
	//플랫폼 초기로드
	Platform_Load("tile.dat", &platforms);	
	
	//샤크 초기로드
	SharkInit(&shark);

	//카메라 초기로드
	Camera_Init(&camera);		

	for (int i = 0; i < platforms.total; i++)
	{
		printf("n = %d, pos = %f %f, size = %f %f\n",
			platforms.total, platforms.platform[i].Pos.x, platforms.platform[i].Pos.y, platforms.platform[i].width, platforms.platform[i].height);
		
		printf("gap = %f %f, type = %d, color = %d %d %d %d\n",
			platforms.platform[i].gap.x, platforms.platform[i].gap.y, platforms.platform[i].type, platforms.platform[i].color.r, platforms.platform[i].color.g, platforms.platform[i].color.b, platforms.platform[i].color.a);
	}
}

void game_update(void)
{
	CP_Graphics_ClearBackground(white);
	CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
	
	//Delta Time 받기	
	time = CP_System_GetDt();

	//Camera_Update
	CameraUpdate(&camera, &player);
	
	//Shark Update
	{
		if (sharkCollision(&player, &shark)) //Game over
		{
			if (!CP_Input_KeyTriggered(KEY_0)) //뭐하는 건지 설명 필요합니다
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


	//====Move=====	
	{
		//SharkMove(&shark, time);
		Move_Player(&player, &platforms, time);		
	}	

	//Collision Update & Gravity Update
	bool col = false;	
	int platformNum = 0;
	PlayerGravity(&player, platformNum, col);

		

	//====Render===
	{
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

		Draw_Player(&player, &camera);
		Draw_PlayerCollision(&player, &camera);
		SharkDraw(&shark,&camera);
		for (int i = 0; i < platforms.total; i++)
			Draw_Platform(&platforms.platform[i], &camera);
	}

	
	
}

void game_exit(void)
{
	

	//struct Platform 동적 할당 시 free
	SharkFree(&shark);
}