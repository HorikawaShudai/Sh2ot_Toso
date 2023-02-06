//========================================================================================
//
// プレイヤーの処理[player.cpp]
// Author: 小笠原　彪
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "game.h"
#include "result.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "object00.h"
#include "input.h"
#include "debugproc.h"
#include "fade.h"
#include "life.h"
#include "PlayNumberSelect.h"
#include "score_item.h"
#include "stamina.h"
#include "key.h"
#include "keyUI.h"
#include "exit.h"

//マクロ定義
#define PLAYER_STEALTHSPEED		(0.3f)			//プレイヤーのステルススピード
#define PLAYER_SPEED			(1.5f)			//プレイヤーのスピード
#define PLAYER_DASHSPEED		(2.0f)			//プレイヤーのダッシュスピード
#define PLAYER_ROT_SPEED		(0.2f)			//プレイヤーの回転スピード
#define PLAYER_JUMP				(12.0f)			//プレイヤーのジャンプ力
#define PLAYER_LIFE				(3)				//プレイヤーの初期ライフ
#define PLAYER_COLLISIONSIZE	(15.0f)			//プレイヤーの当たり判定の大きさ

//プロトタイプ
void UpdatePlayer0(void);
void UpdatePlayer1(void);

void ResPlayerMove(int nCnt);				//プレイヤーそれぞれに対応
void ResPlayerrot(int nCnt);				//プレイヤーそれぞれに対応

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer[100] = {};	//テクスチャのポインタ
LPD3DXMESH g_pMeshPlayer[32] = {};				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer[32] = {};			//マテリアルへのポインタ
DWORD g_dwNumMatPlayer = 0;						//マテリアルの数
Player g_aPlayer[NUM_PLAYER];					//プレイヤーの情報
int g_nIndexPlayerShadow = -1;					//影のインデックス(番号)
bool g_bPlayerOps;

//====================================================================
//プレイヤーの初期化処理
//====================================================================
void InitPlayer(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].pos = D3DXVECTOR3(-1050.0f + nCntPlayer * 30.0f, 0.0f, -621.11f);
		g_aPlayer[nCntPlayer].posOld = D3DXVECTOR3(0.0f, 300.0f, -400.0f);
		g_aPlayer[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].State = PLAYER_NORMAL;
		g_aPlayer[nCntPlayer].MoveState = PLAYER_MOVESTATE_STEALTH;
		g_aPlayer[nCntPlayer].nLife = PLAYER_LIFE;
		g_aPlayer[nCntPlayer].bUse = true;
		g_aPlayer[nCntPlayer].bGetKey = false;
		g_aPlayer[nCntPlayer].VibrtionTrueCount = 0;
		g_aPlayer[nCntPlayer].VibrtionFalseCount = 0;
		g_aPlayer[nCntPlayer].bVibrtion = false;
		g_aPlayer[nCntPlayer].bAppear = false;
#if _DEBUG
		g_aPlayer[nCntPlayer].bAppear = true;
#endif

		g_bPlayerOps = false;
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
	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	for (int nCntModel = 0; nCntModel < PlayNumber.CurrentSelectNumber; nCntModel++)
	{
		//メッシュの破棄
		if (g_pMeshPlayer[nCntModel] != NULL)
		{
			g_pMeshPlayer[nCntModel]->Release();
			g_pMeshPlayer[nCntModel] = NULL;
		}

		//マテリアルの破棄
		if (g_pBuffMatPlayer[nCntModel] != NULL)
		{
			g_pBuffMatPlayer[nCntModel]->Release();
			g_pBuffMatPlayer[nCntModel] = NULL;
		}

		//バイブレーションをオフにする
		GetGamepad_Vibrtion_false(0);
	}
}

//====================================================================
//プレイヤーの更新処理
//====================================================================
void UpdatePlayer(void)
{
//#ifdef _DEBUG
	//個別
	UpdatePlayer0();
//#endif

	//複数
	//UpdatePlayer1();


}

//====================================================================
//プレイヤーの更新処理(一つのコントローラ対応)
//====================================================================
void UpdatePlayer0(void)
{
	//ポインタ情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//カメラ番号をプレイヤーに代入
	int nSelectPlayer = GetCurrentCamera();
	
#ifdef _DEBUG
	//バイブレーション
	if (GetKeyboardTrigger(DIK_F6) == true)
	{
		PlayerSetVibrtion(0,10,10,60000,0);
	}
	if (GetKeyboardTrigger(DIK_F7) == true)
	{
		GetGamepad_Vibrtion_false(0);
	}
#endif

	//バイブレーションの更新処理
	PlayerVibrtionUpdate(0);

	//プレイヤーの状態
	switch (g_aPlayer[nSelectPlayer].State)
	{
	case PLAYER_NORMAL:
		break;

	case PLAYER_WAIT:
		g_aPlayer[nSelectPlayer].nWaitCounter--;
		if (g_aPlayer[nSelectPlayer].nWaitCounter < 0)
		{
			g_aPlayer[nSelectPlayer].State = PLAYER_NORMAL;
		}
		break;

	case PLAYER_DAMAGE:
		g_aPlayer[nSelectPlayer].nDamageCounter--;
		if (g_aPlayer[nSelectPlayer].nDamageCounter < 0)
		{
			g_aPlayer[nSelectPlayer].State = PLAYER_WAIT;
		}
		break;

	case PLAYER_HIT:
		g_aPlayer[nSelectPlayer].nHitCounter--;
		if (g_aPlayer[nSelectPlayer].nHitCounter < 0)
		{
			g_aPlayer[nSelectPlayer].State = PLAYER_DAMAGE;
		}
		break;
	}

	g_aPlayer[nSelectPlayer].posOld = g_aPlayer[nSelectPlayer].pos;

	//減衰係数
	g_aPlayer[nSelectPlayer].move.x = g_aPlayer[nSelectPlayer].move.x * 0.5f;
	g_aPlayer[nSelectPlayer].move.z = g_aPlayer[nSelectPlayer].move.z * 0.5f;

	//値の切り捨て
	if (g_aPlayer[nSelectPlayer].move.x <= 0.005f && g_aPlayer[nSelectPlayer].move.x >= -0.005f)
	{
		g_aPlayer[nSelectPlayer].move.x = 0.0f;
	}
	if (g_aPlayer[nSelectPlayer].move.z <= 0.005f && g_aPlayer[nSelectPlayer].move.z >= -0.005f)
	{
		g_aPlayer[nSelectPlayer].move.z = 0.0f;
	}

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F5) == true)
	{//キーが押された場合
		g_bPlayerOps = g_bPlayerOps ? false : true;			//観察用モードに変更
	}
#endif

	if (g_bPlayerOps == false)
	{
		//プレイヤーの移動入力処理----------
		PlayerMoveInput(nSelectPlayer);

		//移動時にプレイヤーの向きを補正する----------
		PlayerRotUpdate(nSelectPlayer);
	}

	//位置更新(入力による動き)
	g_aPlayer[nSelectPlayer].pos += g_aPlayer[nSelectPlayer].move;

	//オブジェクトとの当たり判定
	CollisionObject00(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);
	//外積の当たり判定
	//CollisionOuterProductObject00(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move);


	//アイテムとの当たり判定
	CollisionItem(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-20.0f, -20.0f, -20.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f), 20.0f, nSelectPlayer);

	//出口との当たり判定
	CollisionExi(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);

	//プレイヤーと敵との距離
	PlayerDistance(nSelectPlayer);

	//鍵の入手処理
	if (g_aPlayer[nSelectPlayer].bGetKey == false)
	{//プレイヤーが鍵を持っていない場合
		if (GetKeyboardTrigger(DIK_E) == true || GetGamepadTrigger(BUTTON_A, nSelectPlayer) || GetGamepadTrigger(BUTTON_B, nSelectPlayer))
		{//Eキー入力
			if(CollisionKey(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nSelectPlayer) == true)
			{//鍵を入手出来た場合
				g_aPlayer[nSelectPlayer].bGetKey = true;	//鍵を入手状態にする
				SetKeyUI(nSelectPlayer, true);				//鍵UIを表示する
			}
		}
	}

	//脱出処理
	if (g_aPlayer[nSelectPlayer].bGetKey == true)
	{//プレイヤーが鍵を持っている場合
		if (GetKeyboardTrigger(DIK_E) == true || GetGamepadTrigger(BUTTON_A, nSelectPlayer) || GetGamepadTrigger(BUTTON_B, nSelectPlayer))
		{//Eキー入力
			if (CollisionExit(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nSelectPlayer) == true)
			{//鍵を入手出来た場合

				g_aPlayer[nSelectPlayer].bGetKey = false;	//鍵を入手してない状態にする
				SetKeyUI(nSelectPlayer, false);			//鍵UIを非表示にする
			}
		}
	}

	//一周した時の向きの補正
	if (g_aPlayer[nSelectPlayer].rot.y > D3DX_PI * 1.0f)
	{
		g_aPlayer[nSelectPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_aPlayer[nSelectPlayer].rot.y < -D3DX_PI * 1.0f)
	{
		g_aPlayer[nSelectPlayer].rot.y += D3DX_PI * 2.0f;
	}

	//体力が減るかどうかテスト用
	if (GetKeyboardTrigger(DIK_M) == true)
	{
		PlayerHit(nSelectPlayer, 1);
	}
#ifdef _DEBUG
	PrintDebugProc("【F3】でプレイヤー切り替え：【プレイヤー%d】\n", nSelectPlayer + 1);

	for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
	{
		PrintDebugProc("プレイヤー%d人目の座標【X : %f | Y : %f | Z : %f】\n", nCntPlayer, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);
		PrintDebugProc("プレイヤー%d人目の移動量【X : %f | Y : %f | Z : %f】\n", nCntPlayer, g_aPlayer[nCntPlayer].move.x, g_aPlayer[nCntPlayer].move.y, g_aPlayer[nCntPlayer].move.z);
	}
	PrintDebugProc("左スティックの出力【%f】", GetGamepad_Stick_Left(0).y);
	PrintDebugProc("左スティックの出力【%f】", GetGamepad_Stick_Left(0).x);
	PrintDebugProc("右スティックの出力【%f】", GetGamepad_Stick_Right(0).y);
	PrintDebugProc("右スティックの出力【%f】", GetGamepad_Stick_Right(0).x);
#endif
}

//====================================================================
//プレイヤーの移動入力処理
//====================================================================
void PlayerMoveInput(int nCnt)
{
	//情報の取得
	Stamina *pStamina = GetStamina();
	Camera *pCamera = GetCamera();
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	int CurrentCamera = GetCurrentCamera();

	//斜め移動の速度修正用の関数を初期化する
	g_aPlayer[nCnt].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (g_aPlayer[nCnt].State != PLAYER_EXSIT)
	{//プレイヤーの状態が脱出状態以外の場合
		//キーボードの移動処理
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.z += 1.0f * cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.x += 1.0f * sinf(Getrot(CurrentCamera).y);

		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.z += -1.0f * cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.x += -1.0f * sinf(Getrot(CurrentCamera).y);
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.x += -1.0f * cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.z -= -1.0f * sinf(Getrot(CurrentCamera).y);

		}
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.x += 1.0f * cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.z -= 1.0f * sinf(Getrot(CurrentCamera).y);
		}

		if (GetKeyboardPress(DIK_W) == false && GetKeyboardPress(DIK_S) == false && GetKeyboardPress(DIK_A) == false && GetKeyboardPress(DIK_D) == false)
		{//キーボードと同時に入力できないようにする
			if (GetGamepad_Stick_Left(0).y > 0.0f)
			{//左スティックの上入力
				g_aPlayer[nCnt].NormarizeMove.z += cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.x += sinf(Getrot(CurrentCamera).y);
			}
			if (GetGamepad_Stick_Left(0).y < 0.0f)
			{//左スティックの下入力
				g_aPlayer[nCnt].NormarizeMove.z -= cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.x -= sinf(Getrot(CurrentCamera).y);
			}
			if (GetGamepad_Stick_Left(0).x > 0.0f)
			{//左スティックの右入力
			 //左スティックによる左右移動
				g_aPlayer[nCnt].NormarizeMove.x += cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.z -= sinf(Getrot(CurrentCamera).y);
			}
			if (GetGamepad_Stick_Left(0).x < 0.0f)
			{//左スティックの左入力
			 //左スティックによる左右移動
				g_aPlayer[nCnt].NormarizeMove.x -= cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.z += sinf(Getrot(CurrentCamera).y);
			}
		}

		//ノーマライズによって斜め移動の速度を修正する
		g_aPlayer[nCnt].NormarizeMove.y = 0.0f;

		D3DXVec3Normalize(&g_aPlayer[nCnt].NormarizeMove, &g_aPlayer[nCnt].NormarizeMove);

		//キーボードの時の速度設定
		if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_SPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_SPEED;
		}

		//左スティックの速度処理と移動の三段階の使い分け処理
		if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) != 0 && GetGamepadPress(BUTTON_R, 0) || GetKeyboardPress(DIK_SPACE) == true)
		{//入力してる状態かつAボタンを押しているとき
			if (pStamina[nCnt].bFatige == false)			//プレイヤーが走れる状態かどうか
			{//疲労状態ではなかった場合

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

			//カメラ状態を無へ
			pCamera[nCnt].State = CAMERASTATE_NONE;
		}
		else if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) != 0)
		{//入力している状態のとき

			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_SPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_SPEED;

			//プレイヤーを通常状態にする
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_NORMAL;

			//カメラ状態を無へ
			pCamera[nCnt].State = CAMERASTATE_NONE;
		}
		else
		{//入力していない場合

			//プレイヤーをステルス状態にする
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;

			//カメラ状態を無へ
			pCamera[nCnt].State = CAMERASTATE_NONE;
		}

		g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;
	}
	else if (g_aPlayer[nCnt].State == PLAYER_EXSIT)
	{
		D3DXVECTOR3 posDest;			//目的の位置
		D3DXVECTOR3 posDiff = D3DXVECTOR3(1000.0f, 0.0f, -1200.0f);

		posDest = posDiff - g_aPlayer[nCnt].pos;

		g_aPlayer[nCnt].pos += posDest * 0.03f;
	}
}

//====================================================================
//プレイヤーの向きの補正
//====================================================================
void PlayerRotUpdate(int nCnt)
{
	//移動方向に向きを合わせる処理
	float fRotMove, fRotDest, fRotDiff;

	int CurrentCamera = GetCurrentCamera();

	fRotMove = g_aPlayer[nCnt].rot.y;
	fRotDest = Getrot(CurrentCamera).y;

	if (GetKeyboardPress(DIK_C) == true)
	{
		g_aPlayer[nCnt].rot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_aPlayer[nCnt].rot.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_W) == true || GetGamepad_Stick_Left(0).y > 0.1f)
	{
		if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * 0.25f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * -0.25f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y));
		}
	}
	else if (GetKeyboardPress(DIK_S) == true || GetGamepad_Stick_Left(0).y < -0.1f)
	{
		if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * -0.75f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).x > 0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(0).x < -0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * -0.5f;
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

	if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).y != 0.0f || GetGamepad_Stick_Left(0).x != 0.0f)
	{
		g_aPlayer[nCnt].rot.y = fRotMove;
	}
}

//====================================================================
//プレイヤーのバイブレーションの更新処理
//====================================================================
void PlayerVibrtionUpdate(int nCnt)
{
	if (g_aPlayer[nCnt].bVibrtion == true)
	{
		g_aPlayer[nCnt].VibrtionTrueCount++;

		if (g_aPlayer[nCnt].VibrtionTrueCount >= g_aPlayer[nCnt].VibrtionTime)
		{
			g_aPlayer[nCnt].bVibrtion = false;
			g_aPlayer[nCnt].VibrtionTrueCount = 0;
			GetGamepad_Vibrtion_false(nCnt);
		}
	}
	else if (g_aPlayer[nCnt].VibrtionFalseCount > 0)
	{
		g_aPlayer[nCnt].VibrtionFalseCount--;
	}
}

//====================================================================
//プレイヤーのバイブレーションの設定処理
//====================================================================
void PlayerSetVibrtion(int nCnt, int nTrueCounter, int nFalseCounter, int nLeftPower, int RightPoewr)
{
	if (g_aPlayer[nCnt].bVibrtion == false)
	{
		g_aPlayer[nCnt].bVibrtion = true;
		g_aPlayer[nCnt].VibrtionTime = nTrueCounter;
		g_aPlayer[nCnt].VibrtionFalseCount = nFalseCounter;
		GetGamepad_Vibrtion(nCnt, nLeftPower, RightPoewr);
	}
}

//====================================================================
//プレイヤーの更新処理(複数のコントローラ対応)
//====================================================================
void UpdatePlayer1(void)
{
	//ポインタ情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	Camera *pCamera = GetCamera();
	int CurrentCamera = GetCurrentCamera();

	//カメラ番号をプレイヤーに代入
	//nCntPlayer = CurrentCamera;
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F6) == true)
	{//バイブレーションをオンにする
		PlayerSetVibrtion(0, 10, 10, 60000, 0);
	}
	if (GetKeyboardTrigger(DIK_F7) == true)
	{//バイブレーションをオフにする
		GetGamepad_Vibrtion_false(0);
	}
#endif

	for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == true && pCamera[nCntPlayer].bUse == true)
		{

			//プレイヤーの状態
			switch (g_aPlayer[nCntPlayer].State)
			{
			case PLAYER_NORMAL:
				break;

			case PLAYER_WAIT:
				g_aPlayer[nCntPlayer].nWaitCounter--;
				if (g_aPlayer[nCntPlayer].nWaitCounter < 0)
				{
					g_aPlayer[nCntPlayer].State = PLAYER_NORMAL;
				}
				break;

			case PLAYER_DAMAGE:
				g_aPlayer[nCntPlayer].nDamageCounter--;
				if (g_aPlayer[nCntPlayer].nDamageCounter < 0)
				{
					g_aPlayer[nCntPlayer].State = PLAYER_WAIT;
				}
				break;

			case PLAYER_HIT:
				g_aPlayer[nCntPlayer].nHitCounter--;
				if (g_aPlayer[nCntPlayer].nHitCounter < 0)
				{
					g_aPlayer[nCntPlayer].State = PLAYER_DAMAGE;
				}
				break;
			}

			g_aPlayer[nCntPlayer].posOld = g_aPlayer[nCntPlayer].pos;

			//減衰係数
			g_aPlayer[nCntPlayer].move.x = g_aPlayer[nCntPlayer].move.x * 0.5f;
			g_aPlayer[nCntPlayer].move.z = g_aPlayer[nCntPlayer].move.z * 0.5f;

			//値の切り捨て
			if (g_aPlayer[nCntPlayer].move.x <= 0.005f && g_aPlayer[nCntPlayer].move.x >= -0.005f)
			{
				g_aPlayer[nCntPlayer].move.x = 0.0f;
			}
			if (g_aPlayer[nCntPlayer].move.z <= 0.005f && g_aPlayer[nCntPlayer].move.z >= -0.005f)
			{
				g_aPlayer[nCntPlayer].move.z = 0.0f;
			}

#ifdef _DEBUG
			if (GetKeyboardTrigger(DIK_F5) == true)
			{//キーが押された場合
				g_bPlayerOps = g_bPlayerOps ? false : true;			//観察用モードに変更
			}
#endif

			if (g_bPlayerOps == false)
			{
				//プレイヤーの移動入力処理----------
				ResPlayerMove(nCntPlayer);
			}

			//位置更新(入力による動き)
			g_aPlayer[nCntPlayer].pos += g_aPlayer[nCntPlayer].move;

			//移動時にプレイヤーの向きを補正する----------
			ResPlayerrot(nCntPlayer);

			//オブジェクトとの当たり判定
			CollisionObject00(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);

		

			CollisionItem(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f, nCntPlayer);

			//出口との当たり判定
			CollisionExi(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);

			//鍵の入手処理
			if (g_aPlayer[nCntPlayer].bGetKey == false)
			{//プレイヤーが鍵を持っていない場合
				if (GetKeyboardTrigger(DIK_E) == true || GetGamepadPress(BUTTON_A, nCntPlayer) || GetGamepadPress(BUTTON_B, nCntPlayer))
				{//Eキー入力
					if (CollisionKey(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nCntPlayer) == true)
					{//鍵を入手出来た場合
						g_aPlayer[nCntPlayer].bGetKey = true;	//鍵を入手状態にする
						SetKeyUI(nCntPlayer, true);				//鍵UIを表示する
					}
				}
			}

			//脱出処理
			if (g_aPlayer[nCntPlayer].bGetKey == true)
			{//プレイヤーが鍵を持っている場合
				if (GetKeyboardTrigger(DIK_E) == true)
				{//Eキー入力
					if (CollisionExit(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nCntPlayer) == true)
					{//鍵を入手出来た場合
						g_aPlayer[nCntPlayer].bGetKey = false;	//鍵を入手してない状態にする
						SetKeyUI(nCntPlayer, false);			//鍵UIを非表示にする
					}
				}
			}

			//一周した時の向きの補正
			if (g_aPlayer[nCntPlayer].rot.y > D3DX_PI * 1.0f)
			{
				g_aPlayer[nCntPlayer].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aPlayer[nCntPlayer].rot.y < -D3DX_PI * 1.0f)
			{
				g_aPlayer[nCntPlayer].rot.y += D3DX_PI * 2.0f;
			}

			//体力が減るかどうかテスト用
			if (GetKeyboardTrigger(DIK_M) == true)
			{
				PlayerHit(nCntPlayer, 1);
			}
		}
	}

#ifdef _DEBUG
	for (int nCntPlayerPlayer = 0; nCntPlayerPlayer < PlayNumber.CurrentSelectNumber; nCntPlayerPlayer++)
	{
		PrintDebugProc("プレイヤー%d人目の座標【X : %f | Y : %f | Z : %f】\n", nCntPlayerPlayer + 1, g_aPlayer[nCntPlayerPlayer].pos.x, g_aPlayer[nCntPlayerPlayer].pos.y, g_aPlayer[nCntPlayerPlayer].pos.z);
		PrintDebugProc("プレイヤー%d人目の移動量【X : %f | Y : %f | Z : %f】\n", nCntPlayerPlayer + 1, g_aPlayer[nCntPlayerPlayer].move.x, g_aPlayer[nCntPlayerPlayer].move.y, g_aPlayer[nCntPlayerPlayer].move.z);
	}
	PrintDebugProc("左スティックの出力【%f】", GetGamepad_Stick_Left(0).y);
	PrintDebugProc("左スティックの出力【%f】", GetGamepad_Stick_Left(0).x);
	PrintDebugProc("右スティックの出力【%f】", GetGamepad_Stick_Right(0).y);
	PrintDebugProc("右スティックの出力【%f】\n", GetGamepad_Stick_Right(0).x);
	PrintDebugProc("左スティックの出力【%f】", GetGamepad_Stick_Left(1).y);
	PrintDebugProc("左スティックの出力【%f】", GetGamepad_Stick_Left(1).x);
	PrintDebugProc("右スティックの出力【%f】", GetGamepad_Stick_Right(1).y);
	PrintDebugProc("右スティックの出力【%f】", GetGamepad_Stick_Right(1).x);
#endif
}

//====================================================================
//プレイヤーの移動入力処理(複数)
//====================================================================
void ResPlayerMove(int nCnt)
{
	//情報の取得
	Stamina *pStamina = GetStamina();
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	Camera *pCamera = GetCamera();
	int CurrentCamera = GetCurrentCamera();

	//斜め移動の速度修正用の関数を初期化する
	g_aPlayer[nCnt].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//キーボードの移動処理
	if (GetKeyboardPress(DIK_W) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.z += 1.0f * cosf(pCamera[nCnt].rot.y);
		g_aPlayer[nCnt].NormarizeMove.x += 1.0f * sinf(pCamera[nCnt].rot.y);

	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.z += -1.0f * cosf(pCamera[nCnt].rot.y);
		g_aPlayer[nCnt].NormarizeMove.x += -1.0f * sinf(pCamera[nCnt].rot.y);
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.x += -1.0f * cosf(pCamera[nCnt].rot.y);
		g_aPlayer[nCnt].NormarizeMove.z -= -1.0f * sinf(pCamera[nCnt].rot.y);

	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.x += 1.0f * cosf(pCamera[nCnt].rot.y);
		g_aPlayer[nCnt].NormarizeMove.z -= 1.0f * sinf(pCamera[nCnt].rot.y);
	}

	if (GetKeyboardPress(DIK_W) == false && GetKeyboardPress(DIK_S) == false && GetKeyboardPress(DIK_A) == false && GetKeyboardPress(DIK_D) == false)
	{//キーボードと同時に入力できないようにする
		if (GetGamepad_Stick_Left(nCnt).y > 0.0f)
		{//左スティックの上入力
			g_aPlayer[nCnt].NormarizeMove.z += cosf(pCamera[nCnt].rot.y);
			g_aPlayer[nCnt].NormarizeMove.x += sinf(pCamera[nCnt].rot.y);
		}
		if (GetGamepad_Stick_Left(nCnt).y < 0.0f)
		{//左スティックの下入力
			g_aPlayer[nCnt].NormarizeMove.z -= cosf(pCamera[nCnt].rot.y);
			g_aPlayer[nCnt].NormarizeMove.x -= sinf(pCamera[nCnt].rot.y);
		}
		if (GetGamepad_Stick_Left(nCnt).x > 0.0f)
		{//左スティックの右入力
		 //左スティックによる左右移動
			g_aPlayer[nCnt].NormarizeMove.x += cosf(pCamera[nCnt].rot.y);
			g_aPlayer[nCnt].NormarizeMove.z -= sinf(pCamera[nCnt].rot.y);
		}
		if (GetGamepad_Stick_Left(nCnt).x < 0.0f)
		{//左スティックの左入力
		 //左スティックによる左右移動
			g_aPlayer[nCnt].NormarizeMove.x -= cosf(pCamera[nCnt].rot.y);
			g_aPlayer[nCnt].NormarizeMove.z += sinf(pCamera[nCnt].rot.y);
		}
	}

	//ノーマライズによって斜め移動の速度を修正する
	g_aPlayer[nCnt].NormarizeMove.y = 0.0f;

	D3DXVec3Normalize(&g_aPlayer[nCnt].NormarizeMove, &g_aPlayer[nCnt].NormarizeMove);

	//キーボードの時の速度設定
	if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_SPEED;
		g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_SPEED;
	}

	//左スティックの速度処理と移動の三段階の使い分け処理
	if (fabsf(GetGamepad_Stick_Left(nCnt).y) + fabsf(GetGamepad_Stick_Left(nCnt).x) != 0 && GetGamepadPress(BUTTON_R, nCnt))
	{//入力してる状態かつAボタンを押しているとき
		if (pStamina[nCnt].bFatige == false)			//プレイヤーが走れる状態かどうか
		{//疲労状態ではなかった場合

			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_DASHSPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_DASHSPEED;

			//プレイヤーをダッシュ状態にする
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_DASH;
		}
	}
	else if (fabsf(GetGamepad_Stick_Left(nCnt).y) + fabsf(GetGamepad_Stick_Left(nCnt).x) < 0.95f)
	{//左スティックを倒し切っていない状態のとき

		g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_STEALTHSPEED;
		g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_STEALTHSPEED;

		g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;

		//プレイヤーをステルス状態にする
		g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;
	}
	else if (fabsf(GetGamepad_Stick_Left(nCnt).y) + fabsf(GetGamepad_Stick_Left(nCnt).x) != 0)
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
//プレイヤーの向き補正(複数)
//====================================================================
void ResPlayerrot(int nCnt)
{
	Camera *pCamera = GetCamera();

	//移動方向に向きを合わせる処理
	float fRotMove, fRotDest, fRotDiff;

	fRotMove = g_aPlayer[nCnt].rot.y;
	fRotDest = pCamera[nCnt].rot.y;

	if (GetKeyboardPress(DIK_C) == true)
	{
		g_aPlayer[nCnt].rot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_aPlayer[nCnt].rot.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_W) == true || GetGamepad_Stick_Left(nCnt).y > 0.1f)
	{
		if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(nCnt).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * 0.25f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(nCnt).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * -0.25f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y));
		}
	}
	else if (GetKeyboardPress(DIK_S) == true || GetGamepad_Stick_Left(nCnt).y < -0.1f)
	{
		if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(nCnt).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(nCnt).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * -0.75f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(nCnt).x > 0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(nCnt).x < -0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * -0.5f;
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

	if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(nCnt).y != 0.0f || GetGamepad_Stick_Left(nCnt).x != 0.0f)
	{
		g_aPlayer[nCnt].rot.y = fRotMove;
	}
}


//====================================================================
//プレイヤーと敵との距離判定
//====================================================================
void PlayerDistance(int nCnt)
{
	ENEMY *pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, 300.0f, 0.0f, -10.0f, 50.0f) == true)
			{//敵の表示処理
				g_aPlayer[nCnt].bAppear = true;
			}
			else
			{
				g_aPlayer[nCnt].bAppear = false;
#if _DEBUG
				g_aPlayer[nCnt].bAppear = true;
#endif // _DEBUG

			}

			if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, 600.0f, 0.0f, -10.0f, 50.0f) == true)
			{//バイブレーション処理
				if (g_aPlayer[nCnt].VibrtionFalseCount <= 0)
				{
					PlayerSetVibrtion(0, 10, 10, 60000, 0);
				}
			}
			else
			{
				GetGamepad_Vibrtion_false(0);
			}

			if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, 800.0f, 0.0f, -10.0f, 50.0f) == true)
			{//サウンド処理

			}
			else
			{

			}
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定
//====================================================================
int CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY)
{
	//注意：intの返り値でHitの関数を呼ぶこと！
	int nCntHit = -1;
	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == true)
		{
			if (
				pos.z + Size >= g_aPlayer[nCntPlayer].pos.z - PLAYER_COLLISIONSIZE &&
				pos.z - Size <= g_aPlayer[nCntPlayer].pos.z + PLAYER_COLLISIONSIZE &&
				pos.x + Size >= g_aPlayer[nCntPlayer].pos.x - PLAYER_COLLISIONSIZE &&
				pos.x - Size <= g_aPlayer[nCntPlayer].pos.x + PLAYER_COLLISIONSIZE &&
				pos.y + MaxY >= g_aPlayer[nCntPlayer].pos.y - 10.0f &&
				pos.y + MinY <= g_aPlayer[nCntPlayer].pos.y + 10.0f
				)
			{//プレイヤーが当たった(Z軸)
				nCntHit = nCntPlayer;
			}
		}
	}
	return nCntHit;
}

//====================================================================
//円の当たり判定
//====================================================================
bool CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn, float MinY, float MaxY)
{//引数は[pos1:自分][pos2:相手][nRadiusOut:外側の半径][nRadiusIn:内側の半径][MinY:下の高さ][MaxY:上の高さ]
	bool nHit = false;

	if (sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.z - pos2.z) * (pos1.z - pos2.z)) <= nRadiusOut
		&& sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
			+ (pos1.z - pos2.z) * (pos1.z - pos2.z)) >= nRadiusIn
		&& pos1.y + MinY < pos2.y
		&& pos1.y + MaxY > pos2.y)
	{//円の判定が当たった
		nHit = true;
	}

	return nHit;
}

//====================================================================
//プレイヤーのヒット処理
//====================================================================
void PlayerHit(int nCnt,int nDamage)
{
	if (g_aPlayer[nCnt].bUse == true)
	{
		g_aPlayer[nCnt].nLife -= nDamage;

		if (g_aPlayer[nCnt].nLife <= 0)
		{
			g_aPlayer[nCnt].nLife = 0;
		}

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
}

//====================================================================
//プレイヤーの描画処理
//====================================================================
void DrawPlayer(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス
	D3DMATERIAL9 matDef;				//現在のマテリアル保存用
	//D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
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
		//for (int nCntModel = 0; nCntModel < g_aPlayer[nCntPlayer].nNumModel; nCntModel++)
		//{

		//	//マテリアルデータへのポインタを所得する
		//	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer[nCntModel]->GetBufferPointer();

		//	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
		//	{
		//		//マテリアルの設定
		//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//		//テクスチャの設定
		//		pDevice->SetTexture(0, g_pTexturePlayer[nCntMat]);

		//		if (g_aPlayer[nCntPlayer].bUse == true)
		//		{
		//			//プレイヤー(パーツ)の描画
		//			g_pMeshPlayer[nCntModel]->DrawSubset(nCntMat);
		//		}
		//	}
		//}

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