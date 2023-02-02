//============================
//
//�t�B�[���h����(porygon.cpp)
//Author:���� �F�M
//
//============================
#include "main.h"
#include "input.h"
#include"field.h"

//�}�N���ϐ�
#define MAX_FIELD (4)  //���̍ő吔

#define POS_INSTITUTE_X (1200.0f) //�������e����X�ʒu
#define POS_INSTITUTE_Y (0)		//�������e����Y�ʒu
#define POS_INSTITUTE_Z (800.0f) //�������e����Z�ʒu

#define POS_COLLAPSE_X	(-1000.0f) //����X�ʒu
#define POS_COLLAPSE_Y	(0) //����Y�ʒu
#define POS_COLLAPSE_Z	(-1500.0f) //����Z�ʒu

#define POS_CAMP_X		(1200.0f)   //��������X���W
#define POS_CAMP_Y		(-0)   //��������Y���W
#define POS_CAMP_Z		(-1000.0f)   //��������Z���W

#define POS_OFFICE_X (-1400.0f)	 //�I�t�B�X�̂�X���W
#define POS_OFFICE_Y (0)	 //�I�t�B�X�̃G���A��Y���W
#define POS_OFFICE_Z (100.0f) //�I�t�B�X�̃G���A��Z���W

#define FIELD_WIDTH		(1300.0f) //���̕�
#define FIELD_DEPTH		(1000.0f) //���̉��s

//���̍\����
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 rot; //����
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
}FIELD;

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;   //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureField[MAX_FIELD] = {};        //�e�N�X�`���̃|�C���^
FIELD g_Field[MAX_FIELD];  // ���̏��

//=============================
//�t�B�[���h�̏���������
//=============================
void InitField(void)
{
	int nCnt;

	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\thumb_concrete.jpg", 
		&g_pTextureField[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\collapse_field.jpeg", 
		&g_pTextureField[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\tile.jpg", 
		&g_pTextureField[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\field_office.jpg", 
		&g_pTextureField[3]);

	//�e��ϐ��̏�����
	for (nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		//���̈ʒu
		if (nCnt == 0)
		{//�����G���A
			g_Field[nCnt].pos = D3DXVECTOR3(POS_INSTITUTE_X, POS_INSTITUTE_Y, POS_INSTITUTE_Z); //�ʒu��������

			g_Field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //������������
		}

		if (nCnt == 1)
		{//�I�t�B�X�G���A
			g_Field[nCnt].pos = D3DXVECTOR3(POS_OFFICE_X, POS_OFFICE_Y, POS_OFFICE_Z); //�ʒu��������

			g_Field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //������������
		}

		if (nCnt == 2)
		{//�������e���G���A
			g_Field[nCnt].pos = D3DXVECTOR3(POS_CAMP_X, POS_CAMP_Y, POS_CAMP_Z); //�ʒu��������

			g_Field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //������������
		}

		if (nCnt == 3)
		{//����G���A
			g_Field[nCnt].pos = D3DXVECTOR3(POS_COLLAPSE_X, POS_COLLAPSE_Y, POS_COLLAPSE_Z); //�ʒu��������

			g_Field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //������������
		}
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	VERTEX_3D *pVtx; //���_���W�ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-FIELD_WIDTH, 0.0f, +FIELD_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(+FIELD_WIDTH, 0.0f, +FIELD_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(-FIELD_WIDTH, 0.0f, -FIELD_DEPTH);
		pVtx[3].pos = D3DXVECTOR3(+FIELD_WIDTH, 0.0f, -FIELD_DEPTH);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffField->Unlock();

}

//========================
//�t�B�[���h�̏I������
//========================
void UninitField(void)
{
	for(int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	//�e�N�X�`���̔j��
	if (g_pTextureField[nCnt] != NULL)
	{
		g_pTextureField[nCnt]->Release();
		g_pTextureField[nCnt] = NULL;
	}
}

//========================
//�t�B�[���h�̍X�V����
//========================
void UpdateField(void)
{

}

//========================
//�t�B�[���h�̕`�揈��
//========================
void DrawField(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Field[nCnt].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Field[nCnt].rot.y, g_Field[nCnt].rot.x, g_Field[nCnt].rot.z);

		D3DXMatrixMultiply(&g_Field[nCnt].mtxWorld,
			&g_Field[nCnt].mtxWorld,
			&mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_Field[nCnt].pos.x, g_Field[nCnt].pos.y, g_Field[nCnt].pos.z);

		D3DXMatrixMultiply(&g_Field[nCnt].mtxWorld, &g_Field[nCnt].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Field[nCnt].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->SetTexture(0, g_pTextureField[nCnt]);

		//�t�B�[���h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //�v���~�e�B�u�̎��
	}
}

////=============================
////�t�B�[���h�̈ʒu��^���鏈��
////=============================
//D3DXVECTOR3 PosField(void)
//{
//	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	{
//		return g_Field[nCnt].pos;
//	}
//}
