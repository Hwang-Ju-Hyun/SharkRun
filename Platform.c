#include "Platform.h"
#include "Header.h"
#include "Camera.h"

void InitTileImg(CP_Image* img)
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
		p->platform[i].col.Pos.x = 0.f;
		p->platform[i].col.Pos.y = 0.f;
		p->platform[i].col.h = p->platform[i].height;
		p->platform[i].col.w = p->platform[i].width;
	}
}


//void Draw_Platform(struct Platform* p, struct Camera* _c)
//{
//	CP_Vector Render;
//
//	Render.x = GetRenderPlatPos(p, _c).x;
//	Render.y = GetRenderPlatPos(p, _c).y;
//
//	CP_Graphics_DrawRect(Render.x, Render.y, p->width, p->height);
//
//}

void Draw_Platform(struct Platform* p, CP_Image* img,  struct Camera* _c)
{	
	float w0, w1, w2, h0, h1, h2, posX, posY;
	w0 = (float)CP_Image_GetWidth(img[0]), h0 = (float)CP_Image_GetHeight(img[0]);
	w1 = (float)CP_Image_GetWidth(img[1]), h1 = (float)CP_Image_GetHeight(img[1]);
	w2 = (float)CP_Image_GetWidth(img[2]), h2 = (float)CP_Image_GetHeight(img[2]);

	CP_Vector Render;
	Render.x = GetRenderPlatPos(p, _c).x;
	Render.y = GetRenderPlatPos(p, _c).y;

	posX = Render.x, posY = Render.y;

	// collision area
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawCircle(posX + p->width, posY, 10);
	CP_Settings_StrokeWeight(1.0f);
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));
	CP_Graphics_DrawRect(posX, posY, p->width, p->height);

	
	for (int j = 0; j < 3; j++)
	{
		if (j == 0)
		{
			//CP_Graphics_DrawCircle(p->Pos.x+ p->Pos.x+ p->width)
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
		CP_Image_Draw(name, posX + 60, posY - (h0 / 2) + 1, nw, nh, 255);
	}
	if (p->detail == 2)
	{

		CP_Image name = CP_Image_Load("Assets\\umbrella.png");
		float nw = (float)CP_Image_GetWidth(name), nh = (float)CP_Image_GetHeight(name);
		CP_Image_Draw(name, posX + 120, posY - (nh / 2) + 7, nw, nh, 255);
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