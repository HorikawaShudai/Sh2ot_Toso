#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "PlayNumberSelect.h"

#define CAMERA_DISTANCE			(5.0f)		//���_�ƒ����_�̋���
#define MODEL_DISTANCE			(10.0f)		//���f���ƒ����_�̋���
#define CAMERA_SPEED			(2.5f)		//�J�����̈ړ��X�s�[�h
#define CAMERA_VR_SPEED			(0.045f)		//�J�����̎��_�X�s�[�h
#define CAMERA_HOMING			(0.1f)		//�J�����̒Ǐ]�X�s�[�h
#define CAMERA_HOMING_POSY		(35.0f)		//�J�����̒Ǐ]�̈ʒu(Y���W)
#define CAMERA_CORR_V			(0.7f)		//�J�������_�̕␳
#define CAMERA_CORR_R			(0.8f)		//�J���������_�̕␳
#define CAMERA_LENGTH_R			(0.0f)		//�v���C���[�ƃJ���������_�Ƃ̋���

#define MAX_CAMERA				(4)		//�J�����̍ő吔

//�v���g�^�C�v�錾
void TpsCamera(void);			//�ώ@�p�J����
void PlayerFpsCamera(void);		//�v���C���[�̎��_�J����
void Camerafollow(int nCurrentCamera);		//�Ǐ]�J����
void CameraMove(int nCurrentCamera);		//�J�����ړ�


//�O���[�o���ϐ�
Camera g_aCamera[MAX_CAMERA];	//�J�����̏��

int g_nCurrentCamera;			//�I������Ă���J�����̔ԍ�
int g_nSaveCamera;				//�J�����ԍ��ۑ��p
bool g_bTpsCamera;				//�ώ@�p�̃J�������g�����ǂ���

//====================================================================
//�J�����̏���������
//====================================================================
void InitCamera(void)
{
	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		g_aCamera[nCntCamera].posV = D3DXVECTOR3(0.0f, 35.0f, 50.0f);
		g_aCamera[nCntCamera].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_aCamera[nCntCamera].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].rot2Old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aCamera[nCntCamera].bUse = false;
	}

	g_nCurrentCamera = 0;			//�I������Ă���J�����̔ԍ����ŏ��̃J������
	g_bTpsCamera = false;			//�ώ@�p�J�������g���Ă��Ȃ���Ԃ�

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
		g_aCamera[2].viewport.Y = 360;					// �`�悷���ʂ̍���Y���W
		g_aCamera[2].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[2].viewport.Height = 360;			// ��ʂ̍���
		g_aCamera[2].viewport.MinZ = 0.0f;
		g_aCamera[2].viewport.MaxZ = 1.0f;
		//3�E4�l�p(4�l��)
		g_aCamera[3].viewport.X = 640;				// �`�悷���ʂ̍���X���W
		g_aCamera[3].viewport.Y = 360;					// �`�悷���ʂ̍���Y���W
		g_aCamera[3].viewport.Width = 640;			// ��ʂ̕�
		g_aCamera[3].viewport.Height = 360;			// ��ʂ̍���
		g_aCamera[3].viewport.MinZ = 0.0f;
		g_aCamera[3].viewport.MaxZ = 1.0f;
		break;
	}
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

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F5) == true)
	{//�L�[�������ꂽ�ꍇ
		g_bTpsCamera = g_bTpsCamera ? false : true;			//�ώ@�p���[�h�ɕύX
	}
#endif

	if (g_bTpsCamera == false)
	{
		//�v���C���[���_�J����
		PlayerFpsCamera();
	}
	else
	{
		//�ώ@�p���[�h
		TpsCamera();
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

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_aCamera[nIdx].mtxProjection,
		D3DXToRadian(45.0f),
		(float)g_aCamera[nIdx].viewport.Width / (float)g_aCamera[nIdx].viewport.Height,
		10.0f,
		10000.0f);

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

//=======================================
// �v���C���[���_�J����
//=======================================
void PlayerFpsCamera(void)
{
	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//�J�����ύX
	if (GetKeyboardTrigger(DIK_F4) == true)
	{
		g_nCurrentCamera++;			//�g���J������ς���

		g_nCurrentCamera %= PlayNumber.CurrentSelectNumber;			//�J��������܂ŗ�����ŏ��̃J�����ɖ߂�
	}

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_aCamera[nCntCamera].bUse == true)
		{
			if (g_aCamera[g_nCurrentCamera].rot2.y <= D3DX_PI * 0.5f && g_aCamera[g_nCurrentCamera].rot2.y >= -(D3DX_PI * 0.5f))
			{//����

				g_aCamera[g_nCurrentCamera].rot2Old = g_aCamera[g_nCurrentCamera].rot2;

				//�L�[�{�[�h
				if (GetKeyboardPress(DIK_I) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y += CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z += CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x += CAMERA_VR_SPEED;
				}
				if (GetKeyboardPress(DIK_K) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y -= CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z -= CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x -= CAMERA_VR_SPEED;
				}

				//�E�X�e�B�b�N�̏㉺���_�ړ�����
				g_aCamera[g_nCurrentCamera].rot2.y += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[g_nCurrentCamera].rot2.z += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[g_nCurrentCamera].rot2.x += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;

				if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x -= GetMouseMove().y * CAMERA_VR_SPEED;
				}
			}

			//�E�X�e�B�b�N�̏㉺���_�ړ�����
			if (fabsf(g_aCamera[g_nCurrentCamera].rot2.y) > fabsf(D3DX_PI * 0.5f))
			{//����ɒB�������P�t���[���O��rot�ɂ��ǂ�
				g_aCamera[g_nCurrentCamera].rot2 = g_aCamera[g_nCurrentCamera].rot2Old;
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

			//���f���Ǐ]����----------------------
			Camerafollow(g_nCurrentCamera);

			//�L�[�{�[�h
			if (GetKeyboardPress(DIK_T) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.z += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.x += CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.z += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.x += CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

			}
			if (GetKeyboardPress(DIK_G) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.z += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.x += -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.z += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.x += -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_F) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.x += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.z -= -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.x += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.z -= -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_H) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.x += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.z -= CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.x += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.z -= CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}

			//�}�E�X
			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
				{

				}
				if (GetMousePress(PUSH_RIGHT) == true)
				{
					//���_�̏����o�͂���
					g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
				}
				if (GetMousePress(PUSH_LEFT) == true)
				{
					//���_�̏����o�͂���
					g_aCamera[g_nCurrentCamera].posV.x = g_aCamera[g_nCurrentCamera].posR.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.z = g_aCamera[g_nCurrentCamera].posR.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.y = g_aCamera[g_nCurrentCamera].posR.y + sinf(-g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
				}
			}
			else
			{//�}�E�X���삪����Ă��Ȃ��ꍇ
			 //�����_�̏����o�͂���
				g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
			}
		}
	}
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
													pPlayer->pos.y + CAMERA_HOMING_POSY,
													g_aCamera[nCurrentCamera].posRDest.z + (cosf(g_aCamera[nCurrentCamera].rot.z) * cosf(g_aCamera[nCurrentCamera].rot.y)) * -CAMERA_DISTANCE);

	//�ړI�̒����_��ݒ�(�����l)
	g_aCamera[nCurrentCamera].posRDest = D3DXVECTOR3(pPlayer->pos.x + sinf(pPlayer->rot.y + D3DX_PI) * 0.0f,
													pPlayer->pos.y,
													pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 0.0f);

	posRDiff = g_aCamera[nCurrentCamera].posRDest - g_aCamera[nCurrentCamera].posR;			//�����_�̍���
	posVDiff = g_aCamera[nCurrentCamera].posVDest - g_aCamera[nCurrentCamera].posV;			//���_�̍���

	g_aCamera[nCurrentCamera].posR += posRDiff * CAMERA_CORR_V;			//�����_��␳����

	g_aCamera[nCurrentCamera].posV += posVDiff * CAMERA_CORR_V;			//���_��␳����
}

//=======================================
//�ώ@�p�J����
//=======================================
void TpsCamera(void)
{
	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//�J�����ύX
	if (GetKeyboardTrigger(DIK_F4) == true)
	{
		g_nCurrentCamera++;			//�g���J������ς���

		g_nCurrentCamera %= PlayNumber.CurrentSelectNumber;			//�J��������܂ŗ�����ŏ��̃J�����ɖ߂�
	}

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_aCamera[nCntCamera].bUse == true)
		{
			if (g_aCamera[g_nCurrentCamera].rot2.y <= D3DX_PI * 0.5f && g_aCamera[g_nCurrentCamera].rot2.y >= -(D3DX_PI * 0.5f))
			{//����

				g_aCamera[g_nCurrentCamera].rot2Old = g_aCamera[g_nCurrentCamera].rot2;

				//�L�[�{�[�h
				if (GetKeyboardPress(DIK_I) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y += CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z += CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x += CAMERA_VR_SPEED;
				}
				if (GetKeyboardPress(DIK_K) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y -= CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z -= CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x -= CAMERA_VR_SPEED;
				}

				//�E�X�e�B�b�N�̏㉺���_�ړ�����
				g_aCamera[g_nCurrentCamera].rot2.y += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[g_nCurrentCamera].rot2.z += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[g_nCurrentCamera].rot2.x += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;

				if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
				{
					g_aCamera[g_nCurrentCamera].rot2.y -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.z -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[g_nCurrentCamera].rot2.x -= GetMouseMove().y * CAMERA_VR_SPEED;
				}
			}

			//�E�X�e�B�b�N�̏㉺���_�ړ�����
			if (fabsf(g_aCamera[g_nCurrentCamera].rot2.y) > fabsf(D3DX_PI * 0.5f))
			{//����ɒB�������P�t���[���O��rot�ɂ��ǂ�
				g_aCamera[g_nCurrentCamera].rot2 = g_aCamera[g_nCurrentCamera].rot2Old;
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
			g_aCamera[g_nCurrentCamera].posV.y -= GetGamepad_Trigger_Left(0);
			g_aCamera[g_nCurrentCamera].posR.y -= GetGamepad_Trigger_Left(0);

			//�E�g���K�[���������ނƃJ�������オ��
			g_aCamera[g_nCurrentCamera].posV.y += GetGamepad_Trigger_Right(0);
			g_aCamera[g_nCurrentCamera].posR.y += GetGamepad_Trigger_Right(0);


			//�L�[�{�[�h
			CameraMove(g_nCurrentCamera);

			if (GetKeyboardPress(DIK_T) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.z += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.x += CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.z += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.x += CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

			}
			if (GetKeyboardPress(DIK_G) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.z += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.x += -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.z += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.x += -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_F) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.x += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.z -= -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.x += -CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.z -= -CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_H) == true)
			{
				g_aCamera[g_nCurrentCamera].posR.x += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posR.z -= CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);

				g_aCamera[g_nCurrentCamera].posV.x += CAMERA_SPEED * cosf(g_aCamera[g_nCurrentCamera].rot.y);
				g_aCamera[g_nCurrentCamera].posV.z -= CAMERA_SPEED * sinf(g_aCamera[g_nCurrentCamera].rot.y);
			}

			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
				{

				}
				if (GetMousePress(PUSH_RIGHT) == true)
				{
					//���_�̏����o�͂���
					g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
				}
				if (GetMousePress(PUSH_LEFT) == true)
				{
					//���_�̏����o�͂���
					g_aCamera[g_nCurrentCamera].posV.x = g_aCamera[g_nCurrentCamera].posR.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.z = g_aCamera[g_nCurrentCamera].posR.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * -cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[g_nCurrentCamera].posV.y = g_aCamera[g_nCurrentCamera].posR.y + sinf(-g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
				}
			}
			else
			{//�}�E�X���삪����Ă��Ȃ��ꍇ
			 //�����_�̏����o�͂���
				g_aCamera[g_nCurrentCamera].posR.x = g_aCamera[g_nCurrentCamera].posV.x + sinf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.z) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.z = g_aCamera[g_nCurrentCamera].posV.z + cosf(g_aCamera[g_nCurrentCamera].rot.y) * cosf(g_aCamera[g_nCurrentCamera].rot2.x) * CAMERA_DISTANCE;
				g_aCamera[g_nCurrentCamera].posR.y = g_aCamera[g_nCurrentCamera].posV.y + sinf(g_aCamera[g_nCurrentCamera].rot2.y) * CAMERA_DISTANCE;
			}
		}
	}
}

//--------------------------------------------------------------------
//�J�����̈ړ�
//--------------------------------------------------------------------
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

D3DXVECTOR3 Getrot(void)
{
	return g_aCamera[0].rot;
}
