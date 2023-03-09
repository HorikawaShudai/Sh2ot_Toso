//========================================================================================
//
// �w�i�p�I�u�W�F�N�g�̏���[ObjectBG.h]
// Author: ��{�@�ėB
//
//========================================================================================
#ifndef _OBJECTBG_H_
#define _OBJECTBG_H_

#define MAX_OBJECTBG (1024)		//�I�u�W�F�N�g�̍ő吔

//���f���̍\����
typedef enum
{
	OBJECTBG_NTYPE00 = 0,
	OBJECTBG_NTYPE01,
	OBJECTBG_NTYPE02,
	OBJECTBG_NTYPE03,
	OBJECTBG_NTYPE04,
	OBJECTBG_NTYPE05,
	OBJECTBG_NTYPE06,			//���C��
	OBJECTBG_NTYPE07,			//�R���N�{�[�h
	OBJECTBG_NTYPE08,			//�Ǌ|���A�[�g
	OBJECTBG_NTYPE09,			//�����P��
	OBJECTBG_NTYPE10,			//���C�g�̃X�C�b�`
	OBJECTBG_NTYPE11,			//�����P��
	OBJECTBG_NTYPE12,			//�ʋC��
	OBJECTBG_NTYPE13,			//��
	OBJECTBG_NTYPE14,			//�v���W�F�N�^�[�̂������ق�
	OBJECTBG_NTYPE15,			//���v
	OBJECTBG_NTYPE16,			//�K�i_�E_��
	OBJECTBG_NTYPE17,			//�K�i_��_��
	OBJECTBG_NTYPE18,			//�V��(��)
	OBJECTBG_NTYPE19,			//�V��(�R���N��)
	OBJECTBG_NTYPE20,			//�V��(�J�G��R���N��)
	OBJECTBG_NTYPE21,			//�V��(�^�C��)
	OBJECTBG_NTYPE22,			//�V��(���͗l����)
	OBJECTBG_NTYPE23,			//��(�S)
	OBJECTBG_NTYPE24,			//��(�R���N��)
	OBJECTBG_NTYPE25,			//��(�^�C��)
	OBJECTBG_NTYPE26,			//��(�I�t�B�X)
	OBJECTBG_NTYPE27,			//��(��)
	OBJECTBG_NTYPE28,			//��(���͗l����)
	OBJECTBG_NTYPE29,			//�E��
	OBJECTBG_NTYPE30,			//���������̏�
	OBJECTBG_NTYPE31,			//�}�b�v0
	OBJECTBG_NTYPE32,			//�}�b�v1
	OBJECTBG_NTYPE33,			//�}�b�v2
	OBJECTBG_NTYPE34,			//�}�b�v3
	OBJECTBG_NTYPE35,			//�o���Ŕ�
	OBJECTBG_NTYPE36,			//���Ί�
	OBJECTBG_NTYPE37,			//�{��
	OBJECTBG_NTYPE38,			//��
	OBJECTBG_NTYPE39,			//�h�A
	OBJECTBG_NTYPE40,			//�h�A
	OBJECTBG_NTYPE41,			//�h�A
	OBJECTBG_NTYPE42,			//�h�A
	OBJECTBG_NTYPE_MAX,

}OBJECTBG_NTYPE;

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
}ObjectBG;

//�v���g�^�C�v�錾
void InitObjectBG(void);
void UninitObjectBG(void);
void UpdateObjectBG(void);
void DrawObjectBG(void);
void UpdateEditObjectBG(void);
void DrawEditObjectBG(void);
void SetObjectBG(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void FalseObjectBG(void);
void CollisionRotObjectBG(int nCnt);
bool EditCollisionObjectBG(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionObjectBGShadow(D3DXVECTOR3 *pPos);
ObjectBG * GetObjectBG(void);
#endif
