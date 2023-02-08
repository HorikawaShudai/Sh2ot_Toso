//========================================================================================
//
// ライト処理[light.h]
// Author: 坂本　翔唯
//
//========================================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//プロトタイプ宣言
void InitLight(void);
void UninitLight(void);
void UpdateLight(void);
int SetIndexLight(void);
void SetLight(int nIdxLight, D3DLIGHTTYPE nType, D3DXCOLOR Diffuse, D3DXVECTOR3 pos, D3DXVECTOR3 nVecDir, float nRange);
#endif