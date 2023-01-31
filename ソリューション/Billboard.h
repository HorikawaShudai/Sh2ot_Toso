#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"


//月の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//現在位置
	bool bUse;			//使用の有無
}MOON;//雨

	  //雨の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//現在位置
	D3DXVECTOR3 move;	//移動量
	bool bUse;			//使用の有無
}RAIN;//雨

	  //プロトタイプ宣言
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
#endif
