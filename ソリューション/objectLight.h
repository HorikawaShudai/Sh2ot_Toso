//========================================================================================
//
// 背景用オブジェクトの処理[ObjectLight.h]
// Author: 坂本　翔唯
//
//========================================================================================
#ifndef _OBJECTLIGHT_H_
#define _OBJECTLIGHT_H_

#define MAX_OBJECTLIGHT (1024)		//オブジェクトの最大数

//モデルの構造体
typedef enum
{
	OBJECTLIGHT_NTYPE00 = 0,
	OBJECTLIGHT_NTYPE01,
	OBJECTLIGHT_NTYPE02,
	OBJECTLIGHT_NTYPE03,
	OBJECTLIGHT_NTYPE04,
	OBJECTLIGHT_NTYPE05,
	OBJECTLIGHT_NTYPE06,

	OBJECTLIGHT_NTYPE_MAX,

}OBJECTLIGHT_NTYPE;

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
	int LightIdx;								//ライトの使用番号
}ObjectLight;

//プロトタイプ宣言
void InitObjectLight(void);
void UninitObjectLight(void);
void UpdateObjectLight(void);
void DrawObjectLight(void);
void UpdateEditObjectLight(void);
void DrawEditObjectLight(void);
void SetObjectLight(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void FalseObjectLight(void);
void CollisionRotObjectLight(int nCnt);
bool EditCollisionObjectLight(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionObjectLightShadow(D3DXVECTOR3 *pPos);
ObjectLight * GetObjectLight(void);
#endif
