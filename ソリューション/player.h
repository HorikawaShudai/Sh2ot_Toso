#ifndef _PLAYER_H_
#define _PLAYER_H_

//�}�N����`
#define MAX_MODEL (32)	//���f���̍ő吔

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//���݂̈ʒu
	D3DXVECTOR3 posOld;							//�ߋ��̈ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 vecMove;						//�ړ��x�N�g��
	D3DXVECTOR3 rot;							//����
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	int nIndexModelParent;						//�e���f���̃C���f�b�N�X
}Model;

//�v���C���[�̍\����
typedef enum
{
	PLAYER_NORMAL = 0,
	PLAYER_WAIT,
	PLAYER_DAMAGE,
	PLAYER_HIT,
	PLAYER_STATE_MAX,

}PLAYER_STATE;

//�v���C���[�̍\����
typedef enum
{
	PLAYER_ACTION_WAIT = 0,
	PLAYER_ACTION_MOVE,
	PLAYER_ACTION_JUMP,
	PLAYER_ACTION_MAX,

}PLAYER_ACTION;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//���݂̈ʒu
	D3DXVECTOR3 posOld;							//�ߋ��̈ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 NormarizeMove;					//�ړ���
	D3DXVECTOR3 rot;							//����
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin;							//���f���̍ŏ�
	D3DXVECTOR3 vtxMax;							//���f���̍ő�
	PLAYER_STATE State;							//�v���C���[�̏��
	PLAYER_ACTION Action;						//�v���C���[�̍s��
	int nLife;									//�v���C���[�̗̑�
	int nNextLife;								//�v���C���[�������p���̗�
	int nWaitCounter;							//�ҋ@��Ԃ̒���
	int nDamageCounter;							//�_���[�W��Ԃ̒���
	int nHitCounter;							//�q�b�g��Ԃ̒���
	Model aModel[MAX_MODEL];					//���f��(�p�[�c)
	int nNumModel;								//���f��(�p�[�c)�̑���
	bool bJump;									//�W�����v���g�p�ł��邩�ǂ���
	bool bUse;									//�v���C���[���g�p�ł��邩�ǂ���
	D3DXMATERIAL pMatH;							//�q�b�g��Ԃ̃}�e���A��
	D3DXMATERIAL pMatD;							//�_���[�W��Ԃ̃}�e���A��
	D3DXMATERIAL pMatW;							//�ҋ@��Ԃ̃}�e���A��
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void PlayerMotion(void);
void PlayerMoveInput(void);
void PlayerRotUpdate(void);
void PlayerHit(int nDamage);
void CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY);
void DrawPlayer(void);
void SetNextLife(void);
Player * GetPlayer(void);
#endif