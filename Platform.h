#pragma once
#include "Header.h"
#include "Collision.h"

struct Platform
{
	int totalNum;
	CP_Vector		Pos;
	float			width;
	float			height;
	CP_Vector		gap;
	int				type;
	CP_Color		color;
	struct Collision col;
	//파일에 ground(0)인지 air(1)인지 확인 필요! 아마 파일에 추가적으로 더 필요할 듯
	enum GROUND_OR_AIR ground;
};


void LoadPosFromFile(CP_Vector* pos , FILE* _inFile);
void LoadGapFromFile(CP_Vector* g, FILE* _inFile);
void LoadTotalFromFile(int* n, FILE* _inFile);
void LoadSizeFromFile(float* w, float* h, FILE* _inFile);
void LoadColorFromFile(CP_Color* _col, FILE* _inFile);

void Platform_Load(char* fileName, struct Platform* p);
//void LoadPlatform(char* fileName)
void Draw_Platform(struct Platform* p);
void Save_Platform(char* fileName, struct Platform* p);