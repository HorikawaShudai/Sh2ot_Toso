//========================================================================================
//
// ライト処理[light.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "light.h"
#include "game.h"

#define MAX_LIGHT (256)	//使用するライトの数

//グローバル変数
D3DLIGHT9 g_light[MAX_LIGHT];	//ライトの情報
bool g_bUse[MAX_LIGHT];			//ライトを使用しているかどうか
int g_Light_LightIdx[MAX_LIGHT];//ライトの使用番号

////====================================================================
////ライトの初期化処理
////====================================================================
//void InitLight(void)
//{
//	//デバイスの所得
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	D3DXVECTOR3 vecDir[MAX_LIGHT];	//設定用方向ベクトル
//
//	//ライトの情報をクリアする
//	ZeroMemory(&g_light, sizeof(D3DLIGHT9));
//
//	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
//	{
//		//ライトの種類を設定
//		g_light[nCntlight].Type = D3DLIGHT_DIRECTIONAL;
//
//		//ライトの拡散光を設定
//		g_light[nCntlight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//ライトの方向を設定
//		switch (nCntlight)
//		{
//		case 0:
//			vecDir[nCntlight] = D3DXVECTOR3(0.2f, -0.8f, -0.5f);
//			break;
//		case 1:
//			vecDir[nCntlight] = D3DXVECTOR3(-0.5f, -0.8f, -0.5f);
//			break;
//		case 2:
//			vecDir[nCntlight] = D3DXVECTOR3(0.0f, -0.8f, 0.6f);
//			break;
//		}
//		D3DXVec3Normalize(&vecDir[nCntlight], &vecDir[nCntlight]);	//ベクトルを正規化する
//		g_light[nCntlight].Direction = vecDir[nCntlight];
//
//		//ライトを設定する
//		pDevice->SetLight(nCntlight, &g_light[nCntlight]);
//
//		//ライトを有効にする
//		pDevice->LightEnable(nCntlight, TRUE);
//	}
//}

//====================================================================
//ライトの初期化処理
//====================================================================
void InitLight(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir[MAX_LIGHT];	//設定用方向ベクトル

	//ライトの情報をクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		//各種変数の初期化
		g_light[nCntlight].Type = D3DLIGHT_DIRECTIONAL;						//ライトの種類を設定
		g_light[nCntlight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//ライトの拡散光を設定
		g_light[nCntlight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//ライトの反射色を設定
		g_light[nCntlight].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//ライトの環境光を設定
		g_light[nCntlight].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//ライトの位置を設定
		vecDir[nCntlight] = D3DXVECTOR3(0.2f, -0.8f, -0.5f);				//ライトの方向を設定
		g_light[nCntlight].Range = 1000.0f;									//ライトの範囲を設定
		g_light[nCntlight].Falloff = 1.0f;									//ライトの円の外側から内側までの照明の減少を設定
		g_light[nCntlight].Attenuation0 = 0.0f;								//ライトの減衰０を設定
		g_light[nCntlight].Attenuation1 = 0.01f;							//ライトの減衰１を設定
		g_light[nCntlight].Attenuation2 = 0.0f;								//ライトの減衰２を設定
		g_light[nCntlight].Theta = 0.0f;									//ライトの内側の円を設定
		g_light[nCntlight].Phi = 1.0f;										//ライトの外側の円を設定
		g_Light_LightIdx[nCntlight] = -1;									//ライトの使用番号の設定

		D3DXVec3Normalize(&vecDir[nCntlight], &vecDir[nCntlight]);	//ベクトルを正規化する
		g_light[nCntlight].Direction = vecDir[nCntlight];

		//ライトを設定する
		pDevice->SetLight(nCntlight, &g_light[nCntlight]);

		//ライトを無効にする
		pDevice->LightEnable(nCntlight, FALSE);
		g_bUse[nCntlight] = false;
	}

	//デフォルトのライトを設置する
	for (int nCntlight = 0; nCntlight < 3; nCntlight++)
	{
		g_Light_LightIdx[nCntlight] = SetIndexLight();		//ライトの使用番号を指定する

		if ((GetMode() == MODE_GAME) ||
			(GetMode() == MODE_TUTORIAL) ||
			(GetMode() == MODE_RESULT && GetClear() == false))
		{
			//ライトの方向を設定
			switch (nCntlight)
			{
			case 0:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 1:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 2:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
				break;
			}
		}
		else if (GetMode() == MODE_NUMBERSELECT)
		{
			//ライトの方向を設定
			switch (nCntlight)
			{
			case 0:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 1:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 2:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
				break;
			}
		}
		else
		{
			//ライトの方向を設定
			switch (nCntlight)
			{
			case 0:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 1:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 2:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
				break;
			}
		}
	}
}

//====================================================================
//ライトの終了処理
//====================================================================
void UninitLight(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		if (g_bUse[nCntlight] == true)
		{
			//ライトを無効にする
			pDevice->LightEnable(nCntlight, FALSE);
			g_bUse[nCntlight] = false;
		}
	}
}

//====================================================================
//ライトの更新処理
//====================================================================
void UpdateLight(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

#ifdef _DEBUG
	//ビジョンがオンの時、デフォルトのライトを明るくする
	for (int nCntlight = 0; nCntlight < 3; nCntlight++)
	{
		if (GetNightVersion() == false)
		{
			if ((GetMode() == MODE_GAME) ||
				(GetMode() == MODE_TUTORIAL) ||
				(GetMode() == MODE_RESULT && GetClear() == false))
			{
				//ライトの方向を設定
				switch (nCntlight)
				{
				case 0:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f,1.0f);
					break;
				case 1:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
					break;
				case 2:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
					break;
				}
			}
			else if (GetMode() == MODE_NUMBERSELECT)
			{
				//ライトの方向を設定
				switch (nCntlight)
				{
				case 0:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
					break;
				case 1:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
					break;
				case 2:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
					break;
				}
			}
			else
			{
				//ライトの方向を設定
				switch (nCntlight)
				{
				case 0:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
					break;
				case 1:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
					break;
				case 2:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
					break;
				}
			}
		}
		else
		{
			//ライトの方向を設定
			switch (nCntlight)
			{
			case 0:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 1:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 2:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
				break;
			}
		}
	}
#endif

	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		if (g_bUse[nCntlight] == true)
		{
			//ライトを設定する
			pDevice->SetLight(nCntlight, &g_light[nCntlight]);
		}
	}
}

//====================================================================
//ライトの番号設定処理
//====================================================================
int SetIndexLight(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nLightIndex = -1;
	int nCntlight;

	for (nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		if (g_bUse[nCntlight] == false)
		{
			nLightIndex = nCntlight;

			//ライトを有効にする
			pDevice->LightEnable(nCntlight, TRUE);
			g_bUse[nCntlight] = true;
			break;
		}
	}

	return nLightIndex;
}

//====================================================================
//ライトの情報設定処理
//====================================================================
void SetLight(int nIdxLight, D3DLIGHTTYPE nType, D3DXCOLOR Diffuse, D3DXVECTOR3 pos, D3DXVECTOR3 nVecDir, float nRange,float nPhi)
{
	D3DXVECTOR3 vecDir;	//設定用方向ベクトル

	g_light[nIdxLight].Type = nType;			//ライトの種類を設定
	g_light[nIdxLight].Diffuse = Diffuse;		//ライトの拡散光を設定
	g_light[nIdxLight].Position = pos;			//ライトの位置を設定
	vecDir = nVecDir;							//ライトの方向を設定
	g_light[nIdxLight].Range = nRange;			//ライトの範囲を設定
	g_light[nIdxLight].Phi = nPhi;				//ライトの外側の円を設定

	D3DXVec3Normalize(&vecDir, &vecDir);	//ベクトルを正規化する
	g_light[nIdxLight].Direction = vecDir;
}