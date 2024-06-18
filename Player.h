#pragma once
#include "Header.h"
#include "Collision.h"



struct Player
{
	CP_Vector Pos;
	float width;
	float height;
	float velocity;
	CP_Color colors;
	CP_Image res;

	float Gravity;  //중력(낙하)
	float JumHeight;
	
	struct Collision col;
	bool JumpKeyPressed;
};

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