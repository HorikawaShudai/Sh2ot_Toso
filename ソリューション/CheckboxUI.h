#ifndef _CHECKBOXUI_H_
#define _CHECKBOXUI_H_

#include "main.h"

//プロトタイプ宣言
void InitCheckboxUI(void);
void UninitCheckboxUI(void);
void UpdateCheckboxUI(void);
void DrawCheckboxUI(void);
void SetCheckUI(int nPlayer, bool SetCheck);
void MovePosCheckUI(int nPlayer, bool SetCheck);
#endif