#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//ゲームの状態
typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_READY,
	GAMESTATE_NORMAL,
	GAMESTATE_CLEAR_END,
	GAMESTATE_GAMEOVER_END,
	GAMESTATE_MAX,
}GAMESTATE;


//プロトタイプ宣言
void InitGame();
void UninitGame();
void UpdateGame();
void DrawGame();
void SetGameState(GAMESTATE state, int nCounter);
GAMESTATE GetGameState();
void SetClear(int ClearNumber);
int GetClear(void);
void ResetClear(void);

#endif