#include "item.h"
#include "Header.h"
void InitItem(struct Item* _pItem, struct Platform* _pPlatform)
{
    if (_pItem == NULL || _pPlatform == NULL) return;

    _pItem = malloc(sizeof(struct Item));

    _pItem->w = 30;  // 아이템의 너비
    _pItem->h = 30;  // 아이템의 높이

    _pItem->IsAlive = true;

    // 아이템의 위치를 플랫폼 위에서 무작위로 설정
    _pItem->Pos.x = _pPlatform->Pos.x + CP_Random_RangeFloat(0, _pPlatform->width - 30);
    _pItem->Pos.y = _pPlatform->Pos.y - 30; // 플랫폼 바로 위에 위치

   
}
void DrawItem(struct Item* _pItem, struct Camera* _cCamera)
{
    if (_pItem == NULL || !_pItem->IsAlive) return;

    // 아이템 그리기 로직
    float posX = ceilf(_pItem->Pos.x - _cCamera->cameraPos.x);
    float posY = ceilf(_pItem->Pos.y - _cCamera->cameraPos.y);

    // 아이템을 나타내는 직사각형 그리기
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255)); // 아이템을 빨간색으로 채우기
    CP_Graphics_DrawRect(posX, posY, _pItem->w, _pItem->h);

}

void ItemUpdate(struct Item* _pItem, struct Player* _pPlayer)
{
    if (_pItem == NULL || !_pItem->IsAlive) 
        return;

    // 플레이어나 상어와의 충돌 체크 (의사 코드)
    if (CheckCollisionItem(_pItem, _pPlayer))
    {
        _pItem->IsAlive = false;
        // 플레이어가 아이템을 먹었을 때 처리
    }
    
}

bool CheckCollisionItem(struct Item* _pItem, struct Player* _pPlayer)
{
    if (_pItem->Pos.x < _pPlayer->Pos.x + _pPlayer->width &&
        _pItem->Pos.x + _pItem->w > _pPlayer->Pos.x &&
        _pItem->Pos.y < _pPlayer->Pos.y + _pPlayer->height &&
        _pItem->Pos.y + _pItem->h > _pPlayer->Pos.y)
    {
        return true;
    }
    return false;
}
