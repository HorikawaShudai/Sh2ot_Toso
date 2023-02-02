#ifndef _THUNDER_H_
#define _THUNDER_H_

#include "main.h"

//雷の状態の構造体宣言
typedef enum
{
	THUNDER_NONE = 0,		//何もしていない状態
	THUNDER_MOVE,			//フェード状態
}THUNDER_TYPE;

//雷の構造体宣言
typedef struct
{
	bool bUse;				//表示状態
	D3DXVECTOR3 pos;		//表示位置
	D3DXCOLOR col;			//雷の色
	THUNDER_TYPE nType;		//雷の状態
}THUNDER;

//プロトタイプ宣言
void InitThunder(void);
void UninitThunder(void);
void UpdateThunder(void);
void DrawThunder(void);
void SetThunder(void);
THUNDER GetThunder(void);
#endif
