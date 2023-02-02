//========================================================================================
//
// �o���̏���[exit.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "exit.h"
#include "PlayNumberSelect.h"
#include "Fade.h"

const char *c_apExit[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\Exit\\BigDoorFrame.x",
	"Data\\MODEL\\Exit\\BigDoor_L.x",
	"Data\\MODEL\\Exit\\BigDoor_R.x",
};

//�v���g�^�C�v�錾
void DoorOpen(void);

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExit[64][EXIT_TYPE_MAX] = {};		//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshExit[EXIT_TYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatExit[EXIT_TYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatExit[EXIT_TYPE_MAX] = {};						//�}�e���A���̐�

EXIT g_Exit[MAX_EXIT];					//�I�u�W�F�N�g00�̏��
int g_KeyCount;							//�K�v�ɂȂ錮�̃J�E���g
bool g_bExitFade[MAX_EXIT];

//====================================================================
//�I�u�W�F�N�g00�̏���������
//====================================================================
void InitExit(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		g_Exit[nCntExit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Exit[nCntExit].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Exit[nCntExit].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Exit[nCntExit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Exit[nCntExit].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Exit[nCntExit].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Exit[nCntExit].bUse = false;
		g_Exit[nCntExit].bExitOK = false;
		g_Exit[nCntExit].nType = EXIT_TYPE_BIGFRAME;

	/*	g_bExitFade[nCntExit]. = false;*/
	}

	g_KeyCount = 0;

	//X�t�@�C���̓ǂݍ���
	for (int nCntObj = 0; nCntObj < EXIT_TYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apExit[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatExit[nCntObj],
			NULL,
			&g_dwNumMatExit[nCntObj],
			&g_pMeshExit[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < EXIT_TYPE_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatExit[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatExit[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureExit[nCntMat][nCntNumObject]);
			}
		}
	}

	
	SetExit(D3DXVECTOR3(-1000.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXIT_TYPE_BIGFRAME);
	SetExit(D3DXVECTOR3(-930.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), EXIT_TYPE_BIGDOOR_R);
	SetExit(D3DXVECTOR3(-1070.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), EXIT_TYPE_BIGDOOR_L);
	
}

//====================================================================
//�I�u�W�F�N�g00�̏I������
//====================================================================
void UninitExit(void)
{
	for (int nCntNumObject = 0; nCntNumObject < EXIT_TYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureExit[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureExit[nCntTex][nCntNumObject]->Release();
				g_pTextureExit[nCntTex][nCntNumObject] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_pMeshExit[nCntNumObject] != NULL)
		{
			g_pMeshExit[nCntNumObject]->Release();
			g_pMeshExit[nCntNumObject] = NULL;
		}
		//�}�e���A���̔j��
		if (g_pBuffMatExit[nCntNumObject] != NULL)
		{
			g_pBuffMatExit[nCntNumObject]->Release();
			g_pBuffMatExit[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateExit(void)
{
	//�����J������
	DoorOpen();
}

//====================================================================
//�I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawExit(void)
{
	int nCntExit;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_Exit[nCntExit].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Exit[nCntExit].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Exit[nCntExit].rot.y, g_Exit[nCntExit].rot.x, g_Exit[nCntExit].rot.z);

			D3DXMatrixMultiply(&g_Exit[nCntExit].mtxWorld, &g_Exit[nCntExit].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Exit[nCntExit].pos.x, g_Exit[nCntExit].pos.y, g_Exit[nCntExit].pos.z);

			D3DXMatrixMultiply(&g_Exit[nCntExit].mtxWorld, &g_Exit[nCntExit].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Exit[nCntExit].mtxWorld);

			//���݂̃}�e���A��������
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^����������
			pMat = (D3DXMATERIAL*)g_pBuffMatExit[g_Exit[nCntExit].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatExit[g_Exit[nCntExit].nType]; nCntMat++)
			{

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Exit[nCntExit].bUse == true)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureExit[nCntMat][g_Exit[nCntExit].nType]);

					//�I�u�W�F�N�g00(�p�[�c)�̕`��
					g_pMeshExit[g_Exit[nCntExit].nType]->DrawSubset(nCntMat);
				}
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

void DoorOpen(void)
{
	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		/*if (g_Exit[nCntExit].bUse == true && g_Exit[nCntExit].bExitOK == true)
		{
		if (g_bExitFade[nCntExit] == false)
		{
		SetFade(MODE_RESULT);

		g_bExitFade[nCntExit] = true;
		}
		}*/

		if (g_Exit[nCntExit].bUse == true && g_Exit[nCntExit].bExitOK == true)
		{
			for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
			{
				if (g_Exit[nCntExit].nType == 1 && g_Exit[nCntExit].rot.y >= 1.5f)
				{
					g_Exit[1].rot.y -= 0.01f;

					g_Exit[2].rot.y += 0.01f;
				}
			}
		}
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateEditExit(void)
{
	
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawEditExit(void)
{

}

//====================================================================
//�I�u�W�F�N�g00�̐ݒ菈��
//====================================================================
void SetExit(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntExit;

	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_Exit[nCntExit].bUse == false)
		{
			g_Exit[nCntExit].pos = pos;
			g_Exit[nCntExit].posOld = pos;
			g_Exit[nCntExit].move = move;
			g_Exit[nCntExit].rot = rot;
			g_Exit[nCntExit].nType = nType;

			g_Exit[nCntExit].bUse = true;

			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

			//���_��������
			nNumVtx = g_pMeshExit[nType]->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y������
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshExit[nType]->GetFVF());

			//���_�o�b�t�@�����b�N
			g_pMeshExit[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				if (g_Exit[nCntExit].vtxMin.x > vtx.x)
				{
					g_Exit[nCntExit].vtxMin.x = vtx.x;
				}
				if (g_Exit[nCntExit].vtxMin.y > vtx.y)
				{
					g_Exit[nCntExit].vtxMin.y = vtx.y;
				}
				if (g_Exit[nCntExit].vtxMin.z > vtx.z)
				{
					g_Exit[nCntExit].vtxMin.z = vtx.z;
				}

				if (g_Exit[nCntExit].vtxMax.x < vtx.x)
				{
					g_Exit[nCntExit].vtxMax.x = vtx.x;
				}
				if (g_Exit[nCntExit].vtxMax.y < vtx.y)
				{
					g_Exit[nCntExit].vtxMax.y = vtx.y;
				}
				if (g_Exit[nCntExit].vtxMax.z < vtx.z)
				{
					g_Exit[nCntExit].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pMeshExit[nType]->UnlockVertexBuffer();

			CollisionRotObject00(nCntExit);

			break;
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool CollisionExit(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer)
{
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	bool bHit = false;

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_Exit[nCntExit].bUse == true && g_Exit[nCntExit].bExitOK == false)
		{
			if (pPos->x >= g_Exit[nCntExit].pos.x - Size
				&& pPos->x <= g_Exit[nCntExit].pos.x + Size
				&& pPos->y >= g_Exit[nCntExit].pos.y - Size
				&& pPos->y <= g_Exit[nCntExit].pos.y + Size
				&& pPos->z >= g_Exit[nCntExit].pos.z - Size
				&& pPos->z <= g_Exit[nCntExit].pos.z + Size)

			{//�A�C�e���ƃv���C���[����������(X��)
				bHit = true;
				g_KeyCount++;

				if (g_KeyCount > PlayNumber.CurrentSelectNumber - 1)
				{//�����v���C���[�l�����g��ꂽ�ꍇ
					g_Exit[nCntExit].bExitOK = true;
				}

				break;
			}
		}
	}

	return bHit;
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool CollisionExi(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

	for (int nCntExit = 0; nCntExit < MAX_OBJECT00; nCntExit++)
	{
		if (g_Exit[nCntExit].bUse == true && g_Exit[nCntExit].bExitOK == false)
		{
			if (
				(
					pPos->y + max.y >= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMin.y && pPosOld->y + max.y< g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMin.y ||
					pPos->y + min.y <= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMax.y && pPosOld->y + min.y > g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMax.y) &&
				pPos->x + Size >= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMin.x &&
				pPos->x - Size <= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMax.x &&
				pPos->z + Size >= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMin.z &&
				pPos->z - Size <= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bHit = true;
			}

			if (
				(
					pPos->z + Size >= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMin.z && pPosOld->z + Size < g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMin.z ||
					pPos->z - Size <= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMax.z && pPosOld->z - Size > g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMax.z) &&
				pPos->x + Size >= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMin.x &&
				pPos->x - Size <= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMax.x &&
				pPos->y + max.y >= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMin.y&&
				pPos->y + min.y <= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMax.y
				)
			{//�ǂƃv���C���[����������(Z��)
				pPos->z = pPosOld->z;
				pMove->z = 0.0f;
				bHit = true;
			}

			if (
				(
					pPos->x + Size >= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMin.x && pPosOld->x + Size < g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMin.x ||
					pPos->x - Size <= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMax.x && pPosOld->x - Size > g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMax.x) &&
				pPos->z + Size >= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMin.z &&
				pPos->z - Size <= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMax.z &&
				pPos->y + max.y >= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMin.y &&
				pPos->y + min.y <= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMax.y
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->x = pPosOld->x;
				pMove->x = 0.0f;
				bHit = true;
			}
		}
	}
	return bHit;
}

//====================================================================
//�e�Ƃ̓����蔻�菈��
//====================================================================
void CollisionExitShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_Exit[nCntExit].bUse == true)
		{
			if (
				pPos->y >= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMin.y &&
				pPos->y <= g_Exit[nCntExit].pos.y + g_Exit[nCntExit].vtxMax.y &&
				pPos->x >= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMin.x &&
				pPos->x <= g_Exit[nCntExit].pos.x + g_Exit[nCntExit].vtxMax.x &&
				pPos->z >= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMin.z &&
				pPos->z <= g_Exit[nCntExit].pos.z + g_Exit[nCntExit].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = g_Exit[nCntExit].vtxMax.y;
			}
		}
	}
}
