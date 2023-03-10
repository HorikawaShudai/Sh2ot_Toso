//========================================================================================
//
// プレイヤーの処理[player.cpp]
// Author: 小笠原　彪
// Author: 坂本　翔唯
// Author: 丹野竜之介
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
#include "light.h"
#include "CheckboxUI.h"
#include "PolygonBG.h"
#include "EscapeTutorial.h"
#include "key.h"
#include "ChasePolygon.h"
#include "time.h"
#include "sound.h"

//マクロ定義
#define PLAYER_STEALTHSPEED		(0.3f)			//プレイヤーのステルススピード
#define PLAYER_SPEED			(1.5f)			//プレイヤーのスピード
#define PLAYER_DASHSPEED		(2.0f)			//プレイヤーのダッシュスピード
#define PLAYER_ROT_SPEED		(0.2f)			//プレイヤーの回転スピード
#define PLAYER_JUMP				(12.0f)			//プレイヤーのジャンプ力
#define PLAYER_LIFE				(3)				//プレイヤーの初期ライフ
#define PLAYER_COLLISIONSIZE	(15.0f)			//プレイヤーの当たり判定の大きさ
#define PLAYER_LIGHT			(350.0f)		//プレイヤーの当たり判定の大きさ
#define ENEMY_SE_SPEED			(60)			//敵の足音を鳴らす間隔
#define PLAYER_SE_WALK			(40)			//プレイヤーの足音を鳴らす間隔(歩き)
#define PLAYER_SE_DASH			(30)			//プレイヤーの足音を鳴らす間隔(ダッシュ)
#define PLAYER_DISTANCE_SE		(800.0f)		//敵の音が聞こえるようになる距離
#define PLAYER_DISTANCE_VIB_S	(600.0f)		//バイブレーション(小)がオンになる距離
#define PLAYER_DISTANCE_VIB_M	(400.0f)		//バイブレーション(中)がオンになる距離
#define PLAYER_DISTANCE_VIB_L	(200.0f)		//バイブレーション(大)がオンになる距離
#define PLAYER_DISTANCE_APPEAR	(250.0f)		//敵が見えるようになる距離
#define PLAYER_WAITCOUNTER		(120)			//プレイヤーの待機状態の長さ
#define PLAYER_DAMAGECOUNTER	(120)			//プレイヤーのダメージ状態の長さ
#define PLAYER_DEATHCOUNTER		(1000)			//プレイヤーの死亡状態の長さ
#define PLAYER_HITCOUNTER		(60)			//プレイヤーのヒット状態の長さ

//プロトタイプ
void UpdatePlayer1(void);

void ResPlayerMove(int nCnt);					//プレイヤーそれぞれに対応
void ResPlayerrot(int nCnt);					//プレイヤーそれぞれに対応

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer[100] = {};	//テクスチャのポインタ
LPD3DXMESH g_pMeshPlayer[32] = {};				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer[32] = {};			//マテリアルへのポインタ
DWORD g_dwNumMatPlayer = 0;						//マテリアルの数
Player g_aPlayer[NUM_PLAYER];					//プレイヤーの情報
int g_nIndexPlayerShadow = -1;					//影のインデックス(番号)
bool g_bPlayerOps;
bool g_GameEnd;
bool bMove;										//プレイヤーが移動したかどうか
int g_Rand_PolygonColor_R;
int g_Rand_PolygonColor_G;
int g_Rand_PolygonColor_B;
int g_Rand_PolygonColor_A;
int g_Rand_PolygonType;
int g_ExitCount;								//脱出した人数
int EnemySECount;								//敵のSEを鳴らす間隔

//====================================================================
//プレイヤーの初期化処理
//====================================================================
void InitPlayer(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].bExit = true;
	}

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
		g_aPlayer[nCntPlayer].LightIdx00 = SetIndexLight();		//ライトのセット処理
		g_aPlayer[nCntPlayer].nWaitCounter = PLAYER_WAITCOUNTER;
		g_aPlayer[nCntPlayer].nDamageCounter = PLAYER_DAMAGECOUNTER;
		g_aPlayer[nCntPlayer].nDeathCounter = PLAYER_DEATHCOUNTER;
		g_aPlayer[nCntPlayer].bChase = false;
		g_aPlayer[nCntPlayer].LightColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_aPlayer[nCntPlayer].bCheck = false;  //チェックボックスがついていない状態に
		g_aPlayer[nCntPlayer].bExit = false;
		g_aPlayer[nCntPlayer].bVibrtion = false;
		g_aPlayer[nCntPlayer].bAppear = false;
#if _DEBUG
		g_aPlayer[nCntPlayer].bAppear = true;
#endif
		g_aPlayer[nCntPlayer].bEnemyRight = false;
		g_aPlayer[nCntPlayer].bEnemyLeft = false;

		g_bPlayerOps = false;
		g_GameEnd = false;
		bMove = false;
		g_aPlayer[nCntPlayer].nStelthCnt = 0;
		g_aPlayer[nCntPlayer].nVibCnt = 0;
		g_aPlayer[nCntPlayer].KeyHelpUI = false;
		g_aPlayer[nCntPlayer].ExitHelpUI = false;

		g_aPlayer[nCntPlayer].nPlayerSECount = 0;

		g_Rand_PolygonColor_R = 0;
		g_Rand_PolygonColor_G = 0;
		g_Rand_PolygonColor_B = 0;
		g_Rand_PolygonColor_A = 0;
		g_Rand_PolygonType = 0;
		g_ExitCount = 0;

		EnemySECount = 0;  //敵のSEを鳴らす処理を初期化

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
	//複数
	UpdatePlayer1();
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
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();
	MODE mode = GetMode();


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

				g_aPlayer[CurrentCamera].bCheck = true;

				//移動したらチェックをつける処理
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//移動した状態にする
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(0).y < 0.0f)
			{//左スティックの下入力
				g_aPlayer[nCnt].NormarizeMove.z -= cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.x -= sinf(Getrot(CurrentCamera).y);

				g_aPlayer[CurrentCamera].bCheck = true;

				//移動したらチェックをつける処理
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//移動した状態にする
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(0).x > 0.0f)
			{//左スティックの右入力
			 //左スティックによる左右移動
				g_aPlayer[nCnt].NormarizeMove.x += cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.z -= sinf(Getrot(CurrentCamera).y);

				g_aPlayer[CurrentCamera].bCheck = true;

				//移動したらチェックをつける処理
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//移動した状態にする
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(0).x < 0.0f)
			{//左スティックの左入力
			 //左スティックによる左右移動
				g_aPlayer[nCnt].NormarizeMove.x -= cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.z += sinf(Getrot(CurrentCamera).y);

				g_aPlayer[CurrentCamera].bCheck = true;

				//移動したらチェックをつける処理
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//移動した状態にする
					MoveTCheck(nCnt, true);
				}
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

				//ダッシュしたらチェック状態にする処理
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_DASH)
				{
					SetCheckUI(nCnt, true);
				}
			}
		}
		else if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) < 0.95f)
		{//左スティックを倒し切っていない状態のとき

			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_STEALTHSPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_STEALTHSPEED;

			g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;

			//プレイヤーをステルス状態にする
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;

			//チュートリアルステルス状態の時の処理
			if (mode == MODE_TUTORIAL && do_Tutorial == MODE_STELTH && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_STEALTH)
			{
				if (g_aPlayer[nCnt].move != D3DXVECTOR3(0.0f, 0.0f, 0.0f) && g_aPlayer[nCnt].nStelthCnt > 299)
				{
					{
						//チェックをつける処理
						SetCheckUI(nCnt, true);
					}
				}
				g_aPlayer[nCnt].nStelthCnt++;
			}

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
	{//プレイヤーの状態が脱出状態の時

		D3DXVECTOR3 posDest;			//目的の位置

		D3DXVECTOR3 posDiff = D3DXVECTOR3(-1000.0f, 0.0f, -4000.0f);

		posDest = posDiff - g_aPlayer[nCnt].pos;

		g_aPlayer[nCnt].pos.x += posDest.x * 0.005f;
		g_aPlayer[nCnt].pos.z += posDest.z * 0.0006f;
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
//プレイヤーの更新処理(複数のコントローラ対応)
//====================================================================
void UpdatePlayer1(void)
{
	//チュートリアルの項目情報を与える処理
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();
	MODE mode = GetMode();

	//ポインタ情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	Camera *pCamera = GetCamera();
	int CurrentCamera = GetCurrentCamera();

	//カメラ番号をプレイヤーに代入
	//nCntPlayer = CurrentCamera;

	for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
	{
		//プレイヤーの状態管理
		PlayerState(nCntPlayer);

		if (g_aPlayer[nCntPlayer].bUse == true && pCamera[nCntPlayer].bUse == true && g_aPlayer[nCntPlayer].State == PLAYER_NORMAL)
		{
#ifdef _DEBUG
			//バイブレーション
			if (GetKeyboardTrigger(DIK_F6) == true)
			{
				PlayerSetVibrtion(nCntPlayer, 60, 0, 60000, 0);
			}
			if (GetKeyboardTrigger(DIK_F7) == true)
			{
				GetGamepad_Vibrtion_false(nCntPlayer);
			}
#endif

			g_aPlayer[nCntPlayer].rot.y += 0.5f;

			//バイブレーションの更新処理
			PlayerVibrtionUpdate(nCntPlayer);

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

				//移動時にプレイヤーの向きを補正
				ResPlayerrot(nCntPlayer);
			}

			//位置更新(入力による動き)
			g_aPlayer[nCntPlayer].pos += g_aPlayer[nCntPlayer].move;

			//オブジェクトとの当たり判定
			CollisionObject00(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 50.0f, 10.0f), 10.0f);
			CollisionObjectWall(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 50.0f, 10.0f), 10.0f);

			//外積の当たり判定
			//CollisionOuterProductObject00(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move);

			if (g_aPlayer[nCntPlayer].bExit == false)
			{//脱出していない状態の時

				//出口との当たり判定
				CollisionExi(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);
			}

			//プレイヤーと敵との距離
			PlayerDistance(nCntPlayer);

			if (g_aPlayer[nCntPlayer].bChase == true)
			{
				g_aPlayer[nCntPlayer].LightColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{
				if (g_aPlayer[nCntPlayer].LightColor.b <= 1.0f || g_aPlayer[nCntPlayer].LightColor.g <= 1.0f)
				{
					g_aPlayer[nCntPlayer].LightColor.b += 0.005f;
					g_aPlayer[nCntPlayer].LightColor.g += 0.005f;
				}
			}

			//プレイヤーが保持するライトの更新処理
			SetLight(g_aPlayer[nCntPlayer].LightIdx00, D3DLIGHT_SPOT, g_aPlayer[nCntPlayer].LightColor, D3DXVECTOR3(g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y + 50.0f, g_aPlayer[nCntPlayer].pos.z), D3DXVECTOR3(sinf(Getrot(nCntPlayer).y), sinf(Getrot(nCntPlayer).x), cosf(Getrot(nCntPlayer).y)), PLAYER_LIGHT, 1.0f);

			//ヘルプUIの表示
			if (g_aPlayer[nCntPlayer].bGetKey == false)
			{
				g_aPlayer[nCntPlayer].KeyHelpUI = CollisionKeyHelpUI(&g_aPlayer[nCntPlayer].pos, 200.0f);
			}
			if (g_aPlayer[nCntPlayer].bGetKey == true)
			{
				g_aPlayer[nCntPlayer].ExitHelpUI = CollisionExitHelpUI(&g_aPlayer[nCntPlayer].pos, 350.0f);
			}

			//鍵の入手処理
			if (g_aPlayer[nCntPlayer].bGetKey == false)
			{//プレイヤーが鍵を持っていない場合
				if (GetKeyboardTrigger(DIK_E) == true || GetGamepadTrigger(BUTTON_A, nCntPlayer) || GetGamepadTrigger(BUTTON_B, nCntPlayer))
				{//Eキー入力
					if (CollisionKey(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nCntPlayer) == true)
					{//鍵を入手出来た場合
						g_aPlayer[nCntPlayer].bGetKey = true;		//鍵を入手状態にする
						SetKeyUI(nCntPlayer, true);					//鍵UIを表示する
						g_aPlayer[nCntPlayer].KeyHelpUI = false;

						//鍵の入手音
						PlaySound(SOUND_LABEL_SE_GETKEY);

						g_aPlayer[nCntPlayer].bCheck = true;

						//鍵をゲットしたとき
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_GET_KEY)
						{
							//チェックをつける処理
							SetCheckUI(nCntPlayer, true);
						}
					}
				}
			}

			//脱出処理
			if (g_aPlayer[nCntPlayer].bGetKey == true)
			{//プレイヤーが鍵を持っている場合
				if (GetKeyboardTrigger(DIK_E) == true || GetGamepadTrigger(BUTTON_A, nCntPlayer) || GetGamepadTrigger(BUTTON_B, nCntPlayer))
				{//Eキー入力
					if (CollisionExit(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nCntPlayer) == true)
					{//鍵を入手出来た場合

						//ドアのカギを解除する音
						PlaySound(SOUND_LABEL_SE_UNLOCKKEY);

						g_aPlayer[nCntPlayer].bGetKey = false;	//鍵を入手してない状態にする
						SetKeyUI(nCntPlayer, false);			//鍵UIを非表示にする
						g_aPlayer[nCntPlayer].ExitHelpUI = false;

						//チュートリアルモード脱出の時
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_ESCAPE)
						{
							//チェックをつける
							SetCheckUI(nCntPlayer, true);

							do_Tutorial = MODE_GOEXIT;
						}

						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_GOEXIT)
						{
							do_Tutorial = MODE_END;
						}
					}
				}
			}

			//プレイヤーがカギを持っていないとき
			else
			{//プレイヤーが鍵を持っている場合
				if (GetKeyboardTrigger(DIK_E) == true || GetGamepadTrigger(BUTTON_A, nCntPlayer) || GetGamepadTrigger(BUTTON_B, nCntPlayer))
				{//Eキー入力
					if (CollisionExit(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nCntPlayer) == true)
					{//鍵を入手出来た場合
						//鍵を持っていないときの音
						PlaySound(SOUND_LABEL_SE_NOKEY);
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
		else if (g_aPlayer[nCntPlayer].bUse == false && g_aPlayer[nCntPlayer].State != PLAYER_DEATH)
		{
			g_aPlayer[nCntPlayer].State = PLAYER_SMITE;
		}
	}

	//ゲーム終了処理
	if (g_GameEnd == false)
	{
		if ((g_aPlayer[0].bExit == true || g_aPlayer[0].bUse == false) &&
			(g_aPlayer[1].bExit == true || g_aPlayer[1].bUse == false) &&
			(g_aPlayer[2].bExit == true || g_aPlayer[2].bUse == false) &&
			(g_aPlayer[3].bExit == true || g_aPlayer[3].bUse == false))
		{//全員脱出しているとき

			for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
			{
				if (g_aPlayer[nCntPlayer].bExit == true)
				{
					g_ExitCount++;
				}
			}

			//チュートリアルモード脱出の時
			if (GetMode() == MODE_TUTORIAL)
			{
				g_GameEnd = true;
				SetFade(MODE_GAME);
			}
			if (GetMode() == MODE_GAME)
			{
				g_GameEnd = true;
				SetGameState(GAMESTATE_CLEAR_END, 60);
				SetFalseCount(false);
				SetRankTime();

				if (g_ExitCount == PlayNumber.CurrentSelectNumber)
				{//全員脱出出来た場合
					SetClear(1);
				}
				else if (g_ExitCount != 1)
				{//全員ではないが脱出出来た場合
					SetClear(2);
				}
				else
				{//一人だけ脱出出来た場合
					SetClear(3);
				}
			}
		}

		if ((g_aPlayer[0].bUse == false) && 
			(g_aPlayer[1].bUse == false) && 
			(g_aPlayer[2].bUse == false) && 
			(g_aPlayer[3].bUse == false))
		{//全員死亡しているとき
			g_GameEnd = true;
			SetGameState(GAMESTATE_GAMEOVER_END, 340);
			SetFalseCount(false);
		}
	}

#ifdef _DEBUG
	for (int nCntPlayerPlayer = 0; nCntPlayerPlayer < PlayNumber.CurrentSelectNumber; nCntPlayerPlayer++)
	{
		PrintDebugProc("プレイヤー%d人目の座標【X : %f | Y : %f | Z : %f】\n", nCntPlayerPlayer + 1, g_aPlayer[nCntPlayerPlayer].pos.x, g_aPlayer[nCntPlayerPlayer].pos.y, g_aPlayer[nCntPlayerPlayer].pos.z);
		PrintDebugProc("プレイヤー%d人目の移動量【X : %f | Y : %f | Z : %f】\n", nCntPlayerPlayer + 1, g_aPlayer[nCntPlayerPlayer].move.x, g_aPlayer[nCntPlayerPlayer].move.y, g_aPlayer[nCntPlayerPlayer].move.z);
		PrintDebugProc("プレイヤーが脱出した数【%d】\n", g_ExitCount);
	}
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
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();
	MODE mode = GetMode();

	//斜め移動の速度修正用の関数を初期化する
	g_aPlayer[nCnt].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (g_aPlayer[nCnt].State != PLAYER_EXSIT)
	{//プレイヤーの状態が脱出状態以外の場合
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

				g_aPlayer[nCnt].nPlayerSECount++;

				if (g_aPlayer[nCnt].nPlayerSECount > PLAYER_SE_WALK && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_NORMAL)
				{
					//プレイヤーの歩き
					PlaySound(SOUND_LABEL_SE_WALK);

					g_aPlayer[nCnt].nPlayerSECount = 0;
				}

				else
				{

				}

				//移動したらチェックをつける処理
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//移動した状態にする
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(nCnt).y < 0.0f)
			{//左スティックの下入力
				g_aPlayer[nCnt].NormarizeMove.z -= cosf(pCamera[nCnt].rot.y);
				g_aPlayer[nCnt].NormarizeMove.x -= sinf(pCamera[nCnt].rot.y);

				g_aPlayer[nCnt].nPlayerSECount++;

				if (g_aPlayer[nCnt].nPlayerSECount > PLAYER_SE_WALK && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_NORMAL)
				{
					//プレイヤーの歩き
					PlaySound(SOUND_LABEL_SE_WALK);

					g_aPlayer[nCnt].nPlayerSECount = 0;
				}

				else
				{

				}

				//移動したらチェックをつける処理
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//移動した状態にする
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(nCnt).x > 0.0f)
			{//左スティックの右入力
			 //左スティックによる左右移動
				g_aPlayer[nCnt].NormarizeMove.x += cosf(pCamera[nCnt].rot.y);
				g_aPlayer[nCnt].NormarizeMove.z -= sinf(pCamera[nCnt].rot.y);

				g_aPlayer[nCnt].nPlayerSECount++;

				if (g_aPlayer[nCnt].nPlayerSECount > PLAYER_SE_WALK && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_NORMAL)
				{
					//プレイヤーの歩き
					PlaySound(SOUND_LABEL_SE_WALK);

					g_aPlayer[nCnt].nPlayerSECount = 0;
				}

				else
				{

				}

				//移動したらチェックをつける処理
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//移動した状態にする
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(nCnt).x < 0.0f)
			{//左スティックの左入力
			 //左スティックによる左右移動
				g_aPlayer[nCnt].NormarizeMove.x -= cosf(pCamera[nCnt].rot.y);
				g_aPlayer[nCnt].NormarizeMove.z += sinf(pCamera[nCnt].rot.y);

				g_aPlayer[nCnt].nPlayerSECount++;

				if (g_aPlayer[nCnt].nPlayerSECount > PLAYER_SE_WALK && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_NORMAL)
				{
					//プレイヤーの歩き
					PlaySound(SOUND_LABEL_SE_WALK);

					g_aPlayer[nCnt].nPlayerSECount = 0;
				}

				else
				{

				}

				//移動したらチェックをつける処理
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//移動した状態にする
					MoveTCheck(nCnt, true);
				}
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
		if (fabsf(GetGamepad_Stick_Left(nCnt).y) + fabsf(GetGamepad_Stick_Left(nCnt).x) != 0 && GetGamepadPress(BUTTON_R, nCnt) || GetKeyboardPress(DIK_SPACE) == true)
		{//入力してる状態かつAボタンを押しているとき
			if (pStamina[nCnt].bFatige == false)			//プレイヤーが走れる状態かどうか
			{//疲労状態ではなかった場合

				g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_DASHSPEED;
				g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_DASHSPEED;

				g_aPlayer[nCnt].nPlayerSECount++;

				if (g_aPlayer[nCnt].nPlayerSECount > PLAYER_SE_DASH && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_DASH)
				{
					//ダッシュ状態の音
					PlaySound(SOUND_LABEL_SE_WALK);

					g_aPlayer[nCnt].nPlayerSECount = 0;
				}

				else
				{

				}

				//プレイヤーをダッシュ状態にする
				g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_DASH;

				//ダッシュしたらチェック状態にする処理
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_DASH)
				{
					SetCheckUI(nCnt, true);
				}
			}
		}
		else if ((fabsf(GetGamepad_Stick_Left(nCnt).y) + fabsf(GetGamepad_Stick_Left(nCnt).x) < 0.95f) || GetGamepadPress(BUTTON_L, nCnt))
		{//左スティックを倒し切っていない状態のとき

			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_STEALTHSPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_STEALTHSPEED;

			g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;

			//プレイヤーをステルス状態にする
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;

			//チュートリアルステルス状態の時の処理
			if (mode == MODE_TUTORIAL && do_Tutorial == MODE_STELTH && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_STEALTH)
			{
				if (g_aPlayer[nCnt].move != D3DXVECTOR3(0.0f, 0.0f, 0.0f) && g_aPlayer[nCnt].nStelthCnt > 299)
				{
					{
						//チェックをつける処理
						SetCheckUI(nCnt, true);
					}
				}
				g_aPlayer[nCnt].nStelthCnt++;
			}
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
//プレイヤーの状態管理
//====================================================================
void PlayerState(int nCnt)
{
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//プレイヤーの状態
	switch (g_aPlayer[nCnt].State)
	{
	case PLAYER_NORMAL:
		break;

	case PLAYER_WAIT:
		g_aPlayer[nCnt].nWaitCounter--;
		if (g_aPlayer[nCnt].nWaitCounter < 0)
		{
			g_aPlayer[nCnt].nWaitCounter = PLAYER_WAITCOUNTER;
			g_aPlayer[nCnt].State = PLAYER_NORMAL;
		}
		break;

	case PLAYER_HIT:
		g_aPlayer[nCnt].nHitCounter--;
		g_Rand_PolygonColor_R = rand() % 11;
		g_Rand_PolygonColor_G = rand() % 4;
		g_Rand_PolygonColor_B = rand() % 11;
		g_Rand_PolygonColor_A = rand() % 11;
		g_Rand_PolygonType = rand() % 4;
		if (g_aPlayer[nCnt].nHitCounter == 59)
		{
			switch (PlayNumber.CurrentSelectNumber)
			{
			case 1:
				SetPolygonBG(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 640.0f, 360.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				break;
			case 2:
				SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 360.0f, 0.0f), 320.0f, 360.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				break;
			case 3:
				if (nCnt == 2)
				{//3
					SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				}
				else
				{//12
					SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				}
				break;
			case 4:
				if (nCnt == 3)
				{//4
					SetPolygonBG(D3DXVECTOR3(960.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				}
				else if (nCnt == 2)
				{//3
					SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				}
				else
				{//12
					SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				}
				break;
			}
		}
		if (g_aPlayer[nCnt].nHitCounter % 10 == 0)
		{
			switch (PlayNumber.CurrentSelectNumber)
			{
			case 1:
				SetPolygonBG(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 640.0f, 360.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				break;
			case 2:
				SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 360.0f, 0.0f), 320.0f, 360.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				break;
			case 3:
				if (nCnt == 2)
				{//3
					SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				}
				else
				{//12
					SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				}
				break;
			case 4:
				if (nCnt == 3)
				{//4
					SetPolygonBG(D3DXVECTOR3(960.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				}
				else if (nCnt == 2)
				{//3
					SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				}
				else
				{//12
					SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				}
				break;
			}
		}
		if (g_aPlayer[nCnt].nHitCounter < 0)
		{
			g_aPlayer[nCnt].State = PLAYER_WAIT;
		}
		break;

	case PLAYER_DAMAGE:
		g_aPlayer[nCnt].nDamageCounter--;
		if (g_aPlayer[nCnt].nDamageCounter < 0)
		{
			g_aPlayer[nCnt].State = PLAYER_DEATH;

		g_aPlayer[nCnt].State = PLAYER_SMITE;
		}
		break;

	case PLAYER_DEATH:
		//死んだプレイヤーのバイブレーションをオフにする
		GetGamepad_Vibrtion_false(nCnt);

		switch (PlayNumber.CurrentSelectNumber)
		{
		case 1:
			SetPolygonBG(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 640.0f, 360.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			break;
		case 2:
			SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 360.0f, 0.0f), 320.0f, 360.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			break;
		case 3:
			if (nCnt == 2)
			{//3
				SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			}
			else
			{//12
				SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			}
			break;
		case 4:
			if (nCnt == 3)
			{//4
				SetPolygonBG(D3DXVECTOR3(960.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			}
			else if (nCnt == 2)
			{//3
				SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			}
			else
			{//12
				SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			}
			break;
		}

		break;
	case PLAYER_EXSIT:

		D3DXVECTOR3 posDest;			//目的の位置

		D3DXVECTOR3 posDiff = D3DXVECTOR3(-1000.0f, 0.0f, -4000.0f);

		posDest = posDiff - g_aPlayer[nCnt].pos;

		g_aPlayer[nCnt].pos.x += posDest.x * 0.005f;
		g_aPlayer[nCnt].pos.z += posDest.z * 0.0006f;
		SetLife(0, nCnt);

		switch (PlayNumber.CurrentSelectNumber)
		{
		case 1:
			SetPolygonBG(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 640.0f, 360.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			break;
		case 2:
			SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 360.0f, 0.0f), 320.0f, 360.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			break;
		case 3:
			if (nCnt == 2)
			{//3
				SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			}
			else
			{//12
				SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			}
			break;
		case 4:
			if (nCnt == 3)
			{//4
				SetPolygonBG(D3DXVECTOR3(960.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			}
			else if (nCnt == 2)
			{//3
				SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			}
			else
			{//12
				SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 30, 4);
			}
			break;
		}
		break;
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
		SetColorChasePolygon((float)g_aPlayer[nCnt].VibrtionTrueCount, nCnt);

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
		SetColorChasePolygonMAX((float)nTrueCounter, nCnt);
	}
}

//====================================================================
//プレイヤーと敵との距離判定と位置関係の外積
//====================================================================
void PlayerDistance(int nCnt)
{
	ENEMY *pEnemy = GetEnemy();

	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();

	MODE mode = GetMode();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, PLAYER_DISTANCE_APPEAR, 0.0f, -10.0f, 50.0f) == true)
			{//敵の表示処理
				g_aPlayer[nCnt].bAppear = true;
				break;
			}
			else
			{
				g_aPlayer[nCnt].bAppear = false;
#if _DEBUG
				g_aPlayer[nCnt].bAppear = true;
#endif // _DEBUG

			}
		}
	}

	pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			//チュートリアル項目用距離判定
			if (mode == MODE_TUTORIAL && do_Tutorial == MODE_VIBE)
			{
				if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, PLAYER_DISTANCE_VIB_S, 0.0f, -10.0f, 50.0f) == true)
				{//バイブレーション処理
					if (g_aPlayer[nCnt].VibrtionFalseCount <= 0)
					{
						g_aPlayer[nCnt].nVibCnt++;
						if (g_aPlayer[nCnt].nVibCnt > 5)
						{
							SetCheckUI(nCnt, true);
						}
					}
				}
			}

			if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, PLAYER_DISTANCE_VIB_L, 0.0f, -10.0f, 50.0f) == true)
			{//バイブレーション処理(大)
				if (g_aPlayer[nCnt].VibrtionFalseCount <= 0)
				{
					PlayerSetVibrtion(nCnt, 5, 5, 60000, 60000);
				}
			}
			else if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, PLAYER_DISTANCE_VIB_M, 0.0f, -10.0f, 50.0f) == true)
			{//バイブレーション処理(中)
				if (g_aPlayer[nCnt].VibrtionFalseCount <= 0)
				{
					PlayerSetVibrtion(nCnt, 10, 10, 40000, 40000);
				}
			}
			else if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, PLAYER_DISTANCE_VIB_S, 0.0f, -10.0f, 50.0f) == true)
			{//バイブレーション処理(小)
				if (g_aPlayer[nCnt].VibrtionFalseCount <= 0)
				{
					PlayerSetVibrtion(nCnt, 20, 20, 20000, 20000);
				}
			}

			if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, PLAYER_DISTANCE_SE, 0.0f, -10.0f, 50.0f) == true)
			{//サウンド処理
				EnemySECount++;

				if (EnemySECount > ENEMY_SE_SPEED)
				{
					PlaySound(SOUND_LABEL_SE_ENEMYMOVE);

					EnemySECount = 0;
				}
			}
		}
	}

	//プレイヤーと敵の位置関係を示す外積
	pEnemy = GetEnemy();
	Camera *pCamera = GetCamera();
	pCamera += nCnt;
	for (int nCntEnemy = 0, nEnemyL = 0, nEnemyR = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{

			if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, PLAYER_DISTANCE_VIB_S, 0.0f, -10.0f, 50.0f) == true)
			{
				D3DXVECTOR3 vecToPos;
				D3DXVECTOR3 vecLine;
				float A;

				vecToPos.x = (pEnemy->pos.x) - (g_aPlayer[nCnt].pos.x);
				vecToPos.z = (pEnemy->pos.z) - (g_aPlayer[nCnt].pos.z);

				vecLine.x = sinf(pCamera->rot.y);
				vecLine.y = 0.0f;
				vecLine.z = cosf(pCamera->rot.y);

				A = (vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z);

				if (A < 0)
				{
					g_aPlayer[nCnt].bEnemyRight = true;
					nEnemyR++;
				}
				else
				{
					g_aPlayer[nCnt].bEnemyLeft = true;
					nEnemyL++;
				}
#ifdef _DEBUG
				PrintDebugProc("aaaaaa:%f\n", A);
				PrintDebugProc("aaaaaa:%f\n", pCamera->rot.y);
#endif // DEBUG
			}
			if (nEnemyR > 0)
			{
				g_aPlayer[nCnt].bEnemyRight = true;
			}
			else
			{
				g_aPlayer[nCnt].bEnemyRight = false;
			}
			if (nEnemyL > 0)
			{
				g_aPlayer[nCnt].bEnemyLeft = true;
			}
			else
			{
				g_aPlayer[nCnt].bEnemyLeft = false;
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
//プレイヤーとの外積の当たり判定
//====================================================================
D3DXVECTOR3 CollisionOuterProductPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	//移動ベクトルを割り出す
	D3DXVECTOR3 vecMove = *pPos - *pPosOld;
	//座標保管用
	int nPosCount = 0;
	D3DXVECTOR3 pos[NUM_PLAYER * 4] = {};
	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		if (g_aPlayer[nCnt].bUse == true)
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
					pos0 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + -25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + 25.0f);
					pos1 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + 25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + 25.0f);
					break;
				case 1:
					pos0 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + 25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + 25.0f);
					pos1 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + 25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + -25.0f);
					break;
				case 2:
					pos0 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + 25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + -25.0f);
					pos1 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + -25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + -25.0f);
					break;
				case 3:
					pos0 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + -25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + -25.0f);
					pos1 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + -25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + 25.0f);
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
					pos[nPosCount] = g_aPlayer[nCnt].pos;
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
		return pos[0];
	}
	


	return D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
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
void PlayerHit(int nCnt, int nDamage)
{
	if (g_aPlayer[nCnt].bUse == true && g_aPlayer[nCnt].State == PLAYER_NORMAL)
	{
		g_aPlayer[nCnt].nLife -= nDamage;

		if (g_aPlayer[nCnt].nLife > 0)
		{
			//ダメージ音(ライフがマックスか、2の時)
			PlaySound(SOUND_LABEL_SE_DAMAGE);
		}

		else
		{
			////ダメージ音(ライフが1の時)
			//PlaySound(SOUND_LABEL_SE_DAMAGE);
		}

		if (g_aPlayer[nCnt].nLife <= 0)
		{
			g_aPlayer[nCnt].nLife = 0;
		}

		//ライフのセット処理
		SetLife(nDamage, nCnt);

		if (g_aPlayer[nCnt].nLife <= 0)
		{
			g_aPlayer[nCnt].bUse = false;
			g_aPlayer[nCnt].State = PLAYER_DAMAGE;
			g_aPlayer[nCnt].nDamageCounter = PLAYER_DAMAGECOUNTER;
			if (g_aPlayer[nCnt].bGetKey == true)
			{
				g_aPlayer[nCnt].bGetKey = false;
				SetKey(D3DXVECTOR3(g_aPlayer[nCnt].pos.x, g_aPlayer[nCnt].pos.y + 3.0f, g_aPlayer[nCnt].pos.z), D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.1f, 0.0f), 0);
				SetKeyUI(nCnt, false);					//鍵UIを表示する
			}
		}

		else
		{
			g_aPlayer[nCnt].State = PLAYER_HIT;
			g_aPlayer[nCnt].nHitCounter = PLAYER_HITCOUNTER;

			//ダメージ後のノイズの音
			PlaySound(SOUND_LABEL_SE_NOIZE);
		}
		g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;
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

		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//制限時間終了時の処理
//====================================================================
void PlayerAllDown(void)
{
	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].bUse = false;
	}
}

//====================================================================
//プレイヤー情報の所得
//====================================================================
Player * GetPlayer(void)
{
	return &g_aPlayer[0];
}

//====================================================================
//脱出人数の所得
//====================================================================
int GetExitCount(void)
{
	return g_ExitCount;
}