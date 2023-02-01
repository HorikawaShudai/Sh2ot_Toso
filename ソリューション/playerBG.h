#ifndef _PLAYERBG_H_
#define _PLAYERBG_H_

//�}�N����`
#define MAX_MODEL (32)	//���f���̍ő吔
#define MAX_PARTS (13)	//�p�[�c�̑���
#define MAX_KEY (6)	//�L�[�̑���

//�v���C���[�̃��[�V����
typedef enum
{
	PLAYERBG_ACTION_WAIT = 0,
	PLAYERBG_ACTION_MOVE,
	PLAYERBG_ACTION_JUMP,
	PLAYERBG_ACTION_MAX,

}MOTION_TYPE;

//�L�[�̍\����
typedef struct
{
	float fPosX;		//�ʒuX
	float fPosY;		//�ʒuY
	float fPosZ;		//�ʒuZ
	float fRotX;		//����X
	float fRotY;		//����Y
	float fRotZ;		//����Z
}KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;				//�Đ��t���[��
	KEY aKey[MAX_PARTS];		//�e���f���̃L�[�v�f[�p�[�c�̑���]
}KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;						//���[�v���邩�ǂ���
	int NumKey;						//�e���f���̃L�[�v�f
	KEY_INFO aKeyInfo[MAX_KEY];			//�L�[���[�L�[�̑���]
}MOTION_INFO;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//���݂̈ʒu
	D3DXVECTOR3 posOld;							//�ߋ��̈ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 vecMove;						//�ړ��x�N�g��
	D3DXVECTOR3 rot;							//����
	D3DXVECTOR3 Setpos;							//���[�V�������̈ʒu
	D3DXVECTOR3 Setrot;							//���[�V�������̌���
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	int nIndexModelParent;						//�e���f���̃C���f�b�N�X
}Model;

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
	int nLife;									//�v���C���[�̗̑�
	int nNextLife;								//�v���C���[�������p���̗�

	Model aModel[MAX_MODEL];					//���f��(�p�[�c)
	int nNumModel;								//���f��(�p�[�c)�̑���
	MOTION_INFO aMotionInfo[PLAYERBG_ACTION_MAX];	//���[�V�����̏��[���[�V�����̑���]
	int nNumMotion;								//���[�V�����̑���
	MOTION_TYPE MotionType;						//���[�V�����̎��
	bool bLoopMotion;							//���[�v���邩�ǂ���
	int nNumkey;								//�L�[�̑���
	int nkey;									//���݂̃L�[No.
	int nCounterMotion;							//���[�V�����̃J�E���^�[
	int g_nNextKey;							//���[�V�������̎��̃L�[
	bool g_bMotion;							//���[�V�������Ă��邩�ǂ���

	bool bJump;									//�W�����v���g�p�ł��邩�ǂ���
	bool bUse;									//�v���C���[��`�悷�邩�ǂ���
}PlayerBG;

//�v���g�^�C�v�錾
void InitPlayerBG(void);
void UninitPlayerBG(void);
void UpdatePlayerBG(void);
void DrawPlayerBG(void);
void UpdateMotion(int nCnt);
void SetMotion(MOTION_TYPE nType, int nCnt);
void LoadMotion(int nPlayerBG);
void PlayerBGMoveInput(int nCnt);
void PlayerBGRotUpdate(int nCnt);
PlayerBG * GetPlayerBG(void);
#endif