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

void LoadPlatformFromFile(struct Platforms* p)
{
	FILE* _inFile = fopen("tile.dat", "rt");
	if (_inFile == NULL)
	{
		printf("Error! Platform File is not exists : (function)Map_Load\n");
		return;
	}

	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile); //read total
	sscanf(str, "%d", &p->total);

	for (int j = 0; j < p->total; j++)
	{
		fgets(str, BUFFERSIZE, _inFile);
		sscanf(str, "%f %f %d %d %d", &p->platform[j].Pos.x, &p->platform[j].Pos.y,
			&p->platform[j].tileSize, &p->platform[j].type, &p->platform[j].detail);
	}

	fclose(_inFile);
}


void Platform_Init(struct Platforms* p, CP_Image* img)
{
	LoadPlatformFromFile(p);
	
	float dw = (float)(CP_Image_GetWidth(img[0]) + CP_Image_GetWidth(img[2]));
	float ih = (float)CP_Image_GetHeight(img[0]);
	for (int i = 0; i < p->total; i++)
	{
		float w = dw + (CP_Image_GetWidth(img[1]) * p->platform[i].tileSize);
		p->platform[i].width = w - 1;
		p->platform[i].height = ih;

		///////////////////Collision Init Here//////////////////
		p->platform[i].col.Pos.x = p->platform[i].Pos.x;
		p->platform[i].col.Pos.y = p->platform[i].Pos.y;
		p->platform[i].col.h = p->platform[i].height;
		p->platform[i].col.w = p->platform[i].width;
	}
}

void Draw_Platform(struct Platform* p, CP_Image* img)
{
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
				posX = posX + w1;
			}
		}
		else
		{
			CP_Image_Draw(img[2], posX + (w2/2), posY + (h2/2), w2, h2, 255);
		}
	}

	if (p->detail == 1)
	{
		CP_Image name = CP_Image_Load("Assets\\parmTree.png");
		float nw = (float)CP_Image_GetWidth(name), nh = (float)CP_Image_GetHeight(name);
		CP_Image_Draw(name, p->Pos.x + 60, posY - (h0 / 2) + 1, nw, nh, 255);
	}
	if (p->detail == 2)
	{

		CP_Image name = CP_Image_Load("Assets\\umbrella.png");
		float nw = (float)CP_Image_GetWidth(name), nh = (float)CP_Image_GetHeight(name);
		CP_Image_Draw(name, p->Pos.x + 120, posY - (nh / 2) + 7, nw, nh, 255);
	}

	// collision area
	CP_Settings_StrokeWeight(1.0f);
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));
	CP_Graphics_DrawRect(p->col.Pos.x, p->col.Pos.y, p->col.w, p->col.h);
}

void FreeImg(CP_Image* img)
{
	if (img == NULL) return;
	for (int j = 0; j < 3; j++)
	{
		CP_Image_Free(&img[j]);
	}
}