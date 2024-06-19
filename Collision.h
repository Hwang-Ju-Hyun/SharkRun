#pragma once
#include "Header.h"

struct Player;
struct Platform;
struct Shark;

struct Collision
{
	CP_Vector Pos;
	float w, h;
};

//Player Collision 정보
void SetPlayerCollision_Pos(struct Player* _pPlayer, CP_Vector _pos);
const CP_Vector GetPlayerCollisionPos(struct Player* _pPlayer);
void SetPlayerCollision_Width_Height(struct Player* _pPlayer, float _w, float _h);
const float GetPlayerCollisionWidth(struct Player* _pPlayer);
const float GetPlayerCollisionHeight(struct Player* _pPlayer);

//Player와 Platform간의 충돌체크
bool IsCollision(struct Player* _pPlayer, struct Platform* _pPlatform);


//Player와 Shark간의 충돌 체크
//bool IsCollision(struct Player* _pPlayer, struct Shark* _pPlatform);
bool sharkCollision(struct Player* p, struct Shark* s);