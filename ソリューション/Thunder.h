#ifndef _THUNDER_H_
#define _THUNDER_H_

#include "main.h"

//���̏�Ԃ̍\���̐錾
typedef enum
{
	THUNDER_NONE = 0,		//�������Ă��Ȃ����
	THUNDER_MOVE,			//�t�F�[�h���
}THUNDER_TYPE;

//���̍\���̐錾
typedef struct
{
	bool bUse;				//�\�����
	D3DXVECTOR3 pos;		//�\���ʒu
	D3DXCOLOR col;			//���̐F
	THUNDER_TYPE nType;		//���̏��
}THUNDER;

//�v���g�^�C�v�錾
void InitThunder(void);
void UninitThunder(void);
void UpdateThunder(void);
void DrawThunder(void);
void SetThunder(void);
THUNDER GetThunder(void);
#endif
