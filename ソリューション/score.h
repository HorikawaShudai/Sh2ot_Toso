//===============================
//
//スコア処理(score.h)
//Author:早川 友貴
//
//===============================
#ifndef _SCORE_H_   //このマクロ定義がされていなかったら
#define _SCORE_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nType);
int GetScore(void);
void SetPosScore(D3DXVECTOR3 pos,float nWINDTH,float nHeight);

#endif
