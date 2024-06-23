#pragma once
#include "Header.h"

struct Camera
{
	CP_Vector  cameraPos;//실제 카메라가 보고 있는 좌표
	CP_Vector  prevLookAt; //카메라가 이전에 봤던 좌표
	CP_Vector  curLookAt; //현재 카메라가 보고 있는 좌표
	CP_Vector  offset;
	float speed;
	float time;
	float accTime;
	struct Player* player;		
};

void Camera_Init(struct Camera* _pCamera);
void CameraUpdate(struct Camera* _pCamera, struct Player* _pPlayer);
CP_Vector GetRenderPlatPos(struct Platform* _pPlatform, struct Camera* _pCamera);
CP_Vector GetRenderPlayerPos(struct Player* _pPlayer, struct Camera* _pCamera);
CP_Vector GetRenderPlayerColPos(struct Player* _pPlayer, struct Camera* _pCamera);
CP_Vector GetRenderSharkColPos(struct Shark* _pShark, struct Camera* _pCamera);
CP_Vector GetRenderSharkPos(struct Shark* _pShark, struct Camera* _pCamera);
CP_Vector GetRenderItemPos(struct Item* _pShark, struct Camera* _pCamera);