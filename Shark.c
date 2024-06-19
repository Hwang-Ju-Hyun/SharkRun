#include "Game.h"
#include "Shark.h"

void SharkInit(struct Shark* s)
{
	s->res = CP_Image_Load("Assets\\shark.png");

	if (s->res == NULL) return;

	s->width = (float)CP_Image_GetWidth(s->res);
	s->height = (float)CP_Image_GetHeight(s->res);

	s->Pos.x = 0 - s->width + 10.0f;
	s->Pos.y = WINDOW_HEIGHT / 2 - (s->height / 2.0f);

	s->speed = 10.0f;
	s->alpha = 255;

	//s->col.Pos.x = s->Pos.x;
	//s->col.Pos.y = s->Pos.y;

	SharkCollisionArea(s);
}

void SharkDraw(struct Shark* s)
{
	//collision area draw
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));
	CP_Graphics_DrawRect(s->col.Pos.x, s->col.Pos.y, s->col.w, s->col.h);

	//shark
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Image_Draw(s->res, s->Pos.x + (s->width / 2.0f), s->Pos.y + (s->height / 2.0f), s->width, s->height, s->alpha);
}

void SharkMove(struct Shark* s, float dt)
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

	CP_Image_Free(&s->res);
}

void SharkCollisionArea(struct Shark* s)
{
	s->col.Pos.x = s->Pos.x;
	s->col.Pos.y = 0;
	s->col.w = s->width - 20.0f;
	s->col.h = WINDOW_HEIGHT;
}
