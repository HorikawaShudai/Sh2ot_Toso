#include "main.h"
#include "NeedKeyPolygon.h"
#include "player.h"
#include "exit.h"
#include "PlayNumberSelect.h"
#include "exit.h"
#include "sound.h"

//マクロ定義
#define NEEDKEYPOLYGON_SIZE (5.0f)	//ヘルプUIの大きさ
#define NEEDKEYPOLYGONNUMBER_SIZE (2.0f)	//ヘルプUIの大きさ
#define NEEDKEYPOLYGONNUMBER_X (2.0f)	//ヘルプUIの大きさ
#define NEEDKEYPOLYGONNUMBER_Y (0.5f)	//ヘルプUIの大きさ

//プロトタイプ宣言

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureNeedKeyPolygon[NEEDKEYPOLYGON_MAX];	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNeedKeyPolygon;					//頂点バッファのポインタ
NeedKeyPolygon g_aNeedKeyPolygon[MAX_NEEDKEYPOLYGON];

//====================================================================
//ヘルプUIの初期化処理
//====================================================================
void InitNeedKeyPolygon(void)
{
	int nCntUI;
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ExitNumber.png",
		&g_pTextureNeedKeyPolygon[NEEDKEYPOLYGON_CENTER]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number00.png",
		&g_pTextureNeedKeyPolygon[NEEDKEYPOLYGON_LEFT]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number00.png",
		&g_pTextureNeedKeyPolygon[NEEDKEYPOLYGON_RIGHT]);

	for (nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		g_aNeedKeyPolygon[nCntUI].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		switch (nCntUI)
		{
		case 0:
			g_aNeedKeyPolygon[nCntUI].fSize = NEEDKEYPOLYGON_SIZE;
			break;
		case 1:
		case 2:
			g_aNeedKeyPolygon[nCntUI].fSize = NEEDKEYPOLYGONNUMBER_SIZE;
			break;
		}
		g_aNeedKeyPolygon[nCntUI].bUse = true;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_NEEDKEYPOLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNeedKeyPolygon,
		NULL);

	VERTEX_3D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffNeedKeyPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(-g_aNeedKeyPolygon[nCntUI].fSize, +g_aNeedKeyPolygon[nCntUI].fSize, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+g_aNeedKeyPolygon[nCntUI].fSize, +g_aNeedKeyPolygon[nCntUI].fSize, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aNeedKeyPolygon[nCntUI].fSize, -g_aNeedKeyPolygon[nCntUI].fSize, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+g_aNeedKeyPolygon[nCntUI].fSize, -g_aNeedKeyPolygon[nCntUI].fSize, 0.0f);

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
	g_pVtxBuffNeedKeyPolygon->Unlock();
}

//====================================================================
//ヘルプUIの終了処理
//====================================================================
void UninitNeedKeyPolygon(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < NEEDKEYPOLYGON_MAX; nCntTex++)
	{
		if (g_pTextureNeedKeyPolygon[nCntTex] != NULL)
		{
			g_pTextureNeedKeyPolygon[nCntTex]->Release();
			g_pTextureNeedKeyPolygon[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffNeedKeyPolygon != NULL)
	{
		g_pVtxBuffNeedKeyPolygon->Release();
		g_pVtxBuffNeedKeyPolygon = NULL;
	}
}

//====================================================================
//ヘルプUIの更新処理
//====================================================================
void UpdateNeedKeyPolygon(void)
{
	int nCntUI;

	for (nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		if (g_aNeedKeyPolygon[nCntUI].bUse == true)
		{

		}
	}

	VERTEX_3D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffNeedKeyPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		if (g_aNeedKeyPolygon[nCntUI].bUse == true)
		{
			switch (nCntUI)
			{
			case 0:
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			case 1:
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + GetPlayNumberSelect().CurrentSelectNumber * 0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + GetPlayNumberSelect().CurrentSelectNumber * 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + GetPlayNumberSelect().CurrentSelectNumber * 0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + GetPlayNumberSelect().CurrentSelectNumber * 0.1f, 1.0f);
				break;
			case 2:
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + GetKeyCount() * 0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + GetKeyCount() * 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + GetKeyCount() * 0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + GetKeyCount() * 0.1f, 1.0f);
				break;
			}
		}

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffNeedKeyPolygon->Unlock();
}

//====================================================================
//ヘルプUIの描画処理
//====================================================================
void DrawNeedKeyPolygon(int nCntPlayer)
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

	////ライトを無効にする
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aNeedKeyPolygon[nCntUI].mtxWorld);

		//ビューマトリックスを所得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面を向ける
		D3DXMatrixInverse(&g_aNeedKeyPolygon[nCntUI].mtxWorld, NULL, &mtxView);	//逆行列を求める
		g_aNeedKeyPolygon[nCntUI].mtxWorld._41 = 0.0f;
		g_aNeedKeyPolygon[nCntUI].mtxWorld._42 = 0.0f;
		g_aNeedKeyPolygon[nCntUI].mtxWorld._43 = 0.0f;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aNeedKeyPolygon[nCntUI].pos.x, g_aNeedKeyPolygon[nCntUI].pos.y, g_aNeedKeyPolygon[nCntUI].pos.z);

		D3DXMatrixMultiply(&g_aNeedKeyPolygon[nCntUI].mtxWorld, &g_aNeedKeyPolygon[nCntUI].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aNeedKeyPolygon[nCntUI].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffNeedKeyPolygon, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureNeedKeyPolygon[nCntUI]);

		if (g_aNeedKeyPolygon[nCntUI].bUse == true)
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

	////ライトを有効にする
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//====================================================================
//ヘルプUIの設定処理
//====================================================================
void SetNeedKeyPolygon(D3DXVECTOR3 pos)
{
	g_aNeedKeyPolygon[0].pos = pos;
	g_aNeedKeyPolygon[1].pos = D3DXVECTOR3(pos.x - NEEDKEYPOLYGONNUMBER_X, pos.y - NEEDKEYPOLYGONNUMBER_Y + 0.5f, pos.z);
	g_aNeedKeyPolygon[2].pos = D3DXVECTOR3(pos.x + NEEDKEYPOLYGONNUMBER_X, pos.y + NEEDKEYPOLYGONNUMBER_Y + 0.5f, pos.z);
}

//====================================================================
//ヘルプUIの削除処理
//====================================================================
void FalseNeedKeyPolygon(void)
{
	for (int nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		g_aNeedKeyPolygon[nCntUI].bUse = false;
	}
}

//====================================================================
//ヘルプUIの所得
//====================================================================
NeedKeyPolygon * GetNeedKeyPolygon(void)
{
	return &g_aNeedKeyPolygon[0];
}