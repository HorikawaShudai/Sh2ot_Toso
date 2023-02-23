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
