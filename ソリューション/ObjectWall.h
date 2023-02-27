//========================================================================================
//
// オブジェクトの処理[ObjectWall.h]
// Author: 坂本　翔唯
// Author: 丹野竜之介
//
//========================================================================================
#ifndef _OBJECTWALL_H_
#define _OBJECTWALL_H_

#define MAX_OBJECTWALL (2048)		//オブジェクトの最大数

//モデルの構造体
typedef enum
{
	OBJECTWALL_NTYPE00 = 0,		//ポリゴン数の多い壁
	OBJECTWALL_NTYPE01,			//壁(メインホール)
	OBJECTWALL_NTYPE02,			//壁(黒レンガ)
	OBJECTWALL_NTYPE03,			//壁(廊下)
	OBJECTWALL_NTYPE04,			//壁(白タイル)
	OBJECTWALL_NTYPE_MAX,

}OBJECTWALL_NTYPE;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 posOld;							//位置
	D3DXVECTOR3 move;							//位置
	D3DXVECTOR3 rot;							//向き
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	LPDIRECT3DTEXTURE9 pTexture[30];			//テクスチャへのポインタ

	D3DXVECTOR3 vtxMin;							//モデルの最小
	D3DXVECTOR3 vtxMax;							//モデルの最大
	int nDamageCounter;							//ダメージ状態の長さ
	int nType;									//モデルの種類
	bool bUse;									//モデルが使用されているかどうか
	D3DXMATERIAL pMatE;							//エディット状態のマテリアル
	int nIdxModelParent; //親子設定
}ObjectWall;

//プロトタイプ宣言
void InitObjectWall(void);
void UninitObjectWall(void);
void UpdateObjectWall(void);
void DrawObjectWall(void);
void UpdateEditObjectWall(void);
void DrawEditObjectWall(void);
void SetObjectWall(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void FalseObjectWall(void);
void CollisionRotObjectWall(int nCnt);
D3DXVECTOR3 CollisionOuterProductObjectWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool EditCollisionObjectWall(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
bool CollisionObjectWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionObjectWallShadow(D3DXVECTOR3 *pPos);
ObjectWall * GetObjectWall(void);
#endif