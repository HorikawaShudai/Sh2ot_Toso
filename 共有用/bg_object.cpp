#include "main.h"
#include "bg_object.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

#define OBJECT00_LIFE (7)		//�I�u�W�F�N�g�̗̑�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBg_object[64][OBJECT00_NTYPE_MAX] = {};		//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshBg_object[OBJECT00_NTYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatBg_object[OBJECT00_NTYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatBg_object[OBJECT00_NTYPE_MAX] = {};						//�}�e���A���̐�

Object00 g_Bg_object[MAX_OBJECT00];					//�I�u�W�F�N�g00�̏��
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
void InitBg_object(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		g_Bg_object[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bg_object[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bg_object[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bg_object[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bg_object[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Bg_object[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Bg_object[nCntObject].bUse = false;
		g_Bg_object[nCntObject].nType = OBJECT00_NTYPE00;
		g_Bg_object[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	}
	EditIndex01 = 0;
	EditPos01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditRot01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditType01 = 0;
	g_ObjectCount01 = 0;

	//X�t�@�C���̓ǂݍ���
	for (int nCntObj = 0; nCntObj < OBJECT00_NTYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModelObj01[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatBg_object[nCntObj],
			NULL,
			&g_dwNumMatBg_object[nCntObj],
			&g_pMeshBg_object[nCntObj]);
	}


	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < OBJECT00_NTYPE_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatBg_object[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBg_object[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureBg_object[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̏I������
//====================================================================
void UninitBg_object(void)
{
	for (int nCntNumObject = 0; nCntNumObject < OBJECT00_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureBg_object[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureBg_object[nCntTex][nCntNumObject]->Release();
				g_pTextureBg_object[nCntTex][nCntNumObject] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_pMeshBg_object[nCntNumObject] != NULL)
		{
			g_pMeshBg_object[nCntNumObject]->Release();
			g_pMeshBg_object[nCntNumObject] = NULL;
		}

		//�}�e���A���̔j��
		if (g_pBuffMatBg_object[nCntNumObject] != NULL)
		{
			g_pBuffMatBg_object[nCntNumObject]->Release();
			g_pBuffMatBg_object[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateBg_object(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Bg_object[nCntObject].bUse == true)
		{

		}
	}
	PrintDebugProc("�I�u�W�F�N�g�̐�:%d\n", g_ObjectCount01);
}

//====================================================================
//�I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawBg_object(void)
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
		D3DXMatrixIdentity(&g_Bg_object[nCntObject].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Bg_object[nCntObject].rot.y, g_Bg_object[nCntObject].rot.x, g_Bg_object[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_Bg_object[nCntObject].mtxWorld, &g_Bg_object[nCntObject].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Bg_object[nCntObject].pos.x, g_Bg_object[nCntObject].pos.y, g_Bg_object[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_Bg_object[nCntObject].mtxWorld, &g_Bg_object[nCntObject].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Bg_object[nCntObject].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^����������
		pMat = (D3DXMATERIAL*)g_pBuffMatBg_object[g_Bg_object[nCntObject].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBg_object[g_Bg_object[nCntObject].nType]; nCntMat++)
		{

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_Bg_object[nCntObject].bUse == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBg_object[nCntMat][g_Bg_object[nCntObject].nType]);

				//�I�u�W�F�N�g00(�p�[�c)�̕`��
				g_pMeshBg_object[g_Bg_object[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateEditBg_object(void)
{
	//�L�[�{�[�h�̈ړ�����----------
	if (g_Bg_object[EditIndex01].nType == 0)
	{//�I������Ă���I�u�W�F�N�g���ǂ̎�
		if (GetKeyboardTrigger(DIK_UP) == true)
		{//�O�ړ�
			EditPos01.z += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{//���ړ�
			EditPos01.z -= 100.0f;
		}
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{//�E�ړ�
			EditPos01.x += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{//���ړ�
			EditPos01.x -= 100.0f;
		}
	}

	if (g_Bg_object[EditIndex01].nType != 0)
	{//�I������Ă���I�u�W�F�N�g���ǈȊO�̎�
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

		if (EditType01 > OBJECT00_NTYPE_MAX - 1)
		{
			EditType01 = 0;
		}

		if (EditType01 == 0)
		{
			EditPos01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
	if (GetKeyboardTrigger(DIK_8) == true)
	{//�W�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditType01--;

		if (EditType01 < 0)
		{
			EditType01 = OBJECT00_NTYPE_MAX - 1;
		}

		if (EditType01 == 0)
		{
			EditPos01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	//�G�f�B�b�g���[�h�̕ύX���I�u�W�F�N�g�ɔ��f������
	g_Bg_object[EditIndex01].pos = EditPos01;
	g_Bg_object[EditIndex01].rot = EditRot01;
	g_Bg_object[EditIndex01].nType = EditType01;

	//�I�u�W�F�N�g�̍폜����(�d�Ȃ��Ă������)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionBg_object(g_Bg_object[EditIndex01].pos, g_Bg_object[EditIndex01].vtxMin, g_Bg_object[EditIndex01].vtxMax, 20.0f);
	}

	//�I�u�W�F�N�g�̍폜����(CTRL+Z)----------
	if (GetKeyboardTrigger(DIK_Z) == true && GetKeyboardPress(DIK_LCONTROL) == true)
	{
		FalseBg_object();
	}

	//�I�u�W�F�N�g�̐ݒu����----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetBg_object(g_Bg_object[EditIndex01].pos, g_Bg_object[EditIndex01].move, g_Bg_object[EditIndex01].rot, g_Bg_object[EditIndex01].nType);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawEditBg_object(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^


									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Bg_object[EditIndex01].mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Bg_object[EditIndex01].rot.y, g_Bg_object[EditIndex01].rot.x, g_Bg_object[EditIndex01].rot.z);

	D3DXMatrixMultiply(&g_Bg_object[EditIndex01].mtxWorld, &g_Bg_object[EditIndex01].mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Bg_object[EditIndex01].pos.x, g_Bg_object[EditIndex01].pos.y, g_Bg_object[EditIndex01].pos.z);

	D3DXMatrixMultiply(&g_Bg_object[EditIndex01].mtxWorld, &g_Bg_object[EditIndex01].mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Bg_object[EditIndex01].mtxWorld);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^����������
	pMat = (D3DXMATERIAL*)g_pBuffMatBg_object[g_Bg_object[EditIndex01].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBg_object[g_Bg_object[EditIndex01].nType]; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&g_Bg_object[EditIndex01].pMatE.MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBg_object[nCntMat][g_Bg_object[EditIndex01].nType]);

		//�I�u�W�F�N�g00(�p�[�c)�̕`��
		g_pMeshBg_object[g_Bg_object[EditIndex01].nType]->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//�I�u�W�F�N�g00�̐ݒ菈��
//====================================================================
void SetBg_object(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Bg_object[nCntObject].bUse == false)
		{
			g_Bg_object[nCntObject].pos = pos;
			g_Bg_object[nCntObject].posOld = pos;
			g_Bg_object[nCntObject].move = move;
			g_Bg_object[nCntObject].rot = rot;
			g_Bg_object[nCntObject].nType = nType;

			g_Bg_object[nCntObject].bUse = true;
			EditIndex01++;
			g_ObjectCount01++;

			//if (g_Object00[nCntObject].nType != 0)
			//{
			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

								//���_��������
			nNumVtx = g_pMeshBg_object[nType]->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y������
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshBg_object[nType]->GetFVF());

			//���_�o�b�t�@�����b�N
			g_pMeshBg_object[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				if (g_Bg_object[nCntObject].vtxMin.x > vtx.x)
				{
					g_Bg_object[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_Bg_object[nCntObject].vtxMin.y > vtx.y)
				{
					g_Bg_object[nCntObject].vtxMin.y = vtx.y;
				}	  
				if (g_Bg_object[nCntObject].vtxMin.z > vtx.z)
				{	  
					g_Bg_object[nCntObject].vtxMin.z = vtx.z;
				}	  
					  
				if (g_Bg_object[nCntObject].vtxMax.x < vtx.x)
				{	  
					g_Bg_object[nCntObject].vtxMax.x = vtx.x;
				}	  
				if (g_Bg_object[nCntObject].vtxMax.y < vtx.y)
				{	  
					g_Bg_object[nCntObject].vtxMax.y = vtx.y;
				}	  
				if (g_Bg_object[nCntObject].vtxMax.z < vtx.z)
				{	  
					g_Bg_object[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pMeshBg_object[nType]->UnlockVertexBuffer();
			//}
			//else
			//{
			//	g_Object00[nCntObject].vtxMin = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
			//	g_Object00[nCntObject].vtxMax = D3DXVECTOR3(100.0f, 150.0f, 5.0f);
			//}


			CollisionRotBg_object(nCntObject);

			break;
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̍폜����
//====================================================================
void FalseBg_object(void)
{
	int nCntObject;

	for (nCntObject = MAX_OBJECT00; nCntObject >= 0; nCntObject--)
	{
		if (g_Bg_object[nCntObject].bUse == true)
		{
			g_Bg_object[nCntObject].bUse = false;
			EditIndex01--;
			break;
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool EditCollisionBg_object(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Bg_object[nCntObject].bUse == true)
		{
			if (
				pPos.y + Size >= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y && pPos.y - Size <= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y &&
				pPos.x + Size >= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x && pPos.x - Size <= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x &&
				pPos.z + Size >= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z && pPos.z - Size <= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z
				)
			{//�I�u�W�F�N�g���m���d�Ȃ��Ă���
				g_Bg_object[nCntObject].bUse = false;

				bON = true;
			}
		}
	}
	return bON;
}

//====================================================================
//�I�u�W�F�N�g�̓����蔻�����]�����鏈��
//====================================================================
void CollisionRotBg_object(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_Bg_object[nCnt].vtxMax.z;
	MaxX = g_Bg_object[nCnt].vtxMax.x;
	MinZ = g_Bg_object[nCnt].vtxMin.z;
	MinX = g_Bg_object[nCnt].vtxMin.x;


	if (g_Bg_object[nCnt].rot.y <= 0.0f)
	{
		g_Bg_object[nCnt].vtxMax.z = MaxZ;
		g_Bg_object[nCnt].vtxMax.x = MaxX;
		g_Bg_object[nCnt].vtxMin.z = MinZ;
		g_Bg_object[nCnt].vtxMin.x = MinX;
	}
	else if (g_Bg_object[nCnt].rot.y <= 1.57f)
	{
		g_Bg_object[nCnt].vtxMax.z = -MinX;
		g_Bg_object[nCnt].vtxMax.x = MaxZ;
		g_Bg_object[nCnt].vtxMin.z = -MaxX;
		g_Bg_object[nCnt].vtxMin.x = MinZ;
	}
	else if (g_Bg_object[nCnt].rot.y <= 3.14f)
	{
		g_Bg_object[nCnt].vtxMax.z = -MinZ;
		g_Bg_object[nCnt].vtxMax.x = -MinX;
		g_Bg_object[nCnt].vtxMin.z = -MaxZ;
		g_Bg_object[nCnt].vtxMin.x = -MaxX;
	}
	else if (g_Bg_object[nCnt].rot.y <= 4.71f)
	{
		g_Bg_object[nCnt].vtxMax.z = MaxX;
		g_Bg_object[nCnt].vtxMax.x = -MinZ;
		g_Bg_object[nCnt].vtxMin.z = MinX;
		g_Bg_object[nCnt].vtxMin.x = -MaxZ;
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool CollisionBg_object(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Bg_object[nCntObject].bUse == true)
		{
			if (
				(
					pPos->y + max.y >= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y && pPosOld->y + max.y< g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y ||
					pPos->y + min.y <= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y && pPosOld->y + min.y > g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y) &&
				pPos->x + Size >= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x &&
				pPos->z + Size >= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bHit = true;
			}

			if (
				(
					pPos->z + Size >= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z && pPosOld->z + Size < g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z ||
					pPos->z - Size <= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z && pPosOld->z - Size > g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z) &&
				pPos->x + Size >= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x &&
				pPos->y + max.y >= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y&&
				pPos->y + min.y <= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y
				)
			{//�ǂƃv���C���[����������(Z��)
				pPos->z = pPosOld->z;
				pMove->z = 0.0f;
				bHit = true;
			}

			if (
				(
					pPos->x + Size >= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x && pPosOld->x + Size < g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x ||
					pPos->x - Size <= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x && pPosOld->x - Size > g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x) &&
				pPos->z + Size >= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z &&
				pPos->y + max.y >= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y &&
				pPos->y + min.y <= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y
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
void CollisionBg_objectShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Bg_object[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMin.y &&
				pPos->y <= g_Bg_object[nCntObject].pos.y + g_Bg_object[nCntObject].vtxMax.y &&
				pPos->x >= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMin.x &&
				pPos->x <= g_Bg_object[nCntObject].pos.x + g_Bg_object[nCntObject].vtxMax.x &&
				pPos->z >= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMin.z &&
				pPos->z <= g_Bg_object[nCntObject].pos.z + g_Bg_object[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = g_Bg_object[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//�I�u�W�F�N�g00�̏���
//====================================================================
Object00 * GetBg_object(void)
{
	return &g_Bg_object[0];
}