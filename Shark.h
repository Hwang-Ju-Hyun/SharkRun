#pragma once
#include "Header.h"

struct Shark
{	
	CP_Image res;
	CP_Vector Pos;
	float width;
	float height;
	float speed;
	int alpha;
};

void SharkInit(struct Shark* s);
void SharkDraw(struct Shark* s);
void SharkMove(struct Shark* s, float dt);
void SharkSpeedUp(struct Shark* s, float v);
void SharkFree(struct Shark* s);
