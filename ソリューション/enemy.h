//========================================================================================
//
// �G�l�~�[�w�b�_�[[enemy.h]
// Author: �O�� ���V��
//
//========================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "objectWall.h"
#include "objectPoly.h"

//�}�N����`
#define MAX_ENEMY (3)		//�G�ő吔

#define MAX_ENEMY_MODEL (32)	//���f���̍ő吔
#define MAX_ENEMY_PARTS (32)	//�p�[�c�̑���
#define MAX_ENEMY_KEY (16)	//�L�[�̑���


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
	ENEMYSTATE_ATTACK_STANDBY,	//�U���ҋ@
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

//=======================================================���[�V�����G���A
//�G�̃��[�V����
typedef enum
{
	ENEMY_ACTION_NORMAL = 0,
	ENEMY_ACTION_MOVE,
	ENEMY_ACTION_ATTACK,
	ENEMY_ACTION_DASH,
	ENEMY_ACTION_MAX,

}ENEMY_MOTION_TYPE;

//�L�[�̍\����
typedef struct
{
	float fPosX;		//�ʒuX
	float fPosY;		//�ʒuY
	float fPosZ;		//�ʒuZ
	float fRotX;		//����X
	float fRotY;		//����Y
	float fRotZ;		//����Z
}ENEMY_KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;				//�Đ��t���[��
	ENEMY_KEY aKey[MAX_ENEMY_PARTS];		//�e���f���̃L�[�v�f[�p�[�c�̑���]
}ENEMY_KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;						//���[�v���邩�ǂ���
	int NumKey;						//�e���f���̃L�[�v�f
	ENEMY_KEY_INFO aKeyInfo[MAX_ENEMY_KEY];			//�L�[���[�L�[�̑���]
}ENEMY_MOTION_INFO;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//���݂̈ʒu
	D3DXVECTOR3 posOld;							//�ߋ��̈ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 vecMove;						//�ړ��x�N�g��
	D3DXVECTOR3 rot;							//����
	D3DXVECTOR3 Setpos;							//���[�V�������̈ʒu
	D3DXVECTOR3 Setrot;							//���[�V�������̌���
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	int nIndexModelParent;						//�e���f���̃C���f�b�N�X
	LPDIRECT3DTEXTURE9 g_pTextureEnemyBG[100];	//�e�N�X�`���̃|�C���^
	DWORD g_dwNumMatEnemyBG;				//�}�e���A���̐�
}EnemyModel;

//==========================================================================================

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//���݂̈ʒu
	D3DXVECTOR3 posOld;							//�ߋ��̈ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 NormarizeMove;					//�ړ���
	D3DXVECTOR3 rot;							//����
	D3DXMATRIX mtx;						//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin;							//���f���̍ŏ�
	D3DXVECTOR3 vtxMax;							//���f���̍ő�

	ENEMYSTATE state;							//���
	ENEMYMOVE MoveState;						//�ړ������̏��
	int StateCount;

	bool bUse;									//���f�����g�p����Ă��邩�ǂ���
	//�l���ʂւ̋���

	EnemyModel aModel[MAX_ENEMY_MODEL]; //�����Ă郂�f���̏��
	int nNumModel;											//���f��(�p�[�c)�̑���
	ENEMY_MOTION_INFO aMotionInfo[ENEMY_ACTION_MAX];		//���[�V�����̏��[���[�V�����̑���]
	int nNumMotion;											//���[�V�����̑���
	ENEMY_MOTION_TYPE MotionType;							//���[�V�����̎��
	bool bLoopMotion;										//���[�v���邩�ǂ���
	int nNumkey;											//�L�[�̑���
	int nkey;												//���݂̃L�[No.
	int nCounterMotion;										//���[�V�����̃J�E���^�[
	int g_nNextKey;											//���[�V�������̎��̃L�[
	bool g_bMotion;											//���[�V�������Ă��邩�ǂ���

	D3DXVECTOR3 Tgpos;							//�ڕW�ʒu
	D3DXVECTOR3 rotDest;						//����
	float fDistanceN;
	float fDistanceS;
	float fDistanceW;
	float fDistanceE;
	float fDistanceFront;
	float fDistanceLeft;
	float fDistanceRight;

	int nCoolTurn;
	int nTarget;
	bool bHit;
	int nTargetOld;
	int nCntStop;
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
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);
void TeleportationEnemy(D3DXVECTOR3 *pPos);
void CollisionEnemyShadow(D3DXVECTOR3 *pPos);
ENEMY * GetEnemy(void);
void FalseEnemy(void);
float DetectWall(D3DXVECTOR3 pos, float fmoveRot, int nLife);
bool DetectPlayer(D3DXVECTOR3 pos, float fmoveRot, int nEnemy);

void UpdateEnemyMotion(int nCnt);
void SetEnemyMotion(ENEMY_MOTION_TYPE nType, int nCnt);
void LoadEnemyMotion(int nPlayerBG);

#endif
