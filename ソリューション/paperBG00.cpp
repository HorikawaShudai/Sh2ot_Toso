#include "main.h"
#include "EScapeTutorial.h"
#include "paperBG00.h"

//�}�N����`
#define NUM_SSUI				(2)			//GAMEUI�̎�ސ�

#define POS_BLACK_BG_X			(640.0f)	//�u���F�̔w�i�v��X���W�̈ʒu
#define POS_BLACK_BG_Y			(360.0f)	//�u���F�̔w�i�v��Y���W�̈ʒu
#define SIZE_BLACK_BG_X			(640.0f)	//�u���F�̔w�i�v�̕�
#define SIZE_BLACK_BG_Y			(360.0f)	//�u���F�̔w�i�v�̍���

#define POS_PAPER_BG_X			(640.0f)	//�u���v��X���W�̈ʒu
#define POS_PAPER_BG_Y			(310.0f)	//�u���v��Y���W�̈ʒu
#define SIZE_PAPER_BG_X			(500.0f)	//�u���v�̕�
#define SIZE_PAPER_BG_Y			(300.0f)	//�u���v�̍���

#define UP_PAPER_BG				(100.0f)	//�������o���Ƃ��̏㏸�x
#define UP_PAPER_COUNTER_MAX	(100)		//�������o�������̃J�E���^�[

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePaperBG00[NUM_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPaperBG00 = NULL;		//���_�o�b�t�@�ւ̃|�C���^
bool bUsePaperBG00[NUM_SSUI];		//UI���g���Ă��邩�ǂ���
int PaperBG00TrueCounter;			//�������o���Ƃ��̃J�E���^�[

//====================================================================
//���w�i00�̏���������
//====================================================================
void InitPaperBG00(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
	//	&g_apTexturePaperBG00[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
		&g_apTexturePaperBG00[1]);

	//UI�̕\���ݒ�
	bUsePaperBG00[0] = true;
	bUsePaperBG00[1] = true;
	PaperBG00TrueCounter = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPaperBG00,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffPaperBG00->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_BLACK_BG_X - SIZE_BLACK_BG_X, POS_BLACK_BG_Y - SIZE_BLACK_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_BLACK_BG_X + SIZE_BLACK_BG_X, POS_BLACK_BG_Y - SIZE_BLACK_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_BLACK_BG_X - SIZE_BLACK_BG_X, POS_BLACK_BG_Y + SIZE_BLACK_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_BLACK_BG_X + SIZE_BLACK_BG_X, POS_BLACK_BG_Y + SIZE_BLACK_BG_Y, 0.0f);
			break;

		case 1:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_PAPER_BG_X - SIZE_PAPER_BG_X, POS_PAPER_BG_Y - SIZE_PAPER_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PAPER_BG_X + SIZE_PAPER_BG_X, POS_PAPER_BG_Y - SIZE_PAPER_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PAPER_BG_X - SIZE_PAPER_BG_X, POS_PAPER_BG_Y + SIZE_PAPER_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PAPER_BG_X + SIZE_PAPER_BG_X, POS_PAPER_BG_Y + SIZE_PAPER_BG_Y, 0.0f);
			break;
		}

		switch (nCntBG)
		{
		case 0:
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			break;

		case 1:
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			break;
		}

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPaperBG00->Unlock();
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitPaperBG00(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTexturePaperBG00[nCntBG] != NULL)
		{
			g_apTexturePaperBG00[nCntBG]->Release();
			g_apTexturePaperBG00[nCntBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPaperBG00 != NULL)
	{
		g_pVtxBuffPaperBG00->Release();
		g_pVtxBuffPaperBG00 = NULL;
	}
}

//====================================================================
//���w�i00�̍X�V����
//====================================================================
void UpdatePaperBG00(void)
{
	switch (GetEscapeTutorial())
	{
	case TUTORIAL_STATE_STANDBY:
		//�������o���Ƃ��̃J�E���^�[�𑝂₷
		if (PaperBG00TrueCounter < UP_PAPER_COUNTER_MAX)
		{
			PaperBG00TrueCounter++;
		}
		break;

	case TUTORIAL_STATE_WAIT:
		//�������o���Ƃ��̃J�E���^�[�����炷
		if (PaperBG00TrueCounter > 0)
		{
			PaperBG00TrueCounter--;
		}
		break;
	}

	//�������o������
	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffPaperBG00->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			if (PaperBG00TrueCounter <= 0)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			}
			break;

		case 1:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_PAPER_BG_X - SIZE_PAPER_BG_X, POS_PAPER_BG_Y + (UP_PAPER_BG * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter)) - SIZE_PAPER_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PAPER_BG_X + SIZE_PAPER_BG_X, POS_PAPER_BG_Y + (UP_PAPER_BG * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter)) - SIZE_PAPER_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PAPER_BG_X - SIZE_PAPER_BG_X, POS_PAPER_BG_Y + (UP_PAPER_BG * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter)) + SIZE_PAPER_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PAPER_BG_X + SIZE_PAPER_BG_X, POS_PAPER_BG_Y + (UP_PAPER_BG * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter)) + SIZE_PAPER_BG_Y, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter));
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter));
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter));
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_PAPER_COUNTER_MAX / (float)PaperBG00TrueCounter));

			break;
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPaperBG00->Unlock();
}

//====================================================================
//���w�i00�̕`�揈��
//====================================================================
void DrawPaperBG00(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPaperBG00, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePaperBG00[nCntBG]);

		if (bUsePaperBG00[nCntBG] == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntBG,						//�v���~�e�B�u(�|���S��)��
				2);
		}
	}
}

//====================================================================
//���w�i00�̃Z�b�g����
//====================================================================
void SetPaperBG00(bool bUse)
{
	bUsePaperBG00[0] = bUse;
	bUsePaperBG00[1] = bUse;
}