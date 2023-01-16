
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "object00.h"

#define MAX_ENEMY (64)		//�G�ő吔
#define NUM_ENEMYMODEL (2) //�G�̃p�[�c����

//���f���̍\����
typedef enum
{
	ENEMY_NTYPE00 = 0,
	ENEMY_NTYPE_MAX,

}ENEMY_NTYPE;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 posOld;							//�ʒu
	D3DXVECTOR3 move;							//�ʒu
	D3DXVECTOR3 rot;							//����
	D3DXMATRIX mtx;						//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin;							//���f���̍ŏ�
	D3DXVECTOR3 vtxMax;							//���f���̍ő�
	int nDamageCounter;							//�_���[�W��Ԃ̒���
	Object00 aModel[NUM_ENEMYMODEL]; //�����Ă郂�f���̏��
	LPDIRECT3DTEXTURE9 pTexture[30];	//�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH pMesh;		//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A���ւ̃|�C���^
	D3DXMATERIAL pMatData[80];	//�}�e���A���̃f�[�^
	DWORD dwNumMat;			//�}�e���A���̐�
	int nType;						//���f���̎��
	bool bUse;									//���f�����g�p����Ă��邩�ǂ���
}ENEMY;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void UpdateEditEnemy(void);
void DrawEditEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void CollisionRotEnemy(int nCnt);
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionEnemyShadow(D3DXVECTOR3 *pPos);
ENEMY * GetEnemy(void);
#endif#pragma once
