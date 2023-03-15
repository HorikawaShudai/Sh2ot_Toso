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
#define TEX_SIZE	(120.0f)		//�e�N�X�`���̑傫��
#define TEX_POS_X	(640.0f)		//���S���W(X)
#define TEX_POS_Y	(360.0f)		//���S���W(Y)
#define FADE_COUNT	(300)			//�����J�ڂ̃J�E���g

#define EACHICON_POSX	(120.0f)		//���̈ʒu
#define EACHICON_POSY	(600.0f)		//�c�̈ʒu
#define EACHICON_SPACE	(500.0f)		//�A�C�R�����m�̋���
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

typedef struct
{
	D3DXVECTOR3 pos;
	LPDIRECT3DTEXTURE9 Tex;
	int nType;
	bool bUse;
}LOGO;

LOGO g_aLogo[MAX_TEX];
int g_nLogoScreenMode;

//============================================
//���[�h��ʂ̏���������
//============================================
void InitGameLoad(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nLogoScreenMode = 0;
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//���W�ƃe�N�X�`���̐ݒ�;
		switch (nCnt)
		{
		case 0:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.5f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.25f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = true;
			break;
		case 1:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.25f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.6f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = true;
			break;
		case 2:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.5f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.6f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = true;
			break;
		case 3:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.75f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.6f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = true;
			break;
		case 4:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.3f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.6f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = false;
			break;
		case 5:
			g_aLogo[nCnt].pos.x = SCREEN_WIDTH * 0.7f;
			g_aLogo[nCnt].pos.y = SCREEN_HEIGHT * 0.6f;
			g_aLogo[nCnt].pos.z = 0.0f;
			g_aLogo[nCnt].bUse = false;
			break;
		default:
			break;
		}
		D3DXCreateTextureFromFile(pDevice, c_paIconTexname[nCnt], &g_aLogo[nCnt].Tex);
	}

	//�ϐ��̏�����
	g_Texpos = D3DXVECTOR3(TEX_POS_X, TEX_POS_Y, 0.0f);
	bCount = false;
	g_FCount = 0;


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

		if (nCnt == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f);
		
		}
		else
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aLogo[nCnt - 1].pos.x - TEX_SIZE, g_aLogo[nCnt - 1].pos.y - TEX_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLogo[nCnt - 1].pos.x + TEX_SIZE, g_aLogo[nCnt - 1].pos.y - TEX_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLogo[nCnt - 1].pos.x - TEX_SIZE, g_aLogo[nCnt - 1].pos.y + TEX_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLogo[nCnt - 1].pos.x + TEX_SIZE, g_aLogo[nCnt - 1].pos.y + TEX_SIZE, 0.0f);
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
		if (g_nLogoScreenMode == 0)
		{
			for (int nCnt = 0; nCnt < MAX_TEX - 2; nCnt++)
			{
				g_aLogo[nCnt].bUse = true;
			}
		}
		else
		{
			g_aLogo[0].bUse = true;
			g_aLogo[1].bUse = false;
			g_aLogo[2].bUse = false;
			g_aLogo[3].bUse = false;
			g_aLogo[4].bUse = true;
			g_aLogo[5].bUse = true;

		}

		if (g_nLogoScreenMode == 0 && (g_FCount >= ( FADE_COUNT * 0.5f )|| GetGamepadTrigger(BUTTON_START, 0) || GetGamepadTrigger(BUTTON_A, 0) || GetKeyboardTrigger(DIK_RETURN)))
		{
			g_nLogoScreenMode++;
		}

		//�J�E���g����萔�A�܂��͓���{�^���őJ��
		if ((g_FCount == FADE_COUNT || GetGamepadTrigger(BUTTON_START,0) || GetGamepadTrigger(BUTTON_A, 0) || GetKeyboardTrigger(DIK_RETURN) ) && bFade == FADE_NONE && g_nLogoScreenMode > 0)
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
		if (nCnt == 0 || g_aLogo[nCnt - 1].bUse == true)
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
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
		}
	}
}