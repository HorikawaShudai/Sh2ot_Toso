#include "game.h"
#include "edit.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"
#include "stage.h"
#include "player.h"
#include "debugproc.h"


bool g_bPause = false;
bool g_bEdit = false;
GAMESTATE gGameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//====================================================================
//ゲーム画面の初期化処理
//====================================================================
void InitGame()
{
	g_bPause = false;
	g_bEdit = false;

	DWORD time = timeGetTime();
	srand((unsigned int)time);
	SetGameState(GAMESTATE_READY, 60);

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	InitMeshWall();

	InitObject00();

	InitPlayer();

	SetStage(0);
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

	UninitPlayer();
}

//====================================================================
//ゲーム画面の更新処理
//====================================================================
void UpdateGame()
{

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F2) == true)
	{//f2が押されたとき
		g_bEdit = g_bEdit ? false : true;
	}
#endif

	if (g_bPause == false && g_bEdit == false)
	{//ポーズ状態じゃないときかつエディット状態じゃないとき
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

	if (g_bEdit == true)
	{
		UpdateEdit();

		UpdateEditObject00();

		PrintDebugProc("カメラの視点移動【W】【A】【S】【D】\n");
		PrintDebugProc("カメラの注視点移動 【I】【J】【K】【L】\n");
		PrintDebugProc("カメラの上下移動 【左SHIFT】【左CTRL】\n");
		PrintDebugProc("プレイヤーの移動移動 【T】【F】【G】【H】\n");
	}
	else
	{
		UpdateObject00();

		UpdatePlayer();
	}
}

//====================================================================
//ゲーム画面の描画処理
//====================================================================
void DrawGame()
{
	//カメラの描画処理
	SetCamera();

	DrawMeshWall();

	if (g_bEdit == true)
	{
		DrawEditObject00();
	}
	DrawObject00();
	DrawPlayer();
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