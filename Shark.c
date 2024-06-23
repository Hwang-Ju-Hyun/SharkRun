#include "Shark.h"

void SharkInit(struct Shark* s)
{
	
	s->res[0] = CP_Image_Load("Assets\\shark0.png");
	s->res[1] = CP_Image_Load("Assets\\shark1.png");

	s->resIdx = 0;
	s->animTime = 1.0f;

	if (s->res == NULL) return;

	s->width = (float)CP_Image_GetWidth(s->res[0]);
	s->height = (float)CP_Image_GetHeight(s->res[0]);

	s->Pos.x = 0 - s->width + 10.0f;
	s->Pos.y = WINDOW_HEIGHT / 2 - (s->height / 3.0f);

	s->speed = 130.0f;
	s->alpha = 255;

	SharkCollisionArea(s);
}

float sDt = 0;
void SharkDraw(struct Shark* s, struct Camera* c, struct Player* player)
{
	//collision area draw
	/*CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));
	CP_Graphics_DrawRect(s->col.Pos.x, s->col.Pos.y, s->col.w, s->col.h);*/
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));

	CP_Vector Render;
	Render.x = GetRenderSharkColPos(s, c).x;
	Render.y = GetRenderSharkColPos(s, c).y + (player->Pos.y / 2);
	CP_Graphics_DrawRect(Render.x, Render.y, s->col.w, s->col.h);
	
	sDt += CP_System_GetDt();
	if (sDt >= s->animTime)
	{
		sDt = 0;
		s->resIdx = (s->resIdx + 1) % 2; // shark resource 0, 1
	}
	CP_Image_Draw(s->res[s->resIdx], Render.x + (s->width / 2.0f), Render.y + (s->height / 2.0f), s->width, s->height, s->alpha);
}

void SharkMove(struct Shark* s, float dt, struct Player* player)
{
	s->col.Pos.x = s->col.Pos.x + s->speed * dt;
	s->Pos.x = s->Pos.x + s->speed * dt;
}

void SharkSpeedUp(struct Shark* s, float v)
{
	s->speed += v;
}

void SharkFree(struct Shark* s)
{
	if (s->res == NULL) return;

	for(int i=0; i<2; i++)
		CP_Image_Free(&s->res[i]);
}

void SharkCollisionArea(struct Shark* s)
{
	s->col.Pos.x = s->Pos.x;
	s->col.Pos.y = s->Pos.y;
	s->col.w = s->width - 20.0f;
	s->col.h = s->Pos.y + 4000;
}
