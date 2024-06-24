#include "Header.h"
#include "Player.h"
#include "Collision.h"


void PlayerInit(struct Player* p)
{
	p->res[0] = CP_Image_Load("Assets\\dog_left.png");
	p->res[1] = CP_Image_Load("Assets\\dog_right.png");

	p->Pos.x = 100.f;
	p->Pos.y = 50.f;

	p->width =  (float)CP_Image_GetWidth(p->res[0]);
	p->height = (float)CP_Image_GetHeight(p->res[0]);

	p->velocityX = 0.f;		
	p->velocityY = 0.f;
	p->speed = 400.f;

	p->alpha = 255;
	
	p->JumHeight = 600.f;
	
	p->d = RIGHT;	
	p->IsAlive = true;

	p->soundOccur = false;
	//p->IsPlayerItemGet = false;
}

void SetPlayer(struct Player* p, CP_Vector pos, float w, float h, float grav, float v, float jump, int a)
{
	p->Pos = pos;
	p->width = w;
	p->height = h;
	
	p->JumHeight = jump;
	p->alpha = a;
}

void PlayerDraw(struct Player* p, struct Camera* c)
{
	//collision area draw
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));
	CP_Settings_StrokeWeight(0.5f);
	CP_Graphics_DrawRect(p->body.Pos.x, p->body.Pos.y, p->body.w, p->body.h);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Image tmp = p->res[1];
	if (p->d == LEFT)
		tmp = p->res[0];

	CP_Vector Render;
	Render.x = GetRenderPlayerPos(p, c).x;
	Render.y = GetRenderPlayerPos(p, c).y;
	CP_Image_Draw(tmp, Render.x, Render.y, p->width, p->height, p->alpha);
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
			_pPlayer->soundOccur = true;
		}		
	}		
	// 좌우 이동 처리
	if (CP_Input_KeyDown(KEY_D) || CP_Input_KeyReleased(KEY_D))
	{
		_pPlayer->d = RIGHT;		
		_pPlayer->velocityX = _pPlayer->speed;
	}
	else if (CP_Input_KeyDown(KEY_A) || CP_Input_KeyReleased(KEY_A))
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
	p->body.h = p->height - 4;
}