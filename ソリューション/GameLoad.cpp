//=======================================================================
//
//���[�h��ʂ̏���(GameLoad.cpp)
//Auther:�x�씋��
//
//=======================================================================
#include "GameLoad.h"
#include "Fade.h"
#include "Input.h"

//�}�N����`
#define MAX_TEX		(6)				//�e�N�X�`���̍ő吔
#define NUM_BACK	(7)				//�g������
#define HEIGHT_TEX	(200.0f)		//�e�N�X�`���̕�
#define WIDTH_TEX	(200.0f)		//�e�N�X�`���̍���
#define TEX_POS_X	(640.0f)		//���S���W(X)
#define TEX_POS_Y	(360.0f)		//���S���W(Y)
#define FADE_COUNT	(120)			//�����J�ڂ̃J�E���g

#define EACHICON_POSX	(120.0f)		//���̈ʒu
#define EACHICON_POSY	(600.0f)		//�c�̈ʒu
#define EACHICON_SPACE	(260.0f)		//�A�C�R�����m�̋���
#define EACHICON_SIZE	(100.0f)		//�l�A�C�R���̃T�C�Y

//�e�N�X�`���t�@�C����
const char *c_paIconTexname[] =
{
	"Data\\TEXTURE\\Sh2ot_Logo.png",			//�`�[�����S
	"Data\\TEXTURE\\ICON\\Sakamoto_Icon.png",	//��{�̃A�C�R��
	"Data\\TEXTURE\\ICON\\Logo_Hosyu.jpg",		//�x��̃A�C�R��
	"Data\\TEXTURE\\ICON\\yuki_icon.png",		//����̃A�C�R��
	"Data\\TEXTURE\\ICON\\Oga_Icon.png",		//���}���̃A�C�R��
	"Data\\TEXTURE\\ICON\\logo.png",			//�O��̃A�C�R��
};

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureGameLoad[NUM_BACK] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameLoad = NULL;
bool bCount;										//�����J�ڊJ�n
int g_FCount;										//�J�E���g�p�ϐ�
D3DXVECTOR3 g_Texpos;								//���S���W�̕ۑ��p

//============================================
//���[�h��ʂ̏���������
//============================================
void InitGameLoad(void)
{
	//�ϐ��̏�����
	g_Texpos = D3DXVECTOR3(TEX_POS_X, TEX_POS_Y, 0.0f);
	bCount = false;
	g_FCount = 0;

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, c_paIconTexname[nCntTex], &g_pTextureGameLoad[nCntTex]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BACK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameLoad,
		NULL);

	VERTEX_2D * pVtx;
	g_pVtxBuffGameLoad->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_BACK; nCnt++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		switch (nCnt)
		{
		case 0:

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Texpos.x - TEX_POS_X, g_Texpos.y - TEX_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Texpos.x + TEX_POS_X, g_Texpos.y - TEX_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Texpos.x - TEX_POS_X, g_Texpos.y + TEX_POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Texpos.x + TEX_POS_X, g_Texpos.y + TEX_POS_Y, 0.0f);
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			break;
		case 1:

			g_Texpos = D3DXVECTOR3(TEX_POS_X, 200.0f, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Texpos.x - HEIGHT_TEX, g_Texpos.y - WIDTH_TEX, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Texpos.x + HEIGHT_TEX, g_Texpos.y - WIDTH_TEX, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Texpos.x - HEIGHT_TEX, g_Texpos.y + WIDTH_TEX, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Texpos.x + HEIGHT_TEX, g_Texpos.y + WIDTH_TEX, 0.0f);
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		default:

			g_Texpos = D3DXVECTOR3(EACHICON_POSX + (EACHICON_SPACE * (nCnt - 2)), EACHICON_POSY, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Texpos.x - EACHICON_SIZE, g_Texpos.y - EACHICON_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Texpos.x + EACHICON_SIZE, g_Texpos.y - EACHICON_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Texpos.x - EACHICON_SIZE, g_Texpos.y + EACHICON_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Texpos.x + EACHICON_SIZE, g_Texpos.y + EACHICON_SIZE, 0.0f);
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
		}
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		
		pVtx += 4;
	}

	g_pVtxBuffGameLoad->Unlock();
}

//============================================
//���[�h��ʂ̏I������
//============================================
void UninitGameLoad(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureGameLoad[nCntTex] != NULL)
		{
			g_pTextureGameLoad[nCntTex]->Release();
			g_pTextureGameLoad[nCntTex] = NULL;
		}
	}
	if (g_pVtxBuffGameLoad != NULL)
	{
		g_pVtxBuffGameLoad->Release();
		g_pVtxBuffGameLoad = NULL;
	}
}

//============================================
//���[�h��ʂ̍X�V����
//============================================
void UpdateGameLoad(void)
{
	FADE bFade = GetFade();

	if (bCount == false)
	{
		if (bFade == FADE_NONE)
		{
			//�����J�ڊJ�n
			bCount = true;
		}
	}
	else if (bCount == true)
	{
		g_FCount++;

		//�J�E���g����萔�A�܂��͓���{�^���őJ��
		if (g_FCount == FADE_COUNT || GetGamepadTrigger(BUTTON_START,0) || GetGamepadTrigger(BUTTON_A, 0) || GetKeyboardTrigger(DIK_RETURN) && bFade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
		}
	}

}

//============================================
//���[�h��ʂ̕`�揈��
//============================================
void DrawGameLoad(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	pDevice->SetStreamSource(0, g_pVtxBuffGameLoad, 0, sizeof(VERTEX_2D));

	for (int nCnt = 0; nCnt < NUM_BACK; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		if (nCnt == 0)
		{
			pDevice->SetTexture(0, NULL);
		}
		else
		{
			pDevice->SetTexture(0, g_pTextureGameLoad[nCnt - 1]);
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCnt, 2);
	}
}