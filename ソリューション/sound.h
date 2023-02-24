#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,			// �^�C�g��BGM(�J)
	SOUND_LABEL_THUNDER,				//���̉�
	SOUND_LABEL_WIND,					//���̉�
	SOUND_LABEL_CHOICE,					//�I����
	SOUND_LABEL_ENTER,					//���艹
	SOUND_LABEL_PAPER,					//�����߂��鉹
	SOUND_LABEL_SE_WALK,				//�v���C���[�̕���
	SOUND_LABEL_SE_RUN,					//�v���C���[�̃_�b�V��
	SOUND_LABEL_SE_STELTH,				//�v���C���[�̔E�ё�
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
