#pragma once
#include "Header.h"

struct Player;
struct Shark;
struct Platform;
struct Platforms;
struct Camera;

struct Item
{
    CP_Vector Pos;
    float w, h;
    bool IsAlive;
};

void InitItem(struct Item* _pItem, struct Platform* _pPlatform);
void DrawItem(struct Item* _pItem, struct Camera* _cCamera);

void ItemUpdate(struct Item* _pItem, struct Player* _pPlayer);
bool CheckCollisionItem(struct Item* _pItem, struct Player* _pPlayer);