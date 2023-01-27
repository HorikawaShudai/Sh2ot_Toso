#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

#define OBJECT00_LIFE (7)		//オブジェクトの体力
#define FALSE_SIZE (10.0f)		//エディットモードのバックスペースの判定の大きさ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureObject00[64][OBJECT00_NTYPE_MAX] = {};		//テクスチャのポインタ
LPD3DXMESH g_pMeshObject00[OBJECT00_NTYPE_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatObject00[OBJECT00_NTYPE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatObject00[OBJECT00_NTYPE_MAX] = {};						//マテリアルの数

Object00 g_Object00[MAX_OBJECT00];					//オブジェクト00の情報
int EditIndex;								//エディットモード用の番号
D3DXVECTOR3 EditPos;						//エディットモードのオブジェクトの位置
D3DXVECTOR3 EditRot;						//エディットモードのオブジェクトの向き
int EditType;								//エディットモードのオブジェクトの種類
int g_ObjectCount;							//オブジェクトの数

const char *c_apModelObj[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\wall.x",
	"Data\\MODEL\\pc.x",
	"Data\\MODEL\\desk.x",
	"Data\\MODEL\\fan.x",
	"Data\\MODEL\\locker.x",
	"Data\\MODEL\\whiteboard.x",
	"Data\\MODEL\\officechair.x",
	"Data\\MODEL\\corkboard.x",
	"Data\\MODEL\\camera.x",
	"Data\\MODEL\\art.x",
	"Data\\MODEL\\document.x",
	"Data\\MODEL\\door_side1.x",
	"Data\\MODEL\\door_side2.x",
	"Data\\MODEL\\doorup.x",
	"Data\\MODEL\\illumination.x",
	"Data\\MODEL\\jewelry.x",
	"Data\\MODEL\\key.x",
	"Data\\MODEL\\lightbutton.x",
	"Data\\MODEL\\longdesk.x",
	"Data\\MODEL\\machine.x",
	"Data\\MODEL\\moniter.x",
	"Data\\MODEL\\paper.x",
	"Data\\MODEL\\pot.x",
	"Data\\MODEL\\projecter.x",
	"Data\\MODEL\\shelf.x",
	"Data\\MODEL\\vent.x",
	"Data\\MODEL\\window.x",
	"Data\\MODEL\\desk_pc.x",
	"Data\\MODEL\\projecter2.x",
	"Data\\MODEL\\screen.x",
	"Data\\MODEL\\plant.x",
	"Data\\MODEL\\dustbox.x",
	"Data\\MODEL\\partition.x",
	"Data\\MODEL\\book_shelf.x",
	"Data\\MODEL\\papercut_desk.x",
	"Data\\MODEL\\coat_rack.x",
	"Data\\MODEL\\endai.x",
	"Data\\MODEL\\paper_cut.x",
	"Data\\MODEL\\watch.x",
	"Data\\MODEL\\copy.x",
	"Data\\MODEL\\BuleBox.x",
	"Data\\MODEL\\Cabinet.x",
	"Data\\MODEL\\chemicalshelf.x",
	"Data\\MODEL\\Height_Cabinet.x",
	"Data\\MODEL\\rubble.x",
	"Data\\MODEL\\stretcher.x",
	"Data\\MODEL\\catcar.x",
	"Data\\MODEL\\fence.x",
	"Data\\MODEL\\rock2.x",
	"Data\\MODEL\\BlackDesk.x",
	"Data\\MODEL\\prison.x"
};

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
		g_Object00[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	}
	EditIndex = 0;
	EditPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditType = 0;
	g_ObjectCount = 0;

	//Xファイルの読み込み
	for (int nCntObj = 0; nCntObj < OBJECT00_NTYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModelObj[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObject00[nCntObj],
			NULL,
			&g_dwNumMatObject00[nCntObj],
			&g_pMeshObject00[nCntObj]);
	}


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
	PrintDebugProc("オブジェクトの数:%d\n", g_ObjectCount);
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
					//テクスチャの設定
					pDevice->SetTexture(0, g_pTextureObject00[nCntMat][g_Object00[nCntObject].nType]);

					//オブジェクト00(パーツ)の描画
					g_pMeshObject00[g_Object00[nCntObject].nType]->DrawSubset(nCntMat);
				}
			}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//エディットモードのオブジェクト00の更新処理
//====================================================================
void UpdateEditObject00(void)
{
	//キーボードの移動処理----------
	if (g_Object00[EditIndex].nType == 0)
	{//選択されているオブジェクトが壁の時
		if (GetKeyboardTrigger(DIK_UP) == true)
		{//前移動
			EditPos.z += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{//後ろ移動
			EditPos.z -= 100.0f;
		}
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{//右移動
			EditPos.x += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{//左移動
			EditPos.x -= 100.0f;
		}
	}

	if(g_Object00[EditIndex].nType != 0)
	{//選択されているオブジェクトが壁以外の時
		if (GetKeyboardPress(DIK_UP) == true)
		{//前移動
			EditPos.z += 1.0f;
		}
		if (GetKeyboardPress(DIK_DOWN) == true)
		{//後ろ移動
			EditPos.z -= 1.0f;
		}
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{//右移動
			EditPos.x += 1.0f;
		}
		if (GetKeyboardPress(DIK_LEFT) == true)
		{//左移動
			EditPos.x -= 1.0f;
		}
		if (GetKeyboardPress(DIK_RSHIFT) == true)
		{//上移動
			EditPos.y += 1.0f;
		}
		if (GetKeyboardPress(DIK_RCONTROL) == true)
		{//下移動
			EditPos.y -= 1.0f;
		}
	}

	//オブジェクトの回転処理
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		EditRot.y += 1.57f;

		if (EditRot.y >= 6.28f)
		{
			EditRot.y = 0.0f;
		}
	}

	//オブジェクトの切り替え処理----------
	if (GetKeyboardTrigger(DIK_9) == true)
	{//９キーで次のタイプのオブジェクトにする
		EditType++;

		if (EditType > OBJECT00_NTYPE_MAX - 1)
		{
			EditType = 0;
		}

		if (EditType == 0)
		{
			EditPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
	if (GetKeyboardTrigger(DIK_8) == true)
	{//８キーで前のタイプのオブジェクトにする
		EditType--;

		if (EditType < 0)
		{
			EditType = OBJECT00_NTYPE_MAX - 1;
		}

		if (EditType == 0)
		{
			EditPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	//エディットモードの変更をオブジェクトに反映させる
	g_Object00[EditIndex].pos = EditPos;
	g_Object00[EditIndex].rot = EditRot;
	g_Object00[EditIndex].nType = EditType;

	//オブジェクトの削除処理(重なっているもの)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObject00(g_Object00[EditIndex].pos, g_Object00[EditIndex].vtxMin, g_Object00[EditIndex].vtxMax, FALSE_SIZE);
	}

	//オブジェクトの削除処理(CTRL+Z)----------
	if (GetKeyboardTrigger(DIK_Z) == true && GetKeyboardPress(DIK_LCONTROL) == true)
	{
		FalseObject00();
	}

	//オブジェクトの設置処理----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObject00(g_Object00[EditIndex].pos, g_Object00[EditIndex].move, g_Object00[EditIndex].rot, g_Object00[EditIndex].nType);
	}
}

//====================================================================
//エディットモードのオブジェクト00の描画処理
//====================================================================
void DrawEditObject00(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ


		//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Object00[EditIndex].mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object00[EditIndex].rot.y, g_Object00[EditIndex].rot.x, g_Object00[EditIndex].rot.z);

	D3DXMatrixMultiply(&g_Object00[EditIndex].mtxWorld, &g_Object00[EditIndex].mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Object00[EditIndex].pos.x, g_Object00[EditIndex].pos.y, g_Object00[EditIndex].pos.z);

	D3DXMatrixMultiply(&g_Object00[EditIndex].mtxWorld, &g_Object00[EditIndex].mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Object00[EditIndex].mtxWorld);

	//現在のマテリアルを所得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを所得する
	pMat = (D3DXMATERIAL*)g_pBuffMatObject00[g_Object00[EditIndex].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject00[g_Object00[EditIndex].nType]; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&g_Object00[EditIndex].pMatE.MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureObject00[nCntMat][g_Object00[EditIndex].nType]);

		//オブジェクト00(パーツ)の描画
		g_pMeshObject00[g_Object00[EditIndex].nType]->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//オブジェクト00の設定処理
//====================================================================
void SetObject00(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
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
			EditIndex++;
			g_ObjectCount++;

			//if (g_Object00[nCntObject].nType != 0)
			//{
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
			//}
			//else
			//{
			//	g_Object00[nCntObject].vtxMin = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
			//	g_Object00[nCntObject].vtxMax = D3DXVECTOR3(100.0f, 150.0f, 5.0f);
			//}


			CollisionRotObject00(nCntObject);

			break;
		}
	}
}

//====================================================================
//オブジェクト00の削除処理
//====================================================================
void FalseObject00(void)
{
	int nCntObject;

	for (nCntObject = MAX_OBJECT00; nCntObject >= 0; nCntObject--)
	{
		if (g_Object00[nCntObject].bUse == true)
		{
			g_Object00[nCntObject].bUse = false;
			EditIndex--;
			g_ObjectCount--;
			break;
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool EditCollisionObject00(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Object00[nCntObject].bUse == true)
		{
			if (
				pPos.y + Size >= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y && pPos.y - Size <= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y &&
				pPos.x + Size >= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x && pPos.x - Size <= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x &&
				pPos.z + Size >= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z && pPos.z - Size <= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z
				)
			{//オブジェクト同士が重なっている
				g_Object00[nCntObject].bUse = false;
				g_ObjectCount--;
				EditIndex--;
				bON = true;
			}
		}
	}
	return bON;
}

//====================================================================
//オブジェクトの当たり判定を回転させる処理
//====================================================================
void CollisionRotObject00(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_Object00[nCnt].vtxMax.z;
	MaxX = g_Object00[nCnt].vtxMax.x;
	MinZ = g_Object00[nCnt].vtxMin.z;
	MinX = g_Object00[nCnt].vtxMin.x;


	if (g_Object00[nCnt].rot.y <= 0.0f)
	{
		g_Object00[nCnt].vtxMax.z = MaxZ;
		g_Object00[nCnt].vtxMax.x = MaxX;
		g_Object00[nCnt].vtxMin.z = MinZ;
		g_Object00[nCnt].vtxMin.x = MinX;
	}
	else if (g_Object00[nCnt].rot.y <= 1.57f)
	{
		g_Object00[nCnt].vtxMax.z = -MinX;
		g_Object00[nCnt].vtxMax.x = MaxZ;
		g_Object00[nCnt].vtxMin.z = -MaxX;
		g_Object00[nCnt].vtxMin.x = MinZ;
	}
	else if (g_Object00[nCnt].rot.y <= 3.14f)
	{
		g_Object00[nCnt].vtxMax.z = -MinZ;
		g_Object00[nCnt].vtxMax.x = -MinX;
		g_Object00[nCnt].vtxMin.z = -MaxZ;
		g_Object00[nCnt].vtxMin.x = -MaxX;
	}
	else if (g_Object00[nCnt].rot.y <= 4.71f)
	{
		g_Object00[nCnt].vtxMax.z = MaxX;
		g_Object00[nCnt].vtxMax.x = -MinZ;
		g_Object00[nCnt].vtxMin.z = MinX;
		g_Object00[nCnt].vtxMin.x =- MaxZ;
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool CollisionObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

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
				bHit = true;
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
				bHit = true;
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
				bHit = true;
			}
		}
	}
	return bHit;
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