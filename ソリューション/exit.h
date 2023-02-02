//========================================================================================
//
// �o���̏���[exit.h]
// Author: ��{�@�ėB
//
//========================================================================================
#ifndef _EXIT_H_
#define _EXIT_H_

#define MAX_EXIT (32)		//���̍ő吔

typedef enum
{
	EXIT_TYPE_BIGFRAME = 0,			//�傫�����̘g
	EXIT_TYPE_BIGDOOR_R,			//�傫���� �E��
	EXIT_TYPE_BIGDOOR_L,			//�傫���� ����
	EXIT_TYPE_MAX,					//�񋓂̍ő�
}EXIT_TYPE;

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
	bool bExitOK;								//�E�o�\�ł��邩�ǂ���
	int nIdxModelParent; //�e�q�ݒ�
}EXIT;

//�v���g�^�C�v�錾
void InitExit(void);
void UninitExit(void);
void UpdateExit(void);
void DrawExit(void);
void SetExit(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType);
bool CollisionExit(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer);
#endif