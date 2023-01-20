//============================
//
//スコアアイテム処理(score_item.h)
//Author:早川 友貴
//
//============================

#ifndef _SCORE_ITEM_H_   //このマクロ定義がされていなかったら
#define _SCORE_ITEM_H_   //2重インクルード防止のマクロを定義する

#include "main.h"
#include <stdio.h>

//スコアアイテムの最大数
#define MAX_ITEM (128) //スコアアイテムの最大数

//スコアアイテムの構造体
typedef struct
{
	LPDIRECT3DTEXTURE9 _apTexture[20] = {};	//テクスチャへのポインタ
	LPD3DXMESH pMesh = NULL; //メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat = NULL; //マテリアルへのポインタ
	DWORD dwNumMat = 0; //マテリアルの数
	D3DXVECTOR3 VtxMax; //スコアアイテムの矩形の最大値
	D3DXVECTOR3 VtxMin; //スコアアイテムの矩形の最小値
}ITEMDATA;

//スコアアイテムの構造体
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 posold; //前の位置
	D3DXVECTOR3 move; //移動量
	D3DXVECTOR3 rot; //向き
	D3DXMATRIX mtxWorld;  //ワールドマトリックス
	
	bool bUse;  //使っているかどうか
	D3DXVECTOR3 VtxMax; //スコアアイテムの矩形の最大値
	D3DXVECTOR3 VtxMin; //スコアアイテムの矩形の最小値
	int nldxShadow;  //対象の影のインデックス(番号)
	int nLife;  //スコアアイテムのライフ
	int nCounterstate; //スコアアイテムの状態を数える処理
	D3DXMATERIAL RedMat;  //マテリアルを赤くする処理
	bool bSound; //音を使うかどうか
	ITEMDATA Itemdata;

}ITEM;
//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos);
//ENEMY *GetEnemy(void);
//void HitItem(int nCntEnemy, int nDamage);
//void ColisionItem(void);
//int ItemCount(void);
//void ReturnItem(void);

#endif

