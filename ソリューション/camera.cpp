#include "main.h"
#include "camera.h"
#include "input.h"
#include "PlayNumberSelect.h"

#define CAMERA_DISTANCE (200.0f)	//視点と注視点の距離
#define MODEL_DISTANCE (10.0f)	//モデルと注視点の距離
#define CAMERA_SPEED (3.0f)	//カメラの移動スピード
#define CAMERA_VR_SPEED (0.03f)	//カメラの視点スピード
#define CAMERA_HOMING (0.1f)	//カメラの追従スピード

#define MAX_CAMERA		(8)

//グローバル変数
Camera g_aCamera[MAX_CAMERA];	//カメラの情報

//====================================================================
//カメラの初期化処理
//====================================================================
void InitCamera(void)
{
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		g_aCamera[nCntCamera].posV = D3DXVECTOR3(0.0f, 50.0f, 50.0f);
		g_aCamera[nCntCamera].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_aCamera[nCntCamera].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].rot2Old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aCamera[nCntCamera].bUse = false;
	}

	//1人用
	g_aCamera[0].viewport.X = 0;					// 描画する画面の左上X座標
	g_aCamera[0].viewport.Y = 0;					// 描画する画面の左上Y座標

	g_aCamera[0].viewport.Width = 1280;			// 画面の幅
	g_aCamera[0].viewport.Height = 720;			// 画面の高さ

	g_aCamera[0].viewport.MinZ = 0.0f;			// 
	g_aCamera[0].viewport.MaxZ = 1.0f;			// 


	//2人用(一人目)//
	g_aCamera[1].viewport.X = 0;				// 描画する画面の左上X座標
	g_aCamera[1].viewport.Y = 0;				// 描画する画面の左上Y座標

	g_aCamera[1].viewport.Width = 640;			// 画面の幅
	g_aCamera[1].viewport.Height = 720;			// 画面の高さ

	g_aCamera[1].viewport.MinZ = 0.0f;
	g_aCamera[1].viewport.MaxZ = 1.0f;

	//2人用(二人目)
	g_aCamera[2].viewport.X = 640;				// 描画する画面の左上X座標
	g_aCamera[2].viewport.Y = 0;					// 描画する画面の左上Y座標

	g_aCamera[2].viewport.Width = 640;			// 画面の幅
	g_aCamera[2].viewport.Height = 720;			// 画面の高さ

	g_aCamera[2].viewport.MinZ = 0.0f;
	g_aCamera[2].viewport.MaxZ = 1.0f;


	//3・4人用(1人目)//
	g_aCamera[3].viewport.X = 0;				// 描画する画面の左上X座標
	g_aCamera[3].viewport.Y = 0;				// 描画する画面の左上Y座標

	g_aCamera[3].viewport.Width = 640;			// 画面の幅
	g_aCamera[3].viewport.Height = 360;			// 画面の高さ

	g_aCamera[3].viewport.MinZ = 0.0f;
	g_aCamera[3].viewport.MaxZ = 1.0f;

	//3・4人用(2人目)
	g_aCamera[4].viewport.X = 640;				// 描画する画面の左上X座標
	g_aCamera[4].viewport.Y = 0;				// 描画する画面の左上Y座標

	g_aCamera[4].viewport.Width = 640;			// 画面の幅
	g_aCamera[4].viewport.Height = 360;			// 画面の高さ

	g_aCamera[4].viewport.MinZ = 0.0f;
	g_aCamera[4].viewport.MaxZ = 1.0f;

	//3・4人用(3人目)
	g_aCamera[5].viewport.X = 0;				// 描画する画面の左上X座標
	g_aCamera[5].viewport.Y = 360;					// 描画する画面の左上Y座標

	g_aCamera[5].viewport.Width = 640;			// 画面の幅
	g_aCamera[5].viewport.Height = 360;			// 画面の高さ

	g_aCamera[5].viewport.MinZ = 0.0f;
	g_aCamera[5].viewport.MaxZ = 1.0f;

	//3・4人用(4人目)
	g_aCamera[6].viewport.X = 640;				// 描画する画面の左上X座標
	g_aCamera[6].viewport.Y = 360;					// 描画する画面の左上Y座標

	g_aCamera[6].viewport.Width = 640;			// 画面の幅
	g_aCamera[6].viewport.Height = 360;			// 画面の高さ

	g_aCamera[6].viewport.MinZ = 0.0f;
	g_aCamera[6].viewport.MaxZ = 1.0f;
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
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_aCamera[nCntCamera].bUse == true)
		{
			if (g_aCamera[nCntCamera].rot2.y <= D3DX_PI * 0.5f && g_aCamera[nCntCamera].rot2.y >= -(D3DX_PI * 0.5f))
			{//入力
				g_aCamera[nCntCamera].rot2Old = g_aCamera[nCntCamera].rot2;

				//キーボード
				if (GetKeyboardPress(DIK_I) == true)
				{
					g_aCamera[nCntCamera].rot2.y += CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.z += CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.x += CAMERA_VR_SPEED;
				}
				if (GetKeyboardPress(DIK_K) == true)
				{
					g_aCamera[nCntCamera].rot2.y -= CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.z -= CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.x -= CAMERA_VR_SPEED;
				}

				//右スティックの上下視点移動入力
				g_aCamera[nCntCamera].rot2.y += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[nCntCamera].rot2.z += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[nCntCamera].rot2.x += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;

				if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
				{
					g_aCamera[nCntCamera].rot2.y -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.z -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.x -= GetMouseMove().y * CAMERA_VR_SPEED;
				}
			}

			//右スティックの上下視点移動入力
			if (fabsf(g_aCamera[nCntCamera].rot2.y) > fabsf(D3DX_PI * 0.5f))
			{//上限に達した時１フレーム前のrotにもどる
				g_aCamera[nCntCamera].rot2 = g_aCamera[nCntCamera].rot2Old;
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
			g_aCamera[nCntCamera].rot.y += GetGamepad_Stick_Right(0).x * CAMERA_VR_SPEED;

			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				g_aCamera[nCntCamera].rot.y += GetMouseMove().x * CAMERA_VR_SPEED;
			}

			//一周した時の向きの補正
			if (g_aCamera[nCntCamera].rot.y > D3DX_PI * 1.0f)
			{
				g_aCamera[nCntCamera].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aCamera[nCntCamera].rot.y < -D3DX_PI * 1.0f)
			{
				g_aCamera[nCntCamera].rot.y += D3DX_PI * 2.0f;
			}


			//キーボード
			if (GetKeyboardPress(DIK_LSHIFT) == true)
			{
				g_aCamera[nCntCamera].posV.y += CAMERA_SPEED;
				g_aCamera[nCntCamera].posR.y += CAMERA_SPEED;

			}
			if (GetKeyboardPress(DIK_LCONTROL) == true)
			{
				g_aCamera[nCntCamera].posV.y -= CAMERA_SPEED;
				g_aCamera[nCntCamera].posR.y -= CAMERA_SPEED;
			}

			//左トリガーを押し込むとカメラが下がる
			g_aCamera[nCntCamera].posV.y -= GetGamepad_Trigger_Left(0);
			g_aCamera[nCntCamera].posR.y -= GetGamepad_Trigger_Left(0);

			//右トリガーを押し込むとカメラが上がる
			g_aCamera[nCntCamera].posV.y += GetGamepad_Trigger_Right(0);
			g_aCamera[nCntCamera].posR.y += GetGamepad_Trigger_Right(0);

			//キーボード
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_aCamera[nCntCamera].posR.z += CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posR.x += CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);

				g_aCamera[nCntCamera].posV.z += CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posV.x += CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);

			}
			if (GetKeyboardPress(DIK_S) == true)
			{
				g_aCamera[nCntCamera].posR.z += -CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posR.x += -CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);

				g_aCamera[nCntCamera].posV.z += -CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posV.x += -CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_A) == true)
			{
				g_aCamera[nCntCamera].posR.x += -CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posR.z -= -CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);

				g_aCamera[nCntCamera].posV.x += -CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posV.z -= -CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_aCamera[nCntCamera].posR.x += CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posR.z -= CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);

				g_aCamera[nCntCamera].posV.x += CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posV.z -= CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);
			}

			////左スティックによる前後移動	
			//g_aCamera[nCntCamera].posV.z += GetGamepad_Stick_Left(0).y * cosf(g_aCamera[nCntCamera].rot.y);
			//g_aCamera[nCntCamera].posV.x += GetGamepad_Stick_Left(0).y * sinf(g_aCamera[nCntCamera].rot.y);

			////左スティックによる左右移動
			//g_aCamera[nCntCamera].posV.x += GetGamepad_Stick_Left(0).x * cosf(g_aCamera[nCntCamera].rot.y);
			//g_aCamera[nCntCamera].posV.z -= GetGamepad_Stick_Left(0).x * sinf(g_aCamera[nCntCamera].rot.y);

			////左スティックによる前後移動	
			//g_aCamera[nCntCamera].posR.z += GetGamepad_Stick_Left(0).y * cosf(g_aCamera[nCntCamera].rot.y);
			//g_aCamera[nCntCamera].posR.x += GetGamepad_Stick_Left(0).y * sinf(g_aCamera[nCntCamera].rot.y);

			////左スティックによる左右移動
			//g_aCamera[nCntCamera].posR.x += GetGamepad_Stick_Left(0).x * cosf(g_aCamera[nCntCamera].rot.y);
			//g_aCamera[nCntCamera].posR.z -= GetGamepad_Stick_Left(0).x * sinf(g_aCamera[nCntCamera].rot.y);

			//モデル追従処理----------------------
			//Model * pModel = GetModel();
			//g_aCamera[nCntCamera].posRDest.x = g_aCamera[nCntCamera].posV.x + sinf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.z) * CAMERA_DISTANCE;
			//g_aCamera[nCntCamera].posRDest.z = g_aCamera[nCntCamera].posV.z + cosf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.x) * CAMERA_DISTANCE;
			//g_aCamera[nCntCamera].posRDest.y = g_aCamera[nCntCamera].posV.y + sinf(g_aCamera[nCntCamera].rot2.y) * CAMERA_DISTANCE;

			//g_aCamera[nCntCamera].posVDest.x = pModel->pos.x + sinf(pModel->rot.y) * MODEL_DISTANCE + sinf(g_aCamera[nCntCamera].rot.y) * -cosf(g_aCamera[nCntCamera].rot2.z) * CAMERA_DISTANCE;
			//g_aCamera[nCntCamera].posVDest.z = pModel->pos.z + cosf(pModel->rot.y) * MODEL_DISTANCE + cosf(g_aCamera[nCntCamera].rot.y) * -cosf(g_aCamera[nCntCamera].rot2.x) * CAMERA_DISTANCE;
			//g_aCamera[nCntCamera].posVDest.y = pModel->pos.y + sinf(-g_aCamera[nCntCamera].rot2.y) * CAMERA_DISTANCE;
			//
			//g_aCamera[nCntCamera].posR += (g_aCamera[nCntCamera].posRDest - g_aCamera[nCntCamera].posR) * CAMERA_HOMING;
			//g_aCamera[nCntCamera].posV += (g_aCamera[nCntCamera].posVDest - g_aCamera[nCntCamera].posV) * CAMERA_HOMING;

			//------------------------------------

			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
				{

				}
				if (GetMousePress(PUSH_RIGHT) == true)
				{
					//視点の情報を出力する
					g_aCamera[nCntCamera].posR.x = g_aCamera[nCntCamera].posV.x + sinf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[nCntCamera].posR.z = g_aCamera[nCntCamera].posV.z + cosf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[nCntCamera].posR.y = g_aCamera[nCntCamera].posV.y + sinf(g_aCamera[nCntCamera].rot2.y) * CAMERA_DISTANCE;
				}
				if (GetMousePress(PUSH_LEFT) == true)
				{
					//視点の情報を出力する
					g_aCamera[nCntCamera].posV.x = g_aCamera[nCntCamera].posR.x + sinf(g_aCamera[nCntCamera].rot.y) * -cosf(g_aCamera[nCntCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[nCntCamera].posV.z = g_aCamera[nCntCamera].posR.z + cosf(g_aCamera[nCntCamera].rot.y) * -cosf(g_aCamera[nCntCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[nCntCamera].posV.y = g_aCamera[nCntCamera].posR.y + sinf(-g_aCamera[nCntCamera].rot2.y) * CAMERA_DISTANCE;
				}
			}
			else
			{//マウス操作がされていない場合
					//注視点の情報を出力する
				g_aCamera[nCntCamera].posR.x = g_aCamera[nCntCamera].posV.x + sinf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.z) * CAMERA_DISTANCE;
				g_aCamera[nCntCamera].posR.z = g_aCamera[nCntCamera].posV.z + cosf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.x) * CAMERA_DISTANCE;
				g_aCamera[nCntCamera].posR.y = g_aCamera[nCntCamera].posV.y + sinf(g_aCamera[nCntCamera].rot2.y) * CAMERA_DISTANCE;
			}
		}
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

D3DXVECTOR3 Getrot(void)
{
	return g_aCamera[0].rot;
}
