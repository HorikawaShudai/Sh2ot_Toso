#include "main.h"
#include "bg_object.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

#define OBJECT00_LIFE (7)		//オブジェクトの体力

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBg_object[64][OBJECT00_NTYPE_MAX] = {};		//テクスチャのポインタ
LPD3DXMESH g_pMeshBg_object[OBJECT00_NTYPE_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatBg_object[OBJECT00_NTYPE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatBg_object[OBJECT00_NTYPE_MAX] = {};						//マテリアルの数

Object00 g_Bg_object[MAX_OBJECT00];					//オブジェクト00の情報
int EditIndex01;								//エディットモード用の番号
D3DXVECTOR3 EditPos01;						//エディットモードのオブジェクトの位置
D3DXVECTOR3 EditRot01;						//エディットモードのオブジェクトの向き
int EditType01;								//エディットモードのオブジェクトの種類
int g_ObjectCount01;							//オブジェクトの数

const char *c_apModelObj01[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\wood.x",
	"Data\\MODEL\\rock.x",
	
};

//====================================================================
//オブジェクト00の初期化処理
//====================================================================
void InitBg_object(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		g_Bg_object[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bg_object[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bg_object[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bg_object[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bg_object[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Bg_object[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Bg_object[nCntObject].bUse = false;
		g_Bg_object[nCntObject].nType = OBJECT00_NTYPE00;
		g_Bg_object[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	}
	EditIndex01 = 0;
	EditPos01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditRot01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditType01 = 0;
	g_ObjectCount01 = 0;

	//Xファイルの読み込み
	for (int nCntObj = 0; nCntObj < OBJECT00_NTYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModelObj01[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatBg_object[nCntObj],
			NULL,
			&g_dwNumMatBg_object[nCntObj],
			&g_pMeshBg_object[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntNumObject = 0; nCntNumObject < OBJECT00_NTYPE_MAX; nCntNumObject++)
	{
		//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatBg_object[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBg_object[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureBg_object[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//オブジェクト00の終了処理
//====================================================================
void UninitBg_object(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECT00_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//テクスチャの破棄
			if (g_pTextureBg_object[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureBg_object[nCntTex][nCntNumObject]->Release();
				g_pTextureBg_object[nCntTex][nCntNumObject] = NULL;
			}
		}

		//メッシュの破棄
		if (g_pMeshBg_object[nCntNumObject] != NULL)
		{
			g_pMeshBg_object[nCntNumObject]->Release();
			g_pMeshBg_object[nCntNumObject] = NULL;
		}

		//マテリアルの破棄
		if (g_pBuffMatBg_object[nCntNumObject] != NULL)
		{
			g_pBuffMatBg_object[nCntNumObject]->Release();
			g_pBuffMatBg_object[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//オブジェクト00の更新処理
//====================================================================
void UpdateBg_object(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Bg_object[nCntObject].bUse == true)
		{

		}
	}
	PrintDebugProc("オブジェクトの数:%d\n", g_ObjectCount01);
}

//====================================================================
//オブジェクト00の描画処理
//====================================================================
void DrawBg_object(void)
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
		D3DXMatrixIdentity(&g_Bg_object[nCntObject].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Bg_object[nCntObject].rot.y, g_Bg_object[nCntObject].rot.x, g_Bg_object[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_Bg_object[nCntObject].mtxWorld, &g_Bg_object[nCntObject].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Bg_object[nCntObject].pos.x, g_Bg_object[nCntObject].pos.y, g_Bg_object[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_Bg_object[nCntObject].mtxWorld, &g_Bg_object[nCntObject].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Bg_object[nCntObject].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを所得する
		pMat = (D3DXMATERIAL*)g_pBuffMatBg_object[g_Bg_object[nCntObject].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBg_object[g_Bg_object[nCntObject].nType]; nCntMat++)
		{

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_Bg_object[nCntObject].bUse == true)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBg_object[nCntMat][g_Bg_object[nCntObject].nType]);

				//オブジェクト00(パーツ)の描画
				g_pMeshBg_object[g_Bg_object[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//エディットモードのオブジェクト00の更新処理
//====================================================================
void UpdateEditBg_object(void)
{
	//キーボードの移動処理----------
	if (g_Bg_object[EditIndex01].nType == 0)
	{//選択されているオブジェクトが壁の時
		if (GetKeyboardTrigger(DIK_UP) == true)
		{//前移動
			EditPos01.z += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{//後ろ移動
			EditPos01.z -= 100.0f;
		}
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{//右移動
			EditPos01.x += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{//左移動
			EditPos01.x -= 100.0f;
		}
	}

	if (g_Bg_object[EditIndex01].nType != 0)
	{//選択されているオブジェクトが壁以外の時
		if (GetKeyboardPress(DIK_UP) == true)
		{//前移動
			EditPos01.z += 1.0f;
		}
		if (GetKeyboardPress(DIK_DOWN) == true)
		{//後ろ移動
			EditPos01.z -= 1.0f;
		}
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{//右移動
			EditPos01.x += 1.0f;
		}
		if (GetKeyboardPress(DIK_LEFT) == true)
		{//左移動
			EditPos01.x -= 1.0f;
		}
		if (GetKeyboardPress(DIK_RSHIFT) == true)
		{//上移動
			EditPos01.y += 1.0f;
		}
		if (GetKeyboardPress(DIK_RCONTROL) == true)
		{//下移動
			EditPos01.y -= 1.0f;
		}
	}

	//オブジェクトの回転処理
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		EditRot01.y += 1.57f;

		if (EditRot01.y >= 6.28f)
		{
			EditRot01.y = 0.0f;
		}
	}

	//オブジェクトの切り替え処理----------
	if (GetKeyboardTrigger(DIK_9) == true)
	{//９キーで次のタイプのオブジェクトにする
		EditType01++;

		if (EditType01 > OBJECT00_NTYPE_MAX - 1)
		{
			EditType01 = 0;
		}

		if (EditType01 == 0)
		{
			EditPos01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
	if (GetKeyboardTrigger(DIK_8) == true)
	{//８キーで前のタイプのオブジェクトにする
		EditType01--;

		if (EditType01 < 0)
		{
			EditType01 = OBJECT00_NTYPE_MAX - 1;
		}

		if (EditType01 == 0)
		{
			EditPos01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	//エディットモードの変更をオブジェクトに反映させる
	g_Bg_object[EditIndex01].pos = EditPos01;
	g_Bg_object[EditIndex01].rot = EditRot01;
	g_Bg_object[EditIndex01].nType = EditType01;

	//オブジェクトの削除処理(重なっているもの)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionBg_object(g_Bg_object[EditIndex01].pos, g_Bg_object[EditIndex01].vtxMin, g_Bg_object[EditIndex01].vtxMax, 20.0f);
	}

	//オブジェクトの削除処理(CTRL+Z)----------
	if (GetKeyboardTrigger(DIK_Z) == true && GetKeyboardPress(DIK_LCONTROL) == true)
	{
		FalseBg_object();
	}

	//オブジェクトの設置処理----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetBg_object(g_Bg_object[EditIndex01].pos, g_Bg_object[EditIndex01].move, g_Bg_object[EditIndex01].rot, g_Bg_object[EditIndex01].nType);
	}
}

//====================================================================
//エディットモードのオブジェクト00の描画処理
//====================================================================
void DrawEditBg_object(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ


									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Bg_object[EditIndex01].mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Bg_object[EditIndex01].rot.y, g_Bg_object[EditIndex01].rot.x, g_Bg_object[EditIndex01].rot.z);

	D3DXMatrixMultiply(&g_Bg_object[EditIndex01].mtxWorld, &g_Bg_object[EditIndex01].mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Bg_object[EditIndex01].pos.x, g_Bg_object[EditIndex01].pos.y, g_Bg_object[EditIndex01].pos.z);

	D3DXMatrixMultiply(&g_Bg_object[EditIndex01].mtxWorld, &g_Bg_object[EditIndex01].mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Bg_object[EditIndex01].mtxWorld);

	//現在のマテリアルを所得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを所得する
	pMat = (D3DXMATERIAL*)g_pBuffMatBg_object[g_Bg_object[EditIndex01].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBg_object[g_Bg_object[EditIndex01].nType]; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&g_Bg_object[EditIndex01].pMatE.MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBg_object[nCntMat][g_Bg_object[EditIndex01].nType]);

		//オブジェクト00(パーツ)の描画
		g_pMeshBg_object[g_Bg_object[EditIndex01].nType]->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//オブジェクト00の設定処理
//====================================================================
void SetBg_object(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Bg_object[nCntObject].bUse == false)
		{
			g_Bg_object[nCntObject].pos = pos;
			g_Bg_object[nCntObject].posOld = pos;
			g_Bg_object[nCntObject].move = move;
			g_Bg_object[nCntObject].rot = rot;
			g_Bg_object[nCntObject].nType = nType;

			g_Bg_object[nCntObject].bUse = true;
			EditIndex01++;
			g_ObjectCount01++;

			//if (g_Object00[nCntObject].nType != 0)
			//{
			int nNumVtx;		//頂点数
			DWORD dwSizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;		//頂点バッファへのポインタ

								//頂点数を所得
			nNumVtx = g_pMeshBg_object[nType]->GetNumVertices();

			//頂点フォーマットのサイズを所得
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshBg_object[nType]->GetFVF());

			//頂点バッファをロック
			g_pMeshBg_object[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				if (g_Bg_object[nCntObject].vtxMin.x > vtx.x)
				{
					g_Bg_object[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_Bg_object[nCntObject].vtxMin.y > vtx.y)
				{
					g_Bg_object[nCntObject].vtxMin.y = vtx.y;
				}	  
				if (g_Bg_object[nCntObject].vtxMin.z > vtx.z)
				{	  
					g_Bg_object[nCntObject].vtxMin.z = vtx.z;
				}	  
					  
				if (g_Bg_object[nCntObject].vtxMax.x < vtx.x)
				{	  
					g_Bg_object[nCntObject].vtxMax.x = vtx.x;
				}	  
				if (g_Bg_object[nCntObject].vtxMax.y < vtx.y)
				{	  
					g_Bg_object[nCntObject].vtxMax.y = vtx.y;
				}	  
				if (g_Bg_object[nCntObject].vtxMax.z < vtx.z)
				{	  
					g_Bg_object[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshBg_object[nType]->UnlockVertexBuffer();
			//}
			//else
			//{
			//	g_Object00[nCntObject].vtxMin = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
			//	g_Object00[nCntObject].vtxMax = D3DXVECTOR3(100.0f, 150.0f, 5.0f);
			//}


			CollisionRotBg_object(nCntObject);

			break;
		}
	}
}

//====================================================================
//オブジェクト00の削除処理
//====================================================================
void FalseBg_object(void)
{
	int nCntObject;

	for (nCntObject = MAX_OBJECT00; nCntObject >= 0; nCntObject--)
	{
		if (g_Bg_object[nCntObject].bUse == true)
		{
			g_Bg_object[nCntObject].bUse = false;
			EditIndex01--;
			break;
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool EditCollisionBg_object(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Bg_object[nCntObject].bUse == true)
		{
			if (
				pPos.y + Size >= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y && pPos.y - Size <= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y &&
				pPos.x + Size >= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x && pPos.x - Size <= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x &&
				pPos.z + Size >= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z && pPos.z - Size <= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z
				)
			{//オブジェクト同士が重なっている
				g_Bg_object[nCntObject].bUse = false;

				bON = true;
			}
		}
	}
	return bON;
}

//====================================================================
//オブジェクトの当たり判定を回転させる処理
//====================================================================
void CollisionRotBg_object(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_Bg_object[nCnt].vtxMax.z;
	MaxX = g_Bg_object[nCnt].vtxMax.x;
	MinZ = g_Bg_object[nCnt].vtxMin.z;
	MinX = g_Bg_object[nCnt].vtxMin.x;


	if (g_Bg_object[nCnt].rot.y <= 0.0f)
	{
		g_Bg_object[nCnt].vtxMax.z = MaxZ;
		g_Bg_object[nCnt].vtxMax.x = MaxX;
		g_Bg_object[nCnt].vtxMin.z = MinZ;
		g_Bg_object[nCnt].vtxMin.x = MinX;
	}
	else if (g_Bg_object[nCnt].rot.y <= 1.57f)
	{
		g_Bg_object[nCnt].vtxMax.z = -MinX;
		g_Bg_object[nCnt].vtxMax.x = MaxZ;
		g_Bg_object[nCnt].vtxMin.z = -MaxX;
		g_Bg_object[nCnt].vtxMin.x = MinZ;
	}
	else if (g_Bg_object[nCnt].rot.y <= 3.14f)
	{
		g_Bg_object[nCnt].vtxMax.z = -MinZ;
		g_Bg_object[nCnt].vtxMax.x = -MinX;
		g_Bg_object[nCnt].vtxMin.z = -MaxZ;
		g_Bg_object[nCnt].vtxMin.x = -MaxX;
	}
	else if (g_Bg_object[nCnt].rot.y <= 4.71f)
	{
		g_Bg_object[nCnt].vtxMax.z = MaxX;
		g_Bg_object[nCnt].vtxMax.x = -MinZ;
		g_Bg_object[nCnt].vtxMin.z = MinX;
		g_Bg_object[nCnt].vtxMin.x = -MaxZ;
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool CollisionBg_object(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Bg_object[nCntObject].bUse == true)
		{
			if (
				(
					pPos->y + max.y >= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y && pPosOld->y + max.y< g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y ||
					pPos->y + min.y <= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y && pPosOld->y + min.y > g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y) &&
				pPos->x + Size >= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x &&
				pPos->z + Size >= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bHit = true;
			}

			if (
				(
					pPos->z + Size >= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z && pPosOld->z + Size < g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z ||
					pPos->z - Size <= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z && pPosOld->z - Size > g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z) &&
				pPos->x + Size >= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x &&
				pPos->y + max.y >= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y&&
				pPos->y + min.y <= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y
				)
			{//壁とプレイヤーが当たった(Z軸)
				pPos->z = pPosOld->z;
				pMove->z = 0.0f;
				bHit = true;
			}

			if (
				(
					pPos->x + Size >= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x && pPosOld->x + Size < g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x ||
					pPos->x - Size <= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x && pPosOld->x - Size > g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x) &&
				pPos->z + Size >= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z &&
				pPos->y + max.y >= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y &&
				pPos->y + min.y <= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->x = pPosOld->x;
				pMove->x = 0.0f;
				bHit = true;
			}
		}
	}
	return bHit;
}

//====================================================================
//影との当たり判定処理
//====================================================================
void CollisionBg_objectShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Bg_object[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y &&
				pPos->y <= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y &&
				pPos->x >= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x &&
				pPos->x <= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x &&
				pPos->z >= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z &&
				pPos->z <= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = g_Bg_object[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//オブジェクト00の所得
//====================================================================
Object00 * GetBg_object(void)
{
	return &g_Bg_object[0];
}