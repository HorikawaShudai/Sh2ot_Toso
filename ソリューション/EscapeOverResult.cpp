//========================================================================================
//
// リザルトのゲームオーバー処理[EscapeOverResult.cpp]
// Author: 坂本　翔唯
//
//========================================================================================

#include "EscapeOverResult.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "Object00.h"
#include "ObjectBG.h"
#include "ObjectLight.h"
#include "ResultUI.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//マクロ定義
#define INIT_SCREENTEX_X0  (0.0f)	   //テクスチャX軸の最初の位置
#define INIT_SCREENTEX_Y0  (0.0f)      //テクスチャY軸の最初の位置

#define INIT_SCREENTEX_X1  (1280.0f)  //テクスチャX軸の右側の位置
#define INIT_SCREENTEX_Y1  (720.0f)   //テクスチャY軸の最初の位置

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureOver = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOver = NULL;		//頂点バッファへのポインタ
int ntransition;									//遷移するまでの時間								

//====================================================================
//透走モードのゲームオーバーリザルト画面の初期化処理
//====================================================================
void InitEscapeOverResult()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//遷移する時間までの初期化
	ntransition = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RESULT\\GAME_OVER.png",
		&g_pTextureOver);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOver,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffOver->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(INIT_SCREENTEX_X0,INIT_SCREENTEX_Y0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(INIT_SCREENTEX_X1,INIT_SCREENTEX_Y0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(INIT_SCREENTEX_X0,INIT_SCREENTEX_Y1, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(INIT_SCREENTEX_X1,INIT_SCREENTEX_Y1, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	InitObject00();
	InitObjectBG();
	InitObjectLight();

	//ステージの読み込み
	SetStage(5);

	//ゲームオーバーBGM(ノイズ)
	PlaySound(SOUND_LABEL_BGM_GAMEOVER);
	//InitResultUI();
}

//====================================================================
//透走モードのゲームオーバーリザルト画面の終了処理
//====================================================================
void UninitEscapeOverResult()
{
	//サウンドを止める
	StopSound();

	//テクスチャの破棄
	if (g_pTextureOver != NULL)
	{
		g_pTextureOver->Release();
		g_pTextureOver = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffOver != NULL)
	{
		g_pVtxBuffOver->Release();
		g_pVtxBuffOver = NULL;
	}

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	UninitObject00();
	UninitObjectBG();
	UninitObjectLight();

	//UninitResultUI();
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

	UpdateObject00();
	UpdateObjectBG();
	UpdateObjectLight();

	//UpdateResultUI();

	//タイトル画面へ遷移
	if (Fade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(BUTTON_A, 0) || ntransition >= 420)
		{
			SetFade(MODE_TITLE);
		}
		//遷移する時間までを加算
		ntransition++;
	}
}

//====================================================================
//透走モードのゲームオーバーリザルト画面の描画処理
//====================================================================
void DrawEscapeOverResult()
{
	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVIEWPORT9 viewportDef;

	//現在のビューポートを取得
	pDevice->GetViewport(&viewportDef);

	//カメラのセット処理
	SetCamera(4);

	DrawObject00();
	DrawObjectBG();
	DrawObjectLight();

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);

	pDevice->SetStreamSource(0, g_pVtxBuffOver, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureOver);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
