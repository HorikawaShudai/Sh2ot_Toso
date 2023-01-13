#include "game.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"


bool g_bPause = false;
GAMESTATE gGameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//====================================================================
//ゲーム画面の初期化処理
//====================================================================
void InitGame()
{
	g_bPause = false;

	DWORD time = timeGetTime();
	srand((unsigned int)time);
	SetGameState(GAMESTATE_READY, 60);

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	InitMeshWall();

	InitObject00();
}

//====================================================================
//ゲーム画面の終了処理
//====================================================================
void UninitGame()
{
	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	UninitMeshWall();

	UninitObject00();
}

//====================================================================
//ゲーム画面の更新処理
//====================================================================
void UpdateGame()
{
	if (g_bPause == false)
	{//ポーズ状態じゃないとき
		FADE Fade = GetFade();

		if (Fade == FADE_NONE)
		{
			if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(BUTTON_A, 0) || GetGamepadPress(BUTTON_A, 0))
			{
				SetFade(MODE_RESULT);
			}
		}
	}

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	UpdateMeshWall();

	UpdateObject00();
}

//====================================================================
//ゲーム画面の描画処理
//====================================================================
void DrawGame()
{
	//カメラの描画処理
	SetCamera();

	DrawMeshWall();

	DrawObject00();
}

//====================================================================
//ゲームの状態の設定
//====================================================================
void SetGameState(GAMESTATE state, int nCounter)
{
	gGameState = state;
	g_nCounterGameState = nCounter;
}

//====================================================================
//ゲームモードの所得
//====================================================================
GAMESTATE GetGameState()
{
	return gGameState;
}

//====================================================================
//ポーズ状態の設定処理
//====================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}