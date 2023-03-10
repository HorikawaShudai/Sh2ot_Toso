//======================================================================================
//
// プレイ人数選択の処理[PlayNumberselect.cpp]
// Author:小笠原　彪
//
//======================================================================================
#include <stdio.h>
#include "PlayNumberSelect.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "debugproc.h"
#include "camera.h"
#include "playerBG.h"
#include "light.h"
#include "objectBG.h"
#include "stage.h"
#include "object00.h"
#include "ObjectWall.h"
#include "sound.h"
#include "Exit.h"

//***********************************
//マクロ定義
//***********************************
#define MAX_TEX			(5)				//テクスチャの最大数
#define NUM_POLY		(NUM_PLAYNUMBER)	//ポリゴンの数
#define MAX_BUFF		(2)				//バッファの最大数

#define POS_X			(350.0f)		//項目の位置(X)
#define POS_Y			(200.0f)		//項目の位置(Y)
#define SPACE_X			(200.0f)		//項目同士の間の広さ
#define WIDTH_SIZE		(70.0f)			//項目の大きさ(X)
#define HEIGHT_SIZE		(70.0f)			//項目の大きさ(Y)

//***********************************
//テクスチャファイル名
//***********************************
const char *c_apFilenamePlayNumberSelect[MAX_TEX] =
{
	"data\\TEXTURE\\PLAYMODE\\PlayMode00.png",		//選択アイコン(1人)
	"data\\TEXTURE\\PLAYMODE\\PlayMode01.png",		//選択アイコン(2人)
	"data\\TEXTURE\\PLAYMODE\\PlayMode02.png",		//選択アイコン(3人)
	"data\\TEXTURE\\PLAYMODE\\PlayMode03.png",		//選択アイコン(4人)
	"data\\TEXTURE\\RANKING\\Osumi00.png",			//墨のフレーム
};

//***********************************
//プロトタイプ宣言
//***********************************
//初期化
void InitPlaySelectIcon(void);
void InitPlaySelectBg(void);
//更新
void PlayerSelect(void);
//描画
void DrawPlayNumberSelectIcon(void);
void DrawPlayNumberSelectBg(void);

//3D背景用
void Init3DSelect(void);
void Uninit3DSelect(void);
void Update3DSelect(void);
void Draw3DSelect(void);

//==================
//グローバル定義
//==================
LPDIRECT3DTEXTURE9 g_apTexPlayNumberSelect[MAX_TEX] = {};				//テクスチャへの
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayNumberSelect[MAX_BUFF] = {};			//頂点バッファへの
D3DXCOLOR g_PaleColorPns;
D3DXCOLOR g_NormalColorPns;
PlayNumberSelect g_PlayNumberSelect;

//========================================================================
// モード選択の初期化処理
//========================================================================
void InitPlayNumberSelect(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	for (int nCntTexture = 0; nCntTexture < MAX_TEX; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, c_apFilenamePlayNumberSelect[nCntTexture], &g_apTexPlayNumberSelect[nCntTexture]);
	}

	//構造体の初期化
	g_PlayNumberSelect.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PlayNumberSelect.CurrentSelectNumber = 0;
	g_PlayNumberSelect.bUse = true;
	g_PlayNumberSelect.bPush = false;

	//グローバル宣言の初期化
	g_PaleColorPns = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	g_NormalColorPns = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファの生成[0]
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYNUMBER,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
		&g_pVtxBuffPlayNumberSelect[0], NULL);

	//頂点バッファの生成[1]
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
		&g_pVtxBuffPlayNumberSelect[1], NULL);

	InitPlaySelectIcon();

	//3D
	Init3DSelect();

	//背景の初期化
	InitPlaySelectBg();
}

//========================================================================
// モード選択の終了処理
//========================================================================
void UninitPlayNumberSelect(void)
{
	//変数宣言
	int nCntStage;			//forカウント用

	for (nCntStage = 0; nCntStage < MAX_TEX; nCntStage++)
	{
		//テクスチャの破棄
		if (g_apTexPlayNumberSelect[nCntStage] != NULL)
		{
			g_apTexPlayNumberSelect[nCntStage]->Release();
			g_apTexPlayNumberSelect[nCntStage] = NULL;
		}
	}
	for (int nCntBuff = 0; nCntBuff < MAX_BUFF; nCntBuff++)
	{
		//頂点バッファの破棄
		if (g_pVtxBuffPlayNumberSelect[nCntBuff] != NULL)
		{
			g_pVtxBuffPlayNumberSelect[nCntBuff]->Release();
			g_pVtxBuffPlayNumberSelect[nCntBuff] = NULL;
		}
	}
	

	//3D
	Uninit3DSelect();
}

//========================================================================
// モード選択の更新処理
//========================================================================
void UpdatePlayNumberSelect(void)
{
	//プレイ人数の情報取得

	//ステージ選択の関数
	PlayerSelect();

	//3D
	Update3DSelect();

	//デバッグ表示
	PrintDebugProc("選択 【←】【→】\n");
	PrintDebugProc("決定 【ENTER】\n");
	PrintDebugProc("戻る 【B】\n");
}

//========================================================================
// モード選択の描画処理
//========================================================================
void DrawPlayNumberSelect(void)
{
	//プレイ人数の情報取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//3D
	Draw3DSelect();

	//選択背景の描画処理
	DrawPlayNumberSelectBg();

	//選択アイコンの初期化
	DrawPlayNumberSelectIcon();
}

//========================================================================
// モード選択アイコンの初期化処理
//========================================================================
void InitPlaySelectIcon(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayNumberSelect[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStage = 0; nCntStage < NUM_PLAYNUMBER; nCntStage++)
	{
		if (nCntStage == 0)
		{
			g_PlayNumberSelect.pos = D3DXVECTOR3(POS_X, POS_Y, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x - WIDTH_SIZE, g_PlayNumberSelect.pos.y - HEIGHT_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x + WIDTH_SIZE, g_PlayNumberSelect.pos.y - HEIGHT_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x - WIDTH_SIZE, g_PlayNumberSelect.pos.y + HEIGHT_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x + WIDTH_SIZE, g_PlayNumberSelect.pos.y + HEIGHT_SIZE, 0.0f);
			//rhwの設定
			for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
			{
				pVtx[nCntrhw].rhw = 1.0f;
			}
			//頂点カラー(0.0f〜1.0f内で設定)
			for (int nCntcol = 0; nCntcol < 4; nCntcol++)
			{
				pVtx[nCntcol].col = g_NormalColorPns;
			}
			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;					//頂点データを4つ分ずらす
		}
		else
		{
			g_PlayNumberSelect.pos = D3DXVECTOR3(POS_X + SPACE_X * nCntStage, POS_Y, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x - WIDTH_SIZE, g_PlayNumberSelect.pos.y - HEIGHT_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x + WIDTH_SIZE, g_PlayNumberSelect.pos.y - HEIGHT_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x - WIDTH_SIZE, g_PlayNumberSelect.pos.y + HEIGHT_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x + WIDTH_SIZE, g_PlayNumberSelect.pos.y + HEIGHT_SIZE, 0.0f);
			//rhwの設定
			for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
			{
				pVtx[nCntrhw].rhw = 1.0f;
			}
			//頂点カラー(0.0f〜1.0f内で設定)
			for (int nCntcol = 0; nCntcol < 4; nCntcol++)
			{
				pVtx[nCntcol].col = g_PaleColorPns;
			}
			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;					//頂点データを4つ分ずらす
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayNumberSelect[0]->Unlock();
}

//========================================================================
// モード選択画面の背景の初期化処理
//========================================================================
void InitPlaySelectBg(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayNumberSelect[1]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
	{
		pVtx[nCntrhw].rhw = 1.0f;
	}

	//頂点カラー(0.0f〜1.0f内で設定)
	for (int nCntcol = 0; nCntcol < 4; nCntcol++)
	{
		pVtx[nCntcol].col = g_NormalColorPns;
	}

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
	//頂点バッファをアンロックする
	g_pVtxBuffPlayNumberSelect[1]->Unlock();
}

//========================================================================
// モード選択選択アイコンの描画処理
//========================================================================
void DrawPlayNumberSelectIcon(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayNumberSelect[0], 0,
		sizeof(VERTEX_2D));			//頂点情報構造体のサイズ

	for (int nCntStage = 0; nCntStage < NUM_POLY; nCntStage++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexPlayNumberSelect[nCntStage]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
			nCntStage * 4,			//描画する最初のインデックス
			2);						//プリミティブ(ポリゴン)数
	}
}

//========================================================================
// モード選択選択アイコンの描画処理
//========================================================================
void DrawPlayNumberSelectBg(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayNumberSelect[1], 0,
		sizeof(VERTEX_2D));			//頂点情報構造体のサイズ
	
	//テクスチャの設定
	pDevice->SetTexture(0, g_apTexPlayNumberSelect[4]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
		0,			//描画する最初のインデックス
		2);						//プリミティブ(ポリゴン)数
}

//========================================================================
// モード選択の選択処理
//========================================================================
void PlayerSelect(void)
{
	//フェード情報の取得
	FADE pFade = GetFade();

	//プレイ人数の情報取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_D) == true || GetGamepadTrigger(BUTTON_RIGHT, 0) == true || GetGamepad_LStick_Trigger(0, LSTICK_RIGHT) == true)
		{
			//選択音
			PlaySound(SOUND_LABEL_CHOICE);

			//頂点バッファをロック
			g_pVtxBuffPlayNumberSelect[0]->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += g_PlayNumberSelect.CurrentSelectNumber * 4;

			//頂点カラーの設定
			pVtx[0].col = g_PaleColorPns;
			pVtx[1].col = g_PaleColorPns;
			pVtx[2].col = g_PaleColorPns;
			pVtx[3].col = g_PaleColorPns;

			//頂点バッファをアンロックする
			g_pVtxBuffPlayNumberSelect[0]->Unlock();

			//現在地を先に
			g_PlayNumberSelect.CurrentSelectNumber = (g_PlayNumberSelect.CurrentSelectNumber + 1) % NUM_PLAYNUMBER;

			//頂点バッファをロック
			g_pVtxBuffPlayNumberSelect[0]->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += g_PlayNumberSelect.CurrentSelectNumber * 4;

			//頂点カラーの設定
			pVtx[0].col = g_NormalColorPns;
			pVtx[1].col = g_NormalColorPns;
			pVtx[2].col = g_NormalColorPns;
			pVtx[3].col = g_NormalColorPns;

			//頂点バッファをアンロックする
			g_pVtxBuffPlayNumberSelect[0]->Unlock();
		}
		else if (GetKeyboardTrigger(DIK_A) == true || GetGamepadTrigger(BUTTON_LEFT, 0) == true || GetGamepad_LStick_Trigger(0, LSTICK_LEFT) == true)
		{
			//選択音
			PlaySound(SOUND_LABEL_CHOICE);

			//頂点バッファをロック
			g_pVtxBuffPlayNumberSelect[0]->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += g_PlayNumberSelect.CurrentSelectNumber * 4;

			//頂点カラーの設定
			pVtx[0].col = g_PaleColorPns;
			pVtx[1].col = g_PaleColorPns;
			pVtx[2].col = g_PaleColorPns;
			pVtx[3].col = g_PaleColorPns;

			//頂点バッファをアンロックする
			g_pVtxBuffPlayNumberSelect[0]->Unlock();

			//現在地を前へ
			g_PlayNumberSelect.CurrentSelectNumber = (g_PlayNumberSelect.CurrentSelectNumber - 1 + NUM_PLAYNUMBER) % NUM_PLAYNUMBER;

			//頂点バッファをロック
			g_pVtxBuffPlayNumberSelect[0]->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * g_PlayNumberSelect.CurrentSelectNumber;

			//頂点カラーの設定
			pVtx[0].col = g_NormalColorPns;
			pVtx[1].col = g_NormalColorPns;
			pVtx[2].col = g_NormalColorPns;
			pVtx[3].col = g_NormalColorPns;

			//頂点バッファをアンロックする
			g_pVtxBuffPlayNumberSelect[0]->Unlock();
		}

		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_START, 0) || GetGamepadTrigger(BUTTON_A, 0))
		{//決定キー(ENTERキー)が押された

			//決定音
			PlaySound(SOUND_LABEL_ENTER);

			if (g_PlayNumberSelect.CurrentSelectNumber >= 0 && g_PlayNumberSelect.CurrentSelectNumber < PLAYNUMBER_MAX)
			{
				g_PlayNumberSelect.CurrentSelectNumber = g_PlayNumberSelect.CurrentSelectNumber + 1;			//プレイ人数に合わせるため

				SetFade(MODE_TUTORIAL);			//モードの設定(ゲーム画面に移行)
			}
			else if (g_PlayNumberSelect.CurrentSelectNumber == PLAYNUMBER_MAX)
			{
				g_PlayNumberSelect.CurrentSelectNumber = 4;			//プレイ人数に合わせるため

				g_PlayNumberSelect.bUse = false;
			}
			g_PlayNumberSelect.bPush = true;
		}
		else if (GetKeyboardTrigger(DIK_B) || GetGamepadTrigger(BUTTON_B, 0))
		{
			SetFade(MODE_TITLE);			//モードの設定(ゲーム画面に移行)
		}
	}
}


//========================================================================
//3D用
//========================================================================
//初期化
void Init3DSelect(void)
{
	InitCamera();

	InitLight();

	InitPlayerBG();

	InitExit();

	//オブジェクトの初期化
	InitObject00();

	//タイトル用マップの初期化
	InitObjectBG();
	InitObjectWall();

	//ステージの読み込み
	SetStage(2);

	SetExit(D3DXVECTOR3(-80.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 0, 0);
	SetExit(D3DXVECTOR3(80.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 0, 0);
	SetExit(D3DXVECTOR3(0.0f, 100.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 1, 0);
	SetExit(D3DXVECTOR3(-70.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 2, 0);
	SetExit(D3DXVECTOR3(70.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 3, 0);
}

//終了
void Uninit3DSelect(void)
{
	UninitCamera();

	UninitLight();

	UninitPlayerBG();

	UninitExit();

	//オブジェクトの終了
	UninitObject00();

	//タイトル用オブジェクトの終了
	UninitObjectBG();
	UninitObjectWall();
}

//更新
void Update3DSelect(void)
{
	UpdateCamera();

	UpdateLight();

	UpdatePlayerBG();

	UpdateExit();

	//オブジェクトの更新
	UpdateObject00();

	//タイトル用オブジェクトの更新
	UpdateObjectBG();
	UpdateObjectWall();
}

//描画
void Draw3DSelect(void)
{
	SetCamera(4);

	DrawPlayerBG();

	DrawExit();

	//オブジェクトの描画
	DrawObject00();

	//タイトル用オブジェクトの描画
	DrawObjectBG();
	DrawObjectWall();
}

//========================================================================
// モード選択情報の取得
//========================================================================
PlayNumberSelect GetPlayNumberSelect(void)
{
	return g_PlayNumberSelect;
}