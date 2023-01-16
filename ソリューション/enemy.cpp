#include "main.h"
#include "ENEMY.h"
#include "camera.h"
#include "input.h"

#define ENEMY_LIFE (7)		//�I�u�W�F�N�g�̗̑�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureENEMY[64][ENEMY_NTYPE_MAX] = {};	//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshENEMY[ENEMY_NTYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatENEMY[ENEMY_NTYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatENEMY[ENEMY_NTYPE_MAX] = {};						//�}�e���A���̐�

ENEMY g_Enemy[MAX_ENEMY];					//�G�̏��
int EditIndexEnemy;								//�G�f�B�b�g���[�h�p�̔ԍ�

const char *c_apModelEnemy[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\wall.x",
	"Data\\MODEL\\pc.x",
	"Data\\MODEL\\desk.x",
	"Data\\MODEL\\fan.x",
	"Data\\MODEL\\locker.x",
	"Data\\MODEL\\whiteboard.x",
	"Data\\MODEL\\officechair.x",
};


//====================================================================
//�G�̏���������
//====================================================================
void InitEnemy(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		g_Enemy[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Enemy[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Enemy[nCntObject].bUse = false;
		g_Enemy[nCntObject].nType = ENEMY_NTYPE00;
		g_Enemy[nCntObject].aModel[0] = {};
	}
	EditIndexEnemy = 0;

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_NTYPE_MAX; nCntEnemy++)
	{
		D3DXLoadMeshFromX(c_apModelEnemy[nCntEnemy],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatENEMY[nCntEnemy],
			NULL,
			&g_dwNumMatENEMY[nCntEnemy],
			&g_pMeshENEMY[nCntEnemy]);
	}

	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < ENEMY_NTYPE_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureENEMY[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//�G�̏I������
//====================================================================
void UninitEnemy(void)
{
	for (int nCntNumObject = 0; nCntNumObject < ENEMY_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureENEMY[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureENEMY[nCntTex][nCntNumObject]->Release();
				g_pTextureENEMY[nCntTex][nCntNumObject] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_pMeshENEMY[nCntNumObject] != NULL)
		{
			g_pMeshENEMY[nCntNumObject]->Release();
			g_pMeshENEMY[nCntNumObject] = NULL;
		}

		//�}�e���A���̔j��
		if (g_pBuffMatENEMY[nCntNumObject] != NULL)
		{
			g_pBuffMatENEMY[nCntNumObject]->Release();
			g_pBuffMatENEMY[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//�G�̍X�V����
//====================================================================
void UpdateEnemy(void)
{
	for (int nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == true)
		{

		}
	}
}

//====================================================================
//�G�̕`�揈��
//====================================================================
void DrawEnemy(void)
{
	int nCntObject;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^



	for (nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		D3DXMATRIX mtxParent;
		D3DXMATRIX mtxRotModel, mtxTransModel; //�v�Z�p�}�g���N�X

		//�p�[�c�̃}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Enemy[nCntObject].aModel[nCntObject].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[nCntObject].aModel[nCntObject].rot.y, g_Enemy[nCntObject].aModel[nCntObject].rot.x, g_Enemy[nCntObject].aModel[nCntObject].rot.z);
		D3DXMatrixMultiply(&g_Enemy[nCntObject].mtx, &g_Enemy[nCntObject].mtx, &mtxRotModel);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_Enemy[nCntObject].aModel[nCntObject].pos.x, g_Enemy[nCntObject].aModel[nCntObject].pos.y, g_Enemy[nCntObject].aModel[nCntObject].pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCntObject].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObject].aModel[nCntObject].mtxWorld, &mtxTransModel);

		if (g_Enemy[nCntObject].aModel[nCntObject].nIdxModelParent != -1)
		{
			mtxParent = g_Enemy[nCntObject].aModel[g_Enemy[nCntObject].aModel[nCntObject].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Enemy[nCntObject].mtx;
		}

		//�Z�o�����}�g���N�X���������킹��
		D3DXMatrixMultiply(&g_Enemy[nCntObject].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObject].aModel[nCntObject].mtxWorld, &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntObject].aModel[nCntObject].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^����������
			pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[g_Enemy[nCntObject].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[g_Enemy[nCntObject].nType]; nCntMat++)
			{

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Enemy[nCntObject].bUse == true)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureENEMY[nCntMat][g_Enemy[nCntObject].nType]);

					//�G(�p�[�c)�̕`��
					g_pMeshENEMY[g_Enemy[nCntObject].nType]->DrawSubset(nCntMat);
				}
			}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̓G�̍X�V����
//====================================================================
void UpdateEditEnemy(void)
{
	//�L�[�{�[�h�̈ړ�����
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Enemy[EditIndexEnemy].pos.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Enemy[EditIndexEnemy].pos.z -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Enemy[EditIndexEnemy].pos.x += 1.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Enemy[EditIndexEnemy].pos.x -= 1.0f;
	}

	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_Enemy[EditIndexEnemy].rot.y += 1.57f;

		if (g_Enemy[EditIndexEnemy].rot.y >= 6.28f)
		{
			g_Enemy[EditIndexEnemy].rot.y = 0.0f;
		}
	}

	if (GetKeyboardTrigger(DIK_RSHIFT) == true)
	{
		g_Enemy[EditIndexEnemy].nType++;

		if (g_Enemy[EditIndexEnemy].nType > ENEMY_NTYPE_MAX - 1)
		{
			g_Enemy[EditIndexEnemy].nType = 0;
		}
	}
	if (GetKeyboardTrigger(DIK_RCONTROL) == true)
	{
		g_Enemy[EditIndexEnemy].nType--;

		if (g_Enemy[EditIndexEnemy].nType < 0)
		{
			g_Enemy[EditIndexEnemy].nType = ENEMY_NTYPE_MAX - 1;
		}
	}


	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetEnemy(g_Enemy[EditIndexEnemy].pos, g_Enemy[EditIndexEnemy].move, g_Enemy[EditIndexEnemy].rot, g_Enemy[EditIndexEnemy].nType);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̓G�̕`�揈��
//====================================================================
void DrawEditEnemy(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^


		//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Enemy[EditIndexEnemy].mtx);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[EditIndexEnemy].rot.y, g_Enemy[EditIndexEnemy].rot.x, g_Enemy[EditIndexEnemy].rot.z);

	D3DXMatrixMultiply(&g_Enemy[EditIndexEnemy].mtx, &g_Enemy[EditIndexEnemy].mtx, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Enemy[EditIndexEnemy].pos.x, g_Enemy[EditIndexEnemy].pos.y, g_Enemy[EditIndexEnemy].pos.z);

	D3DXMatrixMultiply(&g_Enemy[EditIndexEnemy].mtx, &g_Enemy[EditIndexEnemy].mtx, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[EditIndexEnemy].mtx);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^����������
	pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[g_Enemy[EditIndexEnemy].nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[g_Enemy[EditIndexEnemy].nType]; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureENEMY[nCntMat][g_Enemy[EditIndexEnemy].nType]);

		//�G(�p�[�c)�̕`��
		g_pMeshENEMY[g_Enemy[EditIndexEnemy].nType]->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//�G�̐ݒ菈��
//====================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == false)
		{
			g_Enemy[nCntObject].pos = pos;
			g_Enemy[nCntObject].posOld = pos;
			g_Enemy[nCntObject].move = move;
			g_Enemy[nCntObject].rot = rot;
			g_Enemy[nCntObject].nType = nType;

			//switch (nType)
			//{
			//case 0:
			//	g_Enemy[nCntObject].nType = ENEMY_NTYPE00;
			//	break;
			//}

			g_Enemy[nCntObject].bUse = true;
			EditIndexEnemy++;

			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

			//���_��������
			nNumVtx = g_pMeshENEMY[nType]->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y������
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshENEMY[nType]->GetFVF());

			//���_�o�b�t�@�����b�N
			g_pMeshENEMY[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				if (g_Enemy[nCntObject].vtxMin.x > vtx.x)
				{
					g_Enemy[nCntObject].vtxMin.x = vtx.x;
				}
				if (g_Enemy[nCntObject].vtxMin.y > vtx.y)
				{
					g_Enemy[nCntObject].vtxMin.y = vtx.y;
				}
				if (g_Enemy[nCntObject].vtxMin.z > vtx.z)
				{
					g_Enemy[nCntObject].vtxMin.z = vtx.z;
				}

				if (g_Enemy[nCntObject].vtxMax.x < vtx.x)
				{
					g_Enemy[nCntObject].vtxMax.x = vtx.x;
				}
				if (g_Enemy[nCntObject].vtxMax.y < vtx.y)
				{
					g_Enemy[nCntObject].vtxMax.y = vtx.y;
				}
				if (g_Enemy[nCntObject].vtxMax.z < vtx.z)
				{
					g_Enemy[nCntObject].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pMeshENEMY[nType]->UnlockVertexBuffer();

			CollisionRotEnemy(nCntObject);

			break;
		}
	}
}

//====================================================================
//�I�u�W�F�N�g�̓����蔻�����]�����鏈��
//====================================================================
void CollisionRotEnemy(int nCnt)
{
	float MaxZ, MaxX, MinZ, MinX;

	MaxZ = g_Enemy[nCnt].vtxMax.z;
	MaxX = g_Enemy[nCnt].vtxMax.x;
	MinZ = g_Enemy[nCnt].vtxMin.z;
	MinX = g_Enemy[nCnt].vtxMin.x;


	if (g_Enemy[nCnt].rot.y <= 0.0f)
	{
		g_Enemy[nCnt].vtxMax.z = MaxZ;
		g_Enemy[nCnt].vtxMax.x = MaxX;
		g_Enemy[nCnt].vtxMin.z = MinZ;
		g_Enemy[nCnt].vtxMin.x = MinX;
	}
	else if (g_Enemy[nCnt].rot.y <= 1.57f)
	{

	}
	else if (g_Enemy[nCnt].rot.y <= 3.14f)
	{

	}
	else if (g_Enemy[nCnt].rot.y <= 4.71f)
	{

	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bON = true;

	for (int nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == true)
		{
			if (
				(
				pPos->y + max.y >= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y && pPosOld->y + max.y< g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y ||
				pPos->y + min.y <= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y && pPosOld->y + min.y > g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y) &&
				pPos->x + Size >= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x &&
				pPos->z + Size >= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bON = false;
			}

			if (
				(
				pPos->z + Size >= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z && pPosOld->z + Size < g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z ||
				pPos->z - Size <= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z && pPosOld->z - Size > g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z) &&
				pPos->x + Size >= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x &&
				pPos->x - Size <= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x &&
				pPos->y + max.y >= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y&&
				pPos->y + min.y <= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y
				)
			{//�ǂƃv���C���[����������(Z��)
				pPos->z = pPosOld->z;
				pMove->z = 0.0f;
			}

			if (
				(
				pPos->x + Size >= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x && pPosOld->x + Size < g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x ||
				pPos->x - Size <= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x && pPosOld->x - Size > g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x) &&
				pPos->z + Size >= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z &&
				pPos->z - Size <= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z &&
				pPos->y + max.y >= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y &&
				pPos->y + min.y <= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y
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
void CollisionEnemyShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y &&
				pPos->y <= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y &&
				pPos->x >= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x &&
				pPos->x <= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x &&
				pPos->z >= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z &&
				pPos->z <= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = g_Enemy[nCntObject].vtxMax.y;
			}
		}
	}
}

//====================================================================
//�G�̏���
//====================================================================
ENEMY * GetEnemy(void)
{
	return &g_Enemy[0];
}