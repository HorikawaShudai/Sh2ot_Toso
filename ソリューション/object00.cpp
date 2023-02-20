//========================================================================================
//
// �I�u�W�F�N�g�̏���[Object00.cpp]
// Author: ��{�@�ėB
// Author: �O�엳�V��
//
//========================================================================================
#include "main.h"
#include "object00.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "score.h"

#define OBJECT00_LIFE (7)		//�I�u�W�F�N�g�̗̑�
#define FALSE_SIZE (20.0f)		//�G�f�B�b�g���[�h�̃o�b�N�X�y�[�X�̔���̑傫��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureObject00[64][OBJECT00_NTYPE_MAX] = {};		//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshObject00[OBJECT00_NTYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObject00[OBJECT00_NTYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatObject00[OBJECT00_NTYPE_MAX] = {};						//�}�e���A���̐�

Object00 g_Object00[MAX_OBJECT00];				//�I�u�W�F�N�g00�̏��
int EditIndex;									//�G�f�B�b�g���[�h�p�̔ԍ�
D3DXVECTOR3 EditPos;							//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
D3DXVECTOR3 EditRot;							//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̌���
int EditType;									//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̎��
int g_ObjectCount;								//�I�u�W�F�N�g�̐�

const char *c_apModelObj[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\HighPolyWall.x",				//�|���S�����̑�����
	"Data\\MODEL\\kaidan.x",					//�K�i
	"Data\\MODEL\\kaidanR_up.x",				//�K�i��
	"Data\\MODEL\\countertable.x",				//��t
	"Data\\MODEL\\desk.x",						//��
	"Data\\MODEL\\PapersShelf.x",				//�����I
	"Data\\MODEL\\gareki.x",					//���ꂫ
	"Data\\MODEL\\LaboTable.x",					//���{�e�[�u��
	"Data\\MODEL\\lounge.x",					//���E���W
	"Data\\MODEL\\CultureTank.x",				//�J���`���[�^���N			������
	"Data\\MODEL\\BigCultureTank.x",			//�J���`���[�^���N(��)		������
	"Data\\MODEL\\machine.x",					//�}�V��					������
	"Data\\MODEL\\Messychair.x",				//�ςݏd�Ȃ����֎q
	"Data\\MODEL\\MessyDesk.x",					//�ςݏd�Ȃ�����
	"Data\\MODEL\\MessyMachine.x",				//���ꂫ������Ă�}�V��
	"Data\\MODEL\\MessyObject00.x",				//�F�X�Ȃ��̂��d�Ȃ��Ă���I�u�W�F�N�g
	"Data\\MODEL\\MessyStairs.x",				//����Ă�A�[�`�K�i
	"Data\\MODEL\\moniter.x",					//���j�^�[
	"Data\\MODEL\\ori00.x",						//�B
	"Data\\MODEL\\pot.x",						//�|�b�g					������
	"Data\\MODEL\\prison.x",					//�S��						���e
	"Data\\MODEL\\rubble.x",					//���ɗ����Ă邪�ꂫ
	"Data\\MODEL\\ka-ten00.x",					//�J�[�e��
	"Data\\MODEL\\chemicalshelf.x",				//�򂪓����Ă�I
	"Data\\MODEL\\PapersShelf.x",				//�����I(��)
	"Data\\MODEL\\PapersShelf1.x",				//�����I(��)
	"Data\\MODEL\\Cabinet.x",					//���̒u���Ă���I
	"Data\\MODEL\\small_cage.x",				//�P�[�W
	"Data\\MODEL\\small_cage_twin.x",			//�P�[�W
	"Data\\MODEL\\fence.x",						//�t�F���X
	"Data\\MODEL\\sofaa.x",						//�\�t�@
	"Data\\MODEL\\pillar.x",					//��
	"Data\\MODEL\\desk_pc.x",					//PC���ڂ��Ă���f�X�N
	"Data\\MODEL\\officechair.x",				//�I�t�B�X�̈֎q
};

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
		g_Object00[nCntObject].pMatE.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	}
	EditIndex = MAX_OBJECT00 - 1;
	EditPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EditType = 0;
	g_ObjectCount = 0;

	//X�t�@�C���̓ǂݍ���
	for (int nCntObj = 0; nCntObj < OBJECT00_NTYPE_MAX; nCntObj++)
	{
		D3DXLoadMeshFromX(c_apModelObj[nCntObj],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObject00[nCntObj],
			NULL,
			&g_dwNumMatObject00[nCntObj],
			&g_pMeshObject00[nCntObj]);
	}


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
	PrintDebugProc("�I�u�W�F�N�g�̐�:%d\n", g_ObjectCount);
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
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureObject00[nCntMat][g_Object00[nCntObject].nType]);

					//�I�u�W�F�N�g00(�p�[�c)�̕`��
					g_pMeshObject00[g_Object00[nCntObject].nType]->DrawSubset(nCntMat);
				}
			}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̍X�V����
//====================================================================
void UpdateEditObject00(void)
{
	//�L�[�{�[�h�̈ړ�����----------
	if (g_Object00[EditIndex].nType == 0)
	{//�I������Ă���I�u�W�F�N�g���ǂ̎�
		if (GetKeyboardTrigger(DIK_UP) == true)
		{//�O�ړ�
			EditPos.z += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{//���ړ�
			EditPos.z -= 100.0f;
		}
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{//�E�ړ�
			EditPos.x += 100.0f;
		}
		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{//���ړ�
			EditPos.x -= 100.0f;
		}
	}

	if(g_Object00[EditIndex].nType != 0)
	{//�I������Ă���I�u�W�F�N�g���ǈȊO�̎�
		if (GetKeyboardPress(DIK_UP) == true)
		{//�O�ړ�
			EditPos.z += 1.0f;
		}
		if (GetKeyboardPress(DIK_DOWN) == true)
		{//���ړ�
			EditPos.z -= 1.0f;
		}
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{//�E�ړ�
			EditPos.x += 1.0f;
		}
		if (GetKeyboardPress(DIK_LEFT) == true)
		{//���ړ�
			EditPos.x -= 1.0f;
		}
		if (GetKeyboardPress(DIK_RSHIFT) == true)
		{//��ړ�
			EditPos.y += 1.0f;
		}
		if (GetKeyboardPress(DIK_RCONTROL) == true)
		{//���ړ�
			EditPos.y -= 1.0f;
		}
	}

	//�I�u�W�F�N�g�̉�]����
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		EditRot.y += 1.57f;

		if (EditRot.y >= 6.28f)
		{
			EditRot.y = 0.0f;
		}
	}

	//�I�u�W�F�N�g�̐؂�ւ�����----------
	if (GetKeyboardTrigger(DIK_9) == true)
	{//�X�L�[�Ŏ��̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditType++;

		if (EditType > OBJECT00_NTYPE_MAX - 1)
		{
			EditType = 0;
		}

		if (EditType == 0)
		{
			EditPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
	if (GetKeyboardTrigger(DIK_8) == true)
	{//�W�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditType--;

		if (EditType < 0)
		{
			EditType = OBJECT00_NTYPE_MAX - 1;
		}

		if (EditType == 0)
		{
			EditPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	//�G�f�B�b�g���[�h�̕ύX���I�u�W�F�N�g�ɔ��f������
	g_Object00[EditIndex].pos = EditPos;
	g_Object00[EditIndex].rot = EditRot;
	g_Object00[EditIndex].nType = EditType;

	//�I�u�W�F�N�g�̍폜����(�d�Ȃ��Ă������)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObject00(EditPos, g_Object00[EditIndex].vtxMin, g_Object00[EditIndex].vtxMax, FALSE_SIZE);
	}

	//�I�u�W�F�N�g�̍폜����(CTRL+Z)----------
	if (GetKeyboardTrigger(DIK_Z) == true && GetKeyboardPress(DIK_LCONTROL) == true)
	{
		FalseObject00();
	}

	//�I�u�W�F�N�g�̐ݒu����----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObject00(g_Object00[EditIndex].pos, g_Object00[EditIndex].move, g_Object00[EditIndex].rot, g_Object00[EditIndex].nType);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̃I�u�W�F�N�g00�̕`�揈��
//====================================================================
void DrawEditObject00(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^


		//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Object00[EditIndex].mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object00[EditIndex].rot.y, g_Object00[EditIndex].rot.x, g_Object00[EditIndex].rot.z);

	D3DXMatrixMultiply(&g_Object00[EditIndex].mtxWorld, &g_Object00[EditIndex].mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Object00[EditIndex].pos.x, g_Object00[EditIndex].pos.y, g_Object00[EditIndex].pos.z);

	D3DXMatrixMultiply(&g_Object00[EditIndex].mtxWorld, &g_Object00[EditIndex].mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Object00[EditIndex].mtxWorld);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^����������
	pMat = (D3DXMATERIAL*)g_pBuffMatObject00[g_Object00[EditIndex].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject00[g_Object00[EditIndex].nType]; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&g_Object00[EditIndex].pMatE.MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureObject00[nCntMat][g_Object00[EditIndex].nType]);

		//�I�u�W�F�N�g00(�p�[�c)�̕`��
		g_pMeshObject00[g_Object00[EditIndex].nType]->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//�I�u�W�F�N�g00�̐ݒ菈��
//====================================================================
void SetObject00(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
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
			g_ObjectCount++;

			//if (g_Exit[nCntObject].nType != 0)
			//{
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
			//}
			//else
			//{
			//	g_Exit[nCntObject].vtxMin = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
			//	g_Exit[nCntObject].vtxMax = D3DXVECTOR3(100.0f, 150.0f, 5.0f);
			//}

			CollisionRotObject00(nCntObject);

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
void FalseObject00(void)
{
	int nCntObject;

	for (nCntObject = MAX_OBJECT00; nCntObject >= 0; nCntObject--)
	{
		if (g_Object00[nCntObject].bUse == true)
		{
			g_Object00[nCntObject].bUse = false;
			g_ObjectCount--;
			break;
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool EditCollisionObject00(D3DXVECTOR3 pPos, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT00; nCntObject++)
	{
		if (g_Object00[nCntObject].bUse == true)
		{
			if (
				pPos.y + Size >= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMin.y
				&& pPos.y - Size <= g_Object00[nCntObject].pos.y + g_Object00[nCntObject].vtxMax.y
				&& pPos.x + Size >= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMin.x
				&& pPos.x - Size <= g_Object00[nCntObject].pos.x + g_Object00[nCntObject].vtxMax.x
				&& pPos.z + Size >= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMin.z
				&& pPos.z - Size <= g_Object00[nCntObject].pos.z + g_Object00[nCntObject].vtxMax.z
				)
			{//�I�u�W�F�N�g���m���d�Ȃ��Ă���
				g_Object00[nCntObject].bUse = false;
				g_ObjectCount--;
				bON = true;
			}
		}
	}
	return bON;
}

//====================================================================
//�I�u�W�F�N�g�̓����蔻�����]�����鏈��
//====================================================================
void CollisionRotObject00(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_Object00[nCnt].vtxMax.z;
	MaxX = g_Object00[nCnt].vtxMax.x;
	MinZ = g_Object00[nCnt].vtxMin.z;
	MinX = g_Object00[nCnt].vtxMin.x;


	if (g_Object00[nCnt].rot.y <= 0.0f)
	{
		g_Object00[nCnt].vtxMax.z = MaxZ;
		g_Object00[nCnt].vtxMax.x = MaxX;
		g_Object00[nCnt].vtxMin.z = MinZ;
		g_Object00[nCnt].vtxMin.x = MinX;
	}
	else if (g_Object00[nCnt].rot.y <= 1.57f)
	{
		g_Object00[nCnt].vtxMax.z = -MinX;
		g_Object00[nCnt].vtxMax.x = MaxZ;
		g_Object00[nCnt].vtxMin.z = -MaxX;
		g_Object00[nCnt].vtxMin.x = MinZ;
	}
	else if (g_Object00[nCnt].rot.y <= 3.14f)
	{
		g_Object00[nCnt].vtxMax.z = -MinZ;
		g_Object00[nCnt].vtxMax.x = -MinX;
		g_Object00[nCnt].vtxMin.z = -MaxZ;
		g_Object00[nCnt].vtxMin.x = -MaxX;
	}
	else if (g_Object00[nCnt].rot.y <= 4.71f)
	{
		g_Object00[nCnt].vtxMax.z = MaxX;
		g_Object00[nCnt].vtxMax.x = -MinZ;
		g_Object00[nCnt].vtxMin.z = MinX;
		g_Object00[nCnt].vtxMin.x =- MaxZ;
	}
}

//====================================================================
//�O�ς��g�����I�u�W�F�N�g�̓����蔻��
//====================================================================
D3DXVECTOR3 CollisionOuterProductObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	//�ړ��x�N�g��������o��
	D3DXVECTOR3 vecMove = *pPos - *pPosOld;
	//���W�ۊǗp
	int nPosCount = 0;
	D3DXVECTOR3 pos[MAX_OBJECT00 * 4] = {};
	for (int nCnt = 0; nCnt < MAX_OBJECT00; nCnt++)
	{
		if (g_Object00[nCnt].bUse == true)
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
					 pos0 = D3DXVECTOR3(g_Object00[nCnt].pos.x + g_Object00[nCnt].vtxMin.x, g_Object00[nCnt].pos.y, g_Object00[nCnt].pos.z + g_Object00[nCnt].vtxMax.z);
					 pos1 = D3DXVECTOR3(g_Object00[nCnt].pos.x + g_Object00[nCnt].vtxMax.x, g_Object00[nCnt].pos.y, g_Object00[nCnt].pos.z + g_Object00[nCnt].vtxMax.z);
					break;
				case 1:
					pos0 = D3DXVECTOR3(g_Object00[nCnt].pos.x + g_Object00[nCnt].vtxMax.x, g_Object00[nCnt].pos.y, g_Object00[nCnt].pos.z + g_Object00[nCnt].vtxMax.z);
					pos1 = D3DXVECTOR3(g_Object00[nCnt].pos.x + g_Object00[nCnt].vtxMax.x, g_Object00[nCnt].pos.y, g_Object00[nCnt].pos.z + g_Object00[nCnt].vtxMin.z);
					break;
				case 2:
					pos0 = D3DXVECTOR3(g_Object00[nCnt].pos.x + g_Object00[nCnt].vtxMax.x, g_Object00[nCnt].pos.y, g_Object00[nCnt].pos.z + g_Object00[nCnt].vtxMin.z);
					pos1 = D3DXVECTOR3(g_Object00[nCnt].pos.x + g_Object00[nCnt].vtxMin.x, g_Object00[nCnt].pos.y, g_Object00[nCnt].pos.z + g_Object00[nCnt].vtxMin.z);
					break;
				case 3:
					pos0 = D3DXVECTOR3(g_Object00[nCnt].pos.x + g_Object00[nCnt].vtxMin.x, g_Object00[nCnt].pos.y, g_Object00[nCnt].pos.z + g_Object00[nCnt].vtxMin.z);
					pos1 = D3DXVECTOR3(g_Object00[nCnt].pos.x + g_Object00[nCnt].vtxMin.x, g_Object00[nCnt].pos.y, g_Object00[nCnt].pos.z + g_Object00[nCnt].vtxMax.z);
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

	return pos[0];
}
//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool CollisionObject00(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

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
				bHit = true;
			}

			if (fabsf(pMove->x) >= fabsf(pMove->z))
			{
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
					bHit = true;
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
					bHit = true;
				}
			}
			else
			{
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
					bHit = true;
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