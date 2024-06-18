#include "Player.h"

void PlayerInit(struct Player* p)
{
	p->res[0] = CP_Image_Load("Assets\\dog_left.png");
	p->res[1] = CP_Image_Load("Assets\\dog_right.png");

	p->Pos.x = 140.0f;
	p->Pos.y = 600.0f - 30.0f;

	p->width = (float)CP_Image_GetWidth(p->res[0]);
	p->height = (float)CP_Image_GetHeight(p->res[0]);

	p->velocity = 80.0f;
	p->alpha = 255;

	p->d = RIGHT;
}

void PlayerDraw(struct Player* p)
{
	CP_Image tmp = p->res[1];
	if (p->d == LEFT)
		tmp = p->res[0];

	//else if (p->d == RIGHT) tmp = p->res[1];

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

void SetPos(struct Player* _pPlayer, CP_Vector _pVec){_pPlayer->Pos = _pVec;}
void SetWidth(struct Player* _pPlayer, float _w){_pPlayer->width = _w;}
void SetHeight(struct Player* _pPlayer, float _h){_pPlayer->height = _h;}

const CP_Vector GetPos(struct Player* _pPlayer){return _pPlayer->Pos;}
const float GetHeight(struct Player* _pPlayer){return _pPlayer->height;}
const float GetWidth(struct Player* _pPlayer) { return _pPlayer->width; }

void LoadVelocityFromFile(float* _vel, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf(str, "%f", _vel);
}

void Player_Load(char* fileName, struct Player* p)
{

	FILE* _inFile = fopen(fileName, "rt");

	if (_inFile == NULL)
	{
		printf("Error! Platform File is not exists : (function)Map_Load\n");
		return;
	}

	//char str[BUFFERSIZE] = { '\0' };

	//Player_LOAD			
	//1. 플레이어 Position
	LoadPosFromFile(&p->Pos, _inFile);

	//3. 플레이어 사이즈
	LoadSizeFromFile(&p->width, &p->height, _inFile);

	//4. 플레이어 속도
	LoadVelocityFromFile(&p->velocity, _inFile);

	//5. 플레이어 색깔
	LoadColorFromFile(&p->colors, _inFile);
	
}

void JumpKeyPressed(struct Player* _pPlayer)
{
	_pPlayer->JumpKeyPressed = true;
}

void SetJump(struct Player* _pPlayer, float _vel, float _gra, float _jumpHeight)
{
	_pPlayer->velocity = _vel;
	_pPlayer->Gravity = _gra;
	_pPlayer->JumHeight = _jumpHeight;
}

void Jump(struct Player* _pPlayer) //
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


void Draw_Player(struct Player* _pPlayer)
{
	CP_Settings_Fill(_pPlayer->colors);
	CP_Graphics_DrawRect(_pPlayer->Pos.x,_pPlayer->Pos.y,_pPlayer->width,_pPlayer->height);
}