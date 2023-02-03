#include "VillainResult.h"
#include "camera.h"
#include "light.h"
#include "stage.h"

//グローバル変数宣言

//====================================================================
//悪透モードのリザルト画面の初期化処理
//====================================================================
void InitVillainResult()
{
	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//ステージの読み込み
	SetStage(2);
}

//====================================================================
//悪透モードのリザルト画面の終了処理
//====================================================================
void UninitVillainResult()
{
	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();
}

//====================================================================
//悪透モードのリザルト画面の更新処理
//====================================================================
void UpdateVillainResult()
{
	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();
}

//====================================================================
//悪透モードのリザルト画面の描画処理
//====================================================================
void DrawVillainResult()
{
	D3DVIEWPORT9 viewportDef;

	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//現在のビューポートを取得
	pDevice->GetViewport(&viewportDef);

	//カメラのセット処理
	SetCamera(4);

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);
}
