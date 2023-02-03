#ifndef _TUTORIALUI_H_
#define _TUTORIALUI_H_

#include "main.h"

//プレイヤーの状態
typedef enum
{
	TUTORIALUI_NORMAL = 0,		//通常
	TUTORIALUI_PERFECT,		//パーフェクト
	TUTORIALUI_ALLPERFECT,		//オールパーフェクト
	TUTORIALUI_MAX
}TUTORIALUI;

//プロトタイプ宣言
void InitTutorialUI(void);
void UninitTutorialUI(void);
void UpdateTutorialUI(void);
void DrawTutorialUI(void);
void SetTutorialUI(TUTORIALUI SetClear, bool Clear);
#endif

