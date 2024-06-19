#include "Header.h"
#include "Player.h"
#include "Collision.h"

/*
void LoadVelocityFromFile(float* _vel, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%f", _vel);
}
void Player_Load_fromFile(char* fileName, struct Player* p)
{

	FILE* _inFile = fopen(fileName, "rt");

	if (_inFile == NULL)
	{
		printf("Error! Platform File is not exists : (function)Map_Load\n");
		return;
	}

	//Player_LOAD			
	//1. 플레이어 Position
	LoadPosFromFile(&p->Pos, _inFile);

	//3. 플레이어 사이즈
	LoadSizeFromFile(&p->width, &p->height, _inFile);

	//4. 플레이어 속도
	LoadVelocityFromFile(&p->velocity, _inFile);

	//5. 플레이어 색깔
	LoadColorFromFile(&p->colors, _inFile);

	fclose(_inFile);
}
*/

void PlayerInit(struct Player* p)
{
	p->res[0] = CP_Image_Load("Assets\\dog_left.png");
	p->res[1] = CP_Image_Load("Assets\\dog_right.png");

	p->Pos.x = 140.0f;
	p->Pos.y = 600.0f - 30.0f;

	p->width = (float)CP_Image_GetWidth(p->res[0]);
	p->height = (float)CP_Image_GetHeight(p->res[0]);

	p->velocity = 30.0f;
	p->Gravity = 70.0f;
	p->JumHeight = 0.0f;

	p->alpha = 255;

	p->d = RIGHT;
	p->JumpKeyPressed = false;
}

void SetPlayer(struct Player* p, CP_Vector pos, float w, float h, float grav, float v, float jump, int a)
{
	p->Pos = pos;
	p->width = w;
	p->height = h;
	p->Gravity = grav;
	p->velocity = v;
	p->JumHeight = jump;
	p->alpha = a;
}

void PlayerDraw(struct Player* p)
{
	CP_Image tmp = p->res[1];
	if (p->d == LEFT)
		tmp = p->res[0];

	CP_Image_Draw(tmp, p->Pos.x, p->Pos.y, p->width, p->height, p->alpha);
}

void PlayerMove(struct Player* p, float dt)
{
	if (CP_Input_KeyDown(KEY_RIGHT))
	{
		p->d = RIGHT;
		p->Pos.x += p->velocity * dt;
	}

	if (CP_Input_KeyDown(KEY_LEFT))
	{
		p->d = LEFT;
		p->Pos.x -= p->velocity * dt;
	}

	if (CP_Input_KeyDown(KEY_UP))
	{
		p->Pos.y -= p->velocity * dt;
	}

	if (CP_Input_KeyDown(KEY_DOWN))
	{
		p->Pos.y += p->velocity * dt;
	}

	PlayerDraw(p);
}

void Draw_Player(struct Player* _pPlayer)
{
	
	CP_Image tmp = _pPlayer->res[1];
	if (_pPlayer->d == LEFT)
		tmp = _pPlayer->res[0];
	
	CP_Image_Draw(tmp, _pPlayer->Pos.x, _pPlayer->Pos.y, _pPlayer->width, _pPlayer->height, _pPlayer->alpha);
}

void SetPos(struct Player* _pPlayer, CP_Vector _pVec)
{
	_pPlayer->Pos = _pVec;
}

void SetWidth(struct Player* _pPlayer)
{
	_pPlayer->width = (float)CP_Image_GetWidth(_pPlayer->res[0]);
}

void SetHeight(struct Player* _pPlayer)
{
	_pPlayer->height = (float)CP_Image_GetHeight(_pPlayer->res[0]);
}

const CP_Vector GetPos(struct Player* _pPlayer)	
{
	return _pPlayer->Pos;
}
const float GetHeight(struct Player* _pPlayer)
{
	return _pPlayer->height;
}
const float GetWidth(struct Player* _pPlayer)
{
	return _pPlayer->width;
}

void Move_Player(struct Player* _pPlayer, float dt)
{
	if (CP_Input_KeyDown(KEY_SPACE))//점프
	{
		_pPlayer->JumpKeyPressed = true;
	}

	if (CP_Input_KeyDown(KEY_D))
	{
		_pPlayer->d = RIGHT;

		float right = 150.f * dt;
		_pPlayer->Pos.x = _pPlayer->Pos.x + right;
		_pPlayer->Pos.y = _pPlayer->Pos.y;

		//SetPos(&player, c_rt);
	}

	if (CP_Input_KeyDown(KEY_A))
	{
		_pPlayer->d = LEFT;
		float left = -150.f * dt;
		_pPlayer->Pos.x = _pPlayer->Pos.x + left;
		_pPlayer->Pos.y = _pPlayer->Pos.y;
		//SetPos(&player, c_lt);
	}

	if (_pPlayer->JumpKeyPressed == true)
	{
		Jump(_pPlayer);
		_pPlayer->Pos.x = _pPlayer->Pos.x;
		_pPlayer->Pos.y += _pPlayer->JumHeight;
		//SetPos(_pPlayer, pos);
	}
	Draw_Player(_pPlayer);
}

void SetJump(struct Player* _pPlayer, float _vel, float _gra, float _jumpHeight)
{
	_pPlayer->velocity = _vel;
	_pPlayer->Gravity = _gra;
	_pPlayer->JumHeight = _jumpHeight;
}

void Jump(struct Player* _pPlayer)
{					
	if (_pPlayer->velocity <= -60.f)
	{
		_pPlayer->Pos.y -= (_pPlayer->velocity * 0.04f);
		_pPlayer->velocity = 30.f;
		_pPlayer->JumpKeyPressed = false;
		_pPlayer->JumHeight = 0.f;
		return;
	}
	_pPlayer->JumHeight = _pPlayer->JumHeight - (_pPlayer->velocity * 0.04f);
	_pPlayer->velocity =  _pPlayer->velocity  - (_pPlayer->Gravity  * 0.04f);	
}
