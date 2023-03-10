//============================
//
//スコア処理(score.cpp)
//Author:早川 友貴
//
//============================
#include "score.h"  
#include "player.h"  
#include "playNumberSelect.h"  

//マクロ定義
#define NUM_PLACE		(3)			 //スコアの桁数
#define MAX_SCORE		(128)		//スコアの最大数
#define SCORE_INTERVAL  (40.0f)		//スコアの桁間の幅を決める
#define SCORE_POS_X1	(500.0f)	//スコアのX位置
#define SCORE_POS_Y1	(20.0f)		//スコアのY位置
#define SCORE_POS_X2	(1150.0f)	//スコアのX位置
#define SCORE_POS_Y2	(400.0f)	//スコアのY位置
#define SCORE_WIDTH		(20.0f)		//スコアの幅
#define SCORE_HEIGHT	(20.0f)		//スコアの高さ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL; //頂点バッファへのポインタ
SCORE g_aScore[NUM_PLAYER];

//=============================
//  スコアの初期化
//=============================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\time.png",
		&g_pTextureScore);

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		switch (nCntPlayer)
		{
		case 0:
			//スコアの情報を初期化
			g_aScore[nCntPlayer].posScore = D3DXVECTOR3(SCORE_POS_X1, SCORE_POS_Y1, 0.0f);  //位置を初期化
			g_aScore[nCntPlayer].nScore = 0;		//スコアの値
			g_aScore[nCntPlayer].nWindth = SCORE_WIDTH;
			g_aScore[nCntPlayer].nHeight = SCORE_HEIGHT;
			break;
		case 1:
			//スコアの情報を初期化
			g_aScore[nCntPlayer].posScore = D3DXVECTOR3(SCORE_POS_X2, SCORE_POS_Y1, 0.0f);  //位置を初期化
			g_aScore[nCntPlayer].nScore = 0;		//スコアの値
			g_aScore[nCntPlayer].nWindth = SCORE_WIDTH;
			g_aScore[nCntPlayer].nHeight = SCORE_HEIGHT;
			break;
		case 2:
			//スコアの情報を初期化
			g_aScore[nCntPlayer].posScore = D3DXVECTOR3(SCORE_POS_X1, SCORE_POS_Y2, 0.0f);  //位置を初期化
			g_aScore[nCntPlayer].nScore = 0;		//スコアの値
			g_aScore[nCntPlayer].nWindth = SCORE_WIDTH;
			g_aScore[nCntPlayer].nHeight = SCORE_HEIGHT;
			break;
		case 3:
			//スコアの情報を初期化
			g_aScore[nCntPlayer].posScore = D3DXVECTOR3(SCORE_POS_X2, SCORE_POS_Y2, 0.0f);  //位置を初期化
			g_aScore[nCntPlayer].nScore = 0;		//スコアの値
			g_aScore[nCntPlayer].nWindth = SCORE_WIDTH;
			g_aScore[nCntPlayer].nHeight = SCORE_HEIGHT;
			break;
		}
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE * NUM_PLAYER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aScore[nCntPlayer].posScore.x - g_aScore[nCntPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nCntPlayer].posScore.y - g_aScore[nCntPlayer].nHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aScore[nCntPlayer].posScore.x + g_aScore[nCntPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nCntPlayer].posScore.y - g_aScore[nCntPlayer].nHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aScore[nCntPlayer].posScore.x - g_aScore[nCntPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nCntPlayer].posScore.y + g_aScore[nCntPlayer].nHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aScore[nCntPlayer].posScore.x + g_aScore[nCntPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nCntPlayer].posScore.y + g_aScore[nCntPlayer].nHeight, 0.0f);

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

			pVtx += 4;		//頂点データのポインタを4つ分進める
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//=====================
//スコアの終了処理
//=====================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//スコアの更新処理
void UpdateScore(void)
{

}

//スコアの描画処理
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < NUM_PLACE * PlayNumber.CurrentSelectNumber; nCntScore++)
	{//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//===============================
//スコアの設定処理
//===============================
void SetScore(int nScore, int nPlayer)
{
	LPDIRECT3DDEVICE9 pDevice;
	int aTexU[NUM_PLACE * NUM_PLAYER];  //各桁の数字を格納
	int nCntScore;
	g_aScore[nPlayer].nScore = nScore;

	//デバイスの取得
	pDevice = GetDevice();

	aTexU[0] = g_aScore[nPlayer].nScore % 1000 / 100;
	aTexU[1] = g_aScore[nPlayer].nScore % 100 / 10;
	aTexU[2] = g_aScore[nPlayer].nScore % 10 / 1;

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nPlayer * NUM_PLACE * 4;

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//===============================
//スコアの加算
//===============================
void AddScore(int nType, int nPlayer)
{
	LPDIRECT3DDEVICE9 pDevice;
	int aTexU[NUM_PLACE * NUM_PLAYER];  //各桁の数字を格納
	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	//加点をする処理
	switch (nType)
	{
	case 0:

		g_aScore[nPlayer].nScore += 1;

		break;
	}

	//スコアの上限
	if (g_aScore[nPlayer].nScore >= 999)
	{
		g_aScore[nPlayer].nScore = 999;
	}

	aTexU[0] = g_aScore[nPlayer].nScore % 1000 / 100;
	aTexU[1] = g_aScore[nPlayer].nScore % 100 / 10;
	aTexU[2] = g_aScore[nPlayer].nScore % 10 / 1;

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nPlayer * NUM_PLACE * 4;

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

}

//================================
//スコアを受け取る
//===============================
int GetScore(int nPlayer)
{
	return g_aScore[nPlayer].nScore;
}

//==================================
//スコアの設定
//==================================
void SetPosScore(D3DXVECTOR3 pos, float nWINDTH, float nHeight,int nPlayer)
{
	int nCntScore;

	g_aScore[nPlayer].posScore = pos;

	g_aScore[nPlayer].nWindth = nWINDTH;

	g_aScore[nPlayer].nHeight = nHeight;

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aScore[nPlayer].posScore.x - g_aScore[nPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nPlayer].posScore.y - g_aScore[nPlayer].nHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aScore[nPlayer].posScore.x + g_aScore[nPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nPlayer].posScore.y - g_aScore[nPlayer].nHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aScore[nPlayer].posScore.x - g_aScore[nPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nPlayer].posScore.y + g_aScore[nPlayer].nHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aScore[nPlayer].posScore.x + g_aScore[nPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nPlayer].posScore.y + g_aScore[nPlayer].nHeight, 0.0f);

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

