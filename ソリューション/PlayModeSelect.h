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
#define NUM_PLAYMODE		(4)			//ステージの最大数

//モード選択の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;
	int nType;
	int CurrentSelectNumber;
	bool bStage;
} PlayerModeSelect;

//プロトタイプ宣言
void InitPlayerModeSelect(void);
void UninitPlayerModeSelect(void);
void UpdatePlayerModeSelect(void);
void DrawPlayerModeSelect(void);
PlayerModeSelect GetPlayerModeSelect(void);

#endif
