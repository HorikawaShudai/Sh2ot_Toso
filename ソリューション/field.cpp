////============================
////
////�t�B�[���h����(porygon.cpp)
////Author:���� �F�M
////
////============================
//#include "main.h"
//#include "input.h"
//#include"field.h"
//
////�}�N���ϐ�
//#define MAX_FIELD (512)  //���̍ő吔
//
////�O���[�o��
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;   //���_�o�b�t�@�ւ̃|�C���^
//LPDIRECT3DTEXTURE9 g_pTextureField[MAX_FIELD] = {};        //�e�N�X�`���̃|�C���^
//FIELD g_Field[MAX_FIELD];  // ���̏��
//
//int EditIndexPoly;									//�G�f�B�b�g���[�h�p�̔ԍ�
//D3DXVECTOR3 EditPosPoly;							//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
//float EditWightPoly;								//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
//float EditHeightPoly;								//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
//int g_ObjectFieldCount;								//�I�u�W�F�N�g�̐�
//
////=============================
////�t�B�[���h�̏���������
////=============================
//void InitField(void)
//{
//	int nCnt;
//
//	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice,
//		"Data\\TEXTURE\\thumb_concrete.jpg", 
//		&g_pTextureField[0]);
//
//	//�e��ϐ��̏�����
//	for (nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	{
//		g_Field[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu��������
//		g_Field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//������������
//		g_Field[nCnt].fWigft = 100.0f;						//����������
//		g_Field[nCnt].fHeight = 100.0f;						//������������
//		g_Field[nCnt].bUse = false;							//�g�p���Ă��Ȃ���Ԃɂ���
//	}
//
//	EditIndexPoly = MAX_FIELD - 1;						//�G�f�B�b�g���[�h�p�̔ԍ�
//	EditPosPoly = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
//	EditWightPoly = g_Field[0].fWigft;								//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
//	EditHeightPoly = g_Field[0].fHeight;							//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̈ʒu
//	g_ObjectFieldCount = 0;								//�I�u�W�F�N�g�̐�
//
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffField,
//		NULL);
//
//	VERTEX_3D *pVtx; //���_���W�ւ̃|�C���^
//
//	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
//	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
//	{
//
//		//���_���W�̐ݒ�
//		pVtx[0].pos = D3DXVECTOR3(-g_Field[nCnt].fWigft, 0.0f, +g_Field[nCnt].fHeight);
//		pVtx[1].pos = D3DXVECTOR3(+g_Field[nCnt].fWigft, 0.0f, +g_Field[nCnt].fHeight);
//		pVtx[2].pos = D3DXVECTOR3(-g_Field[nCnt].fWigft, 0.0f, -g_Field[nCnt].fHeight);
//		pVtx[3].pos = D3DXVECTOR3(+g_Field[nCnt].fWigft, 0.0f, -g_Field[nCnt].fHeight);
//
//		//�@���x�N�g���̐ݒ�
//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		//���_�J���[�̐ݒ�
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;
//	}
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffField->Unlock();
//
//}
//
////========================
////�t�B�[���h�̏I������
////========================
//void UninitField(void)
//{
//	for(int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	//�e�N�X�`���̔j��
//	if (g_pTextureField[nCnt] != NULL)
//	{
//		g_pTextureField[nCnt]->Release();
//		g_pTextureField[nCnt] = NULL;
//	}
//}
//
////========================
////�t�B�[���h�̍X�V����
////========================
//void UpdateField(void)
//{
//
//}
//
////========================
////�t�B�[���h�̃G�f�B�b�g���[�h�ł̍X�V����
////========================
//void UpdateEditField(void)
//{
//	if (GetKeyboardPress(DIK_UP) == true)
//	{//�O�ړ�
//		EditPosPoly.z += 1.0f;
//	}
//	if (GetKeyboardPress(DIK_DOWN) == true)
//	{//���ړ�
//		EditPosPoly.z -= 1.0f;
//	}
//	if (GetKeyboardPress(DIK_RIGHT) == true)
//	{//�E�ړ�
//		EditPosPoly.x += 1.0f;
//	}
//	if (GetKeyboardPress(DIK_LEFT) == true)
//	{//���ړ�
//		EditPosPoly.x -= 1.0f;
//	}
//	if (GetKeyboardPress(DIK_RSHIFT) == true)
//	{//��ړ�
//		EditPosPoly.y += 1.0f;
//	}
//	if (GetKeyboardPress(DIK_RCONTROL) == true)
//	{//���ړ�
//		EditPosPoly.y -= 1.0f;
//	}
//
//	if (GetKeyboardTrigger(DIK_6) == true)
//	{//�U�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
//		EditWightPoly++;
//	}
//
//	if (GetKeyboardTrigger(DIK_7) == true)
//	{//�V�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
//		EditWightPoly--;
//	}
//
//	if (GetKeyboardTrigger(DIK_8) == true)
//	{//�W�L�[�őO�̃^�C�v�̃I�u�W�F�N�g�ɂ���
//		EditHeightPoly++;
//	}
//
//	if (GetKeyboardTrigger(DIK_9) == true)
//	{//�X�L�[�Ŏ��̃^�C�v�̃I�u�W�F�N�g�ɂ���
//		EditHeightPoly--;
//	}
//
//
//	//�G�f�B�b�g���[�h�̕ύX���I�u�W�F�N�g�ɔ��f������
//	g_Field[EditIndexPoly].pos = EditPosPoly;
//	g_Field[EditIndexPoly].fWigft = EditWightPoly;
//	g_Field[EditIndexPoly].fHeight = EditHeightPoly;
//
//	//�I�u�W�F�N�g�̍폜����(�d�Ȃ��Ă������)----------
//	if (GetKeyboardTrigger(DIK_BACKSPACE))
//	{
//		EditCollisionField(g_Field[EditIndexPoly].pos, 20.0f);
//	}
//
//	//�I�u�W�F�N�g�̐ݒu����----------
//	if (GetKeyboardTrigger(DIK_RETURN) == true)
//	{
//		SetField(g_Field[EditIndexPoly].pos, g_Field[EditIndexPoly].fWigft, g_Field[EditIndexPoly].fHeight);
//	}
//
//	VERTEX_3D *pVtx; //���_���W�ւ̃|�C���^
//
//	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
//	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
//
//	pVtx += (MAX_FIELD - 1) * 4;
//
//	//���_���W�̐ݒ�
//	pVtx[0].pos = D3DXVECTOR3(-g_Field[EditIndexPoly].fWigft, 0.0f, +g_Field[EditIndexPoly].fHeight);
//	pVtx[1].pos = D3DXVECTOR3(+g_Field[EditIndexPoly].fWigft, 0.0f, +g_Field[EditIndexPoly].fHeight);
//	pVtx[2].pos = D3DXVECTOR3(-g_Field[EditIndexPoly].fWigft, 0.0f, -g_Field[EditIndexPoly].fHeight);
//	pVtx[3].pos = D3DXVECTOR3(+g_Field[EditIndexPoly].fWigft, 0.0f, -g_Field[EditIndexPoly].fHeight);
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffField->Unlock();
//}
//
//
//
////========================
////�t�B�[���h�̕`�揈��
////========================
//void DrawField(void)
//{
//	//�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
//
//	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	{
//		//���[���h�}�g���b�N�X�̏�����
//		D3DXMatrixIdentity(&g_Field[nCnt].mtxWorld);
//
//		//�����𔽉f
//		D3DXMatrixRotationYawPitchRoll(&mtxRot,
//			g_Field[nCnt].rot.y, g_Field[nCnt].rot.x, g_Field[nCnt].rot.z);
//
//		D3DXMatrixMultiply(&g_Field[nCnt].mtxWorld,
//			&g_Field[nCnt].mtxWorld,
//			&mtxRot);
//
//		//�ʒu�𔽉f
//		D3DXMatrixTranslation(&mtxTrans,
//			g_Field[nCnt].pos.x, g_Field[nCnt].pos.y, g_Field[nCnt].pos.z);
//
//		D3DXMatrixMultiply(&g_Field[nCnt].mtxWorld, &g_Field[nCnt].mtxWorld, &mtxTrans);
//
//		//���[���h�}�g���b�N�X�̐ݒ�
//		pDevice->SetTransform(D3DTS_WORLD, &g_Field[nCnt].mtxWorld);
//
//		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));
//
//		//���_�t�H�[�}�b�g�̐ݒ�
//		pDevice->SetFVF(FVF_VERTEX_3D);
//
//		pDevice->SetTexture(0, g_pTextureField[nCnt]);
//
//		if (g_Field[nCnt].bUse == true)
//		{
//			//�t�B�[���h�̕`��
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //�v���~�e�B�u�̎��
//		}
//	}
//}
//
////========================
////�t�B�[���h�̕`�揈��
////========================
//void DrawEditField(void)
//{
//	//�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
//
//		//���[���h�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&g_Field[EditIndexPoly].mtxWorld);
//
//	//�����𔽉f
//	D3DXMatrixRotationYawPitchRoll(&mtxRot,
//		g_Field[EditIndexPoly].rot.y, g_Field[EditIndexPoly].rot.x, g_Field[EditIndexPoly].rot.z);
//
//	D3DXMatrixMultiply(&g_Field[EditIndexPoly].mtxWorld,
//		&g_Field[EditIndexPoly].mtxWorld,
//		&mtxRot);
//
//	//�ʒu�𔽉f
//	D3DXMatrixTranslation(&mtxTrans,
//		g_Field[EditIndexPoly].pos.x, g_Field[EditIndexPoly].pos.y, g_Field[EditIndexPoly].pos.z);
//
//	D3DXMatrixMultiply(&g_Field[EditIndexPoly].mtxWorld, &g_Field[EditIndexPoly].mtxWorld, &mtxTrans);
//
//	//���[���h�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_WORLD, &g_Field[EditIndexPoly].mtxWorld);
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	pDevice->SetTexture(0, g_pTextureField[EditIndexPoly]);
//
//	//�t�B�[���h�̕`��
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, EditIndexPoly * 4, 2); //�v���~�e�B�u�̎��
//}
//
////========================
////�t�B�[���h�̐ݒ菈��
////========================
//void SetField(D3DXVECTOR3 pos, float Wight, float Height)
//{
//	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	{
//		if (g_Field[nCnt].bUse == false)
//		{
//			g_Field[nCnt].pos = pos;	//�ʒu��ݒ�
//			g_Field[nCnt].fWigft = Wight;						//����ݒ�
//			g_Field[nCnt].fHeight = Height;						//������ݒ�
//
//			g_ObjectFieldCount++;
//
//			g_Field[nCnt].bUse = true;							//�g�p���Ă����Ԃɂ���
//
//			break;
//		}
//
//	}
//}
//
////========================
////�t�B�[���h�̍폜����
////========================
//void EditCollisionField(D3DXVECTOR3 pos, float Size)
//{
//	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
//	{
//		if (g_Field[nCnt].bUse == true)
//		{
//			if (
//				pos.y + Size >= g_Field[nCnt].pos.y
//				&& pos.y - Size <= g_Field[nCnt].pos.y
//				&& pos.x + Size >= g_Field[nCnt].pos.x - g_Field[nCnt].fWigft
//				&& pos.x - Size <= g_Field[nCnt].pos.x + g_Field[nCnt].fWigft
//				&& pos.z + Size >= g_Field[nCnt].pos.z - g_Field[nCnt].fHeight
//				&& pos.z - Size <= g_Field[nCnt].pos.z + g_Field[nCnt].fHeight
//				)
//			{//�I�u�W�F�N�g���m���d�Ȃ��Ă���
//				g_Field[nCnt].bUse = false;
//				g_ObjectFieldCount--;
//			}
//		}
//	}
//}
//
//////=============================
//////�t�B�[���h�̈ʒu��^���鏈��
//////=============================
////D3DXVECTOR3 PosField(void)
////{
////	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
////	{
////		return g_Field[nCnt].pos;
////	}
////}
