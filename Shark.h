#pragma once
#include "Header.h"
#include "Collision.h"

#include "Header.h"

struct Shark
{	
	CP_Image res[2];
	int resIdx;
	float animTime;

	CP_Vector Pos;
	float width;
	float height;
	float speed;
	int alpha;

	struct Collision col;
};

void SharkInit(struct Shark* s);
void SharkDraw(struct Shark* s, float dt);
void SharkMove(struct Shark* s, float dt);
void SharkSpeedUp(struct Shark* s, float v);
void SharkFree(struct Shark* s);

void SharkCollisionArea(struct Shark* s);