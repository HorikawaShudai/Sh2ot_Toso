//=======================================================================
//
//���[�h��ʂ̏���(GameLoad.cpp)
//Auther:�x�씋��
//
//=======================================================================
#include "GameLoad.h"
#include "Fade.h"
#include "Input.h"

#define NUM_BACK	(2)			//�g������
#define HEIGHT_TEX	(200.0f)	//�e�N�X�`���̕�
#define WIDTH_TEX	(200.0f)	//�e�N�X�`���̍���
#define TEX_POS_X	(640.0f)	//���S���W(X)
#define TEX_POS_Y	(360.0f)	//���S���W(Y)
#define FADE_COUNT	(120)		//�����J�ڂ̃J�E���g

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureGameLoad = NULL;
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

	D3DXCreateTextureFromFile(pDevice, "Data\\TEXTURE\\Sh2ot_Logo.png", &g_pTextureGameLoad);

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
	if (g_pTextureGameLoad != NULL)
	{
		g_pTextureGameLoad->Release();
		g_pTextureGameLoad = NULL;
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
		switch (nCnt)
		{
		case 0:
			pDevice->SetTexture(0, NULL);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTextureGameLoad);
			break;
		}
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCnt, 2);
	}
}