//======================================================================================
//
//ステージ処理[stage.h]
//Author;小笠原　彪
//
//======================================================================================
#ifndef _PLAYMODESELECT_H_
#define _PLAYMODESELECT_H_

#include "main.h"

//マクロ定義


//モード選択の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;
	int nType;
	int CurrentModeNumber;
	bool bStage;
} PlayerModeSelect;

//プロトタイプ宣言
void InitPlayModeSelect(void);
void UninitPlayModeSelect(void);
void UpdatePlayModeSelect(void);
void DrawPlayModeSelect(void);
PlayerModeSelect GetPlayModeSelect(void);

#endif
