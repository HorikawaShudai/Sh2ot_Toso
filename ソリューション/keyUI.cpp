//========================================================================================
//
// ����UI�̏���[KeyUI.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "KeyUI.h"
#include "fade.h"
#include "keyUI.h"
#include "player.h"
#include "PlayNumberSelect.h"

//�}�N����`
#define MAX_KEY_TEX		(2)				//���̃e�N�X�`���ő吔

#define KEYUIPOS_X_1	(130.0f)			//��UI��X�ʒu1
#define KEYUIPOS_Y_1	(50.0f)			//��UI��Y�ʒu1

#define KEYUIPOS_X_2	(780.0f)		//��UI��X�ʒu2
#define KEYUIPOS_Y_2	(400.0f)		//��UI��Y�ʒu2

#define KEYUI_WIDTH		(30.0f)			//��UI�̕�
#define KEYUI_HEIGHT	(20.0f)			//��UI�̍���
#define KEYUI_INTERVAL	(50.0f)			//��UI���m�̊Ԋu

//��UI�̍\����
typedef struct
{
	D3DXVECTOR3 pos;  //��UI�̈ʒu
	int nKeyUI;  //��UI�̐�
	bool bUse;  //�g���Ă��邩�ǂ���
}KEYUI;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureKeyUI[MAX_KEY_TEX] = {};  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKeyUI = NULL; //���_�o�b�t�@�ւ̃|�C���^
KEYUI g_anKeyUI[NUM_PLAYER];			//��UI�̏��
int g_NumPlayerKeyUI;

//=============================
//  ��UI�̏�����
//=============================
void InitKeyUI(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//�ϐ��錾
	int nCntKeyUI;

	//�O���[�o���錾�̏�����
	g_NumPlayerKeyUI = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\NoCardKey.jpg",
		&g_pTextureKeyUI[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\CardKey.jpg",
		&g_pTextureKeyUI[1]);

	//��UI�̏���������
	for (nCntKeyUI = 0; nCntKeyUI < PlayNumber.CurrentSelectNumber; nCntKeyUI++)
	{
		if (nCntKeyUI == 0)
		{
			g_anKeyUI[nCntKeyUI].pos = D3DXVECTOR3(KEYUIPOS_X_1, KEYUIPOS_Y_1, 0.0f);  //1�l�ڂ̈ʒu��������
		}

		if (nCntKeyUI == 1)
		{
			g_anKeyUI[nCntKeyUI].pos = D3DXVECTOR3(KEYUIPOS_X_2, KEYUIPOS_Y_1, 0.0f);  //2�l�ڂ̈ʒu��������
		}

		if (nCntKeyUI == 2)
		{
			g_anKeyUI[nCntKeyUI].pos = D3DXVECTOR3(KEYUIPOS_X_1, KEYUIPOS_Y_2, 0.0f);  //3�l�ڂ̈ʒu��������
		}

		if (nCntKeyUI == 3)
		{
			g_anKeyUI[nCntKeyUI].pos = D3DXVECTOR3(KEYUIPOS_X_2, KEYUIPOS_Y_2, 0.0f);  //4�l�ڂ̈ʒu��������
		}
		g_anKeyUI[nCntKeyUI].nKeyUI = 3;		//��UI�̒l��������
		g_anKeyUI[nCntKeyUI].bUse = false;  //�g���Ă��Ȃ����Ƃ�
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffKeyUI,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKeyUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_anKeyUI[nCnt].pos.x - KEYUI_WIDTH , g_anKeyUI[nCnt].pos.y - KEYUI_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_anKeyUI[nCnt].pos.x + KEYUI_WIDTH , g_anKeyUI[nCnt].pos.y - KEYUI_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_anKeyUI[nCnt].pos.x - KEYUI_WIDTH , g_anKeyUI[nCnt].pos.y + KEYUI_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_anKeyUI[nCnt].pos.x + KEYUI_WIDTH , g_anKeyUI[nCnt].pos.y + KEYUI_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffKeyUI->Unlock();
}

//=====================
//��UI�̏I������
//=====================
void UninitKeyUI(void)
{
	for (int nCnt = 0; nCnt < MAX_KEY_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureKeyUI[nCnt] != NULL)
		{
			g_pTextureKeyUI[nCnt]->Release();
			g_pTextureKeyUI[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffKeyUI != NULL)
	{
		g_pVtxBuffKeyUI->Release();
		g_pVtxBuffKeyUI = NULL;
	}
}

//==========================
//��UI�̍X�V����
//=========================
void UpdateKeyUI(void)
{

}

//======================
//��UI�̕`�揈��
//======================
void DrawKeyUI(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffKeyUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		if (g_anKeyUI[nCnt].bUse == false)
		{//�����擾���Ă��Ȃ��Ƃ�
		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureKeyUI[0]);
		}

		else
		{//�����擾���Ă���Ƃ�
		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureKeyUI[1]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//===================================
//��UI�̐ݒ菈��
//===================================
void SetKeyUI(int nPlayer, bool SetKey)
{
	g_anKeyUI[nPlayer].bUse = SetKey;
}
