#include "item.h"
#include "Header.h"
void InitItem(struct Item* _pItem, struct Platform* _pPlatform)
{
    if (_pItem == NULL || _pPlatform == NULL) return;

    _pItem = malloc(sizeof(struct Item));

    _pItem->w = 30;  // �������� �ʺ�
    _pItem->h = 30;  // �������� ����

    _pItem->IsAlive = true;

    // �������� ��ġ�� �÷��� ������ �������� ����
    _pItem->Pos.x = _pPlatform->Pos.x + CP_Random_RangeFloat(0, _pPlatform->width - 30);
    _pItem->Pos.y = _pPlatform->Pos.y - 30; // �÷��� �ٷ� ���� ��ġ

   
}
void DrawItem(struct Item* _pItem, struct Camera* _cCamera)
{
    if (_pItem == NULL || !_pItem->IsAlive) return;

    // ������ �׸��� ����
    float posX = ceilf(_pItem->Pos.x - _cCamera->cameraPos.x);
    float posY = ceilf(_pItem->Pos.y - _cCamera->cameraPos.y);

    // �������� ��Ÿ���� ���簢�� �׸���
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255)); // �������� ���������� ä���
    CP_Graphics_DrawRect(posX, posY, _pItem->w, _pItem->h);

}

void ItemUpdate(struct Item* _pItem, struct Player* _pPlayer)
{
    if (_pItem == NULL || !_pItem->IsAlive) 
        return;

    // �÷��̾ ������ �浹 üũ (�ǻ� �ڵ�)
    if (CheckCollisionItem(_pItem, _pPlayer))
    {
        _pItem->IsAlive = false;
        // �÷��̾ �������� �Ծ��� �� ó��
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
