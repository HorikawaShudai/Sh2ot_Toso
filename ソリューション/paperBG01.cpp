#include "main.h"
#include "resultUI.h"
#include "game.h"
#include "paperBG01.h"
#include "EscapeTutorial.h"
#include "PlayNumberSelect.h"

//�}�N����`
#define MAX_SSUI					(4)			//TUTORIALUI�̍ő�g�p��

//��l�v���C
#define POS_TUTORIALUI_1_01_X		(640.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_1_01_Y		(620.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_1_01_X		(400.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_1_01_Y		(100.0f)	//�u�v�̍���
//��l�v���C	��l��
#define POS_TUTORIALUI_2_01_X		(320.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_2_01_Y		(630.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_2_01_X		(300.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_2_01_Y		(80.0f)	//�u�v�̍���
//��l��
#define POS_TUTORIALUI_2_02_X		(960.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_2_02_Y		(630.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_2_02_X		(300.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_2_02_Y		(80.0f)	//�u�v�̍���
//�O�E�l�l�v���C	��l�v���C
#define POS_TUTORIALUI_34_01_X		(320.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_01_Y		(310.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_01_X		(300.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_01_Y		(50.0f)		//�u�v�̍���
//��l�v���C
#define POS_TUTORIALUI_34_02_X		(960.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_02_Y		(310.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_02_X		(300.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_02_Y		(50.0f)		//�u�v�̍���
//�O�l�v���C
#define POS_TUTORIALUI_34_03_X		(320.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_03_Y		(670.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_03_X		(300.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_03_Y		(50.0f)		//�u�v�̍���
//�l�l�v���C
#define POS_TUTORIALUI_34_04_X		(960.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_04_Y		(670.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_04_X		(300.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_04_Y		(50.0f)		//�u�v�̍���

#define UP_PAPERBG01				(100.0f)	//�������o���Ƃ��̏㏸�x
#define UP_PAPERBG01_COUNTER_MAX	(100)		//�������o�������̃J�E���^�[

//�e�N�X�`���t�@�C����
const char *c_cpPaperTexname01[] =
{
	"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
	"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
	"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
	"Data\\TEXTURE\\TUTORIAL\\paper.jpg",
};

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePaperBG01[MAX_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPaperBG01 = NULL;		//���_�o�b�t�@�ւ̃|�C���^
bool bUsePaperBG01[MAX_SSUI];		//���_�o�b�t�@�ւ̃|�C���^

//====================================================================
//�^�C�g����ʂ̏���������
//====================================================================
void InitPaperBG01(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	for (int nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, c_cpPaperTexname01[nCntBG], &g_apTexturePaperBG01[nCntBG]);
	}

	//UI�̕\���ݒ�
	bUsePaperBG01[0] = false;
	bUsePaperBG01[1] = false;
	bUsePaperBG01[2] = false;
	bUsePaperBG01[3] = false;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPaperBG01,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffPaperBG01->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			switch (GetPlayNumberSelect().CurrentSelectNumber)
			{
			case 1:
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_1_01_X - SIZE_TUTORIALUI_1_01_X, POS_TUTORIALUI_1_01_Y - SIZE_TUTORIALUI_1_01_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_1_01_X + SIZE_TUTORIALUI_1_01_X, POS_TUTORIALUI_1_01_Y - SIZE_TUTORIALUI_1_01_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_1_01_X - SIZE_TUTORIALUI_1_01_X, POS_TUTORIALUI_1_01_Y + SIZE_TUTORIALUI_1_01_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_1_01_X + SIZE_TUTORIALUI_1_01_X, POS_TUTORIALUI_1_01_Y + SIZE_TUTORIALUI_1_01_Y, 0.0f);
				break;
			case 2:
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_2_01_X - SIZE_TUTORIALUI_2_01_X, POS_TUTORIALUI_2_01_Y - SIZE_TUTORIALUI_2_01_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_2_01_X + SIZE_TUTORIALUI_2_01_X, POS_TUTORIALUI_2_01_Y - SIZE_TUTORIALUI_2_01_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_2_01_X - SIZE_TUTORIALUI_2_01_X, POS_TUTORIALUI_2_01_Y + SIZE_TUTORIALUI_2_01_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_2_01_X + SIZE_TUTORIALUI_2_01_X, POS_TUTORIALUI_2_01_Y + SIZE_TUTORIALUI_2_01_Y, 0.0f);
				break;
			case 3:
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X - SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y - SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X + SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y - SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X - SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y + SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X + SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y + SIZE_TUTORIALUI_34_01_Y, 0.0f);
				break;
			case 4:
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X - SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y - SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X + SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y - SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X - SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y + SIZE_TUTORIALUI_34_01_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_01_X + SIZE_TUTORIALUI_34_01_X, POS_TUTORIALUI_34_01_Y + SIZE_TUTORIALUI_34_01_Y, 0.0f);
				break;
			}
			break;

		case 1:
			switch (GetPlayNumberSelect().CurrentSelectNumber)
			{
			case 2:
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_2_02_X - SIZE_TUTORIALUI_2_02_X, POS_TUTORIALUI_2_02_Y - SIZE_TUTORIALUI_2_02_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_2_02_X + SIZE_TUTORIALUI_2_02_X, POS_TUTORIALUI_2_02_Y - SIZE_TUTORIALUI_2_02_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_2_02_X - SIZE_TUTORIALUI_2_02_X, POS_TUTORIALUI_2_02_Y + SIZE_TUTORIALUI_2_02_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_2_02_X + SIZE_TUTORIALUI_2_02_X, POS_TUTORIALUI_2_02_Y + SIZE_TUTORIALUI_2_02_Y, 0.0f);
				break;
			case 3:
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X - SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y - SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X + SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y - SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X - SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y + SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X + SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y + SIZE_TUTORIALUI_34_02_Y, 0.0f);
				break;
			case 4:
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X - SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y - SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X + SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y - SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X - SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y + SIZE_TUTORIALUI_34_02_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_02_X + SIZE_TUTORIALUI_34_02_X, POS_TUTORIALUI_34_02_Y + SIZE_TUTORIALUI_34_02_Y, 0.0f);
				break;
			}
			break;

		case 2:
			switch (GetPlayNumberSelect().CurrentSelectNumber)
			{
			case 3:
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X - SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y - SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X + SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y - SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X - SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y + SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X + SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y + SIZE_TUTORIALUI_34_03_Y, 0.0f);
				break;
			case 4:
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X - SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y - SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X + SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y - SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X - SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y + SIZE_TUTORIALUI_34_03_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_03_X + SIZE_TUTORIALUI_34_03_X, POS_TUTORIALUI_34_03_Y + SIZE_TUTORIALUI_34_03_Y, 0.0f);
				break;
			}
			break;

		case 3:
			switch (GetPlayNumberSelect().CurrentSelectNumber)
			{
			case 4:
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_34_04_X - SIZE_TUTORIALUI_34_04_X, POS_TUTORIALUI_34_04_Y - SIZE_TUTORIALUI_34_04_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_34_04_X + SIZE_TUTORIALUI_34_04_X, POS_TUTORIALUI_34_04_Y - SIZE_TUTORIALUI_34_04_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_34_04_X - SIZE_TUTORIALUI_34_04_X, POS_TUTORIALUI_34_04_Y + SIZE_TUTORIALUI_34_04_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_34_04_X + SIZE_TUTORIALUI_34_04_X, POS_TUTORIALUI_34_04_Y + SIZE_TUTORIALUI_34_04_Y, 0.0f);
				break;
			}
			break;
		}

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
	g_pVtxBuffPaperBG01->Unlock();
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitPaperBG01(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTexturePaperBG01[nCntBG] != NULL)
		{
			g_apTexturePaperBG01[nCntBG]->Release();
			g_apTexturePaperBG01[nCntBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPaperBG01 != NULL)
	{
		g_pVtxBuffPaperBG01->Release();
		g_pVtxBuffPaperBG01 = NULL;
	}
}

//====================================================================
//�^�C�g����ʂ̍X�V����
//====================================================================
void UpdatePaperBG01(void)
{

}

//====================================================================
//�^�C�g����ʂ̕`�揈��
//====================================================================
void DrawPaperBG01(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPaperBG01, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePaperBG01[nCntBG]);

		if (bUsePaperBG01[nCntBG] == true)
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
void SetPaperBG01(bool bUse, int nCnt)
{
	bUsePaperBG01[nCnt] = bUse;
}