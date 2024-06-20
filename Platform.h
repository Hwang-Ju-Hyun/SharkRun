#pragma once

#include "Game.h"

#include "Header.h"
#include "Collision.h"

#define MAXPLATFORM 30

enum Detail
{
	Tree = 0,
	Umbrella = 1,
};
struct Platform
{
	int totalNum;
	CP_Vector		Pos;
	float			width;
	float			height;
	int				tileSize;
	enum Detail		detail;
	enum PLATFORM_TYPE		type;

	struct Collision col;
	//파일에 ground(0)인지 air(1)인지 확인 필요! 아마 파일에 추가적으로 더 필요할 듯
	enum GROUND_OR_AIR ground;
};

struct Platforms
{
	int total;
	struct Platform platform[MAXPLATFORM];
};


void LoadTotalFromFile(int* n, FILE* _inFile);
void LoadPosFromFile(CP_Vector* pos, FILE* _inFile);
void LoadSizeFromFile(float* w, float* h, FILE* _inFile);
void LoadGapFromFile(CP_Vector* g, FILE* _inFile);
void LoadColorFromFile(CP_Color* _col, FILE* _inFile);
void LoadTypeFromFile(enum PLATFORM_TYPE* pt, FILE* _inFile);

void InitPlatform(CP_Image* img);
void LoadPlatformFromFile(struct Platforms* p, FILE* _inFile);
void Platform_Load(char* fileName, struct Platforms* p);

void Draw_Platform(struct Platform* p, CP_Image* img);

void FreeImg(CP_Image* img);
