//===============================
//
//探知処理(detect.h)
//
//===============================
#ifndef _Detect_H_   //このマクロ定義がされていなかったら
#define _Detect_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義

//列挙型定義
typedef enum
{
	DETECTTYPE_WALL = 0,
	DETECTTYPE_PLAYER,
	DETECTTYPE_MAX
}DETECTTYPE;

//構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	float fmoveRot;
	int nLife;
	float fDistance;
	bool bUse;
	DETECTTYPE type;
}DETECT;

//プロトタイプ宣言
void InitDetect(void);
void UninitDetect(void);
void UpdateDetect(void);
void SetDetect(D3DXVECTOR3 pos,int nEnemy, float fmoveRot, int nLife ,DETECTTYPE type);

#endif
