#include "main.h"


CP_Color bgColor;

void main_init(void)
{
	bgColor = CP_Color_Create(255, 255, 255, 255);
}

void main_update(void)
{	
	CP_Graphics_ClearBackground(bgColor);

	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Main", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
	{
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	}
}

void main_exit(void)
{
	//exit
}

int main(void)
{
	CP_System_SetWindowTitle("Shank Run!");
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	CP_Engine_SetNextGameState(main_init, main_update, main_exit);
	CP_Engine_Run();
	return 0;
}
