#ifndef _POLYGONBG_H_
#define _POLYGONBG_H_

#include "main.h"

typedef struct
{
	D3DXCOLOR col;		//色
	int nLife;			//寿命
	bool bUse;			//使用しているかどうか
}PolygonBG;

//プロトタイプ宣言
void InitPolygonBG(void);
void UninitPolygonBG(void);
void UpdatePolygonBG(void);
void DrawPolygonBG(void);
void SetPolygonBG(D3DXCOLOR Col,int nLife);
#endif