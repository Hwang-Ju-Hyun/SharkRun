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
	//���Ͽ� ground(0)���� air(1)���� Ȯ�� �ʿ�! �Ƹ� ���Ͽ� �߰������� �� �ʿ��� ��
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