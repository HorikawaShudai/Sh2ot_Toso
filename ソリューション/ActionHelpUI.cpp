#include "main.h"
#include "ActionHelpUI.h"
#include "player.h"
#include "sound.h"

//マクロ定義
#define ACTIONHELPUI_SIZE (5.0f)	//ヘルプUIの大きさ

//プロトタイプ宣言

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureActionHelpUI[ACTIONHELPUI_MAX];				//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffActionHelpUI;		//頂点バッファのポインタ
ActionHelpUI g_aActionHelpUI[MAX_ACTIONHELPUI];

//====================================================================
//ヘルプUIの初期化処理
//====================================================================
void InitActionHelpUI(void)
{
	int nCntUI;
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\GetUi.png",
		&g_pTextureActionHelpUI[ACTIONHELPUI_KEY]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\OpenUi.png",
		&g_pTextureActionHelpUI[ACTIONHELPUI_DOOR]);

	for (nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		g_aActionHelpUI[nCntUI].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_aActionHelpUI[nCntUI].fSize = ACTIONHELPUI_SIZE;
		g_aActionHelpUI[nCntUI].bUse = false;
		g_aActionHelpUI[nCntUI].nType = ACTIONHELPUI_KEY;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ACTIONHELPUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffActionHelpUI,
		NULL);

	VERTEX_3D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffActionHelpUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(-g_aActionHelpUI[nCntUI].fSize, +g_aActionHelpUI[nCntUI].fSize, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+g_aActionHelpUI[nCntUI].fSize, +g_aActionHelpUI[nCntUI].fSize, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aActionHelpUI[nCntUI].fSize, -g_aActionHelpUI[nCntUI].fSize, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+g_aActionHelpUI[nCntUI].fSize, -g_aActionHelpUI[nCntUI].fSize, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffActionHelpUI->Unlock();
}

//====================================================================
//ヘルプUIの終了処理
//====================================================================
void UninitActionHelpUI(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < ACTIONHELPUI_MAX; nCntTex++)
	{
		if (g_pTextureActionHelpUI[nCntTex] != NULL)
		{
			g_pTextureActionHelpUI[nCntTex]->Release();
			g_pTextureActionHelpUI[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffActionHelpUI != NULL)
	{
		g_pVtxBuffActionHelpUI->Release();
		g_pVtxBuffActionHelpUI = NULL;
	}
}

//====================================================================
//ヘルプUIの更新処理
//====================================================================
void UpdateActionHelpUI(void)
{
	int nCntUI;

	for (nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		if (g_aActionHelpUI[nCntUI].bUse == true)
		{

		}
	}

	VERTEX_3D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffActionHelpUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		if (g_aActionHelpUI[nCntUI].bUse == true)
		{
			//頂点座標の設定 
			pVtx[0].pos = D3DXVECTOR3(-g_aActionHelpUI[nCntUI].fSize, +g_aActionHelpUI[nCntUI].fSize, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_aActionHelpUI[nCntUI].fSize, +g_aActionHelpUI[nCntUI].fSize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aActionHelpUI[nCntUI].fSize, -g_aActionHelpUI[nCntUI].fSize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_aActionHelpUI[nCntUI].fSize, -g_aActionHelpUI[nCntUI].fSize, 0.0f);
		}

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffActionHelpUI->Unlock();
}

//====================================================================
//ヘルプUIの描画処理
//====================================================================
void DrawActionHelpUI(int nCntPlayer,bool GetKey)
{
	//プレイヤー情報の取得
	Player *pPlayer = GetPlayer();
	pPlayer += nCntPlayer;

	int nCntUI;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;	//ビューマトリックス所得用

	////Zテストを無効にする
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aActionHelpUI[nCntUI].mtxWorld);

		//ビューマトリックスを所得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面を向ける
		D3DXMatrixInverse(&g_aActionHelpUI[nCntUI].mtxWorld, NULL, &mtxView);	//逆行列を求める
		g_aActionHelpUI[nCntUI].mtxWorld._41 = 0.0f;
		g_aActionHelpUI[nCntUI].mtxWorld._42 = 0.0f;
		g_aActionHelpUI[nCntUI].mtxWorld._43 = 0.0f;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aActionHelpUI[nCntUI].pos.x, g_aActionHelpUI[nCntUI].pos.y, g_aActionHelpUI[nCntUI].pos.z);

		D3DXMatrixMultiply(&g_aActionHelpUI[nCntUI].mtxWorld, &g_aActionHelpUI[nCntUI].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aActionHelpUI[nCntUI].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffActionHelpUI, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		if (GetKey == true && pPlayer->ExitHelpUI == true)
		{
			pDevice->SetTexture(0, g_pTextureActionHelpUI[ACTIONHELPUI_DOOR]);
		}
		else if(GetKey == false && pPlayer->KeyHelpUI == true)
		{
			pDevice->SetTexture(0, g_pTextureActionHelpUI[ACTIONHELPUI_KEY]);
		}

		if (g_aActionHelpUI[nCntUI].bUse == true &&(pPlayer->ExitHelpUI == true || pPlayer->KeyHelpUI == true))
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntUI,										//プリミティブ(ポリゴン)数
				2);
		}
	}

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	////Zテストを有効にする
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//====================================================================
//ヘルプUIの設定処理
//====================================================================
int SetActionHelpUI(D3DXVECTOR3 pos, float Size, ACTIONHELPUI_TYPE Type)
{
	int nIdx = -1;

	for (int nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		if (g_aActionHelpUI[nCntUI].bUse == false)
		{
			g_aActionHelpUI[nCntUI].pos = pos;
			g_aActionHelpUI[nCntUI].fSize = Size;
			g_aActionHelpUI[nCntUI].nType = Type;
			g_aActionHelpUI[nCntUI].bUse = true;
			nIdx = nCntUI;
			break;
		}
	}

	return nIdx;
}

//====================================================================
//ヘルプUIの削除処理
//====================================================================
void FalseActionHelpUI(int Idx)
{
	g_aActionHelpUI[Idx].bUse = false;
}

//====================================================================
//ヘルプUIの所得
//====================================================================
ActionHelpUI * GetActionHelpUI(void)
{
	return &g_aActionHelpUI[0];
}