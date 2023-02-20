#include "main.h"
#include "resultUI.h"
#include "game.h"
#include "tutorialUI.h"
#include "EscapeTutorial.h"
#include "PlayNumberSelect.h"

//マクロ定義
#define NUM_SSUI					(8)			//TUTORIALUIの種類数
#define MAX_SSUI					(5)			//TUTORIALUIの最大使用数

#define POS_TUTORIALUI_ALL_X		(640.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_ALL_Y		(350.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_ALL_X		(200.0f)	//「」の幅
#define SIZE_TUTORIALUI_ALL_Y		(100.0f)	//「」の高さ

#define POS_TUTORIALUI_1_01_X		(640.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_1_01_Y		(620.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_1_01_X		(300.0f)	//「」の幅
#define SIZE_TUTORIALUI_1_01_Y		(50.0f)		//「」の高さ

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

#define UP_TUTORIALUI				(100.0f)	//紙を取り出すときの上昇度
#define UP_TUTORIALUI_COUNTER_MAX	(100)		//紙を取り出す速さのカウンター

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureTutorialUI[NUM_SSUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialUI = NULL;		//頂点バッファへのポインタ
bool bUseTutorialUI[MAX_SSUI];		//頂点バッファへのポインタ
bool g_bStageClear_Tutorial;
int TutorialUI_TrueCounter;			//紙を取り出すときのカウンター

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
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\tutorial_move.png",
		&g_apTextureTutorialUI[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\tutorial_cammove.png",
		&g_apTextureTutorialUI[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\tutorial_dash.png",
		&g_apTextureTutorialUI[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\vibe.png",
		&g_apTextureTutorialUI[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\stealth.png",
		&g_apTextureTutorialUI[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\tutorial_key.png",
		&g_apTextureTutorialUI[5]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\open_doar.png",
		&g_apTextureTutorialUI[6]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\tutorial_end.png",
		&g_apTextureTutorialUI[7]);

	//UIの表示設定
	bUseTutorialUI[0] = true;
	bUseTutorialUI[1] = false;
	bUseTutorialUI[2] = false;
	bUseTutorialUI[3] = false;
	bUseTutorialUI[4] = false;
	TutorialUI_TrueCounter = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialUI,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffTutorialUI->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

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
	g_pVtxBuffTutorialUI->Unlock();
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

	//頂点バッファの破棄
	if (g_pVtxBuffTutorialUI != NULL)
	{
		g_pVtxBuffTutorialUI->Release();
		g_pVtxBuffTutorialUI = NULL;
	}
}

//====================================================================
//タイトル画面の更新処理
//====================================================================
void UpdateTutorialUI(void)
{
	switch (GetEscapeTutorial())
	{
	case TUTORIAL_STATE_STANDBY:
		//紙を取り出すときのカウンターを増やす
		if (TutorialUI_TrueCounter < UP_TUTORIALUI_COUNTER_MAX)
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
	g_pVtxBuffTutorialUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		if (nCntBG == 0 && TutorialUI_TrueCounter < UP_TUTORIALUI_COUNTER_MAX)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X - SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_TUTORIALUI * ((float)UP_TUTORIALUI_COUNTER_MAX / (float)TutorialUI_TrueCounter)) - SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X + SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_TUTORIALUI * ((float)UP_TUTORIALUI_COUNTER_MAX / (float)TutorialUI_TrueCounter)) - SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X - SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_TUTORIALUI * ((float)UP_TUTORIALUI_COUNTER_MAX / (float)TutorialUI_TrueCounter)) + SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X + SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_TUTORIALUI * ((float)UP_TUTORIALUI_COUNTER_MAX / (float)TutorialUI_TrueCounter)) + SIZE_TUTORIALUI_ALL_Y, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_TUTORIALUI_COUNTER_MAX / (float)TutorialUI_TrueCounter));
			pVtx[1].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_TUTORIALUI_COUNTER_MAX / (float)TutorialUI_TrueCounter));
			pVtx[2].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_TUTORIALUI_COUNTER_MAX / (float)TutorialUI_TrueCounter));
			pVtx[3].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_TUTORIALUI_COUNTER_MAX / (float)TutorialUI_TrueCounter));
		}

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTutorialUI->Unlock();
}

//====================================================================
//タイトル画面の描画処理
//====================================================================
void DrawTutorialUI(void)
{
	//チュートリアルの項目情報を与える処理
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();

	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	switch (do_Tutorial)
	{
	case MODE_MOVE:

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTutorialUI[0]);

		break;

	case MODE_DASH:

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTutorialUI[2]);

		break;

	case MODE_VIBE:

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTutorialUI[3]);

		break;

	case MODE_STELTH:

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTutorialUI[4]);

		break;

	case MODE_GET_KEY:

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTutorialUI[5]);

		break;

	case MODE_ESCAPE:

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTutorialUI[6]);

		break;

	case MODE_END:

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTutorialUI[7]);

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
}
//====================================================================
//ランキングUIの設定処理
//====================================================================
void SetTutorialUI(bool bUse, int nCnt)
{
	bUseTutorialUI[nCnt] = bUse;
}