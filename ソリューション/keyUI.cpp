//========================================================================================
//
// 鍵のUIの処理[KeyUI.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "KeyUI.h"
#include "fade.h"
#include "keyUI.h"
#include "player.h"
#include "PlayNumberSelect.h"

//マクロ定義
#define MAX_KEY_TEX		(2)				//鍵のテクスチャ最大数

#define KEYUIPOS_X_1	(130.0f)			//鍵UIのX位置1
#define KEYUIPOS_Y_1	(50.0f)			//鍵UIのY位置1

#define KEYUIPOS_X_2	(780.0f)		//鍵UIのX位置2
#define KEYUIPOS_Y_2	(400.0f)		//鍵UIのY位置2

#define KEYUI_WIDTH		(30.0f)			//鍵UIの幅
#define KEYUI_HEIGHT	(20.0f)			//鍵UIの高さ
#define KEYUI_INTERVAL	(50.0f)			//鍵UI同士の間隔

//鍵UIの構造体
typedef struct
{
	D3DXVECTOR3 pos;  //鍵UIの位置
	int nKeyUI;  //鍵UIの数
	bool bUse;  //使われているかどうか
}KEYUI;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureKeyUI[MAX_KEY_TEX] = {};  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKeyUI = NULL; //頂点バッファへのポインタ
KEYUI g_anKeyUI[NUM_PLAYER];			//鍵UIの情報
int g_NumPlayerKeyUI;

//=============================
//  鍵UIの初期化
//=============================
void InitKeyUI(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//変数宣言
	int nCntKeyUI;

	//グローバル宣言の初期化
	g_NumPlayerKeyUI = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\NoCardKey.jpg",
		&g_pTextureKeyUI[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\CardKey.jpg",
		&g_pTextureKeyUI[1]);

	//鍵UIの情報を初期化
	for (nCntKeyUI = 0; nCntKeyUI < PlayNumber.CurrentSelectNumber; nCntKeyUI++)
	{
		if (nCntKeyUI == 0)
		{
			g_anKeyUI[nCntKeyUI].pos = D3DXVECTOR3(KEYUIPOS_X_1, KEYUIPOS_Y_1, 0.0f);  //1人目の位置を初期化
		}

		if (nCntKeyUI == 1)
		{
			g_anKeyUI[nCntKeyUI].pos = D3DXVECTOR3(KEYUIPOS_X_2, KEYUIPOS_Y_1, 0.0f);  //2人目の位置を初期化
		}

		if (nCntKeyUI == 2)
		{
			g_anKeyUI[nCntKeyUI].pos = D3DXVECTOR3(KEYUIPOS_X_1, KEYUIPOS_Y_2, 0.0f);  //3人目の位置を初期化
		}

		if (nCntKeyUI == 3)
		{
			g_anKeyUI[nCntKeyUI].pos = D3DXVECTOR3(KEYUIPOS_X_2, KEYUIPOS_Y_2, 0.0f);  //4人目の位置を初期化
		}
		g_anKeyUI[nCntKeyUI].nKeyUI = 3;		//鍵UIの値を初期化
		g_anKeyUI[nCntKeyUI].bUse = false;  //使っていないことに
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffKeyUI,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKeyUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_anKeyUI[nCnt].pos.x - KEYUI_WIDTH , g_anKeyUI[nCnt].pos.y - KEYUI_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_anKeyUI[nCnt].pos.x + KEYUI_WIDTH , g_anKeyUI[nCnt].pos.y - KEYUI_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_anKeyUI[nCnt].pos.x - KEYUI_WIDTH , g_anKeyUI[nCnt].pos.y + KEYUI_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_anKeyUI[nCnt].pos.x + KEYUI_WIDTH , g_anKeyUI[nCnt].pos.y + KEYUI_HEIGHT, 0.0f);

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

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffKeyUI->Unlock();
}

//=====================
//鍵UIの終了処理
//=====================
void UninitKeyUI(void)
{
	for (int nCnt = 0; nCnt < MAX_KEY_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureKeyUI[nCnt] != NULL)
		{
			g_pTextureKeyUI[nCnt]->Release();
			g_pTextureKeyUI[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffKeyUI != NULL)
	{
		g_pVtxBuffKeyUI->Release();
		g_pVtxBuffKeyUI = NULL;
	}
}

//==========================
//鍵UIの更新処理
//=========================
void UpdateKeyUI(void)
{

}

//======================
//鍵UIの描画処理
//======================
void DrawKeyUI(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffKeyUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		if (g_anKeyUI[nCnt].bUse == false)
		{//鍵を取得していないとき
		 //テクスチャの設定
			pDevice->SetTexture(0, g_pTextureKeyUI[0]);
		}

		else
		{//鍵を取得しているとき
		 //テクスチャの設定
			pDevice->SetTexture(0, g_pTextureKeyUI[1]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//===================================
//鍵UIの設定処理
//===================================
void SetKeyUI(int nPlayer, bool SetKey)
{
	g_anKeyUI[nPlayer].bUse = SetKey;
}
