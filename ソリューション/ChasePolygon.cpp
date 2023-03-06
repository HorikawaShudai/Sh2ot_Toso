#include "main.h"
#include "resultUI.h"
#include "game.h"
#include "ChasePolygon.h"
#include "EscapeTutorial.h"
#include "PlayNumberSelect.h"
#include "player.h"

//�}�N����`
#define MAX_SSUI					(8)			//TUTORIALUI�̍ő�g�p��
#define NUM_SSUI					(1)			//TUTORIALUI�̍ő��ސ�

#define POS_TUTORIALUI_1_01_X		(640.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_1_01_Y		(360.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_1_01_X		(640.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_1_01_Y		(360.0f)	//�u�v�̍���

#define POS_TUTORIALUI_2_01_X		(320.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_2_01_Y		(360.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_2_01_X		(320.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_2_01_Y		(360.0f)	//�u�v�̍���

#define POS_TUTORIALUI_2_02_X		(960.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_2_02_Y		(360.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_2_02_X		(320.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_2_02_Y		(360.0f)	//�u�v�̍���

#define POS_TUTORIALUI_34_01_X		(320.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_01_Y		(180.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_01_X		(320.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_01_Y		(180.0f)	//�u�v�̍���

#define POS_TUTORIALUI_34_02_X		(960.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_02_Y		(180.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_02_X		(320.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_02_Y		(180.0f)	//�u�v�̍���

#define POS_TUTORIALUI_34_03_X		(320.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_03_Y		(540.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_03_X		(320.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_03_Y		(180.0f)	//�u�v�̍���

#define POS_TUTORIALUI_34_04_X		(960.0f)	//�u�v��X���W�̈ʒu
#define POS_TUTORIALUI_34_04_Y		(540.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_TUTORIALUI_34_04_X		(320.0f)	//�u�v�̕�
#define SIZE_TUTORIALUI_34_04_Y		(180.0f)	//�u�v�̍���

#define UP_PAPERBG01				(100.0f)	//�������o���Ƃ��̏㏸�x
#define UP_PAPERBG01_COUNTER_MAX	(100)		//�������o�������̃J�E���^�[

//�e�N�X�`���t�@�C����
const char *c_cpChaPolyTexname01[] =
{
	"Data\\TEXTURE\\shadow001.jpg",
};

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureChasePolygon[NUM_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffChasePolygon = NULL;		//���_�o�b�t�@�ւ̃|�C���^
bool bUseChasePolygon[MAX_SSUI];		//���_�o�b�t�@�ւ̃|�C���^
float g_ChasePolygonColorA[MAX_SSUI];		//�|���S���̃��l
float g_ChasePolygonColorA_MAX[MAX_SSUI];		//�|���S���̃��l�̍ő�l

//====================================================================
//�^�C�g����ʂ̏���������
//====================================================================
void InitChasePolygon(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	for (int nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, c_cpChaPolyTexname01[nCntBG], &g_apTextureChasePolygon[nCntBG]);
	}

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//UI�̕\���ݒ�
		bUseChasePolygon[nCntBG] = true;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffChasePolygon,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffChasePolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
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
		case 3:
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

		case 4:
		case 5:
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

		case 6:
		case 7:
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

		if (nCntBG % 2 == 0)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		}
		else
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffChasePolygon->Unlock();
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitChasePolygon(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureChasePolygon[nCntBG] != NULL)
		{
			g_apTextureChasePolygon[nCntBG]->Release();
			g_apTextureChasePolygon[nCntBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffChasePolygon != NULL)
	{
		g_pVtxBuffChasePolygon->Release();
		g_pVtxBuffChasePolygon = NULL;
	}
}

//====================================================================
//�^�C�g����ʂ̍X�V����
//====================================================================
void UpdateChasePolygon(void)
{
	float ColorA[MAX_SSUI];
	for (int nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		if (g_ChasePolygonColorA[nCntBG] > g_ChasePolygonColorA_MAX[nCntBG])
		{
			ColorA[nCntBG] = (g_ChasePolygonColorA_MAX[nCntBG] * 2 - g_ChasePolygonColorA[nCntBG]) / g_ChasePolygonColorA_MAX[nCntBG];
		}
		else
		{
			ColorA[nCntBG] = g_ChasePolygonColorA[nCntBG] / g_ChasePolygonColorA_MAX[nCntBG];
		}
	}

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffChasePolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, ColorA[nCntBG] * 0.75f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, ColorA[nCntBG] * 0.75f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, ColorA[nCntBG] * 0.75f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, ColorA[nCntBG] * 0.75f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffChasePolygon->Unlock();
}

//====================================================================
//�^�C�g����ʂ̕`�揈��
//====================================================================
void DrawChasePolygon(int nCnt)
{
	Player *pPlayer = GetPlayer();
	pPlayer += nCnt;
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffChasePolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < MAX_SSUI; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureChasePolygon[0]);

		if (pPlayer->bEnemyLeft == true && pPlayer->bEnemyRight == true)
		{
			if (bUseChasePolygon[nCntBG] == true && (nCntBG == nCnt * 2 || nCntBG == nCnt * 2 + 1))
			{
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
					4 * nCntBG,						//�v���~�e�B�u(�|���S��)��
					2);
			}
		}
		else if (pPlayer->bEnemyLeft == true)
		{
			if (bUseChasePolygon[nCntBG] == true && (nCntBG == nCnt * 2 + 1))
			{
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
					4 * nCntBG,						//�v���~�e�B�u(�|���S��)��
					2);
			}
		}
		else if (pPlayer->bEnemyRight == true)
		{
			if (bUseChasePolygon[nCntBG] == true && (nCntBG == nCnt * 2))
			{
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
					4 * nCntBG,						//�v���~�e�B�u(�|���S��)��
					2);
			}
		}
	}

	//a�u�����f�B���O��ʏ�ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//====================================================================
//�����L���OUI�̐ݒ菈��
//====================================================================
void SetColorChasePolygon(float a, int nCnt)
{
	g_ChasePolygonColorA[nCnt * 2] = a;
	g_ChasePolygonColorA[nCnt * 2 + 1] = a;
}

//====================================================================
//�����L���OUI�̐ݒ菈��
//====================================================================
void SetColorChasePolygonMAX(float a, int nCnt)
{
	g_ChasePolygonColorA_MAX[nCnt * 2] = a / 2;
	g_ChasePolygonColorA_MAX[nCnt * 2 + 1] = a / 2;
}