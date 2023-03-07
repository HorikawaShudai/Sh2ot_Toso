//========================================================================================
//
// ���̏���[Key.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "key.h"
#include "ActionHelpUI.h"
#include "particle.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureKey[64][KEY_TYPE_MAX] = {};		//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshKey[KEY_TYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatKey[KEY_TYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatKey[KEY_TYPE_MAX] = {};						//�}�e���A���̐�

KEY g_Key[MAX_KEY];					//���̏��

const char *c_apKey[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\Cardkey.x",
};

//====================================================================
//���̏���������
//====================================================================
void InitKey(void)
{
	int nCntKey;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		g_Key[nCntKey].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Key[nCntKey].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Key[nCntKey].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Key[nCntKey].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Key[nCntKey].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Key[nCntKey].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Key[nCntKey].bUse = false;
		g_Key[nCntKey].nType = KEY_TYPE_ITEM;
		g_Key[nCntKey].bHelpUI = false;
		g_Key[nCntKey].IndexUI = -1;
		g_Key[nCntKey].nCntMove = 0;
	}

	//X�t�@�C���̓ǂݍ���
	for (int nCntObj = 0; nCntObj < KEY_TYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apKey[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatKey[nCntObj],
			NULL,
			&g_dwNumMatKey[nCntObj],
			&g_pMeshKey[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < KEY_TYPE_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatKey[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatKey[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureKey[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//���̏I������
//====================================================================
void UninitKey(void)
{
	for (int nCntNumObject = 0; nCntNumObject < KEY_TYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureKey[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureKey[nCntTex][nCntNumObject]->Release();
				g_pTextureKey[nCntTex][nCntNumObject] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_pMeshKey[nCntNumObject] != NULL)
		{
			g_pMeshKey[nCntNumObject]->Release();
			g_pMeshKey[nCntNumObject] = NULL;
		}
		//�}�e���A���̔j��
		if (g_pBuffMatKey[nCntNumObject] != NULL)
		{
			g_pBuffMatKey[nCntNumObject]->Release();
			g_pBuffMatKey[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//���̍X�V����
//====================================================================
void UpdateKey(void)
{
	for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{
#ifdef _DEBUG
			PrintDebugProc("��%d�̍��W�yX : %f | Y : %f | Z : %f�z\n", nCntKey + 1, g_Key[nCntKey].pos.x, g_Key[nCntKey].pos.y, g_Key[nCntKey].pos.z);
#endif // _DEBUG

			g_Key[nCntKey].pos += g_Key[nCntKey].move;
			g_Key[nCntKey].nCntMove++;
			if (g_Key[nCntKey].nCntMove % 60 == 0)
			{
				g_Key[nCntKey].move *= -1.0;
			}

			//���̃p�[�e�B�N������
			SetParticle(D3DXVECTOR3(g_Key[nCntKey].pos.x, g_Key[nCntKey].pos.y, g_Key[nCntKey].pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.3f, 0.0f, 0.6f, 0.5f),
				D3DXVECTOR3(D3DX_PI * 0.0f, 0.0f, 0.0f),
				1.0f,
				10.0f,
				20,
				PARTICLE_TYPE_KEY,
				1,
				120,
				1,
				2);

		}
	}
}

//====================================================================
//���̕`�揈��
//====================================================================
void DrawKey(void)
{
	int nCntKey;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Key[nCntKey].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Key[nCntKey].rot.y, g_Key[nCntKey].rot.x, g_Key[nCntKey].rot.z);

		D3DXMatrixMultiply(&g_Key[nCntKey].mtxWorld, &g_Key[nCntKey].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Key[nCntKey].pos.x, g_Key[nCntKey].pos.y, g_Key[nCntKey].pos.z);

		D3DXMatrixMultiply(&g_Key[nCntKey].mtxWorld, &g_Key[nCntKey].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Key[nCntKey].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^����������
		pMat = (D3DXMATERIAL*)g_pBuffMatKey[g_Key[nCntKey].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatKey[g_Key[nCntKey].nType]; nCntMat++)
		{

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_Key[nCntKey].bUse == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureKey[nCntMat][g_Key[nCntKey].nType]);

				//��(�p�[�c)�̕`��
				g_pMeshKey[g_Key[nCntKey].nType]->DrawSubset(nCntMat);
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̌��̍X�V����
//====================================================================
void UpdateEditKey(void)
{

}

//====================================================================
//�G�f�B�b�g���[�h�̌��̕`�揈��
//====================================================================
void DrawEditKey(void)
{

}

//====================================================================
//���̐ݒ菈��
//====================================================================
void SetKey(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntKey;

	for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == false)
		{
			g_Key[nCntKey].pos = pos;
			g_Key[nCntKey].posOld = pos;
			g_Key[nCntKey].move = move;
			g_Key[nCntKey].rot = rot;
			g_Key[nCntKey].nType = nType;
			g_Key[nCntKey].IndexUI = SetActionHelpUI(D3DXVECTOR3(g_Key[nCntKey].pos.x, g_Key[nCntKey].pos.y + 5.0f, g_Key[nCntKey].pos.z), 2.5f, ACTIONHELPUI_KEY);
			g_Key[nCntKey].bUse = true;

			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

								//���_��������
			nNumVtx = g_pMeshKey[nType]->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y������
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshKey[nType]->GetFVF());

			//���_�o�b�t�@�����b�N
			g_pMeshKey[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				if (g_Key[nCntKey].vtxMin.x > vtx.x)
				{
					g_Key[nCntKey].vtxMin.x = vtx.x;
				}
				if (g_Key[nCntKey].vtxMin.y > vtx.y)
				{
					g_Key[nCntKey].vtxMin.y = vtx.y;
				}
				if (g_Key[nCntKey].vtxMin.z > vtx.z)
				{
					g_Key[nCntKey].vtxMin.z = vtx.z;
				}

				if (g_Key[nCntKey].vtxMax.x < vtx.x)
				{
					g_Key[nCntKey].vtxMax.x = vtx.x;
				}
				if (g_Key[nCntKey].vtxMax.y < vtx.y)
				{
					g_Key[nCntKey].vtxMax.y = vtx.y;
				}
				if (g_Key[nCntKey].vtxMax.z < vtx.z)
				{
					g_Key[nCntKey].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pMeshKey[nType]->UnlockVertexBuffer();

			CollisionRotObject00(nCntKey);

			break;
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool CollisionKey(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size, int nPlayer)
{
	bool bHit = false;

	for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{
			if (pPos->x >= g_Key[nCntKey].pos.x - Size
				&& pPos->x <= g_Key[nCntKey].pos.x + Size
				&& pPos->y >= g_Key[nCntKey].pos.y - Size
				&& pPos->y <= g_Key[nCntKey].pos.y + Size
				&& pPos->z >= g_Key[nCntKey].pos.z - Size
				&& pPos->z <= g_Key[nCntKey].pos.z + Size)
			{//�A�C�e���ƃv���C���[����������(X��)
				g_Key[nCntKey].bUse = false;
				FalseActionHelpUI(g_Key[nCntKey].IndexUI);
				bHit = true;
				break;
			}
		}
	}

	return bHit;
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool CollisionKeyHelpUI(D3DXVECTOR3 *pPos, float Size)
{
	bool UI = false;

	for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{
			if (pPos->x >= g_Key[nCntKey].pos.x - Size
				&& pPos->x <= g_Key[nCntKey].pos.x + Size
				&& pPos->y >= g_Key[nCntKey].pos.y - Size
				&& pPos->y <= g_Key[nCntKey].pos.y + Size
				&& pPos->z >= g_Key[nCntKey].pos.z - Size
				&& pPos->z <= g_Key[nCntKey].pos.z + Size)
			{//�A�C�e���ƃv���C���[����������(X��)
				g_Key[nCntKey].bHelpUI = true;
				UI = true;
				break;
			}
		}
		//else if (g_Key[nCntKey].bUse == true && g_Key[nCntKey].bHelpUI == true)
		//{
		//	if (pPos->x <= g_Key[nCntKey].pos.x - Size
		//		|| pPos->x >= g_Key[nCntKey].pos.x + Size
		//		|| pPos->y <= g_Key[nCntKey].pos.y - Size
		//		|| pPos->y >= g_Key[nCntKey].pos.y + Size
		//		|| pPos->z <= g_Key[nCntKey].pos.z - Size
		//		|| pPos->z >= g_Key[nCntKey].pos.z + Size)
		//	{//�A�C�e���ƃv���C���[����������(X��)
		//		g_Key[nCntKey].bHelpUI = false;
		//		UI = false;
		//	}
		//}
		else
		{
			g_Key[nCntKey].bHelpUI = false;
			UI = false;
		}
	}

	return UI;
}

//====================================================================
//�e�Ƃ̓����蔻�菈��
//====================================================================
void CollisionKeyShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{
			if (
				pPos->y >= g_Key[nCntKey].pos.y + g_Key[nCntKey].vtxMin.y &&
				pPos->y <= g_Key[nCntKey].pos.y + g_Key[nCntKey].vtxMax.y &&
				pPos->x >= g_Key[nCntKey].pos.x + g_Key[nCntKey].vtxMin.x &&
				pPos->x <= g_Key[nCntKey].pos.x + g_Key[nCntKey].vtxMax.x &&
				pPos->z >= g_Key[nCntKey].pos.z + g_Key[nCntKey].vtxMin.z &&
				pPos->z <= g_Key[nCntKey].pos.z + g_Key[nCntKey].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = g_Key[nCntKey].vtxMax.y;
			}
		}
	}
}

//====================================================================
//�������_���ݒu����
//====================================================================
void PatternSetKey(int nNumPlayer)
{
	int bnNum;
	switch (nNumPlayer)
	{
	case 1:
		bnNum = rand() % 12;
		SetKey(KeyPos[bnNum], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		break;
	case 2:
		bnNum = rand() % 5;
		SetKey(KeyPos[bnNum], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		SetKey(KeyPos[bnNum + 5], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		break;
	case 3:
		bnNum = rand() % 4;
		SetKey(KeyPos[bnNum], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		bnNum = rand() % 4;
		SetKey(KeyPos[bnNum + 4], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		bnNum = rand() % 4;
		SetKey(KeyPos[bnNum + 8], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		break;
	case 4:
		bnNum = rand() % 2;
		SetKey(KeyPos[bnNum], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		bnNum = rand() % 2;
		SetKey(KeyPos[bnNum + 2], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		bnNum = rand() % 4;
		SetKey(KeyPos[bnNum + 4], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		bnNum = rand() % 4;
		SetKey(KeyPos[bnNum + 8], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		break;
	}
}
