#include "Game.h"

CP_Color white;
struct Platform platforms;

void game_init(void)
{
	white = CP_Color_Create(255, 255, 255, 255);
	Platform_Load("tile.dat", &platforms);

	printf("n = %d, pos = %f %f, size = %f %f\n",
		platforms.totalNum, platforms.Pos.x, platforms.Pos.y, platforms.width, platforms.height);
	
	printf("gap = %f %f, type = %d, color = %d %d %d %d\n",
		platforms.gap.x, platforms.gap.y, platforms.type, platforms.color.r, platforms.color.g, platforms.color.b, platforms.color.a);
}

void game_update(void)
{
	CP_Graphics_ClearBackground(white);

	CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
	{
		CP_Engine_SetNextGameState(main_init, main_update, main_exit);
	}

	Draw_Platform(&platforms);
}

void game_exit(void)
{

	//struct Platform 동적 할당 시 free
}