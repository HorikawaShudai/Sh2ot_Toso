#include "main.h"
#include "RankingUI.h"
#include "numberUI.h"
#include "game.h"

//マクロ定義
#define NUM_SSUI		(4)	//GAMEUIの種類数

#define POS_RANKING_BG_X		(200.0f)	//「」のX座標の位置
#define POS_RANKING_BG_Y		(400.0f)	//「」のY座標の位置
#define SIZE_RANKING_BG_X		(20.0f)		//「」の幅
#define SIZE_RANKING_BG_Y		(20.0f)		//「」の高さ

#define POS_SCORE_BG_X			(400.0f)	//「」のX座標の位置
#define POS_SCORE_BG_Y			(400.0f)	//「」のY座標の位置
#define SIZE_SCORE_BG_X			(20.0f)		//「」の幅
#define SIZE_SCORE_BG_Y			(20.0f)		//「」の高さ

#define POS_PERFECT_BG_X		(1040.0f)	//「」のX座標の位置
#define POS_PERFECT_BG_Y		(100.0f)	//「」のY座標の位置
#define SIZE_PERFECT_BG_X		(150.0f)	//「」の幅
#define SIZE_PERFECT_BG_Y		(75.0f)		//「」の高さ

#define POS_ALLPERFECT_BG_X		(200.0f)	//「」のX座標の位置
#define POS_ALLPERFECT_BG_Y		(120.0f)	//「」のY座標の位置
#define SIZE_ALLPERFECT_BG_X	(200.0f)	//「」の幅
#define SIZE_ALLPERFECT_BG_Y	(100.0f)	//「」の高さ

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

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RankingBG.png",
		&g_apTextureRankingUI[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ranking_Score.png",
		&g_apTextureRankingUI[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RankingPerfect.png",
		&g_apTextureRankingUI[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RankingAllPerfect.png",
		&g_apTextureRankingUI[3]);

	//UIの表示設定
	bUseRankingUI[0] = true;
	bUseRankingUI[1] = true;
	bUseRankingUI[2] = true;
	bUseRankingUI[3] = true;

	//数字を呼び出す
	SetNumberUI(D3DXVECTOR3(600.0f, 600.0f, 0.0f), 50.0f, 50.0f, 1, 0);

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
	g_bStageClear_Ranking = Clear;

	bUseRankingUI[1] = true;
	switch (SetClear)
	{
	case RANKING_NORMAL:

		bUseRankingUI[2] = false;
		bUseRankingUI[3] = false;

		break;

	case RANKING_PERFECT:

		bUseRankingUI[2] = true;
		bUseRankingUI[3] = false;

		break;

	case RANKING_ALLPERFECT:

		bUseRankingUI[2] = true;
		bUseRankingUI[3] = true;

		break;
	}
}