//============================
//
//フィールド処理(porygon.cpp)
//Author:早川 友貴
//
//============================
#include "main.h"
#include "input.h"
#include "objectPoly.h"

//マクロ変数

//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObjectPoly= NULL;   //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureObjectPoly[MAX_OBJECTPOLY] = {};        //テクスチャのポインタ
ObjectPoly g_ObjectPoly[MAX_OBJECTPOLY];  // 床の情報

int EditIndexPoly;									//エディットモード用の番号
D3DXVECTOR3 EditPosPoly;							//エディットモードのオブジェクトの位置
float EditWightPoly;								//エディットモードのオブジェクトの位置
float EditHeightPoly;								//エディットモードのオブジェクトの位置
int g_ObjectObjectPolyCount;						//オブジェクトの数

//=============================
//フィールドの初期化処理
//=============================
void InitObjectPoly(void)
{
	int nCnt;

	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得

											 //テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"Data\\TEXTURE\\thumb_concrete.jpg",
	//	&g_pTextureObjectPoly[0]);

	//各種変数の初期化
	for (nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
	{
		g_ObjectPoly[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置を初期化
		g_ObjectPoly[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きを初期化
		g_ObjectPoly[nCnt].fWidth = 100.0f;							//幅を初期化
		g_ObjectPoly[nCnt].fHeight = 100.0f;						//高さを初期化
		g_ObjectPoly[nCnt].bUse = false;							//使用していない状態にする
	}

	EditIndexPoly = MAX_OBJECTPOLY - 1;								//エディットモード用の番号
	EditPosPoly = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//エディットモードのオブジェクトの位置
	EditWightPoly = g_ObjectPoly[0].fWidth;							//エディットモードのオブジェクトの位置
	EditHeightPoly = g_ObjectPoly[0].fHeight;						//エディットモードのオブジェクトの位置
	g_ObjectObjectPolyCount = 0;									//オブジェクトの数

														//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_OBJECTPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffObjectPoly,
		NULL);

	VERTEX_3D *pVtx; //頂点座標へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffObjectPoly->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntObjectPoly= 0; nCntObjectPoly< MAX_OBJECTPOLY; nCntObjectPoly++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_ObjectPoly[nCnt].fWidth, 0.0f, +g_ObjectPoly[nCnt].fHeight);
		pVtx[1].pos = D3DXVECTOR3(+g_ObjectPoly[nCnt].fWidth, 0.0f, +g_ObjectPoly[nCnt].fHeight);
		pVtx[2].pos = D3DXVECTOR3(-g_ObjectPoly[nCnt].fWidth, 0.0f, -g_ObjectPoly[nCnt].fHeight);
		pVtx[3].pos = D3DXVECTOR3(+g_ObjectPoly[nCnt].fWidth, 0.0f, -g_ObjectPoly[nCnt].fHeight);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffObjectPoly->Unlock();

}

//========================
//フィールドの終了処理
//========================
void UninitObjectPoly(void)
{
	for (int nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
		//テクスチャの破棄
		if (g_pTextureObjectPoly[nCnt] != NULL)
		{
			g_pTextureObjectPoly[nCnt]->Release();
			g_pTextureObjectPoly[nCnt] = NULL;
		}
}

//========================
//フィールドの更新処理
//========================
void UpdateObjectPoly(void)
{

	VERTEX_3D *pVtx; //頂点座標へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffObjectPoly->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntObjectPoly = 0; nCntObjectPoly< MAX_OBJECTPOLY; nCntObjectPoly++)
	{
		if (g_ObjectPoly[nCntObjectPoly].bUse == true)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_ObjectPoly[nCntObjectPoly].fWidth, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, +g_ObjectPoly[nCntObjectPoly].fHeight);
			pVtx[1].pos = D3DXVECTOR3(+g_ObjectPoly[nCntObjectPoly].fWidth, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, +g_ObjectPoly[nCntObjectPoly].fHeight);
			pVtx[2].pos = D3DXVECTOR3(-g_ObjectPoly[nCntObjectPoly].fWidth, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, -g_ObjectPoly[nCntObjectPoly].fHeight);
			pVtx[3].pos = D3DXVECTOR3(+g_ObjectPoly[nCntObjectPoly].fWidth, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, -g_ObjectPoly[nCntObjectPoly].fHeight);
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffObjectPoly->Unlock();
}

//========================
//フィールドのエディットモードでの更新処理
//========================
void UpdateEditObjectPoly(void)
{
	if (GetKeyboardPress(DIK_UP) == true)
	{//前移動
		EditPosPoly.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{//後ろ移動
		EditPosPoly.z -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{//右移動
		EditPosPoly.x += 1.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//左移動
		EditPosPoly.x -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{//上移動
		EditPosPoly.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_RCONTROL) == true)
	{//下移動
		EditPosPoly.y -= 1.0f;
	}

	if (GetKeyboardPress(DIK_6) == true)
	{//６キーで前のタイプのオブジェクトにする
		EditWightPoly++;
	}

	if (GetKeyboardPress(DIK_7) == true)
	{//７キーで前のタイプのオブジェクトにする
		EditWightPoly--;
	}

	if (GetKeyboardPress(DIK_8) == true)
	{//８キーで前のタイプのオブジェクトにする
		EditHeightPoly++;
	}

	if (GetKeyboardPress(DIK_9) == true)
	{//９キーで次のタイプのオブジェクトにする
		EditHeightPoly--;
	}


	//エディットモードの変更をオブジェクトに反映させる
	g_ObjectPoly[EditIndexPoly].pos = EditPosPoly;
	g_ObjectPoly[EditIndexPoly].fWidth = EditWightPoly;
	g_ObjectPoly[EditIndexPoly].fHeight = EditHeightPoly;

	//オブジェクトの削除処理(重なっているもの)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObjectPoly(g_ObjectPoly[EditIndexPoly].pos, 20.0f);
	}

	//オブジェクトの設置処理----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObjectPoly(g_ObjectPoly[EditIndexPoly].pos, g_ObjectPoly[EditIndexPoly].fWidth, g_ObjectPoly[EditIndexPoly].fHeight);
	}

	VERTEX_3D *pVtx; //頂点座標へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffObjectPoly->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (MAX_OBJECTPOLY - 1) * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-g_ObjectPoly[EditIndexPoly].fWidth, 0.0f, +g_ObjectPoly[EditIndexPoly].fHeight);
	pVtx[1].pos = D3DXVECTOR3(+g_ObjectPoly[EditIndexPoly].fWidth, 0.0f, +g_ObjectPoly[EditIndexPoly].fHeight);
	pVtx[2].pos = D3DXVECTOR3(-g_ObjectPoly[EditIndexPoly].fWidth, 0.0f, -g_ObjectPoly[EditIndexPoly].fHeight);
	pVtx[3].pos = D3DXVECTOR3(+g_ObjectPoly[EditIndexPoly].fWidth, 0.0f, -g_ObjectPoly[EditIndexPoly].fHeight);

	//頂点バッファをアンロックする
	g_pVtxBuffObjectPoly->Unlock();
}



//========================
//フィールドの描画処理
//========================
void DrawObjectPoly(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	for (int nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_ObjectPoly[nCnt].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_ObjectPoly[nCnt].rot.y, g_ObjectPoly[nCnt].rot.x, g_ObjectPoly[nCnt].rot.z);

		D3DXMatrixMultiply(&g_ObjectPoly[nCnt].mtxWorld,
			&g_ObjectPoly[nCnt].mtxWorld,
			&mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_ObjectPoly[nCnt].pos.x, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z);

		D3DXMatrixMultiply(&g_ObjectPoly[nCnt].mtxWorld, &g_ObjectPoly[nCnt].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_ObjectPoly[nCnt].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffObjectPoly, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->SetTexture(0, g_pTextureObjectPoly[nCnt]);
		if (g_ObjectPoly[nCnt].bUse == true)
		{
			//フィールドの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //プリミティブの種類
		}
	}
}

//========================
//フィールドのエディットモードでの描画処理
//========================
void DrawEditObjectPoly(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_ObjectPoly[EditIndexPoly].mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_ObjectPoly[EditIndexPoly].rot.y, g_ObjectPoly[EditIndexPoly].rot.x, g_ObjectPoly[EditIndexPoly].rot.z);

	D3DXMatrixMultiply(&g_ObjectPoly[EditIndexPoly].mtxWorld,
		&g_ObjectPoly[EditIndexPoly].mtxWorld,
		&mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		g_ObjectPoly[EditIndexPoly].pos.x, g_ObjectPoly[EditIndexPoly].pos.y, g_ObjectPoly[EditIndexPoly].pos.z);

	D3DXMatrixMultiply(&g_ObjectPoly[EditIndexPoly].mtxWorld, &g_ObjectPoly[EditIndexPoly].mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_ObjectPoly[EditIndexPoly].mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffObjectPoly, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, g_pTextureObjectPoly[EditIndexPoly]);

	//フィールドの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, EditIndexPoly * 4, 2); //プリミティブの種類
}

//========================
//フィールドの設定処理
//========================
void SetObjectPoly(D3DXVECTOR3 pos, float Wight, float Height)
{
	for (int nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
	{
		if (g_ObjectPoly[nCnt].bUse == false)
		{
			g_ObjectPoly[nCnt].pos = pos;	//位置を設定
			g_ObjectPoly[nCnt].fWidth = Wight;						//幅を設定
			g_ObjectPoly[nCnt].fHeight = Height;						//高さを設定

			g_ObjectObjectPolyCount++;

			g_ObjectPoly[nCnt].bUse = true;							//使用している状態にする

			break;
		}

	}
}

//========================
//フィールドの削除処理
//========================
void EditCollisionObjectPoly(D3DXVECTOR3 pos, float Size)
{
	for (int nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
	{
		if (g_ObjectPoly[nCnt].bUse == true)
		{
			if (
				pos.x + Size >= g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWidth
				&& pos.x - Size <= g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWidth
				&& pos.z + Size >= g_ObjectPoly[nCnt].pos.z - g_ObjectPoly[nCnt].fHeight
				&& pos.z - Size <= g_ObjectPoly[nCnt].pos.z + g_ObjectPoly[nCnt].fHeight
				)
			{//オブジェクト同士が重なっている
				g_ObjectPoly[nCnt].bUse = false;
				g_ObjectObjectPolyCount--;
			}
		}
	}
}

//====================================================================
//外積を使ったオブジェクトの当たり判定
//====================================================================
D3DXVECTOR3 CollisionOuterProductObjectPoly(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	//移動ベクトルを割り出す
	D3DXVECTOR3 vecMove = *pPos - *pPosOld;
	//座標保管用
	int nPosCount = 0;
	D3DXVECTOR3 pos[MAX_OBJECTPOLY * 4] = {};
	for (int nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
	{
		if (g_ObjectPoly[nCnt].bUse == true)
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
					pos0 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z + g_ObjectPoly[nCnt].fHeight);
					pos1 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z + g_ObjectPoly[nCnt].fHeight);
					break;
				case 1:
					pos0 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z + g_ObjectPoly[nCnt].fHeight);
					pos1 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z - g_ObjectPoly[nCnt].fHeight);
					break;
				case 2:
					pos0 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z - g_ObjectPoly[nCnt].fHeight);
					pos1 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z - g_ObjectPoly[nCnt].fHeight);
					break;
				case 3:
					pos0 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z - g_ObjectPoly[nCnt].fHeight);
					pos1 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z + g_ObjectPoly[nCnt].fHeight);
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

	return pos[0];
}

//====================================================================
//ポリゴンとの当たり判定処理
//====================================================================
bool CollisionObjectPoly(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECTPOLY; nCntObject++)
	{
		if (g_ObjectPoly[nCntObject].bUse == true)
		{
			if (
				(
				pPos->x + Size >= g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth &&
				pPos->x - Size <= g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth &&
				pPos->z + Size >= g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight &&
				pPos->z - Size <= g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight
				))
			{//壁とプレイヤーが当たった(X軸)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bHit = true;
			}

			if (fabsf(pMove->x) >= fabsf(pMove->z))
			{
				if (
					(
						pPos->z + Size >= g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight && pPosOld->z + Size < g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight ||
						pPos->z - Size <= g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight && pPosOld->z - Size > g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight) &&
					pPos->x + Size >= g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth &&
					pPos->x - Size <= g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth 
					)
				{//壁とプレイヤーが当たった(Z軸)
					pPos->z = pPosOld->z;
					pMove->z = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->x + Size >= g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth && pPosOld->x + Size < g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth ||
						pPos->x - Size <= g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth && pPosOld->x - Size > g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth) &&
					pPos->z + Size >= g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight &&
					pPos->z - Size <= g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight 
					
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
						pPos->x + Size >= g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth && pPosOld->x + Size < g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth ||
						pPos->x - Size <= g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth && pPosOld->x - Size > g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth) &&
					pPos->z + Size >= g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight &&
					pPos->z - Size <= g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight 
					)
				{//壁とプレイヤーが当たった(X軸)
					pPos->x = pPosOld->x;
					pMove->x = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->z + Size >= g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight && pPosOld->z + Size < g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight ||
						pPos->z - Size <= g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight && pPosOld->z - Size > g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight) &&
					pPos->x + Size >= g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth &&
					pPos->x - Size <= g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth 
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
//オブジェクトPolyの所得
//====================================================================
ObjectPoly * GetObjectPoly(void)
{
	return &g_ObjectPoly[0];
}
