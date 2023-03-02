//============================
//
//フィールド処理(field.h)
//Author:早川 友貴
//
//============================

#ifndef _OBJECTPOLY_H_   //このマクロ定義がされていなかったら
#define _OBJECTPOLY_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ変数
#define MAX_OBJECTPOLY (128)  //床の最大数

//床の構造体
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 rot; //向き
	D3DXMATRIX mtxWorld; //ワールドマトリックス
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bUse;		//使用しているかどうか
}ObjectPoly;

//プロトタイプ宣言
void InitObjectPoly(void);
void UninitObjectPoly(void);
void UpdateObjectPoly(void);
void UpdateEditObjectPoly(void);
void DrawObjectPoly(void);
void DrawEditObjectPoly(void);
void SetObjectPoly(D3DXVECTOR3 pos, float Wight, float Height);
void EditCollisionObjectPoly(D3DXVECTOR3 pos, float Size);
D3DXVECTOR3 CollisionOuterProductObjectPoly(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool CollisionObjectPoly(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
ObjectPoly * GetObjectPoly(void);

#endif

