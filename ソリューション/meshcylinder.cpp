//========================================================================================
//
// ����̃|���S���̕`��[meshcylinder.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "main.h"
#include "meshcylinder.h"

#define WAIGHT_SIZE (9)			//���̒��_��(�Xor�P�Vor�R�R)
#define HEIGHT_SIZE (2)				//�c�̒��_��
#define WAIGHT_CENTER (0.5f)		//���̌��_(0.0f�`1.0f)
#define HEIGHT_CENTER (1.0f)		//�c�̌��_(0.0f�`1.0f)
#define CYLINDER_HEIGHT (800.0f)		//�ǈꖇ�̍���
#define CYLINDER_RADIUS (800.0f)	//�~�̔��a
#define MAX_TEXTURE (2)		//�e�N�X�`���̍ő吔

typedef enum
{
	TEX_CLOUD = 0,
	TEX_BLACK,
	TEX_MAX,
}TEX_MODE;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder[MAX_TEXTURE];				//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder;		//���_�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshCylinder;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshCylinder;							//�ʒu
D3DXVECTOR3 g_rotMeshCylinder;							//����
D3DXMATRIX g_mtxWorldMeshCylinder;						//���[���h�}�g���b�N�X
TEX_MODE g_Tex;  //�e�N�X�`���̏��

//====================================================================
//���b�V���V�����_�[�̏���������
//====================================================================
void InitMeshCylinder(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rain_cloud2.jpeg",
		&g_pTextureMeshCylinder[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title_bg.jpg",
		&g_pTextureMeshCylinder[1]);

	g_posMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 250.0f);
	g_rotMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Tex = TEX_CLOUD;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * HEIGHT_SIZE * WAIGHT_SIZE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	VERTEX_3D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0, nData = 0, nCenterW = 0, nCenterH = 0, nHeight = 0; nCnt < HEIGHT_SIZE * WAIGHT_SIZE; nCnt++)
	{
		//���ԍ��̑��
		nCenterW = nCnt % WAIGHT_SIZE;

		if (nCnt % WAIGHT_SIZE == 0 && nCnt != 0)
		{
			nHeight++;
		}

		pVtx[nCnt].pos.x = g_posMeshCylinder.x + sinf(D3DX_PI * (1.0f / ((WAIGHT_SIZE - 1) / 2)) * (nCnt - nHeight)) * CYLINDER_RADIUS;

		pVtx[nCnt].pos.y = CYLINDER_HEIGHT * ((HEIGHT_SIZE - 1) - nHeight);

		pVtx[nCnt].pos.z = g_posMeshCylinder.z + cosf(D3DX_PI * (1.0f / ((WAIGHT_SIZE - 1) / 2)) * (nCnt - nHeight)) * CYLINDER_RADIUS;

		//�@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

		//�e�N�X�`���̐ݒ�
		if (nCenterW % 2 == 0)
		{
			pVtx[nCnt].tex.x = 0.0f;
		}
		else
		{
			pVtx[nCnt].tex.x = 1.0f;
		}
		if (nCenterH % 2 == 0)
		{
			pVtx[nCnt].tex.y = 0.0f;
		}
		else
		{
			pVtx[nCnt].tex.y = 1.0f;
		}

		if ((nCnt - nCenterH) % (WAIGHT_SIZE - 1) == 0 && nCnt != 0 && nCnt != (WAIGHT_SIZE - 1) * nCenterH + nCenterH)
		{//�c�ԍ��̑��
			nCenterH++;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshCylinder->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshCylinder,
		NULL);

	WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^

				//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^������
	g_pIndxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIndxBuffMeshCylinder->Unlock();
}

//====================================================================
//���b�V���V�����_�[�̏I������
//====================================================================
void UninitMeshCylinder(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureMeshCylinder[nCnt] != NULL)
		{
			g_pTextureMeshCylinder[nCnt]->Release();
			g_pTextureMeshCylinder[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIndxBuffMeshCylinder != NULL)
	{
		g_pIndxBuffMeshCylinder->Release();
		g_pIndxBuffMeshCylinder = NULL;
	}
}

//====================================================================
//���b�V���V�����_�[�̍X�V����
//====================================================================
void UpdateMeshCylinder(void)
{

}

//====================================================================
//���b�V���V�����_�[�̕`�揈��
//====================================================================
void DrawMeshCylinder(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIndxBuffMeshCylinder);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	switch (g_Tex)
	{//�e�N�X�`�����[�h�ɂ���ĕς��鏈��
	case TEX_CLOUD:

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshCylinder[0]);

		break;

	case TEX_BLACK:

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshCylinder[1]);

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

//=============================================
//���b�V���V�����_�[�̃e�N�X�`����ς��鏈��
//=============================================
void ChangeMeshCylinder(void)
{
	g_Tex = TEX_BLACK;
}
