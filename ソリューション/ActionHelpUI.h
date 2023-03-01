#ifndef _ACTIONHELPUI_H_
#define _ACTIONHELPUI_H_

#define MAX_ACTIONHELPUI (128)		//影の最大数

//モデルの構造体
typedef enum
{
	ACTIONHELPUI_KEY = 0,
	ACTIONHELPUI_DOOR,
	ACTIONHELPUI_MAX,

}ACTIONHELPUI_TYPE;

//ビルボード構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	ACTIONHELPUI_TYPE nType;					//種類
	bool bUse;									//使用しているかどうか
}ActionHelpUI;

//プロトタイプ宣言
void InitActionHelpUI(void);
void UninitActionHelpUI(void);
void UpdateActionHelpUI(void);
void DrawActionHelpUI(int nCntPlayer, bool GetKey);
int SetActionHelpUI(D3DXVECTOR3 pos, ACTIONHELPUI_TYPE Type);
void FalseActionHelpUI(int Idx);
ActionHelpUI * GetActionHelpUI(void);
#endif