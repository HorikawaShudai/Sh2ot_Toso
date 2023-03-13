#include "main.h"
#include "TimeUpPolygon.h"
#include "numberUI.h"
#include "player.h"
#include "PlayNumberSelect.h"
#include "game.h"
#include "time.h"

//�}�N����`
#define NUM_SSUI		(5)	//GAMEUI�̎�ސ�

#define POS_RANKING_BG_X		(640.0f)	//�u�v��X���W�̈ʒu
#define POS_RANKING_BG_Y		(360.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_RANKING_BG_X		(640.0f)	//�u�v�̕�
#define SIZE_RANKING_BG_Y		(360.0f)	//�u�v�̍���

#define POS_SCORE_BG_X			(640.0f)	//�u�v��X���W�̈ʒu
#define POS_SCORE_BG_Y			(360.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_SCORE_BG_X			(640.0f)	//�u�v�̕�
#define SIZE_SCORE_BG_Y			(360.0f)	//�u�v�̍���

#define POS_PERFECT_BG_X		(640.0f)	//�u�v��X���W�̈ʒu
#define POS_PERFECT_BG_Y		(360.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_PERFECT_BG_X		(640.0f)	//�u�v�̕�
#define SIZE_PERFECT_BG_Y		(360.0f)	//�u�v�̍���

#define POS_ALLPERFECT_BG_X		(250.0f)	//�u�v��X���W�̈ʒu
#define POS_ALLPERFECT_BG_Y		(200.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_ALLPERFECT_BG_X	(200.0f)	//�u�v�̕�
#define SIZE_ALLPERFECT_BG_Y	(100.0f)	//�u�v�̍���

#define POS_EXIT_BG_X			(250.0f)	//�u�v��X���W�̈ʒu
#define POS_EXIT_BG_Y			(450.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_EXIT_BG_X			(200.0f)	//�u�v�̕�
#define SIZE_EXIT_BG_Y			(100.0f)	//�u�v�̍���

#define COUNT00			(110)	//�X�^�[�g�J�E���g
#define COUNT01			(25)	//�J�E���g
#define COUNT02			(150)	//�J�E���g
#define COUNT03			(35)	//�J�E���g
#define COUNT04			(180)	//�J�E���g
#define COUNT05			(180)	//�G���h�J�E���g

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureTimeUpPolygon[NUM_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimeUpPolygon = NULL;		//���_�o�b�t�@�ւ̃|�C���^
bool bUseTimeUpPolygon[NUM_SSUI];		//�|���S�����g���Ă��邩�ǂ���
int g_RandTimeUpAnime;		//�A�j���[�V�����p�̕ϐ�
int g_TimeUpNumber;		//�^�C���I�[�o�[���o�̒i�K�p�ϐ�
int g_TimeUpCount;		//�^�C���I�[�o�[�̒i�K�̗]�C�p�̕ϐ�

//====================================================================
//�^�C�g����ʂ̏���������
//====================================================================
void InitTimeUpPolygon(void)
{
	int nCntBG;
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̏���
	int *pTime = GetTime();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sunaarasi.png",
		&g_apTextureTimeUpPolygon[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\pepepepe02.png",
		&g_apTextureTimeUpPolygon[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\RankUi.png",
		&g_apTextureTimeUpPolygon[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\pepepepe01.png",
		&g_apTextureTimeUpPolygon[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\pepepepe03.png",
		&g_apTextureTimeUpPolygon[4]);

	//�O���[�o���ϐ�������
	g_RandTimeUpAnime = 0;
	g_TimeUpNumber = -1;
	g_TimeUpCount = COUNT00;

	//UI�̕\���ݒ�
	bUseTimeUpPolygon[0] = false;
	bUseTimeUpPolygon[1] = false;
	bUseTimeUpPolygon[2] = false;
	bUseTimeUpPolygon[3] = false;
	bUseTimeUpPolygon[4] = false;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimeUpPolygon,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffTimeUpPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_RANKING_BG_X - SIZE_RANKING_BG_X, POS_RANKING_BG_Y - SIZE_RANKING_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_RANKING_BG_X + SIZE_RANKING_BG_X, POS_RANKING_BG_Y - SIZE_RANKING_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_RANKING_BG_X - SIZE_RANKING_BG_X, POS_RANKING_BG_Y + SIZE_RANKING_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_RANKING_BG_X + SIZE_RANKING_BG_X, POS_RANKING_BG_Y + SIZE_RANKING_BG_Y, 0.0f);
			break;

		case 1:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_SCORE_BG_X - SIZE_SCORE_BG_X, POS_SCORE_BG_Y - SIZE_SCORE_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_SCORE_BG_X + SIZE_SCORE_BG_X, POS_SCORE_BG_Y - SIZE_SCORE_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_SCORE_BG_X - SIZE_SCORE_BG_X, POS_SCORE_BG_Y + SIZE_SCORE_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_SCORE_BG_X + SIZE_SCORE_BG_X, POS_SCORE_BG_Y + SIZE_SCORE_BG_Y, 0.0f);
			break;

		case 2:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_PERFECT_BG_X - SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y - SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PERFECT_BG_X + SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y - SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PERFECT_BG_X - SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y + SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PERFECT_BG_X + SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y + SIZE_PERFECT_BG_Y, 0.0f);
			break;

		case 3:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X - SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y - SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X + SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y - SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X - SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y + SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X + SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y + SIZE_ALLPERFECT_BG_Y, 0.0f);
			break;

		case 4:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_EXIT_BG_X - SIZE_EXIT_BG_X, POS_EXIT_BG_Y - SIZE_EXIT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_EXIT_BG_X + SIZE_EXIT_BG_X, POS_EXIT_BG_Y - SIZE_EXIT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_EXIT_BG_X - SIZE_EXIT_BG_X, POS_EXIT_BG_Y + SIZE_EXIT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_EXIT_BG_X + SIZE_EXIT_BG_X, POS_EXIT_BG_Y + SIZE_EXIT_BG_Y, 0.0f);
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
	g_pVtxBuffTimeUpPolygon->Unlock();
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitTimeUpPolygon(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureTimeUpPolygon[nCntBG] != NULL)
		{
			g_apTextureTimeUpPolygon[nCntBG]->Release();
			g_apTextureTimeUpPolygon[nCntBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTimeUpPolygon != NULL)
	{
		g_pVtxBuffTimeUpPolygon->Release();
		g_pVtxBuffTimeUpPolygon = NULL;
	}
}

//====================================================================
//�^�C�g����ʂ̍X�V����
//====================================================================
void UpdateTimeUpPolygon(void)
{
	if (g_TimeUpNumber != -1)
	{
		//�^�C���̒i�K�ύX����
		g_TimeUpCount--;
		if (g_TimeUpCount <= 0)
		{
			switch (g_TimeUpNumber)
			{
			case 0:
				g_TimeUpCount = COUNT01;
				bUseTimeUpPolygon[0] = false;
				break;
			case 1:
				g_TimeUpCount = COUNT02;
				bUseTimeUpPolygon[0] = true;
				break;
			case 2:
				g_TimeUpCount = COUNT03;
				bUseTimeUpPolygon[0] = false;
				break;
			case 3:
				g_TimeUpCount = COUNT04;
				bUseTimeUpPolygon[0] = true;
				break;
			case 4:
				g_TimeUpCount = COUNT05;
				bUseTimeUpPolygon[0] = false;
				bUseTimeUpPolygon[1] = true;
				bUseTimeUpPolygon[2] = true;
				break;
			case 5:
				g_TimeUpNumber = -2;
				SetGameState(GAMESTATE_GAMEOVER_END, 180);
				break;
			}

			g_TimeUpNumber++;
		}

		//�����|���S���p�̗�������
		g_RandTimeUpAnime = rand() % 101;
		float fRand = ((float)g_RandTimeUpAnime) * 0.1f;

		VERTEX_2D*pVtx;	//���_�|�C���^������

		//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
		g_pVtxBuffTimeUpPolygon->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
		{
			if (nCntBG == 0)
			{
				//���_�J���[�̐ݒ�
				if (g_TimeUpNumber == 0)
				{
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				}
				else if (g_TimeUpNumber == 2)
				{
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				}
				else
				{
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(fRand + 1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, fRand + 1.0f);
				pVtx[3].tex = D3DXVECTOR2(fRand + 1.0f, fRand + 1.0f);
			}

			pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTimeUpPolygon->Unlock();
	}
}

//====================================================================
//�^�C�g����ʂ̕`�揈��
//====================================================================
void DrawTimeUpPolygon(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimeUpPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureTimeUpPolygon[nCntBG]);

		if (bUseTimeUpPolygon[nCntBG] == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntBG,						//�v���~�e�B�u(�|���S��)��
				2);
		}
	}
}

//====================================================================
//�^�C���A�b�v�̐ݒ菈��
//====================================================================
void SetTimeUpPolygon(void)
{
	g_TimeUpNumber = 0;
	bUseTimeUpPolygon[0] = true;
}