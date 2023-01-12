#include "game.h"
#include "Fade.h"
#include "input.h"


bool g_bPause = false;
GAMESTATE gGameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;

void InitGame()
{
	g_bPause = false;

	DWORD time = timeGetTime();
	srand((unsigned int)time);
	SetGameState(GAMESTATE_READY, 60);

}

void UninitGame()
{
	
}

void UpdateGame()
{

	FADE Fade = GetFade();

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(Button_START, 0) || GetGamepadPress(Button_A, 0))
		{
			SetFade(MODE_RESULT);
		}
	}
}

void DrawGame()
{

}

void SetGameState(GAMESTATE state, int nCounter)
{
	gGameState = state;
	g_nCounterGameState = nCounter;
}

GAMESTATE GetGameState()
{
	return gGameState;
}

void SetPause(bool bPause)
{
	g_bPause = bPause;
}