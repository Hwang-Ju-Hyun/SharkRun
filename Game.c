#include "Game.h"

CP_Color white;
struct Platform platforms;
struct Player player;
void game_init(void)
{
	white = CP_Color_Create(255, 255, 255, 255);
	//플레이어 초기로드
	Player_Load("tile.dat", &player);
	//플랫폼 초기로드
	Platform_Load("tile.dat", &platforms);	
	SetJump(&player, 30.f, 60.f, 0.f);
	printf("n = %d, pos = %f %f, size = %f %f\n",
		platforms.totalNum, platforms.Pos.x, platforms.Pos.y, platforms.width, platforms.height);
	
	printf("gap = %f %f, type = %d, color = %d %d %d %d\n",
		platforms.gap.x, platforms.gap.y, platforms.type, platforms.color.r, platforms.color.g, platforms.color.b, platforms.color.a);
}

void game_update(void)
{
	CP_Graphics_ClearBackground(white);

	CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
	

	//GameScene진입
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	if(CP_Input_KeyDown(KEY_SPACE))//점프
	{		
		player.JumpKeyPressed = true;
	}
	if (CP_Input_KeyDown(KEY_D))
	{		 
		float right = 30.f;
		CP_Vector c_rt = {(player.Pos.x + right),player.Pos.y+0.f };
		SetPos(&player, c_rt);
	}
	if (CP_Input_KeyDown(KEY_A))
	{
		float left = -30.f;
		CP_Vector c_lt = { player.Pos.x + left,player.Pos.y + 0.f };
		SetPos(&player, c_lt);		
	}	
	Jump(&player);

	//메인메뉴로 진입
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT)){CP_Engine_SetNextGameState(main_init, main_update, main_exit);}


	//=============
	//====Render===
	//=============
	Draw_Player(&player);
	Draw_Platform(&platforms);
	
}

void game_exit(void)
{

	//struct Platform 동적 할당 시 free
}