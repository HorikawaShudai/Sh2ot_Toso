//========================================================================================
//
// �w�i�p�I�u�W�F�N�g�̏���[ObjectLight.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "main.h"
#include "objectLight.h"
#include "light.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

#define OBJECTLIGHT_LIFE (7)		//�I�u�W�F�N�g�̗̑�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureObjectLight[64][OBJECTLIGHT_NTYPE_MAX] = {};		//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshObjectLight[OBJECTLIGHT_NTYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObjectLight[OBJECTLIGHT_NTYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatObjectLight[OBJECTLIGHT_NTYPE_MAX] = {};						//�}�e���A���̐�

ObjectLight g_ObjectLight[MAX_OBJECTLIGHT];					//�I�u�W�F�N�gLight�̏��
int EditIndex02;								//�G�f�B�b�g���[�h�p�̔ԍ�
D3DXVECTOR3 EditPos02;						//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
D3DXVECTOR3 EditRot02;						//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̌���
int EditType02;								//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̎��
int g_ObjectCount02;							//�I�u�W�F�N�g�̐�

const char *c_apModelObj02[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\wood.x",
	"Data\\MODEL\\rock.x",
	"Data\\MODEL\\Labo.x",
	"Data\\MODEL\\title_field.x",
	"Data\\MODEL\\door_1.x",
	"Data\\MODEL\\door_2.x",
	"Data\\MODEL\\door_huti.x",
};

//====================================================================
//�I�u�W�F�N�gLight�̏���������
//====================================================================
void InitObjectLight(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		g_ObjectLight[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectLight[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectLight[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectLight[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectLight[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_ObjectLight[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_ObjectLight[nCntObject].bUse = false;
		g_ObjectLight[nCntObject].nType = OBJECTLIGHT_NTYPE00;
		g_ObjectLight[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		g_ObjectLight[nCntObject].LightIdx = -1;
	}
	EditIndex02 = MAX_OBJECTLIGHT - 1;
	EditPos02 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditRot02 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditType02 = 0;
	g_ObjectCount02 = 0;

	//X�t�@�C���̓ǂݍ���
	for (int nCntObj = 0; nCntObj < OBJECTLIGHT_NTYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModelObj02[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObjectLight[nCntObj],
			NULL,
			&g_dwNumMatObjectLight[nCntObj],
			&g_pMeshObjectLight[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < OBJECTLIGHT_NTYPE_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectLight[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectLight[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObjectLight[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//�I�u�W�F�N�gLight�̏I������
//====================================================================
void UninitObjectLight(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECTLIGHT_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureObjectLight[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureObjectLight[nCntTex][nCntNumObject]->Release();
				g_pTextureObjectLight[nCntTex][nCntNumObject] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_pMeshObjectLight[nCntNumObject] != NULL)
		{
			g_pMeshObjectLight[nCntNumObject]->Release();
			g_pMeshObjectLight[nCntNumObject] = NULL;
		}

		//�}�e���A���̔j��
		if (g_pBuffMatObjectLight[nCntNumObject] != NULL)
		{
			g_pBuffMatObjectLight[nCntNumObject]->Release();
			g_pBuffMatObjectLight[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//�I�u�W�F�N�gLight�̍X�V����
//====================================================================
void UpdateObjectLight(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		if (g_ObjectLight[nCntObject].bUse == true)
		{
			//�I�u�W�F�N�g���ێ����郉�C�g�̍X�V����
			SetLight(g_ObjectLight[nCntObject].LightIdx, D3DLIGHT_SPOT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(g_ObjectLight[nCntObject].pos.x, g_ObjectLight[nCntObject].pos.y, g_ObjectLight[nCntObject].pos.z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 200.0f, 2.0f);
		}
	}
	PrintDebugProc("�w�i�I�u�W�F�N�g�̐�:%d\n", g_ObjectCount02);
}

//====================================================================
//�I�u�W�F�N�gLight�̕`�揈��
//====================================================================
void DrawObjectLight(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_ObjectLight[nCntObject].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectLight[nCntObject].rot.y, g_ObjectLight[nCntObject].rot.x, g_ObjectLight[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_ObjectLight[nCntObject].mtxWorld, &g_ObjectLight[nCntObject].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_ObjectLight[nCntObject].pos.x, g_ObjectLight[nCntObject].pos.y, g_ObjectLight[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_ObjectLight[nCntObject].mtxWorld, &g_ObjectLight[nCntObject].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_ObjectLight[nCntObject].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^����������
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectLight[g_ObjectLight[nCntObject].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectLight[g_ObjectLight[nCntObject].nType]; nCntMat++)
		{

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_ObjectLight[nCntObject].bUse == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureObjectLight[nCntMat][g_ObjectLight[nCntObject].nType]);

				//�I�u�W�F�N�gLight(�p�[�c)�̕`��
				g_pMeshObjectLight[g_ObjectLight[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�gLight�̍X�V����
//====================================================================
void UpdateEditObjectLight(void)
{
	//�L�[�{�[�h�̈ړ�����----------
	if (GetKeyboardPress(DIK_UP) == true)
	{//�O�ړ�
		EditPos02.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{//���ړ�
		EditPos02.z -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{//�E�ړ�
		EditPos02.x += 1.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//���ړ�
		EditPos02.x -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{//��ړ�
		EditPos02.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_RCONTROL) == true)
	{//���ړ�
		EditPos02.y -= 1.0f;
	}

	//�I�u�W�F�N�g�̉�]����
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		EditRot02.y += 1.57f;

		if (EditRot02.y >= 6.28f)
		{
			EditRot02.y = 0.0f;
		}
	}

	//�I�u�W�F�N�g�̐؂�ւ�����----------
	if (GetKeyboardTrigger(DIK_9) == true)
	{//�X�L�[�Ŏ��̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditType02++;

		if (EditType02 > OBJECTLIGHT_NTYPE_MAX - 1)
		{
			EditType02 = 0;
		}
	}
	if (GetKeyboardTrigger(DIK_8) == true)
	{//�W�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditType02--;

		if (EditType02 < 0)
		{
			EditType02 = OBJECTLIGHT_NTYPE_MAX - 1;
		}
	}

	//�G�f�B�b�g���[�h�̕ύX���I�u�W�F�N�g�ɔ��f������
	g_ObjectLight[EditIndex02].pos = EditPos02;
	g_ObjectLight[EditIndex02].rot = EditRot02;
	g_ObjectLight[EditIndex02].nType = EditType02;

	//�I�u�W�F�N�g�̍폜����(�d�Ȃ��Ă������)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObjectLight(g_ObjectLight[EditIndex02].pos, g_ObjectLight[EditIndex02].vtxMin, g_ObjectLight[EditIndex02].vtxMax, 20.0f);
	}

	//�I�u�W�F�N�g�̍폜����(CTRL+Z)----------
	if (GetKeyboardTrigger(DIK_Z) == true && GetKeyboardPress(DIK_LCONTROL) == true)
	{
		FalseObjectLight();
	}

	//�I�u�W�F�N�g�̐ݒu����----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObjectLight(g_ObjectLight[EditIndex02].pos, g_ObjectLight[EditIndex02].move, g_ObjectLight[EditIndex02].rot, g_ObjectLight[EditIndex02].nType);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�gLight�̕`�揈��
//====================================================================
void DrawEditObjectLight(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^


									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_ObjectLight[EditIndex02].mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectLight[EditIndex02].rot.y, g_ObjectLight[EditIndex02].rot.x, g_ObjectLight[EditIndex02].rot.z);

	D3DXMatrixMultiply(&g_ObjectLight[EditIndex02].mtxWorld, &g_ObjectLight[EditIndex02].mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_ObjectLight[EditIndex02].pos.x, g_ObjectLight[EditIndex02].pos.y, g_ObjectLight[EditIndex02].pos.z);

	D3DXMatrixMultiply(&g_ObjectLight[EditIndex02].mtxWorld, &g_ObjectLight[EditIndex02].mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_ObjectLight[EditIndex02].mtxWorld);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^����������
	pMat = (D3DXMATERIAL*)g_pBuffMatObjectLight[g_ObjectLight[EditIndex02].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectLight[g_ObjectLight[EditIndex02].nType]; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&g_ObjectLight[EditIndex02].pMatE.MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureObjectLight[nCntMat][g_ObjectLight[EditIndex02].nType]);

		//�I�u�W�F�N�gLight(�p�[�c)�̕`��
		g_pMeshObjectLight[g_ObjectLight[EditIndex02].nType]->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//�I�u�W�F�N�gLight�̐ݒ菈��
//====================================================================
void SetObjectLight(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		if (g_ObjectLight[nCntObject].bUse == false)
		{
			g_ObjectLight[nCntObject].pos = pos;
			g_ObjectLight[nCntObject].posOld = pos;
			g_ObjectLight[nCntObject].move = move;
			g_ObjectLight[nCntObject].rot = rot;
			g_ObjectLight[nCntObject].nType = nType;
			g_ObjectLight[nCntObject].LightIdx = SetIndexLight();		//���C�g�̃Z�b�g����

			g_ObjectLight[nCntObject].bUse = true;
			g_ObjectCount02++;

			//if (g_ObjectLight[nCntObject].nType != 0)
			//{
			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

			//���_��������
			nNumVtx = g_pMeshObjectLight[nType]->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y������
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObjectLight[nType]->GetFVF());

			//���_�o�b�t�@�����b�N
			g_pMeshObjectLight[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				if (g_ObjectLight[nCntObject].vtxMin.x > vtx.x)
				{
					g_ObjectLight[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_ObjectLight[nCntObject].vtxMin.y > vtx.y)
				{
					g_ObjectLight[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_ObjectLight[nCntObject].vtxMin.z > vtx.z)
				{
					g_ObjectLight[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_ObjectLight[nCntObject].vtxMax.x < vtx.x)
				{
					g_ObjectLight[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_ObjectLight[nCntObject].vtxMax.y < vtx.y)
				{
					g_ObjectLight[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_ObjectLight[nCntObject].vtxMax.z < vtx.z)
				{
					g_ObjectLight[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pMeshObjectLight[nType]->UnlockVertexBuffer();
			//}
			//else
			//{
			//	g_ObjectLight[nCntObject].vtxMin = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
			//	g_ObjectLight[nCntObject].vtxMax = D3DXVECTOR3(100.0f, 150.0f, 5.0f);
			//}


			CollisionRotObjectLight(nCntObject);

			break;
		}
	}
}

//====================================================================
//�I�u�W�F�N�gLight�̍폜����
//====================================================================
void FalseObjectLight(void)
{
	int nCntObject;

	for (nCntObject = MAX_OBJECTLIGHT; nCntObject >= 0; nCntObject--)
	{
		if (g_ObjectLight[nCntObject].bUse == true)
		{
			g_ObjectLight[nCntObject].bUse = false;
			break;
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool EditCollisionObjectLight(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		if (g_ObjectLight[nCntObject].bUse == true)
		{
			if (
				pPos.y + Size >= g_ObjectLight[nCntObject].pos.y + g_ObjectLight[nCntObject].vtxMin.y && pPos.y - Size <= g_ObjectLight[nCntObject].pos.y + g_ObjectLight[nCntObject].vtxMax.y &&
				pPos.x + Size >= g_ObjectLight[nCntObject].pos.x + g_ObjectLight[nCntObject].vtxMin.x && pPos.x - Size <= g_ObjectLight[nCntObject].pos.x + g_ObjectLight[nCntObject].vtxMax.x &&
				pPos.z + Size >= g_ObjectLight[nCntObject].pos.z + g_ObjectLight[nCntObject].vtxMin.z && pPos.z - Size <= g_ObjectLight[nCntObject].pos.z + g_ObjectLight[nCntObject].vtxMax.z
				)
			{//�I�u�W�F�N�g���m���d�Ȃ��Ă���
				g_ObjectLight[nCntObject].bUse = false;

				bON = true;
			}
		}
	}
	return bON;
}

//====================================================================
//�I�u�W�F�N�g�̓����蔻�����]�����鏈��
//====================================================================
void CollisionRotObjectLight(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_ObjectLight[nCnt].vtxMax.z;
	MaxX = g_ObjectLight[nCnt].vtxMax.x;
	MinZ = g_ObjectLight[nCnt].vtxMin.z;
	MinX = g_ObjectLight[nCnt].vtxMin.x;


	if (g_ObjectLight[nCnt].rot.y <= 0.0f)
	{
		g_ObjectLight[nCnt].vtxMax.z = MaxZ;
		g_ObjectLight[nCnt].vtxMax.x = MaxX;
		g_ObjectLight[nCnt].vtxMin.z = MinZ;
		g_ObjectLight[nCnt].vtxMin.x = MinX;
	}
	else if (g_ObjectLight[nCnt].rot.y <= 1.57f)
	{
		g_ObjectLight[nCnt].vtxMax.z = -MinX;
		g_ObjectLight[nCnt].vtxMax.x = MaxZ;
		g_ObjectLight[nCnt].vtxMin.z = -MaxX;
		g_ObjectLight[nCnt].vtxMin.x = MinZ;
	}
	else if (g_ObjectLight[nCnt].rot.y <= 3.14f)
	{
		g_ObjectLight[nCnt].vtxMax.z = -MinZ;
		g_ObjectLight[nCnt].vtxMax.x = -MinX;
		g_ObjectLight[nCnt].vtxMin.z = -MaxZ;
		g_ObjectLight[nCnt].vtxMin.x = -MaxX;
	}
	else if (g_ObjectLight[nCnt].rot.y <= 4.71f)
	{
		g_ObjectLight[nCnt].vtxMax.z = MaxX;
		g_ObjectLight[nCnt].vtxMax.x = -MinZ;
		g_ObjectLight[nCnt].vtxMin.z = MinX;
		g_ObjectLight[nCnt].vtxMin.x = -MaxZ;
	}
}

//====================================================================
//�e�Ƃ̓����蔻�菈��
//====================================================================
void CollisionObjectLightShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECTLIGHT; nCntObject++)
	{
		if (g_ObjectLight[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_ObjectLight[nCntObject].pos.y + g_ObjectLight[nCntObject].vtxMin.y &&
				pPos->y <= g_ObjectLight[nCntObject].pos.y + g_ObjectLight[nCntObject].vtxMax.y &&
				pPos->x >= g_ObjectLight[nCntObject].pos.x + g_ObjectLight[nCntObject].vtxMin.x &&
				pPos->x <= g_ObjectLight[nCntObject].pos.x + g_ObjectLight[nCntObject].vtxMax.x &&
				pPos->z >= g_ObjectLight[nCntObject].pos.z + g_ObjectLight[nCntObject].vtxMin.z &&
				pPos->z <= g_ObjectLight[nCntObject].pos.z + g_ObjectLight[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = g_ObjectLight[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//�I�u�W�F�N�gLight�̏���
//====================================================================
ObjectLight * GetObjectLight(void)
{
	return &g_ObjectLight[0];
}