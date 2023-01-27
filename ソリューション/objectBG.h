#ifndef _OBJECTBG_H_
#define _OBJECTBG_H_

#define MAX_OBJECTBG (1024)		//オブジェクトの最大数

//モデルの構造体
typedef enum
{
	OBJECTBG_NTYPE00 = 0,
	OBJECTBG_NTYPE01,
	OBJECTBG_NTYPE_MAX,

}OBJECTBG_NTYPE;

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
}ObjectBG;

//プロトタイプ宣言
void InitObjectBG(void);
void UninitObjectBG(void);
void UpdateObjectBG(void);
void DrawObjectBG(void);
void UpdateEditObjectBG(void);
void DrawEditObjectBG(void);
void SetObjectBG(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void FalseObjectBG(void);
void CollisionRotObjectBG(int nCnt);
bool EditCollisionObjectBG(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionObjectBGShadow(D3DXVECTOR3 *pPos);
ObjectBG * GetObjectBG(void);
#endif
