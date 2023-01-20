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
#include "enemy.h"
#include "stamina.h"
#include "life.h"
#include "field.h"

//グローバル変数宣言
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

	//床の初期化処理
	InitField();

	//メッシュ壁の初期化処理
	InitMeshWall();

	//オブジェクトの初期化処理
	InitObject00();

	//プレイヤーの初期化処理
	InitPlayer();

	//敵の初期化処理
	InitEnemy();

	//スタミナの初期化処理
	InitStamina();

	//ライフの初期化処理
	InitLife();

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

	//床の終了処理
	UninitField();

	//メッシュ壁の終了処理
	UninitMeshWall();

	//オブジェクトの終了処理
	UninitObject00();

	//プレイヤーの終了処理
	UninitPlayer();

	//敵の終了処理
	UninitEnemy();

	//スタミナの終了処理
	UninitStamina();

	//ライフの終了処理
	UninitLife();
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
			if (GetKeyboardPress(DIK_RETURN))
			{//ENTERキーを押したときリザルトにフェード
				SetFade(MODE_RESULT);
			}
		}
	}

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	//メッシュの壁の更新処理
	UpdateMeshWall();

	if (g_bEdit == true)
	{
		//エディットの更新処理
		UpdateEdit();

		//エディットモードのオブジェクトの更新処理
		UpdateEditObject00();

		PrintDebugProc("カメラの視点移動【W】【A】【S】【D】\n");
		PrintDebugProc("カメラの注視点移動 【I】【J】【K】【L】\n");
		PrintDebugProc("カメラの上下移動 【左SHIFT】【左CTRL】\n");
		PrintDebugProc("プレイヤーの移動移動 【T】【F】【G】【H】\n");
	}
	else
	{
		//床の更新処理
		UpdateField();

		//オブジェクトの更新処理
		UpdateObject00();

		//プレイヤーの更新処理
		UpdatePlayer();

		//敵の更新処理
		UpdateEnemy();

		//スタミナの更新処理
		UpdateStamina();

		//ライフの更新処理
		UpdateLife();
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
		//エディットモードのオブジェクト処理
		DrawEditObject00();
	}

	//床の描画処理
	DrawField();

	//オブジェクトの描画処理
	DrawObject00();

	//プレイヤーの描画処理
	DrawPlayer();

	//敵の描画処理
	DrawEnemy();

	//スタミナの描画処理
	DrawStamina();

	//ライフの描画処理
	DrawLife();
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