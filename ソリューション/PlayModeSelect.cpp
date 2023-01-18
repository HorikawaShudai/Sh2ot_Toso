//======================================================================================
//
// ステージ処理[stage.cpp]
// Author:小笠原　彪
//
//======================================================================================
#include <stdio.h>
#include "PlayModeSelect.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "debugproc.h"

//***********************************
//マクロ定義
//***********************************
#define MAX_TEX			(5)				//テクスチャの最大数
#define NUM_POLY		(NUM_PLAYMODE)	//ポリゴンの数
#define MAX_BUFF		(2)				//バッファの最大数

//***********************************
//テクスチャファイル名
//***********************************
const char *c_apFilenameStage[MAX_TEX] =
{
	"Data\\TEXTURE\\PLAYMODE\\PlayMode00.png",			//タイトル背景
	"data\\TEXTURE\\PLAYMODE\\PlayMode00.png",		//選択アイコン(1人)
	"data\\TEXTURE\\PLAYMODE\\PlayMode01.png",		//選択アイコン(2人)
	"data\\TEXTURE\\PLAYMODE\\PlayMode02.png",		//選択アイコン(3人)
	"data\\TEXTURE\\PLAYMODE\\PlayMode03.png",		//選択アイコン(4人)
};

//***********************************
//プロトタイプ宣言
//***********************************
//初期化
void InitPlaySelectBg(void);
void InitPlaySelectIcon(void);
//更新
void PlayModeSelect(void);
//描画
void DrawStageBg(void);
void DrawIcon(void);

//==================
//グローバル定義
//==================
LPDIRECT3DTEXTURE9 g_pTextureStage[MAX_TEX] = {};				//テクスチャへの
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage[MAX_BUFF] = {};			//頂点バッファへの
D3DXCOLOR g_PaleColorSt;
D3DXCOLOR g_NormalColorSt;
PlayerModeSelect g_PlayModeSelect;

//========================================================================
// モード選択の初期化処理
//========================================================================
void InitPlayerModeSelect(void)
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
	g_PlayModeSelect.CurrentSelectNumber = 0;
	g_PlayModeSelect.bStage = false;

	//グローバル宣言の初期化
	g_PaleColorSt = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	g_NormalColorSt = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 
								D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
								&g_pVtxBuffStage[0], NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYMODE, 
								D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
								&g_pVtxBuffStage[1], NULL);

	InitPlaySelectBg();

	InitPlaySelectIcon();
}

//========================================================================
// モード選択背景の初期化処理
//========================================================================
void InitPlaySelectBg(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStage[0]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
	{
		pVtx[nCntrhw].rhw = 1.0f;
	}
	//頂点カラー(0.0f～1.0f内で設定)
	for (int nCntcol = 0; nCntcol < 4; nCntcol++)
	{
		pVtx[nCntcol].col = g_NormalColorSt;
	}

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffStage[0]->Unlock();
}

//========================================================================
// モード選択アイコンの初期化処理
//========================================================================
void InitPlaySelectIcon(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStage[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStage = 0; nCntStage < NUM_PLAYMODE; nCntStage++)
	{
		if (nCntStage == 0)
		{
			g_PlayModeSelect.pos = D3DXVECTOR3(300.0f, 400.0f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x - 50.0f, g_PlayModeSelect.pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x + 50.0f, g_PlayModeSelect.pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x - 50.0f, g_PlayModeSelect.pos.y + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x + 50.0f, g_PlayModeSelect.pos.y + 100.0f, 0.0f);
			//rhwの設定
			for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
			{
				pVtx[nCntrhw].rhw = 1.0f;
			}
			//頂点カラー(0.0f～1.0f内で設定)
			for (int nCntcol = 0; nCntcol < 4; nCntcol++)
			{
				pVtx[nCntcol].col = g_NormalColorSt;
			}
			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;					//頂点データを4つ分ずらす
		}
		else if (nCntStage < 5)
		{
			g_PlayModeSelect.pos = D3DXVECTOR3(300.0f + 170.0f * nCntStage, 400.0f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x - 50.0f, g_PlayModeSelect.pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x + 50.0f, g_PlayModeSelect.pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x - 50.0f, g_PlayModeSelect.pos.y + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x + 50.0f, g_PlayModeSelect.pos.y + 100.0f, 0.0f);
			//rhwの設定
			for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
			{
				pVtx[nCntrhw].rhw = 1.0f;
			}
			//頂点カラー(0.0f～1.0f内で設定)
			for (int nCntcol = 0; nCntcol < 4; nCntcol++)
			{
				pVtx[nCntcol].col = g_PaleColorSt;
			}
			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;					//頂点データを4つ分ずらす
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffStage[1]->Unlock();

}

//========================================================================
// モード選択の終了処理
//========================================================================
void UninitPlayerModeSelect(void)
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
	for (nCntStage = 0; nCntStage < MAX_BUFF; nCntStage++)
	{
		//頂点バッファの破棄
		if (g_pVtxBuffStage[nCntStage] != NULL)
		{
			g_pVtxBuffStage[nCntStage]->Release();
			g_pVtxBuffStage[nCntStage] = NULL;
		}
	}
}

//========================================================================
// モード選択の更新処理
//========================================================================
void UpdatePlayerModeSelect(void)
{
	//ステージ選択の関数
	PlayModeSelect();

	//デバッグ表示
	PrintDebugProc("選択 【←】【→】\n");
	PrintDebugProc("決定 【ENTER】\n");
	PrintDebugProc("戻る 【B】\n");
}

//========================================================================
// モード選択の描画処理
//========================================================================
void DrawPlayerModeSelect(void)
{
	//モードセレクトの背景
	DrawStageBg();

	//選択アイコン
	DrawIcon();
}

//========================================================================
// モード選択背景の描画処理
//========================================================================
void DrawStageBg(void)
{
	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStage[0], 0,
		sizeof(VERTEX_2D));			//頂点情報構造体のサイズ

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureStage[0]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
		0,						//描画する最初のインデックス
		2);						//プリミティブ(ポリゴン)数
}

//========================================================================
// モード選択選択アイコンの描画処理
//========================================================================
void DrawIcon(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStage[1], 0,
		sizeof(VERTEX_2D));			//頂点情報構造体のサイズ

	for (int nCntStage = 0; nCntStage < NUM_POLY; nCntStage++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureStage[nCntStage + 1]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
			nCntStage * 4,			//描画する最初のインデックス
			2);						//プリミティブ(ポリゴン)数
	}
}

//========================================================================
// モード選択の選択処理
//========================================================================
void PlayModeSelect(void)
{
	//フェード情報の取得
	FADE pFade = GetFade();

	//頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (GetKeyboardTrigger(DIK_D) == true/* || GetGamePadTrigger(BUTTON_3, 0) == true*/ && pFade == FADE_NONE)
	{
		//頂点バッファをロック
		g_pVtxBuffStage[1]->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += g_PlayModeSelect.CurrentSelectNumber * 4;

		//頂点カラーの設定
		pVtx[0].col = g_PaleColorSt;
		pVtx[1].col = g_PaleColorSt;
		pVtx[2].col = g_PaleColorSt;
		pVtx[3].col = g_PaleColorSt;

		//頂点バッファをアンロックする
		g_pVtxBuffStage[1]->Unlock();

		//現在地を先に
		g_PlayModeSelect.CurrentSelectNumber = (g_PlayModeSelect.CurrentSelectNumber + 1) % NUM_PLAYMODE;

		//頂点バッファをロック
		g_pVtxBuffStage[1]->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += g_PlayModeSelect.CurrentSelectNumber * 4;

		//頂点カラーの設定
		pVtx[0].col = g_NormalColorSt;
		pVtx[1].col = g_NormalColorSt;
		pVtx[2].col = g_NormalColorSt;
		pVtx[3].col = g_NormalColorSt;

		//頂点バッファをアンロックする
		g_pVtxBuffStage[1]->Unlock();
	}
	else if (GetKeyboardTrigger(DIK_A) == true/* || GetGamePadTrigger(BUTTON_2, 0) == true*/ && pFade == FADE_NONE)
	{
		//頂点バッファをロック
		g_pVtxBuffStage[1]->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += g_PlayModeSelect.CurrentSelectNumber * 4;

		//頂点カラーの設定
		pVtx[0].col = g_PaleColorSt;
		pVtx[1].col = g_PaleColorSt;
		pVtx[2].col = g_PaleColorSt;
		pVtx[3].col = g_PaleColorSt;

		//頂点バッファをアンロックする
		g_pVtxBuffStage[1]->Unlock();

		//現在地を前へ
		g_PlayModeSelect.CurrentSelectNumber = (g_PlayModeSelect.CurrentSelectNumber - 1 + NUM_PLAYMODE) % NUM_PLAYMODE;

		//頂点バッファをロック
		g_pVtxBuffStage[1]->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * g_PlayModeSelect.CurrentSelectNumber;

		//頂点カラーの設定
		pVtx[0].col = g_NormalColorSt;
		pVtx[1].col = g_NormalColorSt;
		pVtx[2].col = g_NormalColorSt;
		pVtx[3].col = g_NormalColorSt;

		//頂点バッファをアンロックする
		g_pVtxBuffStage[1]->Unlock();
	}

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(BUTTON_START, 0) || GetGamepadPress(BUTTON_A, 0))
		{//決定キー(ENTERキー)が押された
			if (g_PlayModeSelect.CurrentSelectNumber >= 0 && g_PlayModeSelect.CurrentSelectNumber < NUM_PLAYMODE)
			{
				SetFade(MODE_GAME);			//モードの設定(ゲーム画面に移行)
			}
		}
		else if (GetKeyboardTrigger(DIK_B) == true/* || GetGamePadTrigger(BUTTON_B, 0) == true*/ && pFade == FADE_NONE)
		{//キー(B)が押された
			SetFade(MODE_TITLE);				//モードの設定(タイトル画面に移行)
		}
	}
}

//========================================================================
// モード選択情報の取得
//========================================================================
PlayerModeSelect GetPlayerModeSelect(void)
{
	return g_PlayModeSelect;
}