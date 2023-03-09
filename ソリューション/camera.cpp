//========================================================================================
//
// �J��������[camera.cpp]
// Author: ��{�@�ėB
// Author: ���}���@�V
//
//========================================================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "PlayNumberSelect.h"
#include "debugproc.h"
#include "CheckboxUI.h"
#include "EscapeTutorial.h"
#include "game.h"
#include "enemy.h"
#include "light.h"

//�}�N����`
#define MAX_CAMERA				(5)		//�J�����̍ő吔

#define CAMERA_DISTANCE			(5.0f)		//���_�ƒ����_�̋���
#define MODEL_DISTANCE			(10.0f)		//���f���ƒ����_�̋���
#define CAMERA_SPEED			(2.5f)		//�J�����̈ړ��X�s�[�h
#define CAMERA_VR_SPEED			(0.047f)	//�J�����̎��_�X�s�[�h
#define CAMERA_HOMING			(0.1f)		//�J�����̒Ǐ]�X�s�[�h
#define CAMERA_HOMING_POSY		(35.0f)		//�J�����̒Ǐ]�̈ʒu(Y���W)
#define CAMERA_CORR_V			(0.7f)		//�J�������_�̕␳
#define CAMERA_CORR_R			(0.8f)		//�J���������_�̕␳
#define CAMERA_LENGTH_R			(0.0f)		//�v���C���[�ƃJ���������_�Ƃ̋���

#define POS_MOVE_MAX			(5.0f)		//���_�ʒu�̍ő�l
#define UP_DOWN_SPPED			(0.4f)		//���_�̏㉺�ړ��̑���
#define YUAN_TO_CORRE			(0.2f)		//���_�̌��̈ʒu�ւ̕␳
#define CAM_MOVE_SPEED			(0.0005f)	//�^�C�g���p�J�����̈ړ��X�s�[�h

//�_���[�W������������̃J�����ݒ�
#define DAMAGECAMERA_ROT_Y		(-0.5f)		//�_���[�W���󂯂����̃J���������Ɍ�����p�x
#define DAMAGECAMERA_TIME		(120)		//���������������鎞��
#define DAMAGECAMERA_UPSPEED	(0.009f)	//���Ɍ������p�x����O�Ɍ������鑬��

//���񂾎��̃J�����ݒ�
#define DEATHCAMERA_POS_Y		(8.0f)		//�J���������ɂǂ��܂ŗ����邩
#define DEATHCAMERA_SPEED		(1.0f)		//�J���������ɗ����鑬��
#define DEATHCAMERA_ROTEND		(1.0f)		//�J������Ɍ�������E
#define DEATHCAMERA_TIME		(120)		//�J�����������Ȃ�����
#define DEATHCAMERA_UPSPEED		(0.001f)		//

//�v���g�^�C�v�錾
void TpsCamera(void);						//�ώ@�p�J����
void Camerafollow(int nCurrentCamera);		//�Ǐ]�J����
void CameraMove(int nCurrentCamera);		//�J�����ړ�
void StateYMove(int nCurrentCamera);		//�J�����̏c�̓���

void PlayerCamera(void);					//�R���g���[���[���ꂼ��ɑΉ�
void DownCamera(int nCntCamera);			//�_���[�W���󂯂����̃J����
void DeathCameraEnemy(int nCntCamera);		//���񂾂Ƃ��̃J����(�G�̕����Ɍ�����)
void DeathCamera(int nCntCamera);			//���񂾂Ƃ��̃J����(�J������������)

void Titlecamera(void);
void SelectNumberCamera(void);
void ResultCamera(void);
void RankingCamera(void);

//�O���[�o���ϐ�
Camera g_aCamera[MAX_CAMERA];				//�J�����̏��

int g_nCurrentCamera;						//�I������Ă���J�����̔ԍ�
int g_nSaveCamera;							//�J�����ԍ��ۑ��p
bool g_bTpsCamera;							//�ώ@�p�̃J�������g�����ǂ���
bool bEnter;								//�G���^�[�������ꂽ���ǂ���
bool bCamMove;								//�J���������������ǂ���
int g_Rand_RankingCameraBG;					//�����L���O��ʂ̔w�i�����߂邽�߂̕ϐ�
int g_nCount[NUM_PLAYER];					//�F�X�ȃJ�E���g(�������Ă������ԁA�_���[�W���󂯂����̃J����)
int g_nCount1[NUM_PLAYER];
float g_Acc[NUM_PLAYER];									//�����x

//====================================================================
//�J�����̏���������
//====================================================================
void InitCamera(void)
{
	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	MODE mode = GetMode();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		g_aCamera[nCntCamera].posV = D3DXVECTOR3(0.0f, 35.0f, 50.0f);
		g_aCamera[nCntCamera].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_aCamera[nCntCamera].rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
		g_aCamera[nCntCamera].rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].State = CAMERASTATE_NONE;

		g_aCamera[nCntCamera].fposVmoveY = CAMERA_HOMING_POSY;
		g_aCamera[nCntCamera].fposRmoveY = CAMERA_HOMING_POSY;
		g_aCamera[nCntCamera].bUse = false;
	}

	g_nCurrentCamera = 0;			//�I������Ă���J�����̔ԍ����ŏ��̃J������
	g_bTpsCamera = false;			//�ώ@�p�J�������g���Ă��Ȃ���Ԃ�
	bEnter = false;					//�G���^�[�������Ă��Ȃ���Ԃ�
	bCamMove = false;

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		g_nCount[nCnt] = 0;
		g_nCount1[nCnt] = 0;
		g_Acc[nCnt] = 0.0f;
	}
	g_Rand_RankingCameraBG = rand() % 4;
	
	switch (PlayNumber.CurrentSelectNumber)
	{
	case 1:
		//1�l�p
		g_aCamera[0].viewport.X = 0;				// �`�悷���ʂ̍���X���W
		g_aCamera[0].viewport.Y = 0;				// �`�悷���ʂ̍���Y���W
		g_aCamera[0].viewport.Width = 1280;			// ��ʂ̕�
		g_aCamera[0].viewport.Height = 720;			// ��ʂ̍���
		g_aCamera[0].viewport.MinZ = 0.0f;			// 
		g_aCamera[0].viewport.MaxZ = 1.0f;			// 
		break;
	case 2:
		//2�l�p(��l��)//
		g_aCamera[0].viewport.X = 0;				// �`�悷���ʂ̍���X���W
		g_aCamera[0].viewport.Y = 0;				// �`�悷���ʂ̍���Y���W
		g_aCamera[0].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[0].viewport.Height = 720;			// ��ʂ̍���
		g_aCamera[0].viewport.MinZ = 0.0f;
		g_aCamera[0].viewport.MaxZ = 1.0f;

		//2�l�p(��l��)
		g_aCamera[1].viewport.X = 640;				// �`�悷���ʂ̍���X���W
		g_aCamera[1].viewport.Y = 0;					// �`�悷���ʂ̍���Y���W
		g_aCamera[1].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[1].viewport.Height = 720;			// ��ʂ̍���
		g_aCamera[1].viewport.MinZ = 0.0f;
		g_aCamera[1].viewport.MaxZ = 1.0f;
		break;
	case 3:
		//3�E4�l�p(1�l��)//
		g_aCamera[0].viewport.X = 0;				// �`�悷���ʂ̍���X���W
		g_aCamera[0].viewport.Y = 0;				// �`�悷���ʂ̍���Y���W
		g_aCamera[0].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[0].viewport.Height = 360;			// ��ʂ̍���
		g_aCamera[0].viewport.MinZ = 0.0f;
		g_aCamera[0].viewport.MaxZ = 1.0f;

		//3�E4�l�p(2�l��)
		g_aCamera[1].viewport.X = 640;				// �`�悷���ʂ̍���X���W
		g_aCamera[1].viewport.Y = 0;				// �`�悷���ʂ̍���Y���W
		g_aCamera[1].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[1].viewport.Height = 360;			// ��ʂ̍���
		g_aCamera[1].viewport.MinZ = 0.0f;
		g_aCamera[1].viewport.MaxZ = 1.0f;

		//3�E4�l�p(3�l��)
		g_aCamera[2].viewport.X = 0;				// �`�悷���ʂ̍���X���W
		g_aCamera[2].viewport.Y = 360;					// �`�悷���ʂ̍���Y���W
		g_aCamera[2].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[2].viewport.Height = 360;			// ��ʂ̍���
		g_aCamera[2].viewport.MinZ = 0.0f;
		g_aCamera[2].viewport.MaxZ = 1.0f;
		break;
	case 4:
		//3�E4�l�p(1�l��)//
		g_aCamera[0].viewport.X = 0;				// �`�悷���ʂ̍���X���W
		g_aCamera[0].viewport.Y = 0;				// �`�悷���ʂ̍���Y���W
		g_aCamera[0].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[0].viewport.Height = 360;			// ��ʂ̍���
		g_aCamera[0].viewport.MinZ = 0.0f;
		g_aCamera[0].viewport.MaxZ = 1.0f;
		//3�E4�l�p(2�l��)
		g_aCamera[1].viewport.X = 640;				// �`�悷���ʂ̍���X���W
		g_aCamera[1].viewport.Y = 0;				// �`�悷���ʂ̍���Y���W
		g_aCamera[1].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[1].viewport.Height = 360;			// ��ʂ̍���
		g_aCamera[1].viewport.MinZ = 0.0f;
		g_aCamera[1].viewport.MaxZ = 1.0f;
		//3�E4�l�p(3�l��)
		g_aCamera[2].viewport.X = 0;				// �`�悷���ʂ̍���X���W
		g_aCamera[2].viewport.Y = 360;				// �`�悷���ʂ̍���Y���W
		g_aCamera[2].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[2].viewport.Height = 360;			// ��ʂ̍���
		g_aCamera[2].viewport.MinZ = 0.0f;
		g_aCamera[2].viewport.MaxZ = 1.0f;
		//3�E4�l�p(4�l��)
		g_aCamera[3].viewport.X = 640;				// �`�悷���ʂ̍���X���W
		g_aCamera[3].viewport.Y = 360;				// �`�悷���ʂ̍���Y���W
		g_aCamera[3].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[3].viewport.Height = 360;			// ��ʂ̍���
		g_aCamera[3].viewport.MinZ = 0.0f;
		g_aCamera[3].viewport.MaxZ = 1.0f;
		break;
	}
	
	//���̑��p(3D��ʃ^�C�g���Ȃ�)
	g_aCamera[4].viewport.X = 0;					// �`�悷���ʂ̍���X���W
	g_aCamera[4].viewport.Y = 0;					// �`�悷���ʂ̍���Y���W
	g_aCamera[4].viewport.Width = 1280;				// ��ʂ̕�
	g_aCamera[4].viewport.Height = 720;				// ��ʂ̍���
	g_aCamera[4].viewport.MinZ = 0.0f;				// 
	g_aCamera[4].viewport.MaxZ = 1.0f;				// 
}

//====================================================================
//�J�����̏I������
//====================================================================
void UninitCamera(void)
{

}

//====================================================================
//�J�����̍X�V����
//====================================================================
void UpdateCamera(void)
{
	MODE mode = GetMode();

	switch (mode)
	{
	case MODE_TITLE:
		
		if (bEnter == false)
		{
			Titlecamera();
		}

		if (bEnter == true)
		{
			MoveTitleCamera(1);
		}

		break;
	case MODE_NUMBERSELECT:
		SelectNumberCamera();
		break;
	case MODE_TUTORIAL:
#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_F5) == true)
		{//�L�[�������ꂽ�ꍇ
			g_bTpsCamera = g_bTpsCamera ? false : true;			//�ώ@�p���[�h�ɕύX
		}
#endif
		//�O�l�̃J�������g�����ǂ���
		if (g_bTpsCamera == false)
		{//�g���Ă��Ȃ��ꍇ
		 //�v���C���[���_�J����
			PlayerCamera();
		}
		else
		{//�g���Ă���ꍇ
		 //�ώ@�p���[�h
			TpsCamera();
		}
		break;
	case MODE_GAME:
#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_F5) == true)
		{//�L�[�������ꂽ�ꍇ
			g_bTpsCamera = g_bTpsCamera ? false : true;			//�ώ@�p���[�h�ɕύX
		}
#endif
		//�O�l�̃J�������g�����ǂ���
		if (g_bTpsCamera == false)
		{//�g���Ă��Ȃ��ꍇ
			//�v���C���[���_�J����
			//PlayerFpsCamera();
			PlayerCamera();
		}
		else
		{//�g���Ă���ꍇ
			//�ώ@�p���[�h
			TpsCamera();
		}
		break;
	case MODE_RESULT:
		ResultCamera();
		break;
	case MODE_RANKING:
		RankingCamera();
		break;
	}
}

//====================================================================
//�J�����̐ݒ菈��
//====================================================================
void SetCamera(int nIdx)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_aCamera[nIdx].viewport);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aCamera[nIdx].mtxProjection);

	if (nIdx == 4)
	{
		//�v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&g_aCamera[nIdx].mtxProjection,
			D3DXToRadian(45.0f),
			(float)g_aCamera[nIdx].viewport.Width / (float)g_aCamera[nIdx].viewport.Height,
			10.0f,
			10000.0f);
	}
	else
	{
		//�v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&g_aCamera[nIdx].mtxProjection,
			D3DXToRadian(45.0f),
			(float)g_aCamera[nIdx].viewport.Width / (float)g_aCamera[nIdx].viewport.Height,
			10.0f,
			1000.0f);
	}

#ifdef _DEBUG
	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_aCamera[nIdx].mtxProjection,
		D3DXToRadian(45.0f),
		(float)g_aCamera[nIdx].viewport.Width / (float)g_aCamera[nIdx].viewport.Height,
		10.0f,
		10000.0f);
#endif

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_aCamera[nIdx].mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aCamera[nIdx].mtxView);

	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_aCamera[nIdx].mtxView,
		&g_aCamera[nIdx].posV,
		&g_aCamera[nIdx].posR,
		&g_aCamera[nIdx].vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_aCamera[nIdx].mtxView);

	//�J�������g���Ă��Ԃ�
	g_aCamera[nIdx].bUse = true;
}

//====================================================================
// �J�����̒Ǐ]����
//====================================================================
void Camerafollow(int nCurrentCamera)
{
	//�|�C���^���̎擾
	Player *pPlayer = GetPlayer();

	D3DXVECTOR3 posRDiff;
	D3DXVECTOR3 posVDiff;

	//�ړI�̎��_��ݒ�(�����l)
	g_aCamera[nCurrentCamera].posVDest = D3DXVECTOR3(g_aCamera[nCurrentCamera].posRDest.x + (cosf(g_aCamera[nCurrentCamera].rot.z) * sinf(g_aCamera[nCurrentCamera].rot.y)) * -CAMERA_DISTANCE,
													pPlayer[nCurrentCamera].pos.y + g_aCamera[nCurrentCamera].fposVmoveY,
													g_aCamera[nCurrentCamera].posRDest.z + (cosf(g_aCamera[nCurrentCamera].rot.z) * cosf(g_aCamera[nCurrentCamera].rot.y)) * -CAMERA_DISTANCE);

	//�ړI�̒����_��ݒ�(�����l)
	g_aCamera[nCurrentCamera].posRDest = D3DXVECTOR3(pPlayer[nCurrentCamera].pos.x + sinf(pPlayer->rot.y + D3DX_PI) * 0.0f,
													pPlayer[nCurrentCamera].pos.y,
													pPlayer[nCurrentCamera].pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 0.0f);

	posRDiff = g_aCamera[nCurrentCamera].posRDest - g_aCamera[nCurrentCamera].posR;			//�����_�̍���
	posVDiff = g_aCamera[nCurrentCamera].posVDest - g_aCamera[nCurrentCamera].posV;			//���_�̍���

	g_aCamera[nCurrentCamera].posR += posRDiff * CAMERA_CORR_V;			//�����_��␳����

	g_aCamera[nCurrentCamera].posV += posVDiff * CAMERA_CORR_V;			//���_��␳����
}

//==============================
//�_���[�W���󂯂����̃J�����̓���
//==============================
void DownCamera(int nCntCamera)
{
	Player *pPlayer = GetPlayer();

	if (pPlayer[nCntCamera].State == PLAYER_HIT)
	{
		g_aCamera[nCntCamera].rot.x = DAMAGECAMERA_ROT_Y;
		pPlayer[nCntCamera].rot.x = DAMAGECAMERA_ROT_Y;
	}

	g_nCount[nCntCamera]++;

	if (pPlayer[nCntCamera].State == PLAYER_WAIT && g_aCamera[nCntCamera].rot.x <= 0.0f && g_nCount[nCntCamera] >= DAMAGECAMERA_TIME)
	{
		g_aCamera[nCntCamera].rot.x += DAMAGECAMERA_UPSPEED;
		pPlayer[nCntCamera].rot.x += DAMAGECAMERA_UPSPEED;
	}

	if (pPlayer[nCntCamera].State == PLAYER_NORMAL)
	{
		g_nCount[nCntCamera] = 0;
	}
}

//==============================
//���񂾎��̃J�����̓���
//==============================
void DeathCameraEnemy(int nCntCamera)
{
	//�v���C���[���̎擾
	Player *pPlayer = GetPlayer();
	ENEMY *pEnemy = GetEnemy();
	PlayNumberSelect NumberSelect = GetPlayNumberSelect();

	pPlayer += nCntCamera;

	float rotYDiff;

	if (pPlayer->nLife <= 0)
	{
		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++, pEnemy++)
		{
			if (pEnemy->bHit == true)
			{
				//�G�̈ʒu����v���C���[�̊p�x�����߂�
				rotYDiff = atan2f((pEnemy->pos.x - g_aCamera->posR.x), (pEnemy->pos.z - g_aCamera->posR.z));

				//�J������G�̕����Ɍ�����
				g_aCamera->rot.y = rotYDiff;
				
				//�J�����������Ă鍂����G�̓��̕����֌�����(�Œ�l)
				g_aCamera->rot.x = 0.85f;

				//�J�����̊p�x���v���C���[�̊p�x�ɑ������
				pPlayer->rot.y = g_aCamera->rot.y;
				pPlayer->rot.x = g_aCamera->rot.x;

				//�v���C���[���ێ����郉�C�g�̍X�V����
				SetLight(pPlayer->LightIdx00, D3DLIGHT_SPOT, pPlayer->LightColor, D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 50.0f, pPlayer->pos.z), D3DXVECTOR3(sinf(Getrot(nCntCamera).y), sinf(Getrot(nCntCamera).x), cosf(Getrot(nCntCamera).y)), 350.0f, 1.0f);

				//���S��Ԃ֐؂�ւ���
				if (pEnemy->state == ENEMYSTATE_PATROL && pEnemy->StateCount <= 0)
				{//�G�̏�Ԃ����񃂁[�h�ɐ؂�ւ������

					//�v���C���[�̏�Ԃ����S��Ԃ�
					pPlayer->State = PLAYER_DEATH;

					//�G�̃q�b�g�����false��
					pEnemy->bHit = false;
				}
			}
		}
	}
}

//==============================
//���񂾎��̃J�����̓���
//==============================
void DeathCamera(int nCntCamera)
{
	//�v���C���[���̎擾
	Player *pPlayer = GetPlayer();

	pPlayer += nCntCamera;

	//��Ɍ�������܂ł̃J�E���g
	g_nCount1[nCntCamera]++;

	//�J���������ɗ��Ƃ�
	if (g_aCamera->posV.y >= DEATHCAMERA_POS_Y)
	{//�J�����̈ʒu���F���ȏ�̎�
		//�J�����𗎂Ƃ�
		g_aCamera->posR.y -= DEATHCAMERA_SPEED;
		g_aCamera->posV.y -= DEATHCAMERA_SPEED;

		//�J�E���g������������
		g_Acc[nCntCamera] = 0;
	}
	else if (g_aCamera->rot.x <= DEATHCAMERA_ROTEND && g_nCount1[nCntCamera] >= DEATHCAMERA_TIME)
	{//�J�����̌��������l�ȉ����J�E���g����̎�
		//���������X�ɑ��₷
		g_Acc[nCntCamera] += DEATHCAMERA_UPSPEED;

		//�J��������ɌX����
		g_aCamera->rot.x += DEATHCAMERA_UPSPEED + g_Acc[nCntCamera];
		g_aCamera->rot.z += DEATHCAMERA_UPSPEED + g_Acc[nCntCamera];

		//�J�E���g��������
		g_nCount1[nCntCamera] = 0;
	}
}

//==============================
//�J�����̏㉺
//==============================
void StateYMove(int nCurrentCamera)
{
	Player *pPlayer = GetPlayer();

	float posYDiff;

	if (pPlayer[nCurrentCamera].MoveState == PLAYER_MOVESTATE_DASH)
	{
		//��Ԃ̑J��
		if (g_aCamera[nCurrentCamera].fposVmoveY >= CAMERA_HOMING_POSY + POS_MOVE_MAX)
		{
			g_aCamera[nCurrentCamera].State = CAMERASTATE_DOWN;
		}
		if (g_aCamera[nCurrentCamera].fposVmoveY <= CAMERA_HOMING_POSY + 0.5f)
		{
			g_aCamera[nCurrentCamera].State = CAMERASTATE_UP;
		}

		//�J�����̏㉺�ړ�
		if (g_aCamera[nCurrentCamera].State == CAMERASTATE_UP)
		{
			g_aCamera[nCurrentCamera].fposVmoveY += UP_DOWN_SPPED;
		}
		else if (g_aCamera[nCurrentCamera].State == CAMERASTATE_DOWN)
		{
			g_aCamera[nCurrentCamera].fposVmoveY -= UP_DOWN_SPPED;
		}
	}

	//�J�����ʒu�����̈ʒu�ɖ߂�悤��
	else if (g_aCamera[nCurrentCamera].State == CAMERASTATE_NONE)
	{
		//���̈ʒu�ƌ��݂̈ʒu�̍����Z�o
		posYDiff = CAMERA_HOMING_POSY - g_aCamera[nCurrentCamera].fposVmoveY;

		g_aCamera[nCurrentCamera].fposVmoveY += posYDiff * YUAN_TO_CORRE;
	}
}

//=======================================
//�ώ@�p�J����
//=======================================
void TpsCamera(void)
{
	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	Player *pPlayer = GetPlayer();

	//�J�����ύX
	if (GetKeyboardTrigger(DIK_F4) == true)
	{
		g_nCurrentCamera++;			//�g���J������ς���

		g_nCurrentCamera %= PlayNumber.CurrentSelectNumber;			//�J��������܂ŗ�����ŏ��̃J�����ɖ߂�
	}

	for (int nCntCamera = g_nCurrentCamera; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_aCamera[nCntCamera].bUse == true && pPlayer[nCntCamera].bUse == true)
		{
			if (g_aCamera[g_nCurrentCamera].rot.x <= D3DX_PI * 0.5f && g_aCamera[g_nCurrentCamera].rot.x >= -(D3DX_PI * 0.5f))
			{//����

				g_aCamera[g_nCurrentCamera].rotOld = g_aCamera[g_nCurrentCamera].rot;

				//�L�[�{�[�h
				if (GetKeyboardPress(DIK_I) == true)
				{
					g_aCamera[g_nCurrentCamera].rot.x += CAMERA_VR_SPEED;
				}
				if (GetKeyboardPress(DIK_K) == true)
				{
					g_aCamera[g_nCurrentCamera].rot.x -= CAMERA_VR_SPEED;
				}

				//�E�X�e�B�b�N�̏㉺���_�ړ�����
				g_aCamera[g_nCurrentCamera].rot.x += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;

				if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
				{
					g_aCamera[g_nCurrentCamera].rot.x -= GetMouseMove().y * CAMERA_VR_SPEED;
				}
			}

			//�E�X�e�B�b�N�̏㉺���_�ړ�����
			if (fabsf(g_aCamera[g_nCurrentCamera].rot.x) > fabsf(D3DX_PI * 0.5f))
			{//����ɒB�������P�t���[���O��rot�ɂ��ǂ�
				g_aCamera[g_nCurrentCamera].rot = g_aCamera[g_nCurrentCamera].rotOld;
			}

			//�L�[�{�[�h
			if (GetKeyboardPress(DIK_J) == true)
			{
				g_aCamera[g_nCurrentCamera].rot.y -= CAMERA_VR_SPEED;

			}
			if (GetKeyboardPress(DIK_L) == true)
			{
				g_aCamera[g_nCurrentCamera].rot.y += CAMERA_VR_SPEED;
			}

			//�E�X�e�B�b�N�̍��E���_�ړ�����
			g_aCamera[g_nCurrentCamera].rot.y += GetGamepad_Stick_Right(0).x * CAMERA_VR_SPEED;

			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				g_aCamera[g_nCurrentCamera].rot.y += GetMouseMove().x * CAMERA_VR_SPEED;
			}

			//����������̌����̕␳
			if (g_aCamera[g_nCurrentCamera].rot.y > D3DX_PI * 1.0f)
			{
				g_aCamera[g_nCurrentCamera].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aCamera[g_nCurrentCamera].rot.y < -D3DX_PI * 1.0f)
			{
				g_aCamera[g_nCurrentCamera].rot.y += D3DX_PI * 2.0f;
			}

			//�L�[�{�[�h
			if (GetKeyboardPress(DIK_LSHIFT) == true)
			{
				g_aCamera[g_nCurrentCamera].posV.y += CAMERA_SPEED;
				g_aCamera[g_nCurrentCamera].posR.y += CAMERA_SPEED;

			}
			if (GetKeyboardPress(DIK_LCONTROL) == true)
			{
				g_aCamera[g_nCurrentCamera].posV.y -= CAMERA_SPEED;
				g_aCamera[g_nCurrentCamera].posR.y -= CAMERA_SPEED;
			}

			//���g���K�[���������ނƃJ������������
			g_aCamera[g_nCurrentCamera].posV.y -= GetGamepad_Trigger_Left(0) * 4.0f;
			g_aCamera[g_nCurrentCamera].posR.y -= GetGamepad_Trigger_Left(0) * 4.0f;

			//�E�g���K�[���������ނƃJ�������オ��
			g_aCamera[g_nCurrentCamera].posV.y += GetGamepad_Trigger_Right(0) * 4.0f;
			g_aCamera[g_nCurrentCamera].posR.y += GetGamepad_Trigger_Right(0) * 4.0f;


			//�J�����̈ړ�����
			CameraMove(g_nCurrentCamera);

			//���X�e�B�b�N�ɂ��O��ړ�	
			g_aCamera[g_nCurrentCamera].posV.z += GetGamepad_Stick_Left(0).y * cosf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;
			g_aCamera[g_nCurrentCamera].posV.x += GetGamepad_Stick_Left(0).y * sinf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;

			//���X�e�B�b�N�ɂ�鍶�E�ړ�
			g_aCamera[g_nCurrentCamera].posV.x += GetGamepad_Stick_Left(0).x * cosf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;
			g_aCamera[g_nCurrentCamera].posV.z -= GetGamepad_Stick_Left(0).x * sinf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;

			//���X�e�B�b�N�ɂ��O��ړ�	
			g_aCamera[g_nCurrentCamera].posR.z += GetGamepad_Stick_Left(0).y * cosf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;
			g_aCamera[g_nCurrentCamera].posR.x += GetGamepad_Stick_Left(0).y * sinf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;

			//���X�e�B�b�N�ɂ�鍶�E�ړ�
			g_aCamera[g_nCurrentCamera].posR.x += GetGamepad_Stick_Left(0).x * cosf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;
			g_aCamera[g_nCurrentCamera].posR.z -= GetGamepad_Stick_Left(0).x * sinf(g_aCamera[g_nCurrentCamera].rot.y) * 4.0f;

			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
				{

				}
				if (GetMousePress(PUSH_RIGHT) == true)
				{
					//���_�̏����o�͂���
					g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
				}
				if (GetMousePress(PUSH_LEFT) == true)
				{
					//���_�̏����o�͂���
					g_aCamera[g_nCurrentCamera].posV.x = g_aCamera[g_nCurrentCamera].posR.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.z = g_aCamera[g_nCurrentCamera].posR.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.y = g_aCamera[g_nCurrentCamera].posR.y + sinf(-g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
				}
			}
			else
			{//�}�E�X���삪����Ă��Ȃ��ꍇ
			 //�����_�̏����o�͂���
				g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot.x) * CAMERA_DISTANCE;
			}
		}
	}
}

//=======================================
//�J�����̈ړ�(8����)
//=======================================
void CameraMove(int nCntCamera)
{
	//�������ړ�
	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true)
		{//����ړ�
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.25f) * CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//�����ړ�
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.75f) * CAMERA_SPEED;
		}
		else
		{//���ړ�
			//�J�����ʒu���̍X�V
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + -D3DX_PI * 0.5f) * CAMERA_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true)
		{//�E��ړ�
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//�E���ړ�
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
		}
		else
		{//�E�ړ�
			//�J�����ʒu���̍X�V
			g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//W�L�[�������ꂽ
		//��ړ�
		g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y) * CAMERA_SPEED;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//S�L�[�������ꂽ
		//���ړ�
		g_aCamera[nCntCamera].posV.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posR.x += sinf(g_aCamera[nCntCamera].rot.y + D3DX_PI) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posV.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI) * CAMERA_SPEED;
		g_aCamera[nCntCamera].posR.z += cosf(g_aCamera[nCntCamera].rot.y + D3DX_PI) * CAMERA_SPEED;
	}
}

//=====================================================
//�v���C���[�̃J�����𓮂�������
//=====================================================
void PlayerCamera(void)
{
	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	Player *pPlayer = GetPlayer();
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();
	MODE mode = GetMode();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_aCamera[nCntCamera].bUse == true && pPlayer[nCntCamera].bUse == true)
		{
			if (pPlayer[nCntCamera].State == PLAYER_NORMAL)
			{//�v���C���[��Ԃ��m�[�}���̎�
				if (g_aCamera[nCntCamera].rot.x <= D3DX_PI * 0.5f && g_aCamera[nCntCamera].rot.x >= -(D3DX_PI * 0.5f))
				{//����

					g_aCamera[nCntCamera].rotOld = g_aCamera[nCntCamera].rot;

					//�L�[�{�[�h
					if (GetKeyboardPress(DIK_I) == true)
					{
						g_aCamera[nCntCamera].rot.x += CAMERA_VR_SPEED;

						//�`���[�g���A�����ڂ��J�������[�u�̎�
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
						{
							//�J�������ړ��������Ƃɂ���
							CamMoveTCheck(nCntCamera, true);
						}
					}
					if (GetKeyboardPress(DIK_K) == true)
					{
						g_aCamera[nCntCamera].rot.x -= CAMERA_VR_SPEED;

						//�`���[�g���A�����ڂ��J�������[�u�̎�
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
						{
							//�J�������ړ��������Ƃɂ���
							CamMoveTCheck(nCntCamera, true);
						}
					}

					//�J�����̉��ړ���������`�F�b�N�����鏈��
					if (g_aCamera[nCntCamera].rot.x > 0.1f || g_aCamera[nCntCamera].rot.x < -0.1f)
					{
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
						{
							CamMoveTCheck(nCntCamera, true);
						}
					}

					//�J�����̏c�ړ���������`�F�b�N�����鏈��
					if (g_aCamera[nCntCamera].rot.y > 0.1f || g_aCamera[nCntCamera].rot.y < -0.1f)
					{
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
						{
							CamMoveTCheck(nCntCamera, true);
						}
					}

					//�E�X�e�B�b�N�̏㉺���_�ړ�����
					g_aCamera[nCntCamera].rot.x += GetGamepad_Stick_Right(nCntCamera).y * CAMERA_VR_SPEED;

					/*if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
					{
						g_aCamera[nCntCamera].rot.x -= GetMouseMove().y * CAMERA_VR_SPEED;
					}*/
				}

				//�E�X�e�B�b�N�̏㉺���_�ړ�����
				if (fabsf(g_aCamera[nCntCamera].rot.x) > fabsf(D3DX_PI * 0.5f))
				{//����ɒB�������P�t���[���O��rot�ɂ��ǂ�
					g_aCamera[nCntCamera].rot = g_aCamera[nCntCamera].rotOld;
				}

				//�L�[�{�[�h
				if (GetKeyboardPress(DIK_J) == true)
				{
					g_aCamera[nCntCamera].rot.y -= CAMERA_VR_SPEED;

				}
				if (GetKeyboardPress(DIK_L) == true)
				{
					g_aCamera[nCntCamera].rot.y += CAMERA_VR_SPEED;
				}

				//�E�X�e�B�b�N�̍��E���_�ړ�����
				g_aCamera[nCntCamera].rot.y += GetGamepad_Stick_Right(nCntCamera).x * CAMERA_VR_SPEED;

				/*if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
				{
					g_aCamera[nCntCamera].rot.y += GetMouseMove().x * CAMERA_VR_SPEED;
				}*/

				//����������̌����̕␳
				if (g_aCamera[nCntCamera].rot.y > D3DX_PI * 1.0f)
				{
					g_aCamera[nCntCamera].rot.y -= D3DX_PI * 2.0f;
				}
				else if (g_aCamera[nCntCamera].rot.y < -D3DX_PI * 1.0f)
				{
					g_aCamera[nCntCamera].rot.y += D3DX_PI * 2.0f;
				}

				//�ړ���Ԃɂ��J�����̓���----------
				StateYMove(nCntCamera);

				//���f���Ǐ]����----------------------
				Camerafollow(nCntCamera);
			}
			else if (pPlayer[nCntCamera].State == PLAYER_HIT || pPlayer[nCntCamera].State == PLAYER_WAIT)
			{
				//�_�E����Ԃɂ��J�����̓���
				DownCamera(nCntCamera);
			}
		}
		else if (pPlayer[nCntCamera].State == PLAYER_SMITE)
		{
			DeathCameraEnemy(nCntCamera);
		}
		else if (pPlayer[nCntCamera].State == PLAYER_DEATH)
		{
			DeathCamera(nCntCamera);
		}

		//�����_�̏����o�͂���
		g_aCamera[nCntCamera].posR.x = g_aCamera[nCntCamera].posV.x + sinf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot.x) * CAMERA_DISTANCE;
		g_aCamera[nCntCamera].posR.z = g_aCamera[nCntCamera].posV.z + cosf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot.x) * CAMERA_DISTANCE;
		g_aCamera[nCntCamera].posR.y = g_aCamera[nCntCamera].posV.y + sinf(g_aCamera[nCntCamera].rot.x) * CAMERA_DISTANCE;
	}
}

//==============================================================================================
//3D�p(�^�C�g����ʁE�l���I����ʁE���U���g���)
//==============================================================================================
//�^�C�g�����
void Titlecamera(void)
{
		g_aCamera[4].posV = D3DXVECTOR3(-60.0f, 0.0f, -100.0f);
		g_aCamera[4].posR = D3DXVECTOR3(490.0f, 500.0f, 1000.0);
		g_aCamera[4].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_aCamera[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[4].rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[4].rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		PrintDebugProc("%f , %f , %f", g_aCamera[4].posV.x, g_aCamera[4].posV.y, g_aCamera[4].posV.z);
}

//�l���I�����
void SelectNumberCamera(void)
{
	g_aCamera[4].posV = D3DXVECTOR3(0.0f, 50.0f,-60.0f);
	g_aCamera[4].posR = D3DXVECTOR3(0.0f, 0.0f, 5000.0);
	g_aCamera[4].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_aCamera[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCamera[4].rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCamera[4].rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//���U���g���
void ResultCamera(void)
{
	if (GetClear() != 0)
	{
		g_aCamera[4].posV = D3DXVECTOR3(1010.0f, 20.0f, -353.0f);
		g_aCamera[4].posR = D3DXVECTOR3(-85.0f, 100.0f, 564.0);
	}
	else
	{
		g_aCamera[4].posV = D3DXVECTOR3(48.0f, 15.0f, 68.0f);
		g_aCamera[4].posR = D3DXVECTOR3(38.0f, 0.0f, 73.0f);
	}
}

//�����L���O���
void RankingCamera(void)
{
	switch (g_Rand_RankingCameraBG)
	{
	case 0:
		g_aCamera[4].posV = D3DXVECTOR3(-1953.70f, 35.0f, 1640.36f);
		g_aCamera[4].posR = D3DXVECTOR3(-2170.67f,35.0f,1748.42f);
		break;
	case 1:
		g_aCamera[4].posV = D3DXVECTOR3(473.15f, 35.0f, -69.61f);
		g_aCamera[4].posR = D3DXVECTOR3(300.0f, 35.0f, 556.61f);
		break;

	case 2:
		g_aCamera[4].posV = D3DXVECTOR3(-2200.96f, 35.0f, 1579.65f);
		g_aCamera[4].posR = D3DXVECTOR3(-1950.85f, 100.0f, 1420.71f);
		break;

	case 3:
		g_aCamera[4].posV = D3DXVECTOR3(-1029.69f, 35.0f, 1339.42f);
		g_aCamera[4].posR = D3DXVECTOR3(-929.04f, 35.0f, 1300.73f);
		break;
	}
}

//==========================================
//�J�����̏��
//==========================================
Camera *GetCamera(void)
{
	return &g_aCamera[0];
}

//==========================================
//�J�����̏��
//==========================================
Camera *GetCamera4(void)
{
	return &g_aCamera[4];
}

//==========================================
//�J�����̌������
//==========================================
D3DXVECTOR3 Getrot(int nPlayer)
{
	return g_aCamera[nPlayer].rot;
}

//==========================================
//�I������Ă���J�����ԍ�
//==========================================
int GetCurrentCamera(void)
{
	return g_nCurrentCamera;
}

//=========================================
//�^�C�g���J�����ړ�����
//=========================================
void MoveTitleCamera(int nCnt)
{
	D3DXVECTOR3 PosVDiff;
	D3DXVECTOR3 PosRDiff;

	//�����x�̃J�E���g
	g_nCount[0]++;

	if (g_nCount[0] < 60)
	{
		g_Acc[0] += 0.004f;
		g_nCount[0] = 0;
	}

	if (g_aCamera[4].posV.x <= 200.0f)
	{
		PosVDiff = D3DXVECTOR3(200.0f, 200.0f, 150.0f) - g_aCamera[4].posV;

		PosRDiff = D3DXVECTOR3(-500.0f, 0.0f, 10000.0) - g_aCamera[4].posR;
		
		g_aCamera[4].posV += PosVDiff * CAM_MOVE_SPEED;

		g_aCamera[4].posR += PosRDiff * CAM_MOVE_SPEED;
	}

	if (nCnt <= 0)
	{//�J�����̈ʒu���ړ��p�ɕς��鏈��
		//�G���^�[�����������Ƃɂ���
		bEnter = true;
	}

	else
	{//0�ȊO�̐��l�������Ă����ꍇ
		g_aCamera[4].posV.z += ((float)nCnt + g_Acc[0]);
	}
	
	PrintDebugProc("%f , %f , %f", g_aCamera[4].posV.x, g_aCamera[4].posV.y, g_aCamera[4].posV.z);
}
