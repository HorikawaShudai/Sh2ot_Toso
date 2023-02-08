//========================================================================================
//
// 壁のポリゴンの描画[meshcywall.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "meshwall.h"

#define WAIGHT_SIZE (10)		//横の頂点数
#define HEIGHT_SIZE (5)			//縦の頂点数
#define WAIGHT_CENTER (0.5f)	//横の原点(0.0f～1.0f)
#define HEIGHT_CENTER (1.0f)	//縦の原点(0.0f～1.0f)
#define FIELD_SIZE (10.0f)		//壁一枚の大きさ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMeshWall;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall;		//頂点バッファのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshWall;		//インデックスバッファへのポインタ

MeshWall g_aMeshWall[MAX_MESHWALL];
D3DXVECTOR3 g_posMeshWall;						//位置
D3DXVECTOR3 g_rotMeshWall;						//向き
D3DXMATRIX g_mtxWorldMeshWall;					//ワールドマトリックス

//====================================================================
//メッシュウォールの初期化処理
//====================================================================
void InitMeshWall(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ENEMY00.png",
		&g_pTextureMeshWall);

	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		g_aMeshWall[nCntMeshWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * HEIGHT_SIZE * WAIGHT_SIZE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	VERTEX_3D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0, nCenterW = 0, nCenterH = 0; nCnt < HEIGHT_SIZE * WAIGHT_SIZE; nCnt++)
	{
		nCenterW = nCnt % WAIGHT_SIZE;

		//頂点座標の設定 
		pVtx[nCnt].pos.x = FIELD_SIZE * (nCenterW - (((float)WAIGHT_SIZE - 1) * WAIGHT_CENTER));

		pVtx[nCnt].pos.y = FIELD_SIZE * (HEIGHT_SIZE - 1) * HEIGHT_CENTER - FIELD_SIZE * nCenterH;

		pVtx[nCnt].pos.z = 0.0f;

		//法線ベクトルの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//頂点カラーの設定
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (nCenterW % 2 == 0)
		{
			pVtx[nCnt].tex.x = 0.0f;
		}
		else
		{
			pVtx[nCnt].tex.x = 1.0f;
		}
		if (nCenterH % 2 == 0)
		{
			pVtx[nCnt].tex.y = 0.0f;
		}
		else
		{
			pVtx[nCnt].tex.y = 1.0f;
		}

		if ((nCnt - nCenterH) % (WAIGHT_SIZE - 1) == 0 && nCnt != 0 && nCnt != (WAIGHT_SIZE - 1) * nCenterH + nCenterH)
		{
			nCenterH++;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshWall->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * (WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshWall,
		NULL);

	WORD *pIdx;	//インデックス情報へのポインタ

				//インデックスバッファをロックし、頂点番号データへのポインタを所得
	g_pIndxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0, nOri = 0; nCnt < (WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)) / 2; nCnt++)
	{
		if ((nCnt - nOri) % WAIGHT_SIZE == 0 && nCnt != 0 && nCnt != WAIGHT_SIZE * nOri + nOri)
		{
			pIdx[nCnt * 2] = nCnt - 1 - nOri;					//偶数
			pIdx[nCnt * 2 + 1] = nCnt + WAIGHT_SIZE - nOri;		//奇数

			nOri++;
		}
		else
		{
			pIdx[nCnt * 2] = nCnt + WAIGHT_SIZE - nOri;		//偶数
			pIdx[nCnt * 2 + 1] = nCnt - nOri;				//奇数
		}
	}

	//インデックスバッファをアンロックする
	g_pIndxBuffMeshWall->Unlock();


	SetMeshWall(D3DXVECTOR3(-1000.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
}

//====================================================================
//メッシュウォールの終了処理
//====================================================================
void UninitMeshWall(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIndxBuffMeshWall != NULL)
	{
		g_pIndxBuffMeshWall->Release();
		g_pIndxBuffMeshWall = NULL;
	}
}

//====================================================================
//メッシュウォールの更新処理
//====================================================================
void UpdateMeshWall(void)
{

}

//====================================================================
//メッシュウォールの描画処理
//====================================================================
void DrawMeshWall(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aMeshWall[nCntMeshWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCntMeshWall].rot.y, g_aMeshWall[nCntMeshWall].rot.x, g_aMeshWall[nCntMeshWall].rot.z);

			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorld, &g_aMeshWall[nCntMeshWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCntMeshWall].pos.x, g_aMeshWall[nCntMeshWall].pos.y, g_aMeshWall[nCntMeshWall].pos.z);

			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorld, &g_aMeshWall[nCntMeshWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntMeshWall].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIndxBuffMeshWall);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				0,//用意した頂点の数
				0,
				(WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)) - 2);//描画するプリミティブの数
		}
	}
}

//====================================================================
//メッシュウォールの設定処理
//====================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == false)
		{
			g_aMeshWall[nCntMeshWall].pos = pos;
			g_aMeshWall[nCntMeshWall].rot = rot;
			g_aMeshWall[nCntMeshWall].bUse = true;

			break;
		}
	}
}

//====================================================================
//メッシュウォール情報の取得
//====================================================================
MeshWall GetMeshWall(void)
{
	return g_aMeshWall[0];
}