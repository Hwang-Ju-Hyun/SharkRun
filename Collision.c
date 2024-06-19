#include "Header.h"
#include "Collision.h"

void SetPlayerCollision_Pos(struct Player* _pPlayer, CP_Vector _pos)					{_pPlayer->foot_col.Pos.x = _pos.x;_pPlayer->foot_col.Pos.y = _pos.y;}
const CP_Vector GetPlayerCollisionPos(struct Player* _pPlayer)							{return _pPlayer->foot_col.Pos;}
void SetPlayerCollision_Width_Height(struct Player* _pPlayer, float _w, float _h)		{_pPlayer->foot_col.w = _w;_pPlayer->foot_col.h = _h;}
const float GetPlayerCollisionWidth(struct Player* _pPlayer)							{return _pPlayer->foot_col.w;}
const float GetPlayerCollisionHeight(struct Player* _pPlayer)							{return _pPlayer->foot_col.h;}

void Draw_PlayerCollision(struct Player* p)
{
	CP_Settings_Fill(CP_Color_Create(155, 155, 155, 0));	
	CP_Graphics_DrawRect(p->foot_col.Pos.x, p->foot_col.Pos.y, p->foot_col.w, p->foot_col.h);
}

bool IsCollision(struct Player* _pPlayer, struct Platform* _pPlatform)
{
	if (_pPlayer->foot_col.Pos.x + _pPlayer->foot_col.w<_pPlatform->Pos.x
		|| _pPlayer->foot_col.Pos.x>_pPlatform->Pos.x + _pPlatform->width)
	{
		return false;
	}
	if (_pPlayer->foot_col.Pos.y + _pPlayer->foot_col.h<_pPlatform->Pos.y
		|| _pPlayer->foot_col.Pos.y>_pPlatform->Pos.y + _pPlatform->height)
	{
		return false;
	}
	return true;
}
