#include "Camera.h"

void Camera_Init(struct Camera* _pCamera)
{
	//현재 카메라 좌표를 초기화
	_pCamera->cameraPos.x = WINDOW_WIDTH /2.f;
	_pCamera->cameraPos.y = WINDOW_HEIGHT/2.f;
	_pCamera->curLookAt.x = _pCamera->cameraPos.x;
	_pCamera->curLookAt.y = _pCamera->cameraPos.y;
	_pCamera->time = 1.f;
	_pCamera->accTime = 0.f;
	_pCamera->cameraChange = false;
}

void CallDiff(struct Camera* _pCamera)
{
	float deltaTime = CP_System_GetDt();
	_pCamera->time += deltaTime;
	if (_pCamera->accTime <= _pCamera->time)
	{
		_pCamera->curLookAt = _pCamera->cameraPos;
	}
	else
	{
		CP_Vector LookDir;
		LookDir.x = _pCamera->cameraPos.x - _pCamera->prevLookAt.x;
		LookDir.y = _pCamera->cameraPos.y - _pCamera->prevLookAt.y;
		if (LookDir.y != 0)
		{
			CP_Vector Nom = CP_Vector_Normalize(LookDir);
			_pCamera->curLookAt.x = _pCamera->prevLookAt.x + Nom.x * _pCamera->speed * deltaTime;
			_pCamera->curLookAt.y = _pCamera->prevLookAt.y + Nom.y * _pCamera->speed * deltaTime;
		}
	}
	CP_Vector center;
	center.x = WINDOW_WIDTH / 2.f;
	center.y = WINDOW_HEIGHT / 2.f;

	_pCamera->offset.x = _pCamera->curLookAt.x - center.x;
	_pCamera->offset.y = _pCamera->curLookAt.y - center.y;

	_pCamera->prevLookAt = _pCamera->curLookAt;
}


void CameraUpdate(struct Camera* _pCamera, struct Player* _pPlayer)
{	
	float deltaTime = CP_System_GetDt();
	if (_pCamera->cameraChange == false)
	{
		//플레이어가 오른쪽으로 어느정도 이동한다면 
		if (CP_Input_KeyDown(KEY_UP))
		{
			_pCamera->cameraPos.y -= 600.f * deltaTime;
		}
		if (CP_Input_KeyDown(KEY_DOWN))
		{
			_pCamera->cameraPos.y += 600.f * deltaTime;
		}
		if (CP_Input_KeyDown(KEY_RIGHT))
		{
			_pCamera->cameraPos.x += 600.f * deltaTime;
		}
		if (CP_Input_KeyDown(KEY_LEFT))
		{
			_pCamera->cameraPos.x -= 600.f * deltaTime;
		}
	}
	else if (_pCamera->cameraChange == true)
	{
		//플레이어가 오른쪽으로 어느정도 이동한다면 
		if (CP_Input_KeyDown(KEY_UP))
		{
			_pCamera->cameraPos.y += 600.f * deltaTime;
		}
		if (CP_Input_KeyDown(KEY_DOWN))
		{
			_pCamera->cameraPos.y -= 600.f * deltaTime;
		}
		if (CP_Input_KeyDown(KEY_RIGHT))
		{
			_pCamera->cameraPos.x -= 600.f * deltaTime;
		}
		if (CP_Input_KeyDown(KEY_LEFT))
		{
			_pCamera->cameraPos.x += 600.f * deltaTime;
		}
	}
	
	/*_pCamera->cameraPos.x = _pPlayer->Pos.x;
	_pCamera->cameraPos.y = _pPlayer->Pos.y;*/

	CallDiff(_pCamera);
}

CP_Vector GetRenderPlatPos(struct Platform* _pPlatform, struct Camera* _pCamera)
{
	CP_Vector result;
	result.x=  _pPlatform->Pos.x   -   _pCamera->offset.x;
	result.y= _pPlatform-> Pos.y   -    _pCamera->offset.y;	
	return result;
}

CP_Vector GetRenderPlayerPos(struct Player* _pPlayer, struct Camera* _pCamera)
{
	CP_Vector result;
	result.x = _pPlayer->Pos.x - _pCamera->offset.x;
	result.y = _pPlayer->Pos.y - _pCamera->offset.y;	
	return result;
}

CP_Vector GetRenderPlayerColPos(struct Player* _pPlayer,struct Camera* _pCamera)
{		
	CP_Vector result;
	//GetColliderWolrdPos();

	result.x =  _pPlayer->body.Pos.x - _pCamera->offset.x;
	result.y = _pPlayer->body.Pos.y - _pCamera->offset.y;
	return result;
}

CP_Vector GetRenderSharkColPos(struct Shark* _pShark,struct Camera* _pCamera)
{
	CP_Vector result;
	result.x = _pShark->col.Pos.x - _pCamera->offset.x;
	result.y = _pShark->col.Pos.y - _pCamera->offset.y;	
	return result;
}

CP_Vector GetRenderSharkPos(struct Shark* _pShark, struct Camera* _pCamera)
{
	CP_Vector result;
	result.x = _pShark->Pos.x - _pCamera->offset.x;
	result.y = _pShark->Pos.y - _pCamera->offset.y;
	return result;
}

CP_Vector GetRenderItemPos(struct Item* _pItem,struct Camera* _pCamera)
{
	CP_Vector result;
	result.x = _pItem->Pos.x - _pCamera->offset.x;
	result.y = _pItem->Pos.y - _pCamera->offset.y;
	return result;
}

