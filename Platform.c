#include "Platform.h"
#include "Header.h"


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


void InitPlatform(CP_Image* img)
{
	img[0] = CP_Image_Load("Assets\\tile0.png");
	img[1] = CP_Image_Load("Assets\\tile1.png");
	img[2] = CP_Image_Load("Assets\\tile2.png");
}

#if 0
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

#elif 1
void LoadPlatformFromFile(struct Platforms* p, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile); //read total
	sscanf(str, "%d", &p->total);

	for (int j = 0; j < p->total; j++)
	{
		fgets(str, BUFFERSIZE, _inFile);
		sscanf(str, "%f %f %d %d %d", &p->platform[j].Pos.x, &p->platform[j].Pos.y,
			&p->platform[j].tileSize, &p->platform[j].type, &p->platform[j].detail);
	}
}

#endif

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

void Draw_Platform(struct Platform* p, CP_Image* img)
{
	//CP_Settings_StrokeWeight(1.0f);
	//CP_Settings_Fill(p->color);
	//CP_Graphics_DrawRect(p->Pos.x, p->Pos.y, p->width, p->height);
	float w0, w1, w2, h0, h1, h2, posX, posY;
	w0 = (float)CP_Image_GetWidth(img[0]), h0 = (float)CP_Image_GetHeight(img[0]);
	w1 = (float)CP_Image_GetWidth(img[1]), h1 = (float)CP_Image_GetHeight(img[1]);
	w2 = (float)CP_Image_GetWidth(img[2]), h2 = (float)CP_Image_GetHeight(img[2]);

	posX = p->Pos.x, posY = p->Pos.y;

	for (int j = 0; j < 3; j++)
	{
		if (j == 0)
		{
			CP_Image_Draw(img[0], posX + (w0/2), posY + (h0/2), w0, h0, 255);
			posX = posX + w0;
		}
		
		else if (j == 1)
		{
			for (int i = 0; i < p->tileSize; i++)
			{
				CP_Image_Draw(img[1], posX + (w1/2), posY + (h1/2), w1, h1, 255);
				//if (i == p->tileSize - 1) break;
				posX = posX + w1;
			}
		}
		else
		{
			CP_Image_Draw(img[2], posX + (w2/2), posY + (h2/2), w2, h2, 255);
		}
	}

}

void FreeImg(CP_Image* img)
{
	if (img == NULL) return;
	for (int j = 0; j < 3; j++)
	{
		CP_Image_Free(&img[j]);
	}
}