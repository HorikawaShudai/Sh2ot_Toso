#ifndef _RANKINGUI_H_
#define _RANKINGUI_H_

#include "main.h"

//プレイヤーの状態
typedef enum
{
	RANKING_NORMAL = 0,		//通常
	RANKING_PERFECT,		//パーフェクト
	RANKING_ALLPERFECT,		//オールパーフェクト
	RANKING_MAX
}RANKING;

//プロトタイプ宣言
void InitRankingUI(void);
void UninitRankingUI(void);
void UpdateRankingUI(void);
void DrawRankingUI(void);
void SetRankingUI(RANKING SetClear, bool Clear);
#endif