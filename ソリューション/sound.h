#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	//SOUND_LABEL_BGM_TITLE = 0,			// タイトル
	SOUND_LABEL_SE_WALK = 0,				//プレイヤーの歩き
	SOUND_LABEL_SE_RUN,					//プレイヤーのダッシュ
	SOUND_LABEL_SE_STELTH,				//プレイヤーの忍び足
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
