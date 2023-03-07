#ifndef _RESULTUI_H_
#define _RESULTUI_H_

#include "main.h"

//プレイヤーの状態
typedef enum
{
	RESULTUI_ONLY = 0,		//1人生存(一人プレイを除く)
	RESULTUI_TWO,			//二人以上全員未満生存
	RESULTUI_PERFECT,		//全員生存の場合
	RESULTUI_MAX
}RESULTUI;

//プロトタイプ宣言
void InitResultUI(void);
void UninitResultUI(void);
void UpdateResultUI(void);
void DrawResultUI(void);
void SetResultUI(RESULTUI SetClear);
void SetbResultUi(bool bReseultUi);
bool GetbResultUi(void);
#endif
