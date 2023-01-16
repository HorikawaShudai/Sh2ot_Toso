
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "object00.h"

#define MAX_ENEMY (64)		//敵最大数
#define NUM_ENEMYMODEL (2) //敵のパーツ総数

//モデルの構造体
typedef enum
{
	ENEMY_NTYPE00 = 0,
	ENEMY_NTYPE_MAX,

}ENEMY_NTYPE;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 posOld;							//位置
	D3DXVECTOR3 move;							//位置
	D3DXVECTOR3 rot;							//向き
	D3DXMATRIX mtx;						//ワールドマトリックス
	D3DXVECTOR3 vtxMin;							//モデルの最小
	D3DXVECTOR3 vtxMax;							//モデルの最大
	int nDamageCounter;							//ダメージ状態の長さ
	Object00 aModel[NUM_ENEMYMODEL]; //持ってるモデルの情報
	LPDIRECT3DTEXTURE9 pTexture[30];	//テクスチャへのポインタ
	LPD3DXMESH pMesh;		//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアルへのポインタ
	D3DXMATERIAL pMatData[80];	//マテリアルのデータ
	DWORD dwNumMat;			//マテリアルの数
	int nType;						//モデルの種類
	bool bUse;									//モデルが使用されているかどうか
}ENEMY;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void UpdateEditEnemy(void);
void DrawEditEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void CollisionRotEnemy(int nCnt);
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionEnemyShadow(D3DXVECTOR3 *pPos);
ENEMY * GetEnemy(void);
#endif#pragma once
