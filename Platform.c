#include "Platform.h"
#include "Header.h"
#include "Camera.h"

void InitTileImg(CP_Image* img)
{
	img[0] = CP_Image_Load("Assets\\tile0.png");
	img[1] = CP_Image_Load("Assets\\tile1.png");
	img[2] = CP_Image_Load("Assets\\tile2.png");
}

int LoadPlatformFromFile(struct Platforms* p)
{
	FILE* _inFile = fopen("tile.dat", "rt");
	if (_inFile == NULL)
	{
		printf("Error! Platform File is not exists : (function)Map_Load\n");
		return 0;
	}

	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile); //read total
	sscanf(str, "%d", &p->total);

	///////////////////////////////
	AllocatePlatform(p, p->total);
	InitPlatformsMemory(p);

	for (int j = 0; j < p->total; j++)
	{
		////////////////////////////
		struct Platform* pf = GetFirstDeadPlatform(p);
		p->AlivePlatforms++;
		pf->alive = Alive;

		fgets(str, BUFFERSIZE, _inFile);
		sscanf(str, "%f %f %d %d %d", &p->pf[j].Pos.x, &p->pf[j].Pos.y,
			&p->pf[j].tileSize, &p->pf[j].type, &p->pf[j].detail);
		//sscanf(str, "%f %f %d %d %d", &p->platform[j].Pos.x, &p->platform[j].Pos.y,
		//	&p->platform[j].tileSize, &p->platform[j].type, &p->platform[j].detail);
	}

	fclose(_inFile);
	return 1;
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

void Draw_Platform(struct Platform* p, CP_Image* img,  struct Camera* _c)
{	
	float w0, w1, w2, h0, h1, h2;
	float posX, posY;
	w0 = (float)CP_Image_GetWidth(img[0]), h0 = (float)CP_Image_GetHeight(img[0]);
	w1 = (float)CP_Image_GetWidth(img[1]), h1 = (float)CP_Image_GetHeight(img[1]);
	w2 = (float)CP_Image_GetWidth(img[2]), h2 = (float)CP_Image_GetHeight(img[2]);

	CP_Vector Render;

	Render.x = GetRenderPlatPos(p, _c).x;
	Render.y = GetRenderPlatPos(p, _c).y;

	posX = ceilf(Render.x), posY = ceilf(Render.y);

	// collision area
	//CP_Settings_StrokeWeight(1.0f);
	//CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));
	//CP_Graphics_DrawRect(posX, posY, p->width, p->height);
	
	/*
	int pos_count = 0;
	float pos_x[100] = {0};
	float _w[100] = { 0 };
	*/

	for (int j = 0; j < 3; j++)
	{
		if (j == 0)
		{
			//_w[pos_count] = w0;
			//pos_x[pos_count++] = posX + (w0 / 2);
			
			CP_Image_Draw(img[0], posX + (w0/2), posY + (h0/2), w0, h0, 255);
			posX = posX + w0;
		}
		
		else if (j == 1)
		{
			for (int i = 0; i < p->tileSize; i++)
			{
				//_w[pos_count] = w1;
				//pos_x[pos_count++] = posX + (w1 / 2);
				CP_Image_Draw(img[1], posX + (w1/2), posY + (h1/2), w1, h1, 255);
				posX = posX + w1;
			}
		}
		else
		{
			//_w[pos_count] = w2;
			//pos_x[pos_count++] = posX + (w2 / 2);
			CP_Image_Draw(img[2], posX + (w2/2), posY + (h2/2), w2, h2, 255);
		}
	}

	/*
	float diff = 0;
	for (int i = 0; i < pos_count-1; ++i)
	{
		float dx = pos_x[i + 1] - pos_x[i];
		float w = (_w[i + 1] + _w[i])/2.f;
		if (dx != w)
		{
			diff += dx - _w[i];
		}
	}
	*/

	if (p->detail == 1)
	{
		CP_Image name = CP_Image_Load("Assets\\parmTree.png");
		float nw = (float)CP_Image_GetWidth(name), nh = (float)CP_Image_GetHeight(name);
		CP_Image_Draw(name, posX - 20, posY - (h0 / 2) + 1, nw, nh, 255);
	}
	if (p->detail == 2)
	{
		CP_Image name = CP_Image_Load("Assets\\umbrella.png");
		float nw = (float)CP_Image_GetWidth(name), nh = (float)CP_Image_GetHeight(name);
		CP_Image_Draw(name, posX - 20, posY - (nh / 2) + 7, nw, nh, 255);
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

void InitPlatform(struct Platforms* pfs, struct Platform* p, enum AliveOrDead a, float x, float y, int tileSize, int type, int detail)
{
	if (p == NULL) return;
	
	if (a) pfs->AlivePlatforms++;
	p->alive = a;
	p->Pos.x = x;
	p->Pos.y = y;
	p->tileSize = tileSize;
	p->type = type;
	p->detail = detail;

	CP_Image img0 = CP_Image_Load("Assets\\tile0.png");
	CP_Image img1 = CP_Image_Load("Assets\\tile1.png");
	float dw = (float)(CP_Image_GetWidth(img0) * 2);
	float ih = (float)CP_Image_GetHeight(img0);

	float w = dw + (CP_Image_GetWidth(img1) * p->tileSize);
	p->width = w - 1;
	p->height = ih;

	///////////////////Collision Init Here//////////////////
	p->col.Pos.x = p->Pos.x;
	p->col.Pos.y = p->Pos.y;
	p->col.h = p->height;
	p->col.w = p->width;
}

void InitPlatformRandom(struct Platforms* pfs, struct Platform* p, enum AliveOrDead a)
{
	if (p == NULL) return;

	float x = CP_Random_RangeFloat(0, (float)WINDOW_WIDTH);
	float y = CP_Random_RangeFloat(0, (float)WINDOW_HEIGHT);
	int tileSize = (CP_Random_GetInt() % 3) + 1;
	int type = 0;
	int d = 0;
	if (tileSize > 1)
		d = (CP_Random_GetInt() % 2) + 1;

	InitPlatform(pfs, p, a, x, y, tileSize, type, d);
}

void AllocatePlatform(struct Platforms* pfs, int size)
{
	if (pfs == NULL) return;

	DeallocatePlatform(pfs);
	pfs->total = size;
	pfs->AlivePlatforms = 0;
	pfs->pf = malloc(size * sizeof(struct Platform));
}

void DeallocatePlatform(struct Platforms* pfs)
{
	if (pfs == NULL) return;

	pfs->total = 0;

	if (pfs->pf != NULL)
		free(pfs->pf);

	pfs->pf = NULL;
}

void KillPlatform(struct Platforms* pfs, struct Platform* p)
{
	if (p == NULL) return;
	if (p->alive == Alive)
		pfs->AlivePlatforms--;

	p->alive = Dead;
}

float dt = 0;
void UpdatePlatform(struct Platforms* pfs, struct Platform* p)
{
	if (p == NULL) return;
	dt = CP_System_GetSeconds();
	if (((int)dt % 5) == 0)
	{
		KillPlatform(pfs, p);
		dt = 0;
	}
}

void DrawPlatform(struct Platform* p, CP_Image* img, struct Camera* c)
{
	if (p == NULL) return;

	float w0, w1, w2, h0, h1, h2;
	float posX, posY;
	w0 = (float)CP_Image_GetWidth(img[0]), h0 = (float)CP_Image_GetHeight(img[0]);
	w1 = (float)CP_Image_GetWidth(img[1]), h1 = (float)CP_Image_GetHeight(img[1]);
	w2 = (float)CP_Image_GetWidth(img[2]), h2 = (float)CP_Image_GetHeight(img[2]);

	CP_Vector Render;

	Render.x = GetRenderPlatPos(p, c).x;
	Render.y = GetRenderPlatPos(p, c).y;

	posX = ceilf(Render.x), posY = ceilf(Render.y);

	// collision area
	//CP_Settings_StrokeWeight(1.0f);
	//CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));
	//CP_Graphics_DrawRect(posX, posY, p->width, p->height);

	for (int j = 0; j < 3; j++)
	{
		if (j == 0)
		{
			CP_Image_Draw(img[0], posX + (w0 / 2), posY + (h0 / 2), w0, h0, 255);
			posX = posX + w0;
		}

		else if (j == 1)
		{
			for (int i = 0; i < p->tileSize; i++)
			{
				CP_Image_Draw(img[1], posX + (w1 / 2), posY + (h1 / 2), w1, h1, 255);
				posX = posX + w1;
			}
		}
		else
		{
			CP_Image_Draw(img[2], posX + (w2 / 2), posY + (h2 / 2), w2, h2, 255);
		}
	}

	if (p->detail == 1)
	{
		CP_Image name = CP_Image_Load("Assets\\parmTree.png");
		float nw = (float)CP_Image_GetWidth(name), nh = (float)CP_Image_GetHeight(name);
		CP_Image_Draw(name, posX - 20, posY - (h0 / 2) + 1, nw, nh, 255);
	}
	if (p->detail == 2)
	{
		CP_Image name = CP_Image_Load("Assets\\umbrella.png");
		float nw = (float)CP_Image_GetWidth(name), nh = (float)CP_Image_GetHeight(name);
		CP_Image_Draw(name, posX - 20, posY - (nh / 2) + 7, nw, nh, 255);
	}
}
void InitPlatformsMemory(struct Platforms* pfs)
{
	if (pfs == NULL) return;

	int i = 0;
	for (i = 0; i < pfs->total; i++)
		InitPlatformRandom(pfs, &pfs->pf[i], Dead);
}

void DeleteAllPlatforms(struct Platforms* pfs)
{
	if (pfs == NULL) return;
	for (int i = 0; i < pfs->total; i++)
		KillPlatform(pfs, &pfs->pf[i]);
}

struct Platform* GetFirstDeadPlatform(struct Platforms* pfs)
{
	if (pfs == NULL) return NULL;

	int i = 0;
	for (i = 0; i < pfs->total; i++)
	{
		if (pfs->pf[i].alive == Dead)
			return &pfs->pf[i];
	}

	return NULL;
}

void UpdateAllPlatforms(const struct Platforms* pfs)
{
	if (pfs == NULL) return;
	for (int i = 0; i < pfs->total; i++)
	{
		if (pfs->pf[i].alive == Alive)
			UpdatePlatform(pfs, &pfs->pf[i]);
	}
}

void DrawAllPlatforms(const struct Platforms* pfs, CP_Image* img, struct Camera* c)
{
	if (pfs == NULL) return;

	for (int i = 0; i < pfs->total; i++)
	{
		if (pfs->pf[i].alive == Alive)
			DrawPlatform(&pfs->pf[i], img, c);
	}
}

int SavePlatforms(struct Platforms* pfs)
{
	FILE* outFile = fopen("tile.dat", "w");

	if (outFile == NULL) return 0;
	fprintf(outFile, "%d\n", pfs->total);

	for (int i = 0; i < pfs->total; i++)
	{
		fprintf(outFile, "%f %f %d %d %d\n", pfs->pf[i].Pos.x, pfs->pf[i].Pos.y,
						pfs->pf[i].tileSize, pfs->pf[i].type, pfs->pf[i].detail);
	}

	fclose(outFile);
	return 1;
}