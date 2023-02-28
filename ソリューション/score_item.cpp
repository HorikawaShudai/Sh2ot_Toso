#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "score_item.h"
#include "score.h"

//マクロ定義
#define NUM_SCOREITEM (90)	//配置するスコアの数
#define OBJECT00_LIFE (7)		//オブジェクトの体力

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureItem[64][OBJECT_SCORE_MAX] = {};		//テクスチャのポインタ
LPD3DXMESH g_pMeshItem[OBJECT_SCORE_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatItem[OBJECT_SCORE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatItem[OBJECT_SCORE_MAX] = {};						//マテリアルの数

Object00 g_Item[MAX_ITEM00];					//オブジェクト00の情報

const char *c_apModeObj[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\jewelry.x",
};

//====================================================================
//オブジェクト00の初期化処理
//====================================================================
void InitItem(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_ITEM00; nCntObject++)
	{
		g_Item[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Item[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Item[nCntObject].bUse = false;
		g_Item[nCntObject].nType = OBJECT_SCORE_ITEM;
		g_Item[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	}

	//Xファイルの読み込み
	for (int nCntObj = 0; nCntObj < OBJECT_SCORE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModeObj[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatItem[nCntObj],
			NULL,
			&g_dwNumMatItem[nCntObj],
			&g_pMeshItem[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntNumObject = 0; nCntNumObject < OBJECT_SCORE_MAX; nCntNumObject++)
	{
		//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatItem[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatItem[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureItem[nCntMat][nCntNumObject]);
			}
		}
	}

	//スコア用アイテムの配置
	SetNumItems(21, D3DXVECTOR3(-1650.0f, 0.0f, -400.0f), 50.0f, 0.0f);
	SetNumItems(17, D3DXVECTOR3(-1000.0f, 0.0f, -350.0f), 0.0f, 50.0f);
	SetNumItems(7, D3DXVECTOR3(-1050.0f, 0.0f, 600.0f), 0.0f, 50.0f);
	SetNumItems(9, D3DXVECTOR3(-950.0f, 0.0f, 600.0f), 0.0f, 50.0f);
	SetNumItems(9, D3DXVECTOR3(-1650.0f, 0.0f, -350.0f), 0.0f, 50.0f);
	SetNumItems(14, D3DXVECTOR3(-2150.0f, 0.0f, 150.0f), 50.0f, 0.0f);
	SetNumItems(13, D3DXVECTOR3(-1450.0f, 0.0f, 200.0f), 0.0f, 50.0f);
	SetNumItems(29, D3DXVECTOR3(-1350.0f, 0.0f, 250.0f), 0.0f, 50.0f);
	SetNumItems(13, D3DXVECTOR3(-1250.0f, 0.0f, 1100.0f), 0.0f, 50.0f);
	SetNumItems(19, D3DXVECTOR3(-1250.0f, 0.0f, 1050.0f), 50.0f, 0.0f);
	SetNumItems(10, D3DXVECTOR3(-350.0f, 0.0f, 550.0f), 0.0f, 50.0f);
	SetNumItems(15, D3DXVECTOR3(-300.0f, 0.0f, 550.0f), 50.0f, 0.0f);
	SetNumItems(15, D3DXVECTOR3(-600.0f, 0.0f, -400.0f), 0.0f, 50.0f);
	SetNumItems(8, D3DXVECTOR3(-600.0f, 0.0f, 350.0f), 50.0f, 0.0f);
	SetNumItems(5, D3DXVECTOR3(-250.0f, 0.0f, 150.0f), 0.0f, 50.0f);
	SetNumItems(6, D3DXVECTOR3(-200.0f, 0.0f, 150.0f), 50.0f, 0.0f);
	SetNumItems(11, D3DXVECTOR3(50.0f, 0.0f, -400.0f), 0.0f, 50.0f);
	SetNumItems(5, D3DXVECTOR3(-2150.0f, 0.0f, 200.0f), 0.0f, 50.0f);
	SetNumItems(5, D3DXVECTOR3(-1850.0f, 0.0f, 200.0f), 0.0f, 50.0f);
	SetNumItems(14, D3DXVECTOR3(-2150.0f, 0.0f, 450.0f), 50.0f, 0.0f);
	SetNumItems(14, D3DXVECTOR3(-2150.0f, 0.0f, 650.0f), 50.0f, 0.0f);
	SetNumItems(3, D3DXVECTOR3(-2150.0f, 0.0f, 700.0f), 0.0f, 50.0f);
	SetNumItems(12, D3DXVECTOR3(-2150.0f, 0.0f, 850.0f), 50.0f, 0.0f);
	SetNumItems(3, D3DXVECTOR3(-1950.0f, 0.0f, 900.0f), 0.0f, 50.0f);
	SetNumItems(3, D3DXVECTOR3(-1650.0f, 0.0f, 900.0f), 0.0f, 50.0f);
	SetNumItems(11, D3DXVECTOR3(-1650.0f, 0.0f, 1050.0f), -50.0f, 0.0f);
	SetNumItems(9, D3DXVECTOR3(-2150.0f, 0.0f, 1100.0f), 0.0f, 50.0f);
	SetNumItems(6, D3DXVECTOR3(-2100.0f, 0.0f, 1500.0f), 50.0f, 0.0f);
	SetNumItems(6, D3DXVECTOR3(-1850.0f, 0.0f, 1500.0f), 0.0f, 50.0f);
	SetNumItems(13, D3DXVECTOR3(-1800.0f, 0.0f, 1750.0f), 50.0f, 0.0f);
	SetNumItems(11, D3DXVECTOR3(-2100.0f, 0.0f, 1250.0f), 50.0f, 0.0f);
	SetNumItems(10, D3DXVECTOR3(-1550.0f, 0.0f, 1250.0f), 0.0f, 50.0f);
	SetNumItems(12, D3DXVECTOR3(-1150.0f, 0.0f, 1450.0f), 0.0f, 50.0f);
	SetNumItems(14, D3DXVECTOR3(-1150.0f, 0.0f, 2050.0f), 50.0f, 0.0f);
	SetNumItems(20, D3DXVECTOR3(-450.0f, 0.0f, 1100.0f), 0.0f, 50.0f);
	SetNumItems(13, D3DXVECTOR3(-500.0f, 0.0f, 1450.0f), -50.0f, 0.0f);
	SetNumItems(12, D3DXVECTOR3(-550.0f, 0.0f, -50.0f), 50.0f, 0.0f);
	SetNumItems(9, D3DXVECTOR3(50.0f, 0.0f, -450.0f), 50.0f, 0.0f);
	SetNumItems(15, D3DXVECTOR3(450.0f, 0.0f, -400.0f), 0.0f, 50.0f);
	SetNumItems(10, D3DXVECTOR3(300.0f, 0.0f, -400.0f), 0.0f, 50.0f);
	SetNumItems(13, D3DXVECTOR3(150.0f, 0.0f, -400.0f), 0.0f, 50.0f);
	SetNumItems(5, D3DXVECTOR3(-650.0f, 0.0f, 1100.0f), 0.0f, 50.0f);
	SetNumItems(10, D3DXVECTOR3(-700.0f, 0.0f, 1315.0f), -50.0f, 0.0f);
	SetNumItems(4, D3DXVECTOR3(-500.0f, 0.0f, 1650.0f), -50.0f, 0.0f);
	SetNumItems(4, D3DXVECTOR3(-600.0f, 0.0f, 1700.0f), 0.0f, 50.0f);
	SetNumItems(9, D3DXVECTOR3(-650.0f, 0.0f, 1850.0f), -50.0f, 0.0f);
	SetNumItems(3, D3DXVECTOR3(-1050.0f, 0.0f, 1850.0f), 0.0f, 50.0f);
	SetNumItems(5, D3DXVECTOR3(400.0f, 0.0f, 200.0f), -50.0f, 0.0f);
}

//====================================================================
//オブジェクト00の終了処理
//====================================================================
void UninitItem(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECT_SCORE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//テクスチャの破棄
			if (g_pTextureItem[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureItem[nCntTex][nCntNumObject]->Release();
				g_pTextureItem[nCntTex][nCntNumObject] = NULL;
			}
		}

		//メッシュの破棄
		if (g_pMeshItem[nCntNumObject] != NULL)
		{
			g_pMeshItem[nCntNumObject]->Release();
			g_pMeshItem[nCntNumObject] = NULL;
		}
			//マテリアルの破棄
		if (g_pBuffMatItem[nCntNumObject] != NULL)
		{
			g_pBuffMatItem[nCntNumObject]->Release();
			g_pBuffMatItem[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//オブジェクト00の更新処理
//====================================================================
void UpdateItem(void)
{
	for (int nCntObject = 0; nCntObject < MAX_ITEM00; nCntObject++)
	{
		if (g_Item[nCntObject].bUse == true)
		{
		}
	}
}

//====================================================================
//オブジェクト00の描画処理
//====================================================================
void DrawItem(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (nCntObject = 0; nCntObject < MAX_ITEM00; nCntObject++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Item[nCntObject].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nCntObject].rot.y, g_Item[nCntObject].rot.x, g_Item[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_Item[nCntObject].mtxWorld, &g_Item[nCntObject].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Item[nCntObject].pos.x, g_Item[nCntObject].pos.y, g_Item[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_Item[nCntObject].mtxWorld, &g_Item[nCntObject].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCntObject].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを所得する
		pMat = (D3DXMATERIAL*)g_pBuffMatItem[g_Item[nCntObject].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatItem[g_Item[nCntObject].nType]; nCntMat++)
		{

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_Item[nCntObject].bUse == true)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureItem[nCntMat][g_Item[nCntObject].nType]);

				//オブジェクト00(パーツ)の描画
				g_pMeshItem[g_Item[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//エディットモードのオブジェクト00の更新処理
//====================================================================
void UpdateEditItem(void)
{
}

//====================================================================
//エディットモードのオブジェクト00の描画処理
//====================================================================
void DrawEditItem(void)
{
	
}

//====================================================================
//オブジェクト00の設定処理
//====================================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_ITEM00; nCntObject++)
	{
		if (g_Item[nCntObject].bUse == false)
		{
			g_Item[nCntObject].pos = pos;
			g_Item[nCntObject].posOld = pos;
			g_Item[nCntObject].move = move;
			g_Item[nCntObject].rot = rot;
			g_Item[nCntObject].nType = nType;

			g_Item[nCntObject].bUse = true;
		
			int nNumVtx;		//頂点数
			DWORD dwSizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;		//頂点バッファへのポインタ

								//頂点数を所得
			nNumVtx = g_pMeshItem[nType]->GetNumVertices();

			//頂点フォーマットのサイズを所得
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshItem[nType]->GetFVF());

			//頂点バッファをロック
			g_pMeshItem[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				if (g_Item[nCntObject].vtxMin.x > vtx.x)
				{
					g_Item[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_Item[nCntObject].vtxMin.y > vtx.y)
				{
					g_Item[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_Item[nCntObject].vtxMin.z > vtx.z)
				{
					g_Item[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_Item[nCntObject].vtxMax.x < vtx.x)
				{
					g_Item[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_Item[nCntObject].vtxMax.y < vtx.y)
				{
					g_Item[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_Item[nCntObject].vtxMax.z < vtx.z)
				{
					g_Item[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshItem[nType]->UnlockVertexBuffer();

			CollisionRotObject00(nCntObject);

			break;
		}
	}
}

//====================================================================
//使うスコアアイテムの設定
//====================================================================
void SetNumItems(int nNumItem,D3DXVECTOR3 pos,float fWidth_x, float fWidth_z)
{
	//スコアアイテムの配置
	for (int nCnt = 0; nCnt < nNumItem; nCnt++)
	{
		SetItem(D3DXVECTOR3(pos.x + (nCnt * fWidth_x), pos.y, pos.z + (nCnt * fWidth_z)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size,int nPlayer)
{
	bool bHit = false;

	for (int nCntObject = 0; nCntObject < MAX_ITEM00; nCntObject++)
	{
		if (g_Item[nCntObject].bUse == true)
		{
			if (pPos->x >= g_Item[nCntObject].pos.x + min.x
				&& pPos->x <= g_Item[nCntObject].pos.x + max.x
				&& pPos->y >= g_Item[nCntObject].pos.y + min.y
				&& pPos->y <= g_Item[nCntObject].pos.y + max.y
				&& pPos->z >= g_Item[nCntObject].pos.z + min.z
				&& pPos->z <= g_Item[nCntObject].pos.z + max.z)
			{//アイテムとプレイヤーが当たった(X軸)
				AddScore(g_Item[nCntObject].nType, nPlayer);
				g_Item[nCntObject].bUse = false;
				bHit = true;
			}
		}
	}

	return bHit;
}

//====================================================================
//影との当たり判定処理
//====================================================================
void CollisionItemShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_ITEM00; nCntObject++)
	{
		if (g_Item[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_Item[nCntObject].pos.y + g_Item[nCntObject].vtxMin.y &&
				pPos->y <= g_Item[nCntObject].pos.y + g_Item[nCntObject].vtxMax.y &&
				pPos->x >= g_Item[nCntObject].pos.x + g_Item[nCntObject].vtxMin.x &&
				pPos->x <= g_Item[nCntObject].pos.x + g_Item[nCntObject].vtxMax.x &&
				pPos->z >= g_Item[nCntObject].pos.z + g_Item[nCntObject].vtxMin.z &&
				pPos->z <= g_Item[nCntObject].pos.z + g_Item[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = g_Item[nCntObject].vtxMax.y;
			}
		}
	}
}



