#include "main.h"
#include "ENEMY.h"
#include "camera.h"
#include "input.h"

#define ENEMY_LIFE (7)		//オブジェクトの体力

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureENEMY[64][ENEMY_NTYPE_MAX] = {};	//テクスチャのポインタ
LPD3DXMESH g_pMeshENEMY[ENEMY_NTYPE_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatENEMY[ENEMY_NTYPE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatENEMY[ENEMY_NTYPE_MAX] = {};						//マテリアルの数

ENEMY g_Enemy[MAX_ENEMY];					//敵の情報
int EditIndexEnemy;								//エディットモード用の番号

const char *c_apModelEnemy[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\wall.x",
	"Data\\MODEL\\pc.x",
	"Data\\MODEL\\desk.x",
	"Data\\MODEL\\fan.x",
	"Data\\MODEL\\locker.x",
	"Data\\MODEL\\whiteboard.x",
	"Data\\MODEL\\officechair.x",
};


//====================================================================
//敵の初期化処理
//====================================================================
void InitEnemy(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		g_Enemy[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Enemy[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Enemy[nCntObject].bUse = false;
		g_Enemy[nCntObject].nType = ENEMY_NTYPE00;
		g_Enemy[nCntObject].aModel[0] = {};
	}
	EditIndexEnemy = 0;

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_NTYPE_MAX; nCntEnemy++)
	{
		D3DXLoadMeshFromX(c_apModelEnemy[nCntEnemy],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatENEMY[nCntEnemy],
			NULL,
			&g_dwNumMatENEMY[nCntEnemy],
			&g_pMeshENEMY[nCntEnemy]);
	}

	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntNumObject = 0; nCntNumObject < ENEMY_NTYPE_MAX; nCntNumObject++)
	{
		//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureENEMY[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//敵の終了処理
//====================================================================
void UninitEnemy(void)
{
	for (int nCntNumObject = 0; nCntNumObject < ENEMY_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//テクスチャの破棄
			if (g_pTextureENEMY[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureENEMY[nCntTex][nCntNumObject]->Release();
				g_pTextureENEMY[nCntTex][nCntNumObject] = NULL;
			}
		}

		//メッシュの破棄
		if (g_pMeshENEMY[nCntNumObject] != NULL)
		{
			g_pMeshENEMY[nCntNumObject]->Release();
			g_pMeshENEMY[nCntNumObject] = NULL;
		}

		//マテリアルの破棄
		if (g_pBuffMatENEMY[nCntNumObject] != NULL)
		{
			g_pBuffMatENEMY[nCntNumObject]->Release();
			g_pBuffMatENEMY[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//敵の更新処理
//====================================================================
void UpdateEnemy(void)
{
	for (int nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == true)
		{

		}
	}
}

//====================================================================
//敵の描画処理
//====================================================================
void DrawEnemy(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ



	for (nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		D3DXMATRIX mtxParent;
		D3DXMATRIX mtxRotModel, mtxTransModel; //計算用マトリクス

		//パーツのマトリックスの初期化
		D3DXMatrixIdentity(&g_Enemy[nCntObject].aModel[nCntObject].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[nCntObject].aModel[nCntObject].rot.y, g_Enemy[nCntObject].aModel[nCntObject].rot.x, g_Enemy[nCntObject].aModel[nCntObject].rot.z);
		D3DXMatrixMultiply(&g_Enemy[nCntObject].mtx, &g_Enemy[nCntObject].mtx, &mtxRotModel);

		//位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_Enemy[nCntObject].aModel[nCntObject].pos.x, g_Enemy[nCntObject].aModel[nCntObject].pos.y, g_Enemy[nCntObject].aModel[nCntObject].pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCntObject].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObject].aModel[nCntObject].mtxWorld, &mtxTransModel);

		if (g_Enemy[nCntObject].aModel[nCntObject].nIdxModelParent != -1)
		{
			mtxParent = g_Enemy[nCntObject].aModel[g_Enemy[nCntObject].aModel[nCntObject].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Enemy[nCntObject].mtx;
		}

		//算出したマトリクスをかけ合わせる
		D3DXMatrixMultiply(&g_Enemy[nCntObject].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObject].aModel[nCntObject].mtxWorld, &mtxParent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntObject].aModel[nCntObject].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを所得する
			pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[g_Enemy[nCntObject].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[g_Enemy[nCntObject].nType]; nCntMat++)
			{

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Enemy[nCntObject].bUse == true)
				{
					//テクスチャの設定
					pDevice->SetTexture(0, g_pTextureENEMY[nCntMat][g_Enemy[nCntObject].nType]);

					//敵(パーツ)の描画
					g_pMeshENEMY[g_Enemy[nCntObject].nType]->DrawSubset(nCntMat);
				}
			}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//エディットモードの敵の更新処理
//====================================================================
void UpdateEditEnemy(void)
{
	//キーボードの移動処理
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Enemy[EditIndexEnemy].pos.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Enemy[EditIndexEnemy].pos.z -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Enemy[EditIndexEnemy].pos.x += 1.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Enemy[EditIndexEnemy].pos.x -= 1.0f;
	}

	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_Enemy[EditIndexEnemy].rot.y += 1.57f;

		if (g_Enemy[EditIndexEnemy].rot.y >= 6.28f)
		{
			g_Enemy[EditIndexEnemy].rot.y = 0.0f;
		}
	}

	if (GetKeyboardTrigger(DIK_RSHIFT) == true)
	{
		g_Enemy[EditIndexEnemy].nType++;

		if (g_Enemy[EditIndexEnemy].nType > ENEMY_NTYPE_MAX - 1)
		{
			g_Enemy[EditIndexEnemy].nType = 0;
		}
	}
	if (GetKeyboardTrigger(DIK_RCONTROL) == true)
	{
		g_Enemy[EditIndexEnemy].nType--;

		if (g_Enemy[EditIndexEnemy].nType < 0)
		{
			g_Enemy[EditIndexEnemy].nType = ENEMY_NTYPE_MAX - 1;
		}
	}


	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetEnemy(g_Enemy[EditIndexEnemy].pos, g_Enemy[EditIndexEnemy].move, g_Enemy[EditIndexEnemy].rot, g_Enemy[EditIndexEnemy].nType);
	}
}

//====================================================================
//エディットモードの敵の描画処理
//====================================================================
void DrawEditEnemy(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ


		//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Enemy[EditIndexEnemy].mtx);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[EditIndexEnemy].rot.y, g_Enemy[EditIndexEnemy].rot.x, g_Enemy[EditIndexEnemy].rot.z);

	D3DXMatrixMultiply(&g_Enemy[EditIndexEnemy].mtx, &g_Enemy[EditIndexEnemy].mtx, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Enemy[EditIndexEnemy].pos.x, g_Enemy[EditIndexEnemy].pos.y, g_Enemy[EditIndexEnemy].pos.z);

	D3DXMatrixMultiply(&g_Enemy[EditIndexEnemy].mtx, &g_Enemy[EditIndexEnemy].mtx, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[EditIndexEnemy].mtx);

	//現在のマテリアルを所得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを所得する
	pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[g_Enemy[EditIndexEnemy].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[g_Enemy[EditIndexEnemy].nType]; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureENEMY[nCntMat][g_Enemy[EditIndexEnemy].nType]);

		//敵(パーツ)の描画
		g_pMeshENEMY[g_Enemy[EditIndexEnemy].nType]->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//敵の設定処理
//====================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == false)
		{
			g_Enemy[nCntObject].pos = pos;
			g_Enemy[nCntObject].posOld = pos;
			g_Enemy[nCntObject].move = move;
			g_Enemy[nCntObject].rot = rot;
			g_Enemy[nCntObject].nType = nType;

			//switch (nType)
			//{
			//case 0:
			//	g_Enemy[nCntObject].nType = ENEMY_NTYPE00;
			//	break;
			//}

			g_Enemy[nCntObject].bUse = true;
			EditIndexEnemy++;

			int nNumVtx;		//頂点数
			DWORD dwSizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;		//頂点バッファへのポインタ

			//頂点数を所得
			nNumVtx = g_pMeshENEMY[nType]->GetNumVertices();

			//頂点フォーマットのサイズを所得
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshENEMY[nType]->GetFVF());

			//頂点バッファをロック
			g_pMeshENEMY[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				if (g_Enemy[nCntObject].vtxMin.x > vtx.x)
				{
					g_Enemy[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_Enemy[nCntObject].vtxMin.y > vtx.y)
				{
					g_Enemy[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_Enemy[nCntObject].vtxMin.z > vtx.z)
				{
					g_Enemy[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_Enemy[nCntObject].vtxMax.x < vtx.x)
				{
					g_Enemy[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_Enemy[nCntObject].vtxMax.y < vtx.y)
				{
					g_Enemy[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_Enemy[nCntObject].vtxMax.z < vtx.z)
				{
					g_Enemy[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshENEMY[nType]->UnlockVertexBuffer();

			CollisionRotEnemy(nCntObject);

			break;
		}
	}
}

//====================================================================
//オブジェクトの当たり判定を回転させる処理
//====================================================================
void CollisionRotEnemy(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_Enemy[nCnt].vtxMax.z;
	MaxX = g_Enemy[nCnt].vtxMax.x;
	MinZ = g_Enemy[nCnt].vtxMin.z;
	MinX = g_Enemy[nCnt].vtxMin.x;


	if (g_Enemy[nCnt].rot.y <= 0.0f)
	{
		g_Enemy[nCnt].vtxMax.z = MaxZ;
		g_Enemy[nCnt].vtxMax.x = MaxX;
		g_Enemy[nCnt].vtxMin.z = MinZ;
		g_Enemy[nCnt].vtxMin.x = MinX;
	}
	else if (g_Enemy[nCnt].rot.y <= 1.57f)
	{

	}
	else if (g_Enemy[nCnt].rot.y <= 3.14f)
	{

	}
	else if (g_Enemy[nCnt].rot.y <= 4.71f)
	{

	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = true;

	for (int nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == true)
		{
			if (
				(
				pPos->y + max.y >= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y && pPosOld->y + max.y< g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y ||
				pPos->y + min.y <= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y && pPosOld->y + min.y > g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y) &&
				pPos->x + Size >= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x &&
				pPos->z + Size >= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bON = false;
			}

			if (
				(
				pPos->z + Size >= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z && pPosOld->z + Size < g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z ||
				pPos->z - Size <= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z && pPosOld->z - Size > g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z) &&
				pPos->x + Size >= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x &&
				pPos->y + max.y >= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y&&
				pPos->y + min.y <= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y
				)
			{//壁とプレイヤーが当たった(Z軸)
				pPos->z = pPosOld->z;
				pMove->z = 0.0f;
			}

			if (
				(
				pPos->x + Size >= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x && pPosOld->x + Size < g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x ||
				pPos->x - Size <= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x && pPosOld->x - Size > g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x) &&
				pPos->z + Size >= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z &&
				pPos->y + max.y >= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y &&
				pPos->y + min.y <= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y
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
void CollisionEnemyShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y &&
				pPos->y <= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y &&
				pPos->x >= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x &&
				pPos->x <= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x &&
				pPos->z >= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z &&
				pPos->z <= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = g_Enemy[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//敵の所得
//====================================================================
ENEMY * GetEnemy(void)
{
	return &g_Enemy[0];
}