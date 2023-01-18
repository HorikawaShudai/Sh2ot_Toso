#ifndef _PLAYER_H_
#define _PLAYER_H_

//マクロ定義
#define MAX_MODEL (32)	//モデルの最大数

//プレイヤーの構造体
typedef enum
{
	PLAYER_NORMAL = 0,
	PLAYER_WAIT,
	PLAYER_DAMAGE,
	PLAYER_HIT,
	PLAYER_STATE_MAX,

}PLAYER_STATE;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;							//現在の位置
	D3DXVECTOR3 posOld;							//過去の位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 NormarizeMove;					//移動量
	D3DXVECTOR3 rot;							//向き
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	D3DXVECTOR3 vtxMin;							//モデルの最小
	D3DXVECTOR3 vtxMax;							//モデルの最大
	PLAYER_STATE State;							//プレイヤーの状態
	int nLife;									//プレイヤーの体力
	int nNextLife;								//プレイヤーが引き継ぐ体力
	int nWaitCounter;							//待機状態の長さ
	int nDamageCounter;							//ダメージ状態の長さ
	int nHitCounter;							//ヒット状態の長さ
	int nNumModel;								//モデル(パーツ)の総数
	bool bJump;									//ジャンプが使用できるかどうか
	bool bUse;									//プレイヤーが使用できるかどうか
	D3DXMATERIAL pMatH;							//ヒット状態のマテリアル
	D3DXMATERIAL pMatD;							//ダメージ状態のマテリアル
	D3DXMATERIAL pMatW;							//待機状態のマテリアル
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void PlayerMotion(void);
void PlayerMoveInput(void);
void PlayerRotUpdate(void);
void PlayerHit(void);
void CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY);
void DrawPlayer(void);
void SetNextLife(void);
Player * GetPlayer(void);
#endif