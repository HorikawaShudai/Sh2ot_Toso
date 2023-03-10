#include "game.h"
#include "edit.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"
#include "objectBG.h"
#include "objectLight.h"
#include "ObjectWall.h"
#include "objectPoly.h"
#include "stage.h"
#include "player.h"
#include "debugproc.h"
#include "enemy.h"
#include "stamina.h"
#include "life.h"
#include "meshfield.h"
#include "meshfield.h"
#include "score_item.h"
#include "score.h"
#include "PlayNumberSelect.h"
#include "key.h"
#include "keyUI.h"
#include "Effect.h"
#include "exit.h"
#include "SpotLight.h"
#include "polygonBG.h"
#include "fog.h"
#include "time.h"
#include "ActionHelpUI.h"
#include "sound.h"
#include "pause.h"
#include "particle.h"
#include "ChasePolygon.h"
#include "LifePolygon.h"
#include "NeedKeyPolygon.h"
#include "TimeUpPolygon.h"

//エディットに使うオブジェクトの種類の構造体
typedef enum
{
	EDIT_TYPE_NORMAL = 0,
	EDIT_TYPE_BG,
	EDIT_TYPE_POLY,
	EDIT_TYPE_WALL,
	EDIT_TYPE_LIGHT,
	EDIT_TYPE_MAX,
}EDIT_TYPE;

//グローバル変数宣言
bool g_bEdit = false;
int g_bBG_Edit = 0;
int g_bGameClear = 0;
GAMESTATE gGameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int GameSetEnemyCount = 0;

//====================================================================
//ゲーム画面の初期化処理
//====================================================================
void InitGame()
{
	//ポーズ情報の取得
	Pause *pPause = GetPause();

	g_bEdit = false;
	g_bBG_Edit = 0;
	g_bGameClear = 0;
	GameSetEnemyCount = 0;

	DWORD time = timeGetTime();
	srand((unsigned int)time);
	SetGameState(GAMESTATE_READY, 60);

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//InitSpotLight();

	//床の初期化処理
	InitMeshField();

	//メッシュ壁の初期化処理
	InitMeshWall();

	//オブジェクトの初期化処理
	InitObject00();
	InitObjectBG();
	InitObjectLight();
	InitObjectWall();
	InitObjectPoly();

	//プレイヤーの初期化処理
	InitPlayer();

	//敵の初期化処理
	InitEnemy();

	//ヘルプUIの初期化処理
	InitActionHelpUI();

	//スタミナの初期化処理
	InitStamina();

	//ライフの初期化処理
	InitLife();

	//鍵の初期化処理
	InitKey();

	//鍵UIの初期化処理
	InitKeyUI();

	InitNeedKeyPolygon();

	//エフェクトの初期化
	InitEffect();

	//パーティクルの初期化処理
	InitParticle();

	//出口の初期化処理
	InitExit();

	//出口の読み込み
	LoadExit(0);

	InitPolygonBG();

	InitTime();

	//フォグの初期化
	InitFog();

	//ポーズの初期化処理
	InitPause();

	//ポーズ状態のON/OFF
	pPause->bUse = false;

	//フォグの設定
	SetFog(D3DFOG_LINEAR, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f), 10.0f, 1000.0f, 0.1f);
	
	//プレイヤーの数に応じて敵をセットする回数を指定する。
	switch (GetPlayNumberSelect().CurrentSelectNumber)
	{
	case 1:
		GameSetEnemyCount = 2;
		break;
	case 2:
		GameSetEnemyCount = 2;
		break;
	case 3:
		GameSetEnemyCount = 3;
		break;
	case 4:
		GameSetEnemyCount = 3;
		break;
	}

	//敵設置用変数の値のぶん敵を設置する
	for (int nCnt = 0; nCnt < GameSetEnemyCount; nCnt++)
	{

	}
	SetEnemy(D3DXVECTOR3(-2162.46f, 0.0f, 1529.39f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(-1045.0f,  0.0f,1750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(160.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//プレイヤーの数だけ鍵を設置する
	PatternSetKey(GetPlayNumberSelect().CurrentSelectNumber);

	InitChasePolygon();

	InitLifePolygon();

	InitTimeUpPolygon();

	//ステージの読み込み
	SetStage(0);

	//ゲーム内のBGM(雨)
	PlaySound(SOUND_LABEL_BGM_GAMESOUND);
}

//====================================================================
//ゲーム画面の終了処理
//====================================================================
void UninitGame()
{
	//サウンドの終了
	StopSound();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//UninitSpotLight();

	//床の終了処理
	UninitMeshField();

	//メッシュ壁の終了処理
	UninitMeshWall();

	//オブジェクトの終了処理
	UninitObject00();
	UninitObjectBG();
	UninitObjectLight();
	UninitObjectWall();
	UninitObjectPoly();

	//プレイヤーの終了処理
	UninitPlayer();

	//敵の終了処理
	UninitEnemy();

	//ヘルプUIの終了処理
	UninitActionHelpUI();

	//スタミナの終了処理
	UninitStamina();

	//ライフの終了処理
	UninitLife();

	//鍵の終了処理
	UninitKey();

	//鍵UIの終了処理
	UninitKeyUI();

	UninitNeedKeyPolygon();

	//エフェクトの終了処理
	UninitEffect();

	//パーティクルの終了処理
	UninitParticle();

	//出口の終了処理
	UninitExit();

	UninitTime();

	UninitLifePolygon();

	UninitChasePolygon();

	UninitPolygonBG();

	UninitTimeUpPolygon();

	//ポーズの終了処理
	UninitPause();

	//フォグの終了処理
	UninitFog();
}

//====================================================================
//ゲーム画面の更新処理
//====================================================================
void UpdateGame()
{
	//ポーズ情報の取得
	Pause *pPause = GetPause();

	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F2) == true)
	{//f2が押されたとき
		g_bEdit = g_bEdit ? false : true;
	}

	if (GetKeyboardTrigger(DIK_F3) == true)
	{//f3が押されたとき
		g_bBG_Edit++;
		if (g_bBG_Edit >= EDIT_TYPE_MAX)
		{
			g_bBG_Edit = 0;
		}
	}

	if (GetKeyboardTrigger(DIK_R) == true)
	{
		SetFade(MODE_GAME);
	}

#endif

	if (GetKeyboardTrigger(DIK_P) == true || GetGamepadTrigger(BUTTON_START, 0) == true)
	{//ポーズ処理
		pPause->bUse = pPause->bUse ? false : true;
	}
	else if (GetKeyboardTrigger(DIK_P) == true || GetGamepadTrigger(BUTTON_START, 0) == true && pPause->bUse == false)
	{
		//ポーズを閉じた時選択を最初に戻す
		InitPause();
	}

	if (pPause->bUse == true)
	{//ポーズが使われているとき
		//ポーズの更新処理
		UpdatePause();

		for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
		{//ポーズ中バイブを止める処理
			GetGamepad_Vibrtion_false(nCntPlayer);
		}
	}

#ifdef _DEBUG
	if (pPause->bUse == false && g_bEdit == false)
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
#endif

	if (pPause->bUse == false && GetTimeCount() == true)
	{//ポーズ状態じゃないとき

	//カメラの更新処理
		UpdateCamera();

		//ライトの更新処理
		UpdateLight();

		//UpdateSpotLight();

		//メッシュの壁の更新処理
		UpdateMeshWall();

		//オブジェクトの更新処理
		UpdateObject00();
		UpdateObjectBG();
		UpdateObjectLight();
		UpdateObjectWall();
		UpdateObjectPoly();

		if (g_bEdit == true)
		{//エディットモードの時

			//エディットの更新処理
			UpdateEdit();

			switch (g_bBG_Edit)
			{
			case EDIT_TYPE_NORMAL:
				//エディットモードのオブジェクトの更新処理
				UpdateEditObject00();
				break;
			case EDIT_TYPE_BG:
				//エディットモードのオブジェクトBGの更新処理
				UpdateEditObjectBG();
				break;
			case EDIT_TYPE_POLY:
				//エディットモードのオブジェクトPolyの更新処理
				UpdateEditObjectPoly();
				break;
			case EDIT_TYPE_WALL:
				//エディットモードのオブジェクトWallの更新処理
				UpdateEditObjectWall();
				break;
			case EDIT_TYPE_LIGHT:
				//エディットモードのオブジェクトLightの更新処理
				UpdateEditObjectLight();
				break;
			}
		}

		if (g_bEdit == false)
		{//エディット状態じゃないとき

#ifdef _DEBUG
			PrintDebugProc("カメラの視点移動【W】【A】【S】【D】\n");
			PrintDebugProc("カメラの注視点移動 【I】【J】【K】【L】\n");
			PrintDebugProc("カメラの上下移動 【左SHIFT】【左CTRL】\n");
			PrintDebugProc("プレイヤーの移動移動 【T】【F】【G】【H】\n");
			PrintDebugProc("デバッグ表示のオン/オフ 【F1】\n");
			PrintDebugProc("エディットモードのオン/オフ 【F2】\n");
			PrintDebugProc("ゲーム用と背景用オブジェクトの切り替え 【F3】\n");
			PrintDebugProc("プレイヤーの視点切り替え 【F4】\n");
			PrintDebugProc("プレイヤーカメラと観察用カメラの切り替え 【F5】\n");
			PrintDebugProc("バイブレーションをオンにする 【F6】\n");
			PrintDebugProc("バイブレーションをオフにする 【F7】\n");
			PrintDebugProc("ナイトビジョンのオン/オフ 【F8】\n");
			PrintDebugProc("エディットモード時のセーブ 【F9】\n");
			PrintDebugProc("ワイヤーフレームのオン/オフ【F11】\n");
#endif // _DEBUG

			//床の更新処理
			UpdateMeshField();

			//プレイヤーの更新処理
			UpdatePlayer();

			//敵の更新処理
			UpdateEnemy();

			//ヘルプUIの更新処理
			UpdateActionHelpUI();

			//スタミナの更新処理
			UpdateStamina();

			//ライフの更新処理
			UpdateLife();

			//鍵の更新処理
			UpdateKey();

			//鍵UIの更新処理
			UpdateKeyUI();

			UpdateNeedKeyPolygon();

			//エフェクトの更新処理
			UpdateEffect();

			//パーティクルの更新処理
			UpdateParticle();

			//出口の更新処理
			UpdateExit();

			//タイムの更新処理
			UpdateTime();

			UpdateLifePolygon();

			UpdateChasePolygon();

			//ダメージリアクション用ポリゴンの更新処理
			UpdatePolygonBG();
		}
	}

	if (g_bGameClear == 0)
	{//クリアしていない状態の時
		UpdateTimeUpPolygon();
	}

	switch (gGameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_CLEAR_END:		//ゲームクリア時
		g_nCounterGameState--;
		if (g_nCounterGameState <= 0)
		{
			gGameState = GAMESTATE_NORMAL;

			//フェードの状態を変える
			SetFade(MODE_RESULT);
		}
		break;

	case GAMESTATE_GAMEOVER_END:	//ゲームオーバー時
		g_nCounterGameState--;
		if (g_nCounterGameState <= 0)
		{
			gGameState = GAMESTATE_NORMAL;

			//フェードの状態を変える
			SetFade(MODE_RESULT);

			SetClear(0);
		}
		break;
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

	//プレイヤー情報の取得
	Player *pPlayer = GetPlayer();

	//ポーズ情報の取得
	Pause *pPause = GetPause();

	//現在のビューポートを取得
	pDevice->GetViewport(&viewportDef);
	 
	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++,pPlayer++)
	{
		//カメラのセット処理
		SetCamera(nCnt);

		//プレイヤーが保持するライトの描画処理
		DrawLight(nCnt);

		//メッシュウォールの描画処理
		DrawMeshWall();

		if (g_bEdit == true)
		{
			switch (g_bBG_Edit)
			{
			case EDIT_TYPE_NORMAL:
				//エディットモードのオブジェクトの描画処理
				DrawEditObject00();
				break;
			case EDIT_TYPE_BG:
				//エディットモードのオブジェクトBGの描画処理
				DrawEditObjectBG();
				break;
			case EDIT_TYPE_POLY:
				//エディットモードのオブジェクトPolyの描画処理
				DrawEditObjectPoly();
				break;
			case EDIT_TYPE_WALL:
				//エディットモードのオブジェクトWallの描画処理
				DrawEditObjectWall();
				break;
			case EDIT_TYPE_LIGHT:
				//エディットモードのオブジェクトLightの描画処理
				DrawEditObjectLight();
				break;
			}
		}

		//床の描画処理
		//DrawMeshField();

		//オブジェクトの描画処理
		DrawObjectPoly();
		DrawObject00();
		DrawObjectBG();
		DrawObjectLight();
		DrawObjectWall();

		//出口の描画処理
		DrawExit();

		//プレイヤーの描画処理
		DrawPlayer();

		if (pPlayer->bAppear == true)
		{
			//敵の描画処理
			DrawEnemy();
		}

		//ヘルプUIの描画処理
		DrawActionHelpUI(nCnt,pPlayer->bGetKey);

		//スタミナの描画処理
		DrawStamina();

		//鍵の描画処理
		DrawKey();

		//エフェクトの描画処理
		DrawEffect();

		//パーティクルの描画
		DrawParticle();

		//鍵UIの描画処理
		DrawKeyUI();

		DrawNeedKeyPolygon(nCnt);

		if (pPlayer->bEnemyLeft == true || pPlayer->bEnemyRight == true)
		{
			DrawChasePolygon(nCnt);
		}

		DrawLifePolygon();

		DrawPolygonBG();

		//ライフの描画処理
		DrawLife();

		//フォグの描画
		DrawFog();
	}

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);

	//タイムの描画処理
	DrawTime();

	DrawTimeUpPolygon();

	if (pPause->bUse == true)
	{//ポーズ中だった場合
	 //ポーズの描画処理
		DrawPause();
	}
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
//クリア情報の所得
//====================================================================
int GetClear(void)
{
	return g_bGameClear;
}

//====================================================================
//クリア情報の設定
//====================================================================
void SetClear(int ClearNumber)
{
	g_bGameClear = ClearNumber;
}

//====================================================================
//クリア情報のリセット
//====================================================================
void ResetClear(void)
{
	g_bGameClear = 0;
}
