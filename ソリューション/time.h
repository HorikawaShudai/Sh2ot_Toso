//========================================================================================
//
// タイム処理[time.h]
// Author: 坂本　翔唯
//
//========================================================================================
#ifndef _TIME_H_
#define _TIME_H_

//プロトタイプ宣言
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetRankTime(void);
void SetFalseCount(bool Count);
bool GetTimeCount(void);
int *GetTime(void);
#endif