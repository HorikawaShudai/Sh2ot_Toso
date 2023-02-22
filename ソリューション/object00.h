//========================================================================================
//
// �I�u�W�F�N�g�̏���[Object00.h]
// Author: ��{�@�ėB
// Author: �O�엳�V��
//
//========================================================================================
#ifndef _OBJECT00_H_
#define _OBJECT00_H_

#define MAX_OBJECT00 (2048)		//�I�u�W�F�N�g�̍ő吔

//���f���̍\����
typedef enum
{
	OBJECT00_NTYPE00 = 0,		//�|���S�����̑�����
	OBJECT00_NTYPE01,			//�K�i
	OBJECT00_NTYPE02,			//�K�i��
	OBJECT00_NTYPE03,			//��t
	OBJECT00_NTYPE04,			//��
	OBJECT00_NTYPE05,			//�����I
	OBJECT00_NTYPE06,			//���ꂫ
	OBJECT00_NTYPE07,			//���{�e�[�u��
	OBJECT00_NTYPE08,			//���E���W
	OBJECT00_NTYPE09,			//�J���`���[�^���N			������
	OBJECT00_NTYPE10,			//�J���`���[�^���N(��)		������
	OBJECT00_NTYPE11,			//�}�V��					������
	OBJECT00_NTYPE12,			//�ςݏd�Ȃ����֎q
	OBJECT00_NTYPE13,			//�ςݏd�Ȃ�����
	OBJECT00_NTYPE14,			//���ꂫ������Ă�}�V��
	OBJECT00_NTYPE15,			//�F�X�Ȃ��̂��d�Ȃ��Ă���I�u�W�F�N�g
	OBJECT00_NTYPE16,			//����Ă�A�[�`�K�i
	OBJECT00_NTYPE17,			//���j�^�[
	OBJECT00_NTYPE18,			//�B
	OBJECT00_NTYPE19,			//�|�b�g					������
	OBJECT00_NTYPE20,			//�S��						���e
	OBJECT00_NTYPE21,			//���ɗ����Ă邪�ꂫ
	OBJECT00_NTYPE22,			//�J�[�e��
	OBJECT00_NTYPE23,			//�򂪓����Ă�I
	OBJECT00_NTYPE24,			//�����I(��)
	OBJECT00_NTYPE25,			//�����I(��)
	OBJECT00_NTYPE26,			//���̒u���Ă���I
	OBJECT00_NTYPE27,			//�P�[�W
	OBJECT00_NTYPE28,			//�P�[�W
	OBJECT00_NTYPE29,			//�t�F���X
	OBJECT00_NTYPE30,			//�\�t�@
	OBJECT00_NTYPE31,			//��
	OBJECT00_NTYPE32,			//�p�\�R�����ڂ��Ă����
	OBJECT00_NTYPE33,			//���̈֎q
	OBJECT00_NTYPE34,			//���b�J�[
	OBJECT00_NTYPE35,			//�z���C�g�{�[�h
	OBJECT00_NTYPE36,			//�Ď��J����
	OBJECT00_NTYPE37,			//�u����
	OBJECT00_NTYPE38,			//�����O�f�X�N
	OBJECT00_NTYPE39,			//�v���W�F�N�^�[�̂����ق�
	OBJECT00_NTYPE40,			//�ϗt�A��
	OBJECT00_NTYPE41,			//�S�~��
	OBJECT00_NTYPE42,			//�p�[�e�[�V����
	OBJECT00_NTYPE43,			//�{�I
	OBJECT00_NTYPE44,			//�R�[�g�|��
	OBJECT00_NTYPE45,			//�����p�̑�
	OBJECT00_NTYPE46,			//�R�s�[�@
	OBJECT00_NTYPE47,			//�u���[�V�[�g�̂���������
	OBJECT00_NTYPE48,			//��߂̒I
	OBJECT00_NTYPE49,			//���ꂫ
	OBJECT00_NTYPE50,			//�~�}�x�b�h
	OBJECT00_NTYPE51,			//���΂����
	OBJECT00_NTYPE52,			//���Ȏ��ɂ���f�X�N
	OBJECT00_NTYPE53,			//���ꂽ������
	OBJECT00_NTYPE54,			//��(���C���z�[��)
	OBJECT00_NTYPE55,			//��(�������K)
	OBJECT00_NTYPE56,			//��(�L��)
	OBJECT00_NTYPE57,			//���{�^���N
	OBJECT00_NTYPE58,			//�̂��l�p�̃e�[�u��
	OBJECT00_NTYPE59,			//�̂��l�p�̈֎q
	OBJECT00_NTYPE60,			//���ڎ��̊�
	OBJECT00_NTYPE_MAX,

}OBJECT00_NTYPE;

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
}Object00;

//�v���g�^�C�v�錾
void InitObject00(void);
void UninitObject00(void);
void UpdateObject00(void);
void DrawObject00(void);
void UpdateEditObject00(void);
void DrawEditObject00(void);
void SetObject00(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void FalseObject00(void);
void CollisionRotObject00(int nCnt);
D3DXVECTOR3 CollisionOuterProductObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool EditCollisionObject00(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
bool CollisionObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionObject00Shadow(D3DXVECTOR3 *pPos);
Object00 * GetObject00(void);
#endif