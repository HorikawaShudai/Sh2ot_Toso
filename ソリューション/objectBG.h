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
	OBJECTBG_NTYPE06,
	OBJECTBG_NTYPE07,
	OBJECTBG_NTYPE08,
	OBJECTBG_NTYPE09,
	OBJECTBG_NTYPE10,
	OBJECTBG_NTYPE11,
	OBJECTBG_NTYPE12,
	OBJECTBG_NTYPE13,
	OBJECTBG_NTYPE14,
	OBJECTBG_NTYPE15,
	OBJECTBG_NTYPE16,
	OBJECTBG_NTYPE17,
	OBJECTBG_NTYPE18,
	OBJECTBG_NTYPE19,
	OBJECTBG_NTYPE20,
	OBJECTBG_NTYPE21,
	OBJECTBG_NTYPE22,
	OBJECTBG_NTYPE23,
	OBJECTBG_NTYPE24,
	OBJECTBG_NTYPE25,
	OBJECTBG_NTYPE26,
	OBJECTBG_NTYPE27,
	OBJECTBG_NTYPE28,
	OBJECTBG_NTYPE29,
	OBJECTBG_NTYPE30,
	OBJECTBG_NTYPE31,
	OBJECTBG_NTYPE32,
	OBJECTBG_NTYPE33,
	OBJECTBG_NTYPE34,
	OBJECTBG_NTYPE35,
	OBJECTBG_NTYPE36,
	OBJECTBG_NTYPE37,
	OBJECTBG_NTYPE38,
	OBJECTBG_NTYPE39,
	OBJECTBG_NTYPE40,
	OBJECTBG_NTYPE41,
	OBJECTBG_NTYPE42,
	OBJECTBG_NTYPE43,
	OBJECTBG_NTYPE44,
	OBJECTBG_NTYPE45,
	OBJECTBG_NTYPE46,
	OBJECTBG_NTYPE47,
	OBJECTBG_NTYPE48,
	OBJECTBG_NTYPE49,
	OBJECTBG_NTYPE50,
	OBJECTBG_NTYPE51,
	OBJECTBG_NTYPE52,
	OBJECTBG_NTYPE53,
	OBJECTBG_NTYPE54,
	OBJECTBG_NTYPE55,
	OBJECTBG_NTYPE56,
	OBJECTBG_NTYPE57,
	OBJECTBG_NTYPE58,
	OBJECTBG_NTYPE59,
	OBJECTBG_NTYPE60,
	OBJECTBG_NTYPE61,
	OBJECTBG_NTYPE62,
	OBJECTBG_NTYPE63,
	OBJECTBG_NTYPE64,
	OBJECTBG_NTYPE65,
	OBJECTBG_NTYPE67,
	OBJECTBG_NTYPE68,
	OBJECTBG_NTYPE69,
	OBJECTBG_NTYPE70,
	OBJECTBG_NTYPE71,
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
