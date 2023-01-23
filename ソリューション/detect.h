//===============================
//
//�T�m����(detect.h)
//
//===============================
#ifndef _Detect_H_   //���̃}�N����`������Ă��Ȃ�������
#define _Detect_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`

//�񋓌^��`
typedef enum
{
	DETECTTYPE_WALL = 0,
	DETECTTYPE_PLAYER,
	DETECTTYPE_MAX
}DETECTTYPE;

//�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	float fmoveRot;
	int nLife;
	float fDistance;
	bool bUse;
	DETECTTYPE type;
}DETECT;

//�v���g�^�C�v�錾
void InitDetect(void);
void UninitDetect(void);
void UpdateDetect(void);
void SetDetect(D3DXVECTOR3 pos,int nEnemy, float fmoveRot, int nLife ,DETECTTYPE type);

#endif
