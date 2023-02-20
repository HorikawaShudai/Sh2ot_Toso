//========================================================================================
//
// オブジェクトの処理[Object00.h]
// Author: 坂本　翔唯
// Author: 丹野竜之介
//
//========================================================================================
#ifndef _OBJECT00_H_
#define _OBJECT00_H_

#define MAX_OBJECT00 (1024)		//オブジェクトの最大数

//モデルの構造体
typedef enum
{
	OBJECT00_NTYPE00 = 0,		//ポリゴン数の多い壁
	OBJECT00_NTYPE01,			//階段
	OBJECT00_NTYPE02,			//階段上
	OBJECT00_NTYPE03,			//受付
	OBJECT00_NTYPE04,			//机
	OBJECT00_NTYPE05,			//ホコリ
	OBJECT00_NTYPE06,			//がれき
	OBJECT00_NTYPE07,			//ラボテーブル
	OBJECT00_NTYPE08,			//ラウンジ
	OBJECT00_NTYPE09,			//カルチャータンク
	OBJECT00_NTYPE10,			//カルチャータンク(大)
	OBJECT00_NTYPE11,			//マシン					研究室
	OBJECT00_NTYPE12,			//積み重なった椅子
	OBJECT00_NTYPE13,			//積み重なった机
	OBJECT00_NTYPE14,			//がれきが乗ってるマシン
	OBJECT00_NTYPE15,			//色々なものが重なっているオブジェクト
	OBJECT00_NTYPE16,			//崩れてるアーチ階段
	OBJECT00_NTYPE17,			//モニター
	OBJECT00_NTYPE18,			//檻
	OBJECT00_NTYPE19,			//ポット					研究室
	OBJECT00_NTYPE20,			//牢屋						収容
	OBJECT00_NTYPE21,			//下に落ちてるがれき
	OBJECT00_NTYPE22,			//カーテン
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
void InitObject00(void);
void UninitObject00(void);
void UpdateObject00(void);
void DrawObject00(void);
void UpdateEditObject00(void);
void DrawEditObject00(void);
void SetObject00(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void FalseObject00(void);
void CollisionRotObject00(int nCnt);
D3DXVECTOR3 CollisionOuterProductObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool EditCollisionObject00(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
bool CollisionObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionObject00Shadow(D3DXVECTOR3 *pPos);
Object00 * GetObject00(void);
#endif