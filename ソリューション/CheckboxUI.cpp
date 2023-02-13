#include "CheckboxUI.h"
#include "fade.h"
#include "player.h"
#include "PlayNumberSelect.h"

//�}�N����`
#define MAX_CHECK_TEX		(2)				//�`�F�b�N�{�b�N�X�̃e�N�X�`���ő吔

#define CHECKUIPOS_X_1	(30.0f)			//�`�F�b�N�{�b�N�X��UI��X�ʒu1
#define CHECKUIPOS_Y_1	(350.0f)		//�`�F�b�N�{�b�N�X��UI��Y�ʒu1

#define CHECKUIPOS_X_2	(670.0f)		//�`�F�b�N�{�b�N�X��UI��X�ʒu2
#define CHECKUIPOS_Y_2	(700.0f)		//�`�F�b�N�{�b�N�X��UI��Y�ʒu2

#define CHECKUI_WIDTH		(20.0f)			//�`�F�b�N�{�b�N�X��UI�̕�
#define CHECKUI_HEIGHT	(20.0f)			//�`�F�b�N�{�b�N�X��UI�̍���
#define CHECKUI_INTERVAL	(50.0f)			//�`�F�b�N�{�b�N�X��UI���m�̊Ԋu

//�`�F�b�N�{�b�N�XUI�̍\����
typedef struct
{
	D3DXVECTOR3 pos;  //��UI�̈ʒu
	int nCheckUI;  //��UI�̐�
	bool bUse;  //�g���Ă��邩�ǂ���
}CHECKUI;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureCheckUI[MAX_CHECK_TEX] = {};  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCheckUI = NULL; //���_�o�b�t�@�ւ̃|�C���^
CHECKUI g_anCheckUI[NUM_PLAYER];			//�`�F�b�N�{�b�N�X��UI�̏��
int g_NumPlayerCheckUI;

//====================================================================
//�`�F�b�N�{�b�N�X�̏���������
//====================================================================
void InitCheckboxUI(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//�ϐ��錾
	int nCntCheckUI;

	//�O���[�o���錾�̏�����
	g_NumPlayerCheckUI = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\nokey.png",
		&g_pTextureCheckUI[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\getkey.png",
		&g_pTextureCheckUI[1]);

	//��UI�̏���������
	for (nCntCheckUI = 0; nCntCheckUI < PlayNumber.CurrentSelectNumber; nCntCheckUI++)
	{
		if (nCntCheckUI == 0)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_1, CHECKUIPOS_Y_1, 0.0f);  //1�l�ڂ̈ʒu��������
		}

		if (nCntCheckUI == 1)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_2, CHECKUIPOS_Y_1, 0.0f);  //2�l�ڂ̈ʒu��������
		}

		if (nCntCheckUI == 2)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_1, CHECKUIPOS_Y_2, 0.0f);  //3�l�ڂ̈ʒu��������
		}

		if (nCntCheckUI == 3)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_2, CHECKUIPOS_Y_2, 0.0f);  //4�l�ڂ̈ʒu��������
		}
		g_anCheckUI[nCntCheckUI].nCheckUI = 3;		//��UI�̒l��������
		g_anCheckUI[nCntCheckUI].bUse = false;  //�g���Ă��Ȃ����Ƃ�
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCheckUI,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCheckUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y - CHECKUI_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y - CHECKUI_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y + CHECKUI_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y + CHECKUI_HEIGHT, 0.0f);

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
	g_pVtxBuffCheckUI->Unlock();
}

//====================================================================
//�`�F�b�N�{�b�N�X�̏I������
//====================================================================
void UninitCheckboxUI(void)
{
	for (int nCnt = 0; nCnt < MAX_CHECK_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureCheckUI[nCnt] != NULL)
		{
			g_pTextureCheckUI[nCnt]->Release();
			g_pTextureCheckUI[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCheckUI != NULL)
	{
		g_pVtxBuffCheckUI->Release();
		g_pVtxBuffCheckUI = NULL;
	}
}

//====================================================================
//�`�F�b�N�{�b�N�X�̍X�V����
//====================================================================
void UpdateCheckboxUI(void)
{

}

//====================================================================
//�`�F�b�N�{�b�N�X�̕`�揈��
//====================================================================
void DrawCheckboxUI(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCheckUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		if (g_anCheckUI[nCnt].bUse == false)
		{//�����擾���Ă��Ȃ��Ƃ�
		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCheckUI[0]);
		}

		else
		{//�����擾���Ă���Ƃ�
		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCheckUI[1]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}