//========================================================================================
//
// �h�[����̃|���S���̕`��[meshcydome.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "main.h"
#include "meshdome.h"

#define WAIGHT_SIZE (17)			//���̒��_��(�Xor�P�Vor�R�R)�������ƃo�O��
#define HEIGHT_SIZE (7)				//�c�̒��_��
#define WAIGHT_CENTER (0.5f)		//���̌��_(0.0f�`1.0f)
#define HEIGHT_CENTER (1.0f)		//�c�̌��_(0.0f�`1.0f)
#define CYLINDER_HEIGHT (150.0f)	//�ǈꖇ�̍���
#define CYLINDER_RADIUS (2800.0f)	//�~�̔��a
#define MAX_TEX  (2)				//�e�N�X�`���̍ő吔

typedef enum
{
	TEX_CLOUD = 0,
	TEX_BLACK,
	TEX_MAX,
}MODE_TEX;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMeshDome[MAX_TEX];				//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshDome;			//���_�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshDome;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshDome;							//�ʒu
D3DXVECTOR3 g_rotMeshDome;							//����
D3DXMATRIX g_mtxWorldMeshDome;						//���[���h�}�g���b�N�X
MODE_TEX g_TexMode;  //�e�N�X�`���̏��

//====================================================================
//���b�V���h�[���̏���������
//====================================================================
void InitMeshDome(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rain_cloud2.jpeg",
		&g_pTextureMeshDome[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title_bg.jpg",
		&g_pTextureMeshDome[1]);

	g_posMeshDome = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshDome = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_TexMode = TEX_CLOUD; //�e�N�X�`���̏���������

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * HEIGHT_SIZE * WAIGHT_SIZE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshDome,
		NULL);

	VERTEX_3D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffMeshDome->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0, nData = 0, nCenterW = 0, nCenterH = 0, nHeight = 0; nCnt < HEIGHT_SIZE * WAIGHT_SIZE; nCnt++)
	{
		//���ԍ��̑��
		nCenterW = nCnt % WAIGHT_SIZE;

		if (nCnt % WAIGHT_SIZE == 0 && nCnt != 0)
		{
			nHeight++;
		}

		//���_���W�̐ݒ� 
		pVtx[nCnt].pos.x = g_posMeshDome.x + sinf(D3DX_PI * (1.0f / ((WAIGHT_SIZE - 1) / 2)) * (nCnt - nHeight)) * cosf(D3DX_PI * (1.0f / ((HEIGHT_SIZE - 1) * 2)) * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		//pVtx[nCnt].pos.y = CYLINDER_HEIGHT * ((HEIGHT_SIZE - 1) - nHeight);

		//pVtx[nCnt].pos.y = sinf(D3DX_PI * 0.0625f * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		pVtx[nCnt].pos.y = sinf(D3DX_PI * (1.0f / ((HEIGHT_SIZE - 1) * 2)) * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		pVtx[nCnt].pos.z = g_posMeshDome.z + cosf(D3DX_PI * (1.0f / ((WAIGHT_SIZE - 1) / 2)) * (nCnt - nHeight)) * cosf(D3DX_PI * (1.0f / ((HEIGHT_SIZE - 1) * 2)) * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		//�@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

		////�e�N�X�`�����W�̐ݒ�
		//if (nCenterW % 2 == 0)
		//{
		//	pVtx[nCnt].tex.x = 0.0f;
		//}
		//else
		//{
		//	pVtx[nCnt].tex.x = 1.0f;
		//}
		//if (nCenterH % 2 == 0)
		//{
		//	pVtx[nCnt].tex.y = 0.0f;
		//}
		//else
		//{
		//	pVtx[nCnt].tex.y = 1.0f;
		//}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex.x = 1.0f / (WAIGHT_SIZE - 1) * nCenterW;
		pVtx[nCnt].tex.y = 1.0f / (HEIGHT_SIZE - 1) * nCenterH;


		if ((nCnt - nCenterH) % (WAIGHT_SIZE - 1) == 0 && nCnt != 0 && nCnt != (WAIGHT_SIZE - 1) * nCenterH + nCenterH)
		{//�c�ԍ��̑��
			nCenterH++;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshDome->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshDome,
		NULL);

	WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^

				//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^������
	g_pIndxBuffMeshDome->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0, nOri = 0; nCnt < (WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)) / 2; nCnt++)
	{
		if ((nCnt - nOri) % WAIGHT_SIZE == 0 && nCnt != 0 && nCnt != WAIGHT_SIZE * nOri + nOri)
		{
			pIdx[nCnt * 2] = nCnt - 1 - nOri;			//����
			pIdx[nCnt * 2 + 1] = nCnt + WAIGHT_SIZE - nOri;		//�

			nOri++;
		}
		else
		{
			pIdx[nCnt * 2] = nCnt + WAIGHT_SIZE - nOri;	//����
			pIdx[nCnt * 2 + 1] = nCnt - nOri;		//�
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIndxBuffMeshDome->Unlock();
}

//====================================================================
//���b�V���h�[���̏I������
//====================================================================
void UninitMeshDome(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureMeshDome[nCnt] != NULL)
		{
			g_pTextureMeshDome[nCnt]->Release();
			g_pTextureMeshDome[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshDome != NULL)
	{
		g_pVtxBuffMeshDome->Release();
		g_pVtxBuffMeshDome = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIndxBuffMeshDome != NULL)
	{
		g_pIndxBuffMeshDome->Release();
		g_pIndxBuffMeshDome = NULL;
	}
}

//====================================================================
//���b�V���h�[���̍X�V����
//====================================================================
void UpdateMeshDome(void)
{

}

//====================================================================
//���b�V���h�[���̕`�揈��
//====================================================================
void DrawMeshDome(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshDome);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshDome.y, g_rotMeshDome.x, g_rotMeshDome.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshDome, &g_mtxWorldMeshDome, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshDome.x, g_posMeshDome.y, g_posMeshDome.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshDome, &g_mtxWorldMeshDome, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshDome);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshDome, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIndxBuffMeshDome);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	switch (g_TexMode)
	{
	case TEX_CLOUD:

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshDome[0]);

		break;

	case TEX_BLACK:

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshDome[1]);

		break;
	}
	
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		0,//�p�ӂ������_�̐�
		0,
		(WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)) - 2);//�`�悷��v���~�e�B�u�̐�
}

//==============================
//�e�N�X�`����ς��鏈��
//==============================
void ChangeMeshDome(void)
{
	g_TexMode = TEX_BLACK;
}