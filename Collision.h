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

//Player Collision ����
void SetPlayerCollision_Pos(struct Player* _pPlayer, CP_Vector _pos);
const CP_Vector GetPlayerCollisionPos(struct Player* _pPlayer);
void SetPlayerCollision_Width_Height(struct Player* _pPlayer, float _w, float _h);
const float GetPlayerCollisionWidth(struct Player* _pPlayer);
const float GetPlayerCollisionHeight(struct Player* _pPlayer);

//Player�� Platform���� �浹üũ
bool IsCollision(struct Player* _pPlayer, struct Platform* _pPlatform);


//Player�� Shark���� �浹 üũ
//bool IsCollision(struct Player* _pPlayer, struct Shark* _pPlatform);
bool sharkCollision(struct Player* p, struct Shark* s);