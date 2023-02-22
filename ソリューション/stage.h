#ifndef _STAGE_H_
#define _STAGE_H_

#define MAX_STAGEOBJECT (4096)		//ステージ配置物の最大数

//プロトタイプ宣言
void SetStage(int nStageNumber);
void LoadStage(int nStageNumber);
int GetSelectStage(void);
#endif