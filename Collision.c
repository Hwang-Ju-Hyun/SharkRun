#include "Header.h"
#include "Collision.h"

void SetPlayerCollision_Pos(struct Player* _pPlayer, CP_Vector _pos)					{_pPlayer->col.Pos.x = _pos.x;_pPlayer->col.Pos.y = _pos.y;}
const CP_Vector GetPlayerCollisionPos(struct Player* _pPlayer)							{return _pPlayer->col.Pos;}
void SetPlayerCollision_Width_Height(struct Player* _pPlayer, float _w, float _h)		{_pPlayer->col.w = _w;_pPlayer->col.h = _h;}
const float GetPlayerCollisionWidth(struct Player* _pPlayer)							{return _pPlayer->col.w;}
const float GetPlayerCollisionHeight(struct Player* _pPlayer)							{return _pPlayer->col.h;}


bool IsCollision(struct Player* _pPlayer,struct Platform* _pPlatform)
{	
	//PosÀ» ¼¾ÅÍ ±âÁØÀ¸·Î ºÁ²Û´Ù
	float LeftPosX = _pPlayer->col.Pos.x+_pPlayer->col.w/2.f;
	float RightPosX= _pPlatform->Pos.x + _pPlatform->width / 2.f;
	float LeftPosY= _pPlayer->col.Pos.y + _pPlayer->col.h / 2.f;
	float RightPosY = _pPlatform->Pos.y + _pPlatform->height / 2.f;

	float LeftScaleX = _pPlayer->col.w;
	float RightScaleX = _pPlatform->width;

	float LeftScaleY = _pPlayer->col.h;
	float RighttScaleY = _pPlatform->height;

	if (fabsf(RightPosX - LeftPosX) < (LeftScaleX + RightScaleX) / 2.f
		&& fabsf(RightPosY - LeftPosY) < (LeftScaleY + RighttScaleY) / 2.f)
	{
		return true;
	}
	return false;
}

