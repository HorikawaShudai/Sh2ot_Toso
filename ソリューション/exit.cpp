//========================================================================================
//
// 出口の処理[exit.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include <stdio.h>
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
#include "debugproc.h"
#include "ActionHelpUI.h"
#include "EscapeTutorial.h"
#include "CheckboxUI.h"

const char *c_apExit[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\Exit\\BigDoorFrame00.x",
	"Data\\MODEL\\Exit\\BigDoor_UP.x",
	"Data\\MODEL\\Exit\\BigDoor_L.x",
	"Data\\MODEL\\Exit\\BigDoor_R.x",
};

//プロトタイプ宣言
void DoorOpen(void);
void ExsitClossLine(int nCntExit);

void CollisionRotExit(int nCnt);

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExit[64][EXIT_TYPE_MAX] = {};		//テクスチャのポインタ
LPD3DXMESH g_pMeshExit[EXIT_TYPE_MAX] = {};						//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatExit[EXIT_TYPE_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatExit[EXIT_TYPE_MAX] = {};						//マテリアルの数

EXIT g_aExit[MAX_EXIT];					//オブジェクト00の情報
int g_KeyCount;							//必要になる鍵のカウント

bool g_bExitFade[MAX_EXIT];
bool g_bExitOK;
bool bLoadExitObj;

D3DXVECTOR3 g_vecToPos;
D3DXVECTOR3 g_vecLine;
D3DXVECTOR3 g_vecNor;
D3DXVECTOR3 g_vecMoveRef;

//====================================================================
//出口の初期化処理
//====================================================================
void InitExit(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PlayModeSelect PlayMode = GetPlayModeSelect();

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			g_aExit[nCntExit].parts[nCntExit1].pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExit[nCntExit].parts[nCntExit1].posOld		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExit[nCntExit].parts[nCntExit1].move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExit[nCntExit].parts[nCntExit1].rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExit[nCntExit].parts[nCntExit1].rotSave		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExit[nCntExit].parts[nCntExit1].vtxMin		= D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
			g_aExit[nCntExit].parts[nCntExit1].vtxMax		= D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
			g_aExit[nCntExit].parts[nCntExit1].bUse			= false;
			g_aExit[nCntExit].parts[nCntExit1].bExitOK		= false;
			g_aExit[nCntExit].parts[nCntExit1].nType		= EXIT_TYPE_BIGFRAME;
			g_aExit[nCntExit].parts[nCntExit1].nExitOKcnt	= 120;

			g_aExit[nCntExit].bUse = false;
		}
	}

	g_vecToPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecLine = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecNor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecMoveRef = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_KeyCount = 0;
	g_bExitOK = false;
	bLoadExitObj = false;

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

	//出口の読み込み
	LoadExit();
}

//====================================================================
//出口の終了処理
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
//出口の更新処理
//====================================================================
void UpdateExit(void)
{
	//扉が開く処理
	DoorOpen();

	PrintDebugProc("%f\n", g_aExit[0].parts[3].rot.y);
}

//====================================================================
//出口の描画処理
//====================================================================
void DrawExit(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aExit[nCntExit].parts[nCntExit1].mtxWorld);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aExit[nCntExit].parts[nCntExit1].rot.y, g_aExit[nCntExit].parts[nCntExit1].rot.x, g_aExit[nCntExit].parts[nCntExit1].rot.z);

				D3DXMatrixMultiply(&g_aExit[nCntExit].parts[nCntExit1].mtxWorld, &g_aExit[nCntExit].parts[nCntExit1].mtxWorld, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aExit[nCntExit].parts[nCntExit1].pos.x, g_aExit[nCntExit].parts[nCntExit1].pos.y, g_aExit[nCntExit].parts[nCntExit1].pos.z);

				D3DXMatrixMultiply(&g_aExit[nCntExit].parts[nCntExit1].mtxWorld, &g_aExit[nCntExit].parts[nCntExit1].mtxWorld, &mtxTrans);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aExit[nCntExit].parts[nCntExit1].mtxWorld);

				//現在のマテリアルを所得
				pDevice->GetMaterial(&matDef);

				//マテリアルデータへのポインタを所得する
				pMat = (D3DXMATERIAL*)g_pBuffMatExit[g_aExit[nCntExit].parts[nCntExit1].nType]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_dwNumMatExit[g_aExit[nCntExit].parts[nCntExit1].nType]; nCntMat++)
				{

					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					if (g_aExit[nCntExit].parts[nCntExit1].bUse == true)
					{
						//テクスチャの設定
						pDevice->SetTexture(0, g_pTextureExit[nCntMat][g_aExit[nCntExit].parts[nCntExit1].nType]);

						//オブジェクト00(パーツ)の描画
						g_pMeshExit[g_aExit[nCntExit].parts[nCntExit1].nType]->DrawSubset(nCntMat);
					}
				}
				//保存していたマテリアルを戻す
				pDevice->SetMaterial(&matDef);
			}
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
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			//外積の脱出判定処理
			ExsitClossLine(nCntExit);

			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true && g_aExit[nCntExit].parts[nCntExit1].bExitOK == true)
			{//出口が使われていて脱出可能の場合
				if (g_aExit[nCntExit].parts[nCntExit1].nType != EXIT_TYPE_BIGFRAME)
				{//出口の種類がフレーム以外の場合

					if (g_aExit[nCntExit].parts[4].rotSave.y - 1.57f <= g_aExit[nCntExit].parts[4].rot.y)
					{
						g_aExit[nCntExit].parts[4].rot.y -= 0.007f;
					}
					
					if (g_aExit[nCntExit].parts[3].rotSave.y + 1.57f >= g_aExit[nCntExit].parts[3].rot.y)
					{
						g_aExit[nCntExit].parts[3].rot.y += 0.007f;
					}
				}

				//出口から出れるまでのカウント
				g_aExit[nCntExit].parts[3].nExitOKcnt--;
				g_aExit[nCntExit].parts[4].nExitOKcnt--;

				if (g_aExit[nCntExit].parts[3].nExitOKcnt <= 0 && g_aExit[nCntExit].parts[4].nExitOKcnt <= 0)
				{
					g_aExit[nCntExit].parts[3].nExitOKcnt = 0;
					g_aExit[nCntExit].parts[4].nExitOKcnt = 0;
				}
			}
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
//オブジェクト00の設定処理
//====================================================================
void SetExit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nNumExit)
{
	for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
	{
		if (g_aExit[nNumExit].parts[nCntExit1].bUse == false)
		{
			g_aExit[nNumExit].parts[nCntExit1].pos = pos;
			g_aExit[nNumExit].parts[nCntExit1].posOld = pos;
			g_aExit[nNumExit].parts[nCntExit1].rot = rot;
			g_aExit[nNumExit].parts[nCntExit1].rotSave = rot;
			g_aExit[nNumExit].parts[nCntExit1].nType = nType;
			if (g_aExit[nNumExit].parts[nCntExit1].nType == 1)
			{
				g_aExit[nNumExit].PseudoCenter = D3DXVECTOR3(g_aExit[nNumExit].parts[nCntExit1].pos.x, g_aExit[nNumExit].parts[nCntExit1].pos.y - 100.0f, g_aExit[nNumExit].parts[nCntExit1].pos.z);
			}

			g_aExit[nNumExit].parts[nCntExit1].bUse = true;

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

				if (g_aExit[nNumExit].parts[nCntExit1].vtxMin.x > vtx.x)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMin.x = vtx.x;
				}
				if (g_aExit[nNumExit].parts[nCntExit1].vtxMin.y > vtx.y)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMin.y = vtx.y;
				}
				if (g_aExit[nNumExit].parts[nCntExit1].vtxMin.z > vtx.z)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMin.z = vtx.z;
				}

				if (g_aExit[nNumExit].parts[nCntExit1].vtxMax.x < vtx.x)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMax.x = vtx.x;
				}
				if (g_aExit[nNumExit].parts[nCntExit1].vtxMax.y < vtx.y)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMax.y = vtx.y;
				}
				if (g_aExit[nNumExit].parts[nCntExit1].vtxMax.z < vtx.z)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshExit[nType]->UnlockVertexBuffer();

			//当たり判定を回転に対応
			CollisionRotExit(nNumExit);

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
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true && g_aExit[nCntExit].parts[nCntExit1].bExitOK == false)
			{
				if (   pPos->x >= g_aExit[nCntExit].PseudoCenter.x - Size
					&& pPos->x <= g_aExit[nCntExit].PseudoCenter.x + Size
					&& pPos->y >= g_aExit[nCntExit].PseudoCenter.y - Size
					&& pPos->y <= g_aExit[nCntExit].PseudoCenter.y + Size
					&& pPos->z >= g_aExit[nCntExit].PseudoCenter.z - Size
					&& pPos->z <= g_aExit[nCntExit].PseudoCenter.z + Size)

				{//アイテムとプレイヤーが当たった(X軸)
					bHit = true;
					g_KeyCount++;

					if (g_KeyCount > PlayNumber.CurrentSelectNumber - 1)
					{//鍵がプレイヤー人数分使われた場合
						g_bExitOK = true;

						g_aExit[nCntExit].parts[3].bExitOK = true;
						g_aExit[nCntExit].parts[4].bExitOK = true;
					}

					break;
				}
			}
		}
	}

	return bHit;
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
void CollisionExitHelpUI(D3DXVECTOR3 *pPos, float Size)
{
	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true && g_aExit[nCntExit].parts[nCntExit1].bExitOK == false && g_aExit[nCntExit].bHelpUI == false)
			{
				if (pPos->x >= g_aExit[nCntExit].PseudoCenter.x - Size
					&& pPos->x <= g_aExit[nCntExit].PseudoCenter.x + Size
					&& pPos->y >= g_aExit[nCntExit].PseudoCenter.y - Size
					&& pPos->y <= g_aExit[nCntExit].PseudoCenter.y + Size
					&& pPos->z >= g_aExit[nCntExit].PseudoCenter.z - Size
					&& pPos->z <= g_aExit[nCntExit].PseudoCenter.z + Size)

				{//アイテムとプレイヤーが当たった(X軸)
					g_aExit[nCntExit].bHelpUI = true;
					g_aExit[nCntExit].IndexUI = SetActionHelpUI(D3DXVECTOR3(g_aExit[nCntExit].PseudoCenter.x, g_aExit[nCntExit].PseudoCenter.y + 20.0f, g_aExit[nCntExit].PseudoCenter.z), ACTIONHELPUI_DOOR);
					break;
				}
			}

			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true && g_aExit[nCntExit].parts[nCntExit1].bExitOK == false && g_aExit[nCntExit].bHelpUI == true)
			{
				if (pPos->x <= g_aExit[nCntExit].PseudoCenter.x - Size
					|| pPos->x >= g_aExit[nCntExit].PseudoCenter.x + Size
					|| pPos->y <= g_aExit[nCntExit].PseudoCenter.y - Size
					|| pPos->y >= g_aExit[nCntExit].PseudoCenter.y + Size
					|| pPos->z <= g_aExit[nCntExit].PseudoCenter.z - Size
					|| pPos->z >= g_aExit[nCntExit].PseudoCenter.z + Size)

				{//アイテムとプレイヤーが当たった(X軸)
					g_aExit[nCntExit].bHelpUI = false;
					FalseActionHelpUI(g_aExit[nCntExit].IndexUI);
					break;
				}
			}
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
bool CollisionExi(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true && g_aExit[nCntExit].parts[nCntExit1].nExitOKcnt >= 1)
			{
				if (
					(
						pPos->y + max.y >= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMin.y && pPosOld->y + max.y< g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMin.y ||
						pPos->y + min.y <= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMax.y && pPosOld->y + min.y > g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMax.y) &&
					pPos->x + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMin.x &&
					pPos->x - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMax.x &&
					pPos->z + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMin.z &&
					pPos->z - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMax.z
					)
				{//壁とプレイヤーが当たった(X軸)
					pPos->y = pPosOld->y;
					pMove->y = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->z + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMin.z && pPosOld->z + Size < g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMin.z ||
						pPos->z - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMax.z && pPosOld->z - Size > g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMax.z) &&
					pPos->x + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMin.x &&
					pPos->x - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMax.x &&
					pPos->y + max.y >= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMin.y&&
					pPos->y + min.y <= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMax.y
					)
				{//壁とプレイヤーが当たった(Z軸)
					pPos->z = pPosOld->z;
					pMove->z = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->x + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMin.x && pPosOld->x + Size < g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMin.x ||
						pPos->x - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMax.x && pPosOld->x - Size > g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMax.x) &&
					pPos->z + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMin.z &&
					pPos->z - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMax.z &&
					pPos->y + max.y >= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMin.y &&
					pPos->y + min.y <= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMax.y
					)
				{//壁とプレイヤーが当たった(X軸)
					pPos->x = pPosOld->x;
					pMove->x = 0.0f;
					bHit = true;
				}
			}
		}
	}
	return bHit;
}

//====================================================================
//オブジェクトの当たり判定を回転させる処理
//====================================================================
void CollisionRotExit(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
	{
		MaxZ = g_aExit[nCnt].parts[nCntExit1].vtxMax.z;
		MaxX = g_aExit[nCnt].parts[nCntExit1].vtxMax.x;
		MinZ = g_aExit[nCnt].parts[nCntExit1].vtxMin.z;
		MinX = g_aExit[nCnt].parts[nCntExit1].vtxMin.x;


		if (g_aExit[nCnt].parts[nCntExit1].rot.y <= 0.0f)
		{
			g_aExit[nCnt].parts[nCntExit1].vtxMax.z = MaxZ;
			g_aExit[nCnt].parts[nCntExit1].vtxMax.x = MaxX;
			g_aExit[nCnt].parts[nCntExit1].vtxMin.z = MinZ;
			g_aExit[nCnt].parts[nCntExit1].vtxMin.x = MinX;
		}
		else if (g_aExit[nCnt].parts[nCntExit1].rot.y <= 1.57f)
		{
			g_aExit[nCnt].parts[nCntExit1].vtxMax.z = -MinX;
			g_aExit[nCnt].parts[nCntExit1].vtxMax.x = MaxZ;
			g_aExit[nCnt].parts[nCntExit1].vtxMin.z = -MaxX;
			g_aExit[nCnt].parts[nCntExit1].vtxMin.x = MinZ;
		}
		else if (g_aExit[nCnt].parts[nCntExit1].rot.y <= 3.14f)
		{
			g_aExit[nCnt].parts[nCntExit1].vtxMax.z = -MinZ;
			g_aExit[nCnt].parts[nCntExit1].vtxMax.x = -MinX;
			g_aExit[nCnt].parts[nCntExit1].vtxMin.z = -MaxZ;
			g_aExit[nCnt].parts[nCntExit1].vtxMin.x = -MaxX;
		}
		else if (g_aExit[nCnt].parts[nCntExit1].rot.y <= 4.71f)
		{
			g_aExit[nCnt].parts[nCntExit1].vtxMax.z = MaxX;
			g_aExit[nCnt].parts[nCntExit1].vtxMax.x = -MinZ;
			g_aExit[nCnt].parts[nCntExit1].vtxMin.z = MinX;
			g_aExit[nCnt].parts[nCntExit1].vtxMin.x = -MaxZ;
		}
	}
}

//====================================================================
//影との当たり判定処理
//====================================================================
void CollisionExitShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true)
			{
				if (
					pPos->y >= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMin.y &&
					pPos->y <= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMax.y &&
					pPos->x >= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMin.x &&
					pPos->x <= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMax.x &&
					pPos->z >= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMin.z &&
					pPos->z <= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMax.z
					)
				{//壁とプレイヤーが当たった(X軸)
					pPos->y = g_aExit[nCntExit].parts[nCntExit1].vtxMax.y;
				}
			}
		}
	}
}

//====================================================================
//出口の読み込み(.txt)
//====================================================================
void LoadExit(void)
{
	//変数宣言
	char not[128];			//使用しない文字列のゴミ箱
	int number;				//使用する出口の配列番号
	int nSetCnt = 0;
	FILE *pFile;			//ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("Data\\TEXT\\Exit_tousou.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
		while (strcmp("END_SCRIPT", &not[0]) != 0)			//END_SCRIPTが読み込めたら0を返し処理を抜ける 0以外の時は繰り返す
		{
			fscanf(pFile, "%s", &not[0]);					//文字列を読み込む

			if (strcmp("SCRIPT", &not[0]) == 0)			//SCRIPTが読み込めたら0を返し処理を開始する 0以外の時は開始しない
			{
				bLoadExitObj = true;			//読み込みを開始する
			}

			if (bLoadExitObj == true)
			{//読み込みが開始された場合
				if (strcmp("EXITSET", &not[0]) == 0)
				{//指定の文字列が読み込めた場合
					fscanf(pFile, "%s", &not[0]);										//文字を読み込む
					fscanf(pFile, "%s", &not[0]);										//=を読み込む
					fscanf(pFile, "%d", &number);										//配列番号を読み込む

					fscanf(pFile, "%s", &not[0]);										//文字を読み込む
					fscanf(pFile, "%s", &not[0]);										//=を読み込む
					fscanf(pFile, "%f", &g_aExit[number].parts[nSetCnt].pos.x);
					fscanf(pFile, "%f", &g_aExit[number].parts[nSetCnt].pos.y);
					fscanf(pFile, "%f", &g_aExit[number].parts[nSetCnt].pos.z);

					fscanf(pFile, "%s", &not[0]);										//文字を読み込む
					fscanf(pFile, "%s", &not[0]);										//=を読み込む
					fscanf(pFile, "%f", &g_aExit[number].parts[nSetCnt].rot.x);
					fscanf(pFile, "%f", &g_aExit[number].parts[nSetCnt].rot.y);
					fscanf(pFile, "%f", &g_aExit[number].parts[nSetCnt].rot.z);

					fscanf(pFile, "%s", &not[0]);										//文字を読み込む
					fscanf(pFile, "%s", &not[0]);										//=を読み込む
					fscanf(pFile, "%d", &g_aExit[number].parts[nSetCnt].nType);
				}
				if (strcmp("END_EXSITSET", &not[0]) == 0)
				{//指定の文字列が読み込めた場合
				 //出口の設置
					SetExit(g_aExit[number].parts[nSetCnt].pos, g_aExit[number].parts[nSetCnt].rot, g_aExit[number].parts[nSetCnt].nType, number);

					nSetCnt++;
				}
				if (strcmp("SETEND_PARTS", &not[0]) == 0)
				{//指定の文字列が読み込めた場合
					nSetCnt = 0;			//カウントを0にする
				}
			}

			if (strcmp("END_SCRIPT", &not[0]) == 0)
			{//SCRIPTが読み込めなかった場合
				bLoadExitObj = false;			//読み込みを終了
				break;			//処理を抜ける
			}
		}
	}
}

