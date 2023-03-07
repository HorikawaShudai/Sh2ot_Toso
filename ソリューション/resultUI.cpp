#include "main.h"
#include "resultUI.h"
#include "numberUI.h"
#include "game.h"

//マクロ定義
#define NUM_SSUI		(6)	//GAMEUIの種類数
#define NUM_UITEX		(3)	//テクスチャ枚数

#define POS_RESULT_BG_X			(640.0f)	//「背景」のX座標の位置
#define POS_RESULT_BG_Y			(360.0f)	//「背景」のY座標の位置
#define SIZE_RESULT_BG_X		(640.0f)	//「背景」の幅
#define SIZE_RESULT_BG_Y		(360.0f)	//「背景」の高さ

#define POS_TEXT_BG_X			(640.0f)	//「テキスト」のX座標の位置
#define POS_TEXT_BG_Y			(400.0f)	//「テキスト」のY座標の位置
#define SIZE_TEXT_BG_X			(450.0f)	//「テキスト」の幅
#define SIZE_TEXT_BG_Y			(100.0f)	//「テキスト」の高さ

#define POS_PUSHKEY_BG_X		(1040.0f)	//「PUSH TO BUTTON」のX座標の位置
#define POS_PUSHKEY_BG_Y		(640.0f)	//「PUSH TO BUTTON」のY座標の位置
#define SIZE_PUSHKEY_BG_X		(150.0f)	//「PUSH TO BUTTON」の幅
#define SIZE_PUSHKEY_BG_Y		(50.0f)		//「PUSH TO BUTTON」の高さ

#define POS_KUROYANAGI_BG_X		(310.0f)	//「KUROYANAGI」のX座標の位置
#define POS_KUROYANAGI_BG_Y		(410.0f)	//「KUROYANAGI」のY座標の位置
#define SIZE_KUROYANAGI_BG_X	(410.0f)	//「KUROYANAGI」の幅
#define SIZE_KUROYANAGI_BG_Y	(310.0f)	//「KUROYANAGI」の高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureResultUI[NUM_SSUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultUI = NULL;		//頂点バッファへのポインタ
bool bUseResultUI[NUM_SSUI];		//頂点バッファへのポインタ
bool g_bStageClear_Result;
D3DXCOLOR g_FadeColor;
D3DXCOLOR g_KeepColor;

//プロトタイプ宣言
void FadeUi(void);

//====================================================================
//タイトル画面の初期化処理
//====================================================================
void InitResultUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RESULT\\Text.png",
		&g_apTextureResultUI[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RESULT\\PleazeButton.png",
		&g_apTextureResultUI[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RESULT\\kuroyanagi00.png",
		&g_apTextureResultUI[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultUI,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両点情報へのポインタを所得
	g_pVtxBuffResultUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_RESULT_BG_X - SIZE_RESULT_BG_X, POS_RESULT_BG_Y - SIZE_RESULT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_RESULT_BG_X + SIZE_RESULT_BG_X, POS_RESULT_BG_Y - SIZE_RESULT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_RESULT_BG_X - SIZE_RESULT_BG_X, POS_RESULT_BG_Y + SIZE_RESULT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_RESULT_BG_X + SIZE_RESULT_BG_X, POS_RESULT_BG_Y + SIZE_RESULT_BG_Y, 0.0f);
			break;

		case 1:
		case 2:
		case 3:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_TEXT_BG_X - SIZE_TEXT_BG_X, POS_TEXT_BG_Y - SIZE_TEXT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_TEXT_BG_X + SIZE_TEXT_BG_X, POS_TEXT_BG_Y - SIZE_TEXT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_TEXT_BG_X - SIZE_TEXT_BG_X, POS_TEXT_BG_Y + SIZE_TEXT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_TEXT_BG_X + SIZE_TEXT_BG_X, POS_TEXT_BG_Y + SIZE_TEXT_BG_Y, 0.0f);
			break;

		case 4:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_PUSHKEY_BG_X - SIZE_PUSHKEY_BG_X, POS_PUSHKEY_BG_Y - SIZE_PUSHKEY_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PUSHKEY_BG_X + SIZE_PUSHKEY_BG_X, POS_PUSHKEY_BG_Y - SIZE_PUSHKEY_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PUSHKEY_BG_X - SIZE_PUSHKEY_BG_X, POS_PUSHKEY_BG_Y + SIZE_PUSHKEY_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PUSHKEY_BG_X + SIZE_PUSHKEY_BG_X, POS_PUSHKEY_BG_Y + SIZE_PUSHKEY_BG_Y, 0.0f);
			break;

		case 5:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_KUROYANAGI_BG_X - SIZE_KUROYANAGI_BG_X, POS_KUROYANAGI_BG_Y - SIZE_KUROYANAGI_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_KUROYANAGI_BG_X + SIZE_KUROYANAGI_BG_X, POS_KUROYANAGI_BG_Y - SIZE_KUROYANAGI_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_KUROYANAGI_BG_X - SIZE_KUROYANAGI_BG_X, POS_KUROYANAGI_BG_Y + SIZE_KUROYANAGI_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_KUROYANAGI_BG_X + SIZE_KUROYANAGI_BG_X, POS_KUROYANAGI_BG_Y + SIZE_KUROYANAGI_BG_Y, 0.0f);
			break;
		}

		if (nCntBG == 0)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
		}
		else
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		if (nCntBG > 0 && nCntBG < 4)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + ((nCntBG - 1)*0.33333f));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + ((nCntBG - 1)*0.33333f));
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.33333f + ((nCntBG - 1)*0.33333f));
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.33333f + ((nCntBG - 1)*0.33333f));
		}
		else
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;	//頂点データのポインタを４つ分進める

	}

	//頂点バッファをアンロックする
	g_pVtxBuffResultUI->Unlock();

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//UIの表示設定
		bUseResultUI[nCntBG] = false;
	}
}

//====================================================================
//タイトルの終了処理
//====================================================================
void UninitResultUI(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_UITEX; nCntBG++)
	{
		//テクスチャの破棄
		if (g_apTextureResultUI[nCntBG] != NULL)
		{
			g_apTextureResultUI[nCntBG]->Release();
			g_apTextureResultUI[nCntBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResultUI != NULL)
	{
		g_pVtxBuffResultUI->Release();
		g_pVtxBuffResultUI = NULL;
	}
}

//====================================================================
//タイトル画面の更新処理
//====================================================================
void UpdateResultUI(void)
{
	if (g_bStageClear_Result == true)
	{
		FadeUi();
	}
}

//====================================================================
//タイトル画面の描画処理
//====================================================================
void DrawResultUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの設定
		switch (nCntBG)
		{
		case 0:
			pDevice->SetTexture(0, NULL);
			break;
		case 1:
		case 2:
		case 3:
			pDevice->SetTexture(0, g_apTextureResultUI[0]);
			break;
		case 4:
			pDevice->SetTexture(0, g_apTextureResultUI[1]);
			break;
		case 5:
			pDevice->SetTexture(0, g_apTextureResultUI[2]);
			break;

		}
		if (bUseResultUI[nCntBG] == true)
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
void SetResultUI(RESULTUI SetClear)
{

	switch (SetClear)
	{
	case RESULTUI_ONLY:				//1人生存(一人プレイを除く)
		bUseResultUI[0] = true;
		bUseResultUI[1] = false;
		bUseResultUI[2] = false;
		bUseResultUI[3] = true;
		bUseResultUI[4] = true;
		bUseResultUI[5] = true;

		break;

	case RESULTUI_TWO:				//二人以上全員未満生存
		bUseResultUI[0] = true;
		bUseResultUI[1] = false;
		bUseResultUI[2] = true;
		bUseResultUI[3] = false;
		bUseResultUI[4] = true;
		bUseResultUI[5] = true;

		break;

	case RESULTUI_PERFECT:			//全員生存の場合
		bUseResultUI[0] = true;
		bUseResultUI[1] = true;
		bUseResultUI[2] = false;
		bUseResultUI[3] = false;
		bUseResultUI[4] = true;
		bUseResultUI[5] = true;

		break;
	}
}

//====================================================================
//UIの遷移処理
//====================================================================
void FadeUi(void)
{
	g_KeepColor.a -= g_FadeColor.a;
	if (g_KeepColor.a<0.0f || g_KeepColor.a>1.0f)
	{
		g_FadeColor *= -1.0f;
	}

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffResultUI->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 16;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(g_KeepColor);
	pVtx[1].col = D3DXCOLOR(g_KeepColor);
	pVtx[2].col = D3DXCOLOR(g_KeepColor);
	pVtx[3].col = D3DXCOLOR(g_KeepColor);


	//頂点バッファをアンロックする
	g_pVtxBuffResultUI->Unlock();
}


//====================================================================
//取得処理
//====================================================================
bool GetbResultUi(void)
{
	return g_bStageClear_Result;
}

//====================================================================
//表示設定処理
//====================================================================
void SetbResultUi(bool bReseultUi)
{
	int nClear = GetClear();
	switch (bReseultUi)
	{
	case true:
		
		switch (nClear)
		{
		case 1:
			SetResultUI(RESULTUI_PERFECT);
			break;
		case 2:
			SetResultUI(RESULTUI_TWO);
			break;
		case 3:
			SetResultUI(RESULTUI_ONLY);
			break;
		}
		g_bStageClear_Result = true;
		break;

	case false:
		g_bStageClear_Result = false;
		break;

	}
}