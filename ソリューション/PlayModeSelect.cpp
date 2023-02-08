//======================================================================================
//
// ステージ処理[stage.cpp]
// Author:小笠原　彪
//
//======================================================================================
#include <stdio.h>
#include "PlayModeSelect.h"
#include "PlayNumberSelect.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "debugproc.h"

//***********************************
//マクロ定義
//***********************************
#define MAX_TEX			(2)				//テクスチャの最大数
#define NUM_PLAYMODE	(2)				//ステージの最大数
#define NUM_POLY		(NUM_PLAYMODE)	//ポリゴンの数
#define MAX_BUFF		(1)				//バッファの最大数

#define NUM_ICON_TEX	(2)				//ポリゴンの数


#define ICON_POS_X		(400.0f)		//選択アイコンの位置(X軸)
#define ICON_POS_Y		(400.0f)		//選択アイコンの位置(Y軸)
#define ICON_SIZE_X		(100.0f)		//選択アイコンの大きさ(X軸)
#define ICON_SIZE_Y		(200.0f)		//選択アイコンの大きさ(Y軸)
#define BRANK_LENGTH	(400.0f)		//選択アイコン同士の間の距離

//***********************************
//テクスチャファイル名
//***********************************
const char *c_apFilenameStage[MAX_TEX] =
{
	"Data\\TEXTURE\\PLAYMODE\\Tousou_logo.png",		//タイトル背景
	"data\\TEXTURE\\PLAYMODE\\Akutou_logo.png",		//選択アイコン(4人)
};

//***********************************
//プロトタイプ宣言
//***********************************
//初期化
void InitPlayModeSelectIcon(void);
//更新
void ModeSelect(void);
//描画
void DrawPlayModeSelectIcon(void);

//==================
//グローバル定義
//==================
LPDIRECT3DTEXTURE9 g_pTextureStage[MAX_TEX] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage = {};			//頂点バッファへのポインタ
D3DXCOLOR g_PaleColorSt;
D3DXCOLOR g_NormalColorSt;

PlayModeSelect g_PlayModeSelect;

//========================================================================
// モード選択の初期化処理
//========================================================================
void InitPlayModeSelect(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	for (int nCntTexture = 0; nCntTexture < MAX_TEX; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, c_apFilenameStage[nCntTexture], &g_pTextureStage[nCntTexture]);
	}

	//構造体の初期化
	g_PlayModeSelect.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PlayModeSelect.nType = 0;
	g_PlayModeSelect.CurrentModeNumber = 0;
	g_PlayModeSelect.bUse = true;

	//グローバル宣言の初期化
	g_PaleColorSt = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	g_NormalColorSt = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファの生成[0]
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_POLY,
								D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
								&g_pVtxBuffStage, NULL);
	//アイコンの初期化
	InitPlayModeSelectIcon();
}

//========================================================================
// モード選択の終了処理
//========================================================================
void UninitPlayModeSelect(void)
{
	//変数宣言
	int nCntStage;			//forカウント用

	for (nCntStage = 0; nCntStage < MAX_TEX; nCntStage++)
	{
		//テクスチャの破棄
		if (g_pTextureStage[nCntStage] != NULL)
		{
			g_pTextureStage[nCntStage]->Release();
			g_pTextureStage[nCntStage] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffStage != NULL)
	{
		g_pVtxBuffStage->Release();
		g_pVtxBuffStage = NULL;
	}
}

//========================================================================
// モード選択の更新処理
//========================================================================
void UpdatePlayModeSelect(void)
{
	//ステージ選択の関数
	ModeSelect();

	//デバッグ表示
	PrintDebugProc("選択 【←】【→】\n");
	PrintDebugProc("決定 【ENTER】\n");
	PrintDebugProc("戻る 【B】\n");
}

//========================================================================
// モード選択の描画処理
//========================================================================
void DrawPlayModeSelect(void)
{
	//プレイ人数の情報取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	if (PlayNumber.bUse == false)
	{
		//選択アイコン
		DrawPlayModeSelectIcon();
	}
}

//========================================================================
// モード選択アイコンの初期化処理
//========================================================================
void InitPlayModeSelectIcon(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStage = 0; nCntStage < NUM_PLAYMODE; nCntStage++)
	{
		g_PlayModeSelect.pos = D3DXVECTOR3(ICON_POS_X + BRANK_LENGTH * nCntStage, ICON_POS_Y, 0.0f);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x - ICON_SIZE_X, g_PlayModeSelect.pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x + ICON_SIZE_X, g_PlayModeSelect.pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x - ICON_SIZE_X, g_PlayModeSelect.pos.y + ICON_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x + ICON_SIZE_X, g_PlayModeSelect.pos.y + ICON_SIZE_Y, 0.0f);

		//rhwの設定
		for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
		{
			pVtx[nCntrhw].rhw = 1.0f;
		}
		if (nCntStage == 0)
		{
			//頂点カラー(0.0f～1.0f内で設定)
			for (int nCntcol = 0; nCntcol < 4; nCntcol++)
			{
				pVtx[nCntcol].col = g_NormalColorSt;
			}
		}
		else
		{
			//頂点カラー(0.0f～1.0f内で設定)
			for (int nCntcol = 0; nCntcol < 4; nCntcol++)
			{
				pVtx[nCntcol].col = g_PaleColorSt;
			}
		}

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;					//頂点データを4つ分ずらす
	}

	//頂点バッファをアンロックする
	g_pVtxBuffStage->Unlock();
}

//========================================================================
// モード選択選択アイコンの描画処理
//========================================================================
void DrawPlayModeSelectIcon(void)
{
	//デバイスへのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStage, 0,
		sizeof(VERTEX_2D));			//頂点情報構造体のサイズ

	for (int nCntStage = 0; nCntStage < NUM_POLY; nCntStage++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureStage[nCntStage]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
			nCntStage * 4,			//描画する最初のインデックス
			2);						//プリミティブ(ポリゴン)数
	}
}

//========================================================================
// モード選択の選択処理
//========================================================================
void ModeSelect(void)
{
	//フェード情報の取得
	FADE pFade = GetFade();

	//プレイ人数の情報取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (pFade == FADE_NONE  && PlayNumber.bUse == false)
	{
		if (GetKeyboardTrigger(DIK_D) == true/* || GetGamePadTrigger(BUTTON_3, 0) == true*/)
		{
			//頂点バッファをロック
			g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += g_PlayModeSelect.CurrentModeNumber * 4;

			//頂点カラーの設定
			pVtx[0].col = g_PaleColorSt;
			pVtx[1].col = g_PaleColorSt;
			pVtx[2].col = g_PaleColorSt;
			pVtx[3].col = g_PaleColorSt;

			//頂点バッファをアンロックする
			g_pVtxBuffStage->Unlock();

			//現在地を先に
			g_PlayModeSelect.CurrentModeNumber = (g_PlayModeSelect.CurrentModeNumber + 1) % NUM_PLAYMODE;

			//頂点バッファをロック
			g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += g_PlayModeSelect.CurrentModeNumber * 4;

			//頂点カラーの設定
			pVtx[0].col = g_NormalColorSt;
			pVtx[1].col = g_NormalColorSt;
			pVtx[2].col = g_NormalColorSt;
			pVtx[3].col = g_NormalColorSt;

			//頂点バッファをアンロックする
			g_pVtxBuffStage->Unlock();
		}
		else if (GetKeyboardTrigger(DIK_A) == true/* || GetGamePadTrigger(BUTTON_2, 0) == true*/ && pFade == FADE_NONE)
		{
			//頂点バッファをロック
			g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += g_PlayModeSelect.CurrentModeNumber * 4;

			//頂点カラーの設定
			pVtx[0].col = g_PaleColorSt;
			pVtx[1].col = g_PaleColorSt;
			pVtx[2].col = g_PaleColorSt;
			pVtx[3].col = g_PaleColorSt;

			//頂点バッファをアンロックする
			g_pVtxBuffStage->Unlock();

			//現在地を前へ
			g_PlayModeSelect.CurrentModeNumber = (g_PlayModeSelect.CurrentModeNumber - 1 + NUM_PLAYMODE) % NUM_PLAYMODE;

			//頂点バッファをロック
			g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * g_PlayModeSelect.CurrentModeNumber;

			//頂点カラーの設定
			pVtx[0].col = g_NormalColorSt;
			pVtx[1].col = g_NormalColorSt;
			pVtx[2].col = g_NormalColorSt;
			pVtx[3].col = g_NormalColorSt;

			//頂点バッファをアンロックする
			g_pVtxBuffStage->Unlock();
		}

		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_START, 0) || GetGamepadTrigger(BUTTON_A, 0))
		{//決定キー(ENTERキー)が押された
			if (g_PlayModeSelect.CurrentModeNumber >= 0 && g_PlayModeSelect.CurrentModeNumber < NUM_PLAYMODE)
			{
				PlayNumber.CurrentSelectNumber = 4;			//プレイ人数に合わせるため

				SetFade(MODE_GAME);			//モードの設定(ゲーム画面に移行)
			}
		}
	}
}

//========================================================================
// モード選択情報の取得
//========================================================================
PlayModeSelect GetPlayModeSelect(void)
{
	return g_PlayModeSelect;
}