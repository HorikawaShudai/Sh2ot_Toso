#ifndef _PLAYERBG_H_
#define _PLAYERBG_H_

//マクロ定義
#define MAX_MODEL (32)	//モデルの最大数
#define MAX_PARTS (13)	//パーツの総数
#define MAX_KEY (6)	//キーの総数

//プレイヤーのモーション
typedef enum
{
	PLAYERBG_ACTION_WAIT = 0,
	PLAYERBG_ACTION_MOVE,
	PLAYERBG_ACTION_JUMP,
	PLAYERBG_ACTION_MAX,

}MOTION_TYPE;

//キーの構造体
typedef struct
{
	float fPosX;		//位置X
	float fPosY;		//位置Y
	float fPosZ;		//位置Z
	float fRotX;		//向きX
	float fRotY;		//向きY
	float fRotZ;		//向きZ
}KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;				//再生フレーム
	KEY aKey[MAX_PARTS];		//各モデルのキー要素[パーツの総数]
}KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;						//ループするかどうか
	int NumKey;						//各モデルのキー要素
	KEY_INFO aKeyInfo[MAX_KEY];			//キー情報[キーの総数]
}MOTION_INFO;

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
}Model;

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
	int nLife;									//プレイヤーの体力
	int nNextLife;								//プレイヤーが引き継ぐ体力

	Model aModel[MAX_MODEL];					//モデル(パーツ)
	int nNumModel;								//モデル(パーツ)の総数
	MOTION_INFO aMotionInfo[PLAYERBG_ACTION_MAX];	//モーションの情報[モーションの総数]
	int nNumMotion;								//モーションの総数
	MOTION_TYPE MotionType;						//モーションの種類
	bool bLoopMotion;							//ループするかどうか
	int nNumkey;								//キーの総数
	int nkey;									//現在のキーNo.
	int nCounterMotion;							//モーションのカウンター
	int g_nNextKey;							//モーション時の次のキー
	bool g_bMotion;							//モーションしているかどうか

	bool bJump;									//ジャンプが使用できるかどうか
	bool bUse;									//プレイヤーを描画するかどうか
}PlayerBG;

//プロトタイプ宣言
void InitPlayerBG(void);
void UninitPlayerBG(void);
void UpdatePlayerBG(void);
void DrawPlayerBG(void);
void UpdateMotion(int nCnt);
void SetMotion(MOTION_TYPE nType, int nCnt);
void LoadMotion(int nPlayerBG);
void PlayerBGMoveInput(int nCnt);
void PlayerBGRotUpdate(int nCnt);
PlayerBG * GetPlayerBG(void);
#endif