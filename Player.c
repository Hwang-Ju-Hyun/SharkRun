#include "Header.h"
#include "Player.h"
#include "Collision.h"

/*
void LoadVelocityFromFile(float* _vel, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%f", _vel);
}
void Player_Load_fromFile(char* fileName, struct Player* p)
{

	FILE* _inFile = fopen(fileName, "rt");

	if (_inFile == NULL)
	{
		printf("Error! Platform File is not exists : (function)Map_Load\n");
		return;
	}

	//Player_LOAD			
	//1. 플레이어 Position
	LoadPosFromFile(&p->Pos, _inFile);

	//3. 플레이어 사이즈
	LoadSizeFromFile(&p->width, &p->height, _inFile);

	//4. 플레이어 속도
	LoadVelocityFromFile(&p->velocity, _inFile);

	//5. 플레이어 색깔
	LoadColorFromFile(&p->colors, _inFile);

	fclose(_inFile);
}
*/

void PlayerInit(struct Player* p)
{
	p->res[0] = CP_Image_Load("Assets\\dog_left.png");
	p->res[1] = CP_Image_Load("Assets\\dog_right.png");

	p->Pos.x = 500.f;
	p->Pos.y = 100.f;

	p->width =  (float)CP_Image_GetWidth(p->res[0]);
	p->height = (float)CP_Image_GetHeight(p->res[0]);

	p->velocityX = 0.f;		
	p->velocityY = 0.f;
	p->speed = 200.f;
	p->alpha = 255;
	
	p->body.w = p->width-10.f;
	p->body.h =p->height-10.f;

	p->JumHeight = 600.f;
	
	p->d = RIGHT;	
}

void SetPlayer(struct Player* p, CP_Vector pos, float w, float h, float grav, float v, float jump, int a)
{
	p->Pos = pos;
	p->width = w;
	p->height = h;
	
	p->JumHeight = jump;
	p->alpha = a;
}


void Draw_Player(struct Player* _pPlayer, struct Camera* c)
{
	/*CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(_pPlayer->body.Pos.x, _pPlayer->body.Pos.y, _pPlayer->body.w, _pPlayer->body.h);*/

	CP_Image tmp = _pPlayer->res[1];
	if (_pPlayer->d == LEFT)
		tmp = _pPlayer->res[0];
	CP_Vector Render;
	Render.x = GetRenderPlayerPos(_pPlayer, c).x;
	Render.y = GetRenderPlayerPos(_pPlayer, c).y;
	Render.x += (_pPlayer->width / 2.0f);
	Render.y += (_pPlayer->height / 2.0f);
	CP_Image_Draw(tmp, Render.x, Render.y, _pPlayer->width, _pPlayer->height, _pPlayer->alpha);
}

void SetPos(struct Player* _pPlayer, CP_Vector _pVec)
{
	_pPlayer->Pos = _pVec;
}
void SetWidth(struct Player* _pPlayer)
{
	_pPlayer->width = (float)CP_Image_GetWidth(_pPlayer->res[0]);
}
void SetHeight(struct Player* _pPlayer)
{
	_pPlayer->height = (float)CP_Image_GetHeight(_pPlayer->res[0]);
}
const CP_Vector GetPos(struct Player* _pPlayer)	
{
	return _pPlayer->Pos;
}
const float GetHeight(struct Player* _pPlayer)
{
	return _pPlayer->height;
}
const float GetWidth(struct Player* _pPlayer)
{
	return _pPlayer->width;
}

void Move_Player(struct Player* _pPlayer,struct Platforms* _pPlatforms, float dt)
{
	if(CP_Input_KeyTriggered(KEY_SPACE))//점프
	{
		//이단점프 방지
		if (_pPlayer->IsGrounded==GROUND)
		{
			_pPlayer->velocityY -= _pPlayer->JumHeight;
			_pPlayer->IsGrounded = AIR;
		}		
	}	
	// 좌우 이동 처리
	if (CP_Input_KeyDown(KEY_D))
	{
		_pPlayer->d = RIGHT;		
		_pPlayer->velocityX = _pPlayer->speed;
	}
	else if (CP_Input_KeyDown(KEY_A))
	{
		_pPlayer->d = LEFT;
		_pPlayer->velocityX = -_pPlayer->speed;
	}
	else
	{
		_pPlayer->velocityX = 0;
	}
}

void PlayerBodyCollisionArea(struct Player* p)
{
	p->body.Pos.x = p->Pos.x;
	p->body.Pos.y = p->Pos.y;
	p->body.w = p->width;
	p->body.h = p->height;
}