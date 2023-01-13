#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"

#define OBJECT00_LIFE (7)		//オブジェクトの体力

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureObject00[64][OBJECT00_NTYPE_MAX] = {};	//テクスチャのポインタ
LPD3DXMESH g_pMeshObject00[OBJECT00_NTYPE_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatObject00[OBJECT00_NTYPE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatObject00[OBJECT00_NTYPE_MAX] = {};						//マテリアルの数

Object00 g_Object00[MAX_OBJECT00];					//オブジェクト00の情報

//====================================================================
//オブジェクト00の初期化処理
//====================================================================
void InitObject00(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		g_Object00[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object00[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object00[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object00[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object00[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Object00[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Object00[nCntObject].bUse = false;
		g_Object00[nCntObject].nType = OBJECT00_NTYPE00;
	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\wall.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE00],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE00],
		&g_pMeshObject00[OBJECT00_NTYPE00]);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\pc.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE01],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE01],
		&g_pMeshObject00[OBJECT00_NTYPE01]);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\desk.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE02],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE02],
		&g_pMeshObject00[OBJECT00_NTYPE02]);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\fan.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE03],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE03],
		&g_pMeshObject00[OBJECT00_NTYPE03]);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\locker.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE04],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE04],
		&g_pMeshObject00[OBJECT00_NTYPE04]);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\whiteboard.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE05],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE05],
		&g_pMeshObject00[OBJECT00_NTYPE05]);

	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntNumObject = 0; nCntNumObject < OBJECT00_NTYPE_MAX; nCntNumObject++)
	{
		//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatObject00[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject00[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObject00[nCntMat][nCntNumObject]);
			}
		}
	}

	SetObject00(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE00);
	SetObject00(D3DXVECTOR3(-200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE01);
	SetObject00(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE02);
	SetObject00(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE03);
	SetObject00(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE04);
	SetObject00(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE05);
}

//====================================================================
//オブジェクト00の終了処理
//====================================================================
void UninitObject00(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECT00_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//テクスチャの破棄
			if (g_pTextureObject00[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureObject00[nCntTex][nCntNumObject]->Release();
				g_pTextureObject00[nCntTex][nCntNumObject] = NULL;
			}
		}

		//メッシュの破棄
		if (g_pMeshObject00[nCntNumObject] != NULL)
		{
			g_pMeshObject00[nCntNumObject]->Release();
			g_pMeshObject00[nCntNumObject] = NULL;
		}

		//マテリアルの破棄
		if (g_pBuffMatObject00[nCntNumObject] != NULL)
		{
			g_pBuffMatObject00[nCntNumObject]->Release();
			g_pBuffMatObject00[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//オブジェクト00の更新処理
//====================================================================
void UpdateObject00(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Object00[nCntObject].bUse == true)
		{

		}
	}
}

//====================================================================
//オブジェクト00の描画処理
//====================================================================
void DrawObject00(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Object00[nCntObject].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object00[nCntObject].rot.y, g_Object00[nCntObject].rot.x, g_Object00[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_Object00[nCntObject].mtxWorld, &g_Object00[nCntObject].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Object00[nCntObject].pos.x, g_Object00[nCntObject].pos.y, g_Object00[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_Object00[nCntObject].mtxWorld, &g_Object00[nCntObject].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Object00[nCntObject].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを所得する
			pMat = (D3DXMATERIAL*)g_pBuffMatObject00[g_Object00[nCntObject].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject00[g_Object00[nCntObject].nType]; nCntMat++)
			{

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Object00[nCntObject].bUse == true)
				{
					//switch (g_Object00[nCntObject].nType)
					//{
					//case OBJECT_NTYPE00:
						//テクスチャの設定
						pDevice->SetTexture(0, g_pTextureObject00[nCntMat][g_Object00[nCntObject].nType]);

						//オブジェクト00(パーツ)の描画
						g_pMeshObject00[g_Object00[nCntObject].nType]->DrawSubset(nCntMat);
					//	break;

					//case OBJECT_NTYPE01:
					//	//テクスチャの設定
					//	pDevice->SetTexture(0, g_pTextureObject00[nCntMat][OBJECT_NTYPE01]);

					//	//オブジェクト00(パーツ)の描画
					//	g_pMeshObject00[OBJECT_NTYPE01]->DrawSubset(nCntMat);
					//	break;
					//}
				}
			}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//オブジェクト00の設定処理
//====================================================================
void SetObject00(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, OBJECT00_NTYPE nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Object00[nCntObject].bUse == false)
		{
			g_Object00[nCntObject].pos = pos;
			g_Object00[nCntObject].posOld = pos;
			g_Object00[nCntObject].move = move;
			g_Object00[nCntObject].rot = rot;
			g_Object00[nCntObject].nType = nType;
			g_Object00[nCntObject].bUse = true;

			int nNumVtx;		//頂点数
			DWORD dwSizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;		//頂点バッファへのポインタ

			//頂点数を所得
			nNumVtx = g_pMeshObject00[nType]->GetNumVertices();

			//頂点フォーマットのサイズを所得
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObject00[nType]->GetFVF());

			//頂点バッファをロック
			g_pMeshObject00[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				if (g_Object00[nCntObject].vtxMin.x > vtx.x)
				{
					g_Object00[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_Object00[nCntObject].vtxMin.y > vtx.y)
				{
					g_Object00[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_Object00[nCntObject].vtxMin.z > vtx.z)
				{
					g_Object00[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_Object00[nCntObject].vtxMax.x < vtx.x)
				{
					g_Object00[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_Object00[nCntObject].vtxMax.y < vtx.y)
				{
					g_Object00[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_Object00[nCntObject].vtxMax.z < vtx.z)
				{
					g_Object00[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshObject00[nType]->UnlockVertexBuffer();

			break;
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool CollisionObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = true;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Object00[nCntObject].bUse == true)
		{
			if (
				(
				pPos->y + max.y >= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y && pPosOld->y + max.y< g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y ||
				pPos->y + min.y <= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y && pPosOld->y + min.y > g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y) &&
				pPos->x + Size >= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x &&
				pPos->z + Size >= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bON = false;
			}

			if (
				(
				pPos->z + Size >= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z && pPosOld->z + Size < g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z ||
				pPos->z - Size <= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z && pPosOld->z - Size > g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z) &&
				pPos->x + Size >= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x &&
				pPos->y + max.y >= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y&&
				pPos->y + min.y <= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y
				)
			{//壁とプレイヤーが当たった(Z軸)
				pPos->z = pPosOld->z;
				pMove->z = 0.0f;
			}

			if (
				(
				pPos->x + Size >= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x && pPosOld->x + Size < g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x ||
				pPos->x - Size <= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x && pPosOld->x - Size > g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x) &&
				pPos->z + Size >= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z &&
				pPos->y + max.y >= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y &&
				pPos->y + min.y <= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->x = pPosOld->x;
				pMove->x = 0.0f;
			}
		}
	}
	return bON;
}

//====================================================================
//影との当たり判定処理
//====================================================================
void CollisionObject00Shadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Object00[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y &&
				pPos->y <= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y &&
				pPos->x >= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x &&
				pPos->x <= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x &&
				pPos->z >= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z &&
				pPos->z <= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = g_Object00[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//オブジェクト00の所得
//====================================================================
Object00 * GetObject00(void)
{
	return &g_Object00[0];
}