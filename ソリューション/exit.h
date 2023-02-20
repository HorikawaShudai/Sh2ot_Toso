//========================================================================================
//
// 出口の処理[exit.h]
// Author: 坂本　翔唯
//
//========================================================================================
#ifndef _EXIT_H_
#define _EXIT_H_

#define MAX_EXIT (32)		//鍵の最大数

typedef enum
{
	EXIT_TYPE_BIGFRAME = 0,			//大きい扉の枠(左右)
	EXIT_TYPE_BIGFRAMEUP,		//大きい扉の枠(上)
	EXIT_TYPE_BIGDOOR_R,			//大きい扉 右側
	EXIT_TYPE_BIGDOOR_L,			//大きい扉 左側
	EXIT_TYPE_MAX,					//列挙の最大
}EXIT_TYPE;

//出口の構造体
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 posOld;							//位置
	D3DXVECTOR3 move;							//位置
	D3DXVECTOR3 rot;							//向き
	D3DXVECTOR3 rotSave;						//向きの保存
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	LPDIRECT3DTEXTURE9 pTexture[30];			//テクスチャへのポインタ

	D3DXVECTOR3 vtxMin;							//モデルの最小
	D3DXVECTOR3 vtxMax;							//モデルの最大
	int nType;									//モデルの種類
	int nExitOKcnt;								//脱出可能までのカウント
	bool bUse;									//モデルが使用されているかどうか
	bool bExitOK;								//脱出可能であるかどうか
	int nIdxModelParent;						//親子設定
} ExitParts;


typedef struct
{
	ExitParts parts[MAX_EXIT];
	D3DXVECTOR3 PseudoCenter;
	bool bUse;

}EXIT;

//プロトタイプ宣言
void InitExit(void);
void UninitExit(void);
void UpdateExit(void);
void DrawExit(void);
void SetExit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nNumExit);
bool CollisionExit(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer);
bool CollisionExi(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);

void LoadExit(void);

#endif