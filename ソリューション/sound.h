#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,			// �^�C�g��BGM(�J)
	SOUND_LABEL_BGM_GAMEOVER,			//�Q�[���I�[�o�[BGM(�m�C�Y)
	SOUND_LABEL_THUNDER,				//���̉�
	SOUND_LABEL_WIND,					//���̉�
	SOUND_LABEL_CHOICE,					//�I����
	SOUND_LABEL_ENTER,					//���艹
	SOUND_LABEL_PAPER,					//�����߂��鉹
	SOUND_LABEL_SE_WALK,				//�v���C���[�̕���
	SOUND_LABEL_SE_DOOR,				//�h�A�̊J��
	SOUND_LABEL_SE_ENEMYMOVE,			//�G�̈ړ���
	SOUND_LABEL_SE_GETKEY,				//���̓��艹
	SOUND_LABEL_SE_DAMAGE,				//�_���[�W��
	SOUND_LABEL_SE_NOIZE,				//�_���[�W��̃m�C�Y��
	SOUND_LABEL_SE_NOKEY,				//���������Ă��Ȃ��Ƃ��̃h�A�̉�
	SOUND_LABEL_SE_UNLOCKKEY,			//�h�A�̌����J����
	SOUND_LABEL_SE_NO_RUN,				//���؂ꉹ
	SOUND_LABEL_SE_ENEMYFIND,			//�G�Ɍ����鉹
	SOUND_LABEL_SE_DEATH,				//���S���̉�
	SOUND_LABEL_SE_NORMAL_NOIZE,		//���ʂ̃m�C�Y�̉�
	SOUND_LABEL_SE_SMALL_NOIZE,			//�����߂̃m�C�Y�̉�
	SOUND_LABEL_SE_BIG_NOIZE,			//�傫�ڂ̃m�C�Y�̉�

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
