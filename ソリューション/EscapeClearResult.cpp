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
#include "playerBG.h"
#include "sound.h"

//グローバル変数宣言
int g_nFadeCount;		//自動遷移用変数

//====================================================================
//透走モードのクリアリザルト画面の初期化処理
//====================================================================
void InitEscapeClearResult()
{
	g_nFadeCount = 0;

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	InitMeshDome();

	InitMeshCylinder();

	InitObject00();
	InitObjectBG();
	InitResultPlayer();

	//ステージの読み込み
	SetStage(3);

	InitNumberUI();

	InitResultUI();

	PlaySound(SOUND_LABEL_BGM_CLEAR);
}

//====================================================================
//透走モードのクリアリザルト画面の終了処理
//====================================================================
void UninitEscapeClearResult()
{
	StopSound();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	UninitMeshDome();

	UninitMeshCylinder();

	UninitObject00();
	UninitObjectBG();
	UninitResultPlayer();

	UninitNumberUI();

	UninitResultUI();

}

//====================================================================
//透走モードのクリアリザルト画面の更新処理
//====================================================================
void UpdateEscapeClearResult()
{
	FADE Fade = GetFade();
	bool ClearUi = GetbResultUi();

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	UpdateMeshDome();

	UpdateMeshCylinder();

	UpdateObject00();
	UpdateObjectBG();
	UpdateResultPlayer();

	UpdateNumberUI();

	UpdateResultUI();



	if (ClearUi == false)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_A, 0))
		{
			//決定音
			PlaySound(SOUND_LABEL_ENTER);

			SetbResultUi(true);
		}
	}
	if (Fade == FADE_NONE && ClearUi == true)
	{
		g_nFadeCount++;
		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_A, 0) || g_nFadeCount == 1200)
		{
			//決定音
			PlaySound(SOUND_LABEL_ENTER);

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
	DrawResultPlayer();

	DrawNumberUI();

	DrawResultUI();

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);
}
