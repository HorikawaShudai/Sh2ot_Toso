#include "EscapeOverResult.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "Object00.h"
#include "ObjectBG.h"
#include "ResultUI.h"
#include "fade.h"
#include "input.h"

//グローバル変数宣言

//====================================================================
//透走モードのゲームオーバーリザルト画面の初期化処理
//====================================================================
void InitEscapeOverResult()
{
	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	InitObjectBG();

	//ステージの読み込み
	SetStage(4);

	InitResultUI();
}

//====================================================================
//透走モードのゲームオーバーリザルト画面の終了処理
//====================================================================
void UninitEscapeOverResult()
{
	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	UninitObjectBG();

	UninitResultUI();
}

//====================================================================
//透走モードのゲームオーバーリザルト画面の更新処理
//====================================================================
void UpdateEscapeOverResult()
{
	FADE Fade = GetFade();

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	UpdateObjectBG();

	UpdateResultUI();

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(BUTTON_A, 0))
		{
			SetFade(MODE_RANKING);
		}
	}
}

//====================================================================
//透走モードのゲームオーバーリザルト画面の描画処理
//====================================================================
void DrawEscapeOverResult()
{
	D3DVIEWPORT9 viewportDef;

	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//現在のビューポートを取得
	pDevice->GetViewport(&viewportDef);

	//カメラのセット処理
	SetCamera(4);

	DrawObjectBG();

	DrawResultUI();

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);
}
