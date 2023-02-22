//========================================================================================
//
// オブジェクトの処理[Object00.h]
// Author: 坂本　翔唯
// Author: 丹野竜之介
//
//========================================================================================
#ifndef _OBJECT00_H_
#define _OBJECT00_H_

#define MAX_OBJECT00 (2048)		//オブジェクトの最大数

//モデルの構造体
typedef enum
{
	OBJECT00_NTYPE00 = 0,		//ポリゴン数の多い壁
	OBJECT00_NTYPE01,			//階段
	OBJECT00_NTYPE02,			//階段上
	OBJECT00_NTYPE03,			//受付
	OBJECT00_NTYPE04,			//机
	OBJECT00_NTYPE05,			//資料棚
	OBJECT00_NTYPE06,			//がれき
	OBJECT00_NTYPE07,			//ラボテーブル
	OBJECT00_NTYPE08,			//ラウンジ
	OBJECT00_NTYPE09,			//カルチャータンク			研究室
	OBJECT00_NTYPE10,			//カルチャータンク(大)		研究室
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
	OBJECT00_NTYPE23,			//薬が入ってる棚
	OBJECT00_NTYPE24,			//資料棚(小)
	OBJECT00_NTYPE25,			//資料棚(大)
	OBJECT00_NTYPE26,			//箱の置いてある棚
	OBJECT00_NTYPE27,			//ケージ
	OBJECT00_NTYPE28,			//ケージ
	OBJECT00_NTYPE29,			//フェンス
	OBJECT00_NTYPE30,			//ソファ
	OBJECT00_NTYPE31,			//柱
	OBJECT00_NTYPE32,			//パソコンが載っている机
	OBJECT00_NTYPE33,			//机の椅子
	OBJECT00_NTYPE34,			//ロッカー
	OBJECT00_NTYPE35,			//ホワイトボード
	OBJECT00_NTYPE36,			//監視カメラ
	OBJECT00_NTYPE37,			//蛍光灯
	OBJECT00_NTYPE38,			//ロングデスク
	OBJECT00_NTYPE39,			//プロジェクターのうつすほう
	OBJECT00_NTYPE40,			//観葉植物
	OBJECT00_NTYPE41,			//ゴミ箱
	OBJECT00_NTYPE42,			//パーテーション
	OBJECT00_NTYPE43,			//本棚
	OBJECT00_NTYPE44,			//コート掛け
	OBJECT00_NTYPE45,			//演説用の台
	OBJECT00_NTYPE46,			//コピー機
	OBJECT00_NTYPE47,			//ブルーシートのかかった箱
	OBJECT00_NTYPE48,			//低めの棚
	OBJECT00_NTYPE49,			//がれき
	OBJECT00_NTYPE50,			//救急ベッド
	OBJECT00_NTYPE51,			//うばぐるま
	OBJECT00_NTYPE52,			//理科室にあるデスク
	OBJECT00_NTYPE53,			//崩れた小部屋
	OBJECT00_NTYPE54,			//壁(メインホール)
	OBJECT00_NTYPE55,			//壁(黒レンガ)
	OBJECT00_NTYPE56,			//壁(廊下)
	OBJECT00_NTYPE57,			//ラボタンク
	OBJECT00_NTYPE58,			//偉い人用のテーブル
	OBJECT00_NTYPE59,			//偉い人用の椅子
	OBJECT00_NTYPE60,			//応接室の机
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