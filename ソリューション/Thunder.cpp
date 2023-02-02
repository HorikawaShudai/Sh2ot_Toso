//====================================================================
//
//雷の表示処理
//Auther:堀川萩大
//
//====================================================================
#include "Thunder.h"
#include "Billboard.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffThunder = NULL;		//雷の頂点バッファのポインタ
THUNDER g_Thunder;
D3DXMATRIX g_mtxWorldThunder;							//雷のワールドマトリックス

//====================================================
//雷の初期化処理
//====================================================
void InitThunder(void)
{
	g_Thunder.bUse = false;
	g_Thunder.nCnt = 0;
	g_Thunder.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Thunder.pos = D3DXVECTOR3(100.0f, +0.0f, 500.0f);


	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffThunder,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffThunder->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-1280.0f, +720.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+1280.0f, +720.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-1280.0f, -720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+1280.0f, -720.0f, 0.0f);

	//rhwの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(g_Thunder.col);
	pVtx[1].col = D3DXCOLOR(g_Thunder.col);
	pVtx[2].col = D3DXCOLOR(g_Thunder.col);
	pVtx[3].col = D3DXCOLOR(g_Thunder.col);

	//頂点バッファをアンロックする
	g_pVtxBuffThunder->Unlock();
}
//====================================================
//雷の終了処理
//====================================================
void UninitThunder(void)
{
	if (g_pVtxBuffThunder != NULL)
	{
		g_pVtxBuffThunder->Release();
		g_pVtxBuffThunder = NULL;
	}
}

//====================================================
//雷の更新処理
//====================================================
void UpdateThunder(void)
{
	if (g_Thunder.bUse == true)
	{
		g_Thunder.col.a -= 0.007f;
		if (g_Thunder.col.a < -0.0f)
		{
			g_Thunder.bUse = false;
		}
	}

	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffThunder->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(g_Thunder.col);
	pVtx[1].col = D3DXCOLOR(g_Thunder.col);
	pVtx[2].col = D3DXCOLOR(g_Thunder.col);
	pVtx[3].col = D3DXCOLOR(g_Thunder.col);

	//頂点バッファをアンロックする
	g_pVtxBuffThunder->Unlock();
}

//====================================================
//雷の描画処理
//====================================================
void DrawThunder(void)
{
	if (g_Thunder.bUse == true)
	{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxTrans;	//計算用マトリックス
		D3DXMATRIX mtxView;		//ビューマトリックスの取得用

								//Zテストを有効にする
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldThunder);

		//ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面に向ける
		D3DXMatrixInverse(&g_mtxWorldThunder, NULL, &mtxView);
		g_mtxWorldThunder._41 = 0.0f;
		g_mtxWorldThunder._42 = 0.0f;
		g_mtxWorldThunder._43 = 0.0f;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Thunder.pos.x, g_Thunder.pos.y, g_Thunder.pos.z);
		D3DXMatrixMultiply(&g_mtxWorldThunder, &g_mtxWorldThunder, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldThunder);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffThunder, 0, sizeof(VERTEX_3D));

		pDevice->SetFVF(FVF_VERTEX_3D);


		pDevice->SetTexture(0, NULL);

		//雷
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//Zテストを有効にする
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}

void SetThunder(void)
{
	g_Thunder.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Thunder.bUse = true;
}