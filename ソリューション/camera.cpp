#include "main.h"
#include "camera.h"
#include "input.h"

#define CAMERA_DISTANCE (200.0f)	//視点と注視点の距離
#define MODEL_DISTANCE (10.0f)	//モデルと注視点の距離
#define CAMERA_SPEED (3.0f)	//カメラの移動スピード
#define CAMERA_VR_SPEED (0.03f)	//カメラの視点スピード
#define CAMERA_HOMING (0.1f)	//カメラの追従スピード

//グローバル変数
Camera g_camera;	//カメラの情報

//====================================================================
//カメラの初期化処理
//====================================================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 50.0f, 50.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rot2Old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	if (g_camera.rot2.y <= D3DX_PI * 0.5f && g_camera.rot2.y >= -(D3DX_PI * 0.5f))
	{//入力
		g_camera.rot2Old = g_camera.rot2;

		//キーボード
		if (GetKeyboardPress(DIK_I) == true)
		{
			g_camera.rot2.y += CAMERA_VR_SPEED;
			g_camera.rot2.z += CAMERA_VR_SPEED;
			g_camera.rot2.x += CAMERA_VR_SPEED;
		}
		if (GetKeyboardPress(DIK_K) == true)
		{
			g_camera.rot2.y -= CAMERA_VR_SPEED;
			g_camera.rot2.z -= CAMERA_VR_SPEED;
			g_camera.rot2.x -= CAMERA_VR_SPEED;
		}

		//右スティックの上下視点移動入力
		g_camera.rot2.y += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
		g_camera.rot2.z += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
		g_camera.rot2.x += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;

		if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
		{
			g_camera.rot2.y -= GetMouseMove().y * CAMERA_VR_SPEED;
			g_camera.rot2.z -= GetMouseMove().y * CAMERA_VR_SPEED;
			g_camera.rot2.x -= GetMouseMove().y * CAMERA_VR_SPEED;
		}
	}

	//右スティックの上下視点移動入力
	if (fabsf(g_camera.rot2.y) > fabsf(D3DX_PI * 0.5f))
	{//上限に達した時１フレーム前のrotにもどる
		g_camera.rot2 = g_camera.rot2Old;
	}

	//キーボード
	if (GetKeyboardPress(DIK_J) == true)
	{
		g_camera.rot.y -= CAMERA_VR_SPEED;

	}
	if (GetKeyboardPress(DIK_L) == true)
	{
		g_camera.rot.y += CAMERA_VR_SPEED;
	}

	//右スティックの左右視点移動入力
	g_camera.rot.y += GetGamepad_Stick_Right(0).x * CAMERA_VR_SPEED;

	if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
	{
		g_camera.rot.y += GetMouseMove().x * CAMERA_VR_SPEED;
	}

	//一周した時の向きの補正
	if (g_camera.rot.y > D3DX_PI * 1.0f)
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.y < -D3DX_PI * 1.0f)
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}


	//キーボード
	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_camera.posV.y += CAMERA_SPEED;
		g_camera.posR.y += CAMERA_SPEED;

	}
	if (GetKeyboardPress(DIK_LCONTROL) == true)
	{
		g_camera.posV.y -= CAMERA_SPEED;
		g_camera.posR.y -= CAMERA_SPEED;
	}

	//左トリガーを押し込むとカメラが下がる
	g_camera.posV.y -= GetGamepad_Trigger_Left(0);
	g_camera.posR.y -= GetGamepad_Trigger_Left(0);

	//右トリガーを押し込むとカメラが上がる
	g_camera.posV.y += GetGamepad_Trigger_Right(0);
	g_camera.posR.y += GetGamepad_Trigger_Right(0);

	//キーボード
	if (GetKeyboardPress(DIK_W) == true)
	{
		g_camera.posR.z += CAMERA_SPEED * cosf(g_camera.rot.y);
		g_camera.posR.x += CAMERA_SPEED * sinf(g_camera.rot.y);

		g_camera.posV.z += CAMERA_SPEED * cosf(g_camera.rot.y);
		g_camera.posV.x += CAMERA_SPEED * sinf(g_camera.rot.y);

	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_camera.posR.z += -CAMERA_SPEED * cosf(g_camera.rot.y);
		g_camera.posR.x += -CAMERA_SPEED * sinf(g_camera.rot.y);

		g_camera.posV.z += -CAMERA_SPEED * cosf(g_camera.rot.y);
		g_camera.posV.x += -CAMERA_SPEED * sinf(g_camera.rot.y);
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_camera.posR.x += -CAMERA_SPEED * cosf(g_camera.rot.y);
		g_camera.posR.z -= -CAMERA_SPEED * sinf(g_camera.rot.y);

		g_camera.posV.x += -CAMERA_SPEED * cosf(g_camera.rot.y);
		g_camera.posV.z -= -CAMERA_SPEED * sinf(g_camera.rot.y);
	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_camera.posR.x += CAMERA_SPEED * cosf(g_camera.rot.y);
		g_camera.posR.z -= CAMERA_SPEED * sinf(g_camera.rot.y);

		g_camera.posV.x += CAMERA_SPEED * cosf(g_camera.rot.y);
		g_camera.posV.z -= CAMERA_SPEED * sinf(g_camera.rot.y);
	}

	//左スティックによる前後移動	
	g_camera.posV.z += GetGamepad_Stick_Left(0).y * cosf(g_camera.rot.y);
	g_camera.posV.x += GetGamepad_Stick_Left(0).y * sinf(g_camera.rot.y);

	//左スティックによる左右移動
	g_camera.posV.x += GetGamepad_Stick_Left(0).x * cosf(g_camera.rot.y);
	g_camera.posV.z -= GetGamepad_Stick_Left(0).x * sinf(g_camera.rot.y);

	//左スティックによる前後移動	
	g_camera.posR.z += GetGamepad_Stick_Left(0).y * cosf(g_camera.rot.y);
	g_camera.posR.x += GetGamepad_Stick_Left(0).y * sinf(g_camera.rot.y);

	//左スティックによる左右移動
	g_camera.posR.x += GetGamepad_Stick_Left(0).x * cosf(g_camera.rot.y);
	g_camera.posR.z -= GetGamepad_Stick_Left(0).x * sinf(g_camera.rot.y);

	//モデル追従処理----------------------
	//Model * pModel = GetModel();
	//g_camera.posRDest.x = g_camera.posV.x + sinf(g_camera.rot.y) * cosf(g_camera.rot2.z) * CAMERA_DISTANCE;
	//g_camera.posRDest.z = g_camera.posV.z + cosf(g_camera.rot.y) * cosf(g_camera.rot2.x) * CAMERA_DISTANCE;
	//g_camera.posRDest.y = g_camera.posV.y + sinf(g_camera.rot2.y) * CAMERA_DISTANCE;

	//g_camera.posVDest.x = pModel->pos.x + sinf(pModel->rot.y) * MODEL_DISTANCE + sinf(g_camera.rot.y) * -cosf(g_camera.rot2.z) * CAMERA_DISTANCE;
	//g_camera.posVDest.z = pModel->pos.z + cosf(pModel->rot.y) * MODEL_DISTANCE + cosf(g_camera.rot.y) * -cosf(g_camera.rot2.x) * CAMERA_DISTANCE;
	//g_camera.posVDest.y = pModel->pos.y + sinf(-g_camera.rot2.y) * CAMERA_DISTANCE;
	//
	//g_camera.posR += (g_camera.posRDest - g_camera.posR) * CAMERA_HOMING;
	//g_camera.posV += (g_camera.posVDest - g_camera.posV) * CAMERA_HOMING;

	//------------------------------------

	if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
	{
		if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
		{

		}
		if (GetMousePress(PUSH_RIGHT) == true)
		{
			//視点の情報を出力する
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * cosf(g_camera.rot2.z) * CAMERA_DISTANCE;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * cosf(g_camera.rot2.x) * CAMERA_DISTANCE;
			g_camera.posR.y = g_camera.posV.y + sinf(g_camera.rot2.y) * CAMERA_DISTANCE;
		}
		if (GetMousePress(PUSH_LEFT) == true)
		{
			//視点の情報を出力する
			g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -cosf(g_camera.rot2.z) * CAMERA_DISTANCE;
			g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -cosf(g_camera.rot2.x) * CAMERA_DISTANCE;
			g_camera.posV.y = g_camera.posR.y + sinf(-g_camera.rot2.y) * CAMERA_DISTANCE;
		}
	}
	else
	{//マウス操作がされていない場合
			//注視点の情報を出力する
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * cosf(g_camera.rot2.z) * CAMERA_DISTANCE;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * cosf(g_camera.rot2.x) * CAMERA_DISTANCE;
		g_camera.posR.y = g_camera.posV.y + sinf(g_camera.rot2.y) * CAMERA_DISTANCE;
	}
}

//====================================================================
//カメラの設定処理
//====================================================================
void SetCamera(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}
