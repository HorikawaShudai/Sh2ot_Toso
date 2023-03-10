#include "main.h"
#include "polygonBG.h"
#include "numberUI.h"
#include "game.h"

//マクロ定義
#define MAX_SSUI		(32)//PolygonBGの種類数
#define NUM_POLYUI		(5)	//PolygonBGの種類数

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTexturePolygonBG[NUM_POLYUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonBG = NULL;		//頂点バッファへのポインタ
PolygonBG g_PolygonBG[MAX_SSUI];

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
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\Damage00.jpg",
		&g_apTexturePolygonBG[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Damage01.png",
		&g_apTexturePolygonBG[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Damage02.jpg",
		&g_apTexturePolygonBG[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Damage03.jpg",
		&g_apTexturePolygonBG[3]);

	//UIの表示設定
	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		g_PolygonBG[nCntBG].bUse = false;
		g_PolygonBG[nCntBG].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
		g_PolygonBG[nCntBG].fWidth = 640.0f;
		g_PolygonBG[nCntBG].fHeight = 360.0f;
		g_PolygonBG[nCntBG].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
		g_PolygonBG[nCntBG].nLife = 0;
		g_PolygonBG[nCntBG].nType = 0;
		g_PolygonBG[nCntBG].KuroPolyA = 0.0f;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygonBG,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPolygonBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_PolygonBG[nCntBG].pos.x - g_PolygonBG[nCntBG].fWidth, g_PolygonBG[nCntBG].pos.y - g_PolygonBG[nCntBG].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_PolygonBG[nCntBG].pos.x + g_PolygonBG[nCntBG].fWidth, g_PolygonBG[nCntBG].pos.y - g_PolygonBG[nCntBG].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_PolygonBG[nCntBG].pos.x - g_PolygonBG[nCntBG].fWidth, g_PolygonBG[nCntBG].pos.y + g_PolygonBG[nCntBG].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_PolygonBG[nCntBG].pos.x + g_PolygonBG[nCntBG].fWidth, g_PolygonBG[nCntBG].pos.y + g_PolygonBG[nCntBG].fHeight, 0.0f);

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
	for (nCntBG = 0; nCntBG < NUM_POLYUI; nCntBG++)
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
	for (int nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		if (g_PolygonBG[nCntBG].bUse == true)
		{
			if (g_PolygonBG[nCntBG].nType == 4)
			{
				g_PolygonBG[nCntBG].KuroPolyA += 0.005f;
			}
			else
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
	}

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPolygonBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		if (g_PolygonBG[nCntBG].bUse == true)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_PolygonBG[nCntBG].pos.x - g_PolygonBG[nCntBG].fWidth, g_PolygonBG[nCntBG].pos.y - g_PolygonBG[nCntBG].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_PolygonBG[nCntBG].pos.x + g_PolygonBG[nCntBG].fWidth, g_PolygonBG[nCntBG].pos.y - g_PolygonBG[nCntBG].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_PolygonBG[nCntBG].pos.x - g_PolygonBG[nCntBG].fWidth, g_PolygonBG[nCntBG].pos.y + g_PolygonBG[nCntBG].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_PolygonBG[nCntBG].pos.x + g_PolygonBG[nCntBG].fWidth, g_PolygonBG[nCntBG].pos.y + g_PolygonBG[nCntBG].fHeight, 0.0f);

			if (g_PolygonBG[nCntBG].nType == 4)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_PolygonBG[nCntBG].KuroPolyA);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_PolygonBG[nCntBG].KuroPolyA);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_PolygonBG[nCntBG].KuroPolyA);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_PolygonBG[nCntBG].KuroPolyA);
			}
			else
			{
				//頂点カラーの設定
				pVtx[0].col = g_PolygonBG[nCntBG].col;
				pVtx[1].col = g_PolygonBG[nCntBG].col;
				pVtx[2].col = g_PolygonBG[nCntBG].col;
				pVtx[3].col = g_PolygonBG[nCntBG].col;
			}
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

	for (nCntBG = 0; nCntBG < NUM_POLYUI; nCntBG++)
	{
		if (g_PolygonBG[nCntBG].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTexturePolygonBG[g_PolygonBG[nCntBG].nType]);

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
void SetPolygonBG(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR Col, int nLife,int nType)
{
	for (int nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		if (g_PolygonBG[nCntBG].bUse == false)
		{
			g_PolygonBG[nCntBG].pos = pos;
			g_PolygonBG[nCntBG].fWidth = fWidth;
			g_PolygonBG[nCntBG].fHeight = fHeight;
			g_PolygonBG[nCntBG].bUse = true;
			g_PolygonBG[nCntBG].col = Col;
			g_PolygonBG[nCntBG].nLife = nLife;
			g_PolygonBG[nCntBG].nType = nType;
			break;
		}
	}
}