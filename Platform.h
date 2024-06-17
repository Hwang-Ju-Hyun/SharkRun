#pragma once
#include "Header.h"

struct Platform
{
	CP_Vector		Pos;
	float			width;
	float			height;
	int				type;
};

void Platform_Load(FILE* _inFile, char* _str);

void LoadIntegerFromFile(int* _value,FILE* _inFile);
void LoadFloatFromFile(float* _value, FILE* _inFile);
void LoadVectorFromFile(CP_Vector* _vec , FILE* _inFile);

void LoadColorFromFile(CP_Color* _col, FILE* _inFile);
