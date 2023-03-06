//========================================================================================
//
// 数字のテクスチャを呼び出す処理[NumberUI.cpp]
// Author: 坂本　翔唯
//
//========================================================================================

#ifndef _NUMBERUI_H_
#define _NUMBERUI_H_

#include "main.h"

//数字UIの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nNumberUI;		//数字
	float Width;		//幅
	float Height;		//高さ
	int nType;			//種類
	bool bUse;			//使用しているかどうか
}NumberUI;

//プロトタイプ宣言
void InitNumberUI(void);
void UninitNumberUI(void);
void UpdateNumberUI(void);
void DrawNumberUI(void);
void SetNumberUI(D3DXVECTOR3 pos, float SizeX, float SizeY, int NumberUI,int nType);
#endif