#ifndef _PLAYERBG_H_
#define _PLAYERBG_H_

//マクロ定義
#define MAX_PLAYER_MODEL (32)	//モデルの最大数
#define MAX_PLAYER_PARTS (32)	//パーツの総数
#define MAX_PLAYER_KEY (16)	//キーの総数

//プレイヤーのモーション
typedef enum
{
	PLAYERBG_ACTION_WAIT = 0,
	PLAYERBG_ACTION_MOVE,
	PLAYERBG_ACTION_JUMP,
	PLAYERBG_ACTION_WAIT2,
	PLAYERBG_ACTION_MAX,

}PLAYER_MOTION_TYPE;

//キーの構造体
typedef struct
{
	float fPosX;		//位置X
	float fPosY;		//位置Y
	float fPosZ;		//位置Z
	float fRotX;		//向きX
	float fRotY;		//向きY
	float fRotZ;		//向きZ
}PLAYER_KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;				//再生フレーム
	PLAYER_KEY aKey[MAX_PLAYER_PARTS];		//各モデルのキー要素[パーツの総数]
}PLAYER_KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;						//ループするかどうか
	int NumKey;						//各モデルのキー要素
	PLAYER_KEY_INFO aKeyInfo[MAX_PLAYER_KEY];			//キー情報[キーの総数]
}PLAYER_MOTION_INFO;

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
	LPDIRECT3DTEXTURE9 g_pTexturePlayerBG[100];	//テクスチャのポインタ
	DWORD g_dwNumMatPlayerBG;				//マテリアルの数
}PlayerModel;

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

	PlayerModel aModel[MAX_PLAYER_MODEL];					//モデル(パーツ)
	int nNumModel;											//モデル(パーツ)の総数
	PLAYER_MOTION_INFO aMotionInfo[PLAYERBG_ACTION_MAX];	//モーションの情報[モーションの総数]
	int nNumMotion;											//モーションの総数
	PLAYER_MOTION_TYPE MotionType;							//モーションの種類
	bool bLoopMotion;										//ループするかどうか
	int nNumkey;											//キーの総数
	int nkey;												//現在のキーNo.
	int nCounterMotion;										//モーションのカウンター
	int g_nNextKey;											//モーション時の次のキー
	bool g_bMotion;											//モーションしているかどうか

	bool bUse;									//プレイヤーを描画するかどうか
}PlayerBG;

//プロトタイプ宣言
void InitPlayerBG(void);
void UninitPlayerBG(void);
void UpdatePlayerBG(void);
void DrawPlayerBG(void);
void UpdatePlayerMotion(int nCnt);
void SetPlayerMotion(PLAYER_MOTION_TYPE nType, int nCnt);
void LoadPlayerMotion(int nPlayerBG);
PlayerBG * GetPlayerBG(void);
#endif