//========================================================================================
//
// ���C�g����[light.h]
// Author: ��{�@�ėB
//
//========================================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//�v���g�^�C�v�錾
void InitLight(void);
void UninitLight(void);
void UpdateLight(void);
int SetIndexLight(void);
void SetLight(int nIdxLight, D3DLIGHTTYPE nType, D3DXCOLOR Diffuse, D3DXVECTOR3 pos, D3DXVECTOR3 nVecDir, float nRange);
#endif