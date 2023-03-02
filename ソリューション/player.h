//========================================================================================
//
// プレイヤーの処理[player.h]
// Author: 小笠原　彪
// Author: 坂本　翔唯
// Author: 丹野竜之介
//
//========================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//マクロ定義
#define NUM_PLAYER	(4)			//プレイヤーの最大人数

//プレイヤーの状態管理
typedef enum
{
	PLAYER_NORMAL = 0,
	PLAYER_WAIT,
	PLAYER_HIT,
	PLAYER_EXSIT,
	PLAYER_DAMAGE,
	PLAYER_SMITE,
	PLAYER_DEATH,
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

//プレイヤーの構造体
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
	int nNumModel;								//モデル(パーツ)の総数
	int VibrtionTrueCount;						//バイブレーション中のカウント
	int VibrtionFalseCount;						//バイブレーションをしていない間のカウント
	int VibrtionTime;							//バイブレーションの長さ
	int LightIdx00;								//ライトの使用番号00
	int nWaitCounter;							//プレイヤーの待機状態の長さ
	int nDamageCounter;							//プレイヤーのダメージ状態の長さ
	int nDeathCounter;							//プレイヤーの死亡状態の長さ
	int nHitCounter;							//プレイヤーのヒット状態の長さ

	bool bUse;									//プレイヤーが使用できるかどうか
	bool bGetKey;								//プレイヤーが鍵を持っているかどうか
	bool bAppear;								//敵を視認できるかどうか
	bool bVibrtion;								//バイブレーションをしているかどうか
	bool bExit;									//脱出しているかどうか
	bool bCheck;								//チェックがついているかどうか
	int nStelthCnt;								//チュートリアル用ステルス状態を数える処理
	int nVibCnt;								//チュートリアル用バイブレーション状態を数える処理
	bool KeyHelpUI;								//鍵のヘルプUIの表示がされているかどうか
	bool ExitHelpUI;							//出口のヘルプUIの表示がされているかどうか
	int  nPlayerSECount;						//プレイヤーのSEを鳴らす間隔
	bool bChase;								//敵に追いかけられているかどうか
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void PlayerMoveInput(int nCnt);
void PlayerRotUpdate(int nCnt);
void PlayerState(int nCnt);
void PlayerDistance(int nCnt);
void PlayerVibrtionUpdate(int nCnt);
void PlayerSetVibrtion(int nCnt, int nTrueCounter, int nFalseCounter, int nLeftPower, int RightPoewr);
void PlayerHit(int nCnt, int nDamage);
int CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY);
D3DXVECTOR3 CollisionOuterProductPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn, float MinY, float MaxY);
void PlayerAllDown(void);
Player * GetPlayer(void);
#endif