//========================================================================================
//
// タイム処理[time.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "player.h"
#include "game.h"
#include "result.h"
#include "time.h"

//マクロ定義
#define NUM_PLACE (4)			//タイムの桁数
#define X_SIZE (25)				//タイムの横幅
#define Y_SIZE (25)				//タイムの縦幅
#define WIDE_SIZE (50)			//タイム同士の幅

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//頂点バッファのポインタ
D3DXVECTOR3 g_posTime[NUM_PLACE];					//タイムの位置
int g_nCountTime;									//タイムのカウント
int g_nTime;										//タイムの値
int g_nMaxTime;										//タイムの最大値
int g_aTexU[NUM_PLACE];								//テクスチャの読み込み位置
bool g_bTimeCount;									//時間をすすめるかどうか
float g_TimeWait;									//時間が終わった時の余韻
float g_TimeStart;									//時間が終わった時の表示

//====================================================================
//タイムの初期化処理
//====================================================================
void InitTime(void)
{
	int nCntTime;
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureTime);

	g_posTime[0] = D3DXVECTOR3(555.0f, 680.0f, 0.0f);	//10分の桁の位置設定
	g_posTime[1] = D3DXVECTOR3(605.0f, 680.0f, 0.0f);	//１分の桁の位置設定
	g_posTime[2] = D3DXVECTOR3(680.0f, 680.0f, 0.0f);	//10秒の桁の位置設定
	g_posTime[3] = D3DXVECTOR3(730.0f, 680.0f, 0.0f);	//１秒の桁の位置設定

	g_nCountTime = 0;

	g_bTimeCount = true;
	g_TimeWait = 0.0f;									//時間が終わった時の余韻
	g_TimeStart = 0.0f;									//時間が終わった時の表示


														//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE, g_posTime[nCntTime].y - Y_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE, g_posTime[nCntTime].y - Y_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE, g_posTime[nCntTime].y + Y_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE, g_posTime[nCntTime].y + Y_SIZE, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//時間の初期化処理
	g_aTexU[0] = 0;
	g_aTexU[1] = 4;
	g_aTexU[2] = 0;
	g_aTexU[3] = 0;

	g_nMaxTime = (g_aTexU[3] + g_aTexU[2] * 10 + g_aTexU[1] * 60 + g_aTexU[0] * 600) * 60;
	g_nTime = (g_aTexU[3] + g_aTexU[2] * 10 + g_aTexU[1] * 60 + g_aTexU[0] * 600);

	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}

//====================================================================
//タイムの終了処理
//====================================================================
void UninitTime(void)
{
	//テクスチャの破棄
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

////====================================================================
////タイムの更新処理(プラス)
////====================================================================
//void UpdateTime(void)
//{
//	MODE g_Mode = GetMode();	//ゲームモードを所得
//	int nCntTime;
//
//	g_nCountTime++;
//	if (g_Mode == MODE_GAME)
//	{
//		if (g_nCountTime >= 60)
//		{
//			g_nCountTime = 0;
//			if (g_aTexU[3] >= 9)
//			{
//				g_aTexU[3] = 0;
//				if (g_aTexU[2] >= 5)
//				{
//					g_aTexU[2] = 0;
//					if (g_aTexU[1] >= 9)
//					{
//						g_aTexU[1] = 0;
//						if (g_aTexU[0] >= 5)
//						{
//							g_aTexU[0] = 0;
//						}
//						else
//						{
//							g_aTexU[0]++;
//						}
//					}
//					else
//					{
//						g_aTexU[1]++;
//					}
//				}
//				else
//				{
//					g_aTexU[2]++;
//				}
//			}
//			else
//			{
//				g_aTexU[3]++;
//			}
//		}
//	}
//
//	VERTEX_2D*pVtx;	//頂点ポインタを所得
//
//					//頂点バッファをロックし、両店情報へのポインタを所得
//	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
//	{
//		switch (g_Mode)
//		{
//		case MODE_GAME:
//			g_posTime[0] = D3DXVECTOR3(1075.0f, 100.0f, 0.0f);
//
//			g_posTime[1] = D3DXVECTOR3(1125.0f, 100.0f, 0.0f);
//
//			g_posTime[2] = D3DXVECTOR3(1200.0f, 100.0f, 0.0f);
//
//			g_posTime[3] = D3DXVECTOR3(1250.0f, 100.0f, 0.0f);
//
//			//頂点座標の設定 
//			pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE, g_posTime[nCntTime].y - Y_SIZE, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE, g_posTime[nCntTime].y - Y_SIZE, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE, g_posTime[nCntTime].y + Y_SIZE, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE, g_posTime[nCntTime].y + Y_SIZE, 0.0f);
//
//			break;
//		case MODE_RESULT:
//			g_posTime[0] = D3DXVECTOR3(550.0f, 420.0f, 0.0f);
//
//			g_posTime[1] = D3DXVECTOR3(650.0f, 420.0f, 0.0f);
//
//			g_posTime[2] = D3DXVECTOR3(800.0f, 420.0f, 0.0f);
//
//			g_posTime[3] = D3DXVECTOR3(900.0f, 420.0f, 0.0f);
//
//			//頂点座標の設定 
//			pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE * 2, g_posTime[nCntTime].y - Y_SIZE * 2, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE * 2, g_posTime[nCntTime].y - Y_SIZE * 2, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE * 2, g_posTime[nCntTime].y + Y_SIZE * 2, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE * 2, g_posTime[nCntTime].y + Y_SIZE * 2, 0.0f);
//
//		}
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f + g_aTexU[nCntTime] * 0.1f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(0.1f + g_aTexU[nCntTime] * 0.1f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f + g_aTexU[nCntTime] * 0.1f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(0.1f + g_aTexU[nCntTime] * 0.1f, 1.0f);
//
//		pVtx += 4;	//頂点データのポインタを４つ分進める
//	}
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffTime->Unlock();
//}

//====================================================================
//タイムの更新処理(マイナス)
//====================================================================
void UpdateTime(void)
{
	if (g_bTimeCount == true)
	{//タイムのカウントダウンが可能な時
		int nCntTime;
		g_nCountTime++;	//カウントを増やす

		if (g_nCountTime >= 60)
		{//60フレームが経過した時
			g_nCountTime = 0;	//フレームをリセットする

			if (g_aTexU[3] <= 0)
			{//１秒の桁が０の時
				g_aTexU[3] = 9;	//１秒の桁を９にする

				if (g_aTexU[2] <= 0)
				{//10秒の桁が０の時
					g_aTexU[2] = 5;//10秒の桁を５にする

					if (g_aTexU[1] <= 0)
					{//１分の桁が０の時
						g_aTexU[1] = 9;

						if (g_aTexU[0] <= 0)
						{//10分の桁が０の時
							g_aTexU[0] = 5;
						}
						else
						{//10分の桁が０ではない時
							g_aTexU[0]--;	//１秒の桁を減少させる
						}
					}
					else
					{//１分の桁が０ではない時
						g_aTexU[1]--;	//１分の桁を減少させる
					}
				}
				else
				{//10秒の桁が０ではない時
					g_aTexU[2]--;	//10秒の桁を減少させる
				}
			}
			else
			{//１秒の桁が０ではない時
				g_aTexU[3]--;	//１秒の桁を減少させる
			}
		}

		g_nTime = (g_aTexU[3] + g_aTexU[2] * 10 + g_aTexU[1] * 100 + g_aTexU[0] * 1000);

		VERTEX_2D*pVtx;	//頂点ポインタを所得

		//頂点バッファをロックし、両店情報へのポインタを所得
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_aTexU[nCntTime] * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + g_aTexU[nCntTime] * 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_aTexU[nCntTime] * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + g_aTexU[nCntTime] * 0.1f, 1.0f);

			pVtx += 4;	//頂点データのポインタを４つ分進める
		}

		//頂点バッファをアンロックする
		g_pVtxBuffTime->Unlock();
	}

	if (g_aTexU[0] == 0 && g_aTexU[1] == 0 && g_aTexU[2] == 0 && g_aTexU[3] == 0)
	{//制限時間が０になったとき
		PlayerAllDown();
	}
}

//====================================================================
//タイムの描画処理
//====================================================================
void DrawTime(void)
{
	int nCntTime;
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);
	for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCntTime,							//プリミティブ(ポリゴン)数
			2);
	}
}

//====================================================================
//タイムの取得
//====================================================================
bool GetTime(void)
{
	return g_bTimeCount;
}