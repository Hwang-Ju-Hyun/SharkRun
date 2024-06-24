#include "main.h"

CP_Color bgColor;

void main_init(void)
{
	bgColor = CP_Color_Create(255, 255, 255, 255);
}

void drawMenu(float x,float y,float w,float h,CP_Color color)
{	
	CP_Settings_Fill(color);	
	CP_Graphics_DrawRect(x, y, w, h);
}

void drawStartTex(const char* str, float texSize, CP_Color color)
{
	CP_Settings_TextSize(texSize);
	CP_Settings_Fill(color);
	CP_Font_DrawText("START", WINDOW_WIDTH / 2-60, WINDOW_HEIGHT / 2);
}

void main_update(void)
{	
	CP_Graphics_ClearBackground(bgColor);

	
	float menu_PosX = WINDOW_WIDTH / 4 + 22;
	float menu_PosY = WINDOW_HEIGHT / 5 + 100;
	float menu_width=650.f;
	float menu_height = 200.f;
	CP_Color color = CP_Color_Create(255, 255,255,255);

	drawMenu(menu_PosX, menu_PosY, menu_width, menu_height,color);
	
	CP_Color TexColor = CP_Color_Create(0, 0, 255, 255);
	drawStartTex("START", 80.f, TexColor);
	
	

	if (CP_Input_GetMouseX() > menu_PosX && CP_Input_GetMouseX() < menu_PosX + menu_width &&
		CP_Input_GetMouseY() > menu_PosY && CP_Input_GetMouseY() < menu_PosY + menu_height)
	{
		TexColor= CP_Color_Create(255, 0, 0, 255);
		drawStartTex("START", 80.f, TexColor);
		//drawMenu(menu_PosX, menu_PosY, menu_width, menu_height, color);
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
		{
			CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		}
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
