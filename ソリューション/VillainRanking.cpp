#include "VillainRanking.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "numberUI.h"
#include "RankingUI.h"
#include "RankingNumber.h"

//グローバル変数宣言

//====================================================================
//悪透モードのランキング画面の初期化処理
//====================================================================
void InitVillainRanking()
{
	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//ステージの読み込み
	SetStage(4);

	InitNumberUI();

	InitRankingUI();

	InitRanKingNumber();
}

//====================================================================
//悪透モードのランキング画面の終了処理
//====================================================================
void UninitVillainRanking()
{
	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	UninitNumberUI();

	UninitRankingUI();

	UninitRanKingNumber();
}

//====================================================================
//悪透モードのランキング画面の更新処理
//====================================================================
void UpdateVillainRanking()
{
	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	UpdateNumberUI();

	UpdateRankingUI();

	UpdateRanKingNumber();
}

//====================================================================
//悪透モードのランキング画面の描画処理
//====================================================================
void DrawVillainRanking()
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

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);
}
