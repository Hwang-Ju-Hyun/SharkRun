#include "Platform.h"
#include "Header.h"
#include "Camera.h"

void LoadTotalFromFile(int* n, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%d", n);
}

void LoadPosFromFile(CP_Vector* pos, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%f %f", &pos->x, &pos->y);
}

void LoadSizeFromFile(float* w, float* h, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%f %f", w, h);
}

void LoadGapFromFile(CP_Vector* g, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%f %f", &g->x, &g->y);
}

void LoadColorFromFile(CP_Color* _col, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);

	int c[4] = { 0 };

	sscanf(str, "%d %d %d %d", &c[0], &c[1], &c[2], &c[3]);

	for (int i = 0; i < 4; i++)
		_col->rgba[i] = (char)c[i];
}

void LoadTypeFromFile(enum PLATFORM_TYPE* pt, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%d", pt);
}

void LoadPlatformFromFile(struct Platforms* p, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	int color[4] = { 0 };
	fgets(str, BUFFERSIZE, _inFile); //read total
	sscanf(str, "%d", &p->total);

	for (int j = 0; j < p->total; j++)
	{
		fgets(str, BUFFERSIZE, _inFile);
		sscanf(str, "%f %f %f %f %f %f %d %d %d %d %d", &p->platform[j].Pos.x, &p->platform[j].Pos.y,
			&p->platform[j].width, &p->platform[j].height, &p->platform[j].gap.x, &p->platform[j].gap.y,
			&color[0], &color[1], &color[2], &color[3], &p->platform[j].type);

		for (int i = 0; i < 4; i++)
			p->platform[j].color.rgba[i] = (char)color[i];
	}
}
void Platform_Load(char* fileName, struct Platforms* p)
{

	FILE* _inFile = fopen(fileName, "rt");

	if (_inFile == NULL)
	{
		printf("Error! Platform File is not exists : (function)Map_Load\n");
		return;
	}

	LoadPlatformFromFile(p, _inFile);

	fclose(_inFile);
}

void Draw_Platform(struct Platform* p, struct Camera* _c)
{
	CP_Vector Render;
	Render.x = GetRenderPlatPos(p,_c).x;
	Render.y = GetRenderPlatPos(p,_c).y;
	CP_Settings_StrokeWeight(1.0f);
	CP_Settings_Fill(p->color); 
	CP_Graphics_DrawRect(Render.x, Render.y, p->width, p->height);
}