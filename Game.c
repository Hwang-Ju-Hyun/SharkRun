#include "Game.h"

CP_Color white;
float time = 0;

struct Platforms platforms;
struct Shark shark;
struct Player player;

void GravityUpdate()
{
	for (int i = 0; i < platforms.total; i++)
	{
		bool Col = IsCollision(&player, &platforms.platform[i]);
		if (Col == true)
			player.IsGrounded = GROUND;
		else
			player.IsGrounded = AIR;
	}	
}

void game_init(void)
{
	white = CP_Color_Create(255, 255, 255, 255);	

	//Player_Load_fromFile("player.dat", &player);
	//player.res[0] = CP_Image_Load("Assets\\dog_left.png");
	//player.res[1] = CP_Image_Load("Assets\\dog_right.png");
	//player.alpha = 255;

	PlayerInit(&player);
	SharkInit(&shark);
	Platform_Load("tile.dat", &platforms);	
	
	SetJump(&player, 30.f/*속도*/, 70.f/*중력*/, 0.f);
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

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);


	if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
		CP_Engine_SetNextGameState(main_init, main_update, main_exit);


	for (int i = 0; i < platforms.total; i++)
		Draw_Platform(&platforms.platform[i]);

	SharkDraw(&shark);
	SharkMove(&shark, time);

	if (CP_Input_KeyTriggered(KEY_1))
		SharkSpeedUp(&shark, 30.0f);

	time = CP_System_GetDt();
	Move_Player(&player, time);
	Draw_Player(&player);

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