//========================================================================================
//
// リザルトのゲームクリア処理[EscapeClearResult.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "EscapeClearResult.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "Object00.h"
#include "ObjectBG.h"
#include "ResultUI.h"
#include "fade.h"
#include "input.h"
#include "meshdome.h"
#include "meshcylinder.h"
#include "numberUI.h"

//グローバル変数宣言

//====================================================================
//透走モードのクリアリザルト画面の初期化処理
//====================================================================
void InitEscapeClearResult()
{
	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	InitMeshDome();

	InitMeshCylinder();

	InitObject00();
	InitObjectBG();

	//ステージの読み込み
	SetStage(3);

	InitNumberUI();

	InitResultUI();
}

//====================================================================
//透走モードのクリアリザルト画面の終了処理
//====================================================================
void UninitEscapeClearResult()
{
	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	UninitMeshDome();

	UninitMeshCylinder();

	UninitObject00();
	UninitObjectBG();

	UninitNumberUI();

	UninitResultUI();
}

//====================================================================
//透走モードのクリアリザルト画面の更新処理
//====================================================================
void UpdateEscapeClearResult()
{
	FADE Fade = GetFade();

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	UpdateMeshDome();

	UpdateMeshCylinder();

	UpdateObject00();
	UpdateObjectBG();

	UpdateNumberUI();

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
//透走モードのクリアリザルト画面の描画処理
//====================================================================
void DrawEscapeClearResult()
{
	D3DVIEWPORT9 viewportDef;

	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//現在のビューポートを取得
	pDevice->GetViewport(&viewportDef);

	//カメラのセット処理
	SetCamera(4);

	DrawMeshDome();

	DrawMeshCylinder();

	DrawObject00();
	DrawObjectBG();

	DrawNumberUI();

	DrawResultUI();

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);
}
