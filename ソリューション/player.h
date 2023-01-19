#ifndef _PLAYER_H_
#define _PLAYER_H_

//�}�N����`
#define MAX_MODEL	(32)			//���f���̍ő吔
#define NUM_PLAYER	(3)			//�v���C���[�̍ő�l��

//�v���C���[�̏�ԊǗ�
typedef enum
{
	PLAYER_NORMAL = 0,
	PLAYER_WAIT,
	PLAYER_DAMAGE,
	PLAYER_HIT,
	PLAYER_STATE_MAX,
}PLAYER_STATE;

//�v���C���[�̏�ԊǗ�
typedef enum
{
	PLAYER_MOVESTATE_STEALTH = 0,		//�X�e���X
	PLAYER_MOVESTATE_NORMAL,			//�ʏ�
	PLAYER_MOVESTATE_DASH,				//�_�b�V��
	PLAYER_MOVESTATE_FATIGE,			//��J
	PLAYER_MOVESTATE_MAX,
}PLAYER_MOVESTATE;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//���݂̈ʒu
	D3DXVECTOR3 posOld;							//�ߋ��̈ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 NormarizeMove;					//�ړ���
	D3DXVECTOR3 rot;							//����
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	PLAYER_STATE State;							//�v���C���[�̏��
	PLAYER_MOVESTATE MoveState;					//�v���C���[�̈ړ����
	int nLife;									//�v���C���[�̗̑�
	int nWaitCounter;							//�ҋ@��Ԃ̒���
	int nDamageCounter;							//�_���[�W��Ԃ̒���
	int nHitCounter;							//�q�b�g��Ԃ̒���
	int nNumModel;								//���f��(�p�[�c)�̑���
	bool bUse;									//�v���C���[���g�p�ł��邩�ǂ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void PlayerMoveInput(int nCnt);
void PlayerRotUpdate(int nCnt);
void PlayerHit(int nCnt,int nDamage);
void CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY);
void DrawPlayer(void);
Player * GetPlayer(void);
#endif