#ifndef _BG_OBJECT_H_
#define _BG_OBJECT_H_

#define MAX_OBJECT00 (1024)		//オブジェクトの最大数

//モデルの構造体
typedef enum
{
	OBJECT00_NTYPE00 = 0,
	OBJECT00_NTYPE01,
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
	D3DXMATERIAL pMatE;							//エディット状態のマテリアル
	int nIdxModelParent; //親子設定
}Object00;

//プロトタイプ宣言
void InitBg_object(void);
void UninitBg_object(void);
void UpdateBg_object(void);
void DrawBg_object(void);
void UpdateEditBg_object(void);
void DrawEditBg_object(void);
void SetBg_object(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void FalseBg_object(void);
void CollisionRotBg_object(int nCnt);
bool EditCollisionBg_object(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
bool CollisionBg_object(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionBg_objectShadow(D3DXVECTOR3 *pPos);
Object00 * GetBg_object(void);
#endif
