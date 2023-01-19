//===============================
//
//ライフ処理(life.h)
//
//===============================
#ifndef _LIFE_H_   //このマクロ定義がされていなかったら
#define _LIFE_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);

#endif
