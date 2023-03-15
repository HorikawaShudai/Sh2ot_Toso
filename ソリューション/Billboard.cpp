//====================================================================
//
//ビルボード表示処理
//Auther:堀川萩大
//
//====================================================================
#include "Billboard.h"
#include "Input.h"

//マクロ定義
#define MAX_RAIN	(400)	//雨の最大数
#define RAIN_HEIGHT	(10.0f)	//雨の高さ
#define RAIN_WIDTH	(0.2f)	//雨の幅

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMoon = NULL;			//月の頂点バッファのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRain = NULL;			//雨の頂点バッファのポインタ
D3DXMATRIX g_mtxWorldBillboard;							//ビルボードのワールドマトリックス
MOON g_Moon;											//月の構造体
RAIN g_Rain[MAX_RAIN];									//雨の構造体
bool g_bRain;

//プロトタイプ宣言
void InitMoon(void);
void InitRain(void);
void UpdateMoon(void);
void UpdateRain(void);
void DrawMoon(void);
void DrawRain(void);
void SetRain(void);

//====================================================
//ビルボードの初期化処理
//====================================================
void InitBillboard(void)
{
	InitMoon();
	InitRain();
}
//====================================================
//ビルボードの終了処理
//====================================================
void UninitBillboard(void)
{
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
	if (g_pVtxBuffMoon != NULL)
	{
		g_pVtxBuffMoon->Release();
		g_pVtxBuffMoon = NULL;
	}
	if (g_pVtxBuffRain != NULL)
	{
		g_pVtxBuffRain->Release();
		g_pVtxBuffRain = NULL;
	}
}

//====================================================
//ビルボードの更新処理
//====================================================
void UpdateBillboard(void)
{
	UpdateMoon();
	UpdateRain();
}

//====================================================
//ビルボードの描画処理
//====================================================
void DrawBillboard(void)
{
	DrawMoon();
	DrawRain();
}

//====================================================
//月の初期化処理
//====================================================
void InitMoon(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Moon.pos = D3DXVECTOR3(1400.0f, 1400.0f, 1300.0f);
	g_Moon.bUse = false;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMoon,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMoon->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\Red_moon.png",
		&g_pTextureBillboard);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-100.0f, +100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+100.0f, +100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+100.0f, -100.0f, 0.0f);

	//norの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffMoon->Unlock();
}


//====================================================
//月の更新処理
//====================================================
void UpdateMoon(void)
{
}

//====================================================
//月の描画処理
//====================================================
void DrawMoon(void)
{
	if (g_Moon.bUse == true)
	{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxTrans;	//計算用マトリックス
		D3DXMATRIX mtxView;		//ビューマトリックスの取得用

		//Zテストを有効にする
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldBillboard);

		//ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面に向ける
		D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);
		g_mtxWorldBillboard._41 = 0.0f;
		g_mtxWorldBillboard._42 = 0.0f;
		g_mtxWorldBillboard._43 = 0.0f;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Moon.pos.x, g_Moon.pos.y, g_Moon.pos.z);
		D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffMoon, 0, sizeof(VERTEX_3D));

		pDevice->SetFVF(FVF_VERTEX_3D);


		pDevice->SetTexture(0, g_pTextureBillboard);

		//ビルボード
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//Zテストを有効にする
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}

//====================================================
//雨の初期化処理
//====================================================
void InitRain(void)
{

	g_bRain = true;

	//構造体の初期化
	for (int nCnt = 0; nCnt < MAX_RAIN; nCnt++)
	{
		g_Rain[nCnt].bUse = false;
		g_Rain[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Rain[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_RAIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRain,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffRain->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_RAIN; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-RAIN_WIDTH, +RAIN_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+RAIN_WIDTH, +RAIN_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-RAIN_WIDTH, -RAIN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+RAIN_WIDTH, -RAIN_HEIGHT, 0.0f);

		//norの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRain->Unlock();
}
//================================================================
//雨の更新処理
//================================================================
void UpdateRain(void)
{
	if (g_bRain == true)
	{
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();

		for (int nRain = 0; nRain < MAX_RAIN; nRain++)
		{
			if (g_Rain[nRain].bUse == true)
			{
				g_Rain[nRain].pos += g_Rain[nRain].move;

				if (g_Rain[nRain].pos.y < 0.0f)
				{
					g_Rain[nRain].bUse = false;
				}
			}
		}
	}
}

//====================================================
//雨の描画処理
//====================================================
void DrawRain(void)
{
	if (g_bRain == true)
	{
		for (int nCnt = 0; nCnt < MAX_RAIN; nCnt++)
		{
			if (g_Rain[nCnt].bUse == true)
			{
				//デバイスの取得
				LPDIRECT3DDEVICE9 pDevice = GetDevice();

				D3DXMATRIX mtxTrans;	//計算用マトリックス
				D3DXMATRIX mtxView;		//ビューマトリックスの取得用

				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_mtxWorldBillboard);

				//ビューマトリックスを取得
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				//ポリゴンをカメラに対して正面に向ける
				D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);
				g_mtxWorldBillboard._41 = 0.0f;
				g_mtxWorldBillboard._42 = 0.0f;
				g_mtxWorldBillboard._43 = 0.0f;

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_Rain[nCnt].pos.x, g_Rain[nCnt].pos.y, g_Rain[nCnt].pos.z);
				D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

				//頂点バッファをデータストリームに設定
				pDevice->SetStreamSource(0, g_pVtxBuffRain, 0, sizeof(VERTEX_3D));

				pDevice->SetFVF(FVF_VERTEX_3D);


				pDevice->SetTexture(0, NULL);

				//ビルボード
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
		}
	}
}

//====================================================
//雨の設定処理
//====================================================
void SetRain(void)
{
	int randPosX;			//rand用の変数
	int randPosZ;			//rand用の変数
	int randMove;			//rand用の変数

	for (int nCnt = 0; nCnt < MAX_RAIN; nCnt++)
	{
		if (g_Rain[nCnt].bUse == false)
		{
			randPosX = rand() % 601;
			randPosZ = rand() % 501;
			randMove = rand() % 11;

			g_Rain[nCnt].pos = D3DXVECTOR3((float)randPosX - 50.0f, 250.0f, (float)randPosZ + 50.0f);
			g_Rain[nCnt].move = D3DXVECTOR3(0.0f, -15.0f + (float)-randMove, 0.0f);
			g_Rain[nCnt].bUse = true;
			break;
		}
	}
}

//=========================================================================
//雨の表示取得処理
//=========================================================================
bool GetbRain(void)
{
	return g_bRain;
}

//=========================================================================
//ビルボードの表示設定
//=========================================================================
void SetBoolBillboard(bool bRain, bool bMoon)
{
	g_bRain = bRain;
	g_Moon.bUse = bMoon;
}