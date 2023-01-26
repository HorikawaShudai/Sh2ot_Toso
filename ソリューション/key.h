#ifndef _KEY_H_
#define _KEY_H_

#define MAX_KEY (32)		//���̍ő吔

typedef enum
{
	KEY_TYPE_ITEM = 0,
	KEY_TYPE_MAX,
}KEY_TYPE;

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
	int nIdxModelParent; //�e�q�ݒ�
}KEY;

//�v���g�^�C�v�錾
void InitKey(void);
void UninitKey(void);
void UpdateKey(void);
void DrawKey(void);
void SetKey(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
bool CollisionKey(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer);
#endif