//========================================================================================
//
// 鍵の処理[Key.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "key.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureKey[64][KEY_TYPE_MAX] = {};		//テクスチャのポインタ
LPD3DXMESH g_pMeshKey[KEY_TYPE_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatKey[KEY_TYPE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatKey[KEY_TYPE_MAX] = {};						//マテリアルの数

KEY g_Key[MAX_KEY];					//鍵の情報

const char *c_apKey[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\key.x",
};

//====================================================================
//鍵の初期化処理
//====================================================================
void InitKey(void)
{
	int nCntKey;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		g_Key[nCntKey].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Key[nCntKey].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Key[nCntKey].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Key[nCntKey].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Key[nCntKey].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Key[nCntKey].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Key[nCntKey].bUse = false;
		g_Key[nCntKey].nType = KEY_TYPE_ITEM;
	}

	//Xファイルの読み込み
	for (int nCntObj = 0; nCntObj < KEY_TYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apKey[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatKey[nCntObj],
			NULL,
			&g_dwNumMatKey[nCntObj],
			&g_pMeshKey[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntNumObject = 0; nCntNumObject < KEY_TYPE_MAX; nCntNumObject++)
	{
		//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatKey[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatKey[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureKey[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//鍵の終了処理
//====================================================================
void UninitKey(void)
{
	for (int nCntNumObject = 0; nCntNumObject < KEY_TYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//テクスチャの破棄
			if (g_pTextureKey[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureKey[nCntTex][nCntNumObject]->Release();
				g_pTextureKey[nCntTex][nCntNumObject] = NULL;
			}
		}

		//メッシュの破棄
		if (g_pMeshKey[nCntNumObject] != NULL)
		{
			g_pMeshKey[nCntNumObject]->Release();
			g_pMeshKey[nCntNumObject] = NULL;
		}
		//マテリアルの破棄
		if (g_pBuffMatKey[nCntNumObject] != NULL)
		{
			g_pBuffMatKey[nCntNumObject]->Release();
			g_pBuffMatKey[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//鍵の更新処理
//====================================================================
void UpdateKey(void)
{
	for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{
		}
	}
}

//====================================================================
//鍵の描画処理
//====================================================================
void DrawKey(void)
{
	int nCntKey;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Key[nCntKey].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Key[nCntKey].rot.y, g_Key[nCntKey].rot.x, g_Key[nCntKey].rot.z);

		D3DXMatrixMultiply(&g_Key[nCntKey].mtxWorld, &g_Key[nCntKey].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Key[nCntKey].pos.x, g_Key[nCntKey].pos.y, g_Key[nCntKey].pos.z);

		D3DXMatrixMultiply(&g_Key[nCntKey].mtxWorld, &g_Key[nCntKey].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Key[nCntKey].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを所得する
		pMat = (D3DXMATERIAL*)g_pBuffMatKey[g_Key[nCntKey].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatKey[g_Key[nCntKey].nType]; nCntMat++)
		{

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_Key[nCntKey].bUse == true)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureKey[nCntMat][g_Key[nCntKey].nType]);

				//鍵(パーツ)の描画
				g_pMeshKey[g_Key[nCntKey].nType]->DrawSubset(nCntMat);
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//エディットモードの鍵の更新処理
//====================================================================
void UpdateEditKey(void)
{
}

//====================================================================
//エディットモードの鍵の描画処理
//====================================================================
void DrawEditKey(void)
{

}

//====================================================================
//鍵の設定処理
//====================================================================
void SetKey(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntKey;

	for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == false)
		{
			g_Key[nCntKey].pos = pos;
			g_Key[nCntKey].posOld = pos;
			g_Key[nCntKey].move = move;
			g_Key[nCntKey].rot = rot;
			g_Key[nCntKey].nType = nType;

			g_Key[nCntKey].bUse = true;

			int nNumVtx;		//頂点数
			DWORD dwSizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;		//頂点バッファへのポインタ

								//頂点数を所得
			nNumVtx = g_pMeshKey[nType]->GetNumVertices();

			//頂点フォーマットのサイズを所得
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshKey[nType]->GetFVF());

			//頂点バッファをロック
			g_pMeshKey[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				if (g_Key[nCntKey].vtxMin.x > vtx.x)
				{
					g_Key[nCntKey].vtxMin.x = vtx.x;
				}
				if (g_Key[nCntKey].vtxMin.y > vtx.y)
				{
					g_Key[nCntKey].vtxMin.y = vtx.y;
				}
				if (g_Key[nCntKey].vtxMin.z > vtx.z)
				{
					g_Key[nCntKey].vtxMin.z = vtx.z;
				}

				if (g_Key[nCntKey].vtxMax.x < vtx.x)
				{
					g_Key[nCntKey].vtxMax.x = vtx.x;
				}
				if (g_Key[nCntKey].vtxMax.y < vtx.y)
				{
					g_Key[nCntKey].vtxMax.y = vtx.y;
				}
				if (g_Key[nCntKey].vtxMax.z < vtx.z)
				{
					g_Key[nCntKey].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshKey[nType]->UnlockVertexBuffer();

			CollisionRotObject00(nCntKey);

			break;
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool CollisionKey(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer)
{
	bool bHit = false;

	for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{
			if (pPos->x >= g_Key[nCntKey].pos.x - Size
				&& pPos->x <= g_Key[nCntKey].pos.x + Size
				&& pPos->y >= g_Key[nCntKey].pos.y - Size
				&& pPos->y <= g_Key[nCntKey].pos.y + Size
				&& pPos->z >= g_Key[nCntKey].pos.z - Size
				&& pPos->z <= g_Key[nCntKey].pos.z + Size)
			{//アイテムとプレイヤーが当たった(X軸)
				g_Key[nCntKey].bUse = false;
				bHit = true;
				break;
			}
		}
	}

	return bHit;
}

//====================================================================
//影との当たり判定処理
//====================================================================
void CollisionKeyShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{
			if (
				pPos->y >= g_Key[nCntKey].pos.y + g_Key[nCntKey].vtxMin.y &&
				pPos->y <= g_Key[nCntKey].pos.y + g_Key[nCntKey].vtxMax.y &&
				pPos->x >= g_Key[nCntKey].pos.x + g_Key[nCntKey].vtxMin.x &&
				pPos->x <= g_Key[nCntKey].pos.x + g_Key[nCntKey].vtxMax.x &&
				pPos->z >= g_Key[nCntKey].pos.z + g_Key[nCntKey].vtxMin.z &&
				pPos->z <= g_Key[nCntKey].pos.z + g_Key[nCntKey].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = g_Key[nCntKey].vtxMax.y;
			}
		}
	}
}
