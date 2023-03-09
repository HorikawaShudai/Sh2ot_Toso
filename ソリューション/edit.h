//========================================================================================
//
// ステージのエディット処理[edit.h]
// Author: 坂本　翔唯
//
//========================================================================================
#ifndef _EDIT_H_
#define _EDIT_H_

//マクロ定義
//#define SET_STAGE_TEXT ("data\\TEXT\\Map_tousou2.txt")		//スタートメッセージがあるかどうかの確認
#define SET_STAGE_TEXT ("data\\TEXT\\Map_tousou2.txt")		//スタートメッセージがあるかどうかの確認

//プロトタイプ宣言
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void SaveEdit(void);
#endif