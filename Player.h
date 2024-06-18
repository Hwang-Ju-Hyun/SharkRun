#pragma once
#include "Game.h"

enum direction
{
	LEFT = 0,
	RIGHT = 1,
};

struct Player
{
	CP_Image res[2];
	CP_Vector Pos;
	float width;
	float height;

	float velocity;
	int alpha;
	
	enum direction d;
};

void PlayerInit(struct Player* p);
void PlayerDraw(struct Player* p);
void PlayerMove(struct Player* p, float dt);
