//========================================================================================
//
// �v���C���[�̏���[player.h]
// Author: ���}���@�V
// Author: ��{�@�ėB
// Author: �O�엳�V��
//
//========================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�}�N����`
#define NUM_PLAYER	(4)			//�v���C���[�̍ő�l��

//�v���C���[�̏�ԊǗ�
typedef enum
{
	PLAYER_NORMAL = 0,
	PLAYER_WAIT,
	PLAYER_HIT,
	PLAYER_EXSIT,
	PLAYER_DAMAGE,
	PLAYER_SMITE,
	PLAYER_DEATH,
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

//�v���C���[�̍\����
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
	int nNumModel;								//���f��(�p�[�c)�̑���
	int VibrtionTrueCount;						//�o�C�u���[�V�������̃J�E���g
	int VibrtionFalseCount;						//�o�C�u���[�V���������Ă��Ȃ��Ԃ̃J�E���g
	int VibrtionTime;							//�o�C�u���[�V�����̒���
	int LightIdx00;								//���C�g�̎g�p�ԍ�00
	int nWaitCounter;							//�v���C���[�̑ҋ@��Ԃ̒���
	int nDamageCounter;							//�v���C���[�̃_���[�W��Ԃ̒���
	int nDeathCounter;							//�v���C���[�̎��S��Ԃ̒���
	int nHitCounter;							//�v���C���[�̃q�b�g��Ԃ̒���

	bool bUse;									//�v���C���[���g�p�ł��邩�ǂ���
	bool bGetKey;								//�v���C���[�����������Ă��邩�ǂ���
	bool bAppear;								//�G�����F�ł��邩�ǂ���
	bool bVibrtion;								//�o�C�u���[�V���������Ă��邩�ǂ���
	bool bExit;									//�E�o���Ă��邩�ǂ���
	bool bCheck;								//�`�F�b�N�����Ă��邩�ǂ���
	int nStelthCnt;								//�`���[�g���A���p�X�e���X��Ԃ𐔂��鏈��
	int nVibCnt;								//�`���[�g���A���p�o�C�u���[�V������Ԃ𐔂��鏈��
	bool KeyHelpUI;								//���̃w���vUI�̕\��������Ă��邩�ǂ���
	bool ExitHelpUI;							//�o���̃w���vUI�̕\��������Ă��邩�ǂ���
	int  nPlayerSECount;						//�v���C���[��SE��炷�Ԋu
	bool bChase;								//�G�ɒǂ��������Ă��邩�ǂ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void PlayerMoveInput(int nCnt);
void PlayerRotUpdate(int nCnt);
void PlayerState(int nCnt);
void PlayerDistance(int nCnt);
void PlayerVibrtionUpdate(int nCnt);
void PlayerSetVibrtion(int nCnt, int nTrueCounter, int nFalseCounter, int nLeftPower, int RightPoewr);
void PlayerHit(int nCnt, int nDamage);
int CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY);
D3DXVECTOR3 CollisionOuterProductPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn, float MinY, float MaxY);
void PlayerAllDown(void);
Player * GetPlayer(void);
#endif