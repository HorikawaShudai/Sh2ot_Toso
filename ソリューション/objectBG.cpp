//========================================================================================
//
// 背景用オブジェクトの処理[ObjectBG.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "objectBG.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

#define OBJECTBG_LIFE (7)		//オブジェクトの体力

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureObjectBG[64][OBJECTBG_NTYPE_MAX] = {};		//テクスチャのポインタ
LPD3DXMESH g_pMeshObjectBG[OBJECTBG_NTYPE_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatObjectBG[OBJECTBG_NTYPE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatObjectBG[OBJECTBG_NTYPE_MAX] = {};						//マテリアルの数

ObjectBG g_ObjectBG[MAX_OBJECTBG];					//オブジェクトBGの情報
int EditIndex01;								//エディットモード用の番号
D3DXVECTOR3 EditPos01;						//エディットモードのオブジェクトの位置
D3DXVECTOR3 EditRot01;						//エディットモードのオブジェクトの向き
int EditType01;								//エディットモードのオブジェクトの種類
int g_ObjectCount01;							//オブジェクトの数

const char *c_apModelObj01[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\wood.x",
	"Data\\MODEL\\rock.x",
	"Data\\MODEL\\Labo.x",
	"Data\\MODEL\\title_field.x",
	"Data\\MODEL\\dropdust.x",				//ホコリ
	"Data\\MODEL\\storns.x",				//石
	"Data\\MODEL\\fan.x",					//換気扇b
	"Data\\MODEL\\corkboard.x",				//コルクボードb
	"Data\\MODEL\\art.x",					//壁掛けアートb
	"Data\\MODEL\\document.x",				//資料単体b
	"Data\\MODEL\\lightbutton.x",			//ライトのスイッチb
	"Data\\MODEL\\paper.x",					//資料単体b
	"Data\\MODEL\\vent.x",					//通気口b
	"Data\\MODEL\\window.x",				//窓b
	"Data\\MODEL\\screen.x",				//プロジェクターのうつされるほうb
	"Data\\MODEL\\watch.x",					//時計b
	"Data\\MODEL\\kaidanRU.x",				//階段_右_上
	"Data\\MODEL\\kaidanLU.x",				//階段_左_上
	"Data\\MODEL\\ceiling.x",				//天井(白)
	"Data\\MODEL\\ceiling1.x",				//天井(コンクリ)
	"Data\\MODEL\\ceiling5.x",				//天井(雨濡れコンクリ)
	"Data\\MODEL\\ceiling3.x",				//天井(タイル)
	"Data\\MODEL\\ceiling4.x",				//天井(白模様入り)
	"Data\\MODEL\\floor.x",					//床(鉄)
	"Data\\MODEL\\floor1.x",				//床(コンクリ)
	"Data\\MODEL\\floor2.x",				//床(タイル)
	"Data\\MODEL\\floor3.x",				//床(オフィス)
	"Data\\MODEL\\floor4.x",				//床(白)
	"Data\\MODEL\\floor5.x",				//床(白模様入り)
	"Data\\MODEL\\Player\\06_R_Hand.x",		//右手
	"Data\\MODEL\\title_tile.x",			//研究所内の床
	"Data\\MODEL\\Map_00.x",				//研究所内の床
	"Data\\MODEL\\Map_01.x",				//研究所内の床
	"Data\\MODEL\\Map_02.x",				//研究所内の床
	"Data\\MODEL\\Map_03.x",				//研究所内の床
	"Data\\MODEL\\escape.x",				//出口看板
	"Data\\MODEL\\fire_extingisher.x",		//消火器
	"Data\\MODEL\\laboratory.x",			//施設
	"Data\\MODEL\\tree000.x",				//木
	"Data\\MODEL\\door1.x",					//ドア
	"Data\\MODEL\\door2.x",					//ドア
	"Data\\MODEL\\door3.x",					//ドア
	"Data\\MODEL\\door4.x",					//ドア
	"Data\\MODEL\\carpet.x",				//カーペット
	"Data\\MODEL\\JailArea.x",				//収容所エリア案内
	"Data\\MODEL\\OfficeArea.x",			//オフィスエリア案内
	"Data\\MODEL\\ResearchArea.x",			//研究所エリア案内
	"Data\\MODEL\\Arrow.x",					//やじるし
};

//====================================================================
//オブジェクトBGの初期化処理
//====================================================================
void InitObjectBG(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		g_ObjectBG[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectBG[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectBG[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectBG[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectBG[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_ObjectBG[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_ObjectBG[nCntObject].bUse = false;
		g_ObjectBG[nCntObject].nType = OBJECTBG_NTYPE00;
		g_ObjectBG[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	}
	EditIndex01 = MAX_OBJECTBG - 1;
	EditPos01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditRot01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditType01 = 0;
	g_ObjectCount01 = 0;

	//Xファイルの読み込み
	for (int nCntObj = 0; nCntObj < OBJECTBG_NTYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModelObj01[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObjectBG[nCntObj],
			NULL,
			&g_dwNumMatObjectBG[nCntObj],
			&g_pMeshObjectBG[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntNumObject = 0; nCntNumObject < OBJECTBG_NTYPE_MAX; nCntNumObject++)
	{
		//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectBG[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectBG[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObjectBG[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//オブジェクトBGの終了処理
//====================================================================
void UninitObjectBG(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECTBG_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//テクスチャの破棄
			if (g_pTextureObjectBG[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureObjectBG[nCntTex][nCntNumObject]->Release();
				g_pTextureObjectBG[nCntTex][nCntNumObject] = NULL;
			}
		}

		//メッシュの破棄
		if (g_pMeshObjectBG[nCntNumObject] != NULL)
		{
			g_pMeshObjectBG[nCntNumObject]->Release();
			g_pMeshObjectBG[nCntNumObject] = NULL;
		}

		//マテリアルの破棄
		if (g_pBuffMatObjectBG[nCntNumObject] != NULL)
		{
			g_pBuffMatObjectBG[nCntNumObject]->Release();
			g_pBuffMatObjectBG[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//オブジェクトBGの更新処理
//====================================================================
void UpdateObjectBG(void)
{
#ifdef _DEBUG
	PrintDebugProc("背景オブジェクトの数:%d\n", g_ObjectCount01);
#endif // _DEBUG
}

//====================================================================
//オブジェクトBGの描画処理
//====================================================================
void DrawObjectBG(void)
{
	int nCntObject;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_ObjectBG[nCntObject].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectBG[nCntObject].rot.y, g_ObjectBG[nCntObject].rot.x, g_ObjectBG[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_ObjectBG[nCntObject].mtxWorld, &g_ObjectBG[nCntObject].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_ObjectBG[nCntObject].pos.x, g_ObjectBG[nCntObject].pos.y, g_ObjectBG[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_ObjectBG[nCntObject].mtxWorld, &g_ObjectBG[nCntObject].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_ObjectBG[nCntObject].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを所得する
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectBG[g_ObjectBG[nCntObject].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectBG[g_ObjectBG[nCntObject].nType]; nCntMat++)
		{

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_ObjectBG[nCntObject].bUse == true)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureObjectBG[nCntMat][g_ObjectBG[nCntObject].nType]);

				//オブジェクトBG(パーツ)の描画
				g_pMeshObjectBG[g_ObjectBG[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//エディットモードのオブジェクトBGの更新処理
//====================================================================
void UpdateEditObjectBG(void)
{
	//キーボードの移動処理----------
	if (g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE18 || g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE19 || g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE20 || g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE21 || g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE22 || g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE23 || g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE24 || g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE25 || g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE26 || g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE27 || g_ObjectBG[EditIndex01].nType == OBJECTBG_NTYPE28)
	{//選択されているオブジェクトが天井の時
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

	if (g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE18 && g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE19 && g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE20 && g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE21 && g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE22 && g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE23 && g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE24 && g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE25 && g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE26 && g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE27 && g_ObjectBG[EditIndex01].nType != OBJECTBG_NTYPE28)
	{//選択されているオブジェクトが天井以外の時
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

		if (EditType01 > OBJECTBG_NTYPE_MAX - 1)
		{
			EditType01 = 0;
		}

		if (EditType01 == OBJECTBG_NTYPE18)
		{//選択されているオブジェクトが天井の時
			EditPos01 = D3DXVECTOR3(0.0f, 150.0f, 0.0f);
		}

		if (EditType01 == OBJECTBG_NTYPE23)
		{//選択されているオブジェクトが床の時
			EditPos01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
	if (GetKeyboardTrigger(DIK_8) == true)
	{//８キーで前のタイプのオブジェクトにする
		EditType01--;

		if (EditType01 < 0)
		{
			EditType01 = OBJECTBG_NTYPE_MAX - 1;
		}
	}

	//エディットモードの変更をオブジェクトに反映させる
	g_ObjectBG[EditIndex01].pos = EditPos01;
	g_ObjectBG[EditIndex01].rot = EditRot01;
	g_ObjectBG[EditIndex01].nType = EditType01;

	//オブジェクトの削除処理(重なっているもの)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObjectBG(g_ObjectBG[EditIndex01].pos, g_ObjectBG[EditIndex01].vtxMin, g_ObjectBG[EditIndex01].vtxMax, 20.0f);
	}

	//オブジェクトの削除処理(CTRL+Z)----------
	if (GetKeyboardTrigger(DIK_Z) == true && GetKeyboardPress(DIK_LCONTROL) == true)
	{
		FalseObjectBG();
	}

	//オブジェクトの設置処理----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObjectBG(g_ObjectBG[EditIndex01].pos, g_ObjectBG[EditIndex01].move, g_ObjectBG[EditIndex01].rot, g_ObjectBG[EditIndex01].nType);
	}
}

//====================================================================
//エディットモードのオブジェクトBGの描画処理
//====================================================================
void DrawEditObjectBG(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ


									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_ObjectBG[EditIndex01].mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectBG[EditIndex01].rot.y, g_ObjectBG[EditIndex01].rot.x, g_ObjectBG[EditIndex01].rot.z);

	D3DXMatrixMultiply(&g_ObjectBG[EditIndex01].mtxWorld, &g_ObjectBG[EditIndex01].mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_ObjectBG[EditIndex01].pos.x, g_ObjectBG[EditIndex01].pos.y, g_ObjectBG[EditIndex01].pos.z);

	D3DXMatrixMultiply(&g_ObjectBG[EditIndex01].mtxWorld, &g_ObjectBG[EditIndex01].mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_ObjectBG[EditIndex01].mtxWorld);

	//現在のマテリアルを所得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを所得する
	pMat = (D3DXMATERIAL*)g_pBuffMatObjectBG[g_ObjectBG[EditIndex01].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectBG[g_ObjectBG[EditIndex01].nType]; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&g_ObjectBG[EditIndex01].pMatE.MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureObjectBG[nCntMat][g_ObjectBG[EditIndex01].nType]);

		//オブジェクトBG(パーツ)の描画
		g_pMeshObjectBG[g_ObjectBG[EditIndex01].nType]->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//オブジェクトBGの設定処理
//====================================================================
void SetObjectBG(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		if (g_ObjectBG[nCntObject].bUse == false)
		{
			g_ObjectBG[nCntObject].pos = pos;
			g_ObjectBG[nCntObject].posOld = pos;
			g_ObjectBG[nCntObject].move = move;
			g_ObjectBG[nCntObject].rot = rot;
			g_ObjectBG[nCntObject].nType = nType;

			g_ObjectBG[nCntObject].bUse = true;
			g_ObjectCount01++;

			//if (g_ObjectBG[nCntObject].nType != 0)
			//{
			int nNumVtx;		//頂点数
			DWORD dwSizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;		//頂点バッファへのポインタ

			//頂点数を所得
			nNumVtx = g_pMeshObjectBG[nType]->GetNumVertices();

			//頂点フォーマットのサイズを所得
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObjectBG[nType]->GetFVF());

			//頂点バッファをロック
			g_pMeshObjectBG[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				if (g_ObjectBG[nCntObject].vtxMin.x > vtx.x)
				{
					g_ObjectBG[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_ObjectBG[nCntObject].vtxMin.y > vtx.y)
				{
					g_ObjectBG[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_ObjectBG[nCntObject].vtxMin.z > vtx.z)
				{
					g_ObjectBG[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_ObjectBG[nCntObject].vtxMax.x < vtx.x)
				{
					g_ObjectBG[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_ObjectBG[nCntObject].vtxMax.y < vtx.y)
				{
					g_ObjectBG[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_ObjectBG[nCntObject].vtxMax.z < vtx.z)
				{
					g_ObjectBG[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshObjectBG[nType]->UnlockVertexBuffer();
			//}
			//else
			//{
			//	g_ObjectBG[nCntObject].vtxMin = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
			//	g_ObjectBG[nCntObject].vtxMax = D3DXVECTOR3(100.0f, 150.0f, 5.0f);
			//}


			CollisionRotObjectBG(nCntObject);

			break;
		}
	}
}

//====================================================================
//オブジェクトBGの削除処理
//====================================================================
void FalseObjectBG(void)
{
	int nCntObject;

	for (nCntObject = MAX_OBJECTBG; nCntObject >= 0; nCntObject--)
	{
		if (g_ObjectBG[nCntObject].bUse == true)
		{
			g_ObjectBG[nCntObject].bUse = false;
			break;
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool EditCollisionObjectBG(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		if (g_ObjectBG[nCntObject].bUse == true)
		{
			if (
				pPos.y + Size >= g_ObjectBG[nCntObject].pos.y + g_ObjectBG[nCntObject].vtxMin.y && pPos.y - Size <= g_ObjectBG[nCntObject].pos.y + g_ObjectBG[nCntObject].vtxMax.y &&
				pPos.x + Size >= g_ObjectBG[nCntObject].pos.x + g_ObjectBG[nCntObject].vtxMin.x && pPos.x - Size <= g_ObjectBG[nCntObject].pos.x + g_ObjectBG[nCntObject].vtxMax.x &&
				pPos.z + Size >= g_ObjectBG[nCntObject].pos.z + g_ObjectBG[nCntObject].vtxMin.z && pPos.z - Size <= g_ObjectBG[nCntObject].pos.z + g_ObjectBG[nCntObject].vtxMax.z
				)
			{//オブジェクト同士が重なっている
				g_ObjectBG[nCntObject].bUse = false;

				bON = true;
			}
		}
	}
	return bON;
}

//====================================================================
//オブジェクトの当たり判定を回転させる処理
//====================================================================
void CollisionRotObjectBG(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_ObjectBG[nCnt].vtxMax.z;
	MaxX = g_ObjectBG[nCnt].vtxMax.x;
	MinZ = g_ObjectBG[nCnt].vtxMin.z;
	MinX = g_ObjectBG[nCnt].vtxMin.x;


	if (g_ObjectBG[nCnt].rot.y <= 0.0f)
	{
		g_ObjectBG[nCnt].vtxMax.z = MaxZ;
		g_ObjectBG[nCnt].vtxMax.x = MaxX;
		g_ObjectBG[nCnt].vtxMin.z = MinZ;
		g_ObjectBG[nCnt].vtxMin.x = MinX;
	}
	else if (g_ObjectBG[nCnt].rot.y <= 1.57f)
	{
		g_ObjectBG[nCnt].vtxMax.z = -MinX;
		g_ObjectBG[nCnt].vtxMax.x = MaxZ;
		g_ObjectBG[nCnt].vtxMin.z = -MaxX;
		g_ObjectBG[nCnt].vtxMin.x = MinZ;
	}
	else if (g_ObjectBG[nCnt].rot.y <= 3.14f)
	{
		g_ObjectBG[nCnt].vtxMax.z = -MinZ;
		g_ObjectBG[nCnt].vtxMax.x = -MinX;
		g_ObjectBG[nCnt].vtxMin.z = -MaxZ;
		g_ObjectBG[nCnt].vtxMin.x = -MaxX;
	}
	else if (g_ObjectBG[nCnt].rot.y <= 4.71f)
	{
		g_ObjectBG[nCnt].vtxMax.z = MaxX;
		g_ObjectBG[nCnt].vtxMax.x = -MinZ;
		g_ObjectBG[nCnt].vtxMin.z = MinX;
		g_ObjectBG[nCnt].vtxMin.x = -MaxZ;
	}
}

//====================================================================
//影との当たり判定処理
//====================================================================
void CollisionObjectBGShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		if (g_ObjectBG[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_ObjectBG[nCntObject].pos.y + g_ObjectBG[nCntObject].vtxMin.y &&
				pPos->y <= g_ObjectBG[nCntObject].pos.y + g_ObjectBG[nCntObject].vtxMax.y &&
				pPos->x >= g_ObjectBG[nCntObject].pos.x + g_ObjectBG[nCntObject].vtxMin.x &&
				pPos->x <= g_ObjectBG[nCntObject].pos.x + g_ObjectBG[nCntObject].vtxMax.x &&
				pPos->z >= g_ObjectBG[nCntObject].pos.z + g_ObjectBG[nCntObject].vtxMin.z &&
				pPos->z <= g_ObjectBG[nCntObject].pos.z + g_ObjectBG[nCntObject].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = g_ObjectBG[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//オブジェクトBGの所得
//====================================================================
ObjectBG * GetObjectBG(void)
{
	return &g_ObjectBG[0];
}