#pragma once
#include "Header.h"

struct Player;
struct Platform;
struct Platforms;
struct Shark;
struct Camera;

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
void Draw_PlayerCollision(struct Player* p,struct Camera* c);
//Player와 Platform간의 충돌체크
bool IsCollision(struct Player* _pPlayer, struct Platform* _pPlatform);
bool IsCollisionXcord(struct Player* _pPlayer, struct Platform* _pPlatform);

//Player와 Shark간의 충돌 체크
//bool IsCollision(struct Player* _pPlayer, struct Shark* _pPlatform);
bool sharkCollision(struct Player* p, struct Shark* s);

CP_Vector GetColliderWorldPos(CP_Vector object_position, CP_Vector collider_position);
bool platformCollision(struct Platform* p, float* x, float* y, float w, float h);