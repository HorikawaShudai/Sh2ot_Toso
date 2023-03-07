#include "main.h"
#include "RankingNumber.h"
#include "input.h"
#include "fade.h"
#include <stdio.h>

//マクロ定義
#define MAX_RANK (5)			//ランクの数
#define NUM_PLACE (4)			//ランキングの桁数

#define X_POS_GAME (850.0f)			//ゲーム画面の時のランキングのX座標
#define Y_POS_GAME (220.0f)			//ゲーム画面の時のランキングのY座標
#define X_SIZE_GAME (40.0f)			//ゲーム画面の時のランキングの横幅
#define Y_SIZE_GAME (40.0f)			//ゲーム画面の時のランキングの縦幅
#define WIDE_SIZE_GAME_X (60.0f)	//ゲーム画面の時のランキング同士の幅
#define WIDE_SIZE_GAME_Y (100.0f)	//ゲーム画面の時のランキング同士の高さ
#define WIDE_SIZE_X (30.0f)	//分と秒の間の幅

//ランキング構造体
typedef struct
{
	D3DXVECTOR3 pos;
	int nScore;
}RanKingNumber;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRanKingNumber = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanKingNumber = NULL;		//頂点バッファのポインタ
RanKingNumber g_RanKingNumber[MAX_RANK];					//ランキングの位置

RANKING_TYPE RankingType;
int g_HighScore = -1;
int g_RankingCounter;
float g_RankingColorR = 1.0f;
float g_RankingColorG = 0.0f;
float g_RankingAR = 0.05f;
float g_RankingAG = -0.05f;
//====================================================================
//ランキングの初期化処理
//====================================================================
void InitRanKingNumber(void)
{
	int aTexU[NUM_PLACE];
	int nCntMax;
	int nCntNum;
	g_RankingCounter = 1200;

	RankingType = RANKING_TYPE_ESCAPE;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number00.png",
		&g_pTextureRanKingNumber);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanKingNumber,
		NULL);

	g_RankingColorR = 0.5f;
	g_RankingColorG = 0.5f;
	g_RankingAR = 0.025f;
	g_RankingAG = -0.025f;

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffRanKingNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMax = 0; nCntMax < MAX_RANK; nCntMax++)
	{
		aTexU[0] = g_RanKingNumber[nCntMax].nScore % 10000 / 1000;
		aTexU[1] = g_RanKingNumber[nCntMax].nScore % 1000 / 100;
		aTexU[2] = g_RanKingNumber[nCntMax].nScore % 100 / 10;
		aTexU[3] = g_RanKingNumber[nCntMax].nScore % 10 / 1;

		for (nCntNum = 0; nCntNum < NUM_PLACE; nCntNum++)
		{
			g_RanKingNumber[nCntMax].pos = D3DXVECTOR3(X_POS_GAME + nCntNum * WIDE_SIZE_GAME_X, Y_POS_GAME + nCntMax * WIDE_SIZE_GAME_Y, 0.0f);

			switch (nCntNum)
			{
			case 0:
			case 1:
				//頂点座標の設定 
				pVtx[0].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x - X_SIZE_GAME, g_RanKingNumber[nCntMax].pos.y - Y_SIZE_GAME, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x + X_SIZE_GAME, g_RanKingNumber[nCntMax].pos.y - Y_SIZE_GAME, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x - X_SIZE_GAME, g_RanKingNumber[nCntMax].pos.y + Y_SIZE_GAME, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x + X_SIZE_GAME, g_RanKingNumber[nCntMax].pos.y + Y_SIZE_GAME, 0.0f);
				break;
			case 2:
			case 3:
				//頂点座標の設定 
				pVtx[0].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x - X_SIZE_GAME + WIDE_SIZE_X, g_RanKingNumber[nCntMax].pos.y - Y_SIZE_GAME, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x + X_SIZE_GAME + WIDE_SIZE_X, g_RanKingNumber[nCntMax].pos.y - Y_SIZE_GAME, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x - X_SIZE_GAME + WIDE_SIZE_X, g_RanKingNumber[nCntMax].pos.y + Y_SIZE_GAME, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x + X_SIZE_GAME + WIDE_SIZE_X, g_RanKingNumber[nCntMax].pos.y + Y_SIZE_GAME, 0.0f);
				break;
			}

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
			pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntNum] * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntNum] * 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntNum] * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntNum] * 0.1f, 1.0f);

			pVtx += 4;	//頂点データのポインタを４つ分進める
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRanKingNumber->Unlock();
}

//====================================================================
//ランキングの終了処理
//====================================================================
void UninitRanKingNumber(void)
{
	//テクスチャの破棄
	if (g_pTextureRanKingNumber != NULL)
	{
		g_pTextureRanKingNumber->Release();
		g_pTextureRanKingNumber = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRanKingNumber != NULL)
	{
		g_pVtxBuffRanKingNumber->Release();
		g_pVtxBuffRanKingNumber = NULL;
	}
	g_HighScore = -1;
}

//====================================================================
//ランキングの更新処理
//====================================================================
void UpdateRanKingNumber(void)
{
	int nCount1;
	int nCntNum;
	MODE g_Mode = GetMode();	//ゲームモードを所得

	if (g_RankingCounter != -1)
	{
		g_RankingCounter--;
	}

	g_RankingColorR += g_RankingAR;
	g_RankingColorG += g_RankingAG;

	if (g_RankingColorR > 1.0f)
	{
		g_RankingColorR = 1.0f;
		g_RankingAR *= -1;
	}
	else if (g_RankingColorR < 0.0f)
	{
		g_RankingColorR = 0.0f;
		g_RankingAR *= -1;
	}

	if (g_RankingColorG > 1.0f)
	{
		g_RankingColorG = 1.0f;
		g_RankingAG *= -1;
	}
	else if (g_RankingColorG < 0.0f)
	{
		g_RankingColorG = 0.0f;
		g_RankingAG *= -1;
	}

	//仮
	if (GetFade() == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_START, 0) == true || GetGamepadTrigger(BUTTON_A, 0) == true || GetGamepadTrigger(BUTTON_B, 0) == true || g_RankingCounter == 0)
		{//ENTERキーが押された

			g_RankingCounter = -1;

			//データをセーブする
			SaveData();

			//フェードの状態を変える
			SetFade(MODE_TITLE);
		}
	}

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffRanKingNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount1 = 0; nCount1 < MAX_RANK; nCount1++)
	{
		for (nCntNum = 0; nCntNum < NUM_PLACE; nCntNum++)
		{
			if (g_HighScore == g_RanKingNumber[nCount1].nScore)
			{//ランキング更新時色を変更する
			 //頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, g_RankingColorR, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, g_RankingColorR, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, g_RankingColorR, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, g_RankingColorR, 1.0f);

				//ランキングの値が同じの時前回の上の順位の色を元に戻す
				if (nCount1 != 0)
				{
					pVtx -= 4 * NUM_PLACE;	//頂点データのポインタを４つ分進める

											//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					pVtx += 4 * NUM_PLACE;	//頂点データのポインタを４つ分進める
				}
			}
			pVtx += 4;	//頂点データのポインタを４つ分進める
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRanKingNumber->Unlock();
}

//====================================================================
//ランキングの描画処理
//====================================================================
void DrawRanKingNumber(void)
{
	int nCntMax;
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanKingNumber, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanKingNumber);
	for (nCntMax = 0; nCntMax < NUM_PLACE * MAX_RANK; nCntMax++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCntMax,							//プリミティブ(ポリゴン)数
			2);
	}
}

//====================================================================
//ランキングの設定処理
//====================================================================
void SetRanking(int nRanKing)
{
	int nCount1;
	int nCount2;
	int nData;

	switch (RankingType)
	{
	case RANKING_TYPE_ESCAPE:
		if (nRanKing > g_RanKingNumber[MAX_RANK - 1].nScore)
		{
			g_RanKingNumber[MAX_RANK - 1].nScore = nRanKing;
			g_HighScore = nRanKing;

			for (nCount1 = 0; nCount1 < MAX_RANK; nCount1++)
			{
				for (nCount2 = nCount1; nCount2 < MAX_RANK; nCount2++)
				{
					if (g_RanKingNumber[nCount1].nScore < g_RanKingNumber[nCount2].nScore)
					{
						nData = g_RanKingNumber[nCount1].nScore;
						g_RanKingNumber[nCount1].nScore = g_RanKingNumber[nCount2].nScore;
						g_RanKingNumber[nCount2].nScore = nData;
					}
				}
			}
		}
		break;
	case RANKING_TYPE_VILLAIN:
		if (nRanKing < g_RanKingNumber[MAX_RANK - 1].nScore)
		{
			g_RanKingNumber[MAX_RANK - 1].nScore = nRanKing;
			g_HighScore = nRanKing;

			for (nCount1 = 0; nCount1 < MAX_RANK; nCount1++)
			{
				for (nCount2 = nCount1; nCount2 < MAX_RANK; nCount2++)
				{
					if (g_RanKingNumber[nCount1].nScore > g_RanKingNumber[nCount2].nScore)
					{
						nData = g_RanKingNumber[nCount1].nScore;
						g_RanKingNumber[nCount1].nScore = g_RanKingNumber[nCount2].nScore;
						g_RanKingNumber[nCount2].nScore = nData;
					}
				}
			}
		}
		break;
	}
}

//====================================================================
//ランキング画面のリセット処理
//====================================================================
void ResetRanKing(void)
{
	int nCntNum;

	for (nCntNum = 0; nCntNum < MAX_RANK; nCntNum++)
	{
		g_RanKingNumber[nCntNum].nScore = 0;
	}
}

//==================================================
//セーブ処理
//==================================================
void SaveData(void)
{
	int nCount;
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("", "w");

	switch (RankingType)
	{
	case RANKING_TYPE_VILLAIN:
		//ファイルを開く
		pFile = fopen("data\\TEXT\\Scoreranking.txt", "w");
		break;
	case RANKING_TYPE_ESCAPE:
		//ファイルを開く
		pFile = fopen("data\\TEXT\\Timeranking.txt", "w");
		break;
	}

	if (pFile != NULL)
	{//ファイルを開けた場合

		for (nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fprintf(pFile, "%d\n", g_RanKingNumber[nCount].nScore);		 //&(アンパサンド)を付けない！
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}

//==================================================
//ロード処理
//==================================================
void LoadData(void)
{
	int nCount;
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("", "r");

	switch (RankingType)
	{
	case RANKING_TYPE_VILLAIN:
		//ファイルを開く
		pFile = fopen("data\\TEXT\\Scoreranking.txt", "r");
		break;
	case RANKING_TYPE_ESCAPE:
		//ファイルを開く
		pFile = fopen("data\\TEXT\\Timeranking.txt", "r");
		break;
	}

	if (pFile != NULL)
	{//ファイルを開けた場合
	 //ファイルから文字を読み込む

		for (nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fscanf(pFile, "%d", &g_RanKingNumber[nCount].nScore);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}

//==================================================
//ランキングスタート処理
//==================================================
void StartRanKing(void)
{
	g_HighScore = -1;
}