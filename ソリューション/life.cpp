//============================
//
//ライフ処理(life.cpp)
//Author:早川 友貴
//
//============================
//#include "enemy.h"
#include "Life.h"
#include "fade.h"
#include "life.h"
#include "player.h"

//マクロ定義
#define NUM_PLACE     (3)		//ライフの数
#define LIFEPOS_X     (30.0f)	//ライフのX位置
#define LIFEPOS_Y     (50.0f)	//ライフのY位置
#define LIFE_WIDTH    (20.0f)   //ライフの幅
#define LIFE_HEIGHT	  (20.0f)   //ライフの高さ
#define LIFE_INTERVAL (60.0f)	//ライフ同士の間隔

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL; //頂点バッファへのポインタ
D3DXVECTOR3 g_posLife;  //ライフの位置
int g_nLife;			//ライフの値

//=============================
//  ライフの初期化
//=============================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLife;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\LIFE.png",
		&g_pTextureLife);

	//ライフの情報を初期化
	for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
	{
		g_posLife = D3DXVECTOR3(LIFEPOS_X, LIFEPOS_Y, 0.0f);  //位置を初期化
	}

	g_nLife = 3;		//ライフの値を初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posLife.x - LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_posLife.y - LIFE_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posLife.x + LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_posLife.y - LIFE_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posLife.x - LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_posLife.y + LIFE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posLife.x + LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_posLife.y + LIFE_HEIGHT, 0.0f);

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
	FADE pFade;
	pFade = GetFade();
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLife;
	Player *pPlayer = GetPlayer();

		//デバイスの取得
		pDevice = GetDevice();

		VERTEX_2D *pVtx;    //頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;		//頂点データのポインタを4つ分進める
		}
		//頂点バッファをアンロックする
		g_pVtxBuffLife->Unlock();

		//プレイヤーの情報を取得
		g_nLife = pPlayer->nLife;

	//ライフの上限
	if (g_nLife == 0)
	{//0になったら
		g_nLife = pPlayer->nLife;

		/*pPlayer->state = PLAYERSTATE_DEATH;*/
	}

	if (pFade == FADE_NONE)
	{
		if (g_nLife == 0)
		{
			
		}
	}
}

//======================
//ライフの描画処理
//======================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntLife;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLife);

	for (nCntLife = 0; nCntLife < g_nLife; nCntLife++)
	{//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
	}
}
