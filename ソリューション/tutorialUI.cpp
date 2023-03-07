#include "main.h"
#include "resultUI.h"
#include "game.h"
#include "tutorialUI.h"
#include "EscapeTutorial.h"
#include "PlayNumberSelect.h"
#include "input.h"

//マクロ定義
#define NUM_SSUI					(18)		//TUTORIALUIの種類数
#define MAX_SSUI					(5)			//TUTORIALUIの最大使用数
#define MAX_BUFF					(3)			//バッファの最大数
#define MAX_GUYDE					(3)			//ガイドの最大数

#define POS_TUTORIALUI_ALL_X		(640.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_ALL_Y		(290.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_ALL_X		(270.0f)	//「」の幅
#define SIZE_TUTORIALUI_ALL_Y		(330.0f)	//「」の高さ

#define POS_TUTORIALUI_1_01_X		(640.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_1_01_Y		(630.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_1_01_X		(300.0f)	//「」の幅
#define SIZE_TUTORIALUI_1_01_Y		(80.0f)		//「」の高さ

#define POS_TUTORIALUI_2_01_X		(320.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_2_01_Y		(600.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_2_01_X		(150.0f)	//「」の幅
#define SIZE_TUTORIALUI_2_01_Y		(60.0f)		//「」の高さ

#define POS_TUTORIALUI_2_02_X		(960.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_2_02_Y		(600.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_2_02_X		(150.0f)	//「」の幅
#define SIZE_TUTORIALUI_2_02_Y		(60.0f)		//「」の高さ

#define POS_TUTORIALUI_34_01_X		(320.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_01_Y		(310.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_01_X		(150.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_01_Y		(25.0f)		//「」の高さ

#define POS_TUTORIALUI_34_02_X		(960.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_02_Y		(310.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_02_X		(150.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_02_Y		(25.0f)		//「」の高さ

#define POS_TUTORIALUI_34_03_X		(320.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_03_Y		(670.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_03_X		(150.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_03_Y		(25.0f)		//「」の高さ

#define POS_TUTORIALUI_34_04_X		(960.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_04_Y		(670.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_04_X		(150.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_04_Y		(25.0f)		//「」の高さ

#define UP_PAPERBG01				(100.0f)	//紙を取り出すときの上昇度
#define UP_PAPERBG01_COUNTER_MAX	(100)		//紙を取り出す速さのカウンター

//プロトタイプ宣言
void InitSkipUI(void);
void DrawSkipUI(void);
void InitGuydeUI(void);
void DrawGuydeUI(void);

//テクスチャファイル名
const char *c_apTutorialUITexname[] =
{
	"data\\TEXTURE\\TUTORIAL\\tutorial0.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial1.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial2.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial3.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial4.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial5.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial6.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial_move1.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial_dash1.png",
	"data\\TEXTURE\\TUTORIAL\\vibe.png",
	"data\\TEXTURE\\TUTORIAL\\stealth.png",
	"data\\TEXTURE\\TUTORIAL\\getkey.png",
	"data\\TEXTURE\\TUTORIAL\\open_doar1.png",
	"data\\TEXTURE\\TUTORIAL\\escape.png",
	"data\\TEXTURE\\TUTORIAL\\skip.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial00.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial02.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial01.png",
	"data\\TEXTURE\\TUTORIAL\\next_page.png",
	"data\\TEXTURE\\TUTORIAL\\back.png",
	"data\\TEXTURE\\TUTORIAL\\check_page.png",
};

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureTutorialUI[NUM_SSUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialUI[MAX_BUFF] = {};		//頂点バッファへのポインタ
bool bUseTutorialUI[MAX_SSUI];		//頂点バッファへのポインタ
bool g_bStageClear_Tutorial;
bool g_TutorialTEX_Change;			//テクスチャを切り替えるためのカウンター
int TutorialUI_TrueCounter;			//紙を取り出すときのカウンター

D3DXVECTOR3 pos;

//====================================================================
//タイトル画面の初期化処理
//====================================================================
void InitTutorialUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//テクスチャの読み込み
	for (int nCntUI = 0; nCntUI < NUM_SSUI; nCntUI++)
	{
		D3DXCreateTextureFromFile(pDevice, c_apTutorialUITexname[nCntUI], &g_apTextureTutorialUI[nCntUI]);
	}

	//UIの表示設定
	bUseTutorialUI[0] = true;
	bUseTutorialUI[1] = false;
	bUseTutorialUI[2] = false;
	bUseTutorialUI[3] = false;
	bUseTutorialUI[4] = false;
	TutorialUI_TrueCounter = 0;
	g_TutorialTEX_Change = false;

	//頂点バッファの生成0
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialUI[0],
		NULL);

	//頂点バッファの生成1
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialUI[1],
		NULL);

	//頂点バッファの生成1
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GUYDE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialUI[2],
		NULL);

	InitGuydeUI();

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffTutorialUI[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X - SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y - SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X + SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y - SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X - SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X + SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + SIZE_TUTORIALUI_ALL_Y, 0.0f);
			break;

		case 1:
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

		case 2:
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

		case 3:
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

		case 4:
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
	g_pVtxBuffTutorialUI[0]->Unlock();

	//スキップUIの初期化
	InitSkipUI();
}

//==============================================
//画面にスキップUIを表示する
//==============================================
void InitSkipUI(void)
{
	pos = D3DXVECTOR3(1160.0f, 690.0f, 0.0f);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、頂点情報へのポインタを所得
	g_pVtxBuffTutorialUI[1]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - 100, pos.y - 30, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 100, pos.y - 30, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 100, pos.y + 30, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 100, pos.y + 30, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffTutorialUI[1]->Unlock();
}

//==============================================
//画面にガイドUIを表示する
//==============================================
void InitGuydeUI(void)
{
	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、頂点情報へのポインタを所得
	g_pVtxBuffTutorialUI[2]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffTutorialUI[2]->Unlock();
}

//====================================================================
//タイトルの終了処理
//====================================================================
void UninitTutorialUI(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの破棄
		if (g_apTextureTutorialUI[nCntBG] != NULL)
		{
			g_apTextureTutorialUI[nCntBG]->Release();
			g_apTextureTutorialUI[nCntBG] = NULL;
		}
	}
	for (int nCntBuff = 0; nCntBuff < MAX_BUFF; nCntBuff++)
	{
		//頂点バッファの破棄
		if (g_pVtxBuffTutorialUI[nCntBuff] != NULL)
		{
			g_pVtxBuffTutorialUI[nCntBuff]->Release();
			g_pVtxBuffTutorialUI[nCntBuff] = NULL;
		}
	}
}

//====================================================================
//タイトル画面の更新処理
//====================================================================
void UpdateTutorialUI(void)
{
	TUTORIAL_STATE Tutorial_State = GetEscapeTutorial();

	switch (GetEscapeTutorial())
	{
	case TUTORIAL_STATE_STANDBY:
		//紙を取り出すときのカウンターを増やす
		if (TutorialUI_TrueCounter < UP_PAPERBG01_COUNTER_MAX)
		{
			TutorialUI_TrueCounter++;
		}
		break;

	case TUTORIAL_STATE_WAIT:
		//紙を取り出すときのカウンターを減らす
		if (TutorialUI_TrueCounter > 0)
		{
			TutorialUI_TrueCounter--;
		}
		break;
	}

	//紙を取り出す動き
	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffTutorialUI[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		if (nCntBG == 0 && TutorialUI_TrueCounter < UP_PAPERBG01_COUNTER_MAX)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X - SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_PAPERBG01 * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter)) - SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X + SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_PAPERBG01 * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter)) - SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X - SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_PAPERBG01 * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter)) + SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X + SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_PAPERBG01 * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter)) + SIZE_TUTORIALUI_ALL_Y, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter));
			pVtx[1].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter));
			pVtx[2].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter));
			pVtx[3].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter));
		}

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTutorialUI[0]->Unlock();
}

//====================================================================
//タイトル画面の描画処理
//====================================================================
void DrawTutorialUI(void)
{
	//チュートリアルの項目情報を与える処理
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();

	TUTORIAL_STATE Tutorial_State = GetEscapeTutorial();

	int nCntBG;

	if (Tutorial_State == TUTORIAL_STATE_GUYDE)
	{
		DrawGuydeUI();
	}

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialUI[0], 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (Tutorial_State == TUTORIAL_STATE_PLAY)
	{
		g_TutorialTEX_Change = false;
	}

	switch (do_Tutorial)
	{
	case MODE_MOVE:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//チュートリアルの状態がSTANDBYまたはWAITの時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[0]);
		}
		else
		{//それ以外の時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[7]);
		}

		break;

	case MODE_DASH:
		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//チュートリアルの状態がSTANDBYまたはWAITの時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[1]);
		}
		else
		{//それ以外の時
			 //テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[8]);
		}

		break;

	case MODE_VIBE:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//チュートリアルの状態がSTANDBYまたはWAITの時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[2]);
		}
		else
		{//それ以外の時
			 //テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[9]);
		}

		break;

	case MODE_STELTH:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//チュートリアルの状態がSTANDBYまたはWAITの時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[3]);
		}
		else
		{//それ以外の時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[10]);
		}

		break;

	case MODE_GET_KEY:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//チュートリアルの状態がSTANDBYまたはWAITの時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[4]);
		}
		else
		{//それ以外の時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[11]);
		}

		break;

	case MODE_ESCAPE:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//チュートリアルの状態がSTANDBYまたはWAITの時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[5]);
		}
		else
		{//それ以外の時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[12]);
		}

		break;

	case MODE_GOEXIT:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//チュートリアルの状態がSTANDBYまたはWAITの時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[6]);
		}
		else
		{//それ以外の時
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorialUI[13]);
		}

		break;

	case MODE_END:

		break;
	}

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		if (bUseTutorialUI[nCntBG] == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntBG,						//プリミティブ(ポリゴン)数
				2);
		}
	}

	DrawSkipUI();
}

//====================================================================
//スキップUIの描画処理
//====================================================================
void DrawSkipUI(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialUI[1], 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_apTextureTutorialUI[14]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,						//プリミティブ(ポリゴン)数
		2);
}

//====================================================================
//ガイドUIの描画処理
//====================================================================
void DrawGuydeUI(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	TUTORIAL_GUYDE Tutorial_Guyde = GetEscapeTutorialGuyde();

	//デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialUI[2], 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (Tutorial_Guyde == TUTORIAL_GUYDE_ESCAPE)
	{
		pDevice->SetTexture(0, g_apTextureTutorialUI[15]);
	}

	if (Tutorial_Guyde == TUTORIAL_GUYDE_KEY)
	{
		pDevice->SetTexture(0, g_apTextureTutorialUI[16]);
	}

	if (Tutorial_Guyde == TUTORIAL_GUYDE_HEALTH)
	{
		pDevice->SetTexture(0, g_apTextureTutorialUI[17]);
	}

	for (int nCntGuyde = 0; nCntGuyde < MAX_GUYDE; nCntGuyde++)
	{
		if (bUseTutorialUI[nCntGuyde] == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntGuyde,						//プリミティブ(ポリゴン)数
				2);
		}
	}
}

//====================================================================
//ランキングUIの設定処理
//====================================================================
void SetTutorialUI(bool bUse, int nCnt)
{
	bUseTutorialUI[nCnt] = bUse;
}