//============================
//
//フィールド処理(porygon.cpp)
//Author:早川 友貴
//
//============================
#include "main.h"
#include "input.h"
#include"field.h"

//マクロ変数
#define MAX_FIELD (4)  //床の最大数

#define POS_INSTITUTE_X (1200.0f) //生物収容所のX位置
#define POS_INSTITUTE_Y (0)		//生物収容所のY位置
#define POS_INSTITUTE_Z (800.0f) //生物収容所のZ位置

#define POS_COLLAPSE_X	(-1000.0f) //崩壊X位置
#define POS_COLLAPSE_Y	(0) //崩壊Y位置
#define POS_COLLAPSE_Z	(-1500.0f) //崩壊Z位置

#define POS_CAMP_X		(1200.0f)   //研究所のX座標
#define POS_CAMP_Y		(-0)   //研究所のY座標
#define POS_CAMP_Z		(-1000.0f)   //研究所のZ座標

#define POS_OFFICE_X (-1400.0f)	 //オフィスののX座標
#define POS_OFFICE_Y (0)	 //オフィスのエリアのY座標
#define POS_OFFICE_Z (100.0f) //オフィスのエリアのZ座標

#define FIELD_WIDTH		(1300.0f) //床の幅
#define FIELD_DEPTH		(1000.0f) //床の奥行

//床の構造体
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 rot; //向き
	D3DXMATRIX mtxWorld; //ワールドマトリックス
}FIELD;

//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;   //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureField[MAX_FIELD] = {};        //テクスチャのポインタ
FIELD g_Field[MAX_FIELD];  // 床の情報

//=============================
//フィールドの初期化処理
//=============================
void InitField(void)
{
	int nCnt;

	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\thumb_concrete.jpg", 
		&g_pTextureField[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\collapse_field.jpeg", 
		&g_pTextureField[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\tile.jpg", 
		&g_pTextureField[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\field_office.jpg", 
		&g_pTextureField[3]);

	//各種変数の初期化
	for (nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		//床の位置
		if (nCnt == 0)
		{//研究エリア
			g_Field[nCnt].pos = D3DXVECTOR3(POS_INSTITUTE_X, POS_INSTITUTE_Y, POS_INSTITUTE_Z); //位置を初期化

			g_Field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化
		}

		if (nCnt == 1)
		{//オフィスエリア
			g_Field[nCnt].pos = D3DXVECTOR3(POS_OFFICE_X, POS_OFFICE_Y, POS_OFFICE_Z); //位置を初期化

			g_Field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化
		}

		if (nCnt == 2)
		{//生物収容所エリア
			g_Field[nCnt].pos = D3DXVECTOR3(POS_CAMP_X, POS_CAMP_Y, POS_CAMP_Z); //位置を初期化

			g_Field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化
		}

		if (nCnt == 3)
		{//崩壊エリア
			g_Field[nCnt].pos = D3DXVECTOR3(POS_COLLAPSE_X, POS_COLLAPSE_Y, POS_COLLAPSE_Z); //位置を初期化

			g_Field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化
		}
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	VERTEX_3D *pVtx; //頂点座標へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-FIELD_WIDTH, 0.0f, +FIELD_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(+FIELD_WIDTH, 0.0f, +FIELD_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(-FIELD_WIDTH, 0.0f, -FIELD_DEPTH);
		pVtx[3].pos = D3DXVECTOR3(+FIELD_WIDTH, 0.0f, -FIELD_DEPTH);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffField->Unlock();

}

//========================
//フィールドの終了処理
//========================
void UninitField(void)
{
	for(int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	//テクスチャの破棄
	if (g_pTextureField[nCnt] != NULL)
	{
		g_pTextureField[nCnt]->Release();
		g_pTextureField[nCnt] = NULL;
	}
}

//========================
//フィールドの更新処理
//========================
void UpdateField(void)
{

}

//========================
//フィールドの描画処理
//========================
void DrawField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Field[nCnt].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Field[nCnt].rot.y, g_Field[nCnt].rot.x, g_Field[nCnt].rot.z);

		D3DXMatrixMultiply(&g_Field[nCnt].mtxWorld,
			&g_Field[nCnt].mtxWorld,
			&mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_Field[nCnt].pos.x, g_Field[nCnt].pos.y, g_Field[nCnt].pos.z);

		D3DXMatrixMultiply(&g_Field[nCnt].mtxWorld, &g_Field[nCnt].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Field[nCnt].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->SetTexture(0, g_pTextureField[nCnt]);

		//フィールドの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //プリミティブの種類
	}
}

////=============================
////フィールドの位置を与える処理
////=============================
//D3DXVECTOR3 PosField(void)
//{
//	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	{
//		return g_Field[nCnt].pos;
//	}
//}
