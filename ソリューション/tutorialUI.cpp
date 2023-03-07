#include "main.h"
#include "resultUI.h"
#include "game.h"
#include "tutorialUI.h"
#include "EscapeTutorial.h"
#include "PlayNumberSelect.h"
#include "input.h"

//�}�N����`
#define NUM_SSUI					(18)		//TUTORIALUI�̎�ސ�
#define MAX_SSUI					(5)			//TUTORIALUI�̍ő�g�p��
#define MAX_BUFF					(3)			//�o�b�t�@�̍ő吔
#define MAX_GUYDE					(3)			//�K�C�h�̍ő吔

#define POS_TUTORIALUI_ALL_X		(640.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_ALL_Y		(290.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_ALL_X		(270.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_ALL_Y		(330.0f)	//�u�v�̍���

#define POS_TUTORIALUI_1_01_X		(640.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_1_01_Y		(630.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_1_01_X		(300.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_1_01_Y		(80.0f)		//�u�v�̍���

#define POS_TUTORIALUI_2_01_X		(320.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_2_01_Y		(600.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_2_01_X		(150.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_2_01_Y		(60.0f)		//�u�v�̍���

#define POS_TUTORIALUI_2_02_X		(960.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_2_02_Y		(600.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_2_02_X		(150.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_2_02_Y		(60.0f)		//�u�v�̍���

#define POS_TUTORIALUI_34_01_X		(320.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_01_Y		(310.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_01_X		(150.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_01_Y		(25.0f)		//�u�v�̍���

#define POS_TUTORIALUI_34_02_X		(960.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_02_Y		(310.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_02_X		(150.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_02_Y		(25.0f)		//�u�v�̍���

#define POS_TUTORIALUI_34_03_X		(320.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_03_Y		(670.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_03_X		(150.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_03_Y		(25.0f)		//�u�v�̍���

#define POS_TUTORIALUI_34_04_X		(960.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_04_Y		(670.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_04_X		(150.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_04_Y		(25.0f)		//�u�v�̍���

#define UP_PAPERBG01				(100.0f)	//�������o���Ƃ��̏㏸�x
#define UP_PAPERBG01_COUNTER_MAX	(100)		//�������o�������̃J�E���^�[

//�v���g�^�C�v�錾
void InitSkipUI(void);
void DrawSkipUI(void);
void InitGuydeUI(void);
void DrawGuydeUI(void);

//�e�N�X�`���t�@�C����
const char *c_apTutorialUITexname[] =
{
	"data\\TEXTURE\\TUTORIAL\\tutorial0.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial1.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial2.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial3.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial4.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial5.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial6.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial_move1.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial_dash1.png",
	"data\\TEXTURE\\TUTORIAL\\vibe.png",
	"data\\TEXTURE\\TUTORIAL\\stealth.png",
	"data\\TEXTURE\\TUTORIAL\\getkey.png",
	"data\\TEXTURE\\TUTORIAL\\open_doar1.png",
	"data\\TEXTURE\\TUTORIAL\\escape.png",
	"data\\TEXTURE\\TUTORIAL\\skip.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial00.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial02.png",
	"data\\TEXTURE\\TUTORIAL\\tutorial01.png",
	"data\\TEXTURE\\TUTORIAL\\next_page.png",
	"data\\TEXTURE\\TUTORIAL\\back.png",
	"data\\TEXTURE\\TUTORIAL\\check_page.png",
};

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureTutorialUI[NUM_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialUI[MAX_BUFF] = {};		//���_�o�b�t�@�ւ̃|�C���^
bool bUseTutorialUI[MAX_SSUI];		//���_�o�b�t�@�ւ̃|�C���^
bool g_bStageClear_Tutorial;
bool g_TutorialTEX_Change;			//�e�N�X�`����؂�ւ��邽�߂̃J�E���^�[
int TutorialUI_TrueCounter;			//�������o���Ƃ��̃J�E���^�[

D3DXVECTOR3 pos;

//====================================================================
//�^�C�g����ʂ̏���������
//====================================================================
void InitTutorialUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	for (int nCntUI = 0; nCntUI < NUM_SSUI; nCntUI++)
	{
		D3DXCreateTextureFromFile(pDevice, c_apTutorialUITexname[nCntUI], &g_apTextureTutorialUI[nCntUI]);
	}

	//UI�̕\���ݒ�
	bUseTutorialUI[0] = true;
	bUseTutorialUI[1] = false;
	bUseTutorialUI[2] = false;
	bUseTutorialUI[3] = false;
	bUseTutorialUI[4] = false;
	TutorialUI_TrueCounter = 0;
	g_TutorialTEX_Change = false;

	//���_�o�b�t�@�̐���0
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialUI[0],
		NULL);

	//���_�o�b�t�@�̐���1
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialUI[1],
		NULL);

	//���_�o�b�t�@�̐���1
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GUYDE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialUI[2],
		NULL);

	InitGuydeUI();

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffTutorialUI[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X - SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y - SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X + SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y - SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X - SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X + SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + SIZE_TUTORIALUI_ALL_Y, 0.0f);
			break;

		case 1:
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

		case 2:
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

		case 3:
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

		case 4:
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
	g_pVtxBuffTutorialUI[0]->Unlock();

	//�X�L�b�vUI�̏�����
	InitSkipUI();
}

//==============================================
//��ʂɃX�L�b�vUI��\������
//==============================================
void InitSkipUI(void)
{
	pos = D3DXVECTOR3(1160.0f, 690.0f, 0.0f);

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^������
	g_pVtxBuffTutorialUI[1]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - 100, pos.y - 30, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 100, pos.y - 30, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 100, pos.y + 30, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 100, pos.y + 30, 0.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorialUI[1]->Unlock();
}

//==============================================
//��ʂɃK�C�hUI��\������
//==============================================
void InitGuydeUI(void)
{
	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^������
	g_pVtxBuffTutorialUI[2]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorialUI[2]->Unlock();
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitTutorialUI(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureTutorialUI[nCntBG] != NULL)
		{
			g_apTextureTutorialUI[nCntBG]->Release();
			g_apTextureTutorialUI[nCntBG] = NULL;
		}
	}
	for (int nCntBuff = 0; nCntBuff < MAX_BUFF; nCntBuff++)
	{
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffTutorialUI[nCntBuff] != NULL)
		{
			g_pVtxBuffTutorialUI[nCntBuff]->Release();
			g_pVtxBuffTutorialUI[nCntBuff] = NULL;
		}
	}
}

//====================================================================
//�^�C�g����ʂ̍X�V����
//====================================================================
void UpdateTutorialUI(void)
{
	TUTORIAL_STATE Tutorial_State = GetEscapeTutorial();

	switch (GetEscapeTutorial())
	{
	case TUTORIAL_STATE_STANDBY:
		//�������o���Ƃ��̃J�E���^�[�𑝂₷
		if (TutorialUI_TrueCounter < UP_PAPERBG01_COUNTER_MAX)
		{
			TutorialUI_TrueCounter++;
		}
		break;

	case TUTORIAL_STATE_WAIT:
		//�������o���Ƃ��̃J�E���^�[�����炷
		if (TutorialUI_TrueCounter > 0)
		{
			TutorialUI_TrueCounter--;
		}
		break;
	}

	//�������o������
	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffTutorialUI[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		if (nCntBG == 0 && TutorialUI_TrueCounter < UP_PAPERBG01_COUNTER_MAX)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X - SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_PAPERBG01 * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter)) - SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X + SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_PAPERBG01 * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter)) - SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X - SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_PAPERBG01 * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter)) + SIZE_TUTORIALUI_ALL_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_TUTORIALUI_ALL_X + SIZE_TUTORIALUI_ALL_X, POS_TUTORIALUI_ALL_Y + (UP_PAPERBG01 * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter)) + SIZE_TUTORIALUI_ALL_Y, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter));
			pVtx[1].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter));
			pVtx[2].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter));
			pVtx[3].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f * ((float)UP_PAPERBG01_COUNTER_MAX / (float)TutorialUI_TrueCounter));
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorialUI[0]->Unlock();
}

//====================================================================
//�^�C�g����ʂ̕`�揈��
//====================================================================
void DrawTutorialUI(void)
{
	//�`���[�g���A���̍��ڏ���^���鏈��
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();

	TUTORIAL_STATE Tutorial_State = GetEscapeTutorial();

	int nCntBG;

	if (Tutorial_State == TUTORIAL_STATE_GUYDE)
	{
		DrawGuydeUI();
	}

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialUI[0], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (Tutorial_State == TUTORIAL_STATE_PLAY)
	{
		g_TutorialTEX_Change = false;
	}

	switch (do_Tutorial)
	{
	case MODE_MOVE:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//�`���[�g���A���̏�Ԃ�STANDBY�܂���WAIT�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[0]);
		}
		else
		{//����ȊO�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[7]);
		}

		break;

	case MODE_DASH:
		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//�`���[�g���A���̏�Ԃ�STANDBY�܂���WAIT�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[1]);
		}
		else
		{//����ȊO�̎�
			 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[8]);
		}

		break;

	case MODE_VIBE:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//�`���[�g���A���̏�Ԃ�STANDBY�܂���WAIT�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[2]);
		}
		else
		{//����ȊO�̎�
			 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[9]);
		}

		break;

	case MODE_STELTH:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//�`���[�g���A���̏�Ԃ�STANDBY�܂���WAIT�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[3]);
		}
		else
		{//����ȊO�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[10]);
		}

		break;

	case MODE_GET_KEY:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//�`���[�g���A���̏�Ԃ�STANDBY�܂���WAIT�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[4]);
		}
		else
		{//����ȊO�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[11]);
		}

		break;

	case MODE_ESCAPE:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//�`���[�g���A���̏�Ԃ�STANDBY�܂���WAIT�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[5]);
		}
		else
		{//����ȊO�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[12]);
		}

		break;

	case MODE_GOEXIT:

		if (Tutorial_State == TUTORIAL_STATE_STANDBY || Tutorial_State == TUTORIAL_STATE_WAIT)
		{//�`���[�g���A���̏�Ԃ�STANDBY�܂���WAIT�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[6]);
		}
		else
		{//����ȊO�̎�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorialUI[13]);
		}

		break;

	case MODE_END:

		break;
	}

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		if (bUseTutorialUI[nCntBG] == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntBG,						//�v���~�e�B�u(�|���S��)��
				2);
		}
	}

	DrawSkipUI();
}

//====================================================================
//�X�L�b�vUI�̕`�揈��
//====================================================================
void DrawSkipUI(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialUI[1], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_apTextureTutorialUI[14]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,						//�v���~�e�B�u(�|���S��)��
		2);
}

//====================================================================
//�K�C�hUI�̕`�揈��
//====================================================================
void DrawGuydeUI(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	TUTORIAL_GUYDE Tutorial_Guyde = GetEscapeTutorialGuyde();

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialUI[2], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (Tutorial_Guyde == TUTORIAL_GUYDE_ESCAPE)
	{
		pDevice->SetTexture(0, g_apTextureTutorialUI[15]);
	}

	if (Tutorial_Guyde == TUTORIAL_GUYDE_KEY)
	{
		pDevice->SetTexture(0, g_apTextureTutorialUI[16]);
	}

	if (Tutorial_Guyde == TUTORIAL_GUYDE_HEALTH)
	{
		pDevice->SetTexture(0, g_apTextureTutorialUI[17]);
	}

	for (int nCntGuyde = 0; nCntGuyde < MAX_GUYDE; nCntGuyde++)
	{
		if (bUseTutorialUI[nCntGuyde] == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntGuyde,						//�v���~�e�B�u(�|���S��)��
				2);
		}
	}
}

//====================================================================
//�����L���OUI�̐ݒ菈��
//====================================================================
void SetTutorialUI(bool bUse, int nCnt)
{
	bUseTutorialUI[nCnt] = bUse;
}