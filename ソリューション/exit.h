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
	EXIT_TYPE_BIGFRAME = 0,			//�傫�����̘g(���E)
	EXIT_TYPE_BIGFRAMEUP,		//�傫�����̘g(��)
	EXIT_TYPE_BIGDOOR_R,			//�傫���� �E��
	EXIT_TYPE_BIGDOOR_L,			//�傫���� ����
	EXIT_TYPE_MAX,					//�񋓂̍ő�
}EXIT_TYPE;

//�o���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 posOld;							//�ʒu
	D3DXVECTOR3 move;							//�ʒu
	D3DXVECTOR3 rot;							//����
	D3DXVECTOR3 rotSave;						//�����̕ۑ�
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 pTexture[30];			//�e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3 vtxMin;							//���f���̍ŏ�
	D3DXVECTOR3 vtxMax;							//���f���̍ő�
	int nType;									//���f���̎��
	int nExitOKcnt;								//�E�o�\�܂ł̃J�E���g
	bool bUse;									//���f�����g�p����Ă��邩�ǂ���
	bool bExitOK;								//�E�o�\�ł��邩�ǂ���
	int nIdxModelParent;						//�e�q�ݒ�
} ExitParts;


typedef struct
{
	ExitParts parts[MAX_EXIT];
	D3DXVECTOR3 PseudoCenter;
	bool bUse;

}EXIT;

//�v���g�^�C�v�錾
void InitExit(void);
void UninitExit(void);
void UpdateExit(void);
void DrawExit(void);
void SetExit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nNumExit);
bool CollisionExit(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer);
bool CollisionExi(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);

void LoadExit(void);

#endif