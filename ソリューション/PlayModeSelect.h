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
#define NUM_PLAYMODE		(4)			//�X�e�[�W�̍ő吔

//���[�h�I���̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;
	int nType;
	int CurrentSelectNumber;
	bool bStage;
} PlayerModeSelect;

//�v���g�^�C�v�錾
void InitPlayerModeSelect(void);
void UninitPlayerModeSelect(void);
void UpdatePlayerModeSelect(void);
void DrawPlayerModeSelect(void);
PlayerModeSelect GetPlayerModeSelect(void);

#endif
