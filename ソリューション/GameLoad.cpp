//=======================================================================
//
//ロード画面の処理(GameLoad.cpp)
//Auther:堀川萩大
//
//=======================================================================
#include "GameLoad.h"
#include "Fade.h"
#include "Input.h"

//マクロ定義
#define MAX_TEX		(2)				//テクスチャの最大数
#define NUM_BACK	(3)				//使う枚数
#define HEIGHT_TEX	(200.0f)		//テクスチャの幅
#define WIDTH_TEX	(200.0f)		//テクスチャの高さ
#define TEX_POS_X	(640.0f)		//中心座標(X)
#define TEX_POS_Y	(360.0f)		//中心座標(Y)
#define FADE_COUNT	(120)			//自動遷移のカウント

#define EACHICON_SIZE	(50.0f)		//個人アイコンのサイズ

//テクスチャファイル名
const char *c_paIconTexname[] =
{
	"Data\\TEXTURE\\Sh2ot_Logo.png",			//チームロゴ
	"Data\\TEXTURE\\ICON\\Name_Icon00.png",		//小笠原のアイコン
};

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureGameLoad[NUM_BACK] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameLoad = NULL;
bool bCount;										//自動遷移開始
int g_FCount;										//カウント用変数
D3DXVECTOR3 g_Texpos;								//中心座標の保存用

//============================================
//ロード画面の初期化処理
//============================================
void InitGameLoad(void)
{
	//変数の初期化
	g_Texpos = D3DXVECTOR3(TEX_POS_X, TEX_POS_Y, 0.0f);
	bCount = false;
	g_FCount = 0;

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, c_paIconTexname[nCntTex], &g_pTextureGameLoad[nCntTex]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BACK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameLoad,
		NULL);

	VERTEX_2D * pVtx;
	g_pVtxBuffGameLoad->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_BACK; nCnt++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		switch (nCnt)
		{
		case 0:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Texpos.x - TEX_POS_X, g_Texpos.y - TEX_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Texpos.x + TEX_POS_X, g_Texpos.y - TEX_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Texpos.x - TEX_POS_X, g_Texpos.y + TEX_POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Texpos.x + TEX_POS_X, g_Texpos.y + TEX_POS_Y, 0.0f);
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			break;
		case 1:

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Texpos.x - HEIGHT_TEX, g_Texpos.y - WIDTH_TEX, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Texpos.x + HEIGHT_TEX, g_Texpos.y - WIDTH_TEX, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Texpos.x - HEIGHT_TEX, g_Texpos.y + WIDTH_TEX, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Texpos.x + HEIGHT_TEX, g_Texpos.y + WIDTH_TEX, 0.0f);
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		default:

			g_Texpos = D3DXVECTOR3(50.0f + (150.0f * (nCnt - 2)), 600.0f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Texpos.x - EACHICON_SIZE, 600.0f - EACHICON_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Texpos.x + EACHICON_SIZE, 600.0f - EACHICON_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Texpos.x - EACHICON_SIZE, 600.0f + EACHICON_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Texpos.x + EACHICON_SIZE, 600.0f + EACHICON_SIZE, 0.0f);
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
		}
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		
		pVtx += 4;
	}

	g_pVtxBuffGameLoad->Unlock();
}

//============================================
//ロード画面の終了処理
//============================================
void UninitGameLoad(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureGameLoad[nCntTex] != NULL)
		{
			g_pTextureGameLoad[nCntTex]->Release();
			g_pTextureGameLoad[nCntTex] = NULL;
		}
	}
	if (g_pVtxBuffGameLoad != NULL)
	{
		g_pVtxBuffGameLoad->Release();
		g_pVtxBuffGameLoad = NULL;
	}
}

//============================================
//ロード画面の更新処理
//============================================
void UpdateGameLoad(void)
{
	FADE bFade = GetFade();

	if (bCount == false)
	{
		if (bFade == FADE_NONE)
		{
			//自動遷移開始
			bCount = true;
		}
	}
	else if (bCount == true)
	{
		g_FCount++;

		//カウントが一定数、または特定ボタンで遷移
		if (g_FCount == FADE_COUNT || GetGamepadTrigger(BUTTON_START,0) || GetGamepadTrigger(BUTTON_A, 0) || GetKeyboardTrigger(DIK_RETURN) && bFade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
		}
	}

}

//============================================
//ロード画面の描画処理
//============================================
void DrawGameLoad(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	pDevice->SetStreamSource(0, g_pVtxBuffGameLoad, 0, sizeof(VERTEX_2D));

	for (int nCnt = 0; nCnt < NUM_BACK; nCnt++)
	{
		//テクスチャの設定
		if (nCnt == 0)
		{
			pDevice->SetTexture(0, NULL);
		}
		else
		{
			pDevice->SetTexture(0, g_pTextureGameLoad[nCnt - 1]);
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCnt, 2);
	}
}