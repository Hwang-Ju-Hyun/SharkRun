#pragma once
#include "Game.h"

enum direction
{
	LEFT = 0,
	RIGHT = 1,
};

struct Player
{
	CP_Image res[2];

	CP_Vector Pos;
	float width;
	float height;

	float velocity;

	int alpha;
	
	enum direction d;
	CP_Color colors;

	float Gravity;  //중력(낙하)
	float JumHeight;

	bool JumpKeyPressed;
};

void PlayerInit(struct Player* p);
void PlayerDraw(struct Player* p);
void PlayerMove(struct Player* p, float dt);

void Draw_Player(struct Player* _pPlayer);				//Player를 그린다
void SetPos(struct Player* _pPlayer,CP_Vector _pVec);	//Player Position을 설정
void SetWidth(struct Player* _pPlayer, float _w);		//Player width를 설정
void SetHeight(struct Player* _pPlayer, float _h);		//Player Height를 설정
const CP_Vector GetPos(struct Player* _pPlayer);		//Player Position을 가져옴
const float GetHeight(struct Player* _pPlayer);			//Player width를 가져옴
const float GetWidth(struct Player* _pPlayer);			//Player Height를 가져옴
void Player_Load(char* fileName, struct Player* p);		//Player초기정보를 file에서 로드해온다

void SetJump(struct Player* _pPlayer,float _vel,float _gra,float _jumpHeight);
void Jump(struct Player* _pPlayer);
void JumpKeyPressed(struct Player* _pPlayer);