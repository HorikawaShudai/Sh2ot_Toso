#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "score_item.h"
#include "score.h"

#define OBJECT00_LIFE (7)		//�I�u�W�F�N�g�̗̑�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureItem[64][OBJECT_SCORE_MAX] = {};		//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshItem[OBJECT_SCORE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatItem[OBJECT_SCORE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatItem[OBJECT_SCORE_MAX] = {};						//�}�e���A���̐�

Object00 g_Item[MAX_OBJECT00];					//�I�u�W�F�N�g00�̏��

const char *c_apModeObj[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\jewelry.x",
};

//====================================================================
//�I�u�W�F�N�g00�̏���������
//====================================================================
void InitItem(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		g_Item[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Item[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Item[nCntObject].bUse = false;
		g_Item[nCntObject].nType = OBJECT_SCORE_ITEM;
		g_Item[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	}

	//X�t�@�C���̓ǂݍ���
	for (int nCntObj = 0; nCntObj < OBJECT_SCORE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModeObj[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatItem[nCntObj],
			NULL,
			&g_dwNumMatItem[nCntObj],
			&g_pMeshItem[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < OBJECT_SCORE_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatItem[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatItem[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureItem[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̏I������
//====================================================================
void UninitItem(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECT_SCORE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureItem[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureItem[nCntTex][nCntNumObject]->Release();
				g_pTextureItem[nCntTex][nCntNumObject] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_pMeshItem[nCntNumObject] != NULL)
		{
			g_pMeshItem[nCntNumObject]->Release();
			g_pMeshItem[nCntNumObject] = NULL;
		}
			//�}�e���A���̔j��
		if (g_pBuffMatItem[nCntNumObject] != NULL)
		{
			g_pBuffMatItem[nCntNumObject]->Release();
			g_pBuffMatItem[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateItem(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Item[nCntObject].bUse == true)
		{
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawItem(void)
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
		D3DXMatrixIdentity(&g_Item[nCntObject].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nCntObject].rot.y, g_Item[nCntObject].rot.x, g_Item[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_Item[nCntObject].mtxWorld, &g_Item[nCntObject].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Item[nCntObject].pos.x, g_Item[nCntObject].pos.y, g_Item[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_Item[nCntObject].mtxWorld, &g_Item[nCntObject].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCntObject].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^����������
		pMat = (D3DXMATERIAL*)g_pBuffMatItem[g_Item[nCntObject].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatItem[g_Item[nCntObject].nType]; nCntMat++)
		{

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_Item[nCntObject].bUse == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem[nCntMat][g_Item[nCntObject].nType]);

				//�I�u�W�F�N�g00(�p�[�c)�̕`��
				g_pMeshItem[g_Item[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateEditItem(void)
{
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawEditItem(void)
{
	
}

//====================================================================
//�I�u�W�F�N�g00�̐ݒ菈��
//====================================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Item[nCntObject].bUse == false)
		{
			g_Item[nCntObject].pos = pos;
			g_Item[nCntObject].posOld = pos;
			g_Item[nCntObject].move = move;
			g_Item[nCntObject].rot = rot;
			g_Item[nCntObject].nType = nType;

			g_Item[nCntObject].bUse = true;
		
			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

								//���_��������
			nNumVtx = g_pMeshItem[nType]->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y������
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshItem[nType]->GetFVF());

			//���_�o�b�t�@�����b�N
			g_pMeshItem[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				if (g_Item[nCntObject].vtxMin.x > vtx.x)
				{
					g_Item[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_Item[nCntObject].vtxMin.y > vtx.y)
				{
					g_Item[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_Item[nCntObject].vtxMin.z > vtx.z)
				{
					g_Item[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_Item[nCntObject].vtxMax.x < vtx.x)
				{
					g_Item[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_Item[nCntObject].vtxMax.y < vtx.y)
				{
					g_Item[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_Item[nCntObject].vtxMax.z < vtx.z)
				{
					g_Item[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pMeshItem[nType]->UnlockVertexBuffer();

			CollisionRotObject00(nCntObject);

			break;
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Item[nCntObject].bUse == true)
		{
			if (pPos->x >= g_Item[nCntObject].pos.x - 15
				&& pPos->x <= g_Item[nCntObject].pos.x + 15
				&& pPos->y >= g_Item[nCntObject].pos.y - 45
				&& pPos->y <= g_Item[nCntObject].pos.y + 45
				&& pPos->z >= g_Item[nCntObject].pos.z - 10
				&& pPos->z <= g_Item[nCntObject].pos.z + 10)
			{//�A�C�e���ƃv���C���[����������(X��)
				AddScore(g_Item[nCntObject].nType);
				g_Item[nCntObject].bUse = false;
				bHit = true;
			}
		}
	}

	return bHit;
}

//====================================================================
//�e�Ƃ̓����蔻�菈��
//====================================================================
void CollisionItemShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Item[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_Item[nCntObject].pos.y + g_Item[nCntObject].vtxMin.y &&
				pPos->y <= g_Item[nCntObject].pos.y + g_Item[nCntObject].vtxMax.y &&
				pPos->x >= g_Item[nCntObject].pos.x + g_Item[nCntObject].vtxMin.x &&
				pPos->x <= g_Item[nCntObject].pos.x + g_Item[nCntObject].vtxMax.x &&
				pPos->z >= g_Item[nCntObject].pos.z + g_Item[nCntObject].vtxMin.z &&
				pPos->z <= g_Item[nCntObject].pos.z + g_Item[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = g_Item[nCntObject].vtxMax.y;
			}
		}
	}
}
