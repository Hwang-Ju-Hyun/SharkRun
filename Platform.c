#include "Platform.h"

void LoadPosFromFile(CP_Vector* pos, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%f %f", &pos->x, &pos->y);
}

void LoadGapFromFile(CP_Vector* g, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%f %f", &g->x, &g->y);
}

void LoadTotalFromFile(int* n, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%d", n);
}

void LoadSizeFromFile(float* w, float* h, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%f %f", w, h);
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

void Platform_Load(char* fileName, struct Platform* p)
{

	FILE* _inFile = fopen(fileName, "rt");

	if (_inFile == NULL)
	{
		printf("Error! Platform File is not exists : (function)Map_Load\n");
		return;
	}

	//char str[BUFFERSIZE] = { '\0' };

	//MAP_LOAD	
	//1. ÇÃ·§Æû °¹¼ö ºÒ·¯¿À±â
	LoadTotalFromFile(&p->totalNum, _inFile);

	//2. ÇÃ·§Æû Position
	LoadPosFromFile(&p->Pos, _inFile);
	
	//3. ÇÃ·§Æû »çÀÌÁî
	LoadSizeFromFile(&p->width, &p->height, _inFile);

	//4. gap »çÀÌÁî
	LoadGapFromFile(&p->gap, _inFile);		

	//color
	LoadColorFromFile(&p->color, _inFile);

	//5. ÇÃ·§Æû Å¸ÀÔ <- º¸·ùÁß 
	LoadTotalFromFile(&p->type, _inFile);
	//³ªÁß¿¡ ÇÕÄ¥°Å¶ó ÀÏ´Ü Total

	fclose(_inFile);
}

void Draw_Platform(struct Platform* p)
{
	CP_Settings_StrokeWeight(1.0f);
	CP_Settings_Fill(p->color);
	CP_Graphics_DrawRect(p->Pos.x, p->Pos.y, p->width, p->height);

}
void Save_Platform(char* fileName, struct Platform* p)
{
	FILE* fp = fopen(fileName, "wt");

	if (fp == NULL) return;

	fclose(fp);
}