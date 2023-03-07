#include "main.h"
#include "resultUI.h"
#include "numberUI.h"
#include "game.h"

//�}�N����`
#define NUM_SSUI		(6)	//GAMEUI�̎�ސ�
#define NUM_UITEX		(3)	//�e�N�X�`������

#define POS_RESULT_BG_X			(640.0f)	//�u�w�i�v��X���W�̈ʒu
#define POS_RESULT_BG_Y			(360.0f)	//�u�w�i�v��Y���W�̈ʒu
#define SIZE_RESULT_BG_X		(640.0f)	//�u�w�i�v�̕�
#define SIZE_RESULT_BG_Y		(360.0f)	//�u�w�i�v�̍���

#define POS_TEXT_BG_X			(640.0f)	//�u�e�L�X�g�v��X���W�̈ʒu
#define POS_TEXT_BG_Y			(400.0f)	//�u�e�L�X�g�v��Y���W�̈ʒu
#define SIZE_TEXT_BG_X			(450.0f)	//�u�e�L�X�g�v�̕�
#define SIZE_TEXT_BG_Y			(100.0f)	//�u�e�L�X�g�v�̍���

#define POS_PUSHKEY_BG_X		(1040.0f)	//�uPUSH TO BUTTON�v��X���W�̈ʒu
#define POS_PUSHKEY_BG_Y		(640.0f)	//�uPUSH TO BUTTON�v��Y���W�̈ʒu
#define SIZE_PUSHKEY_BG_X		(150.0f)	//�uPUSH TO BUTTON�v�̕�
#define SIZE_PUSHKEY_BG_Y		(50.0f)		//�uPUSH TO BUTTON�v�̍���

#define POS_KUROYANAGI_BG_X		(310.0f)	//�uKUROYANAGI�v��X���W�̈ʒu
#define POS_KUROYANAGI_BG_Y		(410.0f)	//�uKUROYANAGI�v��Y���W�̈ʒu
#define SIZE_KUROYANAGI_BG_X	(410.0f)	//�uKUROYANAGI�v�̕�
#define SIZE_KUROYANAGI_BG_Y	(310.0f)	//�uKUROYANAGI�v�̍���

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureResultUI[NUM_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultUI = NULL;		//���_�o�b�t�@�ւ̃|�C���^
bool bUseResultUI[NUM_SSUI];		//���_�o�b�t�@�ւ̃|�C���^
bool g_bStageClear_Result;
D3DXCOLOR g_FadeColor;
D3DXCOLOR g_KeepColor;

//�v���g�^�C�v�錾
void FadeUi(void);

//====================================================================
//�^�C�g����ʂ̏���������
//====================================================================
void InitResultUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RESULT\\Text.png",
		&g_apTextureResultUI[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RESULT\\PleazeButton.png",
		&g_apTextureResultUI[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RESULT\\kuroyanagi00.png",
		&g_apTextureResultUI[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultUI,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^������
	g_pVtxBuffResultUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_RESULT_BG_X - SIZE_RESULT_BG_X, POS_RESULT_BG_Y - SIZE_RESULT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_RESULT_BG_X + SIZE_RESULT_BG_X, POS_RESULT_BG_Y - SIZE_RESULT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_RESULT_BG_X - SIZE_RESULT_BG_X, POS_RESULT_BG_Y + SIZE_RESULT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_RESULT_BG_X + SIZE_RESULT_BG_X, POS_RESULT_BG_Y + SIZE_RESULT_BG_Y, 0.0f);
			break;

		case 1:
		case 2:
		case 3:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_TEXT_BG_X - SIZE_TEXT_BG_X, POS_TEXT_BG_Y - SIZE_TEXT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_TEXT_BG_X + SIZE_TEXT_BG_X, POS_TEXT_BG_Y - SIZE_TEXT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_TEXT_BG_X - SIZE_TEXT_BG_X, POS_TEXT_BG_Y + SIZE_TEXT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_TEXT_BG_X + SIZE_TEXT_BG_X, POS_TEXT_BG_Y + SIZE_TEXT_BG_Y, 0.0f);
			break;

		case 4:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_PUSHKEY_BG_X - SIZE_PUSHKEY_BG_X, POS_PUSHKEY_BG_Y - SIZE_PUSHKEY_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PUSHKEY_BG_X + SIZE_PUSHKEY_BG_X, POS_PUSHKEY_BG_Y - SIZE_PUSHKEY_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PUSHKEY_BG_X - SIZE_PUSHKEY_BG_X, POS_PUSHKEY_BG_Y + SIZE_PUSHKEY_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PUSHKEY_BG_X + SIZE_PUSHKEY_BG_X, POS_PUSHKEY_BG_Y + SIZE_PUSHKEY_BG_Y, 0.0f);
			break;

		case 5:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_KUROYANAGI_BG_X - SIZE_KUROYANAGI_BG_X, POS_KUROYANAGI_BG_Y - SIZE_KUROYANAGI_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_KUROYANAGI_BG_X + SIZE_KUROYANAGI_BG_X, POS_KUROYANAGI_BG_Y - SIZE_KUROYANAGI_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_KUROYANAGI_BG_X - SIZE_KUROYANAGI_BG_X, POS_KUROYANAGI_BG_Y + SIZE_KUROYANAGI_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_KUROYANAGI_BG_X + SIZE_KUROYANAGI_BG_X, POS_KUROYANAGI_BG_Y + SIZE_KUROYANAGI_BG_Y, 0.0f);
			break;
		}

		if (nCntBG == 0)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
		}
		else
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		if (nCntBG > 0 && nCntBG < 4)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + ((nCntBG - 1)*0.33333f));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + ((nCntBG - 1)*0.33333f));
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.33333f + ((nCntBG - 1)*0.33333f));
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.33333f + ((nCntBG - 1)*0.33333f));
		}
		else
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultUI->Unlock();

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//UI�̕\���ݒ�
		bUseResultUI[nCntBG] = false;
	}
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitResultUI(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_UITEX; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureResultUI[nCntBG] != NULL)
		{
			g_apTextureResultUI[nCntBG]->Release();
			g_apTextureResultUI[nCntBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResultUI != NULL)
	{
		g_pVtxBuffResultUI->Release();
		g_pVtxBuffResultUI = NULL;
	}
}

//====================================================================
//�^�C�g����ʂ̍X�V����
//====================================================================
void UpdateResultUI(void)
{
	if (g_bStageClear_Result == true)
	{
		FadeUi();
	}
}

//====================================================================
//�^�C�g����ʂ̕`�揈��
//====================================================================
void DrawResultUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		switch (nCntBG)
		{
		case 0:
			pDevice->SetTexture(0, NULL);
			break;
		case 1:
		case 2:
		case 3:
			pDevice->SetTexture(0, g_apTextureResultUI[0]);
			break;
		case 4:
			pDevice->SetTexture(0, g_apTextureResultUI[1]);
			break;
		case 5:
			pDevice->SetTexture(0, g_apTextureResultUI[2]);
			break;

		}
		if (bUseResultUI[nCntBG] == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntBG,						//�v���~�e�B�u(�|���S��)��
				2);
		}
	}
}
//====================================================================
//�����L���OUI�̐ݒ菈��
//====================================================================
void SetResultUI(RESULTUI SetClear)
{

	switch (SetClear)
	{
	case RESULTUI_ONLY:				//1�l����(��l�v���C������)
		bUseResultUI[0] = true;
		bUseResultUI[1] = false;
		bUseResultUI[2] = false;
		bUseResultUI[3] = true;
		bUseResultUI[4] = true;
		bUseResultUI[5] = true;

		break;

	case RESULTUI_TWO:				//��l�ȏ�S����������
		bUseResultUI[0] = true;
		bUseResultUI[1] = false;
		bUseResultUI[2] = true;
		bUseResultUI[3] = false;
		bUseResultUI[4] = true;
		bUseResultUI[5] = true;

		break;

	case RESULTUI_PERFECT:			//�S�������̏ꍇ
		bUseResultUI[0] = true;
		bUseResultUI[1] = true;
		bUseResultUI[2] = false;
		bUseResultUI[3] = false;
		bUseResultUI[4] = true;
		bUseResultUI[5] = true;

		break;
	}
}

//====================================================================
//UI�̑J�ڏ���
//====================================================================
void FadeUi(void)
{
	g_KeepColor.a -= g_FadeColor.a;
	if (g_KeepColor.a<0.0f || g_KeepColor.a>1.0f)
	{
		g_FadeColor *= -1.0f;
	}

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffResultUI->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 16;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(g_KeepColor);
	pVtx[1].col = D3DXCOLOR(g_KeepColor);
	pVtx[2].col = D3DXCOLOR(g_KeepColor);
	pVtx[3].col = D3DXCOLOR(g_KeepColor);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultUI->Unlock();
}


//====================================================================
//�擾����
//====================================================================
bool GetbResultUi(void)
{
	return g_bStageClear_Result;
}

//====================================================================
//�\���ݒ菈��
//====================================================================
void SetbResultUi(bool bReseultUi)
{
	int nClear = GetClear();
	switch (bReseultUi)
	{
	case true:
		
		switch (nClear)
		{
		case 1:
			SetResultUI(RESULTUI_PERFECT);
			break;
		case 2:
			SetResultUI(RESULTUI_TWO);
			break;
		case 3:
			SetResultUI(RESULTUI_ONLY);
			break;
		}
		g_bStageClear_Result = true;
		break;

	case false:
		g_bStageClear_Result = false;
		break;

	}
}