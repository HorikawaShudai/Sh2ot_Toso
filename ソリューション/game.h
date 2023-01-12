#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_READY,
	GAMESTATE_NORMAL,
	GAMESTATE_END,
	GAMESTATE_MAX,
}GAMESTATE;


//�v���g�^�C�v�錾
void InitGame();
void UninitGame();
void UpdateGame();
void DrawGame();
void SetGameState(GAMESTATE state, int nCounter);
GAMESTATE GetGameState();
void SetPause(bool bPause);

#endif