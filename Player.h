#pragma once

#include "Game.h"
#include "Header.h"
#include "Collision.h"

struct Camera;
struct Platforms;

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
	
	float velocityX;
	float velocityY;
	float speed;
	float Acceleration;
	float JumHeight;	
	int alpha;
	
	enum direction d;
	struct Collision body;

	enum GROUND_OR_AIR IsGrounded;
	bool JumpKeyPressed;
};

//void Player_Load_fromFile(char* fileName, struct Player* p);		//Player초기정보를 file에서 로드해온다
//void LoadVelocityFromFile(float* _vel, FILE* _inFile);

void PlayerInit(struct Player* p);
void SetPlayer(struct Player* p, CP_Vector pos, float w, float h, float grav, float v, float jump, int a);
void PlayerDraw(struct Player* p,struct Camera* c);

void Draw_Player(struct Player* _pPlayer, struct Camera* c);				//Player를 그린다
void SetPos(struct Player* _pPlayer,CP_Vector _pVec);	//Player Position을 설정
void SetWidth(struct Player* _pPlayer);		//Player width를 설정
void SetHeight(struct Player* _pPlayer);		//Player Height를 설정
const CP_Vector GetPos(struct Player* _pPlayer);		//Player Position을 가져옴
const float GetHeight(struct Player* _pPlayer);			//Player width를 가져옴
const float GetWidth(struct Player* _pPlayer);			//Player Height를 가져옴

void Move_Player(struct Player* _pPlayer,struct Platforms* _pPlatforms, float dt);
//void SetJump(struct Player* _pPlayer,float _vel,float _gra,float _jumpHeight);

void Jump(struct Player* _pPlayer, float jumpHeight);

//void PlayerGravity(struct Player* _pPlayer, int _platformNum, bool IsCol);
