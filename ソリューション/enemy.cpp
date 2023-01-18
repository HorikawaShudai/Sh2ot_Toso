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
		
			g_Enemy[nCntObject].aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Enemy[nCntObject].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Enemy[nCntObject].aModel[0].nType = 0;
			g_Enemy[nCntObject].aModel[0].nIdxModelParent = -1;

			g_Enemy[nCntObject].aModel[1].pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
			g_Enemy[nCntObject].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Enemy[nCntObject].aModel[1].nType = 0;
			g_Enemy[nCntObject].aModel[1].nIdxModelParent = 0;
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ

	for (int nCntObjectModel = 0; nCntObjectModel < MAX_ENEMY; nCntObjectModel++)
	{
		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&g_Enemy[nCntObjectModel].mtx);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntObjectModel].rot.y, g_Enemy[nCntObjectModel].rot.x, g_Enemy[nCntObjectModel].rot.z);
		D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].mtx, &g_Enemy[nCntObjectModel].mtx, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntObjectModel].pos.x, g_Enemy[nCntObjectModel].pos.y, g_Enemy[nCntObjectModel].pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].mtx, &g_Enemy[nCntObjectModel].mtx, &mtxTrans);

		//ワールドマトリクスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntObjectModel].mtx);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);
		for (nCntObject = 0; nCntObject < NUM_ENEMYMODEL; nCntObject++)
		{
			D3DXMATRIX mtxParent;
			D3DXMATRIX mtxRotModel, mtxTransModel; //計算用マトリクス

												   //パーツのマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.y, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.x, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].mtx, &g_Enemy[nCntObjectModel].mtx, &mtxRotModel);

			//位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.x, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.y, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &mtxTransModel);

			//親のマトリクスの設定
			if (g_Enemy[nCntObjectModel].aModel[nCntObject].nIdxModelParent != -1)
			{
				mtxParent = g_Enemy[nCntObjectModel].aModel[g_Enemy[nCntObjectModel].aModel[nCntObject].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_Enemy[nCntObjectModel].mtx;
			}

			//算出したマトリクスをかけ合わせる
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &mtxParent);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld);

			//現在のマテリアルを所得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを所得する
			pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[g_Enemy[nCntObjectModel].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[g_Enemy[nCntObjectModel].nType]; nCntMat++)
			{

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Enemy[nCntObjectModel].bUse == true)
				{
					//テクスチャの設定
					pDevice->SetTexture(0, g_pTextureENEMY[nCntMat][g_Enemy[nCntObjectModel].aModel[nCntObject].nType]);

					//敵(パーツ)の描画
					g_pMeshENEMY[g_Enemy[nCntObjectModel].aModel[nCntObject].nType]->DrawSubset(nCntMat);
				}
			}
			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
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
	int nCntObject;
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ

	for (int nCntObjectModel = 0; nCntObjectModel < MAX_ENEMY; nCntObjectModel++)
	{
		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&g_Enemy[nCntObjectModel].mtx);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntObjectModel].rot.y, g_Enemy[nCntObjectModel].rot.x, g_Enemy[nCntObjectModel].rot.z);
		D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].mtx, &g_Enemy[nCntObjectModel].mtx, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntObjectModel].pos.x, g_Enemy[nCntObjectModel].pos.y, g_Enemy[nCntObjectModel].pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].mtx, &g_Enemy[nCntObjectModel].mtx, &mtxTrans);

		//ワールドマトリクスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntObjectModel].mtx);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);
		for (nCntObject = 0; nCntObject < NUM_ENEMYMODEL; nCntObject++)
		{
			D3DXMATRIX mtxParent;
			D3DXMATRIX mtxRotModel, mtxTransModel; //計算用マトリクス

												   //パーツのマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.y, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.x, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].mtx, &g_Enemy[nCntObjectModel].mtx, &mtxRotModel);

			//位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.x, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.y, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &mtxTransModel);

			//親のマトリクスの設定
			if (g_Enemy[nCntObjectModel].aModel[nCntObject].nIdxModelParent != -1)
			{
				mtxParent = g_Enemy[nCntObjectModel].aModel[g_Enemy[nCntObjectModel].aModel[nCntObject].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_Enemy[nCntObjectModel].mtx;
			}

			//算出したマトリクスをかけ合わせる
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &mtxParent);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld);

			//現在のマテリアルを所得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを所得する
			pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[g_Enemy[nCntObjectModel].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[g_Enemy[nCntObjectModel].nType]; nCntMat++)
			{

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Enemy[nCntObjectModel].bUse == true)
				{
					//テクスチャの設定
					pDevice->SetTexture(0, g_pTextureENEMY[nCntMat][g_Enemy[nCntObjectModel].aModel[nCntObject].nType]);

					//敵(パーツ)の描画
					g_pMeshENEMY[g_Enemy[nCntObjectModel].aModel[nCntObject].nType]->DrawSubset(nCntMat);
				}
			}
			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
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

			break;
		}
	}
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