//============================
//
//プレイヤー処理(player.h)
//Author:早川 友貴
//
//============================

#ifndef _PLAYER_H_   //このマクロ定義がされていなかったら
#define _PLAYER_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
D3DXVECTOR3 PosPlayer(void);
D3DXVECTOR3 RotPlayer(void);
void MovePlayer(void);
void AnglePlayer(void);

#endif

