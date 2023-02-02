#ifndef _THUNDER_H_
#define _THUNDER_H_

#include "main.h"

typedef struct
{
	bool bUse;
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	int nCnt;
}THUNDER;

//プロトタイプ宣言
void InitThunder(void);
void UninitThunder(void);
void UpdateThunder(void);
void DrawThunder(void);
void SetThunder(void);
#endif
