//========================================================================================
//
// �I�u�W�F�N�g�̏���[ObjectWall.h]
// Author: ��{�@�ėB
// Author: �O�엳�V��
//
//========================================================================================
#ifndef _OBJECTWALL_H_
#define _OBJECTWALL_H_

#define MAX_OBJECTWALL (2048)		//�I�u�W�F�N�g�̍ő吔

//���f���̍\����
typedef enum
{
	OBJECTWALL_NTYPE00 = 0,		//�|���S�����̑�����
	OBJECTWALL_NTYPE01,			//��(���C���z�[��)
	OBJECTWALL_NTYPE02,			//��(�������K)
	OBJECTWALL_NTYPE03,			//��(�L��)
	OBJECTWALL_NTYPE04,			//��(���^�C��)
	OBJECTWALL_NTYPE_MAX,

}OBJECTWALL_NTYPE;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 posOld;							//�ʒu
	D3DXVECTOR3 move;							//�ʒu
	D3DXVECTOR3 rot;							//����
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 pTexture[30];			//�e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3 vtxMin;							//���f���̍ŏ�
	D3DXVECTOR3 vtxMax;							//���f���̍ő�
	int nDamageCounter;							//�_���[�W��Ԃ̒���
	int nType;									//���f���̎��
	bool bUse;									//���f�����g�p����Ă��邩�ǂ���
	D3DXMATERIAL pMatE;							//�G�f�B�b�g��Ԃ̃}�e���A��
	int nIdxModelParent; //�e�q�ݒ�
}ObjectWall;

//�v���g�^�C�v�錾
void InitObjectWall(void);
void UninitObjectWall(void);
void UpdateObjectWall(void);
void DrawObjectWall(void);
void UpdateEditObjectWall(void);
void DrawEditObjectWall(void);
void SetObjectWall(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void FalseObjectWall(void);
void CollisionRotObjectWall(int nCnt);
D3DXVECTOR3 CollisionOuterProductObjectWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool EditCollisionObjectWall(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
bool CollisionObjectWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionObjectWallShadow(D3DXVECTOR3 *pPos);
ObjectWall * GetObjectWall(void);
#endif