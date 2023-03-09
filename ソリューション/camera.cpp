//========================================================================================
//
// カメラ処理[camera.cpp]
// Author: 坂本　翔唯
// Author: 小笠原　彪
//
//========================================================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "PlayNumberSelect.h"
#include "debugproc.h"
#include "CheckboxUI.h"
#include "EscapeTutorial.h"
#include "game.h"
#include "enemy.h"
#include "light.h"

//マクロ定義
#define MAX_CAMERA				(5)		//カメラの最大数

#define CAMERA_DISTANCE			(5.0f)		//視点と注視点の距離
#define MODEL_DISTANCE			(10.0f)		//モデルと注視点の距離
#define CAMERA_SPEED			(2.5f)		//カメラの移動スピード
#define CAMERA_VR_SPEED			(0.047f)	//カメラの視点スピード
#define CAMERA_HOMING			(0.1f)		//カメラの追従スピード
#define CAMERA_HOMING_POSY		(35.0f)		//カメラの追従の位置(Y座標)
#define CAMERA_CORR_V			(0.7f)		//カメラ視点の補正
#define CAMERA_CORR_R			(0.8f)		//カメラ注視点の補正
#define CAMERA_LENGTH_R			(0.0f)		//プレイヤーとカメラ注視点との距離

#define POS_MOVE_MAX			(5.0f)		//視点位置の最大値
#define UP_DOWN_SPPED			(0.4f)		//視点の上下移動の速さ
#define YUAN_TO_CORRE			(0.2f)		//視点の元の位置への補正
#define CAM_MOVE_SPEED			(0.0005f)	//タイトル用カメラの移動スピード

//ダメージをくらった時のカメラ設定
#define DAMAGECAMERA_ROT_Y		(-0.5f)		//ダメージを受けた時のカメラを下に向ける角度
#define DAMAGECAMERA_TIME		(120)		//下を向かせ続ける時間
#define DAMAGECAMERA_UPSPEED	(0.009f)	//下に向けた角度から前に向かせる速さ

//死んだ時のカメラ設定
#define DEATHCAMERA_POS_Y		(8.0f)		//カメラが下にどこまで落ちるか
#define DEATHCAMERA_SPEED		(1.0f)		//カメラが下に落ちる速さ
#define DEATHCAMERA_ROTEND		(1.0f)		//カメラ上に向ける限界
#define DEATHCAMERA_TIME		(120)		//カメラが動かない時間
#define DEATHCAMERA_UPSPEED		(0.001f)		//

//プロトタイプ宣言
void TpsCamera(void);						//観察用カメラ
void Camerafollow(int nCurrentCamera);		//追従カメラ
void CameraMove(int nCurrentCamera);		//カメラ移動
void StateYMove(int nCurrentCamera);		//カメラの縦の動き

void PlayerCamera(void);					//コントローラーそれぞれに対応
void DownCamera(int nCntCamera);			//ダメージを受けた時のカメラ
void DeathCameraEnemy(int nCntCamera);		//死んだときのカメラ(敵の方向に向ける)
void DeathCamera(int nCntCamera);			//死んだときのカメラ(カメラが落ちる)

void Titlecamera(void);
void SelectNumberCamera(void);
void ResultCamera(void);
void RankingCamera(void);

//グローバル変数
Camera g_aCamera[MAX_CAMERA];				//カメラの情報

int g_nCurrentCamera;						//選択されているカメラの番号
int g_nSaveCamera;							//カメラ番号保存用
bool g_bTpsCamera;							//観察用のカメラを使うかどうか
bool bEnter;								//エンターが押されたかどうか
bool bCamMove;								//カメラが動いたかどうか
int g_Rand_RankingCameraBG;					//ランキング画面の背景を決めるための変数
int g_nCount[NUM_PLAYER];					//色々なカウント(加速していく時間、ダメージを受けた時のカメラ)
int g_nCount1[NUM_PLAYER];
float g_Acc[NUM_PLAYER];									//加速度

//====================================================================
//カメラの初期化処理
//====================================================================
void InitCamera(void)
{
	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	MODE mode = GetMode();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		g_aCamera[nCntCamera].posV = D3DXVECTOR3(0.0f, 35.0f, 50.0f);
		g_aCamera[nCntCamera].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_aCamera[nCntCamera].rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
		g_aCamera[nCntCamera].rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].State = CAMERASTATE_NONE;

		g_aCamera[nCntCamera].fposVmoveY = CAMERA_HOMING_POSY;
		g_aCamera[nCntCamera].fposRmoveY = CAMERA_HOMING_POSY;
		g_aCamera[nCntCamera].bUse = false;
	}

	g_nCurrentCamera = 0;			//選択されているカメラの番号を最初のカメラへ
	g_bTpsCamera = false;			//観察用カメラを使っていない状態へ
	bEnter = false;					//エンターを押していない状態に
	bCamMove = false;

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		g_nCount[nCnt] = 0;
		g_nCount1[nCnt] = 0;
		g_Acc[nCnt] = 0.0f;
	}
	g_Rand_RankingCameraBG = rand() % 4;
	
	switch (PlayNumber.CurrentSelectNumber)
	{
	case 1:
		//1人用
		g_aCamera[0].viewport.X = 0;				// 描画する画面の左上X座標
		g_aCamera[0].viewport.Y = 0;				// 描画する画面の左上Y座標
		g_aCamera[0].viewport.Width = 1280;			// 画面の幅
		g_aCamera[0].viewport.Height = 720;			// 画面の高さ
		g_aCamera[0].viewport.MinZ = 0.0f;			// 
		g_aCamera[0].viewport.MaxZ = 1.0f;			// 
		break;
	case 2:
		//2人用(一人目)//
		g_aCamera[0].viewport.X = 0;				// 描画する画面の左上X座標
		g_aCamera[0].viewport.Y = 0;				// 描画する画面の左上Y座標
		g_aCamera[0].viewport.Width = 640;			// 画面の幅
		g_aCamera[0].viewport.Height = 720;			// 画面の高さ
		g_aCamera[0].viewport.MinZ = 0.0f;
		g_aCamera[0].viewport.MaxZ = 1.0f;

		//2人用(二人目)
		g_aCamera[1].viewport.X = 640;				// 描画する画面の左上X座標
		g_aCamera[1].viewport.Y = 0;					// 描画する画面の左上Y座標
		g_aCamera[1].viewport.Width = 640;			// 画面の幅
		g_aCamera[1].viewport.Height = 720;			// 画面の高さ
		g_aCamera[1].viewport.MinZ = 0.0f;
		g_aCamera[1].viewport.MaxZ = 1.0f;
		break;
	case 3:
		//3・4人用(1人目)//
		g_aCamera[0].viewport.X = 0;				// 描画する画面の左上X座標
		g_aCamera[0].viewport.Y = 0;				// 描画する画面の左上Y座標
		g_aCamera[0].viewport.Width = 640;			// 画面の幅
		g_aCamera[0].viewport.Height = 360;			// 画面の高さ
		g_aCamera[0].viewport.MinZ = 0.0f;
		g_aCamera[0].viewport.MaxZ = 1.0f;

		//3・4人用(2人目)
		g_aCamera[1].viewport.X = 640;				// 描画する画面の左上X座標
		g_aCamera[1].viewport.Y = 0;				// 描画する画面の左上Y座標
		g_aCamera[1].viewport.Width = 640;			// 画面の幅
		g_aCamera[1].viewport.Height = 360;			// 画面の高さ
		g_aCamera[1].viewport.MinZ = 0.0f;
		g_aCamera[1].viewport.MaxZ = 1.0f;

		//3・4人用(3人目)
		g_aCamera[2].viewport.X = 0;				// 描画する画面の左上X座標
		g_aCamera[2].viewport.Y = 360;					// 描画する画面の左上Y座標
		g_aCamera[2].viewport.Width = 640;			// 画面の幅
		g_aCamera[2].viewport.Height = 360;			// 画面の高さ
		g_aCamera[2].viewport.MinZ = 0.0f;
		g_aCamera[2].viewport.MaxZ = 1.0f;
		break;
	case 4:
		//3・4人用(1人目)//
		g_aCamera[0].viewport.X = 0;				// 描画する画面の左上X座標
		g_aCamera[0].viewport.Y = 0;				// 描画する画面の左上Y座標
		g_aCamera[0].viewport.Width = 640;			// 画面の幅
		g_aCamera[0].viewport.Height = 360;			// 画面の高さ
		g_aCamera[0].viewport.MinZ = 0.0f;
		g_aCamera[0].viewport.MaxZ = 1.0f;
		//3・4人用(2人目)
		g_aCamera[1].viewport.X = 640;				// 描画する画面の左上X座標
		g_aCamera[1].viewport.Y = 0;				// 描画する画面の左上Y座標
		g_aCamera[1].viewport.Width = 640;			// 画面の幅
		g_aCamera[1].viewport.Height = 360;			// 画面の高さ
		g_aCamera[1].viewport.MinZ = 0.0f;
		g_aCamera[1].viewport.MaxZ = 1.0f;
		//3・4人用(3人目)
		g_aCamera[2].viewport.X = 0;				// 描画する画面の左上X座標
		g_aCamera[2].viewport.Y = 360;				// 描画する画面の左上Y座標
		g_aCamera[2].viewport.Width = 640;			// 画面の幅
		g_aCamera[2].viewport.Height = 360;			// 画面の高さ
		g_aCamera[2].viewport.MinZ = 0.0f;
		g_aCamera[2].viewport.MaxZ = 1.0f;
		//3・4人用(4人目)
		g_aCamera[3].viewport.X = 640;				// 描画する画面の左上X座標
		g_aCamera[3].viewport.Y = 360;				// 描画する画面の左上Y座標
		g_aCamera[3].viewport.Width = 640;			// 画面の幅
		g_aCamera[3].viewport.Height = 360;			// 画面の高さ
		g_aCamera[3].viewport.MinZ = 0.0f;
		g_aCamera[3].viewport.MaxZ = 1.0f;
		break;
	}
	
	//その他用(3D画面タイトルなど)
	g_aCamera[4].viewport.X = 0;					// 描画する画面の左上X座標
	g_aCamera[4].viewport.Y = 0;					// 描画する画面の左上Y座標
	g_aCamera[4].viewport.Width = 1280;				// 画面の幅
	g_aCamera[4].viewport.Height = 720;				// 画面の高さ
	g_aCamera[4].viewport.MinZ = 0.0f;				// 
	g_aCamera[4].viewport.MaxZ = 1.0f;				// 
}

//====================================================================
//カメラの終了処理
//====================================================================
void UninitCamera(void)
{

}

//====================================================================
//カメラの更新処理
//====================================================================
void UpdateCamera(void)
{
	MODE mode = GetMode();

	switch (mode)
	{
	case MODE_TITLE:
		
		if (bEnter == false)
		{
			Titlecamera();
		}

		if (bEnter == true)
		{
			MoveTitleCamera(1);
		}

		break;
	case MODE_NUMBERSELECT:
		SelectNumberCamera();
		break;
	case MODE_TUTORIAL:
#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_F5) == true)
		{//キーが押された場合
			g_bTpsCamera = g_bTpsCamera ? false : true;			//観察用モードに変更
		}
#endif
		//三人称カメラを使うかどうか
		if (g_bTpsCamera == false)
		{//使っていない場合
		 //プレイヤー視点カメラ
			PlayerCamera();
		}
		else
		{//使われている場合
		 //観察用モード
			TpsCamera();
		}
		break;
	case MODE_GAME:
#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_F5) == true)
		{//キーが押された場合
			g_bTpsCamera = g_bTpsCamera ? false : true;			//観察用モードに変更
		}
#endif
		//三人称カメラを使うかどうか
		if (g_bTpsCamera == false)
		{//使っていない場合
			//プレイヤー視点カメラ
			//PlayerFpsCamera();
			PlayerCamera();
		}
		else
		{//使われている場合
			//観察用モード
			TpsCamera();
		}
		break;
	case MODE_RESULT:
		ResultCamera();
		break;
	case MODE_RANKING:
		RankingCamera();
		break;
	}
}

//====================================================================
//カメラの設定処理
//====================================================================
void SetCamera(int nIdx)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューポートの設定
	pDevice->SetViewport(&g_aCamera[nIdx].viewport);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_aCamera[nIdx].mtxProjection);

	if (nIdx == 4)
	{
		//プロジェクションマトリックスを作成
		D3DXMatrixPerspectiveFovLH(&g_aCamera[nIdx].mtxProjection,
			D3DXToRadian(45.0f),
			(float)g_aCamera[nIdx].viewport.Width / (float)g_aCamera[nIdx].viewport.Height,
			10.0f,
			10000.0f);
	}
	else
	{
		//プロジェクションマトリックスを作成
		D3DXMatrixPerspectiveFovLH(&g_aCamera[nIdx].mtxProjection,
			D3DXToRadian(45.0f),
			(float)g_aCamera[nIdx].viewport.Width / (float)g_aCamera[nIdx].viewport.Height,
			10.0f,
			1000.0f);
	}

#ifdef _DEBUG
	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_aCamera[nIdx].mtxProjection,
		D3DXToRadian(45.0f),
		(float)g_aCamera[nIdx].viewport.Width / (float)g_aCamera[nIdx].viewport.Height,
		10.0f,
		10000.0f);
#endif

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_aCamera[nIdx].mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_aCamera[nIdx].mtxView);

	//ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_aCamera[nIdx].mtxView,
		&g_aCamera[nIdx].posV,
		&g_aCamera[nIdx].posR,
		&g_aCamera[nIdx].vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_aCamera[nIdx].mtxView);

	//カメラを使ってる状態へ
	g_aCamera[nIdx].bUse = true;
}

//====================================================================
// カメラの追従処理
//====================================================================
void Camerafollow(int nCurrentCamera)
{
	//ポインタ情報の取得
	Player *pPlayer = GetPlayer();

	D3DXVECTOR3 posRDiff;
	D3DXVECTOR3 posVDiff;

	//目的の視点を設定(初期値)
	g_aCamera[nCurrentCamera].posVDest = D3DXVECTOR3(g_aCamera[nCurrentCamera].posRDest.x + (cosf(g_aCamera[nCurrentCamera].rot.z) * sinf(g_aCamera[nCurrentCamera].rot.y)) * -CAMERA_DISTANCE,
													pPlayer[nCurrentCamera].pos.y + g_aCamera[nCurrentCamera].fposVmoveY,
													g_aCamera[nCurrentCamera].posRDest.z + (cosf(g_aCamera[nCurrentCamera].rot.z) * cosf(g_aCamera[nCurrentCamera].rot.y)) * -CAMERA_DISTANCE);

	//目的の注視点を設定(初期値)
	g_aCamera[nCurrentCamera].posRDest = D3DXVECTOR3(pPlayer[nCurrentCamera].pos.x + sinf(pPlayer->rot.y + D3DX_PI) * 0.0f,
													pPlayer[nCurrentCamera].pos.y,
													pPlayer[nCurrentCamera].pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 0.0f);

	posRDiff = g_aCamera[nCurrentCamera].posRDest - g_aCamera[nCurrentCamera].posR;			//注視点の差分
	posVDiff = g_aCamera[nCurrentCamera].posVDest - g_aCamera[nCurrentCamera].posV;			//視点の差分

	g_aCamera[nCurrentCamera].posR += posRDiff * CAMERA_CORR_V;			//注視点を補正する

	g_aCamera[nCurrentCamera].posV += posVDiff * CAMERA_CORR_V;			//視点を補正する
}

//==============================
//ダメージを受けた時のカメラの動き
//==============================
void DownCamera(int nCntCamera)
{
	Player *pPlayer = GetPlayer();

	if (pPlayer[nCntCamera].State == PLAYER_HIT)
	{
		g_aCamera[nCntCamera].rot.x = DAMAGECAMERA_ROT_Y;
		pPlayer[nCntCamera].rot.x = DAMAGECAMERA_ROT_Y;
	}

	g_nCount[nCntCamera]++;

	if (pPlayer[nCntCamera].State == PLAYER_WAIT && g_aCamera[nCntCamera].rot.x <= 0.0f && g_nCount[nCntCamera] >= DAMAGECAMERA_TIME)
	{
		g_aCamera[nCntCamera].rot.x += DAMAGECAMERA_UPSPEED;
		pPlayer[nCntCamera].rot.x += DAMAGECAMERA_UPSPEED;
	}

	if (pPlayer[nCntCamera].State == PLAYER_NORMAL)
	{
		g_nCount[nCntCamera] = 0;
	}
}

//==============================
//死んだ時のカメラの動き
//==============================
void DeathCameraEnemy(int nCntCamera)
{
	//プレイヤー情報の取得
	Player *pPlayer = GetPlayer();
	ENEMY *pEnemy = GetEnemy();
	PlayNumberSelect NumberSelect = GetPlayNumberSelect();

	pPlayer += nCntCamera;

	float rotYDiff;

	if (pPlayer->nLife <= 0)
	{
		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++, pEnemy++)
		{
			if (pEnemy->bHit == true)
			{
				//敵の位置からプレイヤーの角度を求める
				rotYDiff = atan2f((pEnemy->pos.x - g_aCamera->posR.x), (pEnemy->pos.z - g_aCamera->posR.z));

				//カメラを敵の方向に向ける
				g_aCamera->rot.y = rotYDiff;
				
				//カメラが向いてる高さを敵の頭の方向へ向ける(固定値)
				g_aCamera->rot.x = 0.85f;

				//カメラの角度をプレイヤーの角度に代入する
				pPlayer->rot.y = g_aCamera->rot.y;
				pPlayer->rot.x = g_aCamera->rot.x;

				//プレイヤーが保持するライトの更新処理
				SetLight(pPlayer->LightIdx00, D3DLIGHT_SPOT, pPlayer->LightColor, D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 50.0f, pPlayer->pos.z), D3DXVECTOR3(sinf(Getrot(nCntCamera).y), sinf(Getrot(nCntCamera).x), cosf(Getrot(nCntCamera).y)), 350.0f, 1.0f);

				//死亡状態へ切り替える
				if (pEnemy->state == ENEMYSTATE_PATROL && pEnemy->StateCount <= 0)
				{//敵の状態が巡回モードに切り替わったら

					//プレイヤーの状態を死亡状態へ
					pPlayer->State = PLAYER_DEATH;

					//敵のヒット判定をfalseへ
					pEnemy->bHit = false;
				}
			}
		}
	}
}

//==============================
//死んだ時のカメラの動き
//==============================
void DeathCamera(int nCntCamera)
{
	//プレイヤー情報の取得
	Player *pPlayer = GetPlayer();

	pPlayer += nCntCamera;

	//上に向かせるまでのカウント
	g_nCount1[nCntCamera]++;

	//カメラを下に落とす
	if (g_aCamera->posV.y >= DEATHCAMERA_POS_Y)
	{//カメラの位置が宇内以上の時
		//カメラを落とす
		g_aCamera->posR.y -= DEATHCAMERA_SPEED;
		g_aCamera->posV.y -= DEATHCAMERA_SPEED;

		//カウントを初期化する
		g_Acc[nCntCamera] = 0;
	}
	else if (g_aCamera->rot.x <= DEATHCAMERA_ROTEND && g_nCount1[nCntCamera] >= DEATHCAMERA_TIME)
	{//カメラの向きが数値以下かつカウントより上の時
		//速さを徐々に増やす
		g_Acc[nCntCamera] += DEATHCAMERA_UPSPEED;

		//カメラを上に傾ける
		g_aCamera->rot.x += DEATHCAMERA_UPSPEED + g_Acc[nCntCamera];
		g_aCamera->rot.z += DEATHCAMERA_UPSPEED + g_Acc[nCntCamera];

		//カウントを初期化
		g_nCount1[nCntCamera] = 0;
	}
}

//==============================
//カメラの上下
//==============================
void StateYMove(int nCurrentCamera)
{
	Player *pPlayer = GetPlayer();

	float posYDiff;

	if (pPlayer[nCurrentCamera].MoveState == PLAYER_MOVESTATE_DASH)
	{
		//状態の遷移
		if (g_aCamera[nCurrentCamera].fposVmoveY >= CAMERA_HOMING_POSY + POS_MOVE_MAX)
		{
			g_aCamera[nCurrentCamera].State = CAMERASTATE_DOWN;
		}
		if (g_aCamera[nCurrentCamera].fposVmoveY <= CAMERA_HOMING_POSY + 0.5f)
		{
			g_aCamera[nCurrentCamera].State = CAMERASTATE_UP;
		}

		//カメラの上下移動
		if (g_aCamera[nCurrentCamera].State == CAMERASTATE_UP)
		{
			g_aCamera[nCurrentCamera].fposVmoveY += UP_DOWN_SPPED;
		}
		else if (g_aCamera[nCurrentCamera].State == CAMERASTATE_DOWN)
		{
			g_aCamera[nCurrentCamera].fposVmoveY -= UP_DOWN_SPPED;
		}
	}

	//カメラ位置が元の位置に戻るように
	else if (g_aCamera[nCurrentCamera].State == CAMERASTATE_NONE)
	{
		//元の位置と現在の位置の差を算出
		posYDiff = CAMERA_HOMING_POSY - g_aCamera[nCurrentCamera].fposVmoveY;

		g_aCamera[nCurrentCamera].fposVmoveY += posYDiff * YUAN_TO_CORRE;
	}
}

//=======================================
//観察用カメラ
//=======================================
void TpsCamera(void)
{
	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	Player *pPlayer = GetPlayer();

	//カメラ変更
	if (GetKeyboardTrigger(DIK_F4) == true)
	{
		g_nCurrentCamera++;			//使うカメラを変える

		g_nCurrentCamera %= PlayNumber.CurrentSelectNumber;			//カメラ上限まで来たら最初のカメラに戻る
	}

	for (int nCntCamera = g_nCurrentCamera; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_aCamera[nCntCamera].bUse == true && pPlayer[nCntCamera].bUse == true)
		{
			if (g_aCamera[g_nCurrentCamera].rot.x <= D3DX_PI * 0.5f && g_aCamera[g_nCurrentCamera].rot.x >= -(D3DX_PI * 0.5f))
			{//入力

				g_aCamera[g_nCurrentCamera].rotOld = g_aCamera[g_nCurrentCamera].rot;

				//キーボード
				if (GetKeyboardPress(DIK_I) == true)
				{
					g_aCamera[g_nCurrentCamera].rot.x += CAMERA_VR_SPEED;
				}
				if (GetKeyboardPress(DIK_K) == true)
				{
					g_aCamera[g_nCurrentCamera].rot.x -= CAMERA_VR_SPEED;
				}

				//右スティックの上下視点移動入力
				g_aCamera[g_nCurrentCamera].rot.x += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;

				if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
				{
					g_aCamera[g_nCurrentCamera].rot.x -= GetMouseMove().y * CAMERA_VR_SPEED;
				}
			}

			//右スティックの上下視点移動入力
			if (fabsf(g_aCamera[g_nCurrentCamera].rot.x) > fabsf(D3DX_PI * 0.5f))
			{//上限に達した時１フレーム前のrotにもどる
				g_aCamera[g_nCurrentCamera].rot = g_aCamera[g_nCurrentCamera].rotOld;
			}

			//キーボード
			if (GetKeyboardPress(DIK_J) == true)
			{
				g_aCamera[g_nCurrentCamera].rot.y -= CAMERA_VR_SPEED;

			}
			if (GetKeyboardPress(DIK_L) == true)
			{
				g_aCamera[g_nCurrentCamera].rot.y += CAMERA_VR_SPEED;
			}

			//右スティックの左右視点移動入力
			g_aCamera[g_nCurrentCamera].rot.y += GetGamepad_Stick_Right(0).x * CAMERA_VR_SPEED;

			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				g_aCamera[g_nCurrentCamera].rot.y += GetMouseMove().x * CAMERA_VR_SPEED;
			}

			//一周した時の向きの補正
			if (g_aCamera[g_nCurrentCamera].rot.y > D3DX_PI * 1.0f)
			{
				g_aCamera[g_nCurrentCamera].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aCamera[g_nCurrentCamera].rot.y < -D3DX_PI * 1.0f)
			{
				g_aCamera[g_nCurrentCamera].rot.y += D3DX_PI * 2.0f;
			}

			//キーボード
			if (GetKeyboardPress(DIK_LSHIFT) == true)
			{
				g_aCamera[g_nCurrentCamera].posV.y += CAMERA_SPEED;
				g_aCamera[g_nCurrentCamera].posR.y += CAMERA_SPEED;

			}
			if (GetKeyboardPress(DIK_LCONTROL) == true)
			{
				g_aCamera[g_nCurrentCamera].posV.y -= CAMERA_SPEED;
				g_aCamera[g_nCurrentCamera].posR.y -= CAMERA_SPEED;
			}

			//左トリガーを押し込むとカメラが下がる
			g_aCamera[g_nCurrentCamera].posV.y -= GetGamepad_Trigger_Left(0) * 4.0f;
			g_aCamera[g_nCurrentCamera].posR.y -= GetGamepad_Trigger_Left(0) * 4.0f;

			//右トリガーを押し込むとカメラが上がる
			g_aCamera[g_nCurrentCamera].posV.y += GetGamepad_Trigger_Right(0) * 4.0f;
			g_aCamera[g_nCurrentCamera].posR.y += GetGamepad_Trigger_Right(0) * 4.0f;


			//カメラの移動処理
			CameraMove(g_nCurrentCamera);

			//左スティックによる前後移動	
			g_aCamera[g_nCurrentCamera].posV.z += GetGamepad_Stick_Left(0).y * cosf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;
			g_aCamera[g_nCurrentCamera].posV.x += GetGamepad_Stick_Left(0).y * sinf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;

			//左スティックによる左右移動
			g_aCamera[g_nCurrentCamera].posV.x += GetGamepad_Stick_Left(0).x * cosf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;
			g_aCamera[g_nCurrentCamera].posV.z -= GetGamepad_Stick_Left(0).x * sinf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;

			//左スティックによる前後移動	
			g_aCamera[g_nCurrentCamera].posR.z += GetGamepad_Stick_Left(0).y * cosf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;
			g_aCamera[g_nCurrentCamera].posR.x += GetGamepad_Stick_Left(0).y * sinf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;

			//左スティックによる左右移動
			g_aCamera[g_nCurrentCamera].posR.x += GetGamepad_Stick_Left(0).x * cosf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;
			g_aCamera[g_nCurrentCamera].posR.z -= GetGamepad_Stick_Left(0).x * sinf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;

			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
				{

				}
				if (GetMousePress(PUSH_RIGHT) == true)
				{
					//視点の情報を出力する
					g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
				}
				if (GetMousePress(PUSH_LEFT) == true)
				{
					//視点の情報を出力する
					g_aCamera[g_nCurrentCamera].posV.x = g_aCamera[g_nCurrentCamera].posR.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.z = g_aCamera[g_nCurrentCamera].posR.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.y = g_aCamera[g_nCurrentCamera].posR.y + sinf(-g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
				}
			}
			else
			{//マウス操作がされていない場合
			 //注視点の情報を出力する
				g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
			}
		}
	}
}

//=======================================
//カメラの移動(8方向)
//=======================================
void CameraMove(int nCntCamera)
{
	//八方向移動
	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
		if (GetKeyboardPress(DIK_W) == true)
		{//左上移動
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//左下移動
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
		}
		else
		{//左移動
			//カメラ位置情報の更新
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された
		if (GetKeyboardPress(DIK_W) == true)
		{//右上移動
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//右下移動
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
		}
		else
		{//右移動
			//カメラ位置情報の更新
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//Wキーが押された
		//上移動
		g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y) * CAMERA_SPEED;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//Sキーが押された
		//下移動
		g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI) * CAMERA_SPEED;
	}
}

//=====================================================
//プレイヤーのカメラを動かす処理
//=====================================================
void PlayerCamera(void)
{
	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	Player *pPlayer = GetPlayer();
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();
	MODE mode = GetMode();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_aCamera[nCntCamera].bUse == true && pPlayer[nCntCamera].bUse == true)
		{
			if (pPlayer[nCntCamera].State == PLAYER_NORMAL)
			{//プレイヤー状態がノーマルの時
				if (g_aCamera[nCntCamera].rot.x <= D3DX_PI * 0.5f && g_aCamera[nCntCamera].rot.x >= -(D3DX_PI * 0.5f))
				{//入力

					g_aCamera[nCntCamera].rotOld = g_aCamera[nCntCamera].rot;

					//キーボード
					if (GetKeyboardPress(DIK_I) == true)
					{
						g_aCamera[nCntCamera].rot.x += CAMERA_VR_SPEED;

						//チュートリアル項目がカメラムーブの時
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
						{
							//カメラを移動したことにする
							CamMoveTCheck(nCntCamera, true);
						}
					}
					if (GetKeyboardPress(DIK_K) == true)
					{
						g_aCamera[nCntCamera].rot.x -= CAMERA_VR_SPEED;

						//チュートリアル項目がカメラムーブの時
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
						{
							//カメラを移動したことにする
							CamMoveTCheck(nCntCamera, true);
						}
					}

					//カメラの横移動をしたらチェックをつける処理
					if (g_aCamera[nCntCamera].rot.x > 0.1f || g_aCamera[nCntCamera].rot.x < -0.1f)
					{
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
						{
							CamMoveTCheck(nCntCamera, true);
						}
					}

					//カメラの縦移動をしたらチェックをつける処理
					if (g_aCamera[nCntCamera].rot.y > 0.1f || g_aCamera[nCntCamera].rot.y < -0.1f)
					{
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
						{
							CamMoveTCheck(nCntCamera, true);
						}
					}

					//右スティックの上下視点移動入力
					g_aCamera[nCntCamera].rot.x += GetGamepad_Stick_Right(nCntCamera).y * CAMERA_VR_SPEED;

					/*if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
					{
						g_aCamera[nCntCamera].rot.x -= GetMouseMove().y * CAMERA_VR_SPEED;
					}*/
				}

				//右スティックの上下視点移動入力
				if (fabsf(g_aCamera[nCntCamera].rot.x) > fabsf(D3DX_PI * 0.5f))
				{//上限に達した時１フレーム前のrotにもどる
					g_aCamera[nCntCamera].rot = g_aCamera[nCntCamera].rotOld;
				}

				//キーボード
				if (GetKeyboardPress(DIK_J) == true)
				{
					g_aCamera[nCntCamera].rot.y -= CAMERA_VR_SPEED;

				}
				if (GetKeyboardPress(DIK_L) == true)
				{
					g_aCamera[nCntCamera].rot.y += CAMERA_VR_SPEED;
				}

				//右スティックの左右視点移動入力
				g_aCamera[nCntCamera].rot.y += GetGamepad_Stick_Right(nCntCamera).x * CAMERA_VR_SPEED;

				/*if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
				{
					g_aCamera[nCntCamera].rot.y += GetMouseMove().x * CAMERA_VR_SPEED;
				}*/

				//一周した時の向きの補正
				if (g_aCamera[nCntCamera].rot.y > D3DX_PI * 1.0f)
				{
					g_aCamera[nCntCamera].rot.y -= D3DX_PI * 2.0f;
				}
				else if (g_aCamera[nCntCamera].rot.y < -D3DX_PI * 1.0f)
				{
					g_aCamera[nCntCamera].rot.y += D3DX_PI * 2.0f;
				}

				//移動状態によるカメラの動き----------
				StateYMove(nCntCamera);

				//モデル追従処理----------------------
				Camerafollow(nCntCamera);
			}
			else if (pPlayer[nCntCamera].State == PLAYER_HIT || pPlayer[nCntCamera].State == PLAYER_WAIT)
			{
				//ダウン状態によるカメラの動き
				DownCamera(nCntCamera);
			}
		}
		else if (pPlayer[nCntCamera].State == PLAYER_SMITE)
		{
			DeathCameraEnemy(nCntCamera);
		}
		else if (pPlayer[nCntCamera].State == PLAYER_DEATH)
		{
			DeathCamera(nCntCamera);
		}

		//注視点の情報を出力する
		g_aCamera[nCntCamera].posR.x = g_aCamera[nCntCamera].posV.x + sinf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot.x) * CAMERA_DISTANCE;
		g_aCamera[nCntCamera].posR.z = g_aCamera[nCntCamera].posV.z + cosf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot.x) * CAMERA_DISTANCE;
		g_aCamera[nCntCamera].posR.y = g_aCamera[nCntCamera].posV.y + sinf(g_aCamera[nCntCamera].rot.x) * CAMERA_DISTANCE;
	}
}

//==============================================================================================
//3D用(タイトル画面・人数選択画面・リザルト画面)
//==============================================================================================
//タイトル画面
void Titlecamera(void)
{
		g_aCamera[4].posV = D3DXVECTOR3(-60.0f, 0.0f, -100.0f);
		g_aCamera[4].posR = D3DXVECTOR3(490.0f, 500.0f, 1000.0);
		g_aCamera[4].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_aCamera[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[4].rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[4].rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		PrintDebugProc("%f , %f , %f", g_aCamera[4].posV.x, g_aCamera[4].posV.y, g_aCamera[4].posV.z);
}

//人数選択画面
void SelectNumberCamera(void)
{
	g_aCamera[4].posV = D3DXVECTOR3(0.0f, 50.0f,-60.0f);
	g_aCamera[4].posR = D3DXVECTOR3(0.0f, 0.0f, 5000.0);
	g_aCamera[4].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_aCamera[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCamera[4].rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCamera[4].rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//リザルト画面
void ResultCamera(void)
{
	if (GetClear() != 0)
	{
		g_aCamera[4].posV = D3DXVECTOR3(1010.0f, 20.0f, -353.0f);
		g_aCamera[4].posR = D3DXVECTOR3(-85.0f, 100.0f, 564.0);
	}
	else
	{
		g_aCamera[4].posV = D3DXVECTOR3(48.0f, 15.0f, 68.0f);
		g_aCamera[4].posR = D3DXVECTOR3(38.0f, 0.0f, 73.0f);
	}
}

//ランキング画面
void RankingCamera(void)
{
	switch (g_Rand_RankingCameraBG)
	{
	case 0:
		g_aCamera[4].posV = D3DXVECTOR3(-1953.70f, 35.0f, 1640.36f);
		g_aCamera[4].posR = D3DXVECTOR3(-2170.67f,35.0f,1748.42f);
		break;
	case 1:
		g_aCamera[4].posV = D3DXVECTOR3(473.15f, 35.0f, -69.61f);
		g_aCamera[4].posR = D3DXVECTOR3(300.0f, 35.0f, 556.61f);
		break;

	case 2:
		g_aCamera[4].posV = D3DXVECTOR3(-2200.96f, 35.0f, 1579.65f);
		g_aCamera[4].posR = D3DXVECTOR3(-1950.85f, 100.0f, 1420.71f);
		break;

	case 3:
		g_aCamera[4].posV = D3DXVECTOR3(-1029.69f, 35.0f, 1339.42f);
		g_aCamera[4].posR = D3DXVECTOR3(-929.04f, 35.0f, 1300.73f);
		break;
	}
}

//==========================================
//カメラの情報
//==========================================
Camera *GetCamera(void)
{
	return &g_aCamera[0];
}

//==========================================
//カメラの情報
//==========================================
Camera *GetCamera4(void)
{
	return &g_aCamera[4];
}

//==========================================
//カメラの向き情報
//==========================================
D3DXVECTOR3 Getrot(int nPlayer)
{
	return g_aCamera[nPlayer].rot;
}

//==========================================
//選択されているカメラ番号
//==========================================
int GetCurrentCamera(void)
{
	return g_nCurrentCamera;
}

//=========================================
//タイトルカメラ移動処理
//=========================================
void MoveTitleCamera(int nCnt)
{
	D3DXVECTOR3 PosVDiff;
	D3DXVECTOR3 PosRDiff;

	//加速度のカウント
	g_nCount[0]++;

	if (g_nCount[0] < 60)
	{
		g_Acc[0] += 0.004f;
		g_nCount[0] = 0;
	}

	if (g_aCamera[4].posV.x <= 200.0f)
	{
		PosVDiff = D3DXVECTOR3(200.0f, 200.0f, 150.0f) - g_aCamera[4].posV;

		PosRDiff = D3DXVECTOR3(-500.0f, 0.0f, 10000.0) - g_aCamera[4].posR;
		
		g_aCamera[4].posV += PosVDiff * CAM_MOVE_SPEED;

		g_aCamera[4].posR += PosRDiff * CAM_MOVE_SPEED;
	}

	if (nCnt <= 0)
	{//カメラの位置を移動用に変える処理
		//エンターを押したことにする
		bEnter = true;
	}

	else
	{//0以外の数値が入ってきた場合
		g_aCamera[4].posV.z += ((float)nCnt + g_Acc[0]);
	}
	
	PrintDebugProc("%f , %f , %f", g_aCamera[4].posV.x, g_aCamera[4].posV.y, g_aCamera[4].posV.z);
}
