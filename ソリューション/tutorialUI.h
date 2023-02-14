#ifndef _TUTORIALUI_H_
#define _TUTORIALUI_H_

#include "main.h"

//プロトタイプ宣言
void InitTutorialUI(void);
void UninitTutorialUI(void);
void UpdateTutorialUI(void);
void DrawTutorialUI(void);
void SetTutorialUI(bool bUse, int nCnt);
#endif