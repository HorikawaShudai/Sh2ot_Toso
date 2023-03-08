#ifndef _NEEDKEYPOLYGON_H_
#define _NEEDKEYPOLYGON_H_

#define MAX_NEEDKEYPOLYGON (3)		//影の最大数

//モデルの構造体
typedef enum
{
	NEEDKEYPOLYGON_CENTER = 0,
	NEEDKEYPOLYGON_LEFT,
	NEEDKEYPOLYGON_RIGHT,
	NEEDKEYPOLYGON_MAX,

}NEEDKEYPOLYGON_TYPE;

//ビルボード構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	float fSize;								//サイズ
	bool bUse;									//使用しているかどうか
}NeedKeyPolygon;

//プロトタイプ宣言
void InitNeedKeyPolygon(void);
void UninitNeedKeyPolygon(void);
void UpdateNeedKeyPolygon(void);
void DrawNeedKeyPolygon(int nCntPlayer);
void SetNeedKeyPolygon(D3DXVECTOR3 pos);
void FalseNeedKeyPolygon(void);
NeedKeyPolygon * GetNeedKeyPolygon(void);
#endif