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
#include "score_item.h"
#include "score.h"
#include "PlayNumberSelect.h"
#include "key.h"
#include "keyUI.h"
#include "Effect.h"

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

	//注意：敵の座標はn100+50を原則とする
	SetEnemy(D3DXVECTOR3(50.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//スコアの初期化
	InitScore();

	//鍵の初期化処理
	InitKey();

	//鍵UIの初期化処理
	InitKeyUI();

	//エフェクトの初期化
	InitEffect();

	//スコアアイテムの初期化
	InitItem();
	SetItem(D3DXVECTOR3(0.0f,0.0f,-40.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), 0);
	SetItem(D3DXVECTOR3(40.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(100.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(150.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(-50.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(-100.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(-150.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(-200.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(200.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(250.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(250.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(150.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(-50.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(50.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

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

	//スコアの終了処理
	UninitScore();

	//アイテムの終了処理
	UninitItem();

	//鍵の終了処理
	UninitKey();

	//鍵UIの終了処理
	UninitKeyUI();

	//エフェクトの終了処理
	UninitEffect();
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
	{//エディットモードの時

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
	{//通常モードの時

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


		//スコアの更新処理
		UpdateScore();

		//スコアアイテムの更新処理
		UpdateItem();

		//鍵の更新処理
		UpdateKey();

		//鍵UIの更新処理
		UpdateKeyUI();

		//エフェクトの更新処理
		UpdateEffect();
	}
}

//====================================================================
//ゲーム画面の描画処理
//====================================================================
void DrawGame()
{
	D3DVIEWPORT9 viewportDef;

	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//現在のビューポートを取得
	pDevice->GetViewport(&viewportDef);
	 
	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		//カメラのセット処理
		SetCamera(nCnt);

		//メッシュウォールの描画処理
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

		//スコアの描画処理
		DrawScore();

		//スコアアイテムの描画処理
		DrawItem();

		//鍵の描画処理
		DrawKey();

		//鍵UIの描画処理
		DrawKeyUI();

		//エフェクトの描画処理
		DrawEffect();
	}

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);
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