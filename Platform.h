#pragma once

#include "Game.h"

#include "Header.h"
#include "Collision.h"

#define MAXPLATFORM 30

struct Platform
{
	CP_Vector		Pos;
	float			width;
	float			height;
	CP_Vector		gap;
	enum PLATFORM_TYPE		type;
	CP_Color		color;

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
void LoadPlatformFromFile(struct Platforms* p, FILE* _inFile);
void Platform_Load(char* fileName, struct Platforms* p);

void Draw_Platform(struct Platform* p);