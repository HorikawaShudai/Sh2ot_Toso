#include "game.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"
#include "objectBG.h"
#include "stage.h"
#include "player.h"
#include "debugproc.h"
#include "enemy.h"
#include "stamina.h"
#include "life.h"
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
#include "paperBG00.h"
#include "paperBG01.h"
#include "tutorialUI.h"
#include "CheckboxUI.h"
#include "EscapeTutorial.h"
#include "ActionHelpUI.h"
#include "player.h"
#include "sound.h"
#include "particle.h"
#include "ChasePolygon.h"
#include "NeedKeyPolygon.h"

//グローバル変数宣言
TUTORIAL_STATE g_EscapeTutorialState;
TUTORIAL_GUYDE g_EscapeTutorialGuyde;
int g_EscapeCounter;
TUTORIAL_MODE g_EscapeTutorial;
bool bpEscapeMove[NUM_PLAYER];
bool bpEscapeCamMove[NUM_PLAYER];

//====================================================================
//チュートリアル画面の初期化処理
//====================================================================
void InitEscapeTutorial()
{
	g_EscapeTutorialState = TUTORIAL_STATE_GUYDE;
	g_EscapeTutorialGuyde = TUTORIAL_GUYDE_ESCAPE;
	g_EscapeTutorial = MODE_MOVE;
	g_EscapeCounter = 0;

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		bpEscapeMove[nCntPlayer] = true;
		bpEscapeCamMove[nCntPlayer] = true;
	}

	for (int nCntPlayer = 0; nCntPlayer < GetPlayNumberSelect().CurrentSelectNumber; nCntPlayer++)
	{
		bpEscapeMove[nCntPlayer] = false;
		bpEscapeCamMove[nCntPlayer] = false;
	}

	DWORD time = timeGetTime();
	srand((unsigned int)time);

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

	//プレイヤーの初期化処理
	InitPlayer();

	//敵の初期化処理
	InitEnemy();

	//スタミナの初期化処理
	InitStamina();

	//ライフの初期化処理
	InitLife();

	////スコアの初期化
	//InitScore();

	//鍵の初期化処理
	InitKey();

	//鍵UIの初期化処理
	InitKeyUI();

	//エフェクトの初期化
	InitEffect();

	//パーティクルの初期化
	InitParticle();

	//出口の初期化処理
	InitExit();

	////スコアアイテムの初期化
	//InitItem();

	InitNeedKeyPolygon();

	InitActionHelpUI();

	InitChasePolygon();

	InitPolygonBG();

	InitTime();

	InitPaperBG00();
	InitPaperBG01();

	InitTutorialUI();

	//チェックボックスの初期化
	InitCheckboxUI();

	//フォグの初期化
	InitFog();

	//フォグの設定
	SetFog(D3DFOG_LINEAR, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), 10.0f, 1000.0f, 0.1f);

	//出口を読み込む
	LoadExit(2);

	//ステージの読み込み
	SetStage(4);
}

//====================================================================
//チュートリアル画面の終了処理
//====================================================================
void UninitEscapeTutorial()
{
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

	//プレイヤーの終了処理
	UninitPlayer();

	//敵の終了処理
	UninitEnemy();

	//スタミナの終了処理
	UninitStamina();

	//ライフの終了処理
	UninitLife();

	////スコアの終了処理
	//UninitScore();

	////アイテムの終了処理
	//UninitItem();

	//鍵の終了処理
	UninitKey();

	//鍵UIの終了処理
	UninitKeyUI();

	//エフェクトの終了処理
	UninitEffect();

	//パーティクルの終了処理
	UninitParticle();

	//出口の終了処理
	UninitExit();

	UninitNeedKeyPolygon();

	UninitActionHelpUI();

	UninitChasePolygon();

	UninitTime();

	UninitPaperBG00();
	UninitPaperBG01();

	UninitTutorialUI();

	UninitCheckboxUI();

	UninitPolygonBG();

	//フォグの終了処理
	UninitFog();
}

//====================================================================
//チュートリアル画面の更新処理
//====================================================================
void UpdateEscapeTutorial()
{
	FADE pFade = GetFade();

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	int nPlayer = GetCurrentCamera();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_V))
	{
		switch (g_EscapeTutorialState)
		{
		case TUTORIAL_STATE_GUYDE:
			g_EscapeTutorialState = TUTORIAL_STATE_STANDBY;
			break;
		case TUTORIAL_STATE_STANDBY:
			g_EscapeTutorialState = TUTORIAL_STATE_WAIT;
			break;
		case TUTORIAL_STATE_WAIT:
			g_EscapeTutorialState = TUTORIAL_STATE_PLAY;
			break;
		case TUTORIAL_STATE_PLAY:
			break;
		}
	}

#endif

	//ガイドのページを進ませる処理
	if (GetKeyboardTrigger(DIK_C) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
	{

		switch (g_EscapeTutorialGuyde)
		{
		case TUTORIAL_GUYDE_ESCAPE:
			g_EscapeTutorialGuyde = TUTORIAL_GUYDE_KEY;

			//紙をめくる音
			PlaySound(SOUND_LABEL_PAPER);
			break;

		case TUTORIAL_GUYDE_KEY:
			g_EscapeTutorialGuyde = TUTORIAL_GUYDE_HEALTH;

			//紙をめくる音
			PlaySound(SOUND_LABEL_PAPER);
			break;

		case TUTORIAL_GUYDE_HEALTH:
			g_EscapeTutorialGuyde = TUTORIAL_GUYDE_MAX;
			break;
		}
	}

	//ガイドのページを戻す処理
	if (GetKeyboardTrigger(DIK_B) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
	{
		switch (g_EscapeTutorialGuyde)
		{
		case TUTORIAL_GUYDE_HEALTH:
			g_EscapeTutorialGuyde = TUTORIAL_GUYDE_KEY;

			//紙をめくる音
			PlaySound(SOUND_LABEL_PAPER);
			break;

		case TUTORIAL_GUYDE_KEY:
			g_EscapeTutorialGuyde = TUTORIAL_GUYDE_ESCAPE;

			//紙をめくる音
			PlaySound(SOUND_LABEL_PAPER);
			break;

		case TUTORIAL_GUYDE_ESCAPE:
			
			break;
		}
	}

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadTrigger(BUTTON_START, 0) == true)
		{//ENTERキーを押したときリザルトにフェード
			SetFade(MODE_GAME);
		}
	}
	//UpdateSpotLight();

	switch (g_EscapeTutorialState)
	{
	case TUTORIAL_STATE_GUYDE:	//スタンバイ状態

			//チェックボックスを人数分オフにする
			for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
			{
				SetCheckUI(nCntTutorial, false);
			}

			if (g_EscapeTutorialGuyde == TUTORIAL_GUYDE_MAX)
			{
				if (GetKeyboardTrigger(DIK_N) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
				{
					g_EscapeTutorialState = TUTORIAL_STATE_STANDBY;
				}
			}

		break;

	case TUTORIAL_STATE_STANDBY:	//スタンバイ状態
		SetPaperBG00(true);
		SetTutorialUI(true,0);
		for (int nCntTutorial = 1; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber + 1; nCntTutorial++)
		{
			SetTutorialUI(false, nCntTutorial);
			MovePosCheckUI(nPlayer, true);
		}
		for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
		{
			SetPaperBG01(false, nCntTutorial);
		}

		g_EscapeCounter = 0;
		break;
	case TUTORIAL_STATE_WAIT:	//待機状態
		SetPaperBG00(true);
		SetTutorialUI(true,0);
		g_EscapeCounter++;
		if (g_EscapeCounter > 100)
		{
			//チェックボックスを人数分オフにする
			for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
			{
				SetCheckUI(nCntTutorial, false);
			}
			g_EscapeTutorialState = TUTORIAL_STATE_PLAY;
		}
		break;
	case TUTORIAL_STATE_PLAY:	//プレイ状態
		SetPaperBG00(false);
		SetTutorialUI(false,0);

		for (int nCntTutorial = 1; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber + 1; nCntTutorial++)
		{
			SetTutorialUI(true, nCntTutorial);
			MovePosCheckUI(nPlayer, false);
		}
		for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
		{
			SetPaperBG01(true, nCntTutorial);
		}
		break;
	}

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	//メッシュの壁の更新処理
	UpdateMeshWall();

	//床の更新処理
	UpdateMeshField();

	//オブジェクトの更新処理
	UpdateObject00();
	UpdateObjectBG();

	//チュートリアル実行画面の時のみ移動可能
	if (g_EscapeTutorialState == TUTORIAL_STATE_PLAY)
	{
		//プレイヤーの更新処理
		UpdatePlayer();

		//スタミナの更新処理
		UpdateStamina();

		//ライフの更新処理
		UpdateLife();

		////スコアの更新処理
		//UpdateScore();

		////スコアアイテムの更新処理
		//UpdateItem();

		//鍵の更新処理
		UpdateKey();

		//鍵UIの更新処理
		UpdateKeyUI();

		//エフェクトの更新処理
		UpdateEffect();

		//パーティクルの更新
		UpdateParticle();

		//出口の更新処理
		UpdateExit();
	}
	UpdateNeedKeyPolygon();

	UpdateActionHelpUI();

	UpdateChasePolygon();

	UpdateTime();

	UpdatePaperBG00();
	UpdatePaperBG01();

	UpdateTutorialUI();

	UpdateCheckboxUI();

	UpdatePolygonBG();

	switch (g_EscapeTutorial)
	{
	case MODE_MOVE:
		break;

	case MODE_DASH:

		break;

	case MODE_STELTH:

		break;

	case MODE_VIBE:

		break;

	case MODE_GET_KEY:

		break;

	case MODE_ESCAPE:

		break;

	case MODE_GOEXIT:

		break;

	case MODE_END:

		if (pFade == FADE_NONE)
		{
			SetFade(MODE_GAME);			//モードの設定(ゲーム画面に移行)
		}

		break;

	}
}

//====================================================================
//チュートリアル画面の描画処理
//====================================================================
void DrawEscapeTutorial()
{
	D3DVIEWPORT9 viewportDef;

	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	Player *pPlayer = GetPlayer();

	//現在のビューポートを取得
	pDevice->GetViewport(&viewportDef);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++, pPlayer++)
	{
		//カメラのセット処理
		SetCamera(nCnt);

		//プレイヤーが保持するライトの描画処理
		DrawLight(nCnt);

		//メッシュウォールの描画処理
		DrawMeshWall();

		//床の描画処理
		DrawMeshField();

		//オブジェクトの描画処理
		DrawObject00();
		DrawObjectBG();

		//出口の描画処理
		DrawExit();

		//プレイヤーの描画処理
		DrawPlayer();

		if (pPlayer->bAppear == true)
		{
			//敵の描画処理
			DrawEnemy();
		}

		DrawNeedKeyPolygon(nCnt);

		//ヘルプUIの描画処理
		DrawActionHelpUI(nCnt, pPlayer->bGetKey);

		//スタミナの描画処理
		DrawStamina();

		//ライフの描画処理
		DrawLife();

		DrawTime();

		////スコアの描画処理
		//DrawScore();

		////スコアアイテムの描画処理
		//DrawItem();

		//鍵の描画処理
		DrawKey();

		//エフェクトの描画処理
		DrawEffect();

		//パーティクルの描画
		DrawParticle();

		DrawChasePolygon(nCnt);

		//鍵UIの描画処理
		DrawKeyUI();

		DrawPolygonBG();

		//フォグの描画
		DrawFog();
	}

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);

	DrawPaperBG00();
	DrawPaperBG01();

	DrawTutorialUI();

	if (g_EscapeTutorial != MODE_GOEXIT || g_EscapeTutorialState != TUTORIAL_STATE_PLAY)
	{
		//チェックボックスの描画
		DrawCheckboxUI();
	}
}

//====================================================================
//チュートリアル画面の状態管理
//====================================================================
TUTORIAL_STATE GetEscapeTutorial()
{
	return g_EscapeTutorialState;
}

//====================================================================
//チュートリアル画面ガイドの状態管理
//====================================================================
TUTORIAL_GUYDE GetEscapeTutorialGuyde()
{
	return g_EscapeTutorialGuyde;
}


//====================================================================
//チュートリアル画面の状態管理
//====================================================================
void SetEscapeTutorial(TUTORIAL_STATE nSet)
{
	g_EscapeTutorialState = nSet;
}

//====================================================================
//チュートリアル項目の状態管理
//====================================================================
void DoEscapeTutorial(TUTORIAL_MODE nMode)
{
	g_EscapeTutorial = nMode;
}

//=====================================
//チュートリアル項目の情報を与える処理
//=====================================
TUTORIAL_MODE GetDoEscapeTutorial(void)
{
	return g_EscapeTutorial;
}

//==============================
//移動したかどうかのチェック用
//==============================
void MoveTCheck(int nCnt,bool check)
{
	//プレイヤーが動いたことに
	bpEscapeMove[nCnt] = check;
}

//==================================
//カメラが動いたかどうかのチェック
//==================================
void CamMoveTCheck(int nCnt,bool camcheck)
{
	//カメラが動いたことに
	bpEscapeCamMove[nCnt] = camcheck;

	//プレイヤーとカメラが動いたときに
	if (bpEscapeMove[nCnt] == true && bpEscapeCamMove[nCnt] == true)
	{
		//チェックをつける処理
		SetCheckUI(nCnt, true);
	}
}

