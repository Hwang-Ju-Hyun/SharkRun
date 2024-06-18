#include "Player.h"

void PlayerInit(struct Player* p)
{
	p->res[0] = CP_Image_Load("dog_left.png");
	p->res[1] = CP_Image_Load("dog_right.png");

	p->Pos.x = 140.0f;
	p->Pos.y = 600.0f - 30.0f;

	p->width = (float)CP_Image_GetWidth(p->res[0]);
	p->height = (float)CP_Image_GetHeight(p->res[0]);

	p->velocity = 80.0f;
	p->alpha = 255;

	p->d = RIGHT;
}

void PlayerDraw(struct Player* p)
{
	CP_Image tmp = p->res[1];
	if (p->d == LEFT)
		tmp = p->res[0];

	//else if (p->d == RIGHT) tmp = p->res[1];

	CP_Image_Draw(tmp, p->Pos.x, p->Pos.y, p->width, p->height, p->alpha);
}

void PlayerMove(struct Player* p, float dt)
{
	if (CP_Input_KeyDown(KEY_RIGHT))
	{
		p->d = RIGHT;
		p->Pos.x += p->velocity * dt;
	}

	if (CP_Input_KeyDown(KEY_LEFT))
	{
		p->d = LEFT;
		p->Pos.x -= p->velocity * dt;
	}

	if (CP_Input_KeyDown(KEY_UP))
	{
		p->Pos.y -= p->velocity * dt;
	}

	if (CP_Input_KeyDown(KEY_DOWN))
	{
		p->Pos.y += p->velocity * dt;
	}

	PlayerDraw(p);
}