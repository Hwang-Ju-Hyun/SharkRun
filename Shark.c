#include "Game.h"
#include "Shark.h"

void SharkInit(struct Shark* s)
{
	s->res = CP_Image_Load("Assets\\shark.png");

	if (s->res == NULL) return;

	s->Pos.x = 0;
	s->Pos.y = WINDOW_HEIGHT / 2;

	s->width = (float)CP_Image_GetWidth(s->res);
	s->height = (float)CP_Image_GetHeight(s->res);

	s->speed = 10.0f;
	s->alpha = 255;
}

void SharkDraw(struct Shark* s)
{
	CP_Image_Draw(s->res, s->Pos.x, s->Pos.y, s->width, s->height, s->alpha);
}

void SharkMove(struct Shark* s, float dt)
{
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
