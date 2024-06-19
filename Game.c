#include "Game.h"

CP_Color white;
float time = 0;

struct Platforms platforms;
struct Shark shark;
struct Player player;

//void CollisionCheck_Update()
//{
//	for (int i = 0; i < platforms.total; i++)
//	{
//		bool Col = IsCollision(&player, &platforms.platform[i]);
//		
//	}	
//}

void PlayerGravity(struct Player* _pPlayer,int _platformNum,bool IsCol)
{
	float t = CP_System_GetDt();
	if (IsCol)
	{
		if (_pPlayer->foot_col.Pos.y + _pPlayer->foot_col.h > platforms.platform[_platformNum].Pos.y)
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
		_pPlayer->Pos.y = _pPlayer->Pos.y + _pPlayer->velocity * t;
		_pPlayer->foot_col.Pos.y += _pPlayer->velocity * t;
		_pPlayer->body.Pos.y += _pPlayer->velocity * t;
		return;
	}
	_pPlayer->velocity = _pPlayer->velocity - _pPlayer->Acceleration * t;
	_pPlayer->IsGrounded = AIR;
	
	_pPlayer->Pos.y = _pPlayer->Pos.y + _pPlayer->velocity * t;
	_pPlayer->foot_col.Pos.y += _pPlayer->velocity * t;
	_pPlayer->body.Pos.y += _pPlayer->velocity * t;
	return;
}

void game_init(void)
{
	white = CP_Color_Create(255, 255, 255, 255);	

	//플레이어 초기로드
	PlayerInit(&player);
	
	//플랫폼 초기로드
	Platform_Load("tile.dat", &platforms);	
		
	SharkInit(&shark);

	for (int i = 0; i < platforms.total; i++)
	{
		printf("n = %d, pos = %f %f, size = %f %f\n",
			platforms.total, platforms.platform[i].Pos.x, platforms.platform[i].Pos.y, platforms.platform[i].width, platforms.platform[i].height);
		
		printf("gap = %f %f, type = %d, color = %d %d %d %d\n",
			platforms.platform[i].gap.x, platforms.platform[i].gap.y, platforms.platform[i].type, platforms.platform[i].color.r, platforms.platform[i].color.g, platforms.platform[i].color.b, platforms.platform[i].color.a);
	}
}


void drp(struct Player* _pPlayer)
{
	CP_Settings_Fill(CP_Color_Create(155, 155, 155, 0));
	CP_Graphics_DrawRect(_pPlayer->Pos.x, _pPlayer->Pos.y, _pPlayer->width, _pPlayer->height);
}

void game_update(void)
{
	CP_Graphics_ClearBackground(white);
	CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	for (int i = 0; i < platforms.total; i++)
		Draw_Platform(&platforms.platform[i]);

	SharkDraw(&shark);
	SharkMove(&shark, time);

	if (CP_Input_KeyTriggered(KEY_1))
		SharkSpeedUp(&shark, 30.0f);


	time = CP_System_GetDt();
	Move_Player(&player, time);

	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	//↓↓↓↓↓↓절대 지우지 말것↓↓↓↓↓
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	bool col = false;
	int platformNum=0;
	for (int i = 0; i < platforms.total; i++)
	{
		col = IsCollision(&player, &platforms.platform[i]);
		platformNum = i;
		if (col == true)
			break;
	}		
	PlayerGravity(&player, platformNum, col);
	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
	//↑↑↑↑↑절대 지우지 말것↑↑↑↑↑↑
	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑


	//PlayerMove(&player, time);	
	
	//=============
	//====Render===
	//=============
	Draw_Player(&player);	
	Draw_PlayerCollision(&player);	
	//drp(&player);

	

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

			CP_Settings_NoStroke();
		}
	}
}

void game_exit(void)
{
	//struct Platform 동적 할당 시 free
	SharkFree(&shark);
}