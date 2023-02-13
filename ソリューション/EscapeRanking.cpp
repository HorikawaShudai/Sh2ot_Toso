#include "EscapeRanking.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "numberUI.h"
#include "RankingUI.h"
#include "RankingNumber.h"
#include "object00.h"
#include "objectBG.h"
#include "objectLight.h"
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

	//オブジェクトの初期化処理
	InitObject00();
	InitObjectBG();
	InitObjectLight();

	//ステージの読み込み
	SetStage(0);

	InitNumberUI();

	InitRankingUI();

	InitRanKingNumber();
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

	//オブジェクトの終了処理
	UninitObject00();
	UninitObjectBG();
	UninitObjectLight();

	UninitNumberUI();

	UninitRankingUI();

	UninitRanKingNumber();
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

	//オブジェクトの更新処理
	UpdateObject00();
	UpdateObjectBG();
	UpdateObjectLight();

	UpdateNumberUI();

	UpdateRankingUI();

	UpdateRanKingNumber();
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

	//オブジェクトの描画処理
	DrawObject00();
	DrawObjectBG();
	DrawObjectLight();

	DrawNumberUI();

	DrawRankingUI();

	DrawRanKingNumber();

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);
}
