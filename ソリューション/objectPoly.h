//============================
//
//�t�B�[���h����(field.h)
//Author:���� �F�M
//
//============================

#ifndef _OBJECTPOLY_H_   //���̃}�N����`������Ă��Ȃ�������
#define _OBJECTPOLY_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N���ϐ�
#define MAX_OBJECTPOLY (512)  //���̍ő吔

//���̍\����
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 rot; //����
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	float fWidth;		//��
	float fHeight;		//����
	bool bUse;		//�g�p���Ă��邩�ǂ���
}ObjectPoly;

//�v���g�^�C�v�錾
void InitObjectPoly(void);
void UninitObjectPoly(void);
void UpdateObjectPoly(void);
void UpdateEditObjectPoly(void);
void DrawObjectPoly(void);
void DrawEditObjectPoly(void);
void SetObjectPoly(D3DXVECTOR3 pos, float Wight, float Height);
void EditCollisionObjectPoly(D3DXVECTOR3 pos, float Size);
ObjectPoly * GetObjectPoly(void);

#endif

