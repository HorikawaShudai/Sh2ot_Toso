//======================================================================================
//
// スタミナ処理[title.cpp]
// Author:
//
//======================================================================================
#include "stamina.h"
#include "player.h"

//**********************************************
//マクロ定義
//**********************************************
#define NUM_TEX			(1)			// テクスチャの数

#define STAMINA_WIDTH	(400.0f)	// スタミナの幅(スタミナの最大値)
#define STAMINA_HEIGHT	(10.0f)		// スタミナの高さ

#define DEC_SPEED		(2.0f)		// スタミナの減るスピード
#define RECOVERY_SPEED	(0.7f)		// スタミナの回復スピード
#define TIRED_VALUE		(150)		// 赤ゲージに入る数値

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
void StaminaIAD(int nCntStamina);								//スタミナの増減

//**********************************************
//グローバル変数
//**********************************************
LPDIRECT3DTEXTURE9 g_apTextureStamina[NUM_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStamina = NULL;			//頂点バッファへのポインタ

Stamina g_aStamina[NUM_PLAYER];					//スタミナ情報

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
		g_aStamina[nCntStamina].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 700.0f, 0.0f);			//位置
		g_aStamina[nCntStamina].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);						//色
		g_aStamina[nCntStamina].nFalseTime = 0;													//スタミナが使われていないときのカウント
		g_aStamina[nCntStamina].fStamina = STAMINA_WIDTH;										//スタミナ
		g_aStamina[nCntStamina].bUse = false;													//使っていない状態
	}

	//テクスチャ読み込み
	for (nCntStamina = 0; nCntStamina < NUM_TEX; nCntStamina++)
	{
		D3DXCreateTextureFromFile(pDevice, c_apStaminaTexName[nCntStamina], &g_apTextureStamina[nCntStamina]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TEX,
		D3DUSAGE_WRITEONLY, { FVF_VERTEX_2D }, D3DPOOL_MANAGED,
		&g_pVtxBuffStamina,
		NULL);
	
	InitStaminaGauge();			//スタミナゲージ
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

	for (int nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureStamina[nCntTitle]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}
}

//============================================================================
// スタミナのセット処理
//============================================================================
void SetStamina(D3DXVECTOR3 pos)
{
	for (int nCntStamina = 0; nCntStamina < 128; nCntStamina++)
	{
		if (g_aStamina[nCntStamina].bUse == false)
		{
			g_aStamina[nCntStamina].pos = pos;
		}
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

	//Player *pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStamina = 0; nCntStamina < NUM_PLAYER; nCntStamina++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fStamina,	g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fStamina,	g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fStamina,	g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fStamina,	g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);

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

	for (int nCntStamina = 0; nCntStamina < NUM_PLAYER; nCntStamina++)
	{
		if (pPlayer->bUse == true/* && g_aStamina[nCntStamina].bUse == true*/)
		{//使われていた場合
			//スタミナの増減
			StaminaIAD(nCntStamina);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fStamina, g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fStamina, g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fStamina, g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fStamina, g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);

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
void StaminaIAD(int nCntStamina)
{
	//プレイヤー情報の取得
	Player *pPlayer = GetPlayer();

	//プレイヤーの状態がダッシュ状態の場合
	if (pPlayer->MoveState == PLAYER_MOVESTATE_DASH)
	{
		g_aStamina[nCntStamina].fStamina -= 1.5f;			//スタミナを減らす

		g_aStamina[nCntStamina].col.a = 0.5f;				//スタミナゲージを表示
	}
	else if(g_aStamina[nCntStamina].fStamina <= STAMINA_WIDTH)
	{//スタミナが減っていた場合

		g_aStamina[nCntStamina].fStamina += 0.7f;			//スタミナを回復する


		if (g_aStamina[nCntStamina].fStamina < TIRED_VALUE)
		{
			g_aStamina[nCntStamina].col.r = 1.0f;
		}

		if (g_aStamina[nCntStamina].fStamina > TIRED_VALUE)
		{
			g_aStamina[nCntStamina].col.r = 0.5f;

			//通常状態にする
			pPlayer->MoveState = PLAYER_MOVESTATE_NORMAL;
		}
	}

	//疲労状態以外の場合
	if (pPlayer->MoveState != PLAYER_MOVESTATE_FATIGE && g_aStamina[nCntStamina].fStamina >= STAMINA_WIDTH)
	{
		//カウントを進める
		g_aStamina[nCntStamina].nFalseTime++;

		if (g_aStamina[nCntStamina].nFalseTime > 120)
		{
			g_aStamina[nCntStamina].col.a -= 0.01f;			//a値を減らす
		}
	}

	//スタミナゲージが0以下に行かないように
	if (g_aStamina[nCntStamina].fStamina <= 0.0f)
	{
		g_aStamina[nCntStamina].fStamina = 0.0f;

		//疲労状態にする
		pPlayer->MoveState = PLAYER_MOVESTATE_FATIGE;
	}

	//色のが0.0f以下、1.0f以上行かないように
	if (g_aStamina[nCntStamina].col.a <= 0.0f)
	{//0.0f以下
		g_aStamina[nCntStamina].col.a = 0.0f;

		g_aStamina[nCntStamina].nFalseTime = 0;
	}
	else if (g_aStamina[nCntStamina].col.a >= 1.0f)
	{//1.0f以上
		g_aStamina[nCntStamina].col.a = 1.0f;
	}
}