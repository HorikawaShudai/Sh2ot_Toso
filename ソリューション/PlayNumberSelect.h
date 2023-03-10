//======================================================================================
//
// プレイ人数選択の処理[PlayNumberSelect.h]
// Author;小笠原　彪
//
//======================================================================================
#ifndef _PLAYNUMBERSELECT_H_
#define _PLAYNUMBERSELECT_H_

#include "main.h"

//マクロ定義
#define NUM_PLAYNUMBER		(4)			//

//プレイ人数選択の列挙型
typedef enum
{
	PLAYNUMBER_ONE,
	PLAYNUMBER_TWO,
	PLAYNUMBER_THREE,
	PLAYNUMBER_FOUR,
	PLAYNUMBER_MAX
} PLAYMODE;

//プレイ選択の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	int CurrentSelectNumber = 4;
	bool bUse;							//使われているか
	bool bPush;							//選択したかどうかの判断
} PlayNumberSelect;

//プロトタイプ宣言
void InitPlayNumberSelect(void);
void UninitPlayNumberSelect(void);
void UpdatePlayNumberSelect(void);
void DrawPlayNumberSelect(void);
PlayNumberSelect GetPlayNumberSelect(void);

#endif
