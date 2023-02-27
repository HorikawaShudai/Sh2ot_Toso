////============================
////
////フィールド処理(porygon.cpp)
////Author:早川 友貴
////
////============================
//#include "main.h"
//#include "input.h"
//#include"field.h"
//
////マクロ変数
//#define MAX_FIELD (512)  //床の最大数
//
////グローバル
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;   //頂点バッファへのポインタ
//LPDIRECT3DTEXTURE9 g_pTextureField[MAX_FIELD] = {};        //テクスチャのポインタ
//FIELD g_Field[MAX_FIELD];  // 床の情報
//
//int EditIndexPoly;									//エディットモード用の番号
//D3DXVECTOR3 EditPosPoly;							//エディットモードのオブジェクトの位置
//float EditWightPoly;								//エディットモードのオブジェクトの位置
//float EditHeightPoly;								//エディットモードのオブジェクトの位置
//int g_ObjectFieldCount;								//オブジェクトの数
//
////=============================
////フィールドの初期化処理
////=============================
//void InitField(void)
//{
//	int nCnt;
//
//	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice,
//		"Data\\TEXTURE\\thumb_concrete.jpg", 
//		&g_pTextureField[0]);
//
//	//各種変数の初期化
//	for (nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	{
//		g_Field[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置を初期化
//		g_Field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きを初期化
//		g_Field[nCnt].fWigft = 100.0f;						//幅を初期化
//		g_Field[nCnt].fHeight = 100.0f;						//高さを初期化
//		g_Field[nCnt].bUse = false;							//使用していない状態にする
//	}
//
//	EditIndexPoly = MAX_FIELD - 1;						//エディットモード用の番号
//	EditPosPoly = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//エディットモードのオブジェクトの位置
//	EditWightPoly = g_Field[0].fWigft;								//エディットモードのオブジェクトの位置
//	EditHeightPoly = g_Field[0].fHeight;							//エディットモードのオブジェクトの位置
//	g_ObjectFieldCount = 0;								//オブジェクトの数
//
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffField,
//		NULL);
//
//	VERTEX_3D *pVtx; //頂点座標へのポインタ
//
//	//頂点バッファをロックし,頂点情報へのポインタを取得
//	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
//	{
//
//		//頂点座標の設定
//		pVtx[0].pos = D3DXVECTOR3(-g_Field[nCnt].fWigft, 0.0f, +g_Field[nCnt].fHeight);
//		pVtx[1].pos = D3DXVECTOR3(+g_Field[nCnt].fWigft, 0.0f, +g_Field[nCnt].fHeight);
//		pVtx[2].pos = D3DXVECTOR3(-g_Field[nCnt].fWigft, 0.0f, -g_Field[nCnt].fHeight);
//		pVtx[3].pos = D3DXVECTOR3(+g_Field[nCnt].fWigft, 0.0f, -g_Field[nCnt].fHeight);
//
//		//法線ベクトルの設定
//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		//頂点カラーの設定
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;
//	}
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffField->Unlock();
//
//}
//
////========================
////フィールドの終了処理
////========================
//void UninitField(void)
//{
//	for(int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	//テクスチャの破棄
//	if (g_pTextureField[nCnt] != NULL)
//	{
//		g_pTextureField[nCnt]->Release();
//		g_pTextureField[nCnt] = NULL;
//	}
//}
//
////========================
////フィールドの更新処理
////========================
//void UpdateField(void)
//{
//
//}
//
////========================
////フィールドのエディットモードでの更新処理
////========================
//void UpdateEditField(void)
//{
//	if (GetKeyboardPress(DIK_UP) == true)
//	{//前移動
//		EditPosPoly.z += 1.0f;
//	}
//	if (GetKeyboardPress(DIK_DOWN) == true)
//	{//後ろ移動
//		EditPosPoly.z -= 1.0f;
//	}
//	if (GetKeyboardPress(DIK_RIGHT) == true)
//	{//右移動
//		EditPosPoly.x += 1.0f;
//	}
//	if (GetKeyboardPress(DIK_LEFT) == true)
//	{//左移動
//		EditPosPoly.x -= 1.0f;
//	}
//	if (GetKeyboardPress(DIK_RSHIFT) == true)
//	{//上移動
//		EditPosPoly.y += 1.0f;
//	}
//	if (GetKeyboardPress(DIK_RCONTROL) == true)
//	{//下移動
//		EditPosPoly.y -= 1.0f;
//	}
//
//	if (GetKeyboardTrigger(DIK_6) == true)
//	{//６キーで前のタイプのオブジェクトにする
//		EditWightPoly++;
//	}
//
//	if (GetKeyboardTrigger(DIK_7) == true)
//	{//７キーで前のタイプのオブジェクトにする
//		EditWightPoly--;
//	}
//
//	if (GetKeyboardTrigger(DIK_8) == true)
//	{//８キーで前のタイプのオブジェクトにする
//		EditHeightPoly++;
//	}
//
//	if (GetKeyboardTrigger(DIK_9) == true)
//	{//９キーで次のタイプのオブジェクトにする
//		EditHeightPoly--;
//	}
//
//
//	//エディットモードの変更をオブジェクトに反映させる
//	g_Field[EditIndexPoly].pos = EditPosPoly;
//	g_Field[EditIndexPoly].fWigft = EditWightPoly;
//	g_Field[EditIndexPoly].fHeight = EditHeightPoly;
//
//	//オブジェクトの削除処理(重なっているもの)----------
//	if (GetKeyboardTrigger(DIK_BACKSPACE))
//	{
//		EditCollisionField(g_Field[EditIndexPoly].pos, 20.0f);
//	}
//
//	//オブジェクトの設置処理----------
//	if (GetKeyboardTrigger(DIK_RETURN) == true)
//	{
//		SetField(g_Field[EditIndexPoly].pos, g_Field[EditIndexPoly].fWigft, g_Field[EditIndexPoly].fHeight);
//	}
//
//	VERTEX_3D *pVtx; //頂点座標へのポインタ
//
//	//頂点バッファをロックし,頂点情報へのポインタを取得
//	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
//
//	pVtx += (MAX_FIELD - 1) * 4;
//
//	//頂点座標の設定
//	pVtx[0].pos = D3DXVECTOR3(-g_Field[EditIndexPoly].fWigft, 0.0f, +g_Field[EditIndexPoly].fHeight);
//	pVtx[1].pos = D3DXVECTOR3(+g_Field[EditIndexPoly].fWigft, 0.0f, +g_Field[EditIndexPoly].fHeight);
//	pVtx[2].pos = D3DXVECTOR3(-g_Field[EditIndexPoly].fWigft, 0.0f, -g_Field[EditIndexPoly].fHeight);
//	pVtx[3].pos = D3DXVECTOR3(+g_Field[EditIndexPoly].fWigft, 0.0f, -g_Field[EditIndexPoly].fHeight);
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffField->Unlock();
//}
//
//
//
////========================
////フィールドの描画処理
////========================
//void DrawField(void)
//{
//	//デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
//
//	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	{
//		//ワールドマトリックスの初期化
//		D3DXMatrixIdentity(&g_Field[nCnt].mtxWorld);
//
//		//向きを反映
//		D3DXMatrixRotationYawPitchRoll(&mtxRot,
//			g_Field[nCnt].rot.y, g_Field[nCnt].rot.x, g_Field[nCnt].rot.z);
//
//		D3DXMatrixMultiply(&g_Field[nCnt].mtxWorld,
//			&g_Field[nCnt].mtxWorld,
//			&mtxRot);
//
//		//位置を反映
//		D3DXMatrixTranslation(&mtxTrans,
//			g_Field[nCnt].pos.x, g_Field[nCnt].pos.y, g_Field[nCnt].pos.z);
//
//		D3DXMatrixMultiply(&g_Field[nCnt].mtxWorld, &g_Field[nCnt].mtxWorld, &mtxTrans);
//
//		//ワールドマトリックスの設定
//		pDevice->SetTransform(D3DTS_WORLD, &g_Field[nCnt].mtxWorld);
//
//		//頂点バッファをデータストリームに設定
//		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));
//
//		//頂点フォーマットの設定
//		pDevice->SetFVF(FVF_VERTEX_3D);
//
//		pDevice->SetTexture(0, g_pTextureField[nCnt]);
//
//		if (g_Field[nCnt].bUse == true)
//		{
//			//フィールドの描画
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //プリミティブの種類
//		}
//	}
//}
//
////========================
////フィールドの描画処理
////========================
//void DrawEditField(void)
//{
//	//デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
//
//		//ワールドマトリックスの初期化
//	D3DXMatrixIdentity(&g_Field[EditIndexPoly].mtxWorld);
//
//	//向きを反映
//	D3DXMatrixRotationYawPitchRoll(&mtxRot,
//		g_Field[EditIndexPoly].rot.y, g_Field[EditIndexPoly].rot.x, g_Field[EditIndexPoly].rot.z);
//
//	D3DXMatrixMultiply(&g_Field[EditIndexPoly].mtxWorld,
//		&g_Field[EditIndexPoly].mtxWorld,
//		&mtxRot);
//
//	//位置を反映
//	D3DXMatrixTranslation(&mtxTrans,
//		g_Field[EditIndexPoly].pos.x, g_Field[EditIndexPoly].pos.y, g_Field[EditIndexPoly].pos.z);
//
//	D3DXMatrixMultiply(&g_Field[EditIndexPoly].mtxWorld, &g_Field[EditIndexPoly].mtxWorld, &mtxTrans);
//
//	//ワールドマトリックスの設定
//	pDevice->SetTransform(D3DTS_WORLD, &g_Field[EditIndexPoly].mtxWorld);
//
//	//頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	pDevice->SetTexture(0, g_pTextureField[EditIndexPoly]);
//
//	//フィールドの描画
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, EditIndexPoly * 4, 2); //プリミティブの種類
//}
//
////========================
////フィールドの設定処理
////========================
//void SetField(D3DXVECTOR3 pos, float Wight, float Height)
//{
//	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	{
//		if (g_Field[nCnt].bUse == false)
//		{
//			g_Field[nCnt].pos = pos;	//位置を設定
//			g_Field[nCnt].fWigft = Wight;						//幅を設定
//			g_Field[nCnt].fHeight = Height;						//高さを設定
//
//			g_ObjectFieldCount++;
//
//			g_Field[nCnt].bUse = true;							//使用している状態にする
//
//			break;
//		}
//
//	}
//}
//
////========================
////フィールドの削除処理
////========================
//void EditCollisionField(D3DXVECTOR3 pos, float Size)
//{
//	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	{
//		if (g_Field[nCnt].bUse == true)
//		{
//			if (
//				pos.y + Size >= g_Field[nCnt].pos.y
//				&& pos.y - Size <= g_Field[nCnt].pos.y
//				&& pos.x + Size >= g_Field[nCnt].pos.x - g_Field[nCnt].fWigft
//				&& pos.x - Size <= g_Field[nCnt].pos.x + g_Field[nCnt].fWigft
//				&& pos.z + Size >= g_Field[nCnt].pos.z - g_Field[nCnt].fHeight
//				&& pos.z - Size <= g_Field[nCnt].pos.z + g_Field[nCnt].fHeight
//				)
//			{//オブジェクト同士が重なっている
//				g_Field[nCnt].bUse = false;
//				g_ObjectFieldCount--;
//			}
//		}
//	}
//}
//
//////=============================
//////フィールドの位置を与える処理
//////=============================
////D3DXVECTOR3 PosField(void)
////{
////	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
////	{
////		return g_Field[nCnt].pos;
////	}
////}
