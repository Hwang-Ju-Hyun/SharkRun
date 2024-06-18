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

	float Gravity;  //�߷�(����)
	float JumHeight;

	bool JumpKeyPressed;
};

void PlayerInit(struct Player* p);
void PlayerDraw(struct Player* p);
void PlayerMove(struct Player* p, float dt);

void Draw_Player(struct Player* _pPlayer);				//Player�� �׸���
void SetPos(struct Player* _pPlayer,CP_Vector _pVec);	//Player Position�� ����
void SetWidth(struct Player* _pPlayer, float _w);		//Player width�� ����
void SetHeight(struct Player* _pPlayer, float _h);		//Player Height�� ����
const CP_Vector GetPos(struct Player* _pPlayer);		//Player Position�� ������
const float GetHeight(struct Player* _pPlayer);			//Player width�� ������
const float GetWidth(struct Player* _pPlayer);			//Player Height�� ������
void Player_Load(char* fileName, struct Player* p);		//Player�ʱ������� file���� �ε��ؿ´�

void SetJump(struct Player* _pPlayer,float _vel,float _gra,float _jumpHeight);
void Jump(struct Player* _pPlayer);
void JumpKeyPressed(struct Player* _pPlayer);