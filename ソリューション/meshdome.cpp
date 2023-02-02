//========================================================================================
//
// ドーム状のポリゴンの描画[meshcydome.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "meshdome.h"

#define WAIGHT_SIZE (17)			//横の頂点数(９or１７or３３)偶数だとバグる
#define HEIGHT_SIZE (7)				//縦の頂点数
#define WAIGHT_CENTER (0.5f)		//横の原点(0.0f～1.0f)
#define HEIGHT_CENTER (1.0f)		//縦の原点(0.0f～1.0f)
#define CYLINDER_HEIGHT (150.0f)	//壁一枚の高さ
#define CYLINDER_RADIUS (2800.0f)	//円の半径
#define MAX_TEX  (2)				//テクスチャの最大数

typedef enum
{
	TEX_CLOUD = 0,
	TEX_BLACK,
	TEX_MAX,
}MODE_TEX;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMeshDome[MAX_TEX];				//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshDome;			//頂点バッファのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshDome;			//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshDome;							//位置
D3DXVECTOR3 g_rotMeshDome;							//向き
D3DXMATRIX g_mtxWorldMeshDome;						//ワールドマトリックス
MODE_TEX g_TexMode;  //テクスチャの情報

//====================================================================
//メッシュドームの初期化処理
//====================================================================
void InitMeshDome(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rain_cloud2.jpeg",
		&g_pTextureMeshDome[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title_bg.jpg",
		&g_pTextureMeshDome[1]);

	g_posMeshDome = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshDome = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_TexMode = TEX_CLOUD; //テクスチャの情報を初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * HEIGHT_SIZE * WAIGHT_SIZE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshDome,
		NULL);

	VERTEX_3D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffMeshDome->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0, nData = 0, nCenterW = 0, nCenterH = 0, nHeight = 0; nCnt < HEIGHT_SIZE * WAIGHT_SIZE; nCnt++)
	{
		//横番号の代入
		nCenterW = nCnt % WAIGHT_SIZE;

		if (nCnt % WAIGHT_SIZE == 0 && nCnt != 0)
		{
			nHeight++;
		}

		//頂点座標の設定 
		pVtx[nCnt].pos.x = g_posMeshDome.x + sinf(D3DX_PI * (1.0f / ((WAIGHT_SIZE - 1) / 2)) * (nCnt - nHeight)) * cosf(D3DX_PI * (1.0f / ((HEIGHT_SIZE - 1) * 2)) * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		//pVtx[nCnt].pos.y = CYLINDER_HEIGHT * ((HEIGHT_SIZE - 1) - nHeight);

		//pVtx[nCnt].pos.y = sinf(D3DX_PI * 0.0625f * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		pVtx[nCnt].pos.y = sinf(D3DX_PI * (1.0f / ((HEIGHT_SIZE - 1) * 2)) * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		pVtx[nCnt].pos.z = g_posMeshDome.z + cosf(D3DX_PI * (1.0f / ((WAIGHT_SIZE - 1) / 2)) * (nCnt - nHeight)) * cosf(D3DX_PI * (1.0f / ((HEIGHT_SIZE - 1) * 2)) * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		//法線ベクトルの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//頂点カラーの設定
		pVtx[nCnt].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

		////テクスチャ座標の設定
		//if (nCenterW % 2 == 0)
		//{
		//	pVtx[nCnt].tex.x = 0.0f;
		//}
		//else
		//{
		//	pVtx[nCnt].tex.x = 1.0f;
		//}
		//if (nCenterH % 2 == 0)
		//{
		//	pVtx[nCnt].tex.y = 0.0f;
		//}
		//else
		//{
		//	pVtx[nCnt].tex.y = 1.0f;
		//}

		//テクスチャ座標の設定
		pVtx[nCnt].tex.x = 1.0f / (WAIGHT_SIZE - 1) * nCenterW;
		pVtx[nCnt].tex.y = 1.0f / (HEIGHT_SIZE - 1) * nCenterH;


		if ((nCnt - nCenterH) % (WAIGHT_SIZE - 1) == 0 && nCnt != 0 && nCnt != (WAIGHT_SIZE - 1) * nCenterH + nCenterH)
		{//縦番号の代入
			nCenterH++;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshDome->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * (WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshDome,
		NULL);

	WORD *pIdx;	//インデックス情報へのポインタ

				//インデックスバッファをロックし、頂点番号データへのポインタを所得
	g_pIndxBuffMeshDome->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0, nOri = 0; nCnt < (WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)) / 2; nCnt++)
	{
		if ((nCnt - nOri) % WAIGHT_SIZE == 0 && nCnt != 0 && nCnt != WAIGHT_SIZE * nOri + nOri)
		{
			pIdx[nCnt * 2] = nCnt - 1 - nOri;			//偶数
			pIdx[nCnt * 2 + 1] = nCnt + WAIGHT_SIZE - nOri;		//奇数

			nOri++;
		}
		else
		{
			pIdx[nCnt * 2] = nCnt + WAIGHT_SIZE - nOri;	//偶数
			pIdx[nCnt * 2 + 1] = nCnt - nOri;		//奇数
		}
	}

	//インデックスバッファをアンロックする
	g_pIndxBuffMeshDome->Unlock();
}

//====================================================================
//メッシュドームの終了処理
//====================================================================
void UninitMeshDome(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureMeshDome[nCnt] != NULL)
		{
			g_pTextureMeshDome[nCnt]->Release();
			g_pTextureMeshDome[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshDome != NULL)
	{
		g_pVtxBuffMeshDome->Release();
		g_pVtxBuffMeshDome = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIndxBuffMeshDome != NULL)
	{
		g_pIndxBuffMeshDome->Release();
		g_pIndxBuffMeshDome = NULL;
	}
}

//====================================================================
//メッシュドームの更新処理
//====================================================================
void UpdateMeshDome(void)
{

}

//====================================================================
//メッシュドームの描画処理
//====================================================================
void DrawMeshDome(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshDome);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshDome.y, g_rotMeshDome.x, g_rotMeshDome.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshDome, &g_mtxWorldMeshDome, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshDome.x, g_posMeshDome.y, g_posMeshDome.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshDome, &g_mtxWorldMeshDome, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshDome);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshDome, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIndxBuffMeshDome);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	switch (g_TexMode)
	{
	case TEX_CLOUD:

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMeshDome[0]);

		break;

	case TEX_BLACK:

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMeshDome[1]);

		break;
	}
	
	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		0,//用意した頂点の数
		0,
		(WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)) - 2);//描画するプリミティブの数
}

//==============================
//テクスチャを変える処理
//==============================
void ChangeMeshDome(void)
{
	g_TexMode = TEX_BLACK;
}