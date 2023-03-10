#ifndef _POLYGONBG_H_
#define _POLYGONBG_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;		//色
	float fWidth;		//幅
	float fHeight;		//高さ
	int nLife;			//寿命
	int nType;			//種類
	float KuroPolyA;	//黒いポリゴンのα値
	bool bUse;			//使用しているかどうか
}PolygonBG;

//プロトタイプ宣言
void InitPolygonBG(void);
void UninitPolygonBG(void);
void UpdatePolygonBG(void);
void DrawPolygonBG(void);
void SetPolygonBG(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR Col, int nLife,int Type);
#endif