#include "CheckboxUI.h"
#include "fade.h"
#include "player.h"
#include "PlayNumberSelect.h"

//マクロ定義
#define MAX_CHECK_TEX		(2)				//チェックボックスのテクスチャ最大数

#define CHECKUIPOS_X_1	(30.0f)			//チェックボックスのUIのX位置1
#define CHECKUIPOS_Y_1	(350.0f)		//チェックボックスのUIのY位置1

#define CHECKUIPOS_X_2	(670.0f)		//チェックボックスのUIのX位置2
#define CHECKUIPOS_Y_2	(700.0f)		//チェックボックスのUIのY位置2

#define CHECKUI_WIDTH		(20.0f)			//チェックボックスのUIの幅
#define CHECKUI_HEIGHT	(20.0f)			//チェックボックスのUIの高さ
#define CHECKUI_INTERVAL	(50.0f)			//チェックボックスのUI同士の間隔

//チェックボックスUIの構造体
typedef struct
{
	D3DXVECTOR3 pos;  //鍵UIの位置
	int nCheckUI;  //鍵UIの数
	bool bUse;  //使われているかどうか
}CHECKUI;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureCheckUI[MAX_CHECK_TEX] = {};  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCheckUI = NULL; //頂点バッファへのポインタ
CHECKUI g_anCheckUI[NUM_PLAYER];			//チェックボックスのUIの情報
int g_NumPlayerCheckUI;

//====================================================================
//チェックボックスの初期化処理
//====================================================================
void InitCheckboxUI(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//変数宣言
	int nCntCheckUI;

	//グローバル宣言の初期化
	g_NumPlayerCheckUI = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\nokey.png",
		&g_pTextureCheckUI[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\getkey.png",
		&g_pTextureCheckUI[1]);

	//鍵UIの情報を初期化
	for (nCntCheckUI = 0; nCntCheckUI < PlayNumber.CurrentSelectNumber; nCntCheckUI++)
	{
		if (nCntCheckUI == 0)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_1, CHECKUIPOS_Y_1, 0.0f);  //1人目の位置を初期化
		}

		if (nCntCheckUI == 1)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_2, CHECKUIPOS_Y_1, 0.0f);  //2人目の位置を初期化
		}

		if (nCntCheckUI == 2)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_1, CHECKUIPOS_Y_2, 0.0f);  //3人目の位置を初期化
		}

		if (nCntCheckUI == 3)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_2, CHECKUIPOS_Y_2, 0.0f);  //4人目の位置を初期化
		}
		g_anCheckUI[nCntCheckUI].nCheckUI = 3;		//鍵UIの値を初期化
		g_anCheckUI[nCntCheckUI].bUse = false;  //使っていないことに
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCheckUI,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCheckUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y - CHECKUI_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y - CHECKUI_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y + CHECKUI_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y + CHECKUI_HEIGHT, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffCheckUI->Unlock();
}

//====================================================================
//チェックボックスの終了処理
//====================================================================
void UninitCheckboxUI(void)
{
	for (int nCnt = 0; nCnt < MAX_CHECK_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureCheckUI[nCnt] != NULL)
		{
			g_pTextureCheckUI[nCnt]->Release();
			g_pTextureCheckUI[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffCheckUI != NULL)
	{
		g_pVtxBuffCheckUI->Release();
		g_pVtxBuffCheckUI = NULL;
	}
}

//====================================================================
//チェックボックスの更新処理
//====================================================================
void UpdateCheckboxUI(void)
{

}

//====================================================================
//チェックボックスの描画処理
//====================================================================
void DrawCheckboxUI(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCheckUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		if (g_anCheckUI[nCnt].bUse == false)
		{//鍵を取得していないとき
		 //テクスチャの設定
			pDevice->SetTexture(0, g_pTextureCheckUI[0]);
		}

		else
		{//鍵を取得しているとき
		 //テクスチャの設定
			pDevice->SetTexture(0, g_pTextureCheckUI[1]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}