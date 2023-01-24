//============================
//
//ライフ処理(life.cpp)
//Author:早川 友貴
//
//============================
#include "Life.h"
#include "fade.h"
#include "life.h"
#include "player.h"
#include "PlayNumberSelect.h"

//マクロ定義
#define NUM_PLACE     (3)			//ライフの数
#define MAX_PLAYER    (NUM_PLAYER)	//プレイヤーの最大数

#define LIFEPOS_X_0     (30.0f)		//1人目ライフのX位置
#define LIFEPOS_Y_0     (50.0f)		//1人目ライフのY位置

#define LIFEPOS_X_1     (670.0f)	//2人目ライフのX位置
#define LIFEPOS_Y_1     (50.0f)		//2人目ライフのY位置

#define LIFEPOS_X_2     (30.0f)		//3人目ライフのX位置
#define LIFEPOS_Y_2     (400.0f)	//3人目ライフのY位置

#define LIFEPOS_X_3     (670.0f)	//4人目ライフのX位置
#define LIFEPOS_Y_3     (400.0f)	//4人目ライフのY位置

#define LIFE_WIDTH    (20.0f)		//ライフの幅
#define LIFE_HEIGHT	  (20.0f)		//ライフの高さ
#define LIFE_INTERVAL (50.0f)		//ライフ同士の間隔

//ライフの構造体
typedef struct
{
	D3DXVECTOR3 pos;  //ライフの位置
	int nLife;  //ライフの数
	bool bUse[NUM_PLACE];  //使われているかどうか
}LIFE;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL; //頂点バッファへのポインタ
LIFE g_anLife[MAX_PLAYER];			//ライフの情報
int g_NumPlayerLife;

//=============================
//  ライフの初期化
//=============================
void InitLife(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//変数宣言
	int nCntLife;

	//グローバル宣言の初期化
	g_NumPlayerLife = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\LIFE.png",
		&g_pTextureLife);

	//ライフの情報を初期化
	for (nCntLife = 0; nCntLife < PlayNumber.CurrentSelectNumber; nCntLife++)
	{
		for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
		{
		if (nCntLife == 0)
		{
			g_anLife[nCntLife].pos = D3DXVECTOR3(LIFEPOS_X_0, LIFEPOS_Y_0, 0.0f);  //1人目の位置を初期化
		}

		if (nCntLife == 1)
		{
			g_anLife[nCntLife].pos = D3DXVECTOR3(LIFEPOS_X_1, LIFEPOS_Y_1, 0.0f);  //2人目の位置を初期化
		}

		if (nCntLife == 2)
		{
			g_anLife[nCntLife].pos = D3DXVECTOR3(LIFEPOS_X_2, LIFEPOS_Y_2, 0.0f);  //3人目の位置を初期化
		}

		if (nCntLife == 3)
		{
			g_anLife[nCntLife].pos = D3DXVECTOR3(LIFEPOS_X_3, LIFEPOS_Y_3, 0.0f);  //4人目の位置を初期化
		}
			g_anLife[nCntLife].nLife = 3;		//ライフの値を初期化
			g_anLife[nCntLife].bUse[nCnt] = true;  //使っていないことに
		}
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE * MAX_PLAYER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_anLife[nCnt].pos.x - LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_anLife[nCnt].pos.y - LIFE_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_anLife[nCnt].pos.x + LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_anLife[nCnt].pos.y - LIFE_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_anLife[nCnt].pos.x - LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_anLife[nCnt].pos.y + LIFE_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_anLife[nCnt].pos.x + LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_anLife[nCnt].pos.y + LIFE_HEIGHT, 0.0f);

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
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

//=====================
//ライフの終了処理
//=====================
void UninitLife(void)
{
	//テクスチャの破棄
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//==========================
//ライフの更新処理
//=========================
void UpdateLife(void)
{

}

//======================
//ライフの描画処理
//======================
void DrawLife(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//変数宣言
	int nCount = 0;
	int nCntLife;

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLife);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber + 1; nCnt++)
	{
		for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
		{
			if (g_anLife[nCnt].bUse[nCntLife] == true)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
			}
			nCount++;
		}
	}
}

//===================================
//ライフの設定処理
//===================================
void SetLife(int nLife,int nPlayer)
{
	g_anLife[nPlayer].bUse[nLife] = false;
}

