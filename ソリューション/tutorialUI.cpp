#include "main.h"
#include "resultUI.h"
#include "numberUI.h"
#include "game.h"
#include "tutorialUI.h"

//�}�N����`
#define NUM_SSUI		(4)	//GAMEUI�̎�ސ�

#define POS_TUTORIAL_BG_X		(200.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIAL_BG_Y		(400.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIAL_BG_X		(20.0f)		//�u�v�̕�
#define SIZE_TUTORIAL_BG_Y		(20.0f)		//�u�v�̍���

#define POS_SCORE_BG_X			(400.0f)	//�u�v��X���W�̈ʒu
#define POS_SCORE_BG_Y			(400.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_SCORE_BG_X			(20.0f)		//�u�v�̕�
#define SIZE_SCORE_BG_Y			(20.0f)		//�u�v�̍���

#define POS_PERFECT_BG_X		(1040.0f)	//�u�v��X���W�̈ʒu
#define POS_PERFECT_BG_Y		(100.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_PERFECT_BG_X		(150.0f)	//�u�v�̕�
#define SIZE_PERFECT_BG_Y		(75.0f)		//�u�v�̍���

#define POS_ALLPERFECT_BG_X		(200.0f)	//�u�v��X���W�̈ʒu
#define POS_ALLPERFECT_BG_Y		(120.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_ALLPERFECT_BG_X	(200.0f)	//�u�v�̕�
#define SIZE_ALLPERFECT_BG_Y	(100.0f)	//�u�v�̍���

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureTutorialUI[NUM_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialUI = NULL;		//���_�o�b�t�@�ւ̃|�C���^
bool bUseTutorialUI[NUM_SSUI];		//���_�o�b�t�@�ւ̃|�C���^
bool g_bStageClear_Tutorial;

//====================================================================
//�^�C�g����ʂ̏���������
//====================================================================
void InitTutorialUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\RankingBG.png",
	//	&g_apTextureTutorialUI[0]);

	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\Ranking_Score.png",
	//	&g_apTextureTutorialUI[1]);

	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\TUTORIAL\\clear_tousou.png",
	//	&g_apTextureTutorialUI[2]);

	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\RankingAllPerfect.png",
	//	&g_apTextureTutorialUI[3]);

	//UI�̕\���ݒ�
	bUseTutorialUI[0] = true;
	bUseTutorialUI[1] = true;
	bUseTutorialUI[2] = true;
	bUseTutorialUI[3] = true;

	if (bUseTutorialUI[1] == true)
	{
		SetNumberUI(D3DXVECTOR3(600.0f, 600.0f, 0.0f), 50.0f, 50.0f, 1);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialUI,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffTutorialUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_TUTORIAL_BG_X - SIZE_TUTORIAL_BG_X, POS_TUTORIAL_BG_Y - SIZE_TUTORIAL_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_TUTORIAL_BG_X + SIZE_TUTORIAL_BG_X, POS_TUTORIAL_BG_Y - SIZE_TUTORIAL_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_TUTORIAL_BG_X - SIZE_TUTORIAL_BG_X, POS_TUTORIAL_BG_Y + SIZE_TUTORIAL_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_TUTORIAL_BG_X + SIZE_TUTORIAL_BG_X, POS_TUTORIAL_BG_Y + SIZE_TUTORIAL_BG_Y, 0.0f);
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
	g_pVtxBuffTutorialUI->Unlock();
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

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorialUI != NULL)
	{
		g_pVtxBuffTutorialUI->Release();
		g_pVtxBuffTutorialUI = NULL;
	}
}

//====================================================================
//�^�C�g����ʂ̍X�V����
//====================================================================
void UpdateTutorialUI(void)
{

}

//====================================================================
//�^�C�g����ʂ̕`�揈��
//====================================================================
void DrawTutorialUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureTutorialUI[nCntBG]);

		if (bUseTutorialUI[nCntBG] == true)
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
void SetTutorialUI(TUTORIALUI SetClear, bool Clear)
{
	/*g_bStageClear_Ranking = Clear;

	bUseRankingUI[1] = true;
	switch (SetClear)
	{
	case RANKING_NORMAL:

	bUseRankingUI[2] = false;
	bUseRankingUI[3] = false;

	break;

	case RANKING_PERFECT:

	bUseRankingUI[2] = true;
	bUseRankingUI[3] = false;

	break;

	case RANKING_ALLPERFECT:

	bUseRankingUI[2] = true;
	bUseRankingUI[3] = true;

	break;
	}*/
}