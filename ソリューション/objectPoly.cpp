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
		g_ObjectPoly[nCnt].fWigft = 100.0f;							//����������
		g_ObjectPoly[nCnt].fHeight = 100.0f;						//������������
		g_ObjectPoly[nCnt].bUse = false;							//�g�p���Ă��Ȃ���Ԃɂ���
	}

	EditIndexPoly = MAX_OBJECTPOLY - 1;								//�G�f�B�b�g���[�h�p�̔ԍ�
	EditPosPoly = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
	EditWightPoly = g_ObjectPoly[0].fWigft;							//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
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
		pVtx[0].pos = D3DXVECTOR3(-g_ObjectPoly[nCnt].fWigft, 0.0f, +g_ObjectPoly[nCnt].fHeight);
		pVtx[1].pos = D3DXVECTOR3(+g_ObjectPoly[nCnt].fWigft, 0.0f, +g_ObjectPoly[nCnt].fHeight);
		pVtx[2].pos = D3DXVECTOR3(-g_ObjectPoly[nCnt].fWigft, 0.0f, -g_ObjectPoly[nCnt].fHeight);
		pVtx[3].pos = D3DXVECTOR3(+g_ObjectPoly[nCnt].fWigft, 0.0f, -g_ObjectPoly[nCnt].fHeight);

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
			pVtx[0].pos = D3DXVECTOR3(-g_ObjectPoly[nCntObjectPoly].fWigft, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, +g_ObjectPoly[nCntObjectPoly].fHeight);
			pVtx[1].pos = D3DXVECTOR3(+g_ObjectPoly[nCntObjectPoly].fWigft, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, +g_ObjectPoly[nCntObjectPoly].fHeight);
			pVtx[2].pos = D3DXVECTOR3(-g_ObjectPoly[nCntObjectPoly].fWigft, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, -g_ObjectPoly[nCntObjectPoly].fHeight);
			pVtx[3].pos = D3DXVECTOR3(+g_ObjectPoly[nCntObjectPoly].fWigft, 100.0f - g_ObjectPoly[nCntObjectPoly].pos.y, -g_ObjectPoly[nCntObjectPoly].fHeight);
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
	g_ObjectPoly[EditIndexPoly].fWigft = EditWightPoly;
	g_ObjectPoly[EditIndexPoly].fHeight = EditHeightPoly;

	//�I�u�W�F�N�g�̍폜����(�d�Ȃ��Ă������)----------
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		EditCollisionObjectPoly(g_ObjectPoly[EditIndexPoly].pos, 20.0f);
	}

	//�I�u�W�F�N�g�̐ݒu����----------
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetObjectPoly(g_ObjectPoly[EditIndexPoly].pos, g_ObjectPoly[EditIndexPoly].fWigft, g_ObjectPoly[EditIndexPoly].fHeight);
	}

	VERTEX_3D *pVtx; //���_���W�ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffObjectPoly->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (MAX_OBJECTPOLY - 1) * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-g_ObjectPoly[EditIndexPoly].fWigft, 0.0f, +g_ObjectPoly[EditIndexPoly].fHeight);
	pVtx[1].pos = D3DXVECTOR3(+g_ObjectPoly[EditIndexPoly].fWigft, 0.0f, +g_ObjectPoly[EditIndexPoly].fHeight);
	pVtx[2].pos = D3DXVECTOR3(-g_ObjectPoly[EditIndexPoly].fWigft, 0.0f, -g_ObjectPoly[EditIndexPoly].fHeight);
	pVtx[3].pos = D3DXVECTOR3(+g_ObjectPoly[EditIndexPoly].fWigft, 0.0f, -g_ObjectPoly[EditIndexPoly].fHeight);

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
			g_ObjectPoly[nCnt].fWigft = Wight;						//����ݒ�
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
				pos.x + Size >= g_ObjectPoly[nCnt].pos.x - g_ObjectPoly[nCnt].fWigft
				&& pos.x - Size <= g_ObjectPoly[nCnt].pos.x + g_ObjectPoly[nCnt].fWigft
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
//�I�u�W�F�N�gPoly�̏���
//====================================================================
ObjectPoly * GetObjectPoly(void)
{
	return &g_ObjectPoly[0];
}
