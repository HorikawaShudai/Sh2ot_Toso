#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,			// タイトルBGM(雨)
	SOUND_LABEL_BGM_GAMEOVER,			//ゲームオーバーBGM(ノイズ)
	SOUND_LABEL_THUNDER,				//雷の音
	SOUND_LABEL_WIND,					//風の音
	SOUND_LABEL_CHOICE,					//選択音
	SOUND_LABEL_ENTER,					//決定音
	SOUND_LABEL_PAPER,					//紙をめくる音
	SOUND_LABEL_SE_WALK,				//プレイヤーの歩き
	SOUND_LABEL_SE_DOOR,				//ドアの開閉音
	SOUND_LABEL_SE_ENEMYMOVE,			//敵の移動音
	SOUND_LABEL_SE_GETKEY,				//鍵の入手音
	SOUND_LABEL_SE_DAMAGE,				//ダメージ音
	SOUND_LABEL_SE_NOIZE,				//ダメージ後のノイズ音
	SOUND_LABEL_SE_NOKEY,				//鍵を持っていないときのドアの音
	SOUND_LABEL_SE_UNLOCKKEY,			//ドアの鍵が開く音
	SOUND_LABEL_SE_NO_RUN,				//息切れ音
	SOUND_LABEL_SE_ENEMYFIND,			//敵に見つかる音
	SOUND_LABEL_SE_DEATH,				//死亡時の音
	SOUND_LABEL_SE_NORMAL_NOIZE,		//普通のノイズの音
	SOUND_LABEL_SE_SMALL_NOIZE,			//小さめのノイズの音
	SOUND_LABEL_SE_BIG_NOIZE,			//大き目のノイズの音

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
