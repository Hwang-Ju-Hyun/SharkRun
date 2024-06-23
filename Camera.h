#pragma once
#include "Header.h"

struct Camera
{
	CP_Vector  cameraPos;//���� ī�޶� ���� �ִ� ��ǥ
	CP_Vector  prevLookAt; //ī�޶� ������ �ô� ��ǥ
	CP_Vector  curLookAt; //���� ī�޶� ���� �ִ� ��ǥ
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