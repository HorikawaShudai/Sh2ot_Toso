//======================================================================================
//
// スタミナ処理[title.cpp]
// Author:
//
//======================================================================================
#include "stamina.h"
#include "player.h"
#include "PlayNumberSelect.h"

//**********************************************
//マクロ定義
//**********************************************
#define NUM_TEX			(1)			// テクスチャの数

#define STAMINA_WIDTH	(400.0f)	// スタミナの幅(スタミナの最大値)
#define STAMINA_HEIGHT	(10.0f)		// スタミナの高さ

#define DEC_SPEED		(2.0f)		// スタミナの減るスピード
#define RECOVERY_SPEED	(0.7f)		// スタミナの回復スピード
#define TIRED_VALUE		(STAMINA_WIDTH / 3)		// 赤ゲージに入る数値

//**********************************************
// テクスチャ名
//**********************************************
const char *c_apStaminaTexName[NUM_TEX] =
{
	"Data\\TEXTURE\\Stamina.png",			//スタミナゲージ
};

//**********************************************
//プロトタイプ宣言
//**********************************************
void InitStaminaGauge(void);						//スタミナゲージの初期化

void UpdateStaminaGauge(void);						//スタミナゲージの更新
void StaminaIAD(int nCntStamina, Player *pPlayer);								//スタミナの増減

//**********************************************
//グローバル変数
//**********************************************
LPDIRECT3DTEXTURE9 g_apTextureStamina[NUM_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStamina = NULL;			//頂点バッファへのポインタ

Stamina g_aStamina[NUM_PLAYER];					//スタミナ情報
float g_fStaminaSize;

//============================================================================
//初期化処理
//============================================================================
void InitStamina(void)
{
	//変数宣言
	int nCntStamina;

	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//グローバル宣言の初期化
	for (nCntStamina = 0; nCntStamina < NUM_PLAYER; nCntStamina++)
	{
		g_aStamina[nCntStamina].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
		g_aStamina[nCntStamina].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);		//色
		g_aStamina[nCntStamina].nFalseTime = 0;									//スタミナが使われていないときのカウント
		g_aStamina[nCntStamina].fGaugeSize = 0.0f;								//スタミナ
		g_aStamina[nCntStamina].bUse = false;									//使っていない状態
		g_aStamina[nCntStamina].bFatige = false;								//疲れていない状態
	}

	g_fStaminaSize = 0.0f;

	//テクスチャ読み込み
	for (nCntStamina = 0; nCntStamina < NUM_TEX; nCntStamina++)
	{
		D3DXCreateTextureFromFile(pDevice, c_apStaminaTexName[nCntStamina], &g_apTextureStamina[nCntStamina]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TEX * NUM_PLAYER,
		D3DUSAGE_WRITEONLY, { FVF_VERTEX_2D }, D3DPOOL_MANAGED,
		&g_pVtxBuffStamina,
		NULL);
	
	InitStaminaGauge();			//スタミナゲージ

	//SetStamina(D3DXVECTOR3(640.0f, 150.0f, 0.0f));

	//SetStamina(D3DXVECTOR3(640.0f, 650.0f, 0.0f));
}

//============================================================================
//終了処理
//============================================================================
void UninitStamina(void)
{
	for (int nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
	{
		//テクスチャの破棄
		if (g_apTextureStamina[nCntTitle] != NULL)
		{
			g_apTextureStamina[nCntTitle]->Release();
			g_apTextureStamina[nCntTitle] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffStamina != NULL)
	{
		g_pVtxBuffStamina->Release();
		g_pVtxBuffStamina = NULL;
	}
}

//============================================================================
//更新処理
//============================================================================
void UpdateStamina(void)
{
	//選択処理
	UpdateStaminaGauge();
}

//============================================================================
//描画処理
//============================================================================
void DrawStamina(void)
{
	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStamina, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureStamina[0]);

	for (int nCntStamina = 0; nCntStamina < NUM_PLAYER; nCntStamina++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntStamina * 4, 2);
	}
}

//************************************
//初期化処理内
//************************************
// スタミナゲージの初期化
void InitStaminaGauge(void)
{
	//頂点情報へのポインタ
	VERTEX_2D * pVtx;

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStamina = 0; nCntStamina < PlayNumber.CurrentSelectNumber + 1; nCntStamina++)
	{
		switch (nCntStamina)
		{//人数によって変わるスタミナの位置、大きさを設定
		case 0:	//1～4人
			if (PlayNumber.CurrentSelectNumber + 1 == 1)
			{//プレイ人数が1人の時
				g_aStamina[nCntStamina].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 700.0f, 0.0f);

				g_fStaminaSize = STAMINA_WIDTH;
			}
			else if (PlayNumber.CurrentSelectNumber + 1 == 2)
			{//プレイ人数が2人の時
				g_aStamina[nCntStamina].pos = D3DXVECTOR3((SCREEN_WIDTH * 0.5f) * 0.5, 700.0f, 0.0f);

				g_fStaminaSize = STAMINA_WIDTH * 0.65f;
			}
			else if (PlayNumber.CurrentSelectNumber + 1 == 3 || PlayNumber.CurrentSelectNumber + 1 == 4)
			{//プレイ人数が3人(4人)の時
				g_aStamina[nCntStamina].pos = D3DXVECTOR3((SCREEN_WIDTH * 0.5f) * 0.5, SCREEN_HEIGHT * 0.5f, 0.0f);

				g_fStaminaSize = STAMINA_WIDTH * 0.65f;
			}
			break;

		case 1:	//2～4人
			if (PlayNumber.CurrentSelectNumber + 1 == 2)
			{//プレイ人数が2人の時
				g_aStamina[nCntStamina].pos = D3DXVECTOR3((SCREEN_WIDTH * 0.5f) + (SCREEN_WIDTH * 0.25f), 700.0f, 0.0f);
			}
			else if (PlayNumber.CurrentSelectNumber + 1 == 3 || PlayNumber.CurrentSelectNumber + 1 == 4)
			{//プレイ人数が3人の時
				g_aStamina[nCntStamina].pos = D3DXVECTOR3((SCREEN_WIDTH * 0.5f) + (SCREEN_WIDTH * 0.25f), SCREEN_HEIGHT * 0.5f, 0.0f);
			}
			break;

		case 2:	//3～4人
			//プレイ人数が3人の時
				g_aStamina[nCntStamina].pos = D3DXVECTOR3((SCREEN_WIDTH * 0.5f) * 0.5f, 700.0f, 0.0f);
			break;

		case 3:	//4人
			//プレイ人数が3人の時
				g_aStamina[nCntStamina].pos = D3DXVECTOR3((SCREEN_WIDTH * 0.5f) + (SCREEN_WIDTH * 0.25f), 700.0f, 0.0f);
			break;
		}

		//スタミナゲージの大きさを代入
		g_aStamina[nCntStamina].fGaugeSize = g_fStaminaSize;
		
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fGaugeSize,	g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fGaugeSize,	g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fGaugeSize,	g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fGaugeSize,	g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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

		pVtx += 4;			//頂点情報を4つ分ずらす
	}

	//頂点バッファのアンロック
	g_pVtxBuffStamina->Unlock();
}

//************************************
//更新処理内の処理
//************************************
// スタミナの動き
void UpdateStaminaGauge(void)
{
	//頂点情報へのポインタ
	VERTEX_2D * pVtx;
	
	//プレイヤー情報の取得
	Player *pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStamina = 0; nCntStamina < NUM_PLAYER; nCntStamina++, pPlayer++)
	{
		if (pPlayer->bUse == true/* && g_aStamina[nCntStamina].bUse == true*/)
		{//使われていた場合

			//スタミナの増減
			StaminaIAD(nCntStamina, pPlayer);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fGaugeSize, g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fGaugeSize, g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fGaugeSize, g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fGaugeSize, g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(g_aStamina[nCntStamina].col.r, g_aStamina[nCntStamina].col.g, g_aStamina[nCntStamina].col.b, g_aStamina[nCntStamina].col.a);
			pVtx[1].col = D3DXCOLOR(g_aStamina[nCntStamina].col.r, g_aStamina[nCntStamina].col.g, g_aStamina[nCntStamina].col.b, g_aStamina[nCntStamina].col.a);
			pVtx[2].col = D3DXCOLOR(g_aStamina[nCntStamina].col.r, g_aStamina[nCntStamina].col.g, g_aStamina[nCntStamina].col.b, g_aStamina[nCntStamina].col.a);
			pVtx[3].col = D3DXCOLOR(g_aStamina[nCntStamina].col.r, g_aStamina[nCntStamina].col.g, g_aStamina[nCntStamina].col.b, g_aStamina[nCntStamina].col.a);
		}

		pVtx += 4;			//頂点情報を4つ分ずらす
	}

	//頂点バッファのアンロック
	g_pVtxBuffStamina->Unlock();
}

// スタミナの増減処理
void StaminaIAD(int nCntStamina, Player *pPlayer)
{
	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//プレイヤーの状態がダッシュ状態の場合
	if (pPlayer->MoveState == PLAYER_MOVESTATE_DASH)
	{
		if (PlayNumber.CurrentSelectNumber /*+ 1*/ == 1)
		{//1人プレイの場合
			g_aStamina[nCntStamina].fGaugeSize -= 1.5f;			//スタミナを減らす
		}
		else if (PlayNumber.CurrentSelectNumber /*+ 1*/ >= 2)
		{//複数人の場合
			g_aStamina[nCntStamina].fGaugeSize -= (1.5f * 0.5f);			//スタミナを減らす
		}

		g_aStamina[nCntStamina].col.a = 0.5f;				//スタミナゲージを表示
	}
	else if(g_aStamina[nCntStamina].fGaugeSize <= g_fStaminaSize)
	{//スタミナが減っていた場合
		if (PlayNumber.CurrentSelectNumber /*+ 1*/ == 1)
		{//1人プレイの場合
			g_aStamina[nCntStamina].fGaugeSize += 0.7f;			//スタミナを回復する
		}
		else if (PlayNumber.CurrentSelectNumber /*+ 1*/ >= 2)
		{//複数人プレイの場合
			g_aStamina[nCntStamina].fGaugeSize += (0.7f * 0.5f);			//スタミナを回復する
		}
		//疲労状態の時のゲージ状態
		if (g_aStamina[nCntStamina].fGaugeSize > g_fStaminaSize / 3)
		{//疲労ゲージより回復したら
			g_aStamina[nCntStamina].col.r = 0.5f;			//色を変更する

			//通常状態にする
			pPlayer->MoveState = PLAYER_MOVESTATE_NORMAL;

			g_aStamina[nCntStamina].bFatige = false;			//疲れていない状態へ
		}
	}

	//疲労状態以外の場合
	if (pPlayer->MoveState != PLAYER_MOVESTATE_FATIGE && g_aStamina[nCntStamina].fGaugeSize >= g_fStaminaSize)
	{
		//カウントを進める
		g_aStamina[nCntStamina].nFalseTime++;

		if (g_aStamina[nCntStamina].nFalseTime > 120)
		{
			g_aStamina[nCntStamina].col.a -= 0.01f;			//a値を減らす
		}
	}

	//スタミナゲージが0以下に行かないように
	if (g_aStamina[nCntStamina].fGaugeSize <= 0.0f)
	{
		g_aStamina[nCntStamina].fGaugeSize = 0.0f;
		
		g_aStamina[nCntStamina].col.r = 1.0f;

		//疲労状態にする
		pPlayer->MoveState = PLAYER_MOVESTATE_FATIGE;
	}

	//色のが0.0f以下、1.0f以上行かないように
	if (g_aStamina[nCntStamina].col.a <= 0.0f)
	{//0.0f以下の場合
		g_aStamina[nCntStamina].col.a = 0.0f;

		g_aStamina[nCntStamina].nFalseTime = 0;

		g_aStamina[nCntStamina].bFatige = true;			//疲れている状態へ
	}
	else if (g_aStamina[nCntStamina].col.a >= 1.0f)
	{//1.0f以上
		g_aStamina[nCntStamina].col.a = 1.0f;
	}
}