#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "PlayNumberSelect.h"

#define CAMERA_DISTANCE			(5.0f)		//視点と注視点の距離
#define MODEL_DISTANCE			(10.0f)		//モデルと注視点の距離
#define CAMERA_SPEED			(2.5f)		//カメラの移動スピード
#define CAMERA_VR_SPEED			(0.045f)		//カメラの視点スピード
#define CAMERA_HOMING			(0.1f)		//カメラの追従スピード
#define CAMERA_HOMING_POSY		(35.0f)		//カメラの追従の位置(Y座標)
#define CAMERA_CORR_V			(0.7f)		//カメラ視点の補正
#define CAMERA_CORR_R			(0.8f)		//カメラ注視点の補正
#define CAMERA_LENGTH_R			(0.0f)		//プレイヤーとカメラ注視点との距離

#define MAX_CAMERA				(4)		//カメラの最大数

//プロトタイプ宣言
void TpsCamera(void);			//観察用カメラ
void PlayerFpsCamera(void);		//プレイヤーの視点カメラ
void Camerafollow(int nCurrentCamera);		//追従カメラ
void CameraMove(int nCurrentCamera);		//カメラ移動


//グローバル変数
Camera g_aCamera[MAX_CAMERA];	//カメラの情報

int g_nCurrentCamera;			//選択されているカメラの番号
int g_nSaveCamera;				//カメラ番号保存用
bool g_bTpsCamera;				//観察用のカメラを使うかどうか

//====================================================================
//カメラの初期化処理
//====================================================================
void InitCamera(void)
{
	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		g_aCamera[nCntCamera].posV = D3DXVECTOR3(0.0f, 35.0f, 50.0f);
		g_aCamera[nCntCamera].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_aCamera[nCntCamera].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].rot2Old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aCamera[nCntCamera].bUse = false;
	}

	g_nCurrentCamera = 0;			//選択されているカメラの番号を最初のカメラへ
	g_bTpsCamera = false;			//観察用カメラを使っていない状態へ

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
		g_aCamera[2].viewport.Y = 360;					// 描画する画面の左上Y座標
		g_aCamera[2].viewport.Width = 640;			// 画面の幅
		g_aCamera[2].viewport.Height = 360;			// 画面の高さ
		g_aCamera[2].viewport.MinZ = 0.0f;
		g_aCamera[2].viewport.MaxZ = 1.0f;
		//3・4人用(4人目)
		g_aCamera[3].viewport.X = 640;				// 描画する画面の左上X座標
		g_aCamera[3].viewport.Y = 360;					// 描画する画面の左上Y座標
		g_aCamera[3].viewport.Width = 640;			// 画面の幅
		g_aCamera[3].viewport.Height = 360;			// 画面の高さ
		g_aCamera[3].viewport.MinZ = 0.0f;
		g_aCamera[3].viewport.MaxZ = 1.0f;
		break;
	}
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

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F5) == true)
	{//キーが押された場合
		g_bTpsCamera = g_bTpsCamera ? false : true;			//観察用モードに変更
	}
#endif

	if (g_bTpsCamera == false)
	{
		//プレイヤー視点カメラ
		PlayerFpsCamera();
	}
	else
	{
		//観察用モード
		TpsCamera();
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

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_aCamera[nIdx].mtxProjection,
		D3DXToRadian(45.0f),
		(float)g_aCamera[nIdx].viewport.Width / (float)g_aCamera[nIdx].viewport.Height,
		10.0f,
		10000.0f);

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

//=======================================
// プレイヤー視点カメラ
//=======================================
void PlayerFpsCamera(void)
{
	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//カメラ変更
	if (GetKeyboardTrigger(DIK_F4) == true)
	{
		g_nCurrentCamera++;			//使うカメラを変える

		g_nCurrentCamera %= PlayNumber.CurrentSelectNumber;			//カメラ上限まで来たら最初のカメラに戻る
	}

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_aCamera[nCntCamera].bUse == true)
		{
			if (g_aCamera[g_nCurrentCamera].rot2.y <= D3DX_PI * 0.5f && g_aCamera[g_nCurrentCamera].rot2.y >= -(D3DX_PI * 0.5f))
			{//入力

				g_aCamera[g_nCurrentCamera].rot2Old = g_aCamera[g_nCurrentCamera].rot2;

				//キーボード
				if (GetKeyboardPress(DIK_I) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y += CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z += CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x += CAMERA_VR_SPEED;
				}
				if (GetKeyboardPress(DIK_K) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y -= CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z -= CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x -= CAMERA_VR_SPEED;
				}

				//右スティックの上下視点移動入力
				g_aCamera[g_nCurrentCamera].rot2.y += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[g_nCurrentCamera].rot2.z += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[g_nCurrentCamera].rot2.x += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;

				if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x -= GetMouseMove().y * CAMERA_VR_SPEED;
				}
			}

			//右スティックの上下視点移動入力
			if (fabsf(g_aCamera[g_nCurrentCamera].rot2.y) > fabsf(D3DX_PI * 0.5f))
			{//上限に達した時１フレーム前のrotにもどる
				g_aCamera[g_nCurrentCamera].rot2 = g_aCamera[g_nCurrentCamera].rot2Old;
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

			//モデル追従処理----------------------
			Camerafollow(g_nCurrentCamera);

			//キーボード
			if (GetKeyboardPress(DIK_T) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.z += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.x += CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.z += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.x += CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

			}
			if (GetKeyboardPress(DIK_G) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.z += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.x += -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.z += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.x += -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_F) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.x += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.z -= -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.x += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.z -= -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_H) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.x += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.z -= CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.x += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.z -= CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}

			//マウス
			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
				{

				}
				if (GetMousePress(PUSH_RIGHT) == true)
				{
					//視点の情報を出力する
					g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
				}
				if (GetMousePress(PUSH_LEFT) == true)
				{
					//視点の情報を出力する
					g_aCamera[g_nCurrentCamera].posV.x = g_aCamera[g_nCurrentCamera].posR.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.z = g_aCamera[g_nCurrentCamera].posR.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.y = g_aCamera[g_nCurrentCamera].posR.y + sinf(-g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
				}
			}
			else
			{//マウス操作がされていない場合
			 //注視点の情報を出力する
				g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
			}
		}
	}
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
													pPlayer->pos.y + CAMERA_HOMING_POSY,
													g_aCamera[nCurrentCamera].posRDest.z + (cosf(g_aCamera[nCurrentCamera].rot.z) * cosf(g_aCamera[nCurrentCamera].rot.y)) * -CAMERA_DISTANCE);

	//目的の注視点を設定(初期値)
	g_aCamera[nCurrentCamera].posRDest = D3DXVECTOR3(pPlayer->pos.x + sinf(pPlayer->rot.y + D3DX_PI) * 0.0f,
													pPlayer->pos.y,
													pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 0.0f);

	posRDiff = g_aCamera[nCurrentCamera].posRDest - g_aCamera[nCurrentCamera].posR;			//注視点の差分
	posVDiff = g_aCamera[nCurrentCamera].posVDest - g_aCamera[nCurrentCamera].posV;			//視点の差分

	g_aCamera[nCurrentCamera].posR += posRDiff * CAMERA_CORR_V;			//注視点を補正する

	g_aCamera[nCurrentCamera].posV += posVDiff * CAMERA_CORR_V;			//視点を補正する
}

//=======================================
//観察用カメラ
//=======================================
void TpsCamera(void)
{
	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//カメラ変更
	if (GetKeyboardTrigger(DIK_F4) == true)
	{
		g_nCurrentCamera++;			//使うカメラを変える

		g_nCurrentCamera %= PlayNumber.CurrentSelectNumber;			//カメラ上限まで来たら最初のカメラに戻る
	}

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_aCamera[nCntCamera].bUse == true)
		{
			if (g_aCamera[g_nCurrentCamera].rot2.y <= D3DX_PI * 0.5f && g_aCamera[g_nCurrentCamera].rot2.y >= -(D3DX_PI * 0.5f))
			{//入力

				g_aCamera[g_nCurrentCamera].rot2Old = g_aCamera[g_nCurrentCamera].rot2;

				//キーボード
				if (GetKeyboardPress(DIK_I) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y += CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z += CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x += CAMERA_VR_SPEED;
				}
				if (GetKeyboardPress(DIK_K) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y -= CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z -= CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x -= CAMERA_VR_SPEED;
				}

				//右スティックの上下視点移動入力
				g_aCamera[g_nCurrentCamera].rot2.y += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[g_nCurrentCamera].rot2.z += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[g_nCurrentCamera].rot2.x += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;

				if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x -= GetMouseMove().y * CAMERA_VR_SPEED;
				}
			}

			//右スティックの上下視点移動入力
			if (fabsf(g_aCamera[g_nCurrentCamera].rot2.y) > fabsf(D3DX_PI * 0.5f))
			{//上限に達した時１フレーム前のrotにもどる
				g_aCamera[g_nCurrentCamera].rot2 = g_aCamera[g_nCurrentCamera].rot2Old;
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
			g_aCamera[g_nCurrentCamera].posV.y -= GetGamepad_Trigger_Left(0);
			g_aCamera[g_nCurrentCamera].posR.y -= GetGamepad_Trigger_Left(0);

			//右トリガーを押し込むとカメラが上がる
			g_aCamera[g_nCurrentCamera].posV.y += GetGamepad_Trigger_Right(0);
			g_aCamera[g_nCurrentCamera].posR.y += GetGamepad_Trigger_Right(0);


			//キーボード
			CameraMove(g_nCurrentCamera);

			if (GetKeyboardPress(DIK_T) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.z += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.x += CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.z += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.x += CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

			}
			if (GetKeyboardPress(DIK_G) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.z += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.x += -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.z += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.x += -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_F) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.x += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.z -= -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.x += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.z -= -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_H) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.x += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.z -= CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.x += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.z -= CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}

			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
				{

				}
				if (GetMousePress(PUSH_RIGHT) == true)
				{
					//視点の情報を出力する
					g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
				}
				if (GetMousePress(PUSH_LEFT) == true)
				{
					//視点の情報を出力する
					g_aCamera[g_nCurrentCamera].posV.x = g_aCamera[g_nCurrentCamera].posR.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.z = g_aCamera[g_nCurrentCamera].posR.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.y = g_aCamera[g_nCurrentCamera].posR.y + sinf(-g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
				}
			}
			else
			{//マウス操作がされていない場合
			 //注視点の情報を出力する
				g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
			}
		}
	}
}

//--------------------------------------------------------------------
//カメラの移動
//--------------------------------------------------------------------
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

D3DXVECTOR3 Getrot(void)
{
	return g_aCamera[0].rot;
}
