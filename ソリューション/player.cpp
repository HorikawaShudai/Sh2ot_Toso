#include "main.h"
#include "game.h"
#include "result.h"
#include "player.h"
#include "camera.h"
#include "object00.h"
#include "input.h"
#include "debugproc.h"
#include "fade.h"
#include "life.h"
#include "score_item.h"

#define PLAYER_STEALTHSPEED (1.0f)		//プレイヤーのステルススピード
#define PLAYER_SPEED (3.0f)				//プレイヤーのスピード
#define PLAYER_DASHSPEED (5.0f)				//プレイヤーのダッシュスピード
#define PLAYER_ROT_SPEED (0.2f)			//プレイヤーの回転スピード
#define PLAYER_JUMP (12.0f)				//プレイヤーのジャンプ力
#define PLAYER_LIFE (3)					//プレイヤーの初期ライフ
#define PLAYER_COLLISIONSIZE (15.0f)	//プレイヤーの当たり判定の大きさ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer[100] = {};	//テクスチャのポインタ
LPD3DXMESH g_pMeshPlayer[32] = {};				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer[32] = {};			//マテリアルへのポインタ
DWORD g_dwNumMatPlayer = 0;						//マテリアルの数
Player g_aPlayer[NUM_PLAYER];					//プレイヤーの情報
int g_nIndexPlayerShadow = -1;					//影のインデックス(番号)
int g_SelectPlayer;								//操作するプレイヤー

//====================================================================
//プレイヤーの初期化処理
//====================================================================
void InitPlayer(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].pos = D3DXVECTOR3(nCntPlayer * 100.0f, 0.0f, -20.0f);
		g_aPlayer[nCntPlayer].posOld = D3DXVECTOR3(0.0f, 300.0f, -400.0f);
		g_aPlayer[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].State = PLAYER_NORMAL;
		g_aPlayer[nCntPlayer].MoveState = PLAYER_MOVESTATE_STEALTH;
		g_aPlayer[nCntPlayer].nLife = PLAYER_LIFE;
		g_aPlayer[nCntPlayer].bUse = true;

		g_SelectPlayer = 0;

		g_aPlayer[nCntPlayer].nNumModel = 1;

		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\player.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatPlayer[nCntPlayer],
			NULL,
			&g_dwNumMatPlayer,
			&g_pMeshPlayer[nCntPlayer]);

		for (int nCntModel = 0; nCntModel < g_aPlayer[nCntPlayer].nNumModel; nCntModel++)
		{
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
}

//====================================================================
//プレイヤーの終了処理
//====================================================================
void UninitPlayer(void)
{
	
	for (int nCntModel = 0; nCntModel < 1; nCntModel++)
	{
		//メッシュの破棄
		if (g_pMeshPlayer[nCntModel] == NULL)
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
	if (GetKeyboardTrigger(DIK_F3) == true)
	{
		g_SelectPlayer++;
		if (g_SelectPlayer >= NUM_PLAYER)
		{
			g_SelectPlayer = 0;
		}
	}

	//プレイヤーの状態
	switch (g_aPlayer[g_SelectPlayer].State)
	{
	case PLAYER_NORMAL:
		break;

	case PLAYER_WAIT:
		g_aPlayer[g_SelectPlayer].nWaitCounter--;
		if (g_aPlayer[g_SelectPlayer].nWaitCounter < 0)
		{
			g_aPlayer[g_SelectPlayer].State = PLAYER_NORMAL;
		}
		break;

	case PLAYER_DAMAGE:
		g_aPlayer[g_SelectPlayer].nDamageCounter--;
		if (g_aPlayer[g_SelectPlayer].nDamageCounter < 0)
		{
			g_aPlayer[g_SelectPlayer].State = PLAYER_WAIT;
		}
		break;

	case PLAYER_HIT:
		g_aPlayer[g_SelectPlayer].nHitCounter--;
		if (g_aPlayer[g_SelectPlayer].nHitCounter < 0)
		{
			g_aPlayer[g_SelectPlayer].State = PLAYER_DAMAGE;
		}
		break;
	}

	g_aPlayer[g_SelectPlayer].posOld = g_aPlayer[g_SelectPlayer].pos;

	//減衰係数
	g_aPlayer[g_SelectPlayer].move.x = g_aPlayer[g_SelectPlayer].move.x * 0.5f;
	g_aPlayer[g_SelectPlayer].move.z = g_aPlayer[g_SelectPlayer].move.z * 0.5f;

	//値の切り捨て
	if (g_aPlayer[g_SelectPlayer].move.x <= 0.005f && g_aPlayer[g_SelectPlayer].move.x >= -0.005f)
	{
		g_aPlayer[g_SelectPlayer].move.x = 0.0f;
	}
	if (g_aPlayer[g_SelectPlayer].move.z <= 0.005f && g_aPlayer[g_SelectPlayer].move.z >= -0.005f)
	{
		g_aPlayer[g_SelectPlayer].move.z = 0.0f;
	}

	//重力の追加
	g_aPlayer[g_SelectPlayer].move.y -= 10.0f;

	//プレイヤーの移動入力処理----------
	PlayerMoveInput(g_SelectPlayer);

	//位置更新(入力による動き)
	g_aPlayer[g_SelectPlayer].pos += g_aPlayer[g_SelectPlayer].move;

	//床の追加
	if (g_aPlayer[g_SelectPlayer].pos.y < 0.0f)
	{//床にふれたとき
		g_aPlayer[g_SelectPlayer].pos.y = 0.0f;	//床の上に戻す
		g_aPlayer[g_SelectPlayer].move.y = 0.0f;	//
	}

	//移動時にプレイヤーの向きを補正する----------
	PlayerRotUpdate(g_SelectPlayer);

	//オブジェクトとの当たり判定
	CollisionObject00(&g_aPlayer[g_SelectPlayer].pos, &g_aPlayer[g_SelectPlayer].posOld, &g_aPlayer[g_SelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);

	//アイテムとの当たり判定
	CollisionItem(&g_aPlayer[g_SelectPlayer].pos, &g_aPlayer[g_SelectPlayer].posOld, &g_aPlayer[g_SelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);

	//一周した時の向きの補正
	if (g_aPlayer[g_SelectPlayer].rot.y > D3DX_PI * 1.0f)
	{
		g_aPlayer[g_SelectPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_aPlayer[g_SelectPlayer].rot.y < -D3DX_PI * 1.0f)
	{
		g_aPlayer[g_SelectPlayer].rot.y += D3DX_PI * 2.0f;
	}

	//体力が減るかどうかテスト用
	if (GetKeyboardTrigger(DIK_M) == true)
	{
		PlayerHit(g_SelectPlayer, 1);
	}

	PrintDebugProc("【F3】でプレイヤー切り替え：【プレイヤー%d】\n", g_SelectPlayer + 1);
	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		PrintDebugProc("プレイヤー%d人目の座標【X : %f | Y : %f | Z : %f】\n", nCntPlayer, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);
	}
	PrintDebugProc("左スティックの出力【%f】", GetGamepad_Stick_Left(0).y);
	PrintDebugProc("左スティックの出力【%f】", GetGamepad_Stick_Left(0).x);
}

//====================================================================
//プレイヤーの移動入力処理
//====================================================================
void PlayerMoveInput(int nCnt)
{
	//斜め移動の速度修正用の関数を初期化する
	g_aPlayer[nCnt].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//キーボードの移動処理
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.z += 1.0f * cosf(Getrot().y);
		g_aPlayer[nCnt].NormarizeMove.x += 1.0f * sinf(Getrot().y);

	}
	if (GetKeyboardPress(DIK_G) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.z += -1.0f * cosf(Getrot().y);
		g_aPlayer[nCnt].NormarizeMove.x += -1.0f * sinf(Getrot().y);
	}
	if (GetKeyboardPress(DIK_F) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.x += -1.0f * cosf(Getrot().y);
		g_aPlayer[nCnt].NormarizeMove.z -= -1.0f * sinf(Getrot().y);

	}
	if (GetKeyboardPress(DIK_H) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.x += 1.0f * cosf(Getrot().y);
		g_aPlayer[nCnt].NormarizeMove.z -= 1.0f * sinf(Getrot().y);
	}

	if (GetKeyboardPress(DIK_T) == false && GetKeyboardPress(DIK_F) == false && GetKeyboardPress(DIK_G) == false && GetKeyboardPress(DIK_H) == false)
	{//キーボードと同時に入力できないようにする
		if (GetGamepad_Stick_Left(0).y > 0.0f)
		{//左スティックの上入力
			g_aPlayer[nCnt].NormarizeMove.z += cosf(Getrot().y);
			g_aPlayer[nCnt].NormarizeMove.x += sinf(Getrot().y);
		}
		if (GetGamepad_Stick_Left(0).y < 0.0f)
		{//左スティックの下入力
			g_aPlayer[nCnt].NormarizeMove.z -= cosf(Getrot().y);
			g_aPlayer[nCnt].NormarizeMove.x -= sinf(Getrot().y);
		}
		if (GetGamepad_Stick_Left(0).x > 0.0f)
		{//左スティックの右入力
			//左スティックによる左右移動
			g_aPlayer[nCnt].NormarizeMove.x += cosf(Getrot().y);
			g_aPlayer[nCnt].NormarizeMove.z -= sinf(Getrot().y);
		}
		if (GetGamepad_Stick_Left(0).x < 0.0f)
		{//左スティックの左入力
			//左スティックによる左右移動
			g_aPlayer[nCnt].NormarizeMove.x -= cosf(Getrot().y);
			g_aPlayer[nCnt].NormarizeMove.z += sinf(Getrot().y);
		}
	}

	//ノーマライズによって斜め移動の速度を修正する
	g_aPlayer[nCnt].NormarizeMove.y = 0.0f;

	D3DXVec3Normalize(&g_aPlayer[nCnt].NormarizeMove, &g_aPlayer[nCnt].NormarizeMove);

	//キーボードの時の速度設定
	if (GetKeyboardPress(DIK_T) == true || GetKeyboardPress(DIK_F) == true || GetKeyboardPress(DIK_G) == true || GetKeyboardPress(DIK_H) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_SPEED;
		g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_SPEED;
	}

	//左スティックの速度処理と移動の三段階の使い分け処理
	if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) != 0 && GetGamepadPress(BUTTON_A, 0))
	{//入力してる状態かつAボタンを押しているとき

		if (g_aPlayer[nCnt].MoveState != PLAYER_MOVESTATE_FATIGE)
		{//疲労状態以外のとき

			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_DASHSPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_DASHSPEED;

			//プレイヤーをダッシュ状態にする
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_DASH;
		}
	}
	else if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) < 0.95f)
	{//左スティックを倒し切っていない状態のとき

		g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_STEALTHSPEED;
		g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_STEALTHSPEED;

	g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;

		//プレイヤーをステルス状態にする
		g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;
	}
	else if(fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) != 0)
	{//入力している状態のとき

		g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_SPEED;
		g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_SPEED;

		//プレイヤーを通常状態にする
		g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_NORMAL;
	}
	else
	{//入力していない場合

		//プレイヤーをステルス状態にする
		g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;
	}

	g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;
}

//====================================================================
//プレイヤーの向きの補正
//====================================================================
void PlayerRotUpdate(int nCnt)
{
	//移動方向に向きを合わせる処理
	float fRotMove, fRotDest, fRotDiff;

	fRotMove = g_aPlayer[nCnt].rot.y;
	fRotDest = Getrot().y;

	if (GetKeyboardPress(DIK_E) == true)
	{
		g_aPlayer[nCnt].rot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_aPlayer[nCnt].rot.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_T) == true || GetGamepad_Stick_Left(0).y > 0.1f)
	{
		if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.25f;
		}
		else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.25f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y));
		}
	}
	else if (GetKeyboardPress(DIK_G) == true || GetGamepad_Stick_Left(0).y < -0.1f)
	{
		if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.75f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.5f;
	}

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
		g_aPlayer[nCnt].rot.y = fRotMove;
	}
}

//====================================================================
//プレイヤーとの当たり判定
//====================================================================
void CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY)
{
	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		if (
			pos.z + Size >= g_aPlayer[nCntPlayer].pos.z - PLAYER_COLLISIONSIZE &&
			pos.z - Size <= g_aPlayer[nCntPlayer].pos.z + PLAYER_COLLISIONSIZE &&
			pos.x + Size >= g_aPlayer[nCntPlayer].pos.x - PLAYER_COLLISIONSIZE &&
			pos.x - Size <= g_aPlayer[nCntPlayer].pos.x + PLAYER_COLLISIONSIZE &&
			pos.y + MaxY >= g_aPlayer[nCntPlayer].pos.y - 10.0f &&
			pos.y + MinY <= g_aPlayer[nCntPlayer].pos.y + 10.0f
			)
		{//弾とプレイヤーが当たった(Z軸)
			PlayerHit(nCntPlayer,1);
		}
	}
}

//====================================================================
//プレイヤーのヒット処理
//====================================================================
void PlayerHit(int nCnt,int nDamage)
{
	g_aPlayer[nCnt].nLife -= nDamage;

	//ライフのセット処理
	SetLife(g_aPlayer[nCnt].nLife, nCnt);

	if (g_aPlayer[nCnt].nLife <= 0)
	{
		g_aPlayer[nCnt].bUse = false;

	}

	else
	{
		g_aPlayer[nCnt].State = PLAYER_HIT;
	}
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

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aPlayer[nCntPlayer].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nCntPlayer].rot.y, g_aPlayer[nCntPlayer].rot.x, g_aPlayer[nCntPlayer].rot.z);

		D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorld, &g_aPlayer[nCntPlayer].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);

		D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorld, &g_aPlayer[nCntPlayer].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nCntPlayer].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

		//全モデル(パーツ)の描画
		for (int nCntModel = 0; nCntModel < g_aPlayer[nCntPlayer].nNumModel; nCntModel++)
		{

			//マテリアルデータへのポインタを所得する
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayer[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexturePlayer[nCntMat]);

				if (g_aPlayer[nCntPlayer].bUse == true)
				{
					//プレイヤー(パーツ)の描画
					g_pMeshPlayer[nCntModel]->DrawSubset(nCntMat);
				}
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//プレイヤー情報の所得
//====================================================================
Player * GetPlayer(void)
{
	return &g_aPlayer[0];
}