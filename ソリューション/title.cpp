//======================================================================================
//
// タイトル処理[title.cpp]
// Author:
//
//======================================================================================
#include "main.h"
#include "Title.h"
#include "input.h"
#include "Fade.h"
#include "debugproc.h"
#include "camera.h"
#include "light.h"
#include "SpotLight.h"
#include "meshdome.h"
#include "stage.h"
#include "objectBG.h"
#include "meshcylinder.h"
#include "object00.h"
#include "Billboard.h"
#include "Thunder.h"
#include "effect.h"
#include "sound.h"
#include "exit.h"

//**********************************************
//マクロ定義
//**********************************************
#define NUM_TEX			(3)		// テクスチャの数
#define NUM_TITLEPOS	(3)		//
#define NUM_SELECT		(2)		//選択欄の数
#define CAMERA_FADEPOS	(370.0f)//画面遷移するカメラ位置(Z軸)

#define POS_STAGESELECT_BG_X		(200.0f)	//「ステージセレクト」のX座標の位置
#define POS_STAGESELECT_BG_Y		(500.0f)	//「ステージセレクト」のY座標の位置
#define SIZE_STAGESELECT_BG_X		(150.0f)	//「ステージセレクト」の幅
#define SIZE_STAGESELECT_BG_Y		(70.0f)		//「ステージセレクト」の高さ

#define POS_RANKING_BG_X			(170.0f)	//「ランキング」のX座標の位置
#define POS_RANKING_BG_Y			(600.0f)	//「ランキング」のY座標の位置
#define SIZE_RANKING_BG_X			(120.0f)	//「ランキング」の幅
#define SIZE_RANKING_BG_Y			(50.0f)		//「ランキング」の高さ

//**********************************************
// テクスチャ名
//**********************************************
const char *c_apTitleTexName[NUM_TEX] =
{
	"Data\\TEXTURE\\TITLE\\Tousou_logo.png",		//透走ロゴ
	"Data\\TEXTURE\\TITLE\\TitleSelect02.png",		//スタート文字
	"Data\\TEXTURE\\TITLE\\TitleSelect03.png",		//セレクト文字
};

//**********************************************
//プロトタイプ宣言
//**********************************************
void InitTitleBg(int nCntTitle);							//タイトル背景
void InitTitleLogo(int nCntTitle);							//タイトルロゴ
void InitTitleSelect0(int nCntTitle);						//タイトルセレクト(モード)
void InitTitleSelect1(int nCntTitle);						//タイトルセレクト(ランキング)
//3D背景用
void Init3DTitle(void);
void Uninit3DTitle(void);
void Update3DTitle(void);
void Draw3DTitle(void);

void UpdateTitleSelect(void);									//タイトルセレクト(ランキング)

//**********************************************
//グローバル変数
//**********************************************
LPDIRECT3DTEXTURE9 g_apTextureTitle[NUM_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			//頂点バッファへのポインタ

D3DXVECTOR3 g_aTitlePos[NUM_TITLEPOS];			//タイトル画面に配置される場所
int g_CurrentNumberTitle;						//現在選択されている番号(モード選択用)
bool bPress;
int g_nFadeCnt;
bool bTitle;

//============================================================================
//初期化処理
//============================================================================
void InitTitle(void)
{
	//変数宣言
	int nCntTitle;

	//デバイスへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//グローバル宣言の初期化
	for (nCntTitle = 0; nCntTitle < NUM_TITLEPOS; nCntTitle++)
	{
		g_aTitlePos[nCntTitle] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_CurrentNumberTitle = 0;

	bPress = false;
	g_nFadeCnt = 0;
	bTitle = false;

	for (nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
	{//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, c_apTitleTexName[nCntTitle], &g_apTextureTitle[nCntTitle]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TEX,
		D3DUSAGE_WRITEONLY, { FVF_VERTEX_2D }, D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//各処理の初期化
	for (nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			InitTitleLogo(nCntTitle);		//タイトルロゴ
			break;
		case 1:
			InitTitleSelect0(nCntTitle);	//選択欄(モード選択)
			break;
		case 2:
			InitTitleSelect1(nCntTitle);	//選択欄(ランキング)
			break;
		}
	}

	//3D
	Init3DTitle();

	//タイトルのBGM(雨)
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

//============================================================================
//終了処理
//============================================================================
void UninitTitle(void)
{
	//曲を止める
	StopSound();

	for (int nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
	{
		//テクスチャの破棄
		if (g_apTextureTitle[nCntTitle] != NULL)
		{
			g_apTextureTitle[nCntTitle]->Release();
			g_apTextureTitle[nCntTitle] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//3D
	Uninit3DTitle();
}

//============================================================================
//更新処理
//============================================================================
void UpdateTitle(void)
{
	Camera *pCamera = GetCamera();
	THUNDER aThunder = GetThunder();

	pCamera += 4;

	if (bTitle == false && bPress ==false)
	{
		g_nFadeCnt++;
		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadPress(BUTTON_START, 0) || GetGamepadTrigger(BUTTON_A, 0))
		{//決定キー(ENTERキー)が押された
			g_nFadeCnt = 219;

			//選択音
			PlaySound(SOUND_LABEL_ENTER);
		}
		else if (g_nFadeCnt == 220)
		{
			SetThunder();
			bTitle = true;
		}
	}
	//3D
	Update3DTitle();

	if (aThunder.nType == THUNDER_NONE && bTitle == true)
	{
		//選択処理
		UpdateTitleSelect();
	}

	FADE pFade = GetFade();

	if (pFade == FADE_NONE)
	{
		if (g_CurrentNumberTitle == 0 && pCamera->posV.z >= CAMERA_FADEPOS)
		{//現在の選択番号が0の場合
			SetFade(MODE_NUMBERSELECT);			//モードの設定(モード選択画面に移行)
		}
		else if (g_CurrentNumberTitle == 1 && pCamera->posV.z >= CAMERA_FADEPOS)
		{//現在の選択番号が1の場合
			SetFade(MODE_RANKING);		//モードの設定(ランキング画面に移行)
		}
	}

	//デバッグ表示
	PrintDebugProc("%f\n", pCamera->posV.z);
	PrintDebugProc("選択 【↑】【↓】\n");
	PrintDebugProc("決定 【ENTER】\n");
}

//============================================================================
//描画処理
//============================================================================
void DrawTitle(void)
{
	//3D
	Draw3DTitle();

	if (bTitle == true)
	{
		//デバイスへのポインタを取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

		for (int nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTitle[nCntTitle]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
		}
	}
}

//===================================
//初期化処理内
//===================================
void InitTitleBg(int nCntTitle)
{
	//頂点情報へのポインタ
	VERTEX_2D * pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntTitle * 4;		//頂点情報を進める

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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

	//頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();
}

//タイトルロゴ
void InitTitleLogo(int nCntTitle)
{
	//頂点情報へのポインタ
	VERTEX_2D * pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntTitle * 4;		//頂点情報を進める

	//位置
	g_aTitlePos[0] = D3DXVECTOR3(1000.0f, 50.0f, 0.0f);

	//頂点座標の設定(原点は中央↑)
	pVtx[0].pos = D3DXVECTOR3(g_aTitlePos[0].x - 150.0f, g_aTitlePos[0].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitlePos[0].x + 150.0f, g_aTitlePos[0].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitlePos[0].x - 150.0f, g_aTitlePos[0].y + 450.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitlePos[0].x + 150.0f, g_aTitlePos[0].y + 450.0f, 0.0f);

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

	//頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();
}

//選択(モード選択文字)
void InitTitleSelect0(int nCntTitle)
{
	//頂点情報へのポインタ
	VERTEX_2D * pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntTitle * 4;		//頂点情報を進める

	//位置
	g_aTitlePos[1] = D3DXVECTOR3(POS_STAGESELECT_BG_X, POS_STAGESELECT_BG_Y, 0.0f);

	//頂点座標の設定(原点は中央↑)
	pVtx[0].pos = D3DXVECTOR3(g_aTitlePos[1].x - SIZE_STAGESELECT_BG_X, g_aTitlePos[1].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitlePos[1].x + SIZE_STAGESELECT_BG_X, g_aTitlePos[1].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitlePos[1].x - SIZE_STAGESELECT_BG_X, g_aTitlePos[1].y + SIZE_STAGESELECT_BG_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitlePos[1].x + SIZE_STAGESELECT_BG_X, g_aTitlePos[1].y + SIZE_STAGESELECT_BG_Y, 0.0f);

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

	//頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();
}

//選択(ランキング文字)
void InitTitleSelect1(int nCntTitle)
{
	//頂点情報へのポインタ
	VERTEX_2D * pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntTitle * 4;		//頂点情報を進める

	//位置
	g_aTitlePos[2] = D3DXVECTOR3(POS_RANKING_BG_X, POS_RANKING_BG_Y, 0.0f);

	//頂点座標の設定(原点は中央↑)
	pVtx[0].pos = D3DXVECTOR3(g_aTitlePos[2].x - SIZE_RANKING_BG_X, g_aTitlePos[2].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitlePos[2].x + SIZE_RANKING_BG_X, g_aTitlePos[2].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitlePos[2].x - SIZE_RANKING_BG_X, g_aTitlePos[2].y + SIZE_RANKING_BG_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitlePos[2].x + SIZE_RANKING_BG_X, g_aTitlePos[2].y + SIZE_RANKING_BG_Y, 0.0f);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();
}

//===================================
//更新処理内の処理
//===================================
//選択処理
void UpdateTitleSelect(void)
{
	//フェード情報の取得
	FADE pFade = GetFade();

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_S) == true || GetGamepadTrigger(BUTTON_DOWN, 0) == true || GetGamepad_LStick_Trigger(0, LSTICK_DOWN) == true)
		{
			//選択音
			PlaySound(SOUND_LABEL_CHOICE);

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 + (g_CurrentNumberTitle * 4);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//頂点バッファをアンロックする
			g_pVtxBuffTitle->Unlock();

			//現在地を先に
			g_CurrentNumberTitle = (g_CurrentNumberTitle + 1) % NUM_SELECT;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 + (g_CurrentNumberTitle * 4);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffTitle->Unlock();
		}
		else if (GetKeyboardTrigger(DIK_W) == true || GetGamepadTrigger(BUTTON_UP, 0) == true || GetGamepad_LStick_Trigger(0, LSTICK_UP) == true)
		{
			//選択音
			PlaySound(SOUND_LABEL_CHOICE);

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 + (g_CurrentNumberTitle * 4);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//頂点バッファをアンロックする
			g_pVtxBuffTitle->Unlock();

			//現在地を前へ
			g_CurrentNumberTitle = (g_CurrentNumberTitle - 1 + NUM_SELECT) % NUM_SELECT;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 + (g_CurrentNumberTitle * 4);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffTitle->Unlock();
		}
	
		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadPress(BUTTON_START, 0) || GetGamepadTrigger(BUTTON_A, 0))
		{//決定キー(ENTERキー)が押された
			//モードの設定(ゲーム画面に移行)
			if (bPress == false)
			{
				//決定音
				PlaySound(SOUND_LABEL_ENTER);
				StopSound(SOUND_LABEL_BGM_TITLE);

				//テクスチャを変える処理
				ChangeMeshDome();
				ChangeMeshCylinder();
				SetThunder();
				bTitle = false;
				SetBoolBillboard(false, true);
				//カメラの移動処理
				MoveTitleCamera(0);

				bPress = true;
			}
		}
	}
}

//===================================
//3D用
//===================================
//初期化
void Init3DTitle(void)
{
	//カメラの初期化
	InitCamera();

	InitLight();

	InitMeshDome();

	InitMeshCylinder();

	InitObject00();

	InitBillboard();		//ビルボードの初期化処理

	//ドアの初期化処理
	InitExit();

	LoadExit(1);

	InitThunder();

	InitEffect();

	//タイトル用マップの初期化
	InitObjectBG();

	//ステージの読み込み
	SetStage(1);
}

//終了
void Uninit3DTitle(void)
{
	UninitCamera();

	UninitLight();

	UninitMeshDome();

	UninitMeshCylinder();

	UninitObject00();

	UninitBillboard();		//ビルボードの終了処理

	//ドアの終了処理
	UninitExit();

	UninitThunder();

	UninitEffect();

	//タイトル用マップの終了
	UninitObjectBG();
}

//更新
void Update3DTitle(void)
{
	UpdateCamera();

	UpdateLight();

	UpdateMeshDome();

	UpdateMeshCylinder();

	UpdateObject00();

	UpdateBillboard();

	//ドアの更新処理
	UpdateExit();

	UpdateThunder();

	UpdateEffect();

	//タイトル用マップの更新
	UpdateObjectBG();
}

//描画
void Draw3DTitle(void)
{
	SetCamera(4);

	DrawMeshDome();

	DrawMeshCylinder();

	DrawObject00();

	DrawBillboard();	//月の描画処理（ビルボード）

	//タイトル用マップの描画
	DrawObjectBG();

	DrawEffect();

	//ドアの描画
	DrawExit();

	DrawThunder();
}

