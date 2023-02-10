//========================================================================================
//
// �o���̏���[exit.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include <stdio.h>
#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "exit.h"
#include "PlayNumberSelect.h"
#include "PlayModeSelect.h"
#include "Fade.h"
#include "player.h"
#include "meshwall.h"

const char *c_apExit[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\Exit\\BigDoorFrame00.x",
	"Data\\MODEL\\Exit\\BigDoorFrame.x",
	"Data\\MODEL\\Exit\\BigDoor_L.x",
	"Data\\MODEL\\Exit\\BigDoor_R.x",
};

//�v���g�^�C�v�錾
void DoorOpen(void);
void ExsitClossLine(int nCntExit);

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExit[64][EXIT_TYPE_MAX] = {};		//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshExit[EXIT_TYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatExit[EXIT_TYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatExit[EXIT_TYPE_MAX] = {};						//�}�e���A���̐�

EXIT g_aExit[MAX_EXIT];					//�I�u�W�F�N�g00�̏��
int g_KeyCount;							//�K�v�ɂȂ錮�̃J�E���g
int g_ExitCnt;							//�E�o�\�ɂȂ�܂ł̃J�E���g

bool g_bExitFade[MAX_EXIT];
bool g_bExitOK;
bool bLoadExitObj;

D3DXVECTOR3 g_vecToPos;
D3DXVECTOR3 g_vecLine;
D3DXVECTOR3 g_vecNor;
D3DXVECTOR3 g_vecMoveRef;

//====================================================================
//�I�u�W�F�N�g00�̏���������
//====================================================================
void InitExit(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PlayModeSelect PlayMode = GetPlayModeSelect();

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			g_aExit[nCntExit].parts[nCntExit1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExit[nCntExit].parts[nCntExit1].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExit[nCntExit].parts[nCntExit1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExit[nCntExit].parts[nCntExit1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExit[nCntExit].parts[nCntExit1].rotSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExit[nCntExit].parts[nCntExit1].vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
			g_aExit[nCntExit].parts[nCntExit1].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
			g_aExit[nCntExit].parts[nCntExit1].bUse = false;
			g_aExit[nCntExit].parts[nCntExit1].bExitOK = false;
			g_aExit[nCntExit].parts[nCntExit1].nType = EXIT_TYPE_BIGFRAME;
		}
	}

	g_vecToPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecLine = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecNor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecMoveRef = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_KeyCount = 0;
	g_ExitCnt = 120;			//�o�����J���Ă���ʂ��悤�ɂȂ�܂ł̃J�E���g
	g_bExitOK = false;
	bLoadExitObj = false;

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

	//if (PlayMode.CurrentModeNumber == 0)
	//{
		SetExit(D3DXVECTOR3(-925.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 0);
		SetExit(D3DXVECTOR3(-1075.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 0);
		/*SetExit(D3DXVECTOR3(-935.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), EXIT_TYPE_BIGDOOR_R, 0);
		SetExit(D3DXVECTOR3(-1065.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), EXIT_TYPE_BIGDOOR_L, 0);*/
	//}
	//else
	//{
		//�o���̓ǂݍ���
		//LoadExit();
	//}
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
	//DoorOpen();
}

//====================================================================
//�I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawExit(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aExit[nCntExit].parts[nCntExit1].mtxWorld);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aExit[nCntExit].parts[nCntExit1].rot.y, g_aExit[nCntExit].parts[nCntExit1].rot.x, g_aExit[nCntExit].parts[nCntExit1].rot.z);

				D3DXMatrixMultiply(&g_aExit[nCntExit].parts[nCntExit1].mtxWorld, &g_aExit[nCntExit].parts[nCntExit1].mtxWorld, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aExit[nCntExit].parts[nCntExit1].pos.x, g_aExit[nCntExit].parts[nCntExit1].pos.y, g_aExit[nCntExit].parts[nCntExit1].pos.z);

				D3DXMatrixMultiply(&g_aExit[nCntExit].parts[nCntExit1].mtxWorld, &g_aExit[nCntExit].parts[nCntExit1].mtxWorld, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aExit[nCntExit].parts[nCntExit1].mtxWorld);

				//���݂̃}�e���A��������
				pDevice->GetMaterial(&matDef);

				//�}�e���A���f�[�^�ւ̃|�C���^����������
				pMat = (D3DXMATERIAL*)g_pBuffMatExit[g_aExit[nCntExit].parts[nCntExit1].nType]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_dwNumMatExit[g_aExit[nCntExit].parts[nCntExit1].nType]; nCntMat++)
				{

					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					if (g_aExit[nCntExit].parts[nCntExit1].bUse == true)
					{
						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, g_pTextureExit[nCntMat][g_aExit[nCntExit].parts[nCntExit1].nType]);

						//�I�u�W�F�N�g00(�p�[�c)�̕`��
						g_pMeshExit[g_aExit[nCntExit].parts[nCntExit1].nType]->DrawSubset(nCntMat);
					}
				}
				//�ۑ����Ă����}�e���A����߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//========================================
//�����J������
//========================================
void DoorOpen(void)
{
	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			/*if (g_aExit[nCntExit].bUse == true && g_aExit[nCntExit].bExitOK == true)
			{
			if (g_bExitFade[nCntExit] == false)
			{
			SetFade(MODE_RESULT);

			g_bExitFade[nCntExit] = true;
			}
			}*/

			//�O�ς̒E�o���菈��
			ExsitClossLine(nCntExit);

			//g_aExit[1].rot.y = /*g_aExit[1].rotSave.y + */(sinf(g_aExit[1].rotSave.y) + cosf(g_aExit[1].rotSave.y) - 0.5f);

			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true && g_aExit[nCntExit].parts[nCntExit1].bExitOK == true)
			{//�o�����g���Ă��ĒE�o�\�̏ꍇ
				for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
				{
					if (g_aExit[nCntExit].parts[nCntExit1].nType != EXIT_TYPE_BIGFRAME)
					{
						if (g_aExit[1].parts[nCntExit1].rot.y >= g_aExit[1].parts[nCntExit1].rotSave.y + (sinf(g_aExit[1].parts[nCntExit1].rotSave.y) + cosf(g_aExit[1].parts[nCntExit1].rotSave.y) - 0.5f))
						{
							g_aExit[1].parts[nCntExit1].rot.y += cosf(g_aExit[1].parts[nCntExit1].rot.y) * 0.003f;
							g_aExit[1].parts[nCntExit1].rot.y -= sinf(g_aExit[1].parts[nCntExit1].rot.y) * 0.003f;

							g_aExit[2].parts[nCntExit1].rot.y -= sinf(g_aExit[2].parts[nCntExit1].rot.y) * 0.003f;
							g_aExit[2].parts[nCntExit1].rot.y += -cosf(g_aExit[2].parts[nCntExit1].rot.y) * 0.003f;
						}
					}
				}
				g_ExitCnt--;

				if (g_ExitCnt <= 0)
				{
					g_ExitCnt = 0;
				}
			}

			if (g_aExit[nCntExit].parts[nCntExit1].rot.y > D3DX_PI)
			{
				g_aExit[nCntExit].parts[nCntExit1].rot.y = -D3DX_PI;
			}
			if (g_aExit[nCntExit].parts[nCntExit1].rot.y < -D3DX_PI)
			{
				g_aExit[nCntExit].parts[nCntExit1].rot.y = D3DX_PI;
			}
		}
	}
}

//================================
// �O�ς̓����蔻��
//================================
void ExsitClossLine(int nCntExit)
{
	//�ϐ��錾
	float vec;

	Player *pPlayer = GetPlayer();
	MeshWall MeshWall = GetMeshWall();

	for (int nCntWall = 0; nCntWall < MAX_EXIT; nCntWall++, pPlayer++)
	{
		if (pPlayer->bUse == true && MeshWall.bUse == true)
		{
			float fRate;					//�x�N�g���̊���
			float fMaxArea, fNowArea;		//���̖ʐρ^�ő�ʐ�
			D3DXVECTOR3 pos0, pos1;			//�ꏊ
			D3DXVECTOR3 Cross;				//��_�̏ꏊ

											//�ꏊ�̌v�Z
			pos0 = MeshWall.pos + D3DXVECTOR3(cosf(MeshWall.rot.y) + 50.0f, 0.0f, sinf(MeshWall.rot.y));

			pos1 = MeshWall.pos + D3DXVECTOR3(cosf(MeshWall.rot.y) - 50.0f, 0.0f, sinf(MeshWall.rot.y));

			//pos0��pos1�Ƃ̋�����
			g_vecLine = pos1 - pos0;

			//�o������v���C���[�܂ł̈ʒu
			g_vecToPos = pPlayer->pos - MeshWall.pos;

			//�ő�ʐ�
			fMaxArea = (g_vecLine.z * pPlayer->move.x) - (g_vecLine.x * MeshWall.move.z);

			//���̖ʐ�
			fNowArea = (g_vecToPos.z * pPlayer->move.x) - (g_vecToPos.x * MeshWall.move.z);

			//�x�N�g���̊���
			fRate = fNowArea / fMaxArea;

			//��_
			Cross = D3DXVECTOR3(pos0.x + g_vecLine.x * fRate, pPlayer->pos.y, pos0.z + g_vecLine.z * fRate);

			vec = (g_vecLine.z * g_vecToPos.x) - (g_vecLine.x * g_vecToPos.z);

			if (pPlayer->pos.x <= pos0.x && pPlayer->pos.x >= pos1.x)
			{
				if (vec < 0)
				{
					//�E�o��Ԃ�
					pPlayer->State = PLAYER_EXSIT;
					pPlayer->bExit = true;
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
//�o���̓ǂݍ���(.txt)
//====================================================================
void LoadExit(void)
{
	//�ϐ��錾
	char not[128];			//�g�p���Ȃ�������̃S�~��
	int number[10];		//�g�p����o���̔z��ԍ�
	FILE *pFile;			//�t�@�C���|�C���^��錾

							//�t�@�C�����J��
	pFile = fopen("Data\\TEXT\\Exit_akutou.txt", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		while (1)
		{
			fscanf(pFile, "%s", &not[0]);			//�������ǂݍ���

			if (strcmp("SCRIPT", &not[0]) == 0)
			{//SCRIPT���ǂݍ��߂���
				bLoadExitObj = true;			//�ǂݍ��݂��J�n
			}

			if (bLoadExitObj == true)
			{
				while (1)
				{
					fscanf(pFile, "%s", &not[0]);			//�������ǂݍ���

					if (strcmp("EXITSET", &not[0]) == 0)
					{
						fscanf(pFile, "%d", &number[0]);							//�z��ԍ���ǂݍ���
						fscanf(pFile, "%s", &not[0]);								//������ǂݍ���
						fscanf(pFile, "%s", &not[0]);								//=��ǂݍ���
						fscanf(pFile, "%f", &g_aExit[number[0]].parts[0].pos.x);
						fscanf(pFile, "%f", &g_aExit[number[0]].parts[0].pos.y);
						fscanf(pFile, "%f", &g_aExit[number[0]].parts[0].pos.z);

						fscanf(pFile, "%s", &not[0]);			//������ǂݍ���
						fscanf(pFile, "%s", &not[0]);			//=��ǂݍ���
						fscanf(pFile, "%f", &g_aExit[number[0]].parts[0].rot.x);
						fscanf(pFile, "%f", &g_aExit[number[0]].parts[0].rot.y);
						fscanf(pFile, "%f", &g_aExit[number[0]].parts[0].rot.z);

						fscanf(pFile, "%s", &not[0]);			//������ǂݍ���
						fscanf(pFile, "%s", &not[0]);			//=��ǂݍ���
						fscanf(pFile, "%d", &g_aExit[number[0]].parts[0].nType);

						//�o���̐ݒu
						SetExit(g_aExit[number[0]].parts[0].pos, g_aExit[number[0]].parts[0].rot, g_aExit[number[0]].parts[0].nType, number[0]);
					}

					if (strcmp("END_SCRIPT", &not[0]) == 0)
					{//SCRIPT���ǂݍ��߂Ȃ������ꍇ
						bLoadExitObj = false;			//�ǂݍ��݂��I��
						break;			//�����𔲂���
					}
				}
			}

			if (strcmp("END_SCRIPT", &not[0]) == 0)
			{//SCRIPT���ǂݍ��߂Ȃ������ꍇ
				bLoadExitObj = false;			//�ǂݍ��݂��I��
				break;			//�����𔲂���
			}
		}
	}
}

void SaveExit(void)
{

}

//====================================================================
//�I�u�W�F�N�g00�̐ݒ菈��
//====================================================================
void SetExit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nNumExit)
{
	for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
	{
		if (g_aExit[nNumExit].parts[nCntExit1].bUse == false)
		{
			g_aExit[nNumExit].parts[nCntExit1].pos = pos;
			g_aExit[nNumExit].parts[nCntExit1].posOld = pos;
			g_aExit[nNumExit].parts[nCntExit1].rot = rot;
			g_aExit[nNumExit].parts[nCntExit1].rotSave = rot;
			g_aExit[nNumExit].parts[nCntExit1].nType = nType;

			g_aExit[nNumExit].parts[nCntExit1].bUse = true;

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

				if (g_aExit[nNumExit].parts[nCntExit1].vtxMin.x > vtx.x)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMin.x = vtx.x;
				}
				if (g_aExit[nNumExit].parts[nCntExit1].vtxMin.y > vtx.y)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMin.y = vtx.y;
				}
				if (g_aExit[nNumExit].parts[nCntExit1].vtxMin.z > vtx.z)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMin.z = vtx.z;
				}

				if (g_aExit[nNumExit].parts[nCntExit1].vtxMax.x < vtx.x)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMax.x = vtx.x;
				}
				if (g_aExit[nNumExit].parts[nCntExit1].vtxMax.y < vtx.y)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMax.y = vtx.y;
				}
				if (g_aExit[nNumExit].parts[nCntExit1].vtxMax.z < vtx.z)
				{
					g_aExit[nNumExit].parts[nCntExit1].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}
			
			//���_�o�b�t�@���A�����b�N
			g_pMeshExit[nType]->UnlockVertexBuffer();

			CollisionRotObject00(nCntExit1);

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
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true && g_aExit[nCntExit].parts[nCntExit1].bExitOK == false)
			{
				if (pPos->x >= g_aExit[nCntExit].parts[nCntExit1].pos.x - Size
					&& pPos->x <= g_aExit[nCntExit].parts[nCntExit1].pos.x + Size
					&& pPos->y >= g_aExit[nCntExit].parts[nCntExit1].pos.y - Size
					&& pPos->y <= g_aExit[nCntExit].parts[nCntExit1].pos.y + Size
					&& pPos->z >= g_aExit[nCntExit].parts[nCntExit1].pos.z - Size
					&& pPos->z <= g_aExit[nCntExit].parts[nCntExit1].pos.z + Size)

				{//�A�C�e���ƃv���C���[����������(X��)
					bHit = true;
					g_KeyCount++;

					if (g_KeyCount > PlayNumber.CurrentSelectNumber - 1)
					{//�����v���C���[�l�����g��ꂽ�ꍇ
						g_bExitOK = true;

						g_aExit[1].parts[nCntExit1].bExitOK = true;
						g_aExit[2].parts[nCntExit1].bExitOK = true;
					}

					break;
				}
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

	for (int nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true && g_ExitCnt >= 1)
			{
				if (
					(
						pPos->y + max.y >= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMin.y && pPosOld->y + max.y< g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMin.y ||
						pPos->y + min.y <= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMax.y && pPosOld->y + min.y > g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMax.y) &&
					pPos->x + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMin.x &&
					pPos->x - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMax.x &&
					pPos->z + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMin.z &&
					pPos->z - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMax.z
					)
				{//�ǂƃv���C���[����������(X��)
					pPos->y = pPosOld->y;
					pMove->y = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->z + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMin.z && pPosOld->z + Size < g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMin.z ||
						pPos->z - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMax.z && pPosOld->z - Size > g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMax.z) &&
					pPos->x + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMin.x &&
					pPos->x - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMax.x &&
					pPos->y + max.y >= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMin.y&&
					pPos->y + min.y <= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMax.y
					)
				{//�ǂƃv���C���[����������(Z��)
					pPos->z = pPosOld->z;
					pMove->z = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->x + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMin.x && pPosOld->x + Size < g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMin.x ||
						pPos->x - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMax.x && pPosOld->x - Size > g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMax.x) &&
					pPos->z + Size >= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMin.z &&
					pPos->z - Size <= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMax.z &&
					pPos->y + max.y >= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMin.y &&
					pPos->y + min.y <= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMax.y
					)
				{//�ǂƃv���C���[����������(X��)
					pPos->x = pPosOld->x;
					pMove->x = 0.0f;
					bHit = true;
				}
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
		for (int nCntExit1 = 0; nCntExit1 < MAX_EXIT; nCntExit1++)
		{
			if (g_aExit[nCntExit].parts[nCntExit1].bUse == true)
			{
				if (
					pPos->y >= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMin.y &&
					pPos->y <= g_aExit[nCntExit].parts[nCntExit1].pos.y + g_aExit[nCntExit].parts[nCntExit1].vtxMax.y &&
					pPos->x >= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMin.x &&
					pPos->x <= g_aExit[nCntExit].parts[nCntExit1].pos.x + g_aExit[nCntExit].parts[nCntExit1].vtxMax.x &&
					pPos->z >= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMin.z &&
					pPos->z <= g_aExit[nCntExit].parts[nCntExit1].pos.z + g_aExit[nCntExit].parts[nCntExit1].vtxMax.z
					)
				{//�ǂƃv���C���[����������(X��)
					pPos->y = g_aExit[nCntExit].parts[nCntExit1].vtxMax.y;
				}
			}
		}
	}
}
