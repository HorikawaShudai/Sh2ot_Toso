//======================================================================================
//
//�X�e�[�W����[stage.h]
//Author;���}���@�V
//
//======================================================================================
#ifndef _PLAYMODESELECT_H_
#define _PLAYMODESELECT_H_

#include "main.h"

//�}�N����`


//���[�h�I���̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;
	int nType;
	int CurrentModeNumber;
	bool bStage;
} PlayerModeSelect;

//�v���g�^�C�v�錾
void InitPlayModeSelect(void);
void UninitPlayModeSelect(void);
void UpdatePlayModeSelect(void);
void DrawPlayModeSelect(void);
PlayerModeSelect GetPlayModeSelect(void);

#endif
