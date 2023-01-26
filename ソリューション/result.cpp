#include "main.h"
#include "Result.h"
#include "input.h"
#include "Fade.h"
#include "camera.h"

//�}�N����`
#define NUM_Result (1) //�w�i�̐�

//3D�w�i�p
void Init3DResult(void);
void Uninit3DResult(void);
void Update3Result(void);
void Draw3DResult(void);

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
LPDIRECT3DTEXTURE9 g_apTextureResult[NUM_Result] = {}; //�e�N�X�`���ւ̃|�C���^

float g_aTexUR[NUM_Result];
int g_nResult;
int nCountTime = 600;
int g_nWinner;
float g_rfChoiceA;
bool g_rbChoiceA;
//======================================
//����������
//======================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	int nCntResult;
	pDevice = GetDevice();

	g_nResult = 0;
	g_nWinner = 3;
	g_rbChoiceA = true;
	g_rfChoiceA = 0.0f;

	D3DXCreateTextureFromFile(pDevice, "Data\\TEXTURE\\Result_test.png", &g_apTextureResult[0]);
	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_Result,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_2D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);
	VERTEX_2D * pVtx;
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntResult = 0; nCntResult < NUM_Result; nCntResult++)
	{
		g_aTexUR[nCntResult] = 0.0f;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1000.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffResult->Unlock();

	//3D
	Init3DResult();
}

//======================================
//�I������
//======================================
void UninitResult(void)
{
	int nCntResult;
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	for (nCntResult = 0; nCntResult < NUM_Result; nCntResult++)
	{

		if (g_apTextureResult[nCntResult] != NULL)
		{
			g_apTextureResult[nCntResult]->Release();
			g_apTextureResult[nCntResult] = NULL;
		}
	}

	//3D
	Uninit3DResult();
}

//======================================
//�X�V����
//======================================
void UpdateResult(void)
{

	FADE Fade = GetFade();

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(BUTTON_A, 0))
		{
			SetFade(MODE_TITLE);
		}
	}

	//3D
	Update3Result();
}

//======================================
//�`�揈��
//======================================
void DrawResult(void)
{
	int nCntResult;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntResult = 0; nCntResult < NUM_Result; nCntResult++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureResult[nCntResult]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntResult * 4, 2);
	}

	//3D
	Draw3DResult();
}

//===================================
//3D�^�C�g���p
//===================================
//������
void Init3DResult(void)
{
	InitCamera();
}

//�I��
void Uninit3DResult(void)
{

}

//�X�V
void Update3Result(void)
{
	UpdateCamera();
}

//�`��
void Draw3DResult(void)
{
	SetCamera(5);
}
