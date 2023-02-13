#include "main.h"
#include "polygonBG.h"
#include "numberUI.h"
#include "game.h"

//マクロ定義
#define NUM_SSUI		(4)	//GAMEUIの種類数

#define POS_RANKING_BG_X		(640.0f)	//「」のX座標の位置
#define POS_RANKING_BG_Y		(360.0f)	//「」のY座標の位置
#define SIZE_RANKING_BG_X		(640.0f)	//「」の幅
#define SIZE_RANKING_BG_Y		(360.0f)	//「」の高さ

#define POS_SCORE_BG_X			(640.0f)	//「」のX座標の位置
#define POS_SCORE_BG_Y			(360.0f)	//「」のY座標の位置
#define SIZE_SCORE_BG_X			(640.0f)	//「」の幅
#define SIZE_SCORE_BG_Y			(360.0f)	//「」の高さ

#define POS_PERFECT_BG_X		(640.0f)	//「」のX座標の位置
#define POS_PERFECT_BG_Y		(360.0f)	//「」のY座標の位置
#define SIZE_PERFECT_BG_X		(640.0f)	//「」の幅
#define SIZE_PERFECT_BG_Y		(360.0f)	//「」の高さ

#define POS_ALLPERFECT_BG_X		(640.0f)	//「」のX座標の位置
#define POS_ALLPERFECT_BG_Y		(360.0f)	//「」のY座標の位置
#define SIZE_ALLPERFECT_BG_X	(640.0f)	//「」の幅
#define SIZE_ALLPERFECT_BG_Y	(360.0f)	//「」の高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTexturePolygonBG[NUM_SSUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonBG = NULL;		//頂点バッファへのポインタ
PolygonBG g_PolygonBG[NUM_SSUI];

//====================================================================
//タイトル画面の初期化処理
//====================================================================
void InitPolygonBG(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\Damage00.jpg",
	//	&g_apTexturePolygonBG[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Damage00.jpg",
		&g_apTexturePolygonBG[1]);

	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\Damage00.jpg",
	//	&g_apTexturePolygonBG[2]);

	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\Damage00.jpg",
	//	&g_apTexturePolygonBG[3]);

	//UIの表示設定
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		g_PolygonBG[nCntBG].bUse = false;
		g_PolygonBG[nCntBG].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
		g_PolygonBG[nCntBG].nLife = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygonBG,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPolygonBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_RANKING_BG_X - SIZE_RANKING_BG_X, POS_RANKING_BG_Y - SIZE_RANKING_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_RANKING_BG_X + SIZE_RANKING_BG_X, POS_RANKING_BG_Y - SIZE_RANKING_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_RANKING_BG_X - SIZE_RANKING_BG_X, POS_RANKING_BG_Y + SIZE_RANKING_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_RANKING_BG_X + SIZE_RANKING_BG_X, POS_RANKING_BG_Y + SIZE_RANKING_BG_Y, 0.0f);
			break;

		case 1:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_SCORE_BG_X - SIZE_SCORE_BG_X, POS_SCORE_BG_Y - SIZE_SCORE_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_SCORE_BG_X + SIZE_SCORE_BG_X, POS_SCORE_BG_Y - SIZE_SCORE_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_SCORE_BG_X - SIZE_SCORE_BG_X, POS_SCORE_BG_Y + SIZE_SCORE_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_SCORE_BG_X + SIZE_SCORE_BG_X, POS_SCORE_BG_Y + SIZE_SCORE_BG_Y, 0.0f);
			break;

		case 2:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_PERFECT_BG_X - SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y - SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PERFECT_BG_X + SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y - SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PERFECT_BG_X - SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y + SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PERFECT_BG_X + SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y + SIZE_PERFECT_BG_Y, 0.0f);
			break;

		case 3:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X - SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y - SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X + SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y - SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X - SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y + SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X + SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y + SIZE_ALLPERFECT_BG_Y, 0.0f);
			break;
		}

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

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPolygonBG->Unlock();
}

//====================================================================
//タイトルの終了処理
//====================================================================
void UninitPolygonBG(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの破棄
		if (g_apTexturePolygonBG[nCntBG] != NULL)
		{
			g_apTexturePolygonBG[nCntBG]->Release();
			g_apTexturePolygonBG[nCntBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPolygonBG != NULL)
	{
		g_pVtxBuffPolygonBG->Release();
		g_pVtxBuffPolygonBG = NULL;
	}
}

//====================================================================
//タイトル画面の更新処理
//====================================================================
void UpdatePolygonBG(void)
{
	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		if (g_PolygonBG[nCntBG].bUse == true)
		{
			if (g_PolygonBG[nCntBG].nLife <= 0)
			{
				g_PolygonBG[nCntBG].bUse = false;
			}
			else
			{
				g_PolygonBG[nCntBG].nLife--;
			}
		}
	}

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPolygonBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		if (g_PolygonBG[nCntBG].bUse == true)
		{
			//頂点カラーの設定
			pVtx[0].col = g_PolygonBG[nCntBG].col;
			pVtx[1].col = g_PolygonBG[nCntBG].col;
			pVtx[2].col = g_PolygonBG[nCntBG].col;
			pVtx[3].col = g_PolygonBG[nCntBG].col;
		}

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPolygonBG->Unlock();
}

//====================================================================
//タイトル画面の描画処理
//====================================================================
void DrawPolygonBG(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePolygonBG[nCntBG]);

		if (g_PolygonBG[nCntBG].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntBG,						//プリミティブ(ポリゴン)数
				2);
		}
	}
}
//====================================================================
//ランキングUIの設定処理
//====================================================================
void SetPolygonBG(D3DXCOLOR Col, int nLife)
{
	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		if (g_PolygonBG[nCntBG].bUse == false)
		{
			g_PolygonBG[nCntBG].bUse = true;
			g_PolygonBG[nCntBG].col = Col;
			g_PolygonBG[nCntBG].nLife = nLife;
			break;
		}
	}
}