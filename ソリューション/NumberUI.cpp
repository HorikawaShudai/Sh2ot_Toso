//========================================================================================
//
// 数字のテクスチャを呼び出す処理[NumberUI.cpp]
// Author: 坂本　翔唯
//
//========================================================================================

#include "main.h"
#include "numberUI.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "stage.h"



//マクロ定義
#define NUMBER_MAX		(128)	//数字の最大数
#define NUMBER_NUM		(2)	//数字の種類数

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureNumberUI[NUMBER_NUM] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNumberUI = NULL;		//頂点バッファへのポインタ
NumberUI g_NumberUI[NUMBER_MAX];

//====================================================================
//タイトル画面の初期化処理
//====================================================================
void InitNumberUI(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	int nCntNUMBER;

	//デバイスの所得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number00.png",
		&g_apTextureNumberUI[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number00.png",
		&g_apTextureNumberUI[1]);

	//各種変数の初期化
	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_MAX; nCntNUMBER++)
	{
		g_NumberUI[nCntNUMBER].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_NumberUI[nCntNUMBER].nNumberUI = 0;
		g_NumberUI[nCntNUMBER].nType = 0;
		g_NumberUI[nCntNUMBER].Width = 0.0f;
		g_NumberUI[nCntNUMBER].Height = 0.0f;
		g_NumberUI[nCntNUMBER].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUMBER_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNumberUI,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffNumberUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_MAX; nCntNUMBER++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffNumberUI->Unlock();
}

//====================================================================
//タイトルの終了処理
//====================================================================
void UninitNumberUI(void)
{
	////サウンドの停止
	//StopSound();

	int nCntNUMBER;
	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_NUM; nCntNUMBER++)
	{
		//テクスチャの破棄
		if (g_apTextureNumberUI[nCntNUMBER] != NULL)
		{
			g_apTextureNumberUI[nCntNUMBER]->Release();
			g_apTextureNumberUI[nCntNUMBER] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffNumberUI != NULL)
	{
		g_pVtxBuffNumberUI->Release();
		g_pVtxBuffNumberUI = NULL;
	}
}

//====================================================================
//タイトル画面の更新処理
//====================================================================
void UpdateNumberUI(void)
{
	int nCntNUMBER;

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffNumberUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_MAX; nCntNUMBER++)
	{
		if (g_NumberUI[nCntNUMBER].bUse == true)
		{
			pVtx[0].pos = D3DXVECTOR3(g_NumberUI[nCntNUMBER].pos.x - g_NumberUI[nCntNUMBER].Width, g_NumberUI[nCntNUMBER].pos.y - g_NumberUI[nCntNUMBER].Height, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_NumberUI[nCntNUMBER].pos.x + g_NumberUI[nCntNUMBER].Width, g_NumberUI[nCntNUMBER].pos.y - g_NumberUI[nCntNUMBER].Height, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_NumberUI[nCntNUMBER].pos.x - g_NumberUI[nCntNUMBER].Width, g_NumberUI[nCntNUMBER].pos.y + g_NumberUI[nCntNUMBER].Height, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_NumberUI[nCntNUMBER].pos.x + g_NumberUI[nCntNUMBER].Width, g_NumberUI[nCntNUMBER].pos.y + g_NumberUI[nCntNUMBER].Height, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_NumberUI[nCntNUMBER].nNumberUI * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + g_NumberUI[nCntNUMBER].nNumberUI * 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_NumberUI[nCntNUMBER].nNumberUI * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + g_NumberUI[nCntNUMBER].nNumberUI * 0.1f, 1.0f);
		}

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffNumberUI->Unlock();
}

//====================================================================
//タイトル画面の設定処理
//====================================================================
void SetNumberUI(D3DXVECTOR3 pos, float SizeX, float SizeY, int NumberUI, int nType)
{
	int nCntNUMBER;

	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_MAX; nCntNUMBER++)
	{
		if (g_NumberUI[nCntNUMBER].bUse == false)
		{
			g_NumberUI[nCntNUMBER].pos = pos;
			g_NumberUI[nCntNUMBER].Width = SizeX;
			g_NumberUI[nCntNUMBER].Height = SizeY;
			g_NumberUI[nCntNUMBER].nNumberUI = NumberUI;
			g_NumberUI[nCntNUMBER].nType = nType;
			g_NumberUI[nCntNUMBER].bUse = true;
			break;
		}
	}
}

//====================================================================
//タイトル画面の描画処理
//====================================================================
void DrawNumberUI(void)
{
	int nCntNUMBER;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffNumberUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_MAX; nCntNUMBER++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureNumberUI[g_NumberUI[nCntNUMBER].nType]);

		if (g_NumberUI[nCntNUMBER].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntNUMBER,						//プリミティブ(ポリゴン)数
				2);
		}
	}
}