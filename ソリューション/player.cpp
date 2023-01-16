//============================
//
//プレイヤー処理(player.cpp)
//Author:早川 友貴
//
//============================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"

//マクロ定義

//グローバル
LPDIRECT3DTEXTURE9 g_apTexturPlayer[10] = {};	//テクスチャへのポインタ
LPD3DXMESH g_pMeshPlayer = NULL; //メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer  = NULL; //マテリアルへのポインタ
DWORD g_dwNumMatPlayer = 0; //マテリアルの数
D3DXVECTOR3 g_posPlayer; //位置
D3DXVECTOR3 g_rotPlayer; //向き
D3DXMATRIX g_mtxWorldPlayer;  //ワールドマトリックス
D3DXVECTOR3 g_posPlayerDest; //目的の位置
D3DXVECTOR3 g_rotPlayerDest; //目的の向き
float g_PlayerfAngle; //プレイヤーの角度
float g_PlayerfLength; //プレイヤーの長さ
D3DXVECTOR3 DiffPlayer;

Camera g_cam;	//カメラの情報

//====================
//プレイヤーの初期化
//====================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得

	//各種変数の初期化
	g_posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化

	g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化

	g_posPlayerDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //目的の位置を初期化
	g_rotPlayerDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //目的の向きを初期化

	D3DXVECTOR3 DiffModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_cam.posV = D3DXVECTOR3(0.0f, 50.0f, 50.0f);
	g_cam.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cam.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_cam.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cam.rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cam.rot2Old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視点を固定する場合
	g_PlayerfAngle = atan2f
	(//対角線の角度
		g_posPlayerDest.x - g_posPlayer.x,
		g_posPlayerDest.z - g_posPlayer.z
	);

	g_PlayerfLength = sqrtf
	(//対角線の長さ
		(g_posPlayerDest.x - g_posPlayer.x) * (g_posPlayerDest.x - g_posPlayer.x) +
		(g_posPlayerDest.z - g_posPlayer.z) * (g_posPlayerDest.z - g_posPlayer.z)
	) * 0.5f;

	//Xファイルの読み込み
	D3DXLoadMeshFromX("Data\\MODEL\\Player.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL *pMat; //マテリアルへのポインタ

						//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルネームが存在する
		 //テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturPlayer[nCntMat]);
		}
	}

}

//プレイヤーの終了処理
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//プレイヤーの更新処理
void UpdatePlayer(void)
{
	MovePlayer();

	AnglePlayer();
}

//プレイヤーの描画処理
void DrawPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	D3DMATERIAL9 matDef;  //現在のマテリアル保存用

	D3DXMATERIAL *pMat;	  //マテリアルデータへのポインタ

						  //ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotPlayer.y, g_rotPlayer.x, g_rotPlayer.z);

	D3DXMatrixMultiply(&g_mtxWorldPlayer,
		&g_mtxWorldPlayer,
		&mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		g_posPlayer.x, g_posPlayer.y, g_posPlayer.z);

	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturPlayer[nCntMat]);

		//プレイヤー(パーツ)の描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================
//ポリゴンの位置を与える処理
//=============================
D3DXVECTOR3 PosPlayer(void)
{
	return g_posPlayer;
}

//===========================
//ポリゴンの向きを教える処理
//===========================
D3DXVECTOR3 RotPlayer(void)
{
	return g_rotPlayer;
}

//==================================
//プレイヤーの移動処理
//==================================
void MovePlayer(void)
{
}

//==================================
//プレイヤーの角度処理
//==================================
void AnglePlayer(void)
{
	float fRotMove = g_rotPlayer.y;
	float fRotDest = g_rotPlayer.y; //目標の角度
	float fRotDiff = 0.0f; //目標と現在角度の差分

	//奥移動
	if (GetKeyboardPress(DIK_T) == true)
	{
		if (GetKeyboardPress(DIK_H) == true)
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 0.25f * D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 0.25f * D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 0.75f * -D3DX_PI;
		}

		else if (GetKeyboardPress(DIK_F) == true)
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 0.25f * -D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 0.25f * -D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 0.75f * D3DX_PI;
		}

		else
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 0.0f * D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 0.0f * D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 1.0f * D3DX_PI;
		}
	}

	//手前移動
	else if (GetKeyboardPress(DIK_G) == true)
	{
		if (GetKeyboardPress(DIK_H) == true)
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 0.75f * D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 0.75f * D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 0.25f * -D3DX_PI;

		}

		else if (GetKeyboardPress(DIK_F) == true)
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 0.75f * -D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 0.75f * -D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 0.25f * D3DX_PI;

		}

		else
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 1.0f * D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 1.0f * D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 0.0f * D3DX_PI;
		}
	}

	//左移動
	else if (GetKeyboardPress(DIK_F) == true)
	{
		g_posPlayer.x += sinf(g_cam.rot.y + 0.5f * -D3DX_PI) * 1.0f;
		g_posPlayer.z += cosf(g_cam.rot.y + 0.5f * -D3DX_PI) * 1.0f;

		fRotDest = g_cam.rot.y + 0.5f * D3DX_PI;
	}

	//右移動
	else if (GetKeyboardPress(DIK_H) == true)
	{
		g_posPlayer.x += sinf(g_cam.rot.y + 0.5f * D3DX_PI) * 1.0f;
		g_posPlayer.z += cosf(g_cam.rot.y + 0.5f * D3DX_PI) * 1.0f;

		fRotDest = g_cam.rot.y + 0.5f * -D3DX_PI;
	}


	//目標の角度との差分を求める処理
	fRotDiff = fRotDest - fRotMove;

	//目標の角度の補正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff += -D3DX_PI * 2;
	}

	else if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += D3DX_PI * 2;
	}

	//目的の角度まで補正する処理
	g_rotPlayer.y += fRotDiff * 0.1f;

	//プレイヤーの角度の補正
	if (g_rotPlayer.y > D3DX_PI)
	{
		g_rotPlayer.y += -D3DX_PI * 2;
	}

	else if (g_rotPlayer.y < -D3DX_PI)
	{
		g_rotPlayer.y += D3DX_PI * 2;
	}

	//目的の視点を設定
	g_posPlayerDest.x = g_posPlayer.x - sinf(g_cam.rot.y + D3DX_PI - g_PlayerfAngle) * g_PlayerfLength;
	g_posPlayerDest.z = g_posPlayer.z - cosf(g_cam.rot.y + D3DX_PI - g_PlayerfAngle) * g_PlayerfLength;

	//目的の位置まで補正する処理
	fRotDiff = fRotDest - fRotMove;

	DiffPlayer.x = g_posPlayerDest.x - g_posPlayer.x;

	DiffPlayer.z = g_posPlayerDest.z - g_posPlayer.z;

	//目的の位置まで補正する処理
	g_posPlayer.x += DiffPlayer.x * 0.05f;

	g_posPlayer.z += DiffPlayer.z * 0.05f;
}
