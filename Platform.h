#pragma once
#include "Game.h"

#define MAXPLATFORM 30
struct Platform
{
	//int totalNum;
	CP_Vector		Pos;
	float			width;
	float			height;
	CP_Vector		gap;
	enum pTYPE		type;
	CP_Color		color;
};

struct Platforms
{
	int total;
	struct Platform platform[MAXPLATFORM];
};

void LoadTotalFromFile(int* n, FILE* _inFile);
void LoadPosFromFile(CP_Vector* pos , FILE* _inFile);
void LoadSizeFromFile(float* w, float* h, FILE* _inFile);
void LoadGapFromFile(CP_Vector* g, FILE* _inFile);
void LoadColorFromFile(CP_Color* _col, FILE* _inFile);

void LoadTypeFromFile(enum pTYPE* pt, FILE* _inFile);
void LoadPlatformFromFile(struct Platforms* p, FILE* _inFile);
void Platform_Load(char* fileName, struct Platforms* p);

//void LoadPlatform(char* fileName)
void Draw_Platform(struct Platform* p);
void Save_Platform(char* fileName, struct Platforms* p);