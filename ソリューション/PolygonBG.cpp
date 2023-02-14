#include "main.h"
#include "polygonBG.h"
#include "numberUI.h"
#include "game.h"

//�}�N����`
#define NUM_SSUI		(4)	//GAMEUI�̎�ސ�

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

#define POS_ALLPERFECT_BG_X		(640.0f)	//�u�v��X���W�̈ʒu
#define POS_ALLPERFECT_BG_Y		(360.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_ALLPERFECT_BG_X	(640.0f)	//�u�v�̕�
#define SIZE_ALLPERFECT_BG_Y	(360.0f)	//�u�v�̍���

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePolygonBG[NUM_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonBG = NULL;		//���_�o�b�t�@�ւ̃|�C���^
PolygonBG g_PolygonBG[NUM_SSUI];

//====================================================================
//�^�C�g����ʂ̏���������
//====================================================================
void InitPolygonBG(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\Damage00.jpg",
	//	&g_apTexturePolygonBG[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Damage00.jpg",
		&g_apTexturePolygonBG[1]);

	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\Damage00.jpg",
	//	&g_apTexturePolygonBG[2]);

	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\Damage00.jpg",
	//	&g_apTexturePolygonBG[3]);

	//UI�̕\���ݒ�
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		g_PolygonBG[nCntBG].bUse = false;
		g_PolygonBG[nCntBG].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
		g_PolygonBG[nCntBG].nLife = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygonBG,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffPolygonBG->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffPolygonBG->Unlock();
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitPolygonBG(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTexturePolygonBG[nCntBG] != NULL)
		{
			g_apTexturePolygonBG[nCntBG]->Release();
			g_apTexturePolygonBG[nCntBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygonBG != NULL)
	{
		g_pVtxBuffPolygonBG->Release();
		g_pVtxBuffPolygonBG = NULL;
	}
}

//====================================================================
//�^�C�g����ʂ̍X�V����
//====================================================================
void UpdatePolygonBG(void)
{
	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		if (g_PolygonBG[nCntBG].bUse == true)
		{
			if (g_PolygonBG[nCntBG].nLife <= 0)
			{
				g_PolygonBG[nCntBG].bUse = false;
			}
			else
			{
				g_PolygonBG[nCntBG].nLife--;
			}
		}
	}

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffPolygonBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		if (g_PolygonBG[nCntBG].bUse == true)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = g_PolygonBG[nCntBG].col;
			pVtx[1].col = g_PolygonBG[nCntBG].col;
			pVtx[2].col = g_PolygonBG[nCntBG].col;
			pVtx[3].col = g_PolygonBG[nCntBG].col;
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygonBG->Unlock();
}

//====================================================================
//�^�C�g����ʂ̕`�揈��
//====================================================================
void DrawPolygonBG(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePolygonBG[nCntBG]);

		if (g_PolygonBG[nCntBG].bUse == true)
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
void SetPolygonBG(D3DXCOLOR Col, int nLife)
{
	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		if (g_PolygonBG[nCntBG].bUse == false)
		{
			g_PolygonBG[nCntBG].bUse = true;
			g_PolygonBG[nCntBG].col = Col;
			g_PolygonBG[nCntBG].nLife = nLife;
			break;
		}
	}
}