#include "CheckboxUI.h"
#include "fade.h"
#include "player.h"
#include "PlayNumberSelect.h"
#include "EscapeTutorial.h"
#include "input.h"
#include "key.h"
#include "enemy.h"
#include "sound.h"

//マクロ定義
#define MAX_CHECK_TEX		(2)				//チェックボックスのテクスチャ最大数

//チェックボックスの位置
//一・二プレイ
#define CHECKUIPOS_X_0		(990.0f)		//チェックボックスのUIのX位置(1人目)
#define CHECKUIPOS_Y_0		(680.0f)		//チェックボックスのUIのY位置(1人目)

#define CHECKUIPOS_X_1		(550.0f)		//チェックボックスのUIのX位置(1人目)
#define CHECKUIPOS_Y_1		(680.0f)		//チェックボックスのUIのY位置(1人目)

#define CHECKUIPOS_X_2		(1140.0f)		//チェックボックスのUIのX位置(2人目)
#define CHECKUIPOS_Y_2		(680.0f)		//チェックボックスのUIのY位置(2人目)

//三・四人プレイ
#define CHECKUIPOS_X_1_34	(550.0f)		//チェックボックスのUIのX位置(1人目)
#define CHECKUIPOS_Y_1_34	(320.0f)		//チェックボックスのUIのY位置(1人目)

#define CHECKUIPOS_X_2_34	(1190.0f)		//チェックボックスのUIのX位置(2人目)
#define CHECKUIPOS_Y_2_34	(320.0f)		//チェックボックスのUIのY位置(2人目)

#define CHECKUIPOS_X_3_34	(550.0f)		//チェックボックスのUIのX位置(3人目)
#define CHECKUIPOS_Y_3_34	(680.0f)		//チェックボックスのUIのY位置(3人目)

#define CHECKUIPOS_X_4_34	(1190.0f)		//チェックボックスのUIのX位置(4人目)
#define CHECKUIPOS_Y_4_34	(680.0f)		//チェックボックスのUIのY位置(4人目)

//全体に表示してる時
#define CHECKUIPOS_X_3_0	(100.0f)		//チュートリアル用紙が出ているときのX位置(1人目)
#define CHECKUIPOS_Y_3_0	(550.0f)		//チュートリアル用紙が出ているときのY位置(1人目)

#define CHECKUIPOS_X_3_1	(200.0f)		//チュートリアル用紙が出ているときのX位置(2人目)
#define CHECKUIPOS_Y_3_1	(550.0f)		//チュートリアル用紙が出ているときのY位置(2人目)

#define CHECKUIPOS_X_3_2	(900.0f)		//チュートリアル用紙が出ているときのX位置(3人目)
#define CHECKUIPOS_Y_3_2	(550.0f)		//チュートリアル用紙が出ているときのY位置(3人目)

#define CHECKUIPOS_X_3_3	(1000.0f)		//チュートリアル用紙が出ているときのX位置(4人目)
#define CHECKUIPOS_Y_3_3	(550.0f)		//チュートリアル用紙が出ているときのY位置(4人目)

#define CHECKUI_WIDTH		(40.0f)			//チェックボックスのUIの幅
#define CHECKUI_HEIGHT		(40.0f)			//チェックボックスのUIの高さ
#define CHECKUI_INTERVAL	(50.0f)			//チェックボックスのUI同士の間隔

#define UP_CHECKBOXUI				(100.0f)	//紙を取り出すときの上昇度
#define UP_CHECKBOXUI_COUNTER_MAX	(100)		//紙を取り出す速さのカウンター
#define UP_CHECKBOXUI_WAITCOUNTER	(60)		//項目達成時の余韻

//チェックボックスUIの構造体
typedef struct
{
	D3DXVECTOR3 pos;	 //鍵UIの位置
	int nCheckUI;		 //鍵UIの数
	bool bUse;			 //使われているかどうか
}CHECKUI;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureCheckUI[MAX_CHECK_TEX] = {};  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCheckUI = NULL;			//頂点バッファへのポインタ
CHECKUI g_anCheckUI[NUM_PLAYER];							//チェックボックスのUIの情報
int g_NumPlayerCheckUI;
bool btutorial;  //チュートリアル用紙が表示されているかどうか
int ChecboxUITrueCounter;			//紙を取り出すときのカウンター
int ChecboxUIWaitCount;				//チェックをいれたときの余韻

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
	ChecboxUITrueCounter = 0;
	ChecboxUIWaitCount = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\no_check.png",
		&g_pTextureCheckUI[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\use_check.png",
		&g_pTextureCheckUI[1]);

	for (nCntCheckUI = 0; nCntCheckUI < NUM_PLAYER; nCntCheckUI++)
	{
		g_anCheckUI[nCntCheckUI].bUse = true;  //使っていることに
	}

	//鍵UIの情報を初期化
	for (nCntCheckUI = 0; nCntCheckUI < PlayNumber.CurrentSelectNumber; nCntCheckUI++)
	{
		if (nCntCheckUI == 0)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_0, CHECKUIPOS_Y_3_0, 0.0f);  //1人目の位置を初期化
		}

		if (nCntCheckUI == 1)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_1, CHECKUIPOS_Y_3_1, 0.0f);  //2人目の位置を初期化
		}

		if (nCntCheckUI == 2)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_2, CHECKUIPOS_Y_3_2, 0.0f);  //3人目の位置を初期化
		}

		if (nCntCheckUI == 3)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_3, CHECKUIPOS_Y_3_3, 0.0f);  //4人目の位置を初期化
		}
		g_anCheckUI[nCntCheckUI].nCheckUI = 3;		//鍵UIの値を初期化
		g_anCheckUI[nCntCheckUI].bUse = false;  //使っていないことに
		btutorial = true;  //チュートリアル用紙を使っていることにする
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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//プレイヤー情報の所得
	Player *pPlayer = GetPlayer();

	//変数宣言
	int nCntCheckUI;

	switch (GetEscapeTutorial())
	{
	case TUTORIAL_STATE_STANDBY:
		//スタンバイ状態の時にチェックをオンにする入力処理
		for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
		{
			if ((GetKeyboardTrigger(DIK_N)) || (GetGamepadTrigger(BUTTON_A, nCntPlayer) || GetGamepadTrigger(BUTTON_B, nCntPlayer)) && ChecboxUITrueCounter >= UP_CHECKBOXUI_COUNTER_MAX)
			{
				SetCheckUI(nCntPlayer, true);
			}
		}

		//紙を取り出す処理
		if (ChecboxUITrueCounter < UP_CHECKBOXUI_COUNTER_MAX)
		{
			ChecboxUITrueCounter++;
		}
		break;
	case TUTORIAL_STATE_WAIT:

		//紙をしまう処理
		if (ChecboxUITrueCounter > 0)
		{
			ChecboxUITrueCounter--;
		}
		break;
	}

	if (g_anCheckUI[0].bUse == true && g_anCheckUI[1].bUse == true && g_anCheckUI[2].bUse == true && g_anCheckUI[3].bUse == true)
	{
		switch (GetEscapeTutorial())
		{
		case TUTORIAL_STATE_PLAY:
			ChecboxUIWaitCount++;
			if (ChecboxUIWaitCount >= UP_CHECKBOXUI_WAITCOUNTER)
			{
				ChecboxUIWaitCount = 0;
				for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++, pPlayer++)
				{
					pPlayer->MoveState = PLAYER_MOVESTATE_NORMAL;
					GetGamepad_Vibrtion_false(nCntPlayer);
				}

				switch (GetDoEscapeTutorial())
				{
				case MODE_MOVE:
					//チュートリアル用紙をカメラ移動に
					DoEscapeTutorial(MODE_DASH);
					break;
				case MODE_DASH:
					//チュートリアル用紙をバイブに
					DoEscapeTutorial(MODE_VIBE);

					SetEnemy(D3DXVECTOR3(-1050.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					break;
				case MODE_VIBE:
					//チュートリアル用紙をステルスに
					DoEscapeTutorial(MODE_STELTH);
					break;
				case MODE_STELTH:
					//チュートリアル用紙を鍵をとるに
					DoEscapeTutorial(MODE_GET_KEY);

					FalseEnemy();

					for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
					{
						SetKey(D3DXVECTOR3(-1150.0f + (50.0f * nCntTutorial), 3.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), KEY_TYPE_ITEM);
					}

					break;
				case MODE_GET_KEY:
					//チュートリアル用紙を脱出に
					DoEscapeTutorial(MODE_ESCAPE);
					break;
				case MODE_ESCAPE:
					//チュートリアル用紙をチュートリアル項目の終了に
					DoEscapeTutorial(MODE_GOEXIT);
					break;
				case MODE_GOEXIT:
					//チュートリアル用紙をチュートリアル項目の終了に
					DoEscapeTutorial(MODE_END);
					break;
				}
				//チェックボックスを人数分オフにする
				for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
				{
					g_anCheckUI[nCntTutorial].bUse = false;
				}
				SetEscapeTutorial(TUTORIAL_STATE_STANDBY);
				//紙の音
				PlaySound(SOUND_LABEL_PAPER);
			}
			break;

		case TUTORIAL_STATE_STANDBY:
			SetEscapeTutorial(TUTORIAL_STATE_WAIT);
			//紙の音
			PlaySound(SOUND_LABEL_PAPER);
			break;
		}
	}

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCheckUI->Lock(0, 0, (void**)&pVtx, 0);

	//チュートリアル用紙が使われていなかったら
	if (btutorial == false)
	{
		//鍵UIの情報を初期化
		for (nCntCheckUI = 0; nCntCheckUI < PlayNumber.CurrentSelectNumber; nCntCheckUI++)
		{
			switch (PlayNumber.CurrentSelectNumber)
			{
			case 1:
				if (nCntCheckUI == 0)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_0, CHECKUIPOS_Y_0, 0.0f);  //1人目の位置を初期化
				}
				break;

			case 2:
				if (nCntCheckUI == 0)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_1, CHECKUIPOS_Y_1, 0.0f);  //1人目の位置を初期化
				}
				if (nCntCheckUI == 1)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_2, CHECKUIPOS_Y_1, 0.0f);  //2人目の位置を初期化
				}
				break;

			case 3:
				if (nCntCheckUI == 0)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_1_34, CHECKUIPOS_Y_1_34, 0.0f);  //1人目の位置を初期化
				}
				if (nCntCheckUI == 1)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_2_34, CHECKUIPOS_Y_2_34, 0.0f);  //2人目の位置を初期化
				}
				if (nCntCheckUI == 2)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_34, CHECKUIPOS_Y_3_34, 0.0f);  //3人目の位置を初期化
				}

				if (nCntCheckUI == 3)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_4_34, CHECKUIPOS_Y_4_34, 0.0f);  //4人目の位置を初期化
				}
				break;

			case 4:
				if (nCntCheckUI == 0)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_1_34, CHECKUIPOS_Y_1_34, 0.0f);  //1人目の位置を初期化
				}
				if (nCntCheckUI == 1)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_2_34, CHECKUIPOS_Y_2_34, 0.0f);  //2人目の位置を初期化
				}
				if (nCntCheckUI == 2)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_34, CHECKUIPOS_Y_3_34, 0.0f);  //3人目の位置を初期化
				}

				if (nCntCheckUI == 3)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_4_34, CHECKUIPOS_Y_4_34, 0.0f);  //4人目の位置を初期化
				}
				break;
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH, g_anCheckUI[nCntCheckUI].pos.y - CHECKUI_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH, g_anCheckUI[nCntCheckUI].pos.y - CHECKUI_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH, g_anCheckUI[nCntCheckUI].pos.y + CHECKUI_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH, g_anCheckUI[nCntCheckUI].pos.y + CHECKUI_HEIGHT, 0.0f);

			pVtx += 4;

		}
	}

	//チュートリアル用紙が使われていたら
	else
	{
		//鍵UIの情報を初期化
		for (nCntCheckUI = 0; nCntCheckUI < PlayNumber.CurrentSelectNumber; nCntCheckUI++)
		{
			if (nCntCheckUI == 0)
			{
				g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_0, CHECKUIPOS_Y_3_0, 0.0f);  //1人目の位置を初期化
			}

			if (nCntCheckUI == 1)
			{
				g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_1, CHECKUIPOS_Y_3_1, 0.0f);  //2人目の位置を初期化
			}

			if (nCntCheckUI == 2)
			{
				g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_2, CHECKUIPOS_Y_3_2, 0.0f);  //3人目の位置を初期化
			}

			if (nCntCheckUI == 3)
			{
				g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_3, CHECKUIPOS_Y_3_3, 0.0f);  //4人目の位置を初期化
			}

			////頂点座標の設定
			//pVtx[0].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y - CHECKUI_HEIGHT, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y - CHECKUI_HEIGHT, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + CHECKUI_HEIGHT, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + CHECKUI_HEIGHT, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + (UP_CHECKBOXUI * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter)) - CHECKUI_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + (UP_CHECKBOXUI * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter)) - CHECKUI_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + (UP_CHECKBOXUI * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter)) + CHECKUI_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + (UP_CHECKBOXUI * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter)) + CHECKUI_HEIGHT, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter));
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter));
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter));
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter));

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffCheckUI->Unlock();
}

//====================================================================
//チェックボックスの描画処理
//====================================================================
void DrawCheckboxUI(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プレイ人数情報の取得
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCheckUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		if (g_anCheckUI[nCnt].bUse == false)
		{//チェックがついていないとき
		 //テクスチャの設定
			pDevice->SetTexture(0, g_pTextureCheckUI[0]);
		}

		else
		{//チェックがついたとき
		 //テクスチャの設定
			pDevice->SetTexture(0, g_pTextureCheckUI[1]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//============================
//チェックボックスの設定
//============================
void SetCheckUI(int nPlayer, bool SetCheck)
{
	if (g_anCheckUI[nPlayer].bUse == false)
	{
		if (SetCheck == true)
		{
			//紙の音
			PlaySound(SOUND_LABEL_ENTER);
		}
	}

	g_anCheckUI[nPlayer].bUse = SetCheck;
}

//============================
//チェックボックスの位置設定
//============================
void MovePosCheckUI(int nPlayer, bool SetCheck)
{
	btutorial = SetCheck;
}

