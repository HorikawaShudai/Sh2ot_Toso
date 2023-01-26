#ifndef _EXIT_H_
#define _EXIT_H_

#define MAX_EXIT (32)		//鍵の最大数

typedef enum
{
	EXIT_TYPE_ITEM = 0,
	EXIT_TYPE_MAX,
}EXIT_TYPE;

//鍵の構造体
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
	int nType;									//モデルの種類
	bool bUse;									//モデルが使用されているかどうか
	bool bExitOK;								//脱出可能であるかどうか
	int nIdxModelParent; //親子設定
}EXIT;

//プロトタイプ宣言
void InitExit(void);
void UninitExit(void);
void UpdateExit(void);
void DrawExit(void);
void SetExit(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
bool CollisionExit(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer);
#endif