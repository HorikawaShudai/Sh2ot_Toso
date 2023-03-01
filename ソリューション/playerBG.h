#ifndef _PLAYERBG_H_
#define _PLAYERBG_H_

//�}�N����`
#define MAX_PLAYER_MODEL (32)	//���f���̍ő吔
#define MAX_PLAYER_PARTS (32)	//�p�[�c�̑���
#define MAX_PLAYER_KEY (16)	//�L�[�̑���

//�v���C���[�̃��[�V����
typedef enum
{
	PLAYERBG_ACTION_WAIT = 0,
	PLAYERBG_ACTION_MOVE,
	PLAYERBG_ACTION_JUMP,
	PLAYERBG_ACTION_WAIT2,
	PLAYERBG_ACTION_MAX,

}PLAYER_MOTION_TYPE;

//�L�[�̍\����
typedef struct
{
	float fPosX;		//�ʒuX
	float fPosY;		//�ʒuY
	float fPosZ;		//�ʒuZ
	float fRotX;		//����X
	float fRotY;		//����Y
	float fRotZ;		//����Z
}PLAYER_KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;				//�Đ��t���[��
	PLAYER_KEY aKey[MAX_PLAYER_PARTS];		//�e���f���̃L�[�v�f[�p�[�c�̑���]
}PLAYER_KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;						//���[�v���邩�ǂ���
	int NumKey;						//�e���f���̃L�[�v�f
	PLAYER_KEY_INFO aKeyInfo[MAX_PLAYER_KEY];			//�L�[���[�L�[�̑���]
}PLAYER_MOTION_INFO;

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
	LPDIRECT3DTEXTURE9 g_pTexturePlayerBG[100];	//�e�N�X�`���̃|�C���^
	DWORD g_dwNumMatPlayerBG;				//�}�e���A���̐�
}PlayerModel;

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

	PlayerModel aModel[MAX_PLAYER_MODEL];					//���f��(�p�[�c)
	int nNumModel;											//���f��(�p�[�c)�̑���
	PLAYER_MOTION_INFO aMotionInfo[PLAYERBG_ACTION_MAX];	//���[�V�����̏��[���[�V�����̑���]
	int nNumMotion;											//���[�V�����̑���
	PLAYER_MOTION_TYPE MotionType;							//���[�V�����̎��
	bool bLoopMotion;										//���[�v���邩�ǂ���
	int nNumkey;											//�L�[�̑���
	int nkey;												//���݂̃L�[No.
	int nCounterMotion;										//���[�V�����̃J�E���^�[
	int g_nNextKey;											//���[�V�������̎��̃L�[
	bool g_bMotion;											//���[�V�������Ă��邩�ǂ���

	bool bUse;									//�v���C���[��`�悷�邩�ǂ���
}PlayerBG;

//�v���g�^�C�v�錾
void InitPlayerBG(void);
void UninitPlayerBG(void);
void UpdatePlayerBG(void);
void DrawPlayerBG(void);
void UpdatePlayerMotion(int nCnt);
void SetPlayerMotion(PLAYER_MOTION_TYPE nType, int nCnt);
void LoadPlayerMotion(int nPlayerBG);
PlayerBG * GetPlayerBG(void);
#endif