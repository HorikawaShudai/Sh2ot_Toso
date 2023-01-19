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
#define NUM_PLACE     (3)			//ライフの数
#define MAX_PLAYER    (4)			//プレイヤーの最大数

#define LIFEPOS_X_0     (30.0f)		//1人目ライフのX位置
#define LIFEPOS_Y_0     (50.0f)		//1人目ライフのY位置

#define LIFEPOS_X_1     (600.0f)	//2人目ライフのX位置
#define LIFEPOS_Y_1     (50.0f)		//2人目ライフのY位置

#define LIFEPOS_X_2     (30.0f)		//3人目ライフのX位置
#define LIFEPOS_Y_2     (400.0f)	//3人目ライフのY位置

#define LIFEPOS_X_3     (600.0f)	//4人目ライフのX位置
#define LIFEPOS_Y_3     (400.0f)	//4人目ライフのY位置

#define LIFE_WIDTH    (20.0f)		//ライフの幅
#define LIFE_HEIGHT	  (20.0f)		//ライフの高さ
#define LIFE_INTERVAL (60.0f)		//ライフ同士の間隔

//ライフの構造体
typedef struct
{
	D3DXVECTOR3 pos;  //ライフの位置
	int nLife;  //ライフの数
	bool bUse;  //使われているかどうか
}LIFE;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL; //頂点バッファへのポインタ
LIFE g_anLife[MAX_PLAYER];			//ライフの情報

//=============================
//  ライフの初期化
//=============================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPlayer;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\LIFE.png",
		&g_pTextureLife);

	//ライフの情報を初期化
	for (nCntPlayer = 0; nCntPlayer < NUM_PLACE; nCntPlayer++)
	{
		g_anLife[nCntPlayer].pos = D3DXVECTOR3(LIFEPOS_X_0, LIFEPOS_Y_0, 0.0f);
		g_anLife[nCntPlayer].nLife = 3;		//ライフの値を初期化
		g_anLife[nCntPlayer].bUse = true;  //使っていないことに
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

	for (nCntPlayer = 0; nCntPlayer < NUM_PLACE; nCntPlayer++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_anLife[nCntPlayer].pos.x - LIFE_WIDTH + (nCntPlayer * LIFE_INTERVAL), g_anLife[nCntPlayer].pos.y - LIFE_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_anLife[nCntPlayer].pos.x + LIFE_WIDTH + (nCntPlayer * LIFE_INTERVAL), g_anLife[nCntPlayer].pos.y - LIFE_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_anLife[nCntPlayer].pos.x - LIFE_WIDTH + (nCntPlayer * LIFE_INTERVAL), g_anLife[nCntPlayer].pos.y + LIFE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_anLife[nCntPlayer].pos.x + LIFE_WIDTH + (nCntPlayer * LIFE_INTERVAL), g_anLife[nCntPlayer].pos.y + LIFE_HEIGHT, 0.0f);

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
	int nCntPlayer;
	Player *pPlayer = GetPlayer();

		//デバイスの取得
		pDevice = GetDevice();

		VERTEX_2D *pVtx;    //頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntPlayer = 0; nCntPlayer < NUM_PLACE; nCntPlayer++)
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
		g_anLife[nCntPlayer].nLife = pPlayer->nLife;

	//ライフの上限
	if (g_anLife[nCntPlayer].nLife == 0)
	{//0になったら
		g_anLife[nCntPlayer].nLife = pPlayer->nLife;

		/*pPlayer->state = PLAYERSTATE_DEATH;*/
	}

	if (pFade == FADE_NONE)
	{
		if (g_anLife[nCntPlayer].nLife == 0)
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

	int nCntPlayer;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLife);

	for (nCntPlayer = 0; nCntPlayer < g_anLife[nCntPlayer].nLife; nCntPlayer++)
	{//ポリゴンの描画

		if (g_anLife[nCntPlayer].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlayer * 4, 2);
		}
	}
}

//===================================
//ライフの設定処理
//===================================
void SetLife(int nLife,int nPlayer)
{
	g_anLife[nPlayer].nLife = nLife;
}

