//========================================================================================
//
// 鍵のUIの処理[KeyUI.h]
// Author: 坂本　翔唯
//
//========================================================================================
#ifndef _KEYUI_H_   //このマクロ定義がされていなかったら
#define _KEYUI_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitKeyUI(void);
void UninitKeyUI(void);
void UpdateKeyUI(void);
void DrawKeyUI(void);
void SetKeyUI(int nPlayer, bool SetKey);
#endif
