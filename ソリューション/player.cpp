#include "main.h"
#include "game.h"
#include "result.h"
#include "player.h"
#include "camera.h"
#include "object00.h"
#include "input.h"
#include "debugproc.h"
#include "fade.h"

#define PLAYER_SPEED (1.5f)			//プレイヤーのスピード
#define PLAYER_ROT_SPEED (0.2f)			//プレイヤーの回転スピード
#define PLAYER_JUMP (12.0f)				//プレイヤーのジャンプ力
#define PLAYER_LIFE (3)					//プレイヤーの初期ライフ
#define PLAYER_COLLISIONSIZE (15.0f)	//プレイヤーの当たり判定の大きさ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer[100] = {};	//テクスチャのポインタ
LPD3DXMESH g_pMeshPlayer[32] = {};				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer[32] = {};			//マテリアルへのポインタ
DWORD g_dwNumMatPlayer = 0;						//マテリアルの数
Player g_Player;								//プレイヤーの情報
int g_nIndexPlayerShadow = -1;					//影のインデックス(番号)

int WaitMotionCounter;							//待機モーションのカウンター
int WaitMotion;									//待機モーション
int MoveMotionCounter;							//移動モーションのカウンター
int MoveMotion;									//移動モーション
int JumpMotionCounter;							//ジャンプモーションのカウンター
int JumpMotion;									//ジャンプモーション
bool bWait;										//待機してるかどうかの判断
float JunpPawer;								//待機してるかどうかの判断

//====================================================================
//プレイヤーの初期化処理
//====================================================================
void InitPlayer(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nNumVtx;		//頂点数
	DWORD dwSizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, -20.0f);
	g_Player.posOld = D3DXVECTOR3(0.0f, 300.0f, -400.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_Player.vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_Player.State = PLAYER_NORMAL;
	g_Player.nLife = PLAYER_LIFE;
	g_Player.bJump = false;
	g_Player.bUse = true;
	g_Player.pMatH.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.pMatD.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	g_Player.pMatW.MatD3D.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	WaitMotionCounter = 0;
	WaitMotion = 1;
	MoveMotionCounter = 0;
	MoveMotion = 1;
	JumpMotionCounter = 0;
	JumpMotion = 1;
	bWait = true;
	JunpPawer = 0.0f;

	g_Player.nNumModel = 1;

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\player.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer[0],
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer[0]);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//頂点数を所得
		nNumVtx = g_pMeshPlayer[nCntModel]->GetNumVertices();

		//頂点フォーマットのサイズを所得
		dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer[nCntModel]->GetFVF());

		//頂点バッファをロック
		g_pMeshPlayer[nCntModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

			if (g_Player.vtxMin.x > vtx.x)
			{
				g_Player.vtxMin.x = vtx.x;
			}
			if (g_Player.vtxMin.y > vtx.y)
			{
				g_Player.vtxMin.y = vtx.y;
			}
			if (g_Player.vtxMin.z > vtx.z)
			{
				g_Player.vtxMin.z = vtx.z;
			}

			if (g_Player.vtxMax.x < vtx.x)
			{
				g_Player.vtxMax.x = vtx.x;
			}
			if (g_Player.vtxMax.y < vtx.y)
			{
				g_Player.vtxMax.y = vtx.y;
			}
			if (g_Player.vtxMax.z < vtx.z)
			{
				g_Player.vtxMax.z = vtx.z;
			}

			pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
		}

		//頂点バッファをアンロック
		g_pMeshPlayer[nCntModel]->UnlockVertexBuffer();

		D3DXMATERIAL *pMat;	//マテリアルへのポインタ

							//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatPlayer[nCntModel]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTexturePlayer[nCntMat]);
			}
		}
	}
}

//====================================================================
//プレイヤーの終了処理
//====================================================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//メッシュの破棄
		if (g_pMeshPlayer != NULL)
		{
			g_pMeshPlayer[nCntModel]->Release();
			g_pMeshPlayer[nCntModel] = NULL;
		}

		//マテリアルの破棄
		if (g_pBuffMatPlayer != NULL)
		{
			g_pBuffMatPlayer[nCntModel]->Release();
			g_pBuffMatPlayer[nCntModel] = NULL;
		}
	}
}

//====================================================================
//プレイヤーの更新処理
//====================================================================
void UpdatePlayer(void)
{
	//プレイヤーの状態
	switch (g_Player.State)
	{
	case PLAYER_NORMAL:
		break;

	case PLAYER_WAIT:
		g_Player.nWaitCounter--;
		if (g_Player.nWaitCounter < 0)
		{
			g_Player.State = PLAYER_NORMAL;
		}
		break;

	case PLAYER_DAMAGE:
		g_Player.nDamageCounter--;
		if (g_Player.nDamageCounter < 0)
		{
			g_Player.State = PLAYER_WAIT;
		}
		break;

	case PLAYER_HIT:
		g_Player.nHitCounter--;
		if (g_Player.nHitCounter < 0)
		{
			g_Player.State = PLAYER_DAMAGE;
		}
		break;
	}

	//プレイヤーのモーション
	PlayerMotion();

	g_Player.posOld = g_Player.pos;

	//減衰係数
	g_Player.move.x = g_Player.move.x * 0.5f;
	g_Player.move.z = g_Player.move.z * 0.5f;

	//値の切り捨て
	if (g_Player.move.x <= 0.005f && g_Player.move.x >= -0.005f)
	{
		g_Player.move.x = 0.0f;
	}
	if (g_Player.move.z <= 0.005f && g_Player.move.z >= -0.005f)
	{
		g_Player.move.z = 0.0f;
	}

	//重力の追加
	g_Player.move.y -= 10.0f;

	//プレイヤーの移動入力処理
	PlayerMoveInput();

	//ジャンプ処理
	if (g_Player.bJump == false)
	{//ジャンプをしていないとき
		if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
		{//ジャンプボタン入力時
			g_Player.move.y = PLAYER_JUMP;	//ジャンプする
			g_Player.bJump = true;			//ジャンプを使用している状態にする
		}
	}

	//位置更新(入力による動き)
	g_Player.pos += g_Player.move;

	//床の追加
	if (g_Player.pos.y < 0.0f)
	{//床にふれたとき
		g_Player.pos.y = 0.0f;	//床の上に戻す
		g_Player.move.y = 0.0f;	//
	}

	//一定速度以上で落下している時にジャンプが出来ない状態にする
	if (g_Player.move.y < 0.0f)
	{
		if (g_Player.bJump == false)
		{
			g_Player.bJump = true;			//ジャンプを使用している状態にする
		}
	}

	//移動時にプレイヤーの向きを補正する
	PlayerRotUpdate();

	//オブジェクトとの当たり判定
	if (CollisionObject00(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.vtxMin, g_Player.vtxMax, 10.0f) == false)
	{
		if (g_Player.bJump == true)
		{
			g_Player.bJump = false;	//ジャンプを使用していない状態にする
		}
	}

	//一周した時の向きの補正
	if (g_Player.rot.y > D3DX_PI * 1.0f)
	{
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_Player.rot.y < -D3DX_PI * 1.0f)
	{
		g_Player.rot.y += D3DX_PI * 2.0f;
	}

	PrintDebugProc("fff", g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
}

//====================================================================
//プレイヤーのモーション処理(簡易版)
//====================================================================
void PlayerMotion(void)
{

}

//====================================================================
//プレイヤーの移動入力処理
//====================================================================
void PlayerMoveInput(void)
{
	g_Player.NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//キーボードの移動処理
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_Player.NormarizeMove.z += 1.0f * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.NormarizeMove.x += 1.0f * sinf(Getrot().y) * PLAYER_SPEED;

	}
	if (GetKeyboardPress(DIK_G) == true)
	{
		g_Player.NormarizeMove.z += -1.0f * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.NormarizeMove.x += -1.0f * sinf(Getrot().y) * PLAYER_SPEED;
	}
	if (GetKeyboardPress(DIK_F) == true)
	{
		g_Player.NormarizeMove.x += -1.0f * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.NormarizeMove.z -= -1.0f * sinf(Getrot().y) * PLAYER_SPEED;

	}
	if (GetKeyboardPress(DIK_H) == true)
	{
		g_Player.NormarizeMove.x += 1.0f * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.NormarizeMove.z -= 1.0f * sinf(Getrot().y) * PLAYER_SPEED;
	}

	if (GetKeyboardPress(DIK_T) == false && GetKeyboardPress(DIK_F) == false && GetKeyboardPress(DIK_G) == false && GetKeyboardPress(DIK_H) == false)
	{
		//左スティックによる前後移動	
		g_Player.move.z += GetGamepad_Stick_Left(0).y * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.move.x += GetGamepad_Stick_Left(0).y * sinf(Getrot().y) * PLAYER_SPEED;

		//左スティックによる左右移動
		g_Player.move.x += GetGamepad_Stick_Left(0).x * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.move.z -= GetGamepad_Stick_Left(0).x * sinf(Getrot().y) * PLAYER_SPEED;
	}

	if (GetKeyboardPress(DIK_T) == true || GetKeyboardPress(DIK_F) == true || GetKeyboardPress(DIK_G) == true || GetKeyboardPress(DIK_H) == true)
	{
		JunpPawer = g_Player.NormarizeMove.y;
		g_Player.NormarizeMove.y = 0.0f;

		D3DXVec3Normalize(&g_Player.NormarizeMove, &g_Player.NormarizeMove);

		g_Player.NormarizeMove.x *= PLAYER_SPEED;
		g_Player.NormarizeMove.y = JunpPawer;
		g_Player.NormarizeMove.z *= PLAYER_SPEED;
	}

	g_Player.move += g_Player.NormarizeMove;
}

//====================================================================
//プレイヤーの向きの補正
//====================================================================
void PlayerRotUpdate(void)
{
	//移動方向に向きを合わせる処理
	float fRotMove, fRotDest, fRotDiff;

	fRotMove = g_Player.rot.y;
	fRotDest = Getrot().y;

	if (GetKeyboardPress(DIK_E) == true)
	{
		g_Player.rot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_Player.rot.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_T) == true || GetGamepad_Stick_Left(0).y > 0.1f)
	{
		if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.25f;
		}
		else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.25f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y));
		}
	}
	else if (GetKeyboardPress(DIK_G) == true || GetGamepad_Stick_Left(0).y < -0.1f)
	{
		if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.75f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
	{
		fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
		fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
	{
		fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
		fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.5f;
	}

	////左スティックによる前後移動	
	//g_Player.move.z += GetGamepad_Stick_Left(0).y * cosf(Getrot().y) * PLAYER_SPEED;
	//g_Player.move.x += GetGamepad_Stick_Left(0).y * sinf(Getrot().y) * PLAYER_SPEED;

	////左スティックによる左右移動
	//g_Player.move.x += GetGamepad_Stick_Left(0).x * cosf(Getrot().y) * PLAYER_SPEED;
	//g_Player.move.z -= GetGamepad_Stick_Left(0).x * sinf(Getrot().y) * PLAYER_SPEED;

	//fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
	//fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y) + D3DX_PI * GetGamepad_Stick_Left(0).x);

	fRotDiff = fRotDest - fRotMove;

	if (fRotDiff > D3DX_PI * 1.0f)
	{
		fRotDiff -= D3DX_PI * 2.0f;
	}
	else if (fRotDiff < -D3DX_PI * 1.0f)
	{
		fRotDiff += D3DX_PI * 2.0f;
	}

	fRotMove += fRotDiff * PLAYER_ROT_SPEED;

	if (fRotMove > D3DX_PI * 1.0f)
	{
		fRotMove -= D3DX_PI * 2.0f;
	}
	else if (fRotMove < -D3DX_PI * 1.0f)
	{
		fRotMove += D3DX_PI * 2.0f;
	}

	if (GetKeyboardPress(DIK_T) == true || GetKeyboardPress(DIK_F) == true || GetKeyboardPress(DIK_G) == true || GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).y != 0.0f || GetGamepad_Stick_Left(0).x != 0.0f)
	{
		g_Player.rot.y = fRotMove;
	}
}

//====================================================================
//プレイヤーとの当たり判定
//====================================================================
void CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY)
{
	if (
		pos.z + Size >= g_Player.pos.z - PLAYER_COLLISIONSIZE &&
		pos.z - Size <= g_Player.pos.z + PLAYER_COLLISIONSIZE &&
		pos.x + Size >= g_Player.pos.x - PLAYER_COLLISIONSIZE &&
		pos.x - Size <= g_Player.pos.x + PLAYER_COLLISIONSIZE &&
		pos.y + MaxY >= g_Player.pos.y + g_Player.vtxMin.y &&
		pos.y + MinY <= g_Player.pos.y + g_Player.vtxMax.y
		)
	{//弾とプレイヤーが当たった(Z軸)
		PlayerHit();
	}
}

//====================================================================
//プレイヤーのヒット処理
//====================================================================
void PlayerHit(void)
{

}

//====================================================================
//プレイヤーの描画処理
//====================================================================
void DrawPlayer(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//現在のマテリアルを所得
	pDevice->GetMaterial(&matDef);

	//全モデル(パーツ)の描画
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{

		//マテリアルデータへのポインタを所得する
		pMat = (D3DXMATERIAL*)g_pBuffMatPlayer[nCntModel]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
		{
			switch (g_Player.State)
			{
			case PLAYER_NORMAL:
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				break;

			case PLAYER_WAIT:
				pDevice->SetMaterial(&g_Player.pMatW.MatD3D);
				break;

			case PLAYER_DAMAGE:
				pDevice->SetMaterial(&g_Player.pMatD.MatD3D);
				break;

			case PLAYER_HIT:
				pDevice->SetMaterial(&g_Player.pMatH.MatD3D);
				break;
			}

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePlayer[nCntMat]);

			if (g_Player.bUse == true)
			{
				//プレイヤー(パーツ)の描画
				g_pMeshPlayer[nCntModel]->DrawSubset(nCntMat);
			}
		}
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//次のライフの設定
//====================================================================
void SetNextLife(void)
{
	g_Player.nNextLife = g_Player.nLife;
}

//====================================================================
//プレイヤー情報の所得
//====================================================================
Player * GetPlayer(void)
{
	return &g_Player;
}