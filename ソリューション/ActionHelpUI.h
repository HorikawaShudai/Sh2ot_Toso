#ifndef _ACTIONHELPUI_H_
#define _ACTIONHELPUI_H_

#define MAX_ACTIONHELPUI (128)		//�e�̍ő吔

//���f���̍\����
typedef enum
{
	ACTIONHELPUI_KEY = 0,
	ACTIONHELPUI_DOOR,
	ACTIONHELPUI_MAX,

}ACTIONHELPUI_TYPE;

//�r���{�[�h�\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	ACTIONHELPUI_TYPE nType;					//���
	bool bUse;									//�g�p���Ă��邩�ǂ���
}ActionHelpUI;

//�v���g�^�C�v�錾
void InitActionHelpUI(void);
void UninitActionHelpUI(void);
void UpdateActionHelpUI(void);
void DrawActionHelpUI(int nCntPlayer, bool GetKey);
int SetActionHelpUI(D3DXVECTOR3 pos, ACTIONHELPUI_TYPE Type);
void FalseActionHelpUI(int Idx);
ActionHelpUI * GetActionHelpUI(void);
#endif