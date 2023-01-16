#ifndef _OBJECT00_H_
#define _OBJECT00_H_

#define MAX_OBJECT00 (64)		//オブジェクトの最大数

//モデルの構造体
typedef enum
{
	OBJECT00_NTYPE00 = 0,
	OBJECT00_NTYPE01,
	OBJECT00_NTYPE02,
	OBJECT00_NTYPE03,
	OBJECT00_NTYPE04,
	OBJECT00_NTYPE05,
	OBJECT00_NTYPE06,
	OBJECT00_NTYPE_MAX,

}OBJECT00_NTYPE;

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
	int nIdxModelParent; //親子設定
}Object00;

//プロトタイプ宣言
void InitObject00(void);
void UninitObject00(void);
void UpdateObject00(void);
void DrawObject00(void);
void UpdateEditObject00(void);
void DrawEditObject00(void);
void SetObject00(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void CollisionRotObject00(int nCnt);
bool CollisionObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionObject00Shadow(D3DXVECTOR3 *pPos);
Object00 * GetObject00(void);
#endif