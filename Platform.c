#include "Platform.h"
#include "Header.h"
#include "Camera.h"

void InitTileImg(CP_Image* img)
{
	img[0] = CP_Image_Load("Assets\\tile0.png");
	img[1] = CP_Image_Load("Assets\\tile1.png");
	img[2] = CP_Image_Load("Assets\\tile2.png");
}

int LoadPlatformFromFile(struct Platforms* p, struct Player* player)
{
	FILE* _inFile = fopen("tile.dat", "rt");
	if (_inFile == NULL)
	{
		printf("Error! Platform File is not exists : (function)Map_Load\n");
		return 0;
	}

	int RandNum = 0;
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile); //read total
	sscanf_s(str, "%d %d", &p->total, &RandNum);

	///////////////////////////////
	AllocatePlatform(p, p->total);
	InitPlatformsMemory(p, RandNum, player);


	//밑에 주석처리된 코드가 왜 필요한지 설명 필요합니다.
	//for (int j = 0; j < (p->total - RandNum); j++)
	//{
	//	////////////////////////////
	//	struct Platform* pf = GetFirstDeadPlatform(p);
	//	p->AlivePlatforms++;
	//	pf->alive = Alive;

	//	/*fgets(str, BUFFERSIZE, _inFile);
	//	sscanf(str, "%f %f %d %d %d", &pf->Pos.x, &pf->Pos.y,
	//		&pf->tileSize, &pf->type, &pf->detail);
	//	sscanf(str, "%f %f %d %d %d", &p->platform[j].Pos.x, &p->platform[j].Pos.y,
	//		&p->platform[j].tileSize, &p->platform[j].type, &p->platform[j].detail);*/
	//}

	fclose(_inFile);

	return 1;
}


/* 안쓰는 거 가틈
void Platform_Init(struct Platforms* p, CP_Image* img, struct Player* player)
{
	LoadPlatformFromFile(p, player);
	
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
*/


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
	p->lifeTime =  (x / 280); // + @ : Adjust time depending on difficulty
	//p->lifeTime = 4.0f;
	p->spanTime = 0;
	///////////////////Collision Init Here//////////////////
	p->col.Pos.x = p->Pos.x;
	p->col.Pos.y = p->Pos.y;
	p->col.h = p->height;
	p->col.w = p->width;
}

float tile_width[4] = { 0, 70, 120, 170 };

void InitPlatformRandom(struct Platforms* pfs, struct Platform* p, struct Player* player, enum AliveOrDead a)
{
	if (p == NULL) return;

	float x, y;
	int tileSize;

	float degree = CP_Random_RangeFloat(-45, 45);
	float rx = CP_Random_RangeFloat(0, 1280);
	float ry = CP_Random_RangeFloat(0, 100);

	printf("player x = %f, y = %f\n", player->Pos.x, player->Pos.y);
	
	x = fabsf((cosf(degree) * rx)) + player->Pos.x + player->width;
	y = (sinf(degree) * ry) + player->Pos.y + player->height + (player->JumHeight * 3 / 4);
	printf("x = %f, y = %f\n", x, y);

	tileSize = CP_Random_RangeInt(1, 3);

	/*for (int i = 0; i < pfs->total; i++)
	{
		if (platformCollision(&pfs->pf[i], &x, &y, tile_width[tileSize], TILEHEIGHT))
		{
			printf("collision and correction %d\n", i);
		}
	}*/


	int type = 0;
	int d = 0;
	if (tileSize > 1)
		d = CP_Random_RangeInt(1, 2);

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

//float dt = 0;
void UpdatePlatform(struct Platforms* pfs, struct Platform* p)
{
	if (p == NULL) return;

	p->spanTime += CP_System_GetDt();
	if(p->lifeTime <= p->spanTime)
		KillPlatform(pfs, p);
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
void InitPlatformsMemory(struct Platforms* pfs, int nr, struct Player* player)
{
	if (pfs == NULL) return;

	int i = 0;
	int Alive = 0;

	for (i = 0; i < pfs->total; i++)
	{
		if (i < nr)
			Alive = 1;
		else
			Alive = 0;

		InitPlatformRandom(pfs, &pfs->pf[i], player, Alive);
		
		if (Alive)
		{
			int hasItem = CP_Random_RangeInt(0, 1); // 무작위로 이 플랫폼에 아이템이 있는지 결정
			if (hasItem)
			{
				InitItem(pfs->pf[i].item, &pfs->pf[i]);
			}
		}
	}

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

void UpdateAllPlatforms(const struct Platforms* pfs, struct Player* player)
{
	if (pfs == NULL) return;
	for (int i = 0; i < pfs->total; i++)
	{
		if (pfs->pf[i].alive == Alive)
		{
			UpdatePlatform(pfs, &pfs->pf[i]);

			//// 아이템이 살아있으면 업데이트
			//if (pfs->pf[i].item->IsAlive)
			//{
			//	ItemUpdate(pfs->pf[i].item, player); // 플레이어와 상어가 여기서 사용된다고 가정
			//}
		}
	}
}

void DrawAllPlatforms(const struct Platforms* pfs, CP_Image* img, struct Camera* c)
{
	if (pfs == NULL) return;

	for (int i = 0; i < pfs->total; i++)
	{
		if (pfs->pf[i].alive == Alive)
			DrawPlatform(&pfs->pf[i], img, c);

		//if (pfs->pf[i].item->IsAlive)
		//{
		//	DrawItem(pfs->pf[i].item, c);
		//}
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