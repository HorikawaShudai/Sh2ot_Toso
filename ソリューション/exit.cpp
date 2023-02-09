//========================================================================================
//
// 出口の処理[exit.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "exit.h"
#include "PlayNumberSelect.h"
#include "PlayModeSelect.h"
#include "Fade.h"
#include "player.h"
#include "meshwall.h"

const char *c_apExit[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\Exit\\BigDoorFrame.x",
	"Data\\MODEL\\Exit\\BigDoor_L.x",
	"Data\\MODEL\\Exit\\BigDoor_R.x",
};

//プロトタイプ宣言
void DoorOpen(void);
void ExsitClossLine(int nCntExit);

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExit[64][EXIT_TYPE_MAX] = {};		//テクスチャのポインタ
LPD3DXMESH g_pMeshExit[EXIT_TYPE_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatExit[EXIT_TYPE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatExit[EXIT_TYPE_MAX] = {};						//マテリアルの数

EXIT g_Exit[MAX_EXIT];					//オブジェクト00の情報
int g_KeyCount;							//必要になる鍵のカウント
int g_ExitCnt;							//脱出可能になるまでのカウント

bool g_bExitFade[MAX_EXIT];
bool g_bExitOK;

D3DXVECTOR3 g_vecToPos;
D3DXVECTOR3 g_vecLine;
D3DXVECTOR3 g_vecNor;
D3DXVECTOR3 g_vecMoveRef;

//====================================================================
//オブジェクト00の初期化処理
//====================================================================
void InitExit(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PlayModeSelect PlayMode = GetPlayModeSelect();

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		g_Exit[nCntExit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Exit[nCntExit].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Exit[nCntExit].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Exit[nCntExit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Exit[nCntExit].rotSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Exit[nCntExit].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Exit[nCntExit].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Exit[nCntExit].bUse = false;
		g_Exit[nCntExit].bExitOK = false;
		g_Exit[nCntExit].nType = EXIT_TYPE_BIGFRAME;
	}

	g_vecToPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecLine = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecNor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecMoveRef = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_KeyCount = 0;
	g_ExitCnt = 120;
	g_bExitOK = false;

	//Xファイルの読み込み
	for (int nCntObj = 0; nCntObj < EXIT_TYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apExit[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatExit[nCntObj],
			NULL,
			&g_dwNumMatExit[nCntObj],
			&g_pMeshExit[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntNumObject = 0; nCntNumObject < EXIT_TYPE_MAX; nCntNumObject++)
	{
		//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatExit[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatExit[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureExit[nCntMat][nCntNumObject]);
			}
		}
	}

	if (PlayMode.CurrentModeNumber == 0)
	{
		SetExit(D3DXVECTOR3(-1000.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXIT_TYPE_BIGFRAME);
		SetExit(D3DXVECTOR3(-935.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), EXIT_TYPE_BIGDOOR_R);
		SetExit(D3DXVECTOR3(-1065.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), EXIT_TYPE_BIGDOOR_L);
	}
}

//====================================================================
//オブジェクト00の終了処理
//====================================================================
void UninitExit(void)
{
	for (int nCntNumObject = 0; nCntNumObject < EXIT_TYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//テクスチャの破棄
			if (g_pTextureExit[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureExit[nCntTex][nCntNumObject]->Release();
				g_pTextureExit[nCntTex][nCntNumObject] = NULL;
			}
		}

		//メッシュの破棄
		if (g_pMeshExit[nCntNumObject] != NULL)
		{
			g_pMeshExit[nCntNumObject]->Release();
			g_pMeshExit[nCntNumObject] = NULL;
		}
		//マテリアルの破棄
		if (g_pBuffMatExit[nCntNumObject] != NULL)
		{
			g_pBuffMatExit[nCntNumObject]->Release();
			g_pBuffMatExit[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//オブジェクト00の更新処理
//====================================================================
void UpdateExit(void)
{
	//扉が開く処理
	DoorOpen();
}

//====================================================================
//オブジェクト00の描画処理
//====================================================================
void DrawExit(void)
{
	int nCntExit;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_Exit[nCntExit].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Exit[nCntExit].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Exit[nCntExit].rot.y, g_Exit[nCntExit].rot.x, g_Exit[nCntExit].rot.z);

			D3DXMatrixMultiply(&g_Exit[nCntExit].mtxWorld, &g_Exit[nCntExit].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Exit[nCntExit].pos.x, g_Exit[nCntExit].pos.y, g_Exit[nCntExit].pos.z);

			D3DXMatrixMultiply(&g_Exit[nCntExit].mtxWorld, &g_Exit[nCntExit].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Exit[nCntExit].mtxWorld);

			//現在のマテリアルを所得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを所得する
			pMat = (D3DXMATERIAL*)g_pBuffMatExit[g_Exit[nCntExit].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatExit[g_Exit[nCntExit].nType]; nCntMat++)
			{

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Exit[nCntExit].bUse == true)
				{
					//テクスチャの設定
					pDevice->SetTexture(0, g_pTextureExit[nCntMat][g_Exit[nCntExit].nType]);

					//オブジェクト00(パーツ)の描画
					g_pMeshExit[g_Exit[nCntExit].nType]->DrawSubset(nCntMat);
				}
			}
			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//========================================
//扉が開く処理
//========================================
void DoorOpen(void)
{
	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		/*if (g_Exit[nCntExit].bUse == true && g_Exit[nCntExit].bExitOK == true)
		{
		if (g_bExitFade[nCntExit] == false)
		{
		SetFade(MODE_RESULT);

		g_bExitFade[nCntExit] = true;
		}
		}*/

		//外積の脱出判定処理
		ExsitClossLine(nCntExit);

		//g_Exit[1].rot.y = /*g_Exit[1].rotSave.y + */(sinf(g_Exit[1].rotSave.y) + cosf(g_Exit[1].rotSave.y) - 0.5f);

		if (g_Exit[nCntExit].bUse == true && g_Exit[nCntExit].bExitOK == true)
		{//出口が使われていて脱出可能の場合
			for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
			{
				if (g_Exit[nCntExit1].nType != EXIT_TYPE_BIGFRAME)
				{
					if (g_Exit[1].rot.y >= g_Exit[1].rotSave.y + (sinf(g_Exit[1].rotSave.y) + cosf(g_Exit[1].rotSave.y) - 0.5f))
					{
						g_Exit[1].rot.y += cosf(g_Exit[1].rot.y) * 0.003f;
						g_Exit[1].rot.y -= sinf(g_Exit[1].rot.y) * 0.003f;

						g_Exit[2].rot.y -= sinf(g_Exit[2].rot.y) * 0.003f;
						g_Exit[2].rot.y += -cosf(g_Exit[2].rot.y) * 0.003f;
					}
				}
			}
			g_ExitCnt--;

			if (g_ExitCnt <= 0)
			{
				g_ExitCnt = 0;
			}
		}

		if (g_Exit[nCntExit].rot.y > D3DX_PI)
		{
			g_Exit[nCntExit].rot.y = -D3DX_PI;
		}
		if (g_Exit[nCntExit].rot.y < -D3DX_PI)
		{
			g_Exit[nCntExit].rot.y = D3DX_PI;
		}
	}
}

//================================
// 外積の当たり判定
//================================
void ExsitClossLine(int nCntExit)
{
	//変数宣言
	float vec;

	Player *pPlayer = GetPlayer();
	MeshWall MeshWall = GetMeshWall();

	for (int nCntWall = 0; nCntWall < MAX_EXIT; nCntWall++, pPlayer++)
	{
		if (pPlayer->bUse == true && MeshWall.bUse == true)
		{
			float fRate;					//ベクトルの割合
			float fMaxArea, fNowArea;		//今の面積／最大面積
			D3DXVECTOR3 pos0, pos1;			//場所
			D3DXVECTOR3 Cross;				//交点の場所

			//場所の計算
			pos0 = MeshWall.pos + D3DXVECTOR3(cosf(MeshWall.rot.y) + 50.0f, 0.0f, sinf(MeshWall.rot.y));

			pos1 = MeshWall.pos + D3DXVECTOR3(cosf(MeshWall.rot.y) - 50.0f, 0.0f, sinf(MeshWall.rot.y));

			//pos0とpos1との距離間
			g_vecLine = pos1 - pos0;

			//出口からプレイヤーまでの位置
			g_vecToPos = pPlayer->pos - MeshWall.pos;

			//最大面積
			fMaxArea = (g_vecLine.z * pPlayer->move.x) - (g_vecLine.x * MeshWall.move.z);

			//今の面積
			fNowArea = (g_vecToPos.z * pPlayer->move.x) - (g_vecToPos.x * MeshWall.move.z);

			//ベクトルの割合
			fRate = fNowArea / fMaxArea;

			//交点
			Cross = D3DXVECTOR3(pos0.x + g_vecLine.x * fRate, pPlayer->pos.y, pos0.z + g_vecLine.z * fRate);

			vec = (g_vecLine.z * g_vecToPos.x) - (g_vecLine.x * g_vecToPos.z);

			if (pPlayer->pos.x <= pos0.x && pPlayer->pos.x >= pos1.x)
			{
				if (vec < 0)
				{
					//脱出状態へ
					pPlayer->State = PLAYER_EXSIT;
					pPlayer->bExit = true;
				}
			}
		}
	}
}

//====================================================================
//エディットモードのオブジェクト00の更新処理
//====================================================================
void UpdateEditExit(void)
{
	
}

//====================================================================
//エディットモードのオブジェクト00の描画処理
//====================================================================
void DrawEditExit(void)
{

}

//====================================================================
//オブジェクト00の設定処理
//====================================================================
void SetExit(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntExit;

	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_Exit[nCntExit].bUse == false)
		{
			g_Exit[nCntExit].pos = pos;
			g_Exit[nCntExit].posOld = pos;
			g_Exit[nCntExit].move = move;
			g_Exit[nCntExit].rot = rot;
			g_Exit[nCntExit].rotSave = rot;
			g_Exit[nCntExit].nType = nType;

			g_Exit[nCntExit].bUse = true;

			int nNumVtx;		//頂点数
			DWORD dwSizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;		//頂点バッファへのポインタ

			//頂点数を所得
			nNumVtx = g_pMeshExit[nType]->GetNumVertices();

			//頂点フォーマットのサイズを所得
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshExit[nType]->GetFVF());

			//頂点バッファをロック
			g_pMeshExit[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				if (g_Exit[nCntExit].vtxMin.x > vtx.x)
				{
					g_Exit[nCntExit].vtxMin.x = vtx.x;
				}
				if (g_Exit[nCntExit].vtxMin.y > vtx.y)
				{
					g_Exit[nCntExit].vtxMin.y = vtx.y;
				}
				if (g_Exit[nCntExit].vtxMin.z > vtx.z)
				{
					g_Exit[nCntExit].vtxMin.z = vtx.z;
				}

				if (g_Exit[nCntExit].vtxMax.x < vtx.x)
				{
					g_Exit[nCntExit].vtxMax.x = vtx.x;
				}
				if (g_Exit[nCntExit].vtxMax.y < vtx.y)
				{
					g_Exit[nCntExit].vtxMax.y = vtx.y;
				}
				if (g_Exit[nCntExit].vtxMax.z < vtx.z)
				{
					g_Exit[nCntExit].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshExit[nType]->UnlockVertexBuffer();

			CollisionRotObject00(nCntExit);

			break;
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool CollisionExit(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer)
{
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	bool bHit = false;

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_Exit[nCntExit].bUse == true && g_Exit[nCntExit].bExitOK == false)
		{
			if (pPos->x >= g_Exit[nCntExit].pos.x - Size
				&& pPos->x <= g_Exit[nCntExit].pos.x + Size
				&& pPos->y >= g_Exit[nCntExit].pos.y - Size
				&& pPos->y <= g_Exit[nCntExit].pos.y + Size
				&& pPos->z >= g_Exit[nCntExit].pos.z - Size
				&& pPos->z <= g_Exit[nCntExit].pos.z + Size)

			{//アイテムとプレイヤーが当たった(X軸)
				bHit = true;
				g_KeyCount++;

				if (g_KeyCount > PlayNumber.CurrentSelectNumber - 1)
				{//鍵がプレイヤー人数分使われた場合
					g_bExitOK = true;

					g_Exit[1].bExitOK = true;
					g_Exit[2].bExitOK = true;
				}

				break;
			}
		}
	}

	return bHit;
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool CollisionExi(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_Exit[nCntExit].bUse == true && /*g_Exit[nCntExit].bExitOK == false*/ g_ExitCnt >= 1)
		{
			if (
				(
					pPos->y + max.y >= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMin.y && pPosOld->y + max.y< g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMin.y ||
					pPos->y + min.y <= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMax.y && pPosOld->y + min.y > g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMax.y) &&
				pPos->x + Size >= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMin.x &&
				pPos->x - Size <= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMax.x &&
				pPos->z + Size >= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMin.z &&
				pPos->z - Size <= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bHit = true;
			}

			if (
				(
					pPos->z + Size >= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMin.z && pPosOld->z + Size < g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMin.z ||
					pPos->z - Size <= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMax.z && pPosOld->z - Size > g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMax.z) &&
				pPos->x + Size >= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMin.x &&
				pPos->x - Size <= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMax.x &&
				pPos->y + max.y >= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMin.y&&
				pPos->y + min.y <= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMax.y
				)
			{//壁とプレイヤーが当たった(Z軸)
				pPos->z = pPosOld->z;
				pMove->z = 0.0f;
				bHit = true;
			}

			if (
				(
					pPos->x + Size >= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMin.x && pPosOld->x + Size < g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMin.x ||
					pPos->x - Size <= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMax.x && pPosOld->x - Size > g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMax.x) &&
				pPos->z + Size >= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMin.z &&
				pPos->z - Size <= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMax.z &&
				pPos->y + max.y >= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMin.y &&
				pPos->y + min.y <= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMax.y
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
void CollisionExitShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_Exit[nCntExit].bUse == true)
		{
			if (
				pPos->y >= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMin.y &&
				pPos->y <= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMax.y &&
				pPos->x >= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMin.x &&
				pPos->x <= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMax.x &&
				pPos->z >= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMin.z &&
				pPos->z <= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMax.z
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = g_Exit[nCntExit].vtxMax.y;
			}
		}
	}
}
