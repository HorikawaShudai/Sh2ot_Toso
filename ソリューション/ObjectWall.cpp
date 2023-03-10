//========================================================================================
//
// �I�u�W�F�N�g�̏���[ObjectWall.cpp]
// Author: ��{�@�ėB
// Author: �O�엳�V��
//
//========================================================================================
#include "main.h"
#include "ObjectWall.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "score.h"

#define OBJECTWALL_LIFE (7)		//�I�u�W�F�N�g�̗̑�
#define FALSE_SIZE (10.0f)		//�G�f�B�b�g���[�h�̃o�b�N�X�y�[�X�̔���̑傫��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureObjectWall[64][OBJECTWALL_NTYPE_MAX] = {};		//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshObjectWall[OBJECTWALL_NTYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObjectWall[OBJECTWALL_NTYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatObjectWall[OBJECTWALL_NTYPE_MAX] = {};						//�}�e���A���̐�

ObjectWall g_ObjectWall[MAX_OBJECTWALL];				//�I�u�W�F�N�g00�̏��
int EditIndex03;									//�G�f�B�b�g���[�h�p�̔ԍ�
D3DXVECTOR3 EditPos03;							//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
D3DXVECTOR3 EditRot03;							//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̌���
int EditType03;									//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̎��
int g_ObjectWallCount;								//�I�u�W�F�N�g�̐�

const char *c_apModelWallObj[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\tyuPolyWall.x",				//�|���S�����̑�����
	"Data\\MODEL\\tyuPolyWall1.x",				//��(���C���z�[��)
	"Data\\MODEL\\tyuPolyWall2.x",				//��(�m�[�}���R���N��)
	"Data\\MODEL\\tyuPolyWall3.x",				//��(�J�G��R���N��)
	"Data\\MODEL\\tyuPolyWall4.x",				//��(���^�C��)
};

//====================================================================
//�I�u�W�F�N�g00�̏���������
//====================================================================
void InitObjectWall(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		g_ObjectWall[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectWall[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectWall[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectWall[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectWall[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_ObjectWall[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_ObjectWall[nCntObject].bUse = false;
		g_ObjectWall[nCntObject].nType = OBJECTWALL_NTYPE00;
		g_ObjectWall[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	}
	EditIndex03 = MAX_OBJECTWALL - 1;
	EditPos03 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditRot03 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditType03 = 0;
	g_ObjectWallCount = 0;

	//X�t�@�C���̓ǂݍ���
	for (int nCntObj = 0; nCntObj < OBJECTWALL_NTYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModelWallObj[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObjectWall[nCntObj],
			NULL,
			&g_dwNumMatObjectWall[nCntObj],
			&g_pMeshObjectWall[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < OBJECTWALL_NTYPE_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectWall[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectWall[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObjectWall[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̏I������
//====================================================================
void UninitObjectWall(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECTWALL_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureObjectWall[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureObjectWall[nCntTex][nCntNumObject]->Release();
				g_pTextureObjectWall[nCntTex][nCntNumObject] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_pMeshObjectWall[nCntNumObject] != NULL)
		{
			g_pMeshObjectWall[nCntNumObject]->Release();
			g_pMeshObjectWall[nCntNumObject] = NULL;
		}

		//�}�e���A���̔j��
		if (g_pBuffMatObjectWall[nCntNumObject] != NULL)
		{
			g_pBuffMatObjectWall[nCntNumObject]->Release();
			g_pBuffMatObjectWall[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateObjectWall(void)
{
#ifdef _DEBUG
	PrintDebugProc("�ǃI�u�W�F�N�g�̐�:%d\n", g_ObjectWallCount);
#endif // _DEBUG
}

//====================================================================
//�I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawObjectWall(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_ObjectWall[nCntObject].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectWall[nCntObject].rot.y, g_ObjectWall[nCntObject].rot.x, g_ObjectWall[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_ObjectWall[nCntObject].mtxWorld, &g_ObjectWall[nCntObject].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_ObjectWall[nCntObject].pos.x, g_ObjectWall[nCntObject].pos.y, g_ObjectWall[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_ObjectWall[nCntObject].mtxWorld, &g_ObjectWall[nCntObject].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_ObjectWall[nCntObject].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^����������
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectWall[g_ObjectWall[nCntObject].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectWall[g_ObjectWall[nCntObject].nType]; nCntMat++)
		{

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_ObjectWall[nCntObject].bUse == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureObjectWall[nCntMat][g_ObjectWall[nCntObject].nType]);

				//�I�u�W�F�N�g00(�p�[�c)�̕`��
				g_pMeshObjectWall[g_ObjectWall[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateEditObjectWall(void)
{
	//�L�[�{�[�h�̈ړ�����----------
		if (GetKeyboardTrigger(DIK_UP) == true)
		{//�O�ړ�
			EditPos03.z += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{//���ړ�
			EditPos03.z -= 100.0f;
		}
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{//�E�ړ�
			EditPos03.x += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{//���ړ�
			EditPos03.x -= 100.0f;
		}

	//�I�u�W�F�N�g�̉�]����
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		EditRot03.y += 1.57f;

		if (EditRot03.y >= 6.28f)
		{
			EditRot03.y = 0.0f;
		}
	}

	//�I�u�W�F�N�g�̐؂�ւ�����----------
	if (GetKeyboardTrigger(DIK_9) == true)
	{//�X�L�[�Ŏ��̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditType03++;

		if (EditType03 > OBJECTWALL_NTYPE_MAX - 1)
		{
			EditType03 = 0;
		}

	}
	if (GetKeyboardTrigger(DIK_8) == true)
	{//�W�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditType03--;

		if (EditType03 < 0)
		{
			EditType03 = OBJECTWALL_NTYPE_MAX - 1;
		}
	}

	//�G�f�B�b�g���[�h�̕ύX���I�u�W�F�N�g�ɔ��f������
	g_ObjectWall[EditIndex03].pos = EditPos03;
	g_ObjectWall[EditIndex03].rot = EditRot03;
	g_ObjectWall[EditIndex03].nType = EditType03;

	//�I�u�W�F�N�g�̍폜����(�d�Ȃ��Ă������)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObjectWall(D3DXVECTOR3(EditPos03.x, EditPos03.y + 0.0f, EditPos03.z), g_ObjectWall[EditIndex03].vtxMin, g_ObjectWall[EditIndex03].vtxMax, FALSE_SIZE);
	}

	//�I�u�W�F�N�g�̍폜����(CTRL+Z)----------
	if (GetKeyboardTrigger(DIK_Z) == true && GetKeyboardPress(DIK_LCONTROL) == true)
	{
		FalseObjectWall();
	}

	//�I�u�W�F�N�g�̐ݒu����----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObjectWall(g_ObjectWall[EditIndex03].pos, g_ObjectWall[EditIndex03].move, g_ObjectWall[EditIndex03].rot, g_ObjectWall[EditIndex03].nType);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawEditObjectWall(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^


	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_ObjectWall[EditIndex03].mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectWall[EditIndex03].rot.y, g_ObjectWall[EditIndex03].rot.x, g_ObjectWall[EditIndex03].rot.z);

	D3DXMatrixMultiply(&g_ObjectWall[EditIndex03].mtxWorld, &g_ObjectWall[EditIndex03].mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_ObjectWall[EditIndex03].pos.x, g_ObjectWall[EditIndex03].pos.y, g_ObjectWall[EditIndex03].pos.z);

	D3DXMatrixMultiply(&g_ObjectWall[EditIndex03].mtxWorld, &g_ObjectWall[EditIndex03].mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_ObjectWall[EditIndex03].mtxWorld);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^����������
	pMat = (D3DXMATERIAL*)g_pBuffMatObjectWall[g_ObjectWall[EditIndex03].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectWall[g_ObjectWall[EditIndex03].nType]; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&g_ObjectWall[EditIndex03].pMatE.MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureObjectWall[nCntMat][g_ObjectWall[EditIndex03].nType]);

		//�I�u�W�F�N�g00(�p�[�c)�̕`��
		g_pMeshObjectWall[g_ObjectWall[EditIndex03].nType]->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//�I�u�W�F�N�g00�̐ݒ菈��
//====================================================================
void SetObjectWall(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		if (g_ObjectWall[nCntObject].bUse == false)
		{
			g_ObjectWall[nCntObject].pos = pos;
			g_ObjectWall[nCntObject].posOld = pos;
			g_ObjectWall[nCntObject].move = move;
			g_ObjectWall[nCntObject].rot = rot;
			g_ObjectWall[nCntObject].nType = nType;

			g_ObjectWall[nCntObject].bUse = true;
			g_ObjectWallCount++;

			//if (g_Exit[nCntObject].nType != 0)
			//{
			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

			//���_��������
			nNumVtx = g_pMeshObjectWall[nType]->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y������
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObjectWall[nType]->GetFVF());

			//���_�o�b�t�@�����b�N
			g_pMeshObjectWall[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				if (g_ObjectWall[nCntObject].vtxMin.x > vtx.x)
				{
					g_ObjectWall[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_ObjectWall[nCntObject].vtxMin.y > vtx.y)
				{
					g_ObjectWall[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_ObjectWall[nCntObject].vtxMin.z > vtx.z)
				{
					g_ObjectWall[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_ObjectWall[nCntObject].vtxMax.x < vtx.x)
				{
					g_ObjectWall[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_ObjectWall[nCntObject].vtxMax.y < vtx.y)
				{
					g_ObjectWall[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_ObjectWall[nCntObject].vtxMax.z < vtx.z)
				{
					g_ObjectWall[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pMeshObjectWall[nType]->UnlockVertexBuffer();
			//}
			//else
			//{
			//	g_Exit[nCntObject].vtxMin = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
			//	g_Exit[nCntObject].vtxMax = D3DXVECTOR3(100.0f, 150.0f, 5.0f);
			//}

			CollisionRotObjectWall(nCntObject);

			if (nType == 58)
			{
				int a = 0;
			}

			break;
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̍폜����
//====================================================================
void FalseObjectWall(void)
{
	int nCntObject;

	for (nCntObject = MAX_OBJECTWALL; nCntObject >= 0; nCntObject--)
	{
		if (g_ObjectWall[nCntObject].bUse == true)
		{
			g_ObjectWall[nCntObject].bUse = false;
			g_ObjectWallCount--;
			break;
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool EditCollisionObjectWall(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		if (g_ObjectWall[nCntObject].bUse == true)
		{
			if (
				pPos.y + Size >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y
				&& pPos.y - Size <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y
				&& pPos.x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x
				&& pPos.x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x
				&& pPos.z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z
				&& pPos.z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z
				)
			{//�I�u�W�F�N�g���m���d�Ȃ��Ă���
				g_ObjectWall[nCntObject].bUse = false;
				g_ObjectWallCount--;
				bON = true;
			}
		}
	}
	return bON;
}

//====================================================================
//�I�u�W�F�N�g�̓����蔻�����]�����鏈��
//====================================================================
void CollisionRotObjectWall(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_ObjectWall[nCnt].vtxMax.z;
	MaxX = g_ObjectWall[nCnt].vtxMax.x;
	MinZ = g_ObjectWall[nCnt].vtxMin.z;
	MinX = g_ObjectWall[nCnt].vtxMin.x;


	if (g_ObjectWall[nCnt].rot.y <= 0.0f)
	{
		g_ObjectWall[nCnt].vtxMax.z = MaxZ;
		g_ObjectWall[nCnt].vtxMax.x = MaxX;
		g_ObjectWall[nCnt].vtxMin.z = MinZ;
		g_ObjectWall[nCnt].vtxMin.x = MinX;
	}
	else if (g_ObjectWall[nCnt].rot.y <= 1.57f)
	{
		g_ObjectWall[nCnt].vtxMax.z = -MinX;
		g_ObjectWall[nCnt].vtxMax.x = MaxZ;
		g_ObjectWall[nCnt].vtxMin.z = -MaxX;
		g_ObjectWall[nCnt].vtxMin.x = MinZ;
	}
	else if (g_ObjectWall[nCnt].rot.y <= 3.14f)
	{
		g_ObjectWall[nCnt].vtxMax.z = -MinZ;
		g_ObjectWall[nCnt].vtxMax.x = -MinX;
		g_ObjectWall[nCnt].vtxMin.z = -MaxZ;
		g_ObjectWall[nCnt].vtxMin.x = -MaxX;
	}
	else if (g_ObjectWall[nCnt].rot.y <= 4.71f)
	{
		g_ObjectWall[nCnt].vtxMax.z = MaxX;
		g_ObjectWall[nCnt].vtxMax.x = -MinZ;
		g_ObjectWall[nCnt].vtxMin.z = MinX;
		g_ObjectWall[nCnt].vtxMin.x = -MaxZ;
	}
}

//====================================================================
//�O�ς��g�����I�u�W�F�N�g�̓����蔻��
//====================================================================
D3DXVECTOR3 CollisionOuterProductObjectWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	//�ړ��x�N�g��������o��
	D3DXVECTOR3 vecMove = *pPos - *pPosOld;
	//���W�ۊǗp
	int nPosCount = 0;
	D3DXVECTOR3 pos[MAX_OBJECTWALL * 4] = {};
	for (int nCnt = 0; nCnt < MAX_OBJECTWALL; nCnt++)
	{
		if (g_ObjectWall[nCnt].bUse == true)
		{
			for (int nLine = 0; nLine < 4; nLine++)
			{
				bool bHit = false;
				bool bHit1 = false;
				bool bHit2 = false;

				D3DXVECTOR3 pos0, pos1;
				switch (nLine)
				{//���Ђ̓����蔻��
				case 0:
					pos0 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMin.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMax.z);
					pos1 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMax.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMax.z);
					break;
				case 1:
					pos0 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMax.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMax.z);
					pos1 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMax.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMin.z);
					break;
				case 2:
					pos0 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMax.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMin.z);
					pos1 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMin.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMin.z);
					break;
				case 3:
					pos0 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMin.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMin.z);
					pos1 = D3DXVECTOR3(g_ObjectWall[nCnt].pos.x + g_ObjectWall[nCnt].vtxMin.x, g_ObjectWall[nCnt].pos.y, g_ObjectWall[nCnt].pos.z + g_ObjectWall[nCnt].vtxMax.z);
					break;
				default:
					break;
				}

				//�x�N�g���̖ڕW�n�_

				D3DXVECTOR3 vecLine = pos1 - pos0;

				D3DXVECTOR3 vecToPos = *pPos - pos0;

				D3DXVECTOR3 vecToPos2 = *pPosOld - pos0;

				float A, B, fRate;
				A = (vecToPos.z * vecMove.x) - (vecToPos.x * vecMove.z);
				B = (vecLine.z * vecMove.x) - (vecLine.x * vecMove.z);
				if (B != 0)
				{
					fRate = A / B;
				}
				else
				{
					fRate = 10.0f;
				}

				if (fRate >= 0.0f &&fRate <= 1.0f)
				{//vecLine�����؂����Ƃ�
					if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) < 0)
					{
						bHit1 = true;
					}

					if ((vecLine.z * vecToPos2.x) - (vecLine.x * vecToPos2.z) < 0)
					{
						bHit2 = true;
					}

					if (bHit1 != bHit2)
					{
						bHit = true;
					}

					bHit1 = false;
					bHit2 = false;

					if ((vecLine.z * vecToPos.x) + (vecLine.x * vecToPos.z) > 0)
					{
						bHit1 = true;
					}

					if ((vecLine.z * vecToPos2.x) + (vecLine.x * vecToPos2.z) > 0)
					{
						bHit2 = true;
					}

					if (bHit1 != bHit2)
					{
						bHit = true;
					}
				}
				if (bHit == true)
				{
					pos[nPosCount] = pos0 + vecLine*fRate;
					nPosCount++;
				}
			}
		}

	}
	if (nPosCount > 1)
	{
		for (int nCheck = 0; nCheck < nPosCount - 1; nCheck++)
		{//�����̍�������o���ď����Ƀ\�[�g

			for (int nCnt = (nCheck + 1); nCnt < nPosCount; nCnt++)
			{
				D3DXVECTOR3 Temp = pos[nCnt];
				float fDis1, fDis2;
				fDis1 = (pos[nCheck].x - pPosOld->x) + (pos[nCheck].z - pPosOld->z);
				fDis2 = (pos[nCnt].x - pPosOld->x) + (pos[nCnt].z - pPosOld->z);
				if (fDis1 < 0)
				{
					fDis1 *= -1.0f;
				}
				if (fDis2 < 0)
				{
					fDis2 *= -1.0f;
				}
				if (fDis1 > fDis2)
				{
					pos[nCnt] = pos[nCheck];
					pos[nCheck] = Temp;
				}
			}
		}
		
	}
	if (nPosCount > 0)
	{
		return pos[0];
	}
	
	return D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	
}
//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool CollisionObjectWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		if (g_ObjectWall[nCntObject].bUse == true)
		{
			if (
				(
					pPos->y + max.y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y && pPosOld->y + max.y< g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y ||
					pPos->y + min.y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y && pPosOld->y + min.y > g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y) &&
				pPos->x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x &&
				pPos->z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bHit = true;
			}

			if (fabsf(pMove->x) >= fabsf(pMove->z))
			{
				if (
					(
						pPos->z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z && pPosOld->z + Size < g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z ||
						pPos->z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z && pPosOld->z - Size > g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z) &&
					pPos->x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x &&
					pPos->x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x &&
					pPos->y + max.y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y&&
					pPos->y + min.y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y
					)
				{//�ǂƃv���C���[����������(Z��)
					pPos->z = pPosOld->z;
					pMove->z = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x && pPosOld->x + Size < g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x ||
						pPos->x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x && pPosOld->x - Size > g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x) &&
					pPos->z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z &&
					pPos->z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z &&
					pPos->y + max.y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y &&
					pPos->y + min.y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y
					)
				{//�ǂƃv���C���[����������(X��)
					pPos->x = pPosOld->x;
					pMove->x = 0.0f;
					bHit = true;
				}
			}
			else
			{
				if (
					(
						pPos->x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x && pPosOld->x + Size < g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x ||
						pPos->x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x && pPosOld->x - Size > g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x) &&
					pPos->z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z &&
					pPos->z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z &&
					pPos->y + max.y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y &&
					pPos->y + min.y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y
					)
				{//�ǂƃv���C���[����������(X��)
					pPos->x = pPosOld->x;
					pMove->x = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->z + Size >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z && pPosOld->z + Size < g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z ||
						pPos->z - Size <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z && pPosOld->z - Size > g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z) &&
					pPos->x + Size >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x &&
					pPos->x - Size <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x &&
					pPos->y + max.y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y&&
					pPos->y + min.y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y
					)
				{//�ǂƃv���C���[����������(Z��)
					pPos->z = pPosOld->z;
					pMove->z = 0.0f;
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
void CollisionObjectWallShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECTWALL; nCntObject++)
	{
		if (g_ObjectWall[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMin.y &&
				pPos->y <= g_ObjectWall[nCntObject].pos.y + g_ObjectWall[nCntObject].vtxMax.y &&
				pPos->x >= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMin.x &&
				pPos->x <= g_ObjectWall[nCntObject].pos.x + g_ObjectWall[nCntObject].vtxMax.x &&
				pPos->z >= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMin.z &&
				pPos->z <= g_ObjectWall[nCntObject].pos.z + g_ObjectWall[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = g_ObjectWall[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̏���
//====================================================================
ObjectWall * GetObjectWall(void)
{
	return &g_ObjectWall[0];
}