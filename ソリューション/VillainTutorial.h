#ifndef _VILLAINTUTORIAL_H_
#define _VILLAINTUTORIAL_H_

#include "tutorial.h"

//プロトタイプ宣言
void InitVillainTutorial();
void UninitVillainTutorial();
void UpdateVillainTutorial();
void DrawVillainTutorial();
TUTORIAL_STATE GetVillainTutorial();
void SetVillainTutorial(TUTORIAL_STATE nSet);
void DoVillainTutorial(TUTORIAL_MODE nMode);
TUTORIAL_MODE GetDoVillainTutorial(void);
void MoveVCheck(int nCnt, bool check);
void CamMoveVCheck(int nCnt, bool camcheck);

#endif