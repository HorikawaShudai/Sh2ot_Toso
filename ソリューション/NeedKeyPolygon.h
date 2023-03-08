#ifndef _NEEDKEYPOLYGON_H_
#define _NEEDKEYPOLYGON_H_

#define MAX_NEEDKEYPOLYGON (3)		//�e�̍ő吔

//���f���̍\����
typedef enum
{
	NEEDKEYPOLYGON_CENTER = 0,
	NEEDKEYPOLYGON_LEFT,
	NEEDKEYPOLYGON_RIGHT,
	NEEDKEYPOLYGON_MAX,

}NEEDKEYPOLYGON_TYPE;

//�r���{�[�h�\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	float fSize;								//�T�C�Y
	bool bUse;									//�g�p���Ă��邩�ǂ���
}NeedKeyPolygon;

//�v���g�^�C�v�錾
void InitNeedKeyPolygon(void);
void UninitNeedKeyPolygon(void);
void UpdateNeedKeyPolygon(void);
void DrawNeedKeyPolygon(int nCntPlayer);
void SetNeedKeyPolygon(D3DXVECTOR3 pos);
void FalseNeedKeyPolygon(void);
NeedKeyPolygon * GetNeedKeyPolygon(void);
#endif