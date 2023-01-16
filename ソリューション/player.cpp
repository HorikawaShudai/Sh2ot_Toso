//============================
//
//�v���C���[����(player.cpp)
//Author:���� �F�M
//
//============================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"

//�}�N����`

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTexturPlayer[10] = {};	//�e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshPlayer = NULL; //���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer  = NULL; //�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0; //�}�e���A���̐�
D3DXVECTOR3 g_posPlayer; //�ʒu
D3DXVECTOR3 g_rotPlayer; //����
D3DXMATRIX g_mtxWorldPlayer;  //���[���h�}�g���b�N�X
D3DXVECTOR3 g_posPlayerDest; //�ړI�̈ʒu
D3DXVECTOR3 g_rotPlayerDest; //�ړI�̌���
float g_PlayerfAngle; //�v���C���[�̊p�x
float g_PlayerfLength; //�v���C���[�̒���
D3DXVECTOR3 DiffPlayer;

Camera g_cam;	//�J�����̏��

//====================
//�v���C���[�̏�����
//====================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾

	//�e��ϐ��̏�����
	g_posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu��������

	g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //������������

	g_posPlayerDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ړI�̈ʒu��������
	g_rotPlayerDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ړI�̌�����������

	D3DXVECTOR3 DiffModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_cam.posV = D3DXVECTOR3(0.0f, 50.0f, 50.0f);
	g_cam.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cam.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_cam.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cam.rot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cam.rot2Old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_���Œ肷��ꍇ
	g_PlayerfAngle = atan2f
	(//�Ίp���̊p�x
		g_posPlayerDest.x - g_posPlayer.x,
		g_posPlayerDest.z - g_posPlayer.z
	);

	g_PlayerfLength = sqrtf
	(//�Ίp���̒���
		(g_posPlayerDest.x - g_posPlayer.x) * (g_posPlayerDest.x - g_posPlayer.x) +
		(g_posPlayerDest.z - g_posPlayer.z) * (g_posPlayerDest.z - g_posPlayer.z)
	) * 0.5f;

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("Data\\MODEL\\Player.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL *pMat; //�}�e���A���ւ̃|�C���^

						//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C���l�[�������݂���
		 //�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturPlayer[nCntMat]);
		}
	}

}

//�v���C���[�̏I������
void UninitPlayer(void)
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//�v���C���[�̍X�V����
void UpdatePlayer(void)
{
	MovePlayer();

	AnglePlayer();
}

//�v���C���[�̕`�揈��
void DrawPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;  //���݂̃}�e���A���ۑ��p

	D3DXMATERIAL *pMat;	  //�}�e���A���f�[�^�ւ̃|�C���^

						  //���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotPlayer.y, g_rotPlayer.x, g_rotPlayer.z);

	D3DXMatrixMultiply(&g_mtxWorldPlayer,
		&g_mtxWorldPlayer,
		&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		g_posPlayer.x, g_posPlayer.y, g_posPlayer.z);

	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturPlayer[nCntMat]);

		//�v���C���[(�p�[�c)�̕`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================
//�|���S���̈ʒu��^���鏈��
//=============================
D3DXVECTOR3 PosPlayer(void)
{
	return g_posPlayer;
}

//===========================
//�|���S���̌����������鏈��
//===========================
D3DXVECTOR3 RotPlayer(void)
{
	return g_rotPlayer;
}

//==================================
//�v���C���[�̈ړ�����
//==================================
void MovePlayer(void)
{
}

//==================================
//�v���C���[�̊p�x����
//==================================
void AnglePlayer(void)
{
	float fRotMove = g_rotPlayer.y;
	float fRotDest = g_rotPlayer.y; //�ڕW�̊p�x
	float fRotDiff = 0.0f; //�ڕW�ƌ��݊p�x�̍���

	//���ړ�
	if (GetKeyboardPress(DIK_T) == true)
	{
		if (GetKeyboardPress(DIK_H) == true)
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 0.25f * D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 0.25f * D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 0.75f * -D3DX_PI;
		}

		else if (GetKeyboardPress(DIK_F) == true)
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 0.25f * -D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 0.25f * -D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 0.75f * D3DX_PI;
		}

		else
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 0.0f * D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 0.0f * D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 1.0f * D3DX_PI;
		}
	}

	//��O�ړ�
	else if (GetKeyboardPress(DIK_G) == true)
	{
		if (GetKeyboardPress(DIK_H) == true)
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 0.75f * D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 0.75f * D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 0.25f * -D3DX_PI;

		}

		else if (GetKeyboardPress(DIK_F) == true)
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 0.75f * -D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 0.75f * -D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 0.25f * D3DX_PI;

		}

		else
		{
			g_posPlayer.x += sinf(g_cam.rot.y + 1.0f * D3DX_PI) * 1.0f;
			g_posPlayer.z += cosf(g_cam.rot.y + 1.0f * D3DX_PI) * 1.0f;

			fRotDest = g_cam.rot.y + 0.0f * D3DX_PI;
		}
	}

	//���ړ�
	else if (GetKeyboardPress(DIK_F) == true)
	{
		g_posPlayer.x += sinf(g_cam.rot.y + 0.5f * -D3DX_PI) * 1.0f;
		g_posPlayer.z += cosf(g_cam.rot.y + 0.5f * -D3DX_PI) * 1.0f;

		fRotDest = g_cam.rot.y + 0.5f * D3DX_PI;
	}

	//�E�ړ�
	else if (GetKeyboardPress(DIK_H) == true)
	{
		g_posPlayer.x += sinf(g_cam.rot.y + 0.5f * D3DX_PI) * 1.0f;
		g_posPlayer.z += cosf(g_cam.rot.y + 0.5f * D3DX_PI) * 1.0f;

		fRotDest = g_cam.rot.y + 0.5f * -D3DX_PI;
	}


	//�ڕW�̊p�x�Ƃ̍��������߂鏈��
	fRotDiff = fRotDest - fRotMove;

	//�ڕW�̊p�x�̕␳
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff += -D3DX_PI * 2;
	}

	else if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += D3DX_PI * 2;
	}

	//�ړI�̊p�x�܂ŕ␳���鏈��
	g_rotPlayer.y += fRotDiff * 0.1f;

	//�v���C���[�̊p�x�̕␳
	if (g_rotPlayer.y > D3DX_PI)
	{
		g_rotPlayer.y += -D3DX_PI * 2;
	}

	else if (g_rotPlayer.y < -D3DX_PI)
	{
		g_rotPlayer.y += D3DX_PI * 2;
	}

	//�ړI�̎��_��ݒ�
	g_posPlayerDest.x = g_posPlayer.x - sinf(g_cam.rot.y + D3DX_PI - g_PlayerfAngle) * g_PlayerfLength;
	g_posPlayerDest.z = g_posPlayer.z - cosf(g_cam.rot.y + D3DX_PI - g_PlayerfAngle) * g_PlayerfLength;

	//�ړI�̈ʒu�܂ŕ␳���鏈��
	fRotDiff = fRotDest - fRotMove;

	DiffPlayer.x = g_posPlayerDest.x - g_posPlayer.x;

	DiffPlayer.z = g_posPlayerDest.z - g_posPlayer.z;

	//�ړI�̈ʒu�܂ŕ␳���鏈��
	g_posPlayer.x += DiffPlayer.x * 0.05f;

	g_posPlayer.z += DiffPlayer.z * 0.05f;
}
