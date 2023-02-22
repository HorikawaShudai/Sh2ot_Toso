//========================================================================================
//
// エネミーヘッダー[enemy.h]
// Author: 丹野 竜之介
//
//========================================================================================
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

typedef enum
{
	ENEMYSTATE_STOP = 0,	//停止状態
	ENEMYSTATE_PATROL,		//巡回
	ENEMYSTATE_CHASE,		//追跡
	ENEMYSTATE_SEEK,		//探す
	ENEMYSTATE_ATTACK,		//攻撃
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef enum
{
	ENEMYMOVE_NONE = 0,
	ENEMYMOVE_N,
	ENEMYMOVE_S,
	ENEMYMOVE_W,
	ENEMYMOVE_E,
	ENEMYMOVE_MAX
}ENEMYMOVE;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 posOld;							//位置
	D3DXVECTOR3 Tgpos;							//目標位置
	D3DXVECTOR3 move;							//位置
	D3DXVECTOR3 rot;							//向き
	D3DXVECTOR3 rotDest;						//向き
	D3DXMATRIX mtx;						//ワールドマトリックス
	D3DXVECTOR3 vtxMin;							//モデルの最小
	D3DXVECTOR3 vtxMax;							//モデルの最大
	int nDamageCounter;							//ダメージ状態の長さ
	ENEMYSTATE state;							//状態
	ENEMYMOVE MoveState;						//移動方向の状態
	int StateCount;
	Object00 aModel[NUM_ENEMYMODEL]; //持ってるモデルの情報
	int nType;						//モデルの種類
	bool bUse;									//モデルが使用されているかどうか
												//四方位への距離
	float fDistanceN;
	float fDistanceS;
	float fDistanceW;
	float fDistanceE;
	float fDistanceFront;
	float fDistanceLeft;
	float fDistanceRight;

	int nCoolTurn;
}ENEMY;

//探査用構造体
typedef struct
{
	D3DXVECTOR3 Startpos;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	int nTarget;
	float fmoveRot;
	int nLife;
	float fDistance;
}DETECT;

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
void FalseEnemy(void);
float DetectWall(D3DXVECTOR3 pos, float fmoveRot, int nLife);
bool DetectPlayer(D3DXVECTOR3 pos, float fmoveRot, int nEnemy);

#endif
