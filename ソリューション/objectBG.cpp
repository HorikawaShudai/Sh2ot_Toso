#include "main.h"
#include "objectBG.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

#define OBJECTBG_LIFE (7)		//�I�u�W�F�N�g�̗̑�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureObjectBG[64][OBJECTBG_NTYPE_MAX] = {};		//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshObjectBG[OBJECTBG_NTYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObjectBG[OBJECTBG_NTYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatObjectBG[OBJECTBG_NTYPE_MAX] = {};						//�}�e���A���̐�

ObjectBG g_ObjectBG[MAX_OBJECTBG];					//�I�u�W�F�N�g00�̏��
int EditIndex01;								//�G�f�B�b�g���[�h�p�̔ԍ�
D3DXVECTOR3 EditPos01;						//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
D3DXVECTOR3 EditRot01;						//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̌���
int EditType01;								//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̎��
int g_ObjectCount01;							//�I�u�W�F�N�g�̐�

const char *c_apModelObj01[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\wood.x",
	"Data\\MODEL\\rock.x",

};

//====================================================================
//�I�u�W�F�N�g00�̏���������
//====================================================================
void InitObjectBG(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		g_ObjectBG[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectBG[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectBG[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectBG[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectBG[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_ObjectBG[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_ObjectBG[nCntObject].bUse = false;
		g_ObjectBG[nCntObject].nType = OBJECTBG_NTYPE00;
		g_ObjectBG[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	}
	EditIndex01 = 0;
	EditPos01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditRot01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditType01 = 0;
	g_ObjectCount01 = 0;

	//X�t�@�C���̓ǂݍ���
	for (int nCntObj = 0; nCntObj < OBJECTBG_NTYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModelObj01[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObjectBG[nCntObj],
			NULL,
			&g_dwNumMatObjectBG[nCntObj],
			&g_pMeshObjectBG[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < OBJECTBG_NTYPE_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectBG[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectBG[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObjectBG[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̏I������
//====================================================================
void UninitObjectBG(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECTBG_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureObjectBG[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureObjectBG[nCntTex][nCntNumObject]->Release();
				g_pTextureObjectBG[nCntTex][nCntNumObject] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_pMeshObjectBG[nCntNumObject] != NULL)
		{
			g_pMeshObjectBG[nCntNumObject]->Release();
			g_pMeshObjectBG[nCntNumObject] = NULL;
		}

		//�}�e���A���̔j��
		if (g_pBuffMatObjectBG[nCntNumObject] != NULL)
		{
			g_pBuffMatObjectBG[nCntNumObject]->Release();
			g_pBuffMatObjectBG[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateObjectBG(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		if (g_ObjectBG[nCntObject].bUse == true)
		{

		}
	}
	PrintDebugProc("�w�i�I�u�W�F�N�g�̐�:%d\n", g_ObjectCount01);
}

//====================================================================
//�I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawObjectBG(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_ObjectBG[nCntObject].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectBG[nCntObject].rot.y, g_ObjectBG[nCntObject].rot.x, g_ObjectBG[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_ObjectBG[nCntObject].mtxWorld, &g_ObjectBG[nCntObject].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_ObjectBG[nCntObject].pos.x, g_ObjectBG[nCntObject].pos.y, g_ObjectBG[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_ObjectBG[nCntObject].mtxWorld, &g_ObjectBG[nCntObject].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_ObjectBG[nCntObject].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^����������
		pMat = (D3DXMATERIAL*)g_pBuffMatObjectBG[g_ObjectBG[nCntObject].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectBG[g_ObjectBG[nCntObject].nType]; nCntMat++)
		{

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_ObjectBG[nCntObject].bUse == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureObjectBG[nCntMat][g_ObjectBG[nCntObject].nType]);

				//�I�u�W�F�N�g00(�p�[�c)�̕`��
				g_pMeshObjectBG[g_ObjectBG[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateEditObjectBG(void)
{
	//�L�[�{�[�h�̈ړ�����----------
	if (GetKeyboardPress(DIK_UP) == true)
	{//�O�ړ�
		EditPos01.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{//���ړ�
		EditPos01.z -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{//�E�ړ�
		EditPos01.x += 1.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//���ړ�
		EditPos01.x -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{//��ړ�
		EditPos01.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_RCONTROL) == true)
	{//���ړ�
		EditPos01.y -= 1.0f;
	}

	//�I�u�W�F�N�g�̉�]����
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		EditRot01.y += 1.57f;

		if (EditRot01.y >= 6.28f)
		{
			EditRot01.y = 0.0f;
		}
	}

	//�I�u�W�F�N�g�̐؂�ւ�����----------
	if (GetKeyboardTrigger(DIK_9) == true)
	{//�X�L�[�Ŏ��̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditType01++;

		if (EditType01 > OBJECTBG_NTYPE_MAX - 1)
		{
			EditType01 = 0;
		}
	}
	if (GetKeyboardTrigger(DIK_8) == true)
	{//�W�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditType01--;

		if (EditType01 < 0)
		{
			EditType01 = OBJECTBG_NTYPE_MAX - 1;
		}
	}

	//�G�f�B�b�g���[�h�̕ύX���I�u�W�F�N�g�ɔ��f������
	g_ObjectBG[EditIndex01].pos = EditPos01;
	g_ObjectBG[EditIndex01].rot = EditRot01;
	g_ObjectBG[EditIndex01].nType = EditType01;

	//�I�u�W�F�N�g�̍폜����(�d�Ȃ��Ă������)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObjectBG(g_ObjectBG[EditIndex01].pos, g_ObjectBG[EditIndex01].vtxMin, g_ObjectBG[EditIndex01].vtxMax, 20.0f);
	}

	//�I�u�W�F�N�g�̍폜����(CTRL+Z)----------
	if (GetKeyboardTrigger(DIK_Z) == true && GetKeyboardPress(DIK_LCONTROL) == true)
	{
		FalseObjectBG();
	}

	//�I�u�W�F�N�g�̐ݒu����----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObjectBG(g_ObjectBG[EditIndex01].pos, g_ObjectBG[EditIndex01].move, g_ObjectBG[EditIndex01].rot, g_ObjectBG[EditIndex01].nType);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawEditObjectBG(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^


									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_ObjectBG[EditIndex01].mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectBG[EditIndex01].rot.y, g_ObjectBG[EditIndex01].rot.x, g_ObjectBG[EditIndex01].rot.z);

	D3DXMatrixMultiply(&g_ObjectBG[EditIndex01].mtxWorld, &g_ObjectBG[EditIndex01].mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_ObjectBG[EditIndex01].pos.x, g_ObjectBG[EditIndex01].pos.y, g_ObjectBG[EditIndex01].pos.z);

	D3DXMatrixMultiply(&g_ObjectBG[EditIndex01].mtxWorld, &g_ObjectBG[EditIndex01].mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_ObjectBG[EditIndex01].mtxWorld);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^����������
	pMat = (D3DXMATERIAL*)g_pBuffMatObjectBG[g_ObjectBG[EditIndex01].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObjectBG[g_ObjectBG[EditIndex01].nType]; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&g_ObjectBG[EditIndex01].pMatE.MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureObjectBG[nCntMat][g_ObjectBG[EditIndex01].nType]);

		//�I�u�W�F�N�g00(�p�[�c)�̕`��
		g_pMeshObjectBG[g_ObjectBG[EditIndex01].nType]->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//�I�u�W�F�N�g00�̐ݒ菈��
//====================================================================
void SetObjectBG(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		if (g_ObjectBG[nCntObject].bUse == false)
		{
			g_ObjectBG[nCntObject].pos = pos;
			g_ObjectBG[nCntObject].posOld = pos;
			g_ObjectBG[nCntObject].move = move;
			g_ObjectBG[nCntObject].rot = rot;
			g_ObjectBG[nCntObject].nType = nType;

			g_ObjectBG[nCntObject].bUse = true;
			EditIndex01++;
			g_ObjectCount01++;

			//if (g_ObjectBG[nCntObject].nType != 0)
			//{
			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

								//���_��������
			nNumVtx = g_pMeshObjectBG[nType]->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y������
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObjectBG[nType]->GetFVF());

			//���_�o�b�t�@�����b�N
			g_pMeshObjectBG[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				if (g_ObjectBG[nCntObject].vtxMin.x > vtx.x)
				{
					g_ObjectBG[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_ObjectBG[nCntObject].vtxMin.y > vtx.y)
				{
					g_ObjectBG[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_ObjectBG[nCntObject].vtxMin.z > vtx.z)
				{
					g_ObjectBG[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_ObjectBG[nCntObject].vtxMax.x < vtx.x)
				{
					g_ObjectBG[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_ObjectBG[nCntObject].vtxMax.y < vtx.y)
				{
					g_ObjectBG[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_ObjectBG[nCntObject].vtxMax.z < vtx.z)
				{
					g_ObjectBG[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pMeshObjectBG[nType]->UnlockVertexBuffer();
			//}
			//else
			//{
			//	g_ObjectBG[nCntObject].vtxMin = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
			//	g_ObjectBG[nCntObject].vtxMax = D3DXVECTOR3(100.0f, 150.0f, 5.0f);
			//}


			CollisionRotObjectBG(nCntObject);

			break;
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̍폜����
//====================================================================
void FalseObjectBG(void)
{
	int nCntObject;

	for (nCntObject = MAX_OBJECTBG; nCntObject >= 0; nCntObject--)
	{
		if (g_ObjectBG[nCntObject].bUse == true)
		{
			g_ObjectBG[nCntObject].bUse = false;
			EditIndex01--;
			break;
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool EditCollisionObjectBG(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		if (g_ObjectBG[nCntObject].bUse == true)
		{
			if (
				pPos.y + Size >= g_ObjectBG[nCntObject].pos.y + g_ObjectBG[nCntObject].vtxMin.y && pPos.y - Size <= g_ObjectBG[nCntObject].pos.y + g_ObjectBG[nCntObject].vtxMax.y &&
				pPos.x + Size >= g_ObjectBG[nCntObject].pos.x + g_ObjectBG[nCntObject].vtxMin.x && pPos.x - Size <= g_ObjectBG[nCntObject].pos.x + g_ObjectBG[nCntObject].vtxMax.x &&
				pPos.z + Size >= g_ObjectBG[nCntObject].pos.z + g_ObjectBG[nCntObject].vtxMin.z && pPos.z - Size <= g_ObjectBG[nCntObject].pos.z + g_ObjectBG[nCntObject].vtxMax.z
				)
			{//�I�u�W�F�N�g���m���d�Ȃ��Ă���
				g_ObjectBG[nCntObject].bUse = false;

				bON = true;
			}
		}
	}
	return bON;
}

//====================================================================
//�I�u�W�F�N�g�̓����蔻�����]�����鏈��
//====================================================================
void CollisionRotObjectBG(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_ObjectBG[nCnt].vtxMax.z;
	MaxX = g_ObjectBG[nCnt].vtxMax.x;
	MinZ = g_ObjectBG[nCnt].vtxMin.z;
	MinX = g_ObjectBG[nCnt].vtxMin.x;


	if (g_ObjectBG[nCnt].rot.y <= 0.0f)
	{
		g_ObjectBG[nCnt].vtxMax.z = MaxZ;
		g_ObjectBG[nCnt].vtxMax.x = MaxX;
		g_ObjectBG[nCnt].vtxMin.z = MinZ;
		g_ObjectBG[nCnt].vtxMin.x = MinX;
	}
	else if (g_ObjectBG[nCnt].rot.y <= 1.57f)
	{
		g_ObjectBG[nCnt].vtxMax.z = -MinX;
		g_ObjectBG[nCnt].vtxMax.x = MaxZ;
		g_ObjectBG[nCnt].vtxMin.z = -MaxX;
		g_ObjectBG[nCnt].vtxMin.x = MinZ;
	}
	else if (g_ObjectBG[nCnt].rot.y <= 3.14f)
	{
		g_ObjectBG[nCnt].vtxMax.z = -MinZ;
		g_ObjectBG[nCnt].vtxMax.x = -MinX;
		g_ObjectBG[nCnt].vtxMin.z = -MaxZ;
		g_ObjectBG[nCnt].vtxMin.x = -MaxX;
	}
	else if (g_ObjectBG[nCnt].rot.y <= 4.71f)
	{
		g_ObjectBG[nCnt].vtxMax.z = MaxX;
		g_ObjectBG[nCnt].vtxMax.x = -MinZ;
		g_ObjectBG[nCnt].vtxMin.z = MinX;
		g_ObjectBG[nCnt].vtxMin.x = -MaxZ;
	}
}

//====================================================================
//�e�Ƃ̓����蔻�菈��
//====================================================================
void CollisionObjectBGShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECTBG; nCntObject++)
	{
		if (g_ObjectBG[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_ObjectBG[nCntObject].pos.y + g_ObjectBG[nCntObject].vtxMin.y &&
				pPos->y <= g_ObjectBG[nCntObject].pos.y + g_ObjectBG[nCntObject].vtxMax.y &&
				pPos->x >= g_ObjectBG[nCntObject].pos.x + g_ObjectBG[nCntObject].vtxMin.x &&
				pPos->x <= g_ObjectBG[nCntObject].pos.x + g_ObjectBG[nCntObject].vtxMax.x &&
				pPos->z >= g_ObjectBG[nCntObject].pos.z + g_ObjectBG[nCntObject].vtxMin.z &&
				pPos->z <= g_ObjectBG[nCntObject].pos.z + g_ObjectBG[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = g_ObjectBG[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̏���
//====================================================================
ObjectBG * GetObjectBG(void)
{
	return &g_ObjectBG[0];
}