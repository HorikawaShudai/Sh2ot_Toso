#include "main.h"
#include "resultUI.h"
#include "game.h"
#include "ChasePolygon.h"
#include "EscapeTutorial.h"
#include "PlayNumberSelect.h"
#include "player.h"

//マクロ定義
#define MAX_SSUI					(8)			//TUTORIALUIの最大使用数
#define NUM_SSUI					(1)			//TUTORIALUIの最大種類数

#define POS_TUTORIALUI_1_01_X		(640.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_1_01_Y		(360.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_1_01_X		(640.0f)	//「」の幅
#define SIZE_TUTORIALUI_1_01_Y		(360.0f)	//「」の高さ

#define POS_TUTORIALUI_2_01_X		(320.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_2_01_Y		(360.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_2_01_X		(320.0f)	//「」の幅
#define SIZE_TUTORIALUI_2_01_Y		(360.0f)	//「」の高さ

#define POS_TUTORIALUI_2_02_X		(960.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_2_02_Y		(360.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_2_02_X		(320.0f)	//「」の幅
#define SIZE_TUTORIALUI_2_02_Y		(360.0f)	//「」の高さ

#define POS_TUTORIALUI_34_01_X		(320.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_01_Y		(180.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_01_X		(320.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_01_Y		(180.0f)	//「」の高さ

#define POS_TUTORIALUI_34_02_X		(960.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_02_Y		(180.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_02_X		(320.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_02_Y		(180.0f)	//「」の高さ

#define POS_TUTORIALUI_34_03_X		(320.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_03_Y		(540.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_03_X		(320.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_03_Y		(180.0f)	//「」の高さ

#define POS_TUTORIALUI_34_04_X		(960.0f)	//「」のX座標の位置
#define POS_TUTORIALUI_34_04_Y		(540.0f)	//「」のY座標の位置
#define SIZE_TUTORIALUI_34_04_X		(320.0f)	//「」の幅
#define SIZE_TUTORIALUI_34_04_Y		(180.0f)	//「」の高さ

#define UP_PAPERBG01				(100.0f)	//紙を取り出すときの上昇度
#define UP_PAPERBG01_COUNTER_MAX	(100)		//紙を取り出す速さのカウンター

//テクスチャファイル名
const char *c_cpChaPolyTexname01[] =
{
	"Data\\TEXTURE\\shadow001.jpg",
};

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureChasePolygon[NUM_SSUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffChasePolygon = NULL;		//頂点バッファへのポインタ
bool bUseChasePolygon[MAX_SSUI];		//頂点バッファへのポインタ
float g_ChasePolygonColorA[MAX_SSUI];		//ポリゴンのα値
float g_ChasePolygonColorA_MAX[MAX_SSUI];		//ポリゴンのα値の最大値

//====================================================================
//タイトル画面の初期化処理
//====================================================================
void InitChasePolygon(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, c_cpChaPolyTexname01[nCntBG], &g_apTextureChasePolygon[nCntBG]);
	}

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//UIの表示設定
		bUseChasePolygon[nCntBG] = true;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffChasePolygon,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffChasePolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
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
		case 3:
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

		case 4:
		case 5:
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

		case 6:
		case 7:
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

		if (nCntBG % 2 == 0)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		}
		else
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffChasePolygon->Unlock();
}

//====================================================================
//タイトルの終了処理
//====================================================================
void UninitChasePolygon(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの破棄
		if (g_apTextureChasePolygon[nCntBG] != NULL)
		{
			g_apTextureChasePolygon[nCntBG]->Release();
			g_apTextureChasePolygon[nCntBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffChasePolygon != NULL)
	{
		g_pVtxBuffChasePolygon->Release();
		g_pVtxBuffChasePolygon = NULL;
	}
}

//====================================================================
//タイトル画面の更新処理
//====================================================================
void UpdateChasePolygon(void)
{
	float ColorA[MAX_SSUI];
	for (int nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		if (g_ChasePolygonColorA[nCntBG] > g_ChasePolygonColorA_MAX[nCntBG])
		{
			ColorA[nCntBG] = (g_ChasePolygonColorA_MAX[nCntBG] * 2 - g_ChasePolygonColorA[nCntBG]) / g_ChasePolygonColorA_MAX[nCntBG];
		}
		else
		{
			ColorA[nCntBG] = g_ChasePolygonColorA[nCntBG] / g_ChasePolygonColorA_MAX[nCntBG];
		}
	}

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffChasePolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, ColorA[nCntBG] * 0.75f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, ColorA[nCntBG] * 0.75f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, ColorA[nCntBG] * 0.75f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, ColorA[nCntBG] * 0.75f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffChasePolygon->Unlock();
}

//====================================================================
//タイトル画面の描画処理
//====================================================================
void DrawChasePolygon(int nCnt)
{
	Player *pPlayer = GetPlayer();
	pPlayer += nCnt;
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffChasePolygon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureChasePolygon[0]);

		if (pPlayer->bEnemyLeft == true && pPlayer->bEnemyRight == true)
		{
			if (bUseChasePolygon[nCntBG] == true && (nCntBG == nCnt * 2 || nCntBG == nCnt * 2 + 1))
			{
				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
					4 * nCntBG,						//プリミティブ(ポリゴン)数
					2);
			}
		}
		else if (pPlayer->bEnemyLeft == true)
		{
			if (bUseChasePolygon[nCntBG] == true && (nCntBG == nCnt * 2 + 1))
			{
				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
					4 * nCntBG,						//プリミティブ(ポリゴン)数
					2);
			}
		}
		else if (pPlayer->bEnemyRight == true)
		{
			if (bUseChasePolygon[nCntBG] == true && (nCntBG == nCnt * 2))
			{
				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
					4 * nCntBG,						//プリミティブ(ポリゴン)数
					2);
			}
		}
	}

	//aブレンディングを通常に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//====================================================================
//ランキングUIの設定処理
//====================================================================
void SetColorChasePolygon(float a, int nCnt)
{
	g_ChasePolygonColorA[nCnt * 2] = a;
	g_ChasePolygonColorA[nCnt * 2 + 1] = a;
}

//====================================================================
//ランキングUIの設定処理
//====================================================================
void SetColorChasePolygonMAX(float a, int nCnt)
{
	g_ChasePolygonColorA_MAX[nCnt * 2] = a / 2;
	g_ChasePolygonColorA_MAX[nCnt * 2 + 1] = a / 2;
}