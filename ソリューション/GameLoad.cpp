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
#define MAX_TEX		(6)				//テクスチャの最大数
#define NUM_BACK	(7)				//使う枚数
#define TEX_SIZE	(120.0f)		//テクスチャの大きさ
#define TEX_POS_X	(640.0f)		//中心座標(X)
#define TEX_POS_Y	(360.0f)		//中心座標(Y)
#define FADE_COUNT	(300)			//自動遷移のカウント

#define EACHICON_POSX	(120.0f)		//横の位置
#define EACHICON_POSY	(600.0f)		//縦の位置
#define EACHICON_SPACE	(500.0f)		//アイコン同士の距離
#define EACHICON_SIZE	(100.0f)		//個人アイコンのサイズ

//テクスチャファイル名
const char *c_paIconTexname[] =
{
	"Data\\TEXTURE\\Sh2ot_Logo.png",			//チームロゴ
	"Data\\TEXTURE\\ICON\\Sakamoto_Icon.png",	//坂本のアイコン
	"Data\\TEXTURE\\ICON\\Logo_Hosyu.jpg",		//堀川のアイコン
	"Data\\TEXTURE\\ICON\\yuki_icon.png",		//早川のアイコン
	"Data\\TEXTURE\\ICON\\Oga_Icon.png",		//小笠原のアイコン
	"Data\\TEXTURE\\ICON\\logo.png",			//丹野のアイコン
};

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureGameLoad[NUM_BACK] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameLoad = NULL;
bool bCount;										//自動遷移開始
int g_FCount;										//カウント用変数
D3DXVECTOR3 g_Texpos;								//中心座標の保存用

typedef struct
{
	D3DXVECTOR3 pos;
	LPDIRECT3DTEXTURE9 Tex;
	int nType;
	bool bUse;
}LOGO;

LOGO g_aLogo[MAX_TEX];
int g_nLogoScreenMode;

//============================================
//ロード画面の初期化処理
//============================================
void InitGameLoad(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nLogoScreenMode = 0;
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//座標とテクスチャの設定;
		switch (nCnt)
		{
		case 0:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.5f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.25f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = true;
			break;
		case 1:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.25f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.6f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = true;
			break;
		case 2:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.5f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.6f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = true;
			break;
		case 3:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.75f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.6f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = true;
			break;
		case 4:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.3f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.6f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = false;
			break;
		case 5:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.7f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.6f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = false;
			break;
		default:
			break;
		}
		D3DXCreateTextureFromFile(pDevice, c_paIconTexname[nCnt], &g_aLogo[nCnt].Tex);
	}

	//変数の初期化
	g_Texpos = D3DXVECTOR3(TEX_POS_X, TEX_POS_Y, 0.0f);
	bCount = false;
	g_FCount = 0;


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

		if (nCnt == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
		
		}
		else
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aLogo[nCnt - 1].pos.x - TEX_SIZE, g_aLogo[nCnt - 1].pos.y - TEX_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLogo[nCnt - 1].pos.x + TEX_SIZE, g_aLogo[nCnt - 1].pos.y - TEX_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLogo[nCnt - 1].pos.x - TEX_SIZE, g_aLogo[nCnt - 1].pos.y + TEX_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLogo[nCnt - 1].pos.x + TEX_SIZE, g_aLogo[nCnt - 1].pos.y + TEX_SIZE, 0.0f);
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
		if (g_nLogoScreenMode == 0)
		{
			for (int nCnt = 0; nCnt < MAX_TEX - 2; nCnt++)
			{
				g_aLogo[nCnt].bUse = true;
			}
		}
		else
		{
			g_aLogo[0].bUse = true;
			g_aLogo[1].bUse = false;
			g_aLogo[2].bUse = false;
			g_aLogo[3].bUse = false;
			g_aLogo[4].bUse = true;
			g_aLogo[5].bUse = true;

		}

		if (g_nLogoScreenMode == 0 && (g_FCount >= ( FADE_COUNT * 0.5f )|| GetGamepadTrigger(BUTTON_START, 0) || GetGamepadTrigger(BUTTON_A, 0) || GetKeyboardTrigger(DIK_RETURN)))
		{
			g_nLogoScreenMode++;
		}

		//カウントが一定数、または特定ボタンで遷移
		if ((g_FCount == FADE_COUNT || GetGamepadTrigger(BUTTON_START,0) || GetGamepadTrigger(BUTTON_A, 0) || GetKeyboardTrigger(DIK_RETURN) ) && bFade == FADE_NONE && g_nLogoScreenMode > 0)
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
		if (nCnt == 0 || g_aLogo[nCnt - 1].bUse == true)
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
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
		}
	}
}