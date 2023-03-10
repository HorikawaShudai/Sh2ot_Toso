//========================================================================================
//
// オブジェクトの処理[ObjectWall.cpp]
// Author: 坂本　翔唯
// Author: 丹野竜之介
//
//========================================================================================
#include "main.h"
#include "ObjectWall.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "score.h"

#define OBJECTWALL_LIFE (7)		//オブジェクトの体力
#define FALSE_SIZE (10.0f)		//エディットモードのバックスペースの判定の大きさ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureObjectWall[64][OBJECTWALL_NTYPE_MAX] = {};		//テクスチャのポインタ
LPD3DXMESH g_pMeshObjectWall[OBJECTWALL_NTYPE_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatObjectWall[OBJECTWALL_NTYPE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatObjectWall[OBJECTWALL_NTYPE_MAX] = {};						//マテリアルの数

ObjectWall g_ObjectWall[MAX_OBJECTWALL];				//オブジェクト00の情報
int EditIndex03;									//エディットモード用の番号
D3DXVECTOR3 EditPos03;							//エディットモードのオブジェクトの位置
D3DXVECTOR3 EditRot03;							//エディットモードのオブジェクトの向き
int EditType03;									//エディットモードのオブジェクトの種類
int g_ObjectWallCount;								//オブジェクトの数

const char *c_apModelWallObj[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\tyuPolyWall.x",				//ポリゴン数の多い壁
	"Data\\MODEL\\tyuPolyWall1.x",				//壁(メインホール)
	"Data\\MODEL\\tyuPolyWall2.x",				//壁(ノーマルコンクリ)
	"Data\\MODEL\\tyuPolyWall3.x",				//壁(雨濡れコンクリ)
	"Data\\MODEL\\tyuPolyWall4.x",				//壁(白タイル)
};

//====================================================================
//オブジェクト00の初期化処理
//====================================================================
void InitObjectWall(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		g_ObjectWall[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectWall[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectWall[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectWall[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectWall[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_ObjectWall[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_ObjectWall[nCntObject].bUse = false;
		g_ObjectWall[nCntObject].nType = OBJECTWALL_NTYPE00;
		g_ObjectWall[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	}
	EditIndex03 = MAX_OBJECTWALL - 1;
	EditPos03 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditRot03 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditType03 = 0;
	g_ObjectWallCount = 0;

	//Xファイルの読み込み
	for (int nCntObj = 0; nCntObj < OBJECTWALL_NTYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModelWallObj[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObjectWall[nCntObj],
			NULL,
			&g_dwNumMatObjectWall[nCntObj],
			&g_pMeshObjectWall[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntNumObject = 0; nCntNumObject < OBJECTWALL_NTYPE_MAX; nCntNumObject++)
	{
		//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectWall[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectWall[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObjectWall[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//オブジェクト00の終了処理
//====================================================================
void UninitObjectWall(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECTWALL_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//テクスチャの破棄
			if (g_pTextureObjectWall[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureObjectWall[nCntTex][nCntNumObject]->Release();
				g_pTextureObjectWall[nCntTex][nCntNumObject] = NULL;
			}
		}

		//メッシュの破棄
		if (g_pMeshObjectWall[nCntNumObject] != NULL)
		{
			g_pMeshObjectWall[nCntNumObject]->Release();
			g_pMeshObjectWall[nCntNumObject] = NULL;
		}

		//マテリアルの破棄
		if (g_pBuffMatObjectWall[nCntNumObject] != NULL)
		{
			g_pBuffMatObjectWall[nCntNumObject]->Release();
			g_pBuffMatObjectWall[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//オブジェクト00の更新処理
//====================================================================
void UpdateObjectWall(void)
{
#ifdef _DEBUG
	PrintDebugProc("壁オブジェクトの数:%d\n", g_ObjectWallCount);
#endif // _DEBUG
}

//====================================================================
//オブジェクト00の描画処理
//====================================================================
void DrawObjectWall(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_ObjectWall[nCntObject].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectWall[nCntObject].rot.y, g_ObjectWall[nCntObject].rot.x, g_ObjectWall[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_ObjectWall[nCntObject].mtxWorld, &g_ObjectWall[nCntObject].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_ObjectWall[nCntObject].pos.x, g_ObjectWall[nCntObject].pos.y, g_ObjectWall[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_ObjectWall[nCntObject].mtxWorld, &g_ObjectWall[nCntObject].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_ObjectWall[nCntObject].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを所得する
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectWall[g_ObjectWall[nCntObject].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectWall[g_ObjectWall[nCntObject].nType]; nCntMat++)
		{

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_ObjectWall[nCntObject].bUse == true)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureObjectWall[nCntMat][g_ObjectWall[nCntObject].nType]);

				//オブジェクト00(パーツ)の描画
				g_pMeshObjectWall[g_ObjectWall[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//エディットモードのオブジェクト00の更新処理
//====================================================================
void UpdateEditObjectWall(void)
{
	//キーボードの移動処理----------
		if (GetKeyboardTrigger(DIK_UP) == true)
		{//前移動
			EditPos03.z += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{//後ろ移動
			EditPos03.z -= 100.0f;
		}
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{//右移動
			EditPos03.x += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{//左移動
			EditPos03.x -= 100.0f;
		}

	//オブジェクトの回転処理
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		EditRot03.y += 1.57f;

		if (EditRot03.y >= 6.28f)
		{
			EditRot03.y = 0.0f;
		}
	}

	//オブジェクトの切り替え処理----------
	if (GetKeyboardTrigger(DIK_9) == true)
	{//９キーで次のタイプのオブジェクトにする
		EditType03++;

		if (EditType03 > OBJECTWALL_NTYPE_MAX - 1)
		{
			EditType03 = 0;
		}

	}
	if (GetKeyboardTrigger(DIK_8) == true)
	{//８キーで前のタイプのオブジェクトにする
		EditType03--;

		if (EditType03 < 0)
		{
			EditType03 = OBJECTWALL_NTYPE_MAX - 1;
		}
	}

	//エディットモードの変更をオブジェクトに反映させる
	g_ObjectWall[EditIndex03].pos = EditPos03;
	g_ObjectWall[EditIndex03].rot = EditRot03;
	g_ObjectWall[EditIndex03].nType = EditType03;

	//オブジェクトの削除処理(重なっているもの)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObjectWall(D3DXVECTOR3(EditPos03.x, EditPos03.y + 0.0f, EditPos03.z), g_ObjectWall[EditIndex03].vtxMin, g_ObjectWall[EditIndex03].vtxMax, FALSE_SIZE);
	}

	//オブジェクトの削除処理(CTRL+Z)----------
	if (GetKeyboardTrigger(DIK_Z) == true && GetKeyboardPress(DIK_LCONTROL) == true)
	{
		FalseObjectWall();
	}

	//オブジェクトの設置処理----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObjectWall(g_ObjectWall[EditIndex03].pos, g_ObjectWall[EditIndex03].move, g_ObjectWall[EditIndex03].rot, g_ObjectWall[EditIndex03].nType);
	}
}

//====================================================================
//エディットモードのオブジェクト00の描画処理
//====================================================================
void DrawEditObjectWall(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ


	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_ObjectWall[EditIndex03].mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectWall[EditIndex03].rot.y, g_ObjectWall[EditIndex03].rot.x, g_ObjectWall[EditIndex03].rot.z);

	D3DXMatrixMultiply(&g_ObjectWall[EditIndex03].mtxWorld, &g_ObjectWall[EditIndex03].mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_ObjectWall[EditIndex03].pos.x, g_ObjectWall[EditIndex03].pos.y, g_ObjectWall[EditIndex03].pos.z);

	D3DXMatrixMultiply(&g_ObjectWall[EditIndex03].mtxWorld, &g_ObjectWall[EditIndex03].mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_ObjectWall[EditIndex03].mtxWorld);

	//現在のマテリアルを所得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを所得する
	pMat = (D3DXMATERIAL*)g_pBuffMatObjectWall[g_ObjectWall[EditIndex03].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectWall[g_ObjectWall[EditIndex03].nType]; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&g_ObjectWall[EditIndex03].pMatE.MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureObjectWall[nCntMat][g_ObjectWall[EditIndex03].nType]);

		//オブジェクト00(パーツ)の描画
		g_pMeshObjectWall[g_ObjectWall[EditIndex03].nType]->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//オブジェクト00の設定処理
//====================================================================
void SetObjectWall(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		if (g_ObjectWall[nCntObject].bUse == false)
		{
			g_ObjectWall[nCntObject].pos = pos;
			g_ObjectWall[nCntObject].posOld = pos;
			g_ObjectWall[nCntObject].move = move;
			g_ObjectWall[nCntObject].rot = rot;
			g_ObjectWall[nCntObject].nType = nType;

			g_ObjectWall[nCntObject].bUse = true;
			g_ObjectWallCount++;

			//if (g_Exit[nCntObject].nType != 0)
			//{
			int nNumVtx;		//頂点数
			DWORD dwSizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;		//頂点バッファへのポインタ

			//頂点数を所得
			nNumVtx = g_pMeshObjectWall[nType]->GetNumVertices();

			//頂点フォーマットのサイズを所得
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObjectWall[nType]->GetFVF());

			//頂点バッファをロック
			g_pMeshObjectWall[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				if (g_ObjectWall[nCntObject].vtxMin.x > vtx.x)
				{
					g_ObjectWall[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_ObjectWall[nCntObject].vtxMin.y > vtx.y)
				{
					g_ObjectWall[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_ObjectWall[nCntObject].vtxMin.z > vtx.z)
				{
					g_ObjectWall[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_ObjectWall[nCntObject].vtxMax.x < vtx.x)
				{
					g_ObjectWall[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_ObjectWall[nCntObject].vtxMax.y < vtx.y)
				{
					g_ObjectWall[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_ObjectWall[nCntObject].vtxMax.z < vtx.z)
				{
					g_ObjectWall[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshObjectWall[nType]->UnlockVertexBuffer();
			//}
			//else
			//{
			//	g_Exit[nCntObject].vtxMin = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
			//	g_Exit[nCntObject].vtxMax = D3DXVECTOR3(100.0f, 150.0f, 5.0f);
			//}

			CollisionRotObjectWall(nCntObject);

			if (nType == 58)
			{
				int a = 0;
			}

			break;
		}
	}
}

//====================================================================
//オブジェクト00の削除処理
//====================================================================
void FalseObjectWall(void)
{
	int nCntObject;

	for (nCntObject = MAX_OBJECTWALL; nCntObject >= 0; nCntObject--)
	{
		if (g_ObjectWall[nCntObject].bUse == true)
		{
			g_ObjectWall[nCntObject].bUse = false;
			g_ObjectWallCount--;
			break;
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool EditCollisionObjectWall(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		if (g_ObjectWall[nCntObject].bUse == true)
		{
			if (
				pPos.y + Size >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y
				&& pPos.y - Size <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y
				&& pPos.x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x
				&& pPos.x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x
				&& pPos.z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z
				&& pPos.z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z
				)
			{//オブジェクト同士が重なっている
				g_ObjectWall[nCntObject].bUse = false;
				g_ObjectWallCount--;
				bON = true;
			}
		}
	}
	return bON;
}

//====================================================================
//オブジェクトの当たり判定を回転させる処理
//====================================================================
void CollisionRotObjectWall(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_ObjectWall[nCnt].vtxMax.z;
	MaxX = g_ObjectWall[nCnt].vtxMax.x;
	MinZ = g_ObjectWall[nCnt].vtxMin.z;
	MinX = g_ObjectWall[nCnt].vtxMin.x;


	if (g_ObjectWall[nCnt].rot.y <= 0.0f)
	{
		g_ObjectWall[nCnt].vtxMax.z = MaxZ;
		g_ObjectWall[nCnt].vtxMax.x = MaxX;
		g_ObjectWall[nCnt].vtxMin.z = MinZ;
		g_ObjectWall[nCnt].vtxMin.x = MinX;
	}
	else if (g_ObjectWall[nCnt].rot.y <= 1.57f)
	{
		g_ObjectWall[nCnt].vtxMax.z = -MinX;
		g_ObjectWall[nCnt].vtxMax.x = MaxZ;
		g_ObjectWall[nCnt].vtxMin.z = -MaxX;
		g_ObjectWall[nCnt].vtxMin.x = MinZ;
	}
	else if (g_ObjectWall[nCnt].rot.y <= 3.14f)
	{
		g_ObjectWall[nCnt].vtxMax.z = -MinZ;
		g_ObjectWall[nCnt].vtxMax.x = -MinX;
		g_ObjectWall[nCnt].vtxMin.z = -MaxZ;
		g_ObjectWall[nCnt].vtxMin.x = -MaxX;
	}
	else if (g_ObjectWall[nCnt].rot.y <= 4.71f)
	{
		g_ObjectWall[nCnt].vtxMax.z = MaxX;
		g_ObjectWall[nCnt].vtxMax.x = -MinZ;
		g_ObjectWall[nCnt].vtxMin.z = MinX;
		g_ObjectWall[nCnt].vtxMin.x = -MaxZ;
	}
}

//====================================================================
//外積を使ったオブジェクトの当たり判定
//====================================================================
D3DXVECTOR3 CollisionOuterProductObjectWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	//移動ベクトルを割り出す
	D3DXVECTOR3 vecMove = *pPos - *pPosOld;
	//座標保管用
	int nPosCount = 0;
	D3DXVECTOR3 pos[MAX_OBJECTWALL * 4] = {};
	for (int nCnt = 0; nCnt < MAX_OBJECTWALL; nCnt++)
	{
		if (g_ObjectWall[nCnt].bUse == true)
		{
			for (int nLine = 0; nLine < 4; nLine++)
			{
				bool bHit = false;
				bool bHit1 = false;
				bool bHit2 = false;

				D3DXVECTOR3 pos0, pos1;
				switch (nLine)
				{//紙片の当たり判定
				case 0:
					pos0 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMin.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMax.z);
					pos1 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMax.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMax.z);
					break;
				case 1:
					pos0 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMax.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMax.z);
					pos1 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMax.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMin.z);
					break;
				case 2:
					pos0 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMax.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMin.z);
					pos1 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMin.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMin.z);
					break;
				case 3:
					pos0 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMin.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMin.z);
					pos1 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMin.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMax.z);
					break;
				default:
					break;
				}

				//ベクトルの目標地点

				D3DXVECTOR3 vecLine = pos1 - pos0;

				D3DXVECTOR3 vecToPos = *pPos - pos0;

				D3DXVECTOR3 vecToPos2 = *pPosOld - pos0;

				float A, B, fRate;
				A = (vecToPos.z * vecMove.x) - (vecToPos.x * vecMove.z);
				B = (vecLine.z * vecMove.x) - (vecLine.x * vecMove.z);
				if (B != 0)
				{
					fRate = A / B;
				}
				else
				{
					fRate = 10.0f;
				}

				if (fRate >= 0.0f &&fRate <= 1.0f)
				{//vecLineを横切ったとき
					if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) < 0)
					{
						bHit1 = true;
					}

					if ((vecLine.z * vecToPos2.x) - (vecLine.x * vecToPos2.z) < 0)
					{
						bHit2 = true;
					}

					if (bHit1 != bHit2)
					{
						bHit = true;
					}

					bHit1 = false;
					bHit2 = false;

					if ((vecLine.z * vecToPos.x) + (vecLine.x * vecToPos.z) > 0)
					{
						bHit1 = true;
					}

					if ((vecLine.z * vecToPos2.x) + (vecLine.x * vecToPos2.z) > 0)
					{
						bHit2 = true;
					}

					if (bHit1 != bHit2)
					{
						bHit = true;
					}
				}
				if (bHit == true)
				{
					pos[nPosCount] = pos0 + vecLine*fRate;
					nPosCount++;
				}
			}
		}

	}
	if (nPosCount > 1)
	{
		for (int nCheck = 0; nCheck < nPosCount - 1; nCheck++)
		{//距離の差を割り出して昇順にソート

			for (int nCnt = (nCheck + 1); nCnt < nPosCount; nCnt++)
			{
				D3DXVECTOR3 Temp = pos[nCnt];
				float fDis1, fDis2;
				fDis1 = (pos[nCheck].x - pPosOld->x) + (pos[nCheck].z - pPosOld->z);
				fDis2 = (pos[nCnt].x - pPosOld->x) + (pos[nCnt].z - pPosOld->z);
				if (fDis1 < 0)
				{
					fDis1 *= -1.0f;
				}
				if (fDis2 < 0)
				{
					fDis2 *= -1.0f;
				}
				if (fDis1 > fDis2)
				{
					pos[nCnt] = pos[nCheck];
					pos[nCheck] = Temp;
				}
			}
		}
		
	}
	if (nPosCount > 0)
	{
		return pos[0];
	}
	
	return D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	
}
//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool CollisionObjectWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		if (g_ObjectWall[nCntObject].bUse == true)
		{
			if (
				(
					pPos->y + max.y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y && pPosOld->y + max.y< g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y ||
					pPos->y + min.y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y && pPosOld->y + min.y > g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y) &&
				pPos->x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x &&
				pPos->z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bHit = true;
			}

			if (fabsf(pMove->x) >= fabsf(pMove->z))
			{
				if (
					(
						pPos->z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z && pPosOld->z + Size < g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z ||
						pPos->z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z && pPosOld->z - Size > g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z) &&
					pPos->x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x &&
					pPos->x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x &&
					pPos->y + max.y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y&&
					pPos->y + min.y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y
					)
				{//壁とプレイヤーが当たった(Z軸)
					pPos->z = pPosOld->z;
					pMove->z = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x && pPosOld->x + Size < g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x ||
						pPos->x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x && pPosOld->x - Size > g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x) &&
					pPos->z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z &&
					pPos->z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z &&
					pPos->y + max.y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y &&
					pPos->y + min.y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y
					)
				{//壁とプレイヤーが当たった(X軸)
					pPos->x = pPosOld->x;
					pMove->x = 0.0f;
					bHit = true;
				}
			}
			else
			{
				if (
					(
						pPos->x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x && pPosOld->x + Size < g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x ||
						pPos->x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x && pPosOld->x - Size > g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x) &&
					pPos->z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z &&
					pPos->z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z &&
					pPos->y + max.y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y &&
					pPos->y + min.y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y
					)
				{//壁とプレイヤーが当たった(X軸)
					pPos->x = pPosOld->x;
					pMove->x = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z && pPosOld->z + Size < g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z ||
						pPos->z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z && pPosOld->z - Size > g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z) &&
					pPos->x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x &&
					pPos->x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x &&
					pPos->y + max.y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y&&
					pPos->y + min.y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y
					)
				{//壁とプレイヤーが当たった(Z軸)
					pPos->z = pPosOld->z;
					pMove->z = 0.0f;
					bHit = true;
				}
			}
		}
	}
	return bHit;
}

//====================================================================
//影との当たり判定処理
//====================================================================
void CollisionObjectWallShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		if (g_ObjectWall[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y &&
				pPos->y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y &&
				pPos->x >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x &&
				pPos->x <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x &&
				pPos->z >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z &&
				pPos->z <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = g_ObjectWall[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//オブジェクト00の所得
//====================================================================
ObjectWall * GetObjectWall(void)
{
	return &g_ObjectWall[0];
}