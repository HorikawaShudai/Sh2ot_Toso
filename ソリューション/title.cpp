//======================================================================================
//
// �^�C�g������[title.cpp]
// Author:
//
//======================================================================================
#include "main.h"
#include "Title.h"
#include "input.h"
#include "Fade.h"
#include "debugproc.h"
#include "camera.h"
#include "light.h"
#include "SpotLight.h"
#include "meshdome.h"
#include "stage.h"
#include "objectBG.h"
#include "meshcylinder.h"
#include "object00.h"
#include "Billboard.h"
#include "Thunder.h"
#include "effect.h"
#include "sound.h"
#include "exit.h"

//**********************************************
//�}�N����`
//**********************************************
#define NUM_TEX			(3)		// �e�N�X�`���̐�
#define NUM_TITLEPOS	(3)		//
#define NUM_SELECT		(2)		//�I�𗓂̐�
#define CAMERA_FADEPOS	(370.0f)//��ʑJ�ڂ���J�����ʒu(Z��)

#define POS_STAGESELECT_BG_X		(200.0f)	//�u�X�e�[�W�Z���N�g�v��X���W�̈ʒu
#define POS_STAGESELECT_BG_Y		(500.0f)	//�u�X�e�[�W�Z���N�g�v��Y���W�̈ʒu
#define SIZE_STAGESELECT_BG_X		(150.0f)	//�u�X�e�[�W�Z���N�g�v�̕�
#define SIZE_STAGESELECT_BG_Y		(70.0f)		//�u�X�e�[�W�Z���N�g�v�̍���

#define POS_RANKING_BG_X			(170.0f)	//�u�����L���O�v��X���W�̈ʒu
#define POS_RANKING_BG_Y			(600.0f)	//�u�����L���O�v��Y���W�̈ʒu
#define SIZE_RANKING_BG_X			(120.0f)	//�u�����L���O�v�̕�
#define SIZE_RANKING_BG_Y			(50.0f)		//�u�����L���O�v�̍���

//**********************************************
// �e�N�X�`����
//**********************************************
const char *c_apTitleTexName[NUM_TEX] =
{
	"Data\\TEXTURE\\TITLE\\Tousou_logo.png",		//�������S
	"Data\\TEXTURE\\TITLE\\TitleSelect02.png",		//�X�^�[�g����
	"Data\\TEXTURE\\TITLE\\TitleSelect03.png",		//�Z���N�g����
};

//**********************************************
//�v���g�^�C�v�錾
//**********************************************
void InitTitleBg(int nCntTitle);							//�^�C�g���w�i
void InitTitleLogo(int nCntTitle);							//�^�C�g�����S
void InitTitleSelect0(int nCntTitle);						//�^�C�g���Z���N�g(���[�h)
void InitTitleSelect1(int nCntTitle);						//�^�C�g���Z���N�g(�����L���O)
//3D�w�i�p
void Init3DTitle(void);
void Uninit3DTitle(void);
void Update3DTitle(void);
void Draw3DTitle(void);

void UpdateTitleSelect(void);									//�^�C�g���Z���N�g(�����L���O)

//**********************************************
//�O���[�o���ϐ�
//**********************************************
LPDIRECT3DTEXTURE9 g_apTextureTitle[NUM_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			//���_�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3 g_aTitlePos[NUM_TITLEPOS];			//�^�C�g����ʂɔz�u�����ꏊ
int g_CurrentNumberTitle;						//���ݑI������Ă���ԍ�(���[�h�I��p)
bool bPress;
int g_nFadeCnt;
bool bTitle;

//============================================================================
//����������
//============================================================================
void InitTitle(void)
{
	//�ϐ��錾
	int nCntTitle;

	//�f�o�C�X�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�O���[�o���錾�̏�����
	for (nCntTitle = 0; nCntTitle < NUM_TITLEPOS; nCntTitle++)
	{
		g_aTitlePos[nCntTitle] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_CurrentNumberTitle = 0;

	bPress = false;
	g_nFadeCnt = 0;
	bTitle = false;

	for (nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
	{//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, c_apTitleTexName[nCntTitle], &g_apTextureTitle[nCntTitle]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TEX,
		D3DUSAGE_WRITEONLY, { FVF_VERTEX_2D }, D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//�e�����̏�����
	for (nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			InitTitleLogo(nCntTitle);		//�^�C�g�����S
			break;
		case 1:
			InitTitleSelect0(nCntTitle);	//�I��(���[�h�I��)
			break;
		case 2:
			InitTitleSelect1(nCntTitle);	//�I��(�����L���O)
			break;
		}
	}

	//3D
	Init3DTitle();

	//�^�C�g����BGM(�J)
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

//============================================================================
//�I������
//============================================================================
void UninitTitle(void)
{
	//�Ȃ��~�߂�
	StopSound();

	for (int nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureTitle[nCntTitle] != NULL)
		{
			g_apTextureTitle[nCntTitle]->Release();
			g_apTextureTitle[nCntTitle] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//3D
	Uninit3DTitle();
}

//============================================================================
//�X�V����
//============================================================================
void UpdateTitle(void)
{
	Camera *pCamera = GetCamera();
	THUNDER aThunder = GetThunder();

	pCamera += 4;

	if (bTitle == false && bPress ==false)
	{
		g_nFadeCnt++;
		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadPress(BUTTON_START, 0) || GetGamepadTrigger(BUTTON_A, 0))
		{//����L�[(ENTER�L�[)�������ꂽ
			g_nFadeCnt = 219;

			//�I����
			PlaySound(SOUND_LABEL_ENTER);
		}
		else if (g_nFadeCnt == 220)
		{
			SetThunder();
			bTitle = true;
		}
	}
	//3D
	Update3DTitle();

	if (aThunder.nType == THUNDER_NONE && bTitle == true)
	{
		//�I������
		UpdateTitleSelect();
	}

	FADE pFade = GetFade();

	if (pFade == FADE_NONE)
	{
		if (g_CurrentNumberTitle == 0 && pCamera->posV.z >= CAMERA_FADEPOS)
		{//���݂̑I��ԍ���0�̏ꍇ
			SetFade(MODE_NUMBERSELECT);			//���[�h�̐ݒ�(���[�h�I����ʂɈڍs)
		}
		else if (g_CurrentNumberTitle == 1 && pCamera->posV.z >= CAMERA_FADEPOS)
		{//���݂̑I��ԍ���1�̏ꍇ
			SetFade(MODE_RANKING);		//���[�h�̐ݒ�(�����L���O��ʂɈڍs)
		}
	}

	//�f�o�b�O�\��
	PrintDebugProc("%f\n", pCamera->posV.z);
	PrintDebugProc("�I�� �y���z�y���z\n");
	PrintDebugProc("���� �yENTER�z\n");
}

//============================================================================
//�`�揈��
//============================================================================
void DrawTitle(void)
{
	//3D
	Draw3DTitle();

	if (bTitle == true)
	{
		//�f�o�C�X�ւ̃|�C���^���擾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

		for (int nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTitle[nCntTitle]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
		}
	}
}

//===================================
//������������
//===================================
void InitTitleBg(int nCntTitle)
{
	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntTitle * 4;		//���_����i�߂�

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//�^�C�g�����S
void InitTitleLogo(int nCntTitle)
{
	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntTitle * 4;		//���_����i�߂�

	//�ʒu
	g_aTitlePos[0] = D3DXVECTOR3(1000.0f, 50.0f, 0.0f);

	//���_���W�̐ݒ�(���_�͒�����)
	pVtx[0].pos = D3DXVECTOR3(g_aTitlePos[0].x - 150.0f, g_aTitlePos[0].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitlePos[0].x + 150.0f, g_aTitlePos[0].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitlePos[0].x - 150.0f, g_aTitlePos[0].y + 450.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitlePos[0].x + 150.0f, g_aTitlePos[0].y + 450.0f, 0.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//�I��(���[�h�I�𕶎�)
void InitTitleSelect0(int nCntTitle)
{
	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntTitle * 4;		//���_����i�߂�

	//�ʒu
	g_aTitlePos[1] = D3DXVECTOR3(POS_STAGESELECT_BG_X, POS_STAGESELECT_BG_Y, 0.0f);

	//���_���W�̐ݒ�(���_�͒�����)
	pVtx[0].pos = D3DXVECTOR3(g_aTitlePos[1].x - SIZE_STAGESELECT_BG_X, g_aTitlePos[1].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitlePos[1].x + SIZE_STAGESELECT_BG_X, g_aTitlePos[1].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitlePos[1].x - SIZE_STAGESELECT_BG_X, g_aTitlePos[1].y + SIZE_STAGESELECT_BG_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitlePos[1].x + SIZE_STAGESELECT_BG_X, g_aTitlePos[1].y + SIZE_STAGESELECT_BG_Y, 0.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//�I��(�����L���O����)
void InitTitleSelect1(int nCntTitle)
{
	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntTitle * 4;		//���_����i�߂�

	//�ʒu
	g_aTitlePos[2] = D3DXVECTOR3(POS_RANKING_BG_X, POS_RANKING_BG_Y, 0.0f);

	//���_���W�̐ݒ�(���_�͒�����)
	pVtx[0].pos = D3DXVECTOR3(g_aTitlePos[2].x - SIZE_RANKING_BG_X, g_aTitlePos[2].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitlePos[2].x + SIZE_RANKING_BG_X, g_aTitlePos[2].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitlePos[2].x - SIZE_RANKING_BG_X, g_aTitlePos[2].y + SIZE_RANKING_BG_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitlePos[2].x + SIZE_RANKING_BG_X, g_aTitlePos[2].y + SIZE_RANKING_BG_Y, 0.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//===================================
//�X�V�������̏���
//===================================
//�I������
void UpdateTitleSelect(void)
{
	//�t�F�[�h���̎擾
	FADE pFade = GetFade();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_S) == true || GetGamepadTrigger(BUTTON_DOWN, 0) == true || GetGamepad_LStick_Trigger(0, LSTICK_DOWN) == true)
		{
			//�I����
			PlaySound(SOUND_LABEL_CHOICE);

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 + (g_CurrentNumberTitle * 4);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffTitle->Unlock();

			//���ݒn����
			g_CurrentNumberTitle = (g_CurrentNumberTitle + 1) % NUM_SELECT;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 + (g_CurrentNumberTitle * 4);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffTitle->Unlock();
		}
		else if (GetKeyboardTrigger(DIK_W) == true || GetGamepadTrigger(BUTTON_UP, 0) == true || GetGamepad_LStick_Trigger(0, LSTICK_UP) == true)
		{
			//�I����
			PlaySound(SOUND_LABEL_CHOICE);

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 + (g_CurrentNumberTitle * 4);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffTitle->Unlock();

			//���ݒn��O��
			g_CurrentNumberTitle = (g_CurrentNumberTitle - 1 + NUM_SELECT) % NUM_SELECT;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 + (g_CurrentNumberTitle * 4);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffTitle->Unlock();
		}
	
		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadPress(BUTTON_START, 0) || GetGamepadTrigger(BUTTON_A, 0))
		{//����L�[(ENTER�L�[)�������ꂽ
			//���[�h�̐ݒ�(�Q�[����ʂɈڍs)
			if (bPress == false)
			{
				//���艹
				PlaySound(SOUND_LABEL_ENTER);
				StopSound(SOUND_LABEL_BGM_TITLE);

				//�e�N�X�`����ς��鏈��
				ChangeMeshDome();
				ChangeMeshCylinder();
				SetThunder();
				bTitle = false;
				SetBoolBillboard(false, true);
				//�J�����̈ړ�����
				MoveTitleCamera(0);

				bPress = true;
			}
		}
	}
}

//===================================
//3D�p
//===================================
//������
void Init3DTitle(void)
{
	//�J�����̏�����
	InitCamera();

	InitLight();

	InitMeshDome();

	InitMeshCylinder();

	InitObject00();

	InitBillboard();		//�r���{�[�h�̏���������

	//�h�A�̏���������
	InitExit();

	LoadExit(1);

	InitThunder();

	InitEffect();

	//�^�C�g���p�}�b�v�̏�����
	InitObjectBG();

	//�X�e�[�W�̓ǂݍ���
	SetStage(1);
}

//�I��
void Uninit3DTitle(void)
{
	UninitCamera();

	UninitLight();

	UninitMeshDome();

	UninitMeshCylinder();

	UninitObject00();

	UninitBillboard();		//�r���{�[�h�̏I������

	//�h�A�̏I������
	UninitExit();

	UninitThunder();

	UninitEffect();

	//�^�C�g���p�}�b�v�̏I��
	UninitObjectBG();
}

//�X�V
void Update3DTitle(void)
{
	UpdateCamera();

	UpdateLight();

	UpdateMeshDome();

	UpdateMeshCylinder();

	UpdateObject00();

	UpdateBillboard();

	//�h�A�̍X�V����
	UpdateExit();

	UpdateThunder();

	UpdateEffect();

	//�^�C�g���p�}�b�v�̍X�V
	UpdateObjectBG();
}

//�`��
void Draw3DTitle(void)
{
	SetCamera(4);

	DrawMeshDome();

	DrawMeshCylinder();

	DrawObject00();

	DrawBillboard();	//���̕`�揈���i�r���{�[�h�j

	//�^�C�g���p�}�b�v�̕`��
	DrawObjectBG();

	DrawEffect();

	//�h�A�̕`��
	DrawExit();

	DrawThunder();
}

