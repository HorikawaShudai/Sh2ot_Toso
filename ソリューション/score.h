//===============================
//
//スコア処理(score.h)
//Author:早川 友貴
//
//===============================
#ifndef _SCORE_H_   //このマクロ定義がされていなかったら
#define _SCORE_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//スコアの構造体
typedef struct
{
	D3DXVECTOR3 posScore;  //スコアの位置
	int nScore;			//スコアの値
	float nWindth;		//幅の値
	float nHeight;		//高さの値
}SCORE;

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore,int nPlayer);
void AddScore(int nType,int nPlayer);
int GetScore(int nPlayer);
void SetPosScore(D3DXVECTOR3 pos,float nWINDTH,float nHeight,int nPlayer);

#endif
