#include "main.h"
#include "camera.h"
#include "input.h"
#include "PlayNumberSelect.h"

#define CAMERA_DISTANCE (200.0f)	//���_�ƒ����_�̋���
#define MODEL_DISTANCE (10.0f)	//���f���ƒ����_�̋���
#define CAMERA_SPEED (3.0f)	//�J�����̈ړ��X�s�[�h
#define CAMERA_VR_SPEED (0.03f)	//�J�����̎��_�X�s�[�h
#define CAMERA_HOMING (0.1f)	//�J�����̒Ǐ]�X�s�[�h

#define MAX_CAMERA		(8)

//�O���[�o���ϐ�
Camera g_aCamera[MAX_CAMERA];	//�J�����̏��

//====================================================================
//�J�����̏���������
//====================================================================
void InitCamera(void)
{
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		g_aCamera[nCntCamera].posV = D3DXVECTOR3(0.0f, 50.0f, 50.0f);
		g_aCamera[nCntCamera].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_aCamera[nCntCamera].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCamera[nCntCamera].rot2Old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aCamera[nCntCamera].bUse = false;
	}

	//1�l�p
	g_aCamera[0].viewport.X = 0;					// �`�悷���ʂ̍���X���W
	g_aCamera[0].viewport.Y = 0;					// �`�悷���ʂ̍���Y���W

	g_aCamera[0].viewport.Width = 1280;			// ��ʂ̕�
	g_aCamera[0].viewport.Height = 720;			// ��ʂ̍���

	g_aCamera[0].viewport.MinZ = 0.0f;			// 
	g_aCamera[0].viewport.MaxZ = 1.0f;			// 


	//2�l�p(��l��)//
	g_aCamera[1].viewport.X = 0;				// �`�悷���ʂ̍���X���W
	g_aCamera[1].viewport.Y = 0;				// �`�悷���ʂ̍���Y���W

	g_aCamera[1].viewport.Width = 640;			// ��ʂ̕�
	g_aCamera[1].viewport.Height = 720;			// ��ʂ̍���

	g_aCamera[1].viewport.MinZ = 0.0f;
	g_aCamera[1].viewport.MaxZ = 1.0f;

	//2�l�p(��l��)
	g_aCamera[2].viewport.X = 640;				// �`�悷���ʂ̍���X���W
	g_aCamera[2].viewport.Y = 0;					// �`�悷���ʂ̍���Y���W

	g_aCamera[2].viewport.Width = 640;			// ��ʂ̕�
	g_aCamera[2].viewport.Height = 720;			// ��ʂ̍���

	g_aCamera[2].viewport.MinZ = 0.0f;
	g_aCamera[2].viewport.MaxZ = 1.0f;


	//3�E4�l�p(1�l��)//
	g_aCamera[3].viewport.X = 0;				// �`�悷���ʂ̍���X���W
	g_aCamera[3].viewport.Y = 0;				// �`�悷���ʂ̍���Y���W

	g_aCamera[3].viewport.Width = 640;			// ��ʂ̕�
	g_aCamera[3].viewport.Height = 360;			// ��ʂ̍���

	g_aCamera[3].viewport.MinZ = 0.0f;
	g_aCamera[3].viewport.MaxZ = 1.0f;

	//3�E4�l�p(2�l��)
	g_aCamera[4].viewport.X = 640;				// �`�悷���ʂ̍���X���W
	g_aCamera[4].viewport.Y = 0;				// �`�悷���ʂ̍���Y���W

	g_aCamera[4].viewport.Width = 640;			// ��ʂ̕�
	g_aCamera[4].viewport.Height = 360;			// ��ʂ̍���

	g_aCamera[4].viewport.MinZ = 0.0f;
	g_aCamera[4].viewport.MaxZ = 1.0f;

	//3�E4�l�p(3�l��)
	g_aCamera[5].viewport.X = 0;				// �`�悷���ʂ̍���X���W
	g_aCamera[5].viewport.Y = 360;					// �`�悷���ʂ̍���Y���W

	g_aCamera[5].viewport.Width = 640;			// ��ʂ̕�
	g_aCamera[5].viewport.Height = 360;			// ��ʂ̍���

	g_aCamera[5].viewport.MinZ = 0.0f;
	g_aCamera[5].viewport.MaxZ = 1.0f;

	//3�E4�l�p(4�l��)
	g_aCamera[6].viewport.X = 640;				// �`�悷���ʂ̍���X���W
	g_aCamera[6].viewport.Y = 360;					// �`�悷���ʂ̍���Y���W

	g_aCamera[6].viewport.Width = 640;			// ��ʂ̕�
	g_aCamera[6].viewport.Height = 360;			// ��ʂ̍���

	g_aCamera[6].viewport.MinZ = 0.0f;
	g_aCamera[6].viewport.MaxZ = 1.0f;
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
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_aCamera[nCntCamera].bUse == true)
		{
			if (g_aCamera[nCntCamera].rot2.y <= D3DX_PI * 0.5f && g_aCamera[nCntCamera].rot2.y >= -(D3DX_PI * 0.5f))
			{//����
				g_aCamera[nCntCamera].rot2Old = g_aCamera[nCntCamera].rot2;

				//�L�[�{�[�h
				if (GetKeyboardPress(DIK_I) == true)
				{
					g_aCamera[nCntCamera].rot2.y += CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.z += CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.x += CAMERA_VR_SPEED;
				}
				if (GetKeyboardPress(DIK_K) == true)
				{
					g_aCamera[nCntCamera].rot2.y -= CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.z -= CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.x -= CAMERA_VR_SPEED;
				}

				//�E�X�e�B�b�N�̏㉺���_�ړ�����
				g_aCamera[nCntCamera].rot2.y += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[nCntCamera].rot2.z += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;
				g_aCamera[nCntCamera].rot2.x += GetGamepad_Stick_Right(0).y * CAMERA_VR_SPEED;

				if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
				{
					g_aCamera[nCntCamera].rot2.y -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.z -= GetMouseMove().y * CAMERA_VR_SPEED;
					g_aCamera[nCntCamera].rot2.x -= GetMouseMove().y * CAMERA_VR_SPEED;
				}
			}

			//�E�X�e�B�b�N�̏㉺���_�ړ�����
			if (fabsf(g_aCamera[nCntCamera].rot2.y) > fabsf(D3DX_PI * 0.5f))
			{//����ɒB�������P�t���[���O��rot�ɂ��ǂ�
				g_aCamera[nCntCamera].rot2 = g_aCamera[nCntCamera].rot2Old;
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
			g_aCamera[nCntCamera].rot.y += GetGamepad_Stick_Right(0).x * CAMERA_VR_SPEED;

			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				g_aCamera[nCntCamera].rot.y += GetMouseMove().x * CAMERA_VR_SPEED;
			}

			//����������̌����̕␳
			if (g_aCamera[nCntCamera].rot.y > D3DX_PI * 1.0f)
			{
				g_aCamera[nCntCamera].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aCamera[nCntCamera].rot.y < -D3DX_PI * 1.0f)
			{
				g_aCamera[nCntCamera].rot.y += D3DX_PI * 2.0f;
			}


			//�L�[�{�[�h
			if (GetKeyboardPress(DIK_LSHIFT) == true)
			{
				g_aCamera[nCntCamera].posV.y += CAMERA_SPEED;
				g_aCamera[nCntCamera].posR.y += CAMERA_SPEED;

			}
			if (GetKeyboardPress(DIK_LCONTROL) == true)
			{
				g_aCamera[nCntCamera].posV.y -= CAMERA_SPEED;
				g_aCamera[nCntCamera].posR.y -= CAMERA_SPEED;
			}

			//���g���K�[���������ނƃJ������������
			g_aCamera[nCntCamera].posV.y -= GetGamepad_Trigger_Left(0);
			g_aCamera[nCntCamera].posR.y -= GetGamepad_Trigger_Left(0);

			//�E�g���K�[���������ނƃJ�������オ��
			g_aCamera[nCntCamera].posV.y += GetGamepad_Trigger_Right(0);
			g_aCamera[nCntCamera].posR.y += GetGamepad_Trigger_Right(0);

			//�L�[�{�[�h
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_aCamera[nCntCamera].posR.z += CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posR.x += CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);

				g_aCamera[nCntCamera].posV.z += CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posV.x += CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);

			}
			if (GetKeyboardPress(DIK_S) == true)
			{
				g_aCamera[nCntCamera].posR.z += -CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posR.x += -CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);

				g_aCamera[nCntCamera].posV.z += -CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posV.x += -CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_A) == true)
			{
				g_aCamera[nCntCamera].posR.x += -CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posR.z -= -CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);

				g_aCamera[nCntCamera].posV.x += -CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posV.z -= -CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);
			}
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_aCamera[nCntCamera].posR.x += CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posR.z -= CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);

				g_aCamera[nCntCamera].posV.x += CAMERA_SPEED * cosf(g_aCamera[nCntCamera].rot.y);
				g_aCamera[nCntCamera].posV.z -= CAMERA_SPEED * sinf(g_aCamera[nCntCamera].rot.y);
			}

			////���X�e�B�b�N�ɂ��O��ړ�	
			//g_aCamera[nCntCamera].posV.z += GetGamepad_Stick_Left(0).y * cosf(g_aCamera[nCntCamera].rot.y);
			//g_aCamera[nCntCamera].posV.x += GetGamepad_Stick_Left(0).y * sinf(g_aCamera[nCntCamera].rot.y);

			////���X�e�B�b�N�ɂ�鍶�E�ړ�
			//g_aCamera[nCntCamera].posV.x += GetGamepad_Stick_Left(0).x * cosf(g_aCamera[nCntCamera].rot.y);
			//g_aCamera[nCntCamera].posV.z -= GetGamepad_Stick_Left(0).x * sinf(g_aCamera[nCntCamera].rot.y);

			////���X�e�B�b�N�ɂ��O��ړ�	
			//g_aCamera[nCntCamera].posR.z += GetGamepad_Stick_Left(0).y * cosf(g_aCamera[nCntCamera].rot.y);
			//g_aCamera[nCntCamera].posR.x += GetGamepad_Stick_Left(0).y * sinf(g_aCamera[nCntCamera].rot.y);

			////���X�e�B�b�N�ɂ�鍶�E�ړ�
			//g_aCamera[nCntCamera].posR.x += GetGamepad_Stick_Left(0).x * cosf(g_aCamera[nCntCamera].rot.y);
			//g_aCamera[nCntCamera].posR.z -= GetGamepad_Stick_Left(0).x * sinf(g_aCamera[nCntCamera].rot.y);

			//���f���Ǐ]����----------------------
			//Model * pModel = GetModel();
			//g_aCamera[nCntCamera].posRDest.x = g_aCamera[nCntCamera].posV.x + sinf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.z) * CAMERA_DISTANCE;
			//g_aCamera[nCntCamera].posRDest.z = g_aCamera[nCntCamera].posV.z + cosf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.x) * CAMERA_DISTANCE;
			//g_aCamera[nCntCamera].posRDest.y = g_aCamera[nCntCamera].posV.y + sinf(g_aCamera[nCntCamera].rot2.y) * CAMERA_DISTANCE;

			//g_aCamera[nCntCamera].posVDest.x = pModel->pos.x + sinf(pModel->rot.y) * MODEL_DISTANCE + sinf(g_aCamera[nCntCamera].rot.y) * -cosf(g_aCamera[nCntCamera].rot2.z) * CAMERA_DISTANCE;
			//g_aCamera[nCntCamera].posVDest.z = pModel->pos.z + cosf(pModel->rot.y) * MODEL_DISTANCE + cosf(g_aCamera[nCntCamera].rot.y) * -cosf(g_aCamera[nCntCamera].rot2.x) * CAMERA_DISTANCE;
			//g_aCamera[nCntCamera].posVDest.y = pModel->pos.y + sinf(-g_aCamera[nCntCamera].rot2.y) * CAMERA_DISTANCE;
			//
			//g_aCamera[nCntCamera].posR += (g_aCamera[nCntCamera].posRDest - g_aCamera[nCntCamera].posR) * CAMERA_HOMING;
			//g_aCamera[nCntCamera].posV += (g_aCamera[nCntCamera].posVDest - g_aCamera[nCntCamera].posV) * CAMERA_HOMING;

			//------------------------------------

			if (GetMousePress(PUSH_LEFT) == true || GetMousePress(PUSH_RIGHT) == true)
			{
				if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
				{

				}
				if (GetMousePress(PUSH_RIGHT) == true)
				{
					//���_�̏����o�͂���
					g_aCamera[nCntCamera].posR.x = g_aCamera[nCntCamera].posV.x + sinf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[nCntCamera].posR.z = g_aCamera[nCntCamera].posV.z + cosf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[nCntCamera].posR.y = g_aCamera[nCntCamera].posV.y + sinf(g_aCamera[nCntCamera].rot2.y) * CAMERA_DISTANCE;
				}
				if (GetMousePress(PUSH_LEFT) == true)
				{
					//���_�̏����o�͂���
					g_aCamera[nCntCamera].posV.x = g_aCamera[nCntCamera].posR.x + sinf(g_aCamera[nCntCamera].rot.y) * -cosf(g_aCamera[nCntCamera].rot2.z) * CAMERA_DISTANCE;
					g_aCamera[nCntCamera].posV.z = g_aCamera[nCntCamera].posR.z + cosf(g_aCamera[nCntCamera].rot.y) * -cosf(g_aCamera[nCntCamera].rot2.x) * CAMERA_DISTANCE;
					g_aCamera[nCntCamera].posV.y = g_aCamera[nCntCamera].posR.y + sinf(-g_aCamera[nCntCamera].rot2.y) * CAMERA_DISTANCE;
				}
			}
			else
			{//�}�E�X���삪����Ă��Ȃ��ꍇ
					//�����_�̏����o�͂���
				g_aCamera[nCntCamera].posR.x = g_aCamera[nCntCamera].posV.x + sinf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.z) * CAMERA_DISTANCE;
				g_aCamera[nCntCamera].posR.z = g_aCamera[nCntCamera].posV.z + cosf(g_aCamera[nCntCamera].rot.y) * cosf(g_aCamera[nCntCamera].rot2.x) * CAMERA_DISTANCE;
				g_aCamera[nCntCamera].posR.y = g_aCamera[nCntCamera].posV.y + sinf(g_aCamera[nCntCamera].rot2.y) * CAMERA_DISTANCE;
			}
		}
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

D3DXVECTOR3 Getrot(void)
{
	return g_aCamera[0].rot;
}
