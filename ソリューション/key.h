//========================================================================================
//
// ���̏���[Key.h]
// Author: ��{�@�ėB
//
//========================================================================================
#ifndef _KEY_H_
#define _KEY_H_

#define MAX_KEY (8)		//���̍ő吔

typedef enum
{
	KEY_TYPE_ITEM = 0,
	KEY_TYPE_MAX,
}KEY_TYPE;

const D3DXVECTOR3 KeyPos[] = //���̍��W
{
	D3DXVECTOR3(-1918.0f,10.0f,1720.0f),
	D3DXVECTOR3(-2055.0f,2.0f,540.0f),
	D3DXVECTOR3(-1585.0f,14.75f,820.0f),
	D3DXVECTOR3(-1570.0f,2.0f,1434.0f),
	D3DXVECTOR3(-983.0f,2.0f,1733.0f),
	D3DXVECTOR3(-800.0f,24.0f,1961.0f),
	D3DXVECTOR3(-915.0f,27.0f,1250.0f),
	D3DXVECTOR3(-680.0f,2.0f,2067.0f),
	D3DXVECTOR3(387.0f,30.0f,-20.0f),
	D3DXVECTOR3(-340.0f,17.0f,160.0f),
	D3DXVECTOR3(165.0f,27.5f,247.0f),
	D3DXVECTOR3(-92.0f,29.0f,-317.0f),
};

//���̍\����
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
	int nType;									//���f���̎��
	bool bUse;									//���f�����g�p����Ă��邩�ǂ���
	bool bHelpUI;								//�w���vUI���g���Ă��邩�ǂ���
	int IndexUI;								//�w���vUI�̎g�p�ԍ�
	int nIdxModelParent; //�e�q�ݒ�
	int nCntMove;								//�㉺�̓����̃J�E���g
}KEY;

//�v���g�^�C�v�錾
void InitKey(void);
void UninitKey(void);
void UpdateKey(void);
void DrawKey(void);
void SetKey(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
bool CollisionKey(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer);
bool CollisionKeyHelpUI(D3DXVECTOR3 *pPos, float Size);
void PatternSetKey(int nNumPlayer);
#endif