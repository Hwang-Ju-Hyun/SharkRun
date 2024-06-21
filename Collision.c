#include "Header.h"
#include "Collision.h"

void SetPlayerCollision_Pos(struct Player* _pPlayer, CP_Vector _pos)					{_pPlayer->body.Pos.x = _pos.x;_pPlayer->body.Pos.y = _pos.y;}
const CP_Vector GetPlayerCollisionPos(struct Player* _pPlayer)							{return _pPlayer->body.Pos;}
void SetPlayerCollision_Width_Height(struct Player* _pPlayer, float _w, float _h)		{_pPlayer->body.w = _w;_pPlayer->body.h = _h;}
const float GetPlayerCollisionWidth(struct Player* _pPlayer)							{return _pPlayer->body.w;}
const float GetPlayerCollisionHeight(struct Player* _pPlayer)							{return _pPlayer->body.h;}

void Draw_PlayerCollision(struct Player* p, struct Camera* c)
{
	CP_Settings_Fill(CP_Color_Create(155, 155, 155, 0));
	CP_Vector Render;
	Render.x = GetRenderPlayerColPos(p, c).x;
	Render.y = GetRenderPlayerColPos(p, c).y;
	CP_Settings_StrokeWeight(0.5f);
	CP_Graphics_DrawRect(Render.x, Render.y, p->body.w, p->body.h);
}

bool IsCollision(struct Player* _pPlayer, struct Platform* _pPlatform)
{
	if (_pPlayer->body.Pos.x + _pPlayer->body.w<_pPlatform->Pos.x
		|| _pPlayer->body.Pos.x>_pPlatform->Pos.x + _pPlatform->width)
	{
		return false;
	}
	if (_pPlayer->body.Pos.y + _pPlayer->body.h<_pPlatform->Pos.y
		|| _pPlayer->body.Pos.y>_pPlatform->Pos.y + _pPlatform->height)
	{
		return false;
	}
	return true;
}

bool IsCollisionXcord(struct Player* _pPlayer,struct Platform* _pPlatform)
{
	if (_pPlayer->body.Pos.x + _pPlayer->body.w<_pPlatform->Pos.x
		|| _pPlayer->body.Pos.x>_pPlatform->Pos.x + _pPlatform->width)
	{
		return false;
	}
	return true;
}



bool sharkCollision(struct Player* p, struct Shark* s)
{
	float sLeftX = s->col.Pos.x,
		 sRightX = s->col.Pos.x + s->col.w,
		   sTopY = s->col.Pos.y,
		   sBotY = s->col.Pos.y + s->col.h;

	float pLeftX = p->body.Pos.x,
		 pRightX = p->body.Pos.x + p->body.w,
		   pTopY = p->body.Pos.y,
		   pBotY = p->body.Pos.y + p->body.h;

	if (sRightX < pLeftX || sLeftX > pRightX || sBotY < pTopY || sTopY > pBotY)
		return false;
	return true;
}
