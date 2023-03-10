#ifndef _RANKINGNUMBER_H_
#define _RANKINGNUMBER_H_

#include "main.h"

typedef enum
{
	RANKING_TYPE_ESCAPE = 0,
	RANKING_TYPE_VILLAIN,
	RANKING_TYPE_MAX,
}RANKING_TYPE;

//プロトタイプ宣言
void InitRanKingNumber(void);
void UninitRanKingNumber(void);
void UpdateRanKingNumber(void);
void DrawRanKingNumber(void);
void ResetRanKing(void);
void SaveData(void);
void LoadData(void);
void SetRanking(int nRanKing, int nPlayer);
void StartRanKing(void);
#endif