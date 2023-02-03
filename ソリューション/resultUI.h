#ifndef _RESULTUI_H_
#define _RESULTUI_H_

#include "main.h"

//プレイヤーの状態
typedef enum
{
	RESULTUI_NORMAL = 0,		//通常
	RESULTUI_PERFECT,		//パーフェクト
	RESULTUI_ALLPERFECT,		//オールパーフェクト
	RESULTUI_MAX
}RESULTUI;

//プロトタイプ宣言
void InitResultUI(void);
void UninitResultUI(void);
void UpdateResultUI(void);
void DrawResultUI(void);
void SetResultUI(RESULTUI SetClear, bool Clear);
#endif
