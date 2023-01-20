//============================
//
//�X�R�A�A�C�e������(score_item.h)
//Author:���� �F�M
//
//============================

#ifndef _SCORE_ITEM_H_   //���̃}�N����`������Ă��Ȃ�������
#define _SCORE_ITEM_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include <stdio.h>

//�X�R�A�A�C�e���̍ő吔
#define MAX_ITEM (128) //�X�R�A�A�C�e���̍ő吔

//�X�R�A�A�C�e���̍\����
typedef struct
{
	LPDIRECT3DTEXTURE9 _apTexture[20] = {};	//�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH pMesh = NULL; //���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat = NULL; //�}�e���A���ւ̃|�C���^
	DWORD dwNumMat = 0; //�}�e���A���̐�
	D3DXVECTOR3 VtxMax; //�X�R�A�A�C�e���̋�`�̍ő�l
	D3DXVECTOR3 VtxMin; //�X�R�A�A�C�e���̋�`�̍ŏ��l
}ITEMDATA;

//�X�R�A�A�C�e���̍\����
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 posold; //�O�̈ʒu
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 rot; //����
	D3DXMATRIX mtxWorld;  //���[���h�}�g���b�N�X
	
	bool bUse;  //�g���Ă��邩�ǂ���
	D3DXVECTOR3 VtxMax; //�X�R�A�A�C�e���̋�`�̍ő�l
	D3DXVECTOR3 VtxMin; //�X�R�A�A�C�e���̋�`�̍ŏ��l
	int nldxShadow;  //�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)
	int nLife;  //�X�R�A�A�C�e���̃��C�t
	int nCounterstate; //�X�R�A�A�C�e���̏�Ԃ𐔂��鏈��
	D3DXMATERIAL RedMat;  //�}�e���A����Ԃ����鏈��
	bool bSound; //�����g�����ǂ���
	ITEMDATA Itemdata;

}ITEM;
//�v���g�^�C�v�錾
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos);
//ENEMY *GetEnemy(void);
//void HitItem(int nCntEnemy, int nDamage);
//void ColisionItem(void);
//int ItemCount(void);
//void ReturnItem(void);

#endif

