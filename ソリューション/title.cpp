#include "main.h"
#include "Title.h"
#include "input.h"
#include "Fade.h"




//�}�N����`
#define NUM_Title (1) //�w�i�̐�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
LPDIRECT3DTEXTURE9 g_apTextureTitle[NUM_Title] = {}; //�e�N�X�`���ւ̃|�C���^



TITLESTATE g_TitleState = TITLESTATE_NONE;
int g_nCounterTitle = 0;
int g_nPlayer;
float g_tfChoice;
float g_tfChoiceA;
bool g_tbChoiceA;
//======================================
//����������
//======================================
void InitTitle(void)
{


	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	int nCntTitle;
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	/*D3DXCreateTextureFromFile(pDevice,
	"Data\\TEXTURE\\skate.jpg",
	&g_pTextureTitle);*/

	D3DXCreateTextureFromFile(pDevice, "Data\\TEXTURE\\Test_logo.jpg", &g_apTextureTitle[0]);



	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_Title,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_2D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);
	VERTEX_2D * pVtx;
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntTitle = 0; nCntTitle < NUM_Title; nCntTitle++)
	{

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

		pVtx += 4;
	}
	g_pVtxBuffTitle->Unlock();

	g_TitleState = TITLESTATE_NORMAL;
	g_nCounterTitle = 0;
}

//======================================
//�I������
//======================================
void UninitTitle(void)
{

	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	for (int nCntTitle = 0; nCntTitle < NUM_Title; nCntTitle++)
	{

		if (g_apTextureTitle[nCntTitle] != NULL)
		{
			g_apTextureTitle[nCntTitle]->Release();
			g_apTextureTitle[nCntTitle] = NULL;
		}
	}

}

//======================================
//�X�V����
//======================================
void UpdateTitle(void)
{

	
	FADE Fade = GetFade();

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(BUTTON_START, 0) || GetGamepadPress(BUTTON_A, 0))
		{
			SetFade(MODE_GAME);
		}
	}
}

//======================================
//�`�揈��
//======================================
void DrawTitle(void)
{


	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < NUM_Title; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureTitle[nCntTitle]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}

}
void SetTitleState(TITLESTATE state, int nCounter)
{
	g_TitleState = state;
	g_nCounterTitle = nCounter;
}

TITLESTATE GetTitleState()
{
	return g_TitleState;
}

int GetPlayerNumber()
{
	return g_nPlayer % 2;
}