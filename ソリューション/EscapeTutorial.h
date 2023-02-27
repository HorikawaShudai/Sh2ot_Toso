#ifndef _ESCAPETUTORIAL_H_
#define _ESCAPETUTORIAL_H_

#include "tutorial.h"

//プロトタイプ宣言
void InitEscapeTutorial();
void UninitEscapeTutorial();
void UpdateEscapeTutorial();
void DrawEscapeTutorial();
TUTORIAL_STATE GetEscapeTutorial();
void SetEscapeTutorial(TUTORIAL_STATE nSet);
void DoEscapeTutorial(TUTORIAL_MODE nMode);
TUTORIAL_MODE GetDoEscapeTutorial(void);
void MoveTCheck(int nCnt, bool check);
void CamMoveTCheck(int nCnt, bool camcheck);

#endif