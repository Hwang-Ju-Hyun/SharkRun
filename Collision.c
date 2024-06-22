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

//CP_Vector GetColliderWorldPos(CP_Vector object_position, CP_Vector collider_position)
//{
//	CP_Vector result;
//	result.x = object_position.x + collider_position.x;
//	result.y = object_position.y + collider_position.y;
//	return result;
//}

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

	float pLeftX = p->Pos.x,
		 pRightX = p->Pos.x + p->width,
		   pTopY = p->Pos.y,
		   pBotY = p->Pos.y + p->height;

	if (sRightX < pLeftX || sLeftX > pRightX || sBotY < pTopY || sTopY > pBotY)
		return false;
	return true;
}

bool platformCollision(struct Platform* p, float* x, float* y, float w, float h)
{
	float rightX = *x + w;
	float botY = *y + h;
	
	float pRightX = p->Pos.x + p->width;
	float pBotY = p->Pos.y + p->height;

	bool lx = true, rx = true, ty = true, by = true;

	if (pRightX < *x || rightX < p->Pos.x || pBotY < *y || p->Pos.y > botY)
		return false;

	if (pRightX >= rightX) rx = false;
	if (*x >= p->Pos.x) lx = false;
	if (pBotY >= botY) ty = false;
	if (*y >= p->Pos.y) by = false;


	if (!lx) *x = *x + (pRightX - *x);
	if (!rx) *x = *x - (rightX - p->Pos.x);
	if (!ty) *y = *y - (botY - p->Pos.y);
	if (!by) *y = *y + (pBotY - *y);
	
	return true;
}