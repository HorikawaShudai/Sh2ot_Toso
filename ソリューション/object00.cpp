#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"

#define OBJECT00_LIFE (7)		//�I�u�W�F�N�g�̗̑�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureObject00[64][OBJECT00_NTYPE_MAX] = {};	//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshObject00[OBJECT00_NTYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObject00[OBJECT00_NTYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatObject00[OBJECT00_NTYPE_MAX] = {};						//�}�e���A���̐�

Object00 g_Object00[MAX_OBJECT00];					//�I�u�W�F�N�g00�̏��

//====================================================================
//�I�u�W�F�N�g00�̏���������
//====================================================================
void InitObject00(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		g_Object00[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object00[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object00[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object00[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object00[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Object00[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Object00[nCntObject].bUse = false;
		g_Object00[nCntObject].nType = OBJECT00_NTYPE00;
	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\wall.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE00],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE00],
		&g_pMeshObject00[OBJECT00_NTYPE00]);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\pc.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE01],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE01],
		&g_pMeshObject00[OBJECT00_NTYPE01]);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\desk.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE02],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE02],
		&g_pMeshObject00[OBJECT00_NTYPE02]);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\fan.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE03],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE03],
		&g_pMeshObject00[OBJECT00_NTYPE03]);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\locker.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE04],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE04],
		&g_pMeshObject00[OBJECT00_NTYPE04]);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\whiteboard.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject00[OBJECT00_NTYPE05],
		NULL,
		&g_dwNumMatObject00[OBJECT00_NTYPE05],
		&g_pMeshObject00[OBJECT00_NTYPE05]);

	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < OBJECT00_NTYPE_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatObject00[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject00[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObject00[nCntMat][nCntNumObject]);
			}
		}
	}

	SetObject00(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE00);
	SetObject00(D3DXVECTOR3(-200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE01);
	SetObject00(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE02);
	SetObject00(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE03);
	SetObject00(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE04);
	SetObject00(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE05);
}

//====================================================================
//�I�u�W�F�N�g00�̏I������
//====================================================================
void UninitObject00(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECT00_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureObject00[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureObject00[nCntTex][nCntNumObject]->Release();
				g_pTextureObject00[nCntTex][nCntNumObject] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_pMeshObject00[nCntNumObject] != NULL)
		{
			g_pMeshObject00[nCntNumObject]->Release();
			g_pMeshObject00[nCntNumObject] = NULL;
		}

		//�}�e���A���̔j��
		if (g_pBuffMatObject00[nCntNumObject] != NULL)
		{
			g_pBuffMatObject00[nCntNumObject]->Release();
			g_pBuffMatObject00[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateObject00(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Object00[nCntObject].bUse == true)
		{

		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawObject00(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Object00[nCntObject].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object00[nCntObject].rot.y, g_Object00[nCntObject].rot.x, g_Object00[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_Object00[nCntObject].mtxWorld, &g_Object00[nCntObject].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Object00[nCntObject].pos.x, g_Object00[nCntObject].pos.y, g_Object00[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_Object00[nCntObject].mtxWorld, &g_Object00[nCntObject].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Object00[nCntObject].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^����������
			pMat = (D3DXMATERIAL*)g_pBuffMatObject00[g_Object00[nCntObject].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject00[g_Object00[nCntObject].nType]; nCntMat++)
			{

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Object00[nCntObject].bUse == true)
				{
					//switch (g_Object00[nCntObject].nType)
					//{
					//case OBJECT_NTYPE00:
						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, g_pTextureObject00[nCntMat][g_Object00[nCntObject].nType]);

						//�I�u�W�F�N�g00(�p�[�c)�̕`��
						g_pMeshObject00[g_Object00[nCntObject].nType]->DrawSubset(nCntMat);
					//	break;

					//case OBJECT_NTYPE01:
					//	//�e�N�X�`���̐ݒ�
					//	pDevice->SetTexture(0, g_pTextureObject00[nCntMat][OBJECT_NTYPE01]);

					//	//�I�u�W�F�N�g00(�p�[�c)�̕`��
					//	g_pMeshObject00[OBJECT_NTYPE01]->DrawSubset(nCntMat);
					//	break;
					//}
				}
			}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�I�u�W�F�N�g00�̐ݒ菈��
//====================================================================
void SetObject00(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, OBJECT00_NTYPE nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Object00[nCntObject].bUse == false)
		{
			g_Object00[nCntObject].pos = pos;
			g_Object00[nCntObject].posOld = pos;
			g_Object00[nCntObject].move = move;
			g_Object00[nCntObject].rot = rot;
			g_Object00[nCntObject].nType = nType;
			g_Object00[nCntObject].bUse = true;

			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

			//���_��������
			nNumVtx = g_pMeshObject00[nType]->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y������
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObject00[nType]->GetFVF());

			//���_�o�b�t�@�����b�N
			g_pMeshObject00[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				if (g_Object00[nCntObject].vtxMin.x > vtx.x)
				{
					g_Object00[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_Object00[nCntObject].vtxMin.y > vtx.y)
				{
					g_Object00[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_Object00[nCntObject].vtxMin.z > vtx.z)
				{
					g_Object00[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_Object00[nCntObject].vtxMax.x < vtx.x)
				{
					g_Object00[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_Object00[nCntObject].vtxMax.y < vtx.y)
				{
					g_Object00[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_Object00[nCntObject].vtxMax.z < vtx.z)
				{
					g_Object00[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pMeshObject00[nType]->UnlockVertexBuffer();

			break;
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool CollisionObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = true;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Object00[nCntObject].bUse == true)
		{
			if (
				(
				pPos->y + max.y >= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y && pPosOld->y + max.y< g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y ||
				pPos->y + min.y <= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y && pPosOld->y + min.y > g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y) &&
				pPos->x + Size >= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x &&
				pPos->z + Size >= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bON = false;
			}

			if (
				(
				pPos->z + Size >= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z && pPosOld->z + Size < g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z ||
				pPos->z - Size <= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z && pPosOld->z - Size > g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z) &&
				pPos->x + Size >= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x &&
				pPos->y + max.y >= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y&&
				pPos->y + min.y <= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y
				)
			{//�ǂƃv���C���[����������(Z��)
				pPos->z = pPosOld->z;
				pMove->z = 0.0f;
			}

			if (
				(
				pPos->x + Size >= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x && pPosOld->x + Size < g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x ||
				pPos->x - Size <= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x && pPosOld->x - Size > g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x) &&
				pPos->z + Size >= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z &&
				pPos->y + max.y >= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y &&
				pPos->y + min.y <= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->x = pPosOld->x;
				pMove->x = 0.0f;
			}
		}
	}
	return bON;
}

//====================================================================
//�e�Ƃ̓����蔻�菈��
//====================================================================
void CollisionObject00Shadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Object00[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y &&
				pPos->y <= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y &&
				pPos->x >= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x &&
				pPos->x <= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x &&
				pPos->z >= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z &&
				pPos->z <= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = g_Object00[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̏���
//====================================================================
Object00 * GetObject00(void)
{
	return &g_Object00[0];
}