//========================================================================================
//
// �J��������[camera.h]
// Author: 
//
//========================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�J������Ԃ̗񋓌^�̒�`
typedef enum
{
	CAMERASTATE_NONE = 0,
	CAMERASTATE_UP,
	CAMERASTATE_DOWN,
	CAMERASTATE_MAX
} CAMERASTATE;

//�J�����̍\���̂��`
typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 vecU;			//������x�N�g��
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rot2;
	D3DXVECTOR3 rot2Old;
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DVIEWPORT9 viewport;		//�r���[�|�[�g
	CAMERASTATE State;

	float fposYmove;
	bool bUse;					//�g���Ă��邩
}Camera;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdx);

D3DXVECTOR3 Getrot(int nPlayer);
Camera *GetCamera(void);
int GetCurrentCamera(void);
void MoveTitleCamera(int nCnt);

#endif