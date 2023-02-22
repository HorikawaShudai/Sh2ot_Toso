#include "main.h"
#include "EScapeTutorial.h"
#include "paperBG00.h"

//マクロ定義
#define NUM_SSUI				(2)			//GAMEUIの種類数

#define POS_BLACK_BG_X			(640.0f)	//「黒色の背景」のX座標の位置
#define POS_BLACK_BG_Y			(360.0f)	//「黒色の背景」のY座標の位置
#define SIZE_BLACK_BG_X			(640.0f)	//「黒色の背景」の幅
#define SIZE_BLACK_BG_Y			(360.0f)	//「黒色の背景」の高さ

#define POS_PAPER_BG_X			(640.0f)	//「紙」のX座標の位置
#define POS_PAPER_BG_Y			(310.0f)	//「紙」のY座標の位置
#define SIZE_PAPER_BG_X			(500.0f)	//「紙」の幅
#define SIZE_PAPER_BG_Y			(300.0f)	//「紙」の高さ

#define UP_PAPER_BG				(100.0f)	//紙を取り出すときの上昇度
#define UP_PAPER_COUNTER_MAX	(100)		//紙を取り出す速さのカウンター

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTexturePaperBG00[NUM_SSUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPaperBG00 = NULL;		//頂点バッファへのポインタ
bool bUsePaperBG00[NUM_SSUI];		//UIを使っているかどうか
int PaperBG00TrueCounter;			//紙を取り出すときのカウンター

//====================================================================
//紙背景00の初期化処理
//====================================================================
void InitPaperBG00(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
	//	&g_apTexturePaperBG00[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
		&g_apTexturePaperBG00[1]);

	//UIの表示設定
	bUsePaperBG00[0] = true;
	bUsePaperBG00[1] = true;
	PaperBG00TrueCounter = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPaperBG00,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPaperBG00->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_BLACK_BG_X - SIZE_BLACK_BG_X, POS_BLACK_BG_Y - SIZE_BLACK_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_BLACK_BG_X + SIZE_BLACK_BG_X, POS_BLACK_BG_Y - SIZE_BLACK_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_BLACK_BG_X - SIZE_BLACK_BG_X, POS_BLACK_BG_Y + SIZE_BLACK_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_BLACK_BG_X + SIZE_BLACK_BG_X, POS_BLACK_BG_Y + SIZE_BLACK_BG_Y, 0.0f);
			break;

		case 1:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_PAPER_BG_X - SIZE_PAPER_BG_X, POS_PAPER_BG_Y - SIZE_PAPER_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PAPER_BG_X + SIZE_PAPER_BG_X, POS_PAPER_BG_Y - SIZE_PAPER_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PAPER_BG_X - SIZE_PAPER_BG_X, POS_PAPER_BG_Y + SIZE_PAPER_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PAPER_BG_X + SIZE_PAPER_BG_X, POS_PAPER_BG_Y + SIZE_PAPER_BG_Y, 0.0f);
			break;
		}

		switch (nCntBG)
		{
		case 0:
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			break;

		case 1:
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			break;
		}

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
	g_pVtxBuffPaperBG00->Unlock();
}

//====================================================================
//タイトルの終了処理
//====================================================================
void UninitPaperBG00(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの破棄
		if (g_apTexturePaperBG00[nCntBG] != NULL)
		{
			g_apTexturePaperBG00[nCntBG]->Release();
			g_apTexturePaperBG00[nCntBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPaperBG00 != NULL)
	{
		g_pVtxBuffPaperBG00->Release();
		g_pVtxBuffPaperBG00 = NULL;
	}
}

//====================================================================
//紙背景00の更新処理
//====================================================================
void UpdatePaperBG00(void)
{
	switch (GetEscapeTutorial())
	{
	case TUTORIAL_STATE_STANDBY:
		//紙を取り出すときのカウンターを増やす
		if (PaperBG00TrueCounter < UP_PAPER_COUNTER_MAX)
		{
			PaperBG00TrueCounter++;
		}
		break;

	case TUTORIAL_STATE_WAIT:
		//紙を取り出すときのカウンターを減らす
		if (PaperBG00TrueCounter > 0)
		{
			PaperBG00TrueCounter--;
		}
		break;
	}

	//紙を取り出す動き
	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPaperBG00->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			if (PaperBG00TrueCounter <= 0)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			}
			else
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			}
			break;

		case 1:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_PAPER_BG_X - SIZE_PAPER_BG_X, POS_PAPER_BG_Y + (UP_PAPER_BG * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter)) - SIZE_PAPER_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PAPER_BG_X + SIZE_PAPER_BG_X, POS_PAPER_BG_Y + (UP_PAPER_BG * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter)) - SIZE_PAPER_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PAPER_BG_X - SIZE_PAPER_BG_X, POS_PAPER_BG_Y + (UP_PAPER_BG * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter)) + SIZE_PAPER_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PAPER_BG_X + SIZE_PAPER_BG_X, POS_PAPER_BG_Y + (UP_PAPER_BG * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter)) + SIZE_PAPER_BG_Y, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter));
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter));
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter));
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter));

			break;
		}

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPaperBG00->Unlock();
}

//====================================================================
//紙背景00の描画処理
//====================================================================
void DrawPaperBG00(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPaperBG00, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePaperBG00[nCntBG]);

		if (bUsePaperBG00[nCntBG] == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntBG,						//プリミティブ(ポリゴン)数
				2);
		}
	}
}

//====================================================================
//紙背景00のセット処理
//====================================================================
void SetPaperBG00(bool bUse)
{
	bUsePaperBG00[0] = bUse;
	bUsePaperBG00[1] = bUse;
}