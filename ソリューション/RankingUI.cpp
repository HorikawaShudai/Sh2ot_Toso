#include "main.h"
#include "RankingUI.h"
#include "numberUI.h"
#include "player.h"
#include "PlayNumberSelect.h"
#include "game.h"
#include "time.h"

//マクロ定義
#define NUM_SSUI		(5)	//GAMEUIの種類数

#define POS_RANKING_BG_X		(640.0f)	//「」のX座標の位置
#define POS_RANKING_BG_Y		(360.0f)	//「」のY座標の位置
#define SIZE_RANKING_BG_X		(640.0f)	//「」の幅
#define SIZE_RANKING_BG_Y		(360.0f)	//「」の高さ

#define POS_SCORE_BG_X			(860.0f)	//「」のX座標の位置
#define POS_SCORE_BG_Y			(495.0f)	//「」のY座標の位置
#define SIZE_SCORE_BG_X			(270.0f)		//「」の幅
#define SIZE_SCORE_BG_Y			(400.0f)		//「」の高さ

#define POS_PERFECT_BG_X		(720.0f)	//「」のX座標の位置
#define POS_PERFECT_BG_Y		(420.0f)	//「」のY座標の位置
#define SIZE_PERFECT_BG_X		(125.0f)	//「」の幅
#define SIZE_PERFECT_BG_Y		(250.0f)		//「」の高さ

#define POS_ALLPERFECT_BG_X		(300.0f)	//「」のX座標の位置
#define POS_ALLPERFECT_BG_Y		(200.0f)	//「」のY座標の位置
#define SIZE_ALLPERFECT_BG_X	(200.0f)	//「」の幅
#define SIZE_ALLPERFECT_BG_Y	(100.0f)	//「」の高さ

#define POS_EXIT_BG_X			(300.0f)	//「」のX座標の位置
#define POS_EXIT_BG_Y			(450.0f)	//「」のY座標の位置
#define SIZE_EXIT_BG_X			(200.0f)	//「」の幅
#define SIZE_EXIT_BG_Y			(100.0f)	//「」の高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureRankingUI[NUM_SSUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingUI = NULL;		//頂点バッファへのポインタ
bool bUseRankingUI[NUM_SSUI];		//頂点バッファへのポインタ
bool g_bStageClear_Ranking;

//====================================================================
//タイトル画面の初期化処理
//====================================================================
void InitRankingUI(void)
{
	int nCntBG;
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの所得
	int *pTime = GetTime();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\Osumi00.png",
		&g_apTextureRankingUI[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\pepepepe02.png",
		&g_apTextureRankingUI[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\RankUi.png",
		&g_apTextureRankingUI[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\pepepepe01.png",
		&g_apTextureRankingUI[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\pepepepe03.png",
		&g_apTextureRankingUI[4]);

	//UIの表示設定
	bUseRankingUI[0] = true;
	bUseRankingUI[1] = true;
	bUseRankingUI[2] = true;

	if (GetClear() == 1)
	{//全員クリア
		bUseRankingUI[3] = true;
		bUseRankingUI[4] = true;
		//タイムを呼び出す
		for (int nCntTime = 0; nCntTime < 4; nCntTime++, pTime++)
		{
			switch (nCntTime)
			{
			case 0:
			case 1:
				SetNumberUI(D3DXVECTOR3(170.0f + nCntTime * 70.0f, 220.0f, 0.0f), 50.0f, 50.0f, *pTime, 0);
				break;
			case 2:
			case 3:
				SetNumberUI(D3DXVECTOR3(220.0f + nCntTime * 70.0f, 220.0f, 0.0f), 50.0f, 50.0f, *pTime, 0);
				break;
			}

			SetNumberUI(D3DXVECTOR3(230.0f, 450.0f, 0.0f), 40.0f, 40.0f, GetPlayNumberSelect().CurrentSelectNumber, 0);
			SetNumberUI(D3DXVECTOR3(360.0f, 480.0f, 0.0f), 40.0f, 40.0f, GetExitCount(), 0);
		}
	}
	else if (GetClear() == 2 || GetClear() == 3)
	{//一人でもクリア
		bUseRankingUI[3] = false;
		bUseRankingUI[4] = true;

		SetNumberUI(D3DXVECTOR3(230.0f, 450.0f, 0.0f), 40.0f, 40.0f, GetPlayNumberSelect().CurrentSelectNumber, 0);
		SetNumberUI(D3DXVECTOR3(360.0f, 480.0f, 0.0f), 40.0f, 40.0f, GetExitCount(), 0);
	}
	else
	{
		bUseRankingUI[3] = false;
		bUseRankingUI[4] = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingUI,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffRankingUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_RANKING_BG_X - SIZE_RANKING_BG_X, POS_RANKING_BG_Y - SIZE_RANKING_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_RANKING_BG_X + SIZE_RANKING_BG_X, POS_RANKING_BG_Y - SIZE_RANKING_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_RANKING_BG_X - SIZE_RANKING_BG_X, POS_RANKING_BG_Y + SIZE_RANKING_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_RANKING_BG_X + SIZE_RANKING_BG_X, POS_RANKING_BG_Y + SIZE_RANKING_BG_Y, 0.0f);
			break;

		case 1:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_SCORE_BG_X - SIZE_SCORE_BG_X, POS_SCORE_BG_Y - SIZE_SCORE_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_SCORE_BG_X + SIZE_SCORE_BG_X, POS_SCORE_BG_Y - SIZE_SCORE_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_SCORE_BG_X - SIZE_SCORE_BG_X, POS_SCORE_BG_Y + SIZE_SCORE_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_SCORE_BG_X + SIZE_SCORE_BG_X, POS_SCORE_BG_Y + SIZE_SCORE_BG_Y, 0.0f);
			break;

		case 2:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_PERFECT_BG_X - SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y - SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PERFECT_BG_X + SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y - SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PERFECT_BG_X - SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y + SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PERFECT_BG_X + SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y + SIZE_PERFECT_BG_Y, 0.0f);
			break;

		case 3:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X - SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y - SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X + SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y - SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X - SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y + SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X + SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y + SIZE_ALLPERFECT_BG_Y, 0.0f);
			break;

		case 4:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_EXIT_BG_X - SIZE_EXIT_BG_X, POS_EXIT_BG_Y - SIZE_EXIT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_EXIT_BG_X + SIZE_EXIT_BG_X, POS_EXIT_BG_Y - SIZE_EXIT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_EXIT_BG_X - SIZE_EXIT_BG_X, POS_EXIT_BG_Y + SIZE_EXIT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_EXIT_BG_X + SIZE_EXIT_BG_X, POS_EXIT_BG_Y + SIZE_EXIT_BG_Y, 0.0f);
			break;
		}

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankingUI->Unlock();
}

//====================================================================
//タイトルの終了処理
//====================================================================
void UninitRankingUI(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの破棄
		if (g_apTextureRankingUI[nCntBG] != NULL)
		{
			g_apTextureRankingUI[nCntBG]->Release();
			g_apTextureRankingUI[nCntBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRankingUI != NULL)
	{
		g_pVtxBuffRankingUI->Release();
		g_pVtxBuffRankingUI = NULL;
	}
}

//====================================================================
//タイトル画面の更新処理
//====================================================================
void UpdateRankingUI(void)
{

}

//====================================================================
//タイトル画面の描画処理
//====================================================================
void DrawRankingUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankingUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureRankingUI[nCntBG]);

		if (bUseRankingUI[nCntBG] == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntBG,						//プリミティブ(ポリゴン)数
				2);
		}
	}
}
//====================================================================
//ランキングUIの設定処理
//====================================================================
void SetRankingUI(RANKING SetClear, bool Clear)
{

}