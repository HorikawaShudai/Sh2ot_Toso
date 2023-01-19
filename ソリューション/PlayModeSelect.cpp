//======================================================================================
//
// �X�e�[�W����[stage.cpp]
// Author:���}���@�V
//
//======================================================================================
#include <stdio.h>
#include "PlayModeSelect.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "debugproc.h"

//***********************************
//�}�N����`
//***********************************
#define MAX_TEX			(5)				//�e�N�X�`���̍ő吔
#define NUM_POLY		(NUM_PLAYMODE)	//�|���S���̐�
#define MAX_BUFF		(2)				//�o�b�t�@�̍ő吔

//***********************************
//�e�N�X�`���t�@�C����
//***********************************
const char *c_apFilenameStage[MAX_TEX] =
{
	"Data\\TEXTURE\\PLAYMODE\\PlayMode00.png",			//�^�C�g���w�i
	"data\\TEXTURE\\PLAYMODE\\PlayMode00.png",		//�I���A�C�R��(1�l)
	"data\\TEXTURE\\PLAYMODE\\PlayMode01.png",		//�I���A�C�R��(2�l)
	"data\\TEXTURE\\PLAYMODE\\PlayMode02.png",		//�I���A�C�R��(3�l)
	"data\\TEXTURE\\PLAYMODE\\PlayMode03.png",		//�I���A�C�R��(4�l)
};

//***********************************
//�v���g�^�C�v�錾
//***********************************
//������
void InitPlaySelectBg(void);
void InitPlaySelectIcon(void);
//�X�V
void PlayModeSelect(void);
//�`��
void DrawStageBg(void);
void DrawIcon(void);

//==================
//�O���[�o����`
//==================
LPDIRECT3DTEXTURE9 g_pTextureStage[MAX_TEX] = {};				//�e�N�X�`���ւ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage[MAX_BUFF] = {};			//���_�o�b�t�@�ւ�
D3DXCOLOR g_PaleColorSt;
D3DXCOLOR g_NormalColorSt;
PlayerModeSelect g_PlayModeSelect;

//========================================================================
// ���[�h�I���̏���������
//========================================================================
void InitPlayerModeSelect(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	for (int nCntTexture = 0; nCntTexture < MAX_TEX; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, c_apFilenameStage[nCntTexture], &g_pTextureStage[nCntTexture]);
	}

	//�\���̂̏�����
	g_PlayModeSelect.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PlayModeSelect.nType = 0;
	g_PlayModeSelect.CurrentSelectNumber = 0;
	g_PlayModeSelect.bStage = false;

	//�O���[�o���錾�̏�����
	g_PaleColorSt = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	g_NormalColorSt = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 
								D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
								&g_pVtxBuffStage[0], NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYMODE, 
								D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
								&g_pVtxBuffStage[1], NULL);

	InitPlaySelectBg();

	InitPlaySelectIcon();
}

//========================================================================
// ���[�h�I��w�i�̏���������
//========================================================================
void InitPlaySelectBg(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStage[0]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
	{
		pVtx[nCntrhw].rhw = 1.0f;
	}
	//���_�J���[(0.0f�`1.0f���Őݒ�)
	for (int nCntcol = 0; nCntcol < 4; nCntcol++)
	{
		pVtx[nCntcol].col = g_NormalColorSt;
	}

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStage[0]->Unlock();
}

//========================================================================
// ���[�h�I���A�C�R���̏���������
//========================================================================
void InitPlaySelectIcon(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStage[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStage = 0; nCntStage < NUM_PLAYMODE; nCntStage++)
	{
		if (nCntStage == 0)
		{
			g_PlayModeSelect.pos = D3DXVECTOR3(300.0f, 400.0f, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x - 50.0f, g_PlayModeSelect.pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x + 50.0f, g_PlayModeSelect.pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x - 50.0f, g_PlayModeSelect.pos.y + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x + 50.0f, g_PlayModeSelect.pos.y + 100.0f, 0.0f);
			//rhw�̐ݒ�
			for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
			{
				pVtx[nCntrhw].rhw = 1.0f;
			}
			//���_�J���[(0.0f�`1.0f���Őݒ�)
			for (int nCntcol = 0; nCntcol < 4; nCntcol++)
			{
				pVtx[nCntcol].col = g_NormalColorSt;
			}
			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;					//���_�f�[�^��4�����炷
		}
		else if (nCntStage < 5)
		{
			g_PlayModeSelect.pos = D3DXVECTOR3(300.0f + 170.0f * nCntStage, 400.0f, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x - 50.0f, g_PlayModeSelect.pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x + 50.0f, g_PlayModeSelect.pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x - 50.0f, g_PlayModeSelect.pos.y + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_PlayModeSelect.pos.x + 50.0f, g_PlayModeSelect.pos.y + 100.0f, 0.0f);
			//rhw�̐ݒ�
			for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
			{
				pVtx[nCntrhw].rhw = 1.0f;
			}
			//���_�J���[(0.0f�`1.0f���Őݒ�)
			for (int nCntcol = 0; nCntcol < 4; nCntcol++)
			{
				pVtx[nCntcol].col = g_PaleColorSt;
			}
			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;					//���_�f�[�^��4�����炷
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStage[1]->Unlock();

}

//========================================================================
// ���[�h�I���̏I������
//========================================================================
void UninitPlayerModeSelect(void)
{
	//�ϐ��錾
	int nCntStage;			//for�J�E���g�p

	for (nCntStage = 0; nCntStage < MAX_TEX; nCntStage++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureStage[nCntStage] != NULL)
		{
			g_pTextureStage[nCntStage]->Release();
			g_pTextureStage[nCntStage] = NULL;
		}
	}
	for (nCntStage = 0; nCntStage < MAX_BUFF; nCntStage++)
	{
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffStage[nCntStage] != NULL)
		{
			g_pVtxBuffStage[nCntStage]->Release();
			g_pVtxBuffStage[nCntStage] = NULL;
		}
	}
}

//========================================================================
// ���[�h�I���̍X�V����
//========================================================================
void UpdatePlayerModeSelect(void)
{
	//�X�e�[�W�I���̊֐�
	PlayModeSelect();

	//�f�o�b�O�\��
	PrintDebugProc("�I�� �y���z�y���z\n");
	PrintDebugProc("���� �yENTER�z\n");
	PrintDebugProc("�߂� �yB�z\n");
}

//========================================================================
// ���[�h�I���̕`�揈��
//========================================================================
void DrawPlayerModeSelect(void)
{
	//���[�h�Z���N�g�̔w�i
	DrawStageBg();

	//�I���A�C�R��
	DrawIcon();
}

//========================================================================
// ���[�h�I��w�i�̕`�揈��
//========================================================================
void DrawStageBg(void)
{
	//�f�o�C�X�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStage[0], 0,
		sizeof(VERTEX_2D));			//���_���\���̂̃T�C�Y

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureStage[0]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
		0,						//�`�悷��ŏ��̃C���f�b�N�X
		2);						//�v���~�e�B�u(�|���S��)��
}

//========================================================================
// ���[�h�I��I���A�C�R���̕`�揈��
//========================================================================
void DrawIcon(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStage[1], 0,
		sizeof(VERTEX_2D));			//���_���\���̂̃T�C�Y

	for (int nCntStage = 0; nCntStage < NUM_POLY; nCntStage++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureStage[nCntStage + 1]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
			nCntStage * 4,			//�`�悷��ŏ��̃C���f�b�N�X
			2);						//�v���~�e�B�u(�|���S��)��
	}
}

//========================================================================
// ���[�h�I���̑I������
//========================================================================
void PlayModeSelect(void)
{
	//�t�F�[�h���̎擾
	FADE pFade = GetFade();

	//���_���̃|�C���^
	VERTEX_2D *pVtx;

	if (GetKeyboardTrigger(DIK_D) == true/* || GetGamePadTrigger(BUTTON_3, 0) == true*/ && pFade == FADE_NONE)
	{
		//���_�o�b�t�@�����b�N
		g_pVtxBuffStage[1]->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += g_PlayModeSelect.CurrentSelectNumber * 4;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_PaleColorSt;
		pVtx[1].col = g_PaleColorSt;
		pVtx[2].col = g_PaleColorSt;
		pVtx[3].col = g_PaleColorSt;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffStage[1]->Unlock();

		//���ݒn����
		g_PlayModeSelect.CurrentSelectNumber = (g_PlayModeSelect.CurrentSelectNumber + 1) % NUM_PLAYMODE;

		//���_�o�b�t�@�����b�N
		g_pVtxBuffStage[1]->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += g_PlayModeSelect.CurrentSelectNumber * 4;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_NormalColorSt;
		pVtx[1].col = g_NormalColorSt;
		pVtx[2].col = g_NormalColorSt;
		pVtx[3].col = g_NormalColorSt;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffStage[1]->Unlock();
	}
	else if (GetKeyboardTrigger(DIK_A) == true/* || GetGamePadTrigger(BUTTON_2, 0) == true*/ && pFade == FADE_NONE)
	{
		//���_�o�b�t�@�����b�N
		g_pVtxBuffStage[1]->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += g_PlayModeSelect.CurrentSelectNumber * 4;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_PaleColorSt;
		pVtx[1].col = g_PaleColorSt;
		pVtx[2].col = g_PaleColorSt;
		pVtx[3].col = g_PaleColorSt;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffStage[1]->Unlock();

		//���ݒn��O��
		g_PlayModeSelect.CurrentSelectNumber = (g_PlayModeSelect.CurrentSelectNumber - 1 + NUM_PLAYMODE) % NUM_PLAYMODE;

		//���_�o�b�t�@�����b�N
		g_pVtxBuffStage[1]->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * g_PlayModeSelect.CurrentSelectNumber;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_NormalColorSt;
		pVtx[1].col = g_NormalColorSt;
		pVtx[2].col = g_NormalColorSt;
		pVtx[3].col = g_NormalColorSt;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffStage[1]->Unlock();
	}

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(BUTTON_START, 0) || GetGamepadPress(BUTTON_A, 0))
		{//����L�[(ENTER�L�[)�������ꂽ
			if (g_PlayModeSelect.CurrentSelectNumber >= 0 && g_PlayModeSelect.CurrentSelectNumber < NUM_PLAYMODE)
			{
				SetFade(MODE_GAME);			//���[�h�̐ݒ�(�Q�[����ʂɈڍs)
			}
		}
		else if (GetKeyboardTrigger(DIK_B) == true/* || GetGamePadTrigger(BUTTON_B, 0) == true*/ && pFade == FADE_NONE)
		{//�L�[(B)�������ꂽ
			SetFade(MODE_TITLE);				//���[�h�̐ݒ�(�^�C�g����ʂɈڍs)
		}
	}
}

//========================================================================
// ���[�h�I�����̎擾
//========================================================================
PlayerModeSelect GetPlayerModeSelect(void)
{
	return g_PlayModeSelect;
}