#ifndef _PLAYER_H_
#define _PLAYER_H_

//マクロ定義
#define MAX_MODEL	(32)			//モデルの最大数
#define NUM_PLAYER	(3)			//プレイヤーの最大人数

//プレイヤーの状態管理
typedef enum
{
	PLAYER_NORMAL = 0,
	PLAYER_WAIT,
	PLAYER_DAMAGE,
	PLAYER_HIT,
	PLAYER_STATE_MAX,
}PLAYER_STATE;

//プレイヤーの状態管理
typedef enum
{
	PLAYER_MOVESTATE_STEALTH = 0,		//ステルス
	PLAYER_MOVESTATE_NORMAL,			//通常
	PLAYER_MOVESTATE_DASH,				//ダッシュ
	PLAYER_MOVESTATE_FATIGE,			//疲労
	PLAYER_MOVESTATE_MAX,
}PLAYER_MOVESTATE;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;							//現在の位置
	D3DXVECTOR3 posOld;							//過去の位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 NormarizeMove;					//移動量
	D3DXVECTOR3 rot;							//向き
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	PLAYER_STATE State;							//プレイヤーの状態
	PLAYER_MOVESTATE MoveState;					//プレイヤーの移動状態
	int nLife;									//プレイヤーの体力
	int nWaitCounter;							//待機状態の長さ
	int nDamageCounter;							//ダメージ状態の長さ
	int nHitCounter;							//ヒット状態の長さ
	int nNumModel;								//モデル(パーツ)の総数
	bool bUse;									//プレイヤーが使用できるかどうか
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void PlayerMoveInput(int nCnt);
void PlayerRotUpdate(int nCnt);
void PlayerHit(int nCnt,int nDamage);
void CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY);
void DrawPlayer(void);
Player * GetPlayer(void);
#endif