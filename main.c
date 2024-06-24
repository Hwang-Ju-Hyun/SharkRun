#include "main.h"

CP_Color bgColor;
CP_Image Digipen = NULL;
CP_Image teamLogo = NULL;

float ACCtime = 0;
void main_init(void)
{
	bgColor = CP_Color_Create(0,0,0, 255);
	Digipen = CP_Image_Load("./Assets/DigiPen.png");
	if (Digipen == NULL)
	{
		printf("Tlqkf");
		return;
	}
	teamLogo = CP_Image_Load("./Assets/Teamlogo.png");
		
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
	CP_Font_DrawText("START", WINDOW_WIDTH / 2-40, WINDOW_HEIGHT / 2);
}

void drawStartTex2(const char* str, float texSize, CP_Color color)
{
	CP_Settings_TextSize(texSize);
	CP_Settings_Fill(color);
	CP_Font_DrawText(str, WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2+150.f);
}

void main_update(void)
{
	ACCtime += CP_System_GetDt();
	if (ACCtime <= 3.f)
	{
		CP_Graphics_ClearBackground(bgColor);
		int width = WINDOW_WIDTH;
		int height = WINDOW_HEIGHT;		
		CP_Image_Draw(Digipen, (float)width / 2, (float)height / 2,505*2, 122*2, 255);
	}
	else if (ACCtime > 3.f && ACCtime <= 6.f)
	{
		CP_Graphics_ClearBackground(bgColor);
		int width = WINDOW_WIDTH;
		int height = WINDOW_HEIGHT;				
		CP_Image_Draw(teamLogo, (float)width / 2, (float)height / 2, 617, 208, 255);
	}
	else if(ACCtime>6.f)
	{
		CP_Graphics_ClearBackground(bgColor);

		float menu_PosX = WINDOW_WIDTH / 4 + 110;
		float menu_PosY = WINDOW_HEIGHT / 5 + 100;
		float menu_width = 650.f;
		float menu_height = 200.f;
		CP_Color color = CP_Color_Create(255, 255, 255, 0);

		drawMenu(menu_PosX, menu_PosY, menu_width, menu_height, color);

		CP_Color TexColor = CP_Color_Create(0, 0, 255, 255);
		
		drawStartTex("START", 80.f, TexColor);


		float menu2_PosX = WINDOW_WIDTH / 4 + 110;
		float menu2_PosY = WINDOW_HEIGHT / 5 + 300;
		float menu2_width = 650.f;
		float menu2_height = 200.f;

		drawMenu(menu2_PosX, menu2_PosY, menu2_width, menu2_height, color);
		CP_Color Tex2Color = CP_Color_Create(0, 0, 255, 255);
		drawStartTex2("Exit", 80.f, Tex2Color);

		if (CP_Input_GetMouseX() > menu_PosX && CP_Input_GetMouseX() < menu_PosX + menu_width &&
			CP_Input_GetMouseY() > menu_PosY && CP_Input_GetMouseY() < menu_PosY + menu_height)
		{
			TexColor = CP_Color_Create(255, 0, 0, 255);
			drawStartTex("START", 80.f, TexColor);
			//drawMenu(menu_PosX, menu_PosY, menu_width, menu_height, color);
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				CP_Engine_SetNextGameState(game_init, game_update, game_exit);
			}
		}
		if (CP_Input_GetMouseX() > menu2_PosX && CP_Input_GetMouseX() < menu2_PosX + menu2_width &&
			CP_Input_GetMouseY() > menu2_PosY && CP_Input_GetMouseY() < menu2_PosY + menu2_height)
		{
			Tex2Color = CP_Color_Create(255, 0, 0, 255);
			drawStartTex2("Exit", 80.f, Tex2Color);
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				CP_Engine_Terminate();
			}
			
		}
	}
	

	
}

void main_exit(void)
{	
}

int main(void)
{
	CP_System_SetWindowTitle("Shank Run!");
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	CP_Engine_SetNextGameState(main_init, main_update, main_exit);
	CP_Engine_Run();
	return 0;
}
