//============================
//
//スコアアイテム処理(model.cpp)
//Author:早川 友貴
//
//============================
#include "main.h"
#include "camera.h"
//#include "shadow.h"
//#include "enemy.h"
#include "player.h"
#include "score.h"
#include "score_item.h"

//マクロ定義
#define NUM_ITEM (100)  //使うアイテムの量

//グローバル
ITEM g_Item[MAX_ITEM]; //スコアアイテムの情報
ITEMDATA g_Itemdata[NUM_ITEM]; //スコアアイテムデータ
int ItemCnt;  //スコアアイテムの数
FILE *pFile;
//int g_BulletCnt;							//弾の数を数える
//int g_nldxShadow = -1; //対象の影のインデックス(番号)

//====================
//スコアアイテムの初期化
//====================
void InitItem(void)
{
	int nCntItem;

	int nNumVtx;  //頂点数

	DWORD dwSizeFVF;  //頂点フォーマットのサイズ

	BYTE *pVtxBUff;  //頂点バッファのポインタ

	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		//各種変数の初期化
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //アイテムの位置を初期化
		g_Item[nCntItem].bUse = false;  //使っているかどうかを初期化
	}
	//g_BulletCnt = 0;

	////影を設定
	//g_nldxShadow = SetShadow();


	//Xファイルの読み込み
	D3DXLoadMeshFromX("Data\\MODEL\\jewelry.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Itemdata[0].pBuffMat,
		NULL,
		&g_Itemdata[0].dwNumMat,
		&g_Itemdata[0].pMesh);

	D3DXMATERIAL *pMat; //マテリアルへのポインタ

						//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)g_Itemdata[0].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Itemdata[0].dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルネームが存在する
		 //テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Itemdata[0]._apTexture[nCntMat]);
		}
	}

	////Xファイルの読み込み
	//D3DXLoadMeshFromX("data\\MODEL\\sword.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_pBuffMatEnemy[1],
	//	NULL,
	//	&g_dwNumMatEnemy[1],
	//	&g_pMeshEnemy[1]);

	////Xファイルの読み込み
	//D3DXLoadMeshFromX("data\\MODEL\\apart.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_pBuffMatEnemy[2],
	//	NULL,
	//	&g_dwNumMatEnemy[2],
	//	&g_pMeshEnemy[2]);

	//頂点数の取得
	nNumVtx = g_Itemdata[0].pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_Itemdata[0].pMesh->GetFVF());

	//頂点バッファをロック
	g_Itemdata[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

	//スコアアイテムの最大値・最小値を抜き出し
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

		if (vtx.x > g_Item[0].VtxMax.x)
		{
			g_Itemdata[0].VtxMax.x = vtx.x;
		}

		if (vtx.x <g_Item[0].VtxMin.x)
		{
			g_Itemdata[0].VtxMin.x = vtx.x;
		}

		if (vtx.y > g_Item[0].VtxMax.y)
		{
			g_Itemdata[0].VtxMax.y = vtx.y;
		}

		if (vtx.y < g_Item[0].VtxMin.y)
		{
			g_Itemdata[0].VtxMin.y = vtx.y;
		}

		if (vtx.z > g_Item[0].VtxMax.z)
		{
			g_Itemdata[0].VtxMax.z = vtx.z;
		}

		if (vtx.z < g_Item[0].VtxMin.z)
		{
			g_Itemdata[0].VtxMin.z = vtx.z;
		}

		pVtxBUff += dwSizeFVF;	//頂点フォーマットのサイズ分ぼいんを進める
	}

	//頂点バッファをアンロック
	g_Itemdata[0].pMesh->UnlockVertexBuffer();
}

//====================
//スコアアイテムの終了処理
//====================
void UninitItem(void)
{
	for (int nCntdata = 0; nCntdata < NUM_ITEM; nCntdata++)
	{
		//メッシュの破棄
		if (g_Itemdata[nCntdata].pMesh != NULL)
		{
			g_Itemdata[nCntdata].pMesh->Release();
			g_Itemdata[nCntdata].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_Itemdata[nCntdata].pBuffMat != NULL)
		{
			g_Itemdata[nCntdata].pBuffMat->Release();
			g_Itemdata[nCntdata].pBuffMat = NULL;
		}

		for (int nCntTex = 0; nCntTex < 20; nCntTex++)
		{
			if (g_Itemdata[nCntdata]._apTexture[nCntTex] != NULL)
			{
				g_Itemdata[nCntdata]._apTexture[nCntTex]->Release();
				g_Itemdata[nCntdata]._apTexture[nCntTex] = NULL;
			}
		}
	}
}

////====================
////スコアアイテムの更新処理
////====================
//void UpdateItem(void)
//{
//	int nCntItem;
//
//	if (ItemCnt <= 0)
//	{
//		//スコアアイテムのリスポーン処理
//		ReturnItem();
//	}
//
//	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
//	{
//		if (g_Item[nCntItem].bUse == true)
//		{
//			//古い位置を更新
//			g_Item[nCntItem].posold = g_Item[nCntItem].pos;
//
//		}
//	}
//
//	//スコアアイテムの角度
//	AngleEnemy();
//
//	//スコアアイテムの状態
//	EnemyState();
//}
//
////====================
////スコアアイテムの描画処理
////====================
//void DrawItem(void)
//{
//	int nCnt;
//
//	//デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
//
//	D3DMATERIAL9 matDef;  //現在のマテリアル保存用
//
//	D3DXMATERIAL *pMat;	  //マテリアルデータへのポインタ
//
//						  /*D3DXMATERIAL *RedMat;*/
//
//						  /*RedMat->MatD3D.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//						  RedMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//						  RedMat->MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);*/
//
//
//	for (nCnt = 0; nCnt < NUM_ITEM; nCnt++)
//	{
//		if (g_Item[nCnt].bUse == true)
//		{
//			//ワールドマトリックスの初期化
//			D3DXMatrixIdentity(&g_Item[nCnt].mtxWorld);
//
//			//向きを反映
//			D3DXMatrixRotationYawPitchRoll(&mtxRot,
//				g_Item[nCnt].rot.y, g_Item[nCnt].rot.x, g_Item[nCnt].rot.z);
//
//			D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld,
//				&g_Item[nCnt].mtxWorld,
//				&mtxRot);
//
//			//位置を反映
//			D3DXMatrixTranslation(&mtxTrans,
//				g_Item[nCnt].pos.x, g_Item[nCnt].pos.y, g_Item[nCnt].pos.z);
//
//			D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxTrans);
//
//			//ワールドマトリックスの設定
//			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCnt].mtxWorld);
//
//			//現在のマテリアルを取得
//			pDevice->GetMaterial(&matDef);
//
//			//マテリアルデータへのポインタを取得
//			pMat = (D3DXMATERIAL*)g_Item[nCnt].Itemdata.pBuffMat->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_Item[nCnt].Itemdata.dwNumMat; nCntMat++)
//			{
//				//テクスチャの設定
//				pDevice->SetTexture(0, g_Itemdata[nCnt]._apTexture[nCntMat]);
//
//				//スコアアイテム(パーツ)の描画
//				g_Item[nCnt].Itemdata.pMesh->DrawSubset(nCntMat);
//			}
//
//			//保存していたマテリアルを戻す
//			pDevice->SetMaterial(&matDef);
//		}
//	}
//}
//
////======================================
////スコアアイテムの設定
////======================================
//void SetEnemy(D3DXVECTOR3 pos)
//{
//	int nCnt;
//
//	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得
//
//	for (nCnt = 0; nCnt < NUM_ITEM; nCnt++)
//	{
//		if (g_Item[nCnt].bUse == false)
//		{
//			g_Item[nCnt].pos = pos;
//			g_Item[nCnt].bUse = true;
//
//			g_Item[nCnt].Itemdata.pBuffMat = g_Item[0].Itemdata.pBuffMat;
//			g_Item[nCnt].Itemdata.dwNumMat = g_Item[0].Itemdata.dwNumMat;
//
//			g_Item[nCnt].Itemdata.pMesh = g_Item[0].Itemdata.pMesh;
//
//			for (int nCntMat = 0; nCntMat < 20; nCntMat++)
//			{
//				g_Item[nCnt].Itemdata._apTexture[nCntMat] = g_Itemdata[0]._apTexture[nCntMat];
//			}
//
//			//スコアアイテムの数を数える処理
//			ItemCnt++;
//
//			break;
//		}
//	}
//
//}

////====================================
////スコアアイテムの情報を取得
////====================================
//ENEMY *GetEnemy(void)
//{
//	return &g_Enemy[0];
//}

////===========================================
////スコアアイテムのヒット処理
////===========================================
//void HitEnemy(int nCntEnemy, int nDamage)
//{
//	//int nCntRed;  //赤い状態を数える処理
//
//	g_Enemy[nCntEnemy].nLife -= nDamage;
//
//	if (g_Enemy[nCntEnemy].nLife <= 0)
//	{//スコアアイテムが死んだ処理
//
//	 /*SetExplosion(g_Enemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/
//		SetParticle(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, (g_Enemy[nCntEnemy].pos.y), g_Enemy[nCntEnemy].pos.z),
//			D3DXVECTOR3(g_Enemy[nCntEnemy].move.x, g_Enemy[nCntEnemy].move.y + MOVE_PPARTICL, g_Enemy[nCntEnemy].move.z),
//			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
//			1.0f,
//			PARTICLE_DAMAGE,
//			PARTICLE_PUSELIF);
//
//		//スコアを加算する処理
//		AddScore(g_Enemy[nCntEnemy].type);
//
//		//影を消す処理
//		ResetShadow(g_Enemy[nCntEnemy].nldxShadow);
//
//		//スコアアイテムの姿を消す処理
//		g_Enemy[nCntEnemy].bUse = false;
//
//		//スコアアイテムの数を減らす処理
//		EnemyCnt--;
//
//		//音を使うようにする
//		g_Enemy[nCntEnemy].bSound = true;
//
//	}
//
//	else
//	{//スコアアイテムのライフが残っている処理
//
//		g_Enemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;
//
//		EnemyState();
//
//		/*	pMat[nCntEnemy].MatD3D.Ambient = D3DXCOLOR(1.0f,0.0f,0.0f, 1.0f);
//
//		pMat[nCntEnemy].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//
//		pMat[nCntEnemy].MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);*/
//
//		/*for (nCntRed = 0; nCntRed < 560; nCntRed++)
//		{
//		if (nCntRed < 560)
//		{
//		pMat->MatD3D.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		}
//		}*/
//	}
//}
//
//
//////=============================
//////ポリゴンの位置を与える処理
//////=============================
////D3DXVECTOR3 PosEnemy(void)
////{
////	int nCnt;
////
////	for(nCnt = 0; nCnt < MAX_ENEMY)
////  return g_Enemy[nCnt].pos;
////	
////}
////
//////===========================
//////ポリゴンの向きを教える処理
//////===========================
////D3DXVECTOR3 RotEnemy(void)
////{
////	
////		return g_Enemy[nCnt].rot;
////}
//
////==================================
////スコアアイテムの移動処理
////==================================
//void MoveEnemy(void)
//{
//	//D3DXVECTOR3 Camrot = Getrot();
//
//	//float fRotMove = g_Enemy[nCntEnemy].rot.y;
//	//float fRotDest = g_Enemy[nCntEnemy].rot.y; //目標の角度
//	//float fRotDiff = 0.0f; //目標と現在角度の差分
//
//	//for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
//	//{
//	//	if (g_Enemy[nCnt].VtxMin.y > 0)
//	//	{
//	//		g_Enemy[nCnt].pos.y -= 0.1f;
//	//	}
//
//	//	if(g_Enemy[nCnt].VtxMin.y <= 0)
//	//	{
//	//		g_Enemy[nCnt].pos.y = 0.0f;
//	//	}
//	//}
//
//	////発射間隔を初期化
//	//if (g_BulletCnt > 0)
//	//{
//	//	g_BulletCnt--;
//	//}
//
//	//if (g_posModel.x <= -90.0f)
//	//{
//	//	g_posModel.x = -90.0f;
//	//}
//
//	//if (g_posModel.x >= 90.0f)
//	//{
//	//	g_posModel.x = 90.0f;
//	//}
//
//	//if (g_posModel.y <= 0.0f)
//	//{
//	//	g_posModel.y = 0.0f;
//	//}
//
//	//if (g_posModel.y >= 90.0f)
//	//{
//	//	g_posModel.y = 90.0f;
//	//}
//
//	//if (g_posModel.z >= 90.0f && g_posModel.x >= -90.0f)
//	//{
//	//	g_posModel.z = 90.0f;
//	//}
//
//	//if (g_posModel.z <= -90.0f && g_posModel.x <= 90.0f)
//	//{
//	//	g_posModel.z = -90.0f;
//	//}
//
//	//
//
//	////射撃処理
//	//if (GetKeyboardTrigger(DIK_SPACE) == true && g_BulletCnt <= 0)
//	//{//スペースキーが押されたとき発射
//
//	// //連続発射間隔
//	//	g_BulletCnt = SHOTSPACE;
//
//	//	SetBullet(D3DXVECTOR3(g_posModel.x, g_posModel.y, g_posModel.z),
//	//		D3DXVECTOR3(sinf(g_rotModel.y), 0.0f, cosf(g_rotModel.y)),
//	//		g_rotModel, 1, BULLETTYPE_PLAYER,
//	//		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//	//}
//
//	////影の位置を設定
//	//SetPositionShadow(g_nldxShadow, D3DXVECTOR3(g_posModel.x, 0.0f, g_posModel.z));
//}
//
////==================================
////スコアアイテムの角度処理
////==================================
//void AngleEnemy(void)
//{
//	D3DXVECTOR3 Posplayer = PosPlayer();
//	int nTime = GetTime();
//
//	for (int nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
//	{
//		D3DXVECTOR3 vecLine0 = D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x + 100.0f, 0.0f, g_Enemy[nCntEnemy].pos.z + 100.0f) - D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
//		D3DXVECTOR3 vecToPos0 = D3DXVECTOR3(Posplayer.x, Posplayer.y, Posplayer.z) - D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x + 100.0f, 0.0f, g_Enemy[nCntEnemy].pos.z + 100.0f);
//
//		D3DXVECTOR3 vecLine1 = D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x - 100.0f, 0.0f, g_Enemy[nCntEnemy].pos.z + 100.0f) - D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
//		D3DXVECTOR3 vecToPos1 = D3DXVECTOR3(Posplayer.x, Posplayer.y, Posplayer.z) - D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x - 100.0f, 0.0f, g_Enemy[nCntEnemy].pos.z + 100.0f);
//
//		/*	if ((vecLine0.z * vecToPos0.x) - (vecLine0.x * vecToPos0.z) >= -1
//		&& (vecLine1.z * vecToPos1.x) - (vecLine1.x * vecToPos1.z) <= 1)*/
//		if (Posplayer.z <= g_Enemy[nCntEnemy].pos.z + ENEMY_SIGHT_Z && Posplayer.z >= g_Enemy[nCntEnemy].pos.z - ENEMY_SIGHT_Z &&
//			Posplayer.x >= g_Enemy[nCntEnemy].pos.x - ENEMY_SIGHT_X && Posplayer.x <= g_Enemy[nCntEnemy].pos.x + ENEMY_SIGHT_X)
//		{
//			float fRotMove = g_Enemy[nCntEnemy].rot.y;
//			float fRotDest = g_Enemy[nCntEnemy].rot.y; //目標の角度
//			float fRotDiff = 0.0f; //目標と現在角度の差分
//
//								   ////視点を固定する場合
//			g_Enemy[nCntEnemy].rot.y = atan2f
//			(//対角線の角度
//				g_Enemy[nCntEnemy].pos.x - Posplayer.x,
//				g_Enemy[nCntEnemy].pos.z - Posplayer.z
//			);
//
//			//目標の角度との差分を求める処理
//			fRotDiff = fRotDest - fRotMove;
//
//			////目標の角度の補正
//			//if (fRotDiff > D3DX_PI)
//			//{
//			//	fRotDiff += -D3DX_PI * 2;
//			//}
//
//			//else if (fRotDiff < -D3DX_PI)
//			//{
//			//	fRotDiff += D3DX_PI * 2;
//			//}
//
//			//減衰処理
//			g_Enemy[nCntEnemy].move.x += (0.0f - g_Enemy[nCntEnemy].move.x) * 0.15f;
//			g_Enemy[nCntEnemy].move.y += (0.0f - g_Enemy[nCntEnemy].move.y) * 0.15f;
//			g_Enemy[nCntEnemy].move.z += (0.0f - g_Enemy[nCntEnemy].move.z) * 0.15f;
//
//			//移動量を位置に代入する
//			g_Enemy[nCntEnemy].pos += g_Enemy[nCntEnemy].move;
//
//			////目的の位置まで補正する処理
//			//	fRotDiff = fRotDest - fRotMove;
//
//			//	DiffEnemy[nCntEnemy].x = g_Enemy[nCntEnemy].posDest.x - g_Enemy[nCntEnemy].pos.x;
//
//			//	DiffEnemy[nCntEnemy].z = g_Enemy[nCntEnemy].posDest.z - g_Enemy[nCntEnemy].pos.z;
//
//			////目的の位置まで補正する処理
//			//g_Enemy[nCntEnemy].pos.x += DiffEnemy[nCntEnemy].x * 0.05f;
//
//			//g_Enemy[nCntEnemy].pos.z += DiffEnemy[nCntEnemy].z * 0.05f;
//
//			////目的のプレイヤーまでの向きを設定
//			//g_Enemy[nCntEnemy].rot.y += fRotDiff * 0.05f;
//
//			////プレイヤーの角度の補正
//			//if (g_Enemy[nCntEnemy].rot.y > D3DX_PI)
//			//{
//			//	g_Enemy[nCntEnemy].rot.y += -D3DX_PI * 2;
//			//}
//
//			//else if (g_Enemy[nCntEnemy].rot.y < -D3DX_PI)
//			//{
//			//	g_Enemy[nCntEnemy].rot.y += D3DX_PI * 2;
//			//}
//
//			if (nTime <= 99 && nTime >= 70)
//			{
//				//スコアアイテムをプレイヤーの方向へ移動させる処理
//				g_Enemy[nCntEnemy].move.x = -sinf(g_Enemy[nCntEnemy].rot.y) * ENEMY_SPEED;
//				g_Enemy[nCntEnemy].move.z = -cosf(g_Enemy[nCntEnemy].rot.y) * ENEMY_SPEED;
//			}
//
//			if (nTime <= 69 && nTime >= 40)
//			{
//				//スコアアイテムをプレイヤーの方向へ移動させる処理
//				g_Enemy[nCntEnemy].move.x = -sinf(g_Enemy[nCntEnemy].rot.y) * 3.0f;
//				g_Enemy[nCntEnemy].move.z = -cosf(g_Enemy[nCntEnemy].rot.y) * 3.0f;
//			}
//
//			if (nTime <= 39 && nTime >= 15)
//			{
//				//スコアアイテムをプレイヤーの方向へ移動させる処理
//				g_Enemy[nCntEnemy].move.x = -sinf(g_Enemy[nCntEnemy].rot.y) * 4.5f;
//				g_Enemy[nCntEnemy].move.z = -cosf(g_Enemy[nCntEnemy].rot.y) * 4.5f;
//			}
//
//			if (nTime <= 15 && nTime >= 0)
//			{
//				//スコアアイテムをプレイヤーの方向へ移動させる処理
//				g_Enemy[nCntEnemy].move.x = -sinf(g_Enemy[nCntEnemy].rot.y) * 6.5f;
//				g_Enemy[nCntEnemy].move.z = -cosf(g_Enemy[nCntEnemy].rot.y) * 6.5f;
//			}
//		}
//
//		else
//		{
//			float fRotMove = g_Enemy[nCntEnemy].rot.y;
//			float fRotDest = g_Enemy[nCntEnemy].rot.y; //目標の角度
//			float fRotDiff = 0.0f; //目標と現在角度の差分
//
//								   ////視点を固定する場合
//			g_Enemy[nCntEnemy].rot.y = atan2f
//			(//対角線の角度
//				g_Enemy[nCntEnemy].pos.x - Posplayer.x,
//				g_Enemy[nCntEnemy].pos.z - Posplayer.z
//			);
//
//			//目標の角度との差分を求める処理
//			fRotDiff = fRotDest - fRotMove;
//
//			////目標の角度の補正
//			//if (fRotDiff > D3DX_PI)
//			//{
//			//	fRotDiff += -D3DX_PI * 2;
//			//}
//
//			//else if (fRotDiff < -D3DX_PI)
//			//{
//			//	fRotDiff += D3DX_PI * 2;
//			//}
//
//			//減衰処理
//			g_Enemy[nCntEnemy].move.x += (0.0f - g_Enemy[nCntEnemy].move.x) * 0.15f;
//			g_Enemy[nCntEnemy].move.y += (0.0f - g_Enemy[nCntEnemy].move.y) * 0.15f;
//			g_Enemy[nCntEnemy].move.z += (0.0f - g_Enemy[nCntEnemy].move.z) * 0.15f;
//
//			//移動量を位置に代入する
//			g_Enemy[nCntEnemy].pos += g_Enemy[nCntEnemy].move;
//
//			////目的の位置まで補正する処理
//			//	fRotDiff = fRotDest - fRotMove;
//
//			//	DiffEnemy[nCntEnemy].x = g_Enemy[nCntEnemy].posDest.x - g_Enemy[nCntEnemy].pos.x;
//
//			//	DiffEnemy[nCntEnemy].z = g_Enemy[nCntEnemy].posDest.z - g_Enemy[nCntEnemy].pos.z;
//
//			////目的の位置まで補正する処理
//			//g_Enemy[nCntEnemy].pos.x += DiffEnemy[nCntEnemy].x * 0.05f;
//
//			//g_Enemy[nCntEnemy].pos.z += DiffEnemy[nCntEnemy].z * 0.05f;
//
//			////目的のプレイヤーまでの向きを設定
//			//g_Enemy[nCntEnemy].rot.y += fRotDiff * 0.05f;
//
//			////プレイヤーの角度の補正
//			//if (g_Enemy[nCntEnemy].rot.y > D3DX_PI)
//			//{
//			//	g_Enemy[nCntEnemy].rot.y += -D3DX_PI * 2;
//			//}
//
//			//else if (g_Enemy[nCntEnemy].rot.y < -D3DX_PI)
//			//{
//			//	g_Enemy[nCntEnemy].rot.y += D3DX_PI * 2;
//			//}
//
//			//スコアアイテムをプレイヤーの方向へ移動させる処理
//			g_Enemy[nCntEnemy].move.x = -sinf(g_Enemy[nCntEnemy].rot.y) * 12.0f;
//			g_Enemy[nCntEnemy].move.z = -cosf(g_Enemy[nCntEnemy].rot.y) * 12.0f;
//		}
//	}
//}
//
////=============================================
////カメラをプレイヤーの後ろに移動させる処理
////=============================================
//void auteCamEnemy(void)
//{
//	/*if()*/
//}
//
////===========================
////スコアアイテムの状態に関する処理
////===========================
//void EnemyState(void)
//{
//
//	for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
//	{
//
//		switch (g_Enemy[nCnt].state)
//		{
//		case ENEMYSTATE_NORMAL:
//
//			g_Enemy[nCnt].nCounterstate = 60;
//
//			break;
//
//		case ENEMYSTATE_DAMEGE:
//
//			g_Enemy[nCnt].nCounterstate--;
//
//			if (g_Enemy[nCnt].nCounterstate <= 0)
//			{
//				g_Enemy[nCnt].state = ENEMYSTATE_NORMAL;
//
//			}
//
//			break;
//		}
//
//	}
//}
//
////=====================================
////スコアアイテムとスコアアイテムの当たり判定
////=====================================
//void ColisionEneEne(void)
//{
//	int nCntEnemy;
//
//	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
//	{//スコアアイテムが使用されている
//
//		if (g_Enemy[nCntEnemy].bUse == true)
//		{//	スコアアイテムが使用されている
//
//			if (g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z
//				&& g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z >= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z)
//			{
//				//左からの当たり判定
//				if (g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x
//					&& g_Enemy[nCntEnemy].posold.x + g_Enemy[nCntEnemy].VtxMax.x <= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x)
//				{//スコアアイテムと弾が当たった 
//
//				 //	//位置を左側に固定
//					g_Enemy[nCntEnemy].pos.x = g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x - g_Enemy[nCntEnemy].VtxMax.x;
//				}
//
//				//右からの当たり判定
//				if (g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x <= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x
//					&& g_Enemy[nCntEnemy].posold.x + g_Enemy[nCntEnemy].VtxMin.x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x)
//				{//スコアアイテムと弾が当たった 
//
//				 //位置を右側に固定
//					g_Enemy[nCntEnemy].pos.x = g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x - g_Enemy[nCntEnemy].VtxMin.x;
//				}
//
//			}
//
//			if (g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x <= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x
//				&& g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x)
//			{
//				//手前からの当たり判定
//				if (g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z >= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z
//					&& g_Enemy[nCntEnemy].posold.z + g_Enemy[nCntEnemy].VtxMax.z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z)
//				{//スコアアイテムと弾が当たった 
//
//				 //	//位置を手前側に固定
//					g_Enemy[nCntEnemy].pos.z = g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z - g_Enemy[nCntEnemy].VtxMax.z;
//				}
//
//				//奥からの当たり判定
//				if (g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z
//					&& g_Enemy[nCntEnemy].posold.z + g_Enemy[nCntEnemy].VtxMin.z >= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z)
//				{//スコアアイテムと弾が当たった 
//
//				 //位置を奥側に固定
//					g_Enemy[nCntEnemy].pos.z = g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z - g_Enemy[nCntEnemy].VtxMin.z;
//				}
//			}
//		}
//	}
//}
//
////=============================
////スコアアイテムの数を渡す処理
////=============================
//int EnemyCount(void)
//{
//	return EnemyCnt;
//}
//
////====================
////スコアアイテム復帰処理
////====================
//void ReturnEnemy(void)
//{
//	
//		SetEnemy(D3DXVECTOR3(g_LoadEnemy[nCnt], g_LoadEnemy[nCnt + 1], g_LoadEnemy[nCnt + 2]), ENEMYTYPE_NOEMAL, 1);
//}
//
//
//
