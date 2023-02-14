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

//グローバル変数宣言
TUTORIAL_MODE g_Tutorial;

//====================================================================
//ゲーム画面の初期化処理
//====================================================================
void InitEscapeTutorial()
{
	g_Tutorial = MODE_MOVE;
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

	SetEnemy(D3DXVECTOR3(-2300.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//スコアの初期化
	InitScore();

	//鍵の初期化処理
	InitKey();

	SetKey(D3DXVECTOR3(-1000.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), KEY_TYPE_ITEM);

	//鍵UIの初期化処理
	InitKeyUI();

	//エフェクトの初期化
	InitEffect();

	//出口の初期化処理
	InitExit();

	SetExit(D3DXVECTOR3(-1000.0f,0.0f,0.8f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXIT_TYPE_BIGFRAME,0);
	SetExit(D3DXVECTOR3(-1070.0f, 0.0f, 0.8f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), EXIT_TYPE_BIGDOOR_R,0);
	SetExit(D3DXVECTOR3(-935.0f, 0.0f, 0.8f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), EXIT_TYPE_BIGDOOR_L,0);

	//スコアアイテムの初期化
	InitItem();

	InitPolygonBG();

	InitTime();

	InitpaperBG00();
	InitpaperBG01();

	InitTutorialUI();

	//チェックボックスの初期化
	InitCheckboxUI();

	//フォグの初期化
	InitFog();

	//フォグの設定
	SetFog(D3DFOG_LINEAR, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), 10.0f, 1000.0f, 0.1f);

	//ステージの読み込み
	SetStage(4);
}

//====================================================================
//ゲーム画面の終了処理
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

	//出口の終了処理
	UninitExit();

	UninitTime();

	UninitpaperBG00();
	UninitpaperBG01();

	UninitTutorialUI();

	UninitCheckboxUI();

	UninitPolygonBG();

	//フォグの終了処理
	UninitFog();
}

//====================================================================
//ゲーム画面の更新処理
//====================================================================
void UpdateEscapeTutorial()
{

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_RETURN))
	{//ENTERキーを押したときリザルトにフェード
		SetFade(MODE_GAME);
	}
#endif

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	//UpdateSpotLight();

	//メッシュの壁の更新処理
	UpdateMeshWall();

	//床の更新処理
	UpdateMeshField();

	//オブジェクトの更新処理
	UpdateObject00();
	UpdateObjectBG();

	//プレイヤーの更新処理
	UpdatePlayer();

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

	//出口の更新処理
	UpdateExit();

	UpdateTime();

	UpdatepaperBG00();
	UpdatepaperBG01();

	UpdateTutorialUI();

	UpdateCheckboxUI();

	UpdatePolygonBG();

	switch (g_Tutorial)
	{
	case MODE_MOVE:

		break;

	case MODE_CAM_MOVE:

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
	}
}

//====================================================================
//ゲーム画面の描画処理
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

		//スタミナの描画処理
		DrawStamina();

		//ライフの描画処理
		DrawLife();

		DrawTime();

		//スコアの描画処理
		DrawScore();

		//スコアアイテムの描画処理
		DrawItem();

		//鍵の描画処理
		DrawKey();

		//鍵UIの描画処理
		DrawKeyUI();

		DrawpaperBG00();
		DrawpaperBG01();

		/*DrawTutorialUI();*/

		DrawCheckboxUI();

		//エフェクトの描画処理
		DrawEffect();

		DrawPolygonBG();

		//フォグの描画
		DrawFog();
	}

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);
}