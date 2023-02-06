#include "EscapeRanking.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "numberUI.h"
#include "RankingUI.h"
#include "RankingNumber.h"
#include "time.h"

//グローバル変数宣言

//====================================================================
//透走モードのランキング画面の初期化処理
//====================================================================
void InitEscapeRanking()
{
	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//ステージの読み込み
	SetStage(3);

	InitNumberUI();

	InitRankingUI();

	InitRanKingNumber();

	InitTime();
}

//====================================================================
//透走モードのランキング画面の終了処理
//====================================================================
void UninitEscapeRanking()
{
	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	UninitNumberUI();

	UninitRankingUI();

	UninitRanKingNumber();

	UninitTime();
}

//====================================================================
//透走モードのランキング画面の更新処理
//====================================================================
void UpdateEscapeRanking()
{
	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	UpdateNumberUI();

	UpdateRankingUI();

	UpdateRanKingNumber();

	UpdateTime();
}

//====================================================================
//透走モードのランキング画面の描画処理
//====================================================================
void DrawEscapeRanking()
{
	D3DVIEWPORT9 viewportDef;

	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//現在のビューポートを取得
	pDevice->GetViewport(&viewportDef);

	//カメラのセット処理
	SetCamera(4);

	DrawNumberUI();

	DrawRankingUI();

	DrawRanKingNumber();

	DrawTime();

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);
}
