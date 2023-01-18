#include "Fade.h"

//�O���[�o���ϐ�

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;
FADE g_fade;
MODE g_ModeNext;
D3DXCOLOR g_colorFade;

//======================================
//����������
//======================================
void InitFade(MODE modeNext)
{
	g_fade = FADE_IN;
	g_ModeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 1,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_2D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D * pVtx;
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	g_pVtxBuffFade->Unlock();
}

//======================================
//�I������
//======================================
void UninitFade(void)
{
	
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

}

//======================================
//�X�V����
//======================================
void UpdateFade(void)
{
	VERTEX_2D * pVtx;
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_colorFade.a -= 0.01f;
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		if (g_fade == FADE_OUT)
		{
			g_colorFade.a += 0.01f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_NONE;
				SetMode(g_ModeNext);
				g_fade = FADE_IN;
			}
		}
		

		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		
	}
g_pVtxBuffFade->Unlock();
}

//======================================
//�`�揈��
//======================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


}

void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_ModeNext = modeNext;
	g_colorFade.a = 0.0f;
}
FADE GetFade(void)
{
	return g_fade;
}