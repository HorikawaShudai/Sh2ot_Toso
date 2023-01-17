#ifndef _OBJECT00_H_
#define _OBJECT00_H_

#define MAX_OBJECT00 (512)		//�I�u�W�F�N�g�̍ő吔

//���f���̍\����
typedef enum
{
	OBJECT00_NTYPE00 = 0,
	OBJECT00_NTYPE01,
	OBJECT00_NTYPE02,
	OBJECT00_NTYPE03,
	OBJECT00_NTYPE04,
	OBJECT00_NTYPE05,
	OBJECT00_NTYPE06,
	OBJECT00_NTYPE07,
	OBJECT00_NTYPE08,
	OBJECT00_NTYPE09,
	OBJECT00_NTYPE010,
	OBJECT00_NTYPE011,
	OBJECT00_NTYPE012,
	OBJECT00_NTYPE013,
	OBJECT00_NTYPE014,
	OBJECT00_NTYPE015,
	OBJECT00_NTYPE016,
	OBJECT00_NTYPE017,
	OBJECT00_NTYPE018,
	OBJECT00_NTYPE019,
	OBJECT00_NTYPE020,
	OBJECT00_NTYPE021,
	OBJECT00_NTYPE022,
	OBJECT00_NTYPE023,
	OBJECT00_NTYPE024,
	OBJECT00_NTYPE025,
	OBJECT00_NTYPE026,
	OBJECT00_NTYPE027,
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
void CollisionRotObject00(int nCnt);
bool CollisionObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size);
void CollisionObject00Shadow(D3DXVECTOR3 *pPos);
Object00 * GetObject00(void);
#endif