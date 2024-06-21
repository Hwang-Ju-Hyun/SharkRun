#pragma once

#include "Game.h"

#include "Header.h"
#include "Collision.h"

#define MAXPLATFORM 30

struct Camera;

enum AliveOrDead
{
	Dead = 0,
	Alive = 1
};

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
	//float			lifeTime;

	int				tileSize;

	enum Detail		detail;
	enum PLATFORM_TYPE		type;
	enum AliveOrDead alive;
	enum GROUND_OR_AIR ground;
	struct Collision col;
};

struct Platforms
{
	int total;
	int AlivePlatforms;

	struct Platform platform[MAXPLATFORM];
	struct Platform* pf;
};


//void Draw_Platform(struct Platform* p, struct Camera* _c);
void InitTileImg(CP_Image* img);
int LoadPlatformFromFile(struct Platforms* p);
void Platform_Init(struct Platforms* p, CP_Image* img);

void Draw_Platform(struct Platform* p, CP_Image* img, struct Camera* _c);
void FreeImg(CP_Image* img);

void InitPlatform(struct Platforms* pfs, struct Platform* p, enum AliveOrDead a, float x, float y, int tileSize, int type, int detail);
void InitPlatformRandom(struct Platforms* pfs, struct Platform* p,  enum AliveOrDead a);
void AllocatePlatform(struct Platforms* pfs, int size);
void DeallocatePlatform(struct Platforms* pfs);
void KillPlatform(struct Platforms* pfs, struct Platform* p);
void UpdatePlatform(struct Platforms* pfs, struct Platform* p);
void DrawPlatform(struct Platform* p, CP_Image* img, struct Camera* c);

void InitPlatformsMemory(struct Platforms* pfs);
void DeleteAllPlatforms(struct Platforms* pfs);
struct Platform* GetFirstDeadPlatform(struct Platforms* pfs);

void UpdateAllPlatforms(const struct Platforms* pfs);
void DrawAllPlatforms(const struct Platforms* pfs, CP_Image* img, struct Camera* c);

int SavePlatforms(struct Platforms* pfs);