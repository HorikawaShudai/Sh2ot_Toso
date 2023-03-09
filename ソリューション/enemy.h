//========================================================================================
//
// エネミーヘッダー[enemy.h]
// Author: 丹野 竜之介
//
//========================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "objectWall.h"
#include "objectPoly.h"

//マクロ定義
#define MAX_ENEMY (3)		//敵最大数

#define MAX_ENEMY_MODEL (32)	//モデルの最大数
#define MAX_ENEMY_PARTS (32)	//パーツの総数
#define MAX_ENEMY_KEY (16)	//キーの総数


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
	ENEMYSTATE_ATTACK_STANDBY,	//攻撃待機
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

//=======================================================モーションエリア
//敵のモーション
typedef enum
{
	ENEMY_ACTION_NORMAL = 0,
	ENEMY_ACTION_MOVE,
	ENEMY_ACTION_ATTACK,
	ENEMY_ACTION_DASH,
	ENEMY_ACTION_MAX,

}ENEMY_MOTION_TYPE;

//キーの構造体
typedef struct
{
	float fPosX;		//位置X
	float fPosY;		//位置Y
	float fPosZ;		//位置Z
	float fRotX;		//向きX
	float fRotY;		//向きY
	float fRotZ;		//向きZ
}ENEMY_KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;				//再生フレーム
	ENEMY_KEY aKey[MAX_ENEMY_PARTS];		//各モデルのキー要素[パーツの総数]
}ENEMY_KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;						//ループするかどうか
	int NumKey;						//各モデルのキー要素
	ENEMY_KEY_INFO aKeyInfo[MAX_ENEMY_KEY];			//キー情報[キーの総数]
}ENEMY_MOTION_INFO;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;							//現在の位置
	D3DXVECTOR3 posOld;							//過去の位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 vecMove;						//移動ベクトル
	D3DXVECTOR3 rot;							//向き
	D3DXVECTOR3 Setpos;							//モーション時の位置
	D3DXVECTOR3 Setrot;							//モーション時の向き
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	int nIndexModelParent;						//親モデルのインデックス
	LPDIRECT3DTEXTURE9 g_pTextureEnemyBG[100];	//テクスチャのポインタ
	DWORD g_dwNumMatEnemyBG;				//マテリアルの数
}EnemyModel;

//==========================================================================================

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;							//現在の位置
	D3DXVECTOR3 posOld;							//過去の位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 NormarizeMove;					//移動量
	D3DXVECTOR3 rot;							//向き
	D3DXMATRIX mtx;						//ワールドマトリックス
	D3DXVECTOR3 vtxMin;							//モデルの最小
	D3DXVECTOR3 vtxMax;							//モデルの最大

	ENEMYSTATE state;							//状態
	ENEMYMOVE MoveState;						//移動方向の状態
	int StateCount;

	bool bUse;									//モデルが使用されているかどうか
	//四方位への距離

	EnemyModel aModel[MAX_ENEMY_MODEL]; //持ってるモデルの情報
	int nNumModel;											//モデル(パーツ)の総数
	ENEMY_MOTION_INFO aMotionInfo[ENEMY_ACTION_MAX];		//モーションの情報[モーションの総数]
	int nNumMotion;											//モーションの総数
	ENEMY_MOTION_TYPE MotionType;							//モーションの種類
	bool bLoopMotion;										//ループするかどうか
	int nNumkey;											//キーの総数
	int nkey;												//現在のキーNo.
	int nCounterMotion;										//モーションのカウンター
	int g_nNextKey;											//モーション時の次のキー
	bool g_bMotion;											//モーションしているかどうか

	D3DXVECTOR3 Tgpos;							//目標位置
	D3DXVECTOR3 rotDest;						//向き
	float fDistanceN;
	float fDistanceS;
	float fDistanceW;
	float fDistanceE;
	float fDistanceFront;
	float fDistanceLeft;
	float fDistanceRight;

	int nCoolTurn;
	int nTarget;
	bool bHit;
	int nTargetOld;
	int nCntStop;
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
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);
void TeleportationEnemy(D3DXVECTOR3 *pPos);
void CollisionEnemyShadow(D3DXVECTOR3 *pPos);
ENEMY * GetEnemy(void);
void FalseEnemy(void);
float DetectWall(D3DXVECTOR3 pos, float fmoveRot, int nLife);
bool DetectPlayer(D3DXVECTOR3 pos, float fmoveRot, int nEnemy);

void UpdateEnemyMotion(int nCnt);
void SetEnemyMotion(ENEMY_MOTION_TYPE nType, int nCnt);
void LoadEnemyMotion(int nPlayerBG);

#endif
