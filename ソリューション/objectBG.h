//========================================================================================
//
// 背景用オブジェクトの処理[ObjectBG.h]
// Author: 坂本　翔唯
//
//========================================================================================
#ifndef _OBJECTBG_H_
#define _OBJECTBG_H_

#define MAX_OBJECTBG (1024)		//オブジェクトの最大数

//モデルの構造体
typedef enum
{
	OBJECTBG_NTYPE00 = 0,
	OBJECTBG_NTYPE01,
	OBJECTBG_NTYPE02,
	OBJECTBG_NTYPE03,
	OBJECTBG_NTYPE04,
	OBJECTBG_NTYPE05,
	OBJECTBG_NTYPE06,			//換気扇
	OBJECTBG_NTYPE07,			//コルクボード
	OBJECTBG_NTYPE08,			//壁掛けアート
	OBJECTBG_NTYPE09,			//資料単体
	OBJECTBG_NTYPE10,			//ライトのスイッチ
	OBJECTBG_NTYPE11,			//資料単体
	OBJECTBG_NTYPE12,			//通気口
	OBJECTBG_NTYPE13,			//窓
	OBJECTBG_NTYPE14,			//プロジェクターのうつされるほう
	OBJECTBG_NTYPE15,			//時計
	OBJECTBG_NTYPE16,			//階段_右_上
	OBJECTBG_NTYPE17,			//階段_左_上
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
