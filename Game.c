#include "Game.h"

CP_Color white;
float time = 0;

struct Platforms platforms;
struct Shark shark;
struct Player player;

void game_init(void)
{
	white = CP_Color_Create(255, 255, 255, 255);	

	//�÷��̾� �ʱ�ε�
	Player_Load("player.dat", &player);
	//�÷��� �ʱ�ε�
	Platform_Load("tile.dat", &platforms);	
	//���� ���� �ʱ� ����
	SetJump(&player, 30.f/*�ӵ�*/, 70.f/*�߷�*/, 0.f);
	for (int i = 0; i < platforms.total; i++)
	{
		printf("n = %d, pos = %f %f, size = %f %f\n",
			platforms.total, platforms.platform[i].Pos.x, platforms.platform[i].Pos.y, platforms.platform[i].width, platforms.platform[i].height);
		
		printf("gap = %f %f, type = %d, color = %d %d %d %d\n",
			platforms.platform[i].gap.x, platforms.platform[i].gap.y, platforms.platform[i].type, platforms.platform[i].color.r, platforms.platform[i].color.g, platforms.platform[i].color.b, platforms.platform[i].color.a);
	}

	SharkInit(&shark);
	//PlayerInit(&player);
}

void game_update(void)
{
	CP_Graphics_ClearBackground(white);

	CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
	

	//GameScene����
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	time = CP_System_GetDt();
	
	if(CP_Input_KeyDown(KEY_SPACE))//����
	{		
		player.JumpKeyPressed = true;		

	}
	if (CP_Input_KeyDown(KEY_D))
	{		 
		float right = 150.f * time;
		CP_Vector c_rt = {(player.Pos.x + right),player.Pos.y+0.f };
		SetPos(&player, c_rt);
	}
	if (CP_Input_KeyDown(KEY_A))
	{
		float left = -150.f * time;
		CP_Vector c_lt = { player.Pos.x + left,player.Pos.y + 0.f };
		SetPos(&player, c_lt);		
	}	
	if (player.JumpKeyPressed == true)
	{
		Jump(&player);
		CP_Vector pos = { player.Pos.x,player.Pos.y + player.JumHeight };
		SetPos(&player, pos);
	}		
	

	for (int i = 0; i < platforms.total; i++)
		Draw_Platform(&platforms.platform[i]);

	SharkDraw(&shark);
	SharkMove(&shark, time);
	//���θ޴��� ����
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT)){CP_Engine_SetNextGameState(main_init, main_update, main_exit);}	

	if (CP_Input_KeyTriggered(KEY_1))
		SharkSpeedUp(&shark, 30.0f);

	//PlayerDraw(&player);
	PlayerMove(&player, time);
	//=============
	//====Render===
	//=============
	Draw_Player(&player);
}

void game_exit(void)
{

	//struct Platform ���� �Ҵ� �� free
	SharkFree(&shark);
}