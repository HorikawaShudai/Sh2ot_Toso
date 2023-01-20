//============================
//
//フィールド処理(field.h)
//Author:早川 友貴
//
//============================

#ifndef _FIELD_H_   //このマクロ定義がされていなかったら
#define _FIELD_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);
//D3DXVECTOR3 PosField(void);

#endif

