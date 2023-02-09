#ifndef _SCORE_ITEM_H_
#define _SCORE_ITEM_H_

#define MAX_ITEM00 (640)		//オブジェクトの最大数

typedef enum
{
	OBJECT_SCORE_ITEM = 0,
	OBJECT_SCORE_MAX,
}OBJECT_SCORE;

//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void UpdateEditItem(void);
void DrawEditItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer);
void CollisionItemShadow(D3DXVECTOR3 *pPos);
void SetNumItems(int nNumItem, D3DXVECTOR3 pos, float fWidth_x, float fWidth_z);
#endif