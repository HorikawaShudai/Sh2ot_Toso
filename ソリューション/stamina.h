//=========================================================================================
//
// スタミナ処理 [stamina.h]
// Author:
//
//=========================================================================================
#ifndef _STAMINA_H_
#define _STAMINA_H_

#include "main.h"

//スタミナ構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXCOLOR col;				//色
	int nFalseTime;				//スタミナが使われていない時間のカウント
	float fGaugeSize;			//スタミナのサイズ(横幅)
	bool bUse;					//使っているかどうか
} Stamina;

//*********************************************
//プロトタイプ宣言
//*********************************************
void InitStamina(void);
void UninitStamina(void);
void UpdateStamina(void);
void DrawStamina(void);

void SetStamina(D3DXVECTOR3 pos);

#endif
