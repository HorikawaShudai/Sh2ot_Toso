//============================
//
//�t�B�[���h����(porygon.cpp)
//Author:���� �F�M
//
//============================
#include "main.h"
#include "input.h"
#include "objectPoly.h"

//�}�N���ϐ�

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObjectPoly= NULL;   //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureObjectPoly[MAX_OBJECTPOLY] = {};        //�e�N�X�`���̃|�C���^
ObjectPoly g_ObjectPoly[MAX_OBJECTPOLY];  // ���̏��

int EditIndexPoly;									//�G�f�B�b�g���[�h�p�̔ԍ�
D3DXVECTOR3 EditPosPoly;							//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
float EditWightPoly;								//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
float EditHeightPoly;								//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
int g_ObjectObjectPolyCount;						//�I�u�W�F�N�g�̐�

//=============================
//�t�B�[���h�̏���������
//=============================
void InitObjectPoly(void)
{
	int nCnt;

	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾

											 //�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"Data\\TEXTURE\\thumb_concrete.jpg",
	//	&g_pTextureObjectPoly[0]);

	//�e��ϐ��̏�����
	for (nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
	{
		g_ObjectPoly[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu��������
		g_ObjectPoly[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������������
		g_ObjectPoly[nCnt].fWidth = 100.0f;							//����������
		g_ObjectPoly[nCnt].fHeight = 100.0f;						//������������
		g_ObjectPoly[nCnt].bUse = false;							//�g�p���Ă��Ȃ���Ԃɂ���
	}

	EditIndexPoly = MAX_OBJECTPOLY - 1;								//�G�f�B�b�g���[�h�p�̔ԍ�
	EditPosPoly = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
	EditWightPoly = g_ObjectPoly[0].fWidth;							//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
	EditHeightPoly = g_ObjectPoly[0].fHeight;						//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
	g_ObjectObjectPolyCount = 0;									//�I�u�W�F�N�g�̐�

														//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_OBJECTPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffObjectPoly,
		NULL);

	VERTEX_3D *pVtx; //���_���W�ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffObjectPoly->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntObjectPoly= 0; nCntObjectPoly< MAX_OBJECTPOLY; nCntObjectPoly++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_ObjectPoly[nCnt].fWidth, 0.0f, +g_ObjectPoly[nCnt].fHeight);
		pVtx[1].pos = D3DXVECTOR3(+g_ObjectPoly[nCnt].fWidth, 0.0f, +g_ObjectPoly[nCnt].fHeight);
		pVtx[2].pos = D3DXVECTOR3(-g_ObjectPoly[nCnt].fWidth, 0.0f, -g_ObjectPoly[nCnt].fHeight);
		pVtx[3].pos = D3DXVECTOR3(+g_ObjectPoly[nCnt].fWidth, 0.0f, -g_ObjectPoly[nCnt].fHeight);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffObjectPoly->Unlock();

}

//========================
//�t�B�[���h�̏I������
//========================
void UninitObjectPoly(void)
{
	for (int nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
		//�e�N�X�`���̔j��
		if (g_pTextureObjectPoly[nCnt] != NULL)
		{
			g_pTextureObjectPoly[nCnt]->Release();
			g_pTextureObjectPoly[nCnt] = NULL;
		}
}

//========================
//�t�B�[���h�̍X�V����
//========================
void UpdateObjectPoly(void)
{

	VERTEX_3D *pVtx; //���_���W�ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffObjectPoly->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntObjectPoly = 0; nCntObjectPoly< MAX_OBJECTPOLY; nCntObjectPoly++)
	{
		if (g_ObjectPoly[nCntObjectPoly].bUse == true)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_ObjectPoly[nCntObjectPoly].fWidth, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, +g_ObjectPoly[nCntObjectPoly].fHeight);
			pVtx[1].pos = D3DXVECTOR3(+g_ObjectPoly[nCntObjectPoly].fWidth, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, +g_ObjectPoly[nCntObjectPoly].fHeight);
			pVtx[2].pos = D3DXVECTOR3(-g_ObjectPoly[nCntObjectPoly].fWidth, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, -g_ObjectPoly[nCntObjectPoly].fHeight);
			pVtx[3].pos = D3DXVECTOR3(+g_ObjectPoly[nCntObjectPoly].fWidth, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, -g_ObjectPoly[nCntObjectPoly].fHeight);
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffObjectPoly->Unlock();
}

//========================
//�t�B�[���h�̃G�f�B�b�g���[�h�ł̍X�V����
//========================
void UpdateEditObjectPoly(void)
{
	if (GetKeyboardPress(DIK_UP) == true)
	{//�O�ړ�
		EditPosPoly.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{//���ړ�
		EditPosPoly.z -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{//�E�ړ�
		EditPosPoly.x += 1.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//���ړ�
		EditPosPoly.x -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{//��ړ�
		EditPosPoly.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_RCONTROL) == true)
	{//���ړ�
		EditPosPoly.y -= 1.0f;
	}

	if (GetKeyboardPress(DIK_6) == true)
	{//�U�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditWightPoly++;
	}

	if (GetKeyboardPress(DIK_7) == true)
	{//�V�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditWightPoly--;
	}

	if (GetKeyboardPress(DIK_8) == true)
	{//�W�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditHeightPoly++;
	}

	if (GetKeyboardPress(DIK_9) == true)
	{//�X�L�[�Ŏ��̃^�C�v�̃I�u�W�F�N�g�ɂ���
		EditHeightPoly--;
	}


	//�G�f�B�b�g���[�h�̕ύX���I�u�W�F�N�g�ɔ��f������
	g_ObjectPoly[EditIndexPoly].pos = EditPosPoly;
	g_ObjectPoly[EditIndexPoly].fWidth = EditWightPoly;
	g_ObjectPoly[EditIndexPoly].fHeight = EditHeightPoly;

	//�I�u�W�F�N�g�̍폜����(�d�Ȃ��Ă������)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObjectPoly(g_ObjectPoly[EditIndexPoly].pos, 20.0f);
	}

	//�I�u�W�F�N�g�̐ݒu����----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObjectPoly(g_ObjectPoly[EditIndexPoly].pos, g_ObjectPoly[EditIndexPoly].fWidth, g_ObjectPoly[EditIndexPoly].fHeight);
	}

	VERTEX_3D *pVtx; //���_���W�ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffObjectPoly->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (MAX_OBJECTPOLY - 1) * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-g_ObjectPoly[EditIndexPoly].fWidth, 0.0f, +g_ObjectPoly[EditIndexPoly].fHeight);
	pVtx[1].pos = D3DXVECTOR3(+g_ObjectPoly[EditIndexPoly].fWidth, 0.0f, +g_ObjectPoly[EditIndexPoly].fHeight);
	pVtx[2].pos = D3DXVECTOR3(-g_ObjectPoly[EditIndexPoly].fWidth, 0.0f, -g_ObjectPoly[EditIndexPoly].fHeight);
	pVtx[3].pos = D3DXVECTOR3(+g_ObjectPoly[EditIndexPoly].fWidth, 0.0f, -g_ObjectPoly[EditIndexPoly].fHeight);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffObjectPoly->Unlock();
}



//========================
//�t�B�[���h�̕`�揈��
//========================
void DrawObjectPoly(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_ObjectPoly[nCnt].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_ObjectPoly[nCnt].rot.y, g_ObjectPoly[nCnt].rot.x, g_ObjectPoly[nCnt].rot.z);

		D3DXMatrixMultiply(&g_ObjectPoly[nCnt].mtxWorld,
			&g_ObjectPoly[nCnt].mtxWorld,
			&mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_ObjectPoly[nCnt].pos.x, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z);

		D3DXMatrixMultiply(&g_ObjectPoly[nCnt].mtxWorld, &g_ObjectPoly[nCnt].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_ObjectPoly[nCnt].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffObjectPoly, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->SetTexture(0, g_pTextureObjectPoly[nCnt]);
		if (g_ObjectPoly[nCnt].bUse == true)
		{
			//�t�B�[���h�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //�v���~�e�B�u�̎��
		}
	}
}

//========================
//�t�B�[���h�̃G�f�B�b�g���[�h�ł̕`�揈��
//========================
void DrawEditObjectPoly(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_ObjectPoly[EditIndexPoly].mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_ObjectPoly[EditIndexPoly].rot.y, g_ObjectPoly[EditIndexPoly].rot.x, g_ObjectPoly[EditIndexPoly].rot.z);

	D3DXMatrixMultiply(&g_ObjectPoly[EditIndexPoly].mtxWorld,
		&g_ObjectPoly[EditIndexPoly].mtxWorld,
		&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		g_ObjectPoly[EditIndexPoly].pos.x, g_ObjectPoly[EditIndexPoly].pos.y, g_ObjectPoly[EditIndexPoly].pos.z);

	D3DXMatrixMultiply(&g_ObjectPoly[EditIndexPoly].mtxWorld, &g_ObjectPoly[EditIndexPoly].mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_ObjectPoly[EditIndexPoly].mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffObjectPoly, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, g_pTextureObjectPoly[EditIndexPoly]);

	//�t�B�[���h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, EditIndexPoly * 4, 2); //�v���~�e�B�u�̎��
}

//========================
//�t�B�[���h�̐ݒ菈��
//========================
void SetObjectPoly(D3DXVECTOR3 pos, float Wight, float Height)
{
	for (int nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
	{
		if (g_ObjectPoly[nCnt].bUse == false)
		{
			g_ObjectPoly[nCnt].pos = pos;	//�ʒu��ݒ�
			g_ObjectPoly[nCnt].fWidth = Wight;						//����ݒ�
			g_ObjectPoly[nCnt].fHeight = Height;						//������ݒ�

			g_ObjectObjectPolyCount++;

			g_ObjectPoly[nCnt].bUse = true;							//�g�p���Ă����Ԃɂ���

			break;
		}

	}
}

//========================
//�t�B�[���h�̍폜����
//========================
void EditCollisionObjectPoly(D3DXVECTOR3 pos, float Size)
{
	for (int nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
	{
		if (g_ObjectPoly[nCnt].bUse == true)
		{
			if (
				pos.x + Size >= g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWidth
				&& pos.x - Size <= g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWidth
				&& pos.z + Size >= g_ObjectPoly[nCnt].pos.z - g_ObjectPoly[nCnt].fHeight
				&& pos.z - Size <= g_ObjectPoly[nCnt].pos.z + g_ObjectPoly[nCnt].fHeight
				)
			{//�I�u�W�F�N�g���m���d�Ȃ��Ă���
				g_ObjectPoly[nCnt].bUse = false;
				g_ObjectObjectPolyCount--;
			}
		}
	}
}

//====================================================================
//�O�ς��g�����I�u�W�F�N�g�̓����蔻��
//====================================================================
D3DXVECTOR3 CollisionOuterProductObjectPoly(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	//�ړ��x�N�g��������o��
	D3DXVECTOR3 vecMove = *pPos - *pPosOld;
	//���W�ۊǗp
	int nPosCount = 0;
	D3DXVECTOR3 pos[MAX_OBJECTPOLY * 4] = {};
	for (int nCnt = 0; nCnt < MAX_OBJECTPOLY; nCnt++)
	{
		if (g_ObjectPoly[nCnt].bUse == true)
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
					pos0 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z + g_ObjectPoly[nCnt].fHeight);
					pos1 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z + g_ObjectPoly[nCnt].fHeight);
					break;
				case 1:
					pos0 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z + g_ObjectPoly[nCnt].fHeight);
					pos1 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z - g_ObjectPoly[nCnt].fHeight);
					break;
				case 2:
					pos0 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z - g_ObjectPoly[nCnt].fHeight);
					pos1 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z - g_ObjectPoly[nCnt].fHeight);
					break;
				case 3:
					pos0 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z - g_ObjectPoly[nCnt].fHeight);
					pos1 = D3DXVECTOR3(g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWidth, g_ObjectPoly[nCnt].pos.y, g_ObjectPoly[nCnt].pos.z + g_ObjectPoly[nCnt].fHeight);
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
//�|���S���Ƃ̓����蔻�菈��
//====================================================================
bool CollisionObjectPoly(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max, float Size)
{
	bool bHit = false;

	for (int nCntObject = 0; nCntObject < MAX_OBJECTPOLY; nCntObject++)
	{
		if (g_ObjectPoly[nCntObject].bUse == true)
		{
			if (
				(
				pPos->x + Size >= g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth &&
				pPos->x - Size <= g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth &&
				pPos->z + Size >= g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight &&
				pPos->z - Size <= g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight
				))
			{//�ǂƃv���C���[����������(X��)
				pPos->y = pPosOld->y;
				pMove->y = 0.0f;
				bHit = true;
			}

			if (fabsf(pMove->x) >= fabsf(pMove->z))
			{
				if (
					(
						pPos->z + Size >= g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight && pPosOld->z + Size < g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight ||
						pPos->z - Size <= g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight && pPosOld->z - Size > g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight) &&
					pPos->x + Size >= g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth &&
					pPos->x - Size <= g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth 
					)
				{//�ǂƃv���C���[����������(Z��)
					pPos->z = pPosOld->z;
					pMove->z = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->x + Size >= g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth && pPosOld->x + Size < g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth ||
						pPos->x - Size <= g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth && pPosOld->x - Size > g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth) &&
					pPos->z + Size >= g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight &&
					pPos->z - Size <= g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight 
					
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
						pPos->x + Size >= g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth && pPosOld->x + Size < g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth ||
						pPos->x - Size <= g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth && pPosOld->x - Size > g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth) &&
					pPos->z + Size >= g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight &&
					pPos->z - Size <= g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight 
					)
				{//�ǂƃv���C���[����������(X��)
					pPos->x = pPosOld->x;
					pMove->x = 0.0f;
					bHit = true;
				}

				if (
					(
						pPos->z + Size >= g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight && pPosOld->z + Size < g_ObjectPoly[nCntObject].pos.z - g_ObjectPoly[nCntObject].fHeight ||
						pPos->z - Size <= g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight && pPosOld->z - Size > g_ObjectPoly[nCntObject].pos.z + g_ObjectPoly[nCntObject].fHeight) &&
					pPos->x + Size >= g_ObjectPoly[nCntObject].pos.x - g_ObjectPoly[nCntObject].fWidth &&
					pPos->x - Size <= g_ObjectPoly[nCntObject].pos.x + g_ObjectPoly[nCntObject].fWidth 
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
//�I�u�W�F�N�gPoly�̏���
//====================================================================
ObjectPoly * GetObjectPoly(void)
{
	return &g_ObjectPoly[0];
}
