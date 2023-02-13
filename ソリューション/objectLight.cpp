//========================================================================================
//
// 背景用オブジェクトの処理[ObjectLight.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "objectLight.h"
#include "light.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

#define OBJECTLIGHT_LIFE (7)		//オブジェクトの体力

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureObjectLight[64][OBJECTLIGHT_NTYPE_MAX] = {};		//テクスチャのポインタ
LPD3DXMESH g_pMeshObjectLight[OBJECTLIGHT_NTYPE_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatObjectLight[OBJECTLIGHT_NTYPE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatObjectLight[OBJECTLIGHT_NTYPE_MAX] = {};						//マテリアルの数

ObjectLight g_ObjectLight[MAX_OBJECTLIGHT];					//オブジェクトLightの情報
int EditIndex02;								//エディットモード用の番号
D3DXVECTOR3 EditPos02;						//エディットモードのオブジェクトの位置
D3DXVECTOR3 EditRot02;						//エディットモードのオブジェクトの向き
int EditType02;								//エディットモードのオブジェクトの種類
int g_ObjectCount02;							//オブジェクトの数

const char *c_apModelObj02[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\wood.x",
	"Data\\MODEL\\rock.x",
	"Data\\MODEL\\Labo.x",
	"Data\\MODEL\\title_field.x",
	"Data\\MODEL\\door_1.x",
	"Data\\MODEL\\door_2.x",
	"Data\\MODEL\\door_huti.x",
};

//====================================================================
//オブジェクトLightの初期化処理
//====================================================================
void InitObjectLight(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		g_ObjectLight[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectLight[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectLight[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectLight[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectLight[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_ObjectLight[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_ObjectLight[nCntObject].bUse = false;
		g_ObjectLight[nCntObject].nType = OBJECTLIGHT_NTYPE00;
		g_ObjectLight[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		g_ObjectLight[nCntObject].LightIdx = -1;
	}
	EditIndex02 = MAX_OBJECTLIGHT - 1;
	EditPos02 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditRot02 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditType02 = 0;
	g_ObjectCount02 = 0;

	//Xファイルの読み込み
	for (int nCntObj = 0; nCntObj < OBJECTLIGHT_NTYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModelObj02[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObjectLight[nCntObj],
			NULL,
			&g_dwNumMatObjectLight[nCntObj],
			&g_pMeshObjectLight[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntNumObject = 0; nCntNumObject < OBJECTLIGHT_NTYPE_MAX; nCntNumObject++)
	{
		//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectLight[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectLight[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObjectLight[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//オブジェクトLightの終了処理
//====================================================================
void UninitObjectLight(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECTLIGHT_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//テクスチャの破棄
			if (g_pTextureObjectLight[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureObjectLight[nCntTex][nCntNumObject]->Release();
				g_pTextureObjectLight[nCntTex][nCntNumObject] = NULL;
			}
		}

		//メッシュの破棄
		if (g_pMeshObjectLight[nCntNumObject] != NULL)
		{
			g_pMeshObjectLight[nCntNumObject]->Release();
			g_pMeshObjectLight[nCntNumObject] = NULL;
		}

		//マテリアルの破棄
		if (g_pBuffMatObjectLight[nCntNumObject] != NULL)
		{
			g_pBuffMatObjectLight[nCntNumObject]->Release();
			g_pBuffMatObjectLight[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//オブジェクトLightの更新処理
//====================================================================
void UpdateObjectLight(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		if (g_ObjectLight[nCntObject].bUse == true)
		{
			//オブジェクトが保持するライトの更新処理
			SetLight(g_ObjectLight[nCntObject].LightIdx, D3DLIGHT_SPOT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(g_ObjectLight[nCntObject].pos.x, g_ObjectLight[nCntObject].pos.y, g_ObjectLight[nCntObject].pos.z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 200.0f, 2.0f);
		}
	}
	PrintDebugProc("背景オブジェクトの数:%d\n", g_ObjectCount02);
}

//====================================================================
//オブジェクトLightの描画処理
//====================================================================
void DrawObjectLight(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_ObjectLight[nCntObject].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectLight[nCntObject].rot.y, g_ObjectLight[nCntObject].rot.x, g_ObjectLight[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_ObjectLight[nCntObject].mtxWorld, &g_ObjectLight[nCntObject].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_ObjectLight[nCntObject].pos.x, g_ObjectLight[nCntObject].pos.y, g_ObjectLight[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_ObjectLight[nCntObject].mtxWorld, &g_ObjectLight[nCntObject].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_ObjectLight[nCntObject].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを所得する
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectLight[g_ObjectLight[nCntObject].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectLight[g_ObjectLight[nCntObject].nType]; nCntMat++)
		{

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_ObjectLight[nCntObject].bUse == true)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureObjectLight[nCntMat][g_ObjectLight[nCntObject].nType]);

				//オブジェクトLight(パーツ)の描画
				g_pMeshObjectLight[g_ObjectLight[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//エディットモードのオブジェクトLightの更新処理
//====================================================================
void UpdateEditObjectLight(void)
{
	//キーボードの移動処理----------
	if (GetKeyboardPress(DIK_UP) == true)
	{//前移動
		EditPos02.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{//後ろ移動
		EditPos02.z -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{//右移動
		EditPos02.x += 1.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//左移動
		EditPos02.x -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{//上移動
		EditPos02.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_RCONTROL) == true)
	{//下移動
		EditPos02.y -= 1.0f;
	}

	//オブジェクトの回転処理
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		EditRot02.y += 1.57f;

		if (EditRot02.y >= 6.28f)
		{
			EditRot02.y = 0.0f;
		}
	}

	//オブジェクトの切り替え処理----------
	if (GetKeyboardTrigger(DIK_9) == true)
	{//９キーで次のタイプのオブジェクトにする
		EditType02++;

		if (EditType02 > OBJECTLIGHT_NTYPE_MAX - 1)
		{
			EditType02 = 0;
		}
	}
	if (GetKeyboardTrigger(DIK_8) == true)
	{//８キーで前のタイプのオブジェクトにする
		EditType02--;

		if (EditType02 < 0)
		{
			EditType02 = OBJECTLIGHT_NTYPE_MAX - 1;
		}
	}

	//エディットモードの変更をオブジェクトに反映させる
	g_ObjectLight[EditIndex02].pos = EditPos02;
	g_ObjectLight[EditIndex02].rot = EditRot02;
	g_ObjectLight[EditIndex02].nType = EditType02;

	//オブジェクトの削除処理(重なっているもの)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObjectLight(g_ObjectLight[EditIndex02].pos, g_ObjectLight[EditIndex02].vtxMin, g_ObjectLight[EditIndex02].vtxMax, 20.0f);
	}

	//オブジェクトの削除処理(CTRL+Z)----------
	if (GetKeyboardTrigger(DIK_Z) == true && GetKeyboardPress(DIK_LCONTROL) == true)
	{
		FalseObjectLight();
	}

	//オブジェクトの設置処理----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObjectLight(g_ObjectLight[EditIndex02].pos, g_ObjectLight[EditIndex02].move, g_ObjectLight[EditIndex02].rot, g_ObjectLight[EditIndex02].nType);
	}
}

//====================================================================
//エディットモードのオブジェクトLightの描画処理
//====================================================================
void DrawEditObjectLight(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ


									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_ObjectLight[EditIndex02].mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectLight[EditIndex02].rot.y, g_ObjectLight[EditIndex02].rot.x, g_ObjectLight[EditIndex02].rot.z);

	D3DXMatrixMultiply(&g_ObjectLight[EditIndex02].mtxWorld, &g_ObjectLight[EditIndex02].mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_ObjectLight[EditIndex02].pos.x, g_ObjectLight[EditIndex02].pos.y, g_ObjectLight[EditIndex02].pos.z);

	D3DXMatrixMultiply(&g_ObjectLight[EditIndex02].mtxWorld, &g_ObjectLight[EditIndex02].mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_ObjectLight[EditIndex02].mtxWorld);

	//現在のマテリアルを所得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを所得する
	pMat = (D3DXMATERIAL*)g_pBuffMatObjectLight[g_ObjectLight[EditIndex02].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectLight[g_ObjectLight[EditIndex02].nType]; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&g_ObjectLight[EditIndex02].pMatE.MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureObjectLight[nCntMat][g_ObjectLight[EditIndex02].nType]);

		//オブジェクトLight(パーツ)の描画
		g_pMeshObjectLight[g_ObjectLight[EditIndex02].nType]->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//オブジェクトLightの設定処理
//====================================================================
void SetObjectLight(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		if (g_ObjectLight[nCntObject].bUse == false)
		{
			g_ObjectLight[nCntObject].pos = pos;
			g_ObjectLight[nCntObject].posOld = pos;
			g_ObjectLight[nCntObject].move = move;
			g_ObjectLight[nCntObject].rot = rot;
			g_ObjectLight[nCntObject].nType = nType;
			g_ObjectLight[nCntObject].LightIdx = SetIndexLight();		//ライトのセット処理

			g_ObjectLight[nCntObject].bUse = true;
			g_ObjectCount02++;

			//if (g_ObjectLight[nCntObject].nType != 0)
			//{
			int nNumVtx;		//頂点数
			DWORD dwSizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;		//頂点バッファへのポインタ

			//頂点数を所得
			nNumVtx = g_pMeshObjectLight[nType]->GetNumVertices();

			//頂点フォーマットのサイズを所得
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObjectLight[nType]->GetFVF());

			//頂点バッファをロック
			g_pMeshObjectLight[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				if (g_ObjectLight[nCntObject].vtxMin.x > vtx.x)
				{
					g_ObjectLight[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_ObjectLight[nCntObject].vtxMin.y > vtx.y)
				{
					g_ObjectLight[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_ObjectLight[nCntObject].vtxMin.z > vtx.z)
				{
					g_ObjectLight[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_ObjectLight[nCntObject].vtxMax.x < vtx.x)
				{
					g_ObjectLight[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_ObjectLight[nCntObject].vtxMax.y < vtx.y)
				{
					g_ObjectLight[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_ObjectLight[nCntObject].vtxMax.z < vtx.z)
				{
					g_ObjectLight[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshObjectLight[nType]->UnlockVertexBuffer();
			//}
			//else
			//{
			//	g_ObjectLight[nCntObject].vtxMin = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
			//	g_ObjectLight[nCntObject].vtxMax = D3DXVECTOR3(100.0f, 150.0f, 5.0f);
			//}


			CollisionRotObjectLight(nCntObject);

			break;
		}
	}
}

//====================================================================
//オブジェクトLightの削除処理
//====================================================================
void FalseObjectLight(void)
{
	int nCntObject;

	for (nCntObject = MAX_OBJECTLIGHT; nCntObject >= 0; nCntObject--)
	{
		if (g_ObjectLight[nCntObject].bUse == true)
		{
			g_ObjectLight[nCntObject].bUse = false;
			break;
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool EditCollisionObjectLight(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		if (g_ObjectLight[nCntObject].bUse == true)
		{
			if (
				pPos.y + Size >= g_ObjectLight[nCntObject].pos.y + g_ObjectLight[nCntObject].vtxMin.y && pPos.y - Size <= g_ObjectLight[nCntObject].pos.y + g_ObjectLight[nCntObject].vtxMax.y &&
				pPos.x + Size >= g_ObjectLight[nCntObject].pos.x + g_ObjectLight[nCntObject].vtxMin.x && pPos.x - Size <= g_ObjectLight[nCntObject].pos.x + g_ObjectLight[nCntObject].vtxMax.x &&
				pPos.z + Size >= g_ObjectLight[nCntObject].pos.z + g_ObjectLight[nCntObject].vtxMin.z && pPos.z - Size <= g_ObjectLight[nCntObject].pos.z + g_ObjectLight[nCntObject].vtxMax.z
				)
			{//オブジェクト同士が重なっている
				g_ObjectLight[nCntObject].bUse = false;

				bON = true;
			}
		}
	}
	return bON;
}

//====================================================================
//オブジェクトの当たり判定を回転させる処理
//====================================================================
void CollisionRotObjectLight(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_ObjectLight[nCnt].vtxMax.z;
	MaxX = g_ObjectLight[nCnt].vtxMax.x;
	MinZ = g_ObjectLight[nCnt].vtxMin.z;
	MinX = g_ObjectLight[nCnt].vtxMin.x;


	if (g_ObjectLight[nCnt].rot.y <= 0.0f)
	{
		g_ObjectLight[nCnt].vtxMax.z = MaxZ;
		g_ObjectLight[nCnt].vtxMax.x = MaxX;
		g_ObjectLight[nCnt].vtxMin.z = MinZ;
		g_ObjectLight[nCnt].vtxMin.x = MinX;
	}
	else if (g_ObjectLight[nCnt].rot.y <= 1.57f)
	{
		g_ObjectLight[nCnt].vtxMax.z = -MinX;
		g_ObjectLight[nCnt].vtxMax.x = MaxZ;
		g_ObjectLight[nCnt].vtxMin.z = -MaxX;
		g_ObjectLight[nCnt].vtxMin.x = MinZ;
	}
	else if (g_ObjectLight[nCnt].rot.y <= 3.14f)
	{
		g_ObjectLight[nCnt].vtxMax.z = -MinZ;
		g_ObjectLight[nCnt].vtxMax.x = -MinX;
		g_ObjectLight[nCnt].vtxMin.z = -MaxZ;
		g_ObjectLight[nCnt].vtxMin.x = -MaxX;
	}
	else if (g_ObjectLight[nCnt].rot.y <= 4.71f)
	{
		g_ObjectLight[nCnt].vtxMax.z = MaxX;
		g_ObjectLight[nCnt].vtxMax.x = -MinZ;
		g_ObjectLight[nCnt].vtxMin.z = MinX;
		g_ObjectLight[nCnt].vtxMin.x = -MaxZ;
	}
}

//====================================================================
//影との当たり判定処理
//====================================================================
void CollisionObjectLightShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		if (g_ObjectLight[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_ObjectLight[nCntObject].pos.y + g_ObjectLight[nCntObject].vtxMin.y &&
				pPos->y <= g_ObjectLight[nCntObject].pos.y + g_ObjectLight[nCntObject].vtxMax.y &&
				pPos->x >= g_ObjectLight[nCntObject].pos.x + g_ObjectLight[nCntObject].vtxMin.x &&
				pPos->x <= g_ObjectLight[nCntObject].pos.x + g_ObjectLight[nCntObject].vtxMax.x &&
				pPos->z >= g_ObjectLight[nCntObject].pos.z + g_ObjectLight[nCntObject].vtxMin.z &&
				pPos->z <= g_ObjectLight[nCntObject].pos.z + g_ObjectLight[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = g_ObjectLight[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//オブジェクトLightの所得
//====================================================================
ObjectLight * GetObjectLight(void)
{
	return &g_ObjectLight[0];
}