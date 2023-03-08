#include "main.h"
#include "resultUI.h"
#include "game.h"
#include "paperBG01.h"
#include "EscapeTutorial.h"
#include "PlayNumberSelect.h"

//マクロ定義
#define MAX_SSUI					(4)			//TUTORIALUIの最大使用数

//一人プレイ
#define POS_TUTORIALUI_1_01_X		(640.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_1_01_Y		(620.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_1_01_X		(400.0f)	//「」の幅
#define SIZE_TUTORIALUI_1_01_Y		(100.0f)	//「」の高さ
//二人プレイ	一人目
#define POS_TUTORIALUI_2_01_X		(320.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_2_01_Y		(630.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_2_01_X		(300.0f)	//「」の幅
#define SIZE_TUTORIALUI_2_01_Y		(80.0f)	//「」の高さ
//二人目
#define POS_TUTORIALUI_2_02_X		(960.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_2_02_Y		(630.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_2_02_X		(300.0f)	//「」の幅
#define SIZE_TUTORIALUI_2_02_Y		(80.0f)	//「」の高さ
//三・四人プレイ	一人プレイ
#define POS_TUTORIALUI_34_01_X		(320.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_01_Y		(310.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_01_X		(300.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_01_Y		(50.0f)		//「」の高さ
//二人プレイ
#define POS_TUTORIALUI_34_02_X		(960.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_02_Y		(310.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_02_X		(300.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_02_Y		(50.0f)		//「」の高さ
//三人プレイ
#define POS_TUTORIALUI_34_03_X		(320.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_03_Y		(670.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_03_X		(300.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_03_Y		(50.0f)		//「」の高さ
//四人プレイ
#define POS_TUTORIALUI_34_04_X		(960.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_04_Y		(670.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_04_X		(300.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_04_Y		(50.0f)		//「」の高さ

#define UP_PAPERBG01				(100.0f)	//紙を取り出すときの上昇度
#define UP_PAPERBG01_COUNTER_MAX	(100)		//紙を取り出す速さのカウンター

//テクスチャファイル名
const char *c_cpPaperTexname01[] =
{
	"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
	"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
	"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
	"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
};

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTexturePaperBG01[MAX_SSUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPaperBG01 = NULL;		//頂点バッファへのポインタ
bool bUsePaperBG01[MAX_SSUI];		//頂点バッファへのポインタ

//====================================================================
//タイトル画面の初期化処理
//====================================================================
void InitPaperBG01(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	for (int nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, c_cpPaperTexname01[nCntBG], &g_apTexturePaperBG01[nCntBG]);
	}

	//UIの表示設定
	bUsePaperBG01[0] = false;
	bUsePaperBG01[1] = false;
	bUsePaperBG01[2] = false;
	bUsePaperBG01[3] = false;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPaperBG01,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPaperBG01->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			switch (GetPlayNumberSelect().CurrentSelectNumber)
			{
			case 1:
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_1_01_X - SIZE_TUTORIALUI_1_01_X, POS_TUTORIALUI_1_01_Y - SIZE_TUTORIALUI_1_01_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_1_01_X + SIZE_TUTORIALUI_1_01_X, POS_TUTORIALUI_1_01_Y - SIZE_TUTORIALUI_1_01_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_1_01_X - SIZE_TUTORIALUI_1_01_X, POS_TUTORIALUI_1_01_Y + SIZE_TUTORIALUI_1_01_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_1_01_X + SIZE_TUTORIALUI_1_01_X, POS_TUTORIALUI_1_01_Y + SIZE_TUTORIALUI_1_01_Y, 0.0f);
				break;
			case 2:
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_2_01_X - SIZE_TUTORIALUI_2_01_X, POS_TUTORIALUI_2_01_Y - SIZE_TUTORIALUI_2_01_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_2_01_X + SIZE_TUTORIALUI_2_01_X, POS_TUTORIALUI_2_01_Y - SIZE_TUTORIALUI_2_01_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_2_01_X - SIZE_TUTORIALUI_2_01_X, POS_TUTORIALUI_2_01_Y + SIZE_TUTORIALUI_2_01_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_2_01_X + SIZE_TUTORIALUI_2_01_X, POS_TUTORIALUI_2_01_Y + SIZE_TUTORIALUI_2_01_Y, 0.0f);
				break;
			case 3:
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X - SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y - SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X + SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y - SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X - SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y + SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X + SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y + SIZE_TUTORIALUI_34_01_Y, 0.0f);
				break;
			case 4:
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X - SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y - SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X + SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y - SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X - SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y + SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X + SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y + SIZE_TUTORIALUI_34_01_Y, 0.0f);
				break;
			}
			break;

		case 1:
			switch (GetPlayNumberSelect().CurrentSelectNumber)
			{
			case 2:
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_2_02_X - SIZE_TUTORIALUI_2_02_X, POS_TUTORIALUI_2_02_Y - SIZE_TUTORIALUI_2_02_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_2_02_X + SIZE_TUTORIALUI_2_02_X, POS_TUTORIALUI_2_02_Y - SIZE_TUTORIALUI_2_02_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_2_02_X - SIZE_TUTORIALUI_2_02_X, POS_TUTORIALUI_2_02_Y + SIZE_TUTORIALUI_2_02_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_2_02_X + SIZE_TUTORIALUI_2_02_X, POS_TUTORIALUI_2_02_Y + SIZE_TUTORIALUI_2_02_Y, 0.0f);
				break;
			case 3:
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X - SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y - SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X + SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y - SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X - SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y + SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X + SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y + SIZE_TUTORIALUI_34_02_Y, 0.0f);
				break;
			case 4:
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X - SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y - SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X + SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y - SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X - SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y + SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X + SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y + SIZE_TUTORIALUI_34_02_Y, 0.0f);
				break;
			}
			break;

		case 2:
			switch (GetPlayNumberSelect().CurrentSelectNumber)
			{
			case 3:
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X - SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y - SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X + SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y - SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X - SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y + SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X + SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y + SIZE_TUTORIALUI_34_03_Y, 0.0f);
				break;
			case 4:
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X - SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y - SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X + SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y - SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X - SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y + SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X + SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y + SIZE_TUTORIALUI_34_03_Y, 0.0f);
				break;
			}
			break;

		case 3:
			switch (GetPlayNumberSelect().CurrentSelectNumber)
			{
			case 4:
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_04_X - SIZE_TUTORIALUI_34_04_X, POS_TUTORIALUI_34_04_Y - SIZE_TUTORIALUI_34_04_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_04_X + SIZE_TUTORIALUI_34_04_X, POS_TUTORIALUI_34_04_Y - SIZE_TUTORIALUI_34_04_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_04_X - SIZE_TUTORIALUI_34_04_X, POS_TUTORIALUI_34_04_Y + SIZE_TUTORIALUI_34_04_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_04_X + SIZE_TUTORIALUI_34_04_X, POS_TUTORIALUI_34_04_Y + SIZE_TUTORIALUI_34_04_Y, 0.0f);
				break;
			}
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
	g_pVtxBuffPaperBG01->Unlock();
}

//====================================================================
//タイトルの終了処理
//====================================================================
void UninitPaperBG01(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//テクスチャの破棄
		if (g_apTexturePaperBG01[nCntBG] != NULL)
		{
			g_apTexturePaperBG01[nCntBG]->Release();
			g_apTexturePaperBG01[nCntBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPaperBG01 != NULL)
	{
		g_pVtxBuffPaperBG01->Release();
		g_pVtxBuffPaperBG01 = NULL;
	}
}

//====================================================================
//タイトル画面の更新処理
//====================================================================
void UpdatePaperBG01(void)
{

}

//====================================================================
//タイトル画面の描画処理
//====================================================================
void DrawPaperBG01(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPaperBG01, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePaperBG01[nCntBG]);

		if (bUsePaperBG01[nCntBG] == true)
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
void SetPaperBG01(bool bUse, int nCnt)
{
	bUsePaperBG01[nCnt] = bUse;
}