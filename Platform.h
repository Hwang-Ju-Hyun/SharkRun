#pragma once

#include "Game.h"

#include "Header.h"
#include "Collision.h"

#define MAXPLATFORM 30

struct Camera;
enum Detail
{
	Tree = 1,
	Umbrella = 2,
};
struct Platform
{
	CP_Vector		Pos;
	float			width;
	float			height;
	int				tileSize;
	enum Detail		detail;
	enum PLATFORM_TYPE		type;

	struct Collision col;
	enum GROUND_OR_AIR ground;
};

struct Platforms
{
	int total;
	struct Platform platform[MAXPLATFORM];
};

//void Draw_Platform(struct Platform* p, struct Camera* _c);
void InitTileImg(CP_Image* img);
void LoadPlatformFromFile(struct Platforms* p);
void Platform_Init(struct Platforms* p, CP_Image* img);

void Draw_Platform(struct Platform* p, CP_Image* img, struct Camera* _c);
void FreeImg(CP_Image* img);

