#include "main.h"
#include "meshfield.h"

#define MAX_MESHFIELD (4)			//���b�V���t�B�[���h�̍ő吔
#define WAIGHT_SIZE (5)			//���̒��_��
#define HEIGHT_SIZE (5)			//�c�̒��_��
#define WAIGHT_CENTER (0.5f)	//���̌��_(0.0f�`1.0f)
#define HEIGHT_CENTER (0.5f)	//�c�̌��_(0.0f�`1.0f)
#define FIELD_SIZE (10.0f)		//���ꖇ�̑傫��
#define MESHFIELD_SIZE (50.0f)	//

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMeshField[MAX_MESHFIELD] = {};				//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField;		//���_�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshField;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshField g_MeshField[MAX_MESHFIELD];				//���b�V���t�B�[���h�̏��

//====================================================================
//���b�V���t�B�[���h�̏���������
//====================================================================
void InitMeshField(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number03.png",
		&g_pTextureMeshField[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number03.png",
		&g_pTextureMeshField[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number03.png",
		&g_pTextureMeshField[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number03.png",
		&g_pTextureMeshField[3]);

	for (int nCntField = 0; nCntField < MAX_MESHFIELD; nCntField++)
	{
		g_MeshField[0].pos = D3DXVECTOR3(-100.0f, 100.0f, 0.0f);
		g_MeshField[1].pos = D3DXVECTOR3(-50.0f, 100.0f, 0.0f);
		g_MeshField[2].pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		g_MeshField[3].pos = D3DXVECTOR3(50.0f, 100.0f, 0.0f);
		g_MeshField[nCntField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshField[nCntField].bUse = true;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * HEIGHT_SIZE * WAIGHT_SIZE * MAX_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	VERTEX_3D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0, nCenterW = 0, nCenterH = 0; nCnt < HEIGHT_SIZE * WAIGHT_SIZE * MAX_MESHFIELD; nCnt++)
	{
		nCenterW = nCnt % WAIGHT_SIZE;

		//���_���W�̐ݒ� 
		pVtx[nCnt].pos.x = FIELD_SIZE * (nCenterW - (((float)WAIGHT_SIZE - 1) * WAIGHT_CENTER));
		pVtx[nCnt].pos.y = 0.0f;
		pVtx[nCnt].pos.z = FIELD_SIZE * (HEIGHT_SIZE - 1) * HEIGHT_CENTER - FIELD_SIZE * nCenterH;

		//�@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
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
		{
			nCenterH++;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshField->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshField,
		NULL);

	WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^������
	g_pIndxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIndxBuffMeshField->Unlock();
}

//====================================================================
//���b�V���t�B�[���h�̏I������
//====================================================================
void UninitMeshField(void)
{
	for (int nCntField = 0; nCntField < MAX_MESHFIELD; nCntField++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureMeshField[nCntField] != NULL)
		{
			g_pTextureMeshField[nCntField]->Release();
			g_pTextureMeshField[nCntField] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIndxBuffMeshField != NULL)
	{
		g_pIndxBuffMeshField->Release();
		g_pIndxBuffMeshField = NULL;
	}
}

//====================================================================
//���b�V���t�B�[���h�̍X�V����
//====================================================================
void UpdateMeshField(void)
{

}

//====================================================================
//���b�V���t�B�[���h�̕`�揈��
//====================================================================
void DrawMeshField(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntField = 0; nCntField < MAX_MESHFIELD; nCntField++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_MeshField[nCntField].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshField[nCntField].rot.y, g_MeshField[nCntField].rot.x, g_MeshField[nCntField].rot.z);

		D3DXMatrixMultiply(&g_MeshField[nCntField].mtxWorld, &g_MeshField[nCntField].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_MeshField[nCntField].pos.x, g_MeshField[nCntField].pos.y, g_MeshField[nCntField].pos.z);

		D3DXMatrixMultiply(&g_MeshField[nCntField].mtxWorld, &g_MeshField[nCntField].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshField[nCntField].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIndxBuffMeshField);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshField[nCntField]);

		//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			4 * nCntField,//�p�ӂ������_�̐�
			0,
			(WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)) - 2);//�`�悷��v���~�e�B�u�̐�
	}
}