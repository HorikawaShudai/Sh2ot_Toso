#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"


//���̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���݈ʒu
	bool bUse;			//�g�p�̗L��
}MOON;//�J

	  //�J�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���݈ʒu
	D3DXVECTOR3 move;	//�ړ���
	bool bUse;			//�g�p�̗L��
}RAIN;//�J

	  //�v���g�^�C�v�錾
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
#endif
