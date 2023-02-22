//========================================================================================
//
// �G�l�~�[�w�b�_�[[enemy.h]
// Author: �O�� ���V��
//
//========================================================================================
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

typedef enum
{
	ENEMYSTATE_STOP = 0,	//��~���
	ENEMYSTATE_PATROL,		//����
	ENEMYSTATE_CHASE,		//�ǐ�
	ENEMYSTATE_SEEK,		//�T��
	ENEMYSTATE_ATTACK,		//�U��
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef enum
{
	ENEMYMOVE_NONE = 0,
	ENEMYMOVE_N,
	ENEMYMOVE_S,
	ENEMYMOVE_W,
	ENEMYMOVE_E,
	ENEMYMOVE_MAX
}ENEMYMOVE;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 posOld;							//�ʒu
	D3DXVECTOR3 Tgpos;							//�ڕW�ʒu
	D3DXVECTOR3 move;							//�ʒu
	D3DXVECTOR3 rot;							//����
	D3DXVECTOR3 rotDest;						//����
	D3DXMATRIX mtx;						//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin;							//���f���̍ŏ�
	D3DXVECTOR3 vtxMax;							//���f���̍ő�
	int nDamageCounter;							//�_���[�W��Ԃ̒���
	ENEMYSTATE state;							//���
	ENEMYMOVE MoveState;						//�ړ������̏��
	int StateCount;
	Object00 aModel[NUM_ENEMYMODEL]; //�����Ă郂�f���̏��
	int nType;						//���f���̎��
	bool bUse;									//���f�����g�p����Ă��邩�ǂ���
												//�l���ʂւ̋���
	float fDistanceN;
	float fDistanceS;
	float fDistanceW;
	float fDistanceE;
	float fDistanceFront;
	float fDistanceLeft;
	float fDistanceRight;

	int nCoolTurn;
}ENEMY;

//�T���p�\����
typedef struct
{
	D3DXVECTOR3 Startpos;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	int nTarget;
	float fmoveRot;
	int nLife;
	float fDistance;
}DETECT;

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
void FalseEnemy(void);
float DetectWall(D3DXVECTOR3 pos, float fmoveRot, int nLife);
bool DetectPlayer(D3DXVECTOR3 pos, float fmoveRot, int nEnemy);

#endif
