//=========================================================================================
//
// �X�^�~�i���� [stamina.h]
// Author:
//
//=========================================================================================
#ifndef _STAMINA_H_
#define _STAMINA_H_

#include "main.h"

//�X�^�~�i�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXCOLOR col;				//�F
	int nFalseTime;				//�X�^�~�i���g���Ă��Ȃ����Ԃ̃J�E���g
	float fGaugeSize;			//�X�^�~�i�̃T�C�Y(����)
	bool bUse;					//�g���Ă��邩�ǂ���
} Stamina;

//*********************************************
//�v���g�^�C�v�錾
//*********************************************
void InitStamina(void);
void UninitStamina(void);
void UpdateStamina(void);
void DrawStamina(void);

void SetStamina(D3DXVECTOR3 pos);

#endif
