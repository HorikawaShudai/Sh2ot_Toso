//========================================================================================
//
// �w�i�p�I�u�W�F�N�g�̏���[ObjectLight.h]
// Author: ��{�@�ėB
//
//========================================================================================
#ifndef _OBJECTLIGHT_H_
#define _OBJECTLIGHT_H_

#define MAX_OBJECTLIGHT (1024)		//�I�u�W�F�N�g�̍ő吔

//���f���̍\����
typedef enum
{
	OBJECTLIGHT_NTYPE00 = 0,
	OBJECTLIGHT_NTYPE01,
	OBJECTLIGHT_NTYPE02,
	OBJECTLIGHT_NTYPE03,
	OBJECTLIGHT_NTYPE04,
	OBJECTLIGHT_NTYPE05,
	OBJECTLIGHT_NTYPE06,

	OBJECTLIGHT_NTYPE_MAX,

}OBJECTLIGHT_NTYPE;

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
	int LightIdx;								//���C�g�̎g�p�ԍ�
}ObjectLight;

//�v���g�^�C�v�錾
void InitObjectLight(void);
void UninitObjectLight(void);
void UpdateObjectLight(void);
void DrawObjectLight(void);
void UpdateEditObjectLight(void);
void DrawEditObjectLight(void);
void SetObjectLight(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
void FalseObjectLight(void);
void CollisionRotObjectLight(int nCnt);
bool EditCollisionObjectLight(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionObjectLightShadow(D3DXVECTOR3 *pPos);
ObjectLight * GetObjectLight(void);
#endif
