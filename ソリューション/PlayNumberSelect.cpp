//======================================================================================
//
// �v���C�l���I���̏���[PlayNumberselect.cpp]
// Author:���}���@�V
//
//======================================================================================
#include <stdio.h>
#include "PlayNumberSelect.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "debugproc.h"
#include "camera.h"
#include "playerBG.h"
#include "light.h"
#include "objectBG.h"
#include "stage.h"
#include "object00.h"
#include "ObjectWall.h"
#include "sound.h"
#include "Exit.h"

//***********************************
//�}�N����`
//***********************************
#define MAX_TEX			(5)				//�e�N�X�`���̍ő吔
#define NUM_POLY		(NUM_PLAYNUMBER)	//�|���S���̐�
#define MAX_BUFF		(2)				//�o�b�t�@�̍ő吔

#define POS_X			(350.0f)		//���ڂ̈ʒu(X)
#define POS_Y			(200.0f)		//���ڂ̈ʒu(Y)
#define SPACE_X			(200.0f)		//���ړ��m�̊Ԃ̍L��
#define WIDTH_SIZE		(70.0f)			//���ڂ̑傫��(X)
#define HEIGHT_SIZE		(70.0f)			//���ڂ̑傫��(Y)

//***********************************
//�e�N�X�`���t�@�C����
//***********************************
const char *c_apFilenamePlayNumberSelect[MAX_TEX] =
{
	"data\\TEXTURE\\PLAYMODE\\PlayMode00.png",		//�I���A�C�R��(1�l)
	"data\\TEXTURE\\PLAYMODE\\PlayMode01.png",		//�I���A�C�R��(2�l)
	"data\\TEXTURE\\PLAYMODE\\PlayMode02.png",		//�I���A�C�R��(3�l)
	"data\\TEXTURE\\PLAYMODE\\PlayMode03.png",		//�I���A�C�R��(4�l)
	"data\\TEXTURE\\RANKING\\Osumi00.png",			//�n�̃t���[��
};

//***********************************
//�v���g�^�C�v�錾
//***********************************
//������
void InitPlaySelectIcon(void);
void InitPlaySelectBg(void);
//�X�V
void PlayerSelect(void);
//�`��
void DrawPlayNumberSelectIcon(void);
void DrawPlayNumberSelectBg(void);

//3D�w�i�p
void Init3DSelect(void);
void Uninit3DSelect(void);
void Update3DSelect(void);
void Draw3DSelect(void);

//==================
//�O���[�o����`
//==================
LPDIRECT3DTEXTURE9 g_apTexPlayNumberSelect[MAX_TEX] = {};				//�e�N�X�`���ւ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayNumberSelect[MAX_BUFF] = {};			//���_�o�b�t�@�ւ�
D3DXCOLOR g_PaleColorPns;
D3DXCOLOR g_NormalColorPns;
PlayNumberSelect g_PlayNumberSelect;

//========================================================================
// ���[�h�I���̏���������
//========================================================================
void InitPlayNumberSelect(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	for (int nCntTexture = 0; nCntTexture < MAX_TEX; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, c_apFilenamePlayNumberSelect[nCntTexture], &g_apTexPlayNumberSelect[nCntTexture]);
	}

	//�\���̂̏�����
	g_PlayNumberSelect.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PlayNumberSelect.CurrentSelectNumber = 0;
	g_PlayNumberSelect.bUse = true;
	g_PlayNumberSelect.bPush = false;

	//�O���[�o���錾�̏�����
	g_PaleColorPns = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	g_NormalColorPns = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@�̐���[0]
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYNUMBER,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
		&g_pVtxBuffPlayNumberSelect[0], NULL);

	//���_�o�b�t�@�̐���[1]
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
		&g_pVtxBuffPlayNumberSelect[1], NULL);

	InitPlaySelectIcon();

	//3D
	Init3DSelect();

	//�w�i�̏�����
	InitPlaySelectBg();
}

//========================================================================
// ���[�h�I���̏I������
//========================================================================
void UninitPlayNumberSelect(void)
{
	//�ϐ��錾
	int nCntStage;			//for�J�E���g�p

	for (nCntStage = 0; nCntStage < MAX_TEX; nCntStage++)
	{
		//�e�N�X�`���̔j��
		if (g_apTexPlayNumberSelect[nCntStage] != NULL)
		{
			g_apTexPlayNumberSelect[nCntStage]->Release();
			g_apTexPlayNumberSelect[nCntStage] = NULL;
		}
	}
	for (int nCntBuff = 0; nCntBuff < MAX_BUFF; nCntBuff++)
	{
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffPlayNumberSelect[nCntBuff] != NULL)
		{
			g_pVtxBuffPlayNumberSelect[nCntBuff]->Release();
			g_pVtxBuffPlayNumberSelect[nCntBuff] = NULL;
		}
	}
	

	//3D
	Uninit3DSelect();
}

//========================================================================
// ���[�h�I���̍X�V����
//========================================================================
void UpdatePlayNumberSelect(void)
{
	//�v���C�l���̏��擾

	//�X�e�[�W�I���̊֐�
	PlayerSelect();

	//3D
	Update3DSelect();

	//�f�o�b�O�\��
	PrintDebugProc("�I�� �y���z�y���z\n");
	PrintDebugProc("���� �yENTER�z\n");
	PrintDebugProc("�߂� �yB�z\n");
}

//========================================================================
// ���[�h�I���̕`�揈��
//========================================================================
void DrawPlayNumberSelect(void)
{
	//�v���C�l���̏��擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//3D
	Draw3DSelect();

	//�I��w�i�̕`�揈��
	DrawPlayNumberSelectBg();

	//�I���A�C�R���̏�����
	DrawPlayNumberSelectIcon();
}

//========================================================================
// ���[�h�I���A�C�R���̏���������
//========================================================================
void InitPlaySelectIcon(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayNumberSelect[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStage = 0; nCntStage < NUM_PLAYNUMBER; nCntStage++)
	{
		if (nCntStage == 0)
		{
			g_PlayNumberSelect.pos = D3DXVECTOR3(POS_X, POS_Y, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x - WIDTH_SIZE, g_PlayNumberSelect.pos.y - HEIGHT_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x + WIDTH_SIZE, g_PlayNumberSelect.pos.y - HEIGHT_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x - WIDTH_SIZE, g_PlayNumberSelect.pos.y + HEIGHT_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x + WIDTH_SIZE, g_PlayNumberSelect.pos.y + HEIGHT_SIZE, 0.0f);
			//rhw�̐ݒ�
			for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
			{
				pVtx[nCntrhw].rhw = 1.0f;
			}
			//���_�J���[(0.0f�`1.0f���Őݒ�)
			for (int nCntcol = 0; nCntcol < 4; nCntcol++)
			{
				pVtx[nCntcol].col = g_NormalColorPns;
			}
			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;					//���_�f�[�^��4�����炷
		}
		else
		{
			g_PlayNumberSelect.pos = D3DXVECTOR3(POS_X + SPACE_X * nCntStage, POS_Y, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x - WIDTH_SIZE, g_PlayNumberSelect.pos.y - HEIGHT_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x + WIDTH_SIZE, g_PlayNumberSelect.pos.y - HEIGHT_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x - WIDTH_SIZE, g_PlayNumberSelect.pos.y + HEIGHT_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_PlayNumberSelect.pos.x + WIDTH_SIZE, g_PlayNumberSelect.pos.y + HEIGHT_SIZE, 0.0f);
			//rhw�̐ݒ�
			for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
			{
				pVtx[nCntrhw].rhw = 1.0f;
			}
			//���_�J���[(0.0f�`1.0f���Őݒ�)
			for (int nCntcol = 0; nCntcol < 4; nCntcol++)
			{
				pVtx[nCntcol].col = g_PaleColorPns;
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
	g_pVtxBuffPlayNumberSelect[0]->Unlock();
}

//========================================================================
// ���[�h�I����ʂ̔w�i�̏���������
//========================================================================
void InitPlaySelectBg(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayNumberSelect[1]->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[nCntcol].col = g_NormalColorPns;
	}

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayNumberSelect[1]->Unlock();
}

//========================================================================
// ���[�h�I��I���A�C�R���̕`�揈��
//========================================================================
void DrawPlayNumberSelectIcon(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayNumberSelect[0], 0,
		sizeof(VERTEX_2D));			//���_���\���̂̃T�C�Y

	for (int nCntStage = 0; nCntStage < NUM_POLY; nCntStage++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexPlayNumberSelect[nCntStage]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
			nCntStage * 4,			//�`�悷��ŏ��̃C���f�b�N�X
			2);						//�v���~�e�B�u(�|���S��)��
	}
}

//========================================================================
// ���[�h�I��I���A�C�R���̕`�揈��
//========================================================================
void DrawPlayNumberSelectBg(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayNumberSelect[1], 0,
		sizeof(VERTEX_2D));			//���_���\���̂̃T�C�Y
	
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTexPlayNumberSelect[4]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
		0,			//�`�悷��ŏ��̃C���f�b�N�X
		2);						//�v���~�e�B�u(�|���S��)��
}

//========================================================================
// ���[�h�I���̑I������
//========================================================================
void PlayerSelect(void)
{
	//�t�F�[�h���̎擾
	FADE pFade = GetFade();

	//�v���C�l���̏��擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//���_���̃|�C���^
	VERTEX_2D *pVtx;

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_D) == true || GetGamepadTrigger(BUTTON_RIGHT, 0) == true || GetGamepad_LStick_Trigger(0, LSTICK_RIGHT) == true)
		{
			//�I����
			PlaySound(SOUND_LABEL_CHOICE);

			//���_�o�b�t�@�����b�N
			g_pVtxBuffPlayNumberSelect[0]->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += g_PlayNumberSelect.CurrentSelectNumber * 4;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_PaleColorPns;
			pVtx[1].col = g_PaleColorPns;
			pVtx[2].col = g_PaleColorPns;
			pVtx[3].col = g_PaleColorPns;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPlayNumberSelect[0]->Unlock();

			//���ݒn����
			g_PlayNumberSelect.CurrentSelectNumber = (g_PlayNumberSelect.CurrentSelectNumber + 1) % NUM_PLAYNUMBER;

			//���_�o�b�t�@�����b�N
			g_pVtxBuffPlayNumberSelect[0]->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += g_PlayNumberSelect.CurrentSelectNumber * 4;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_NormalColorPns;
			pVtx[1].col = g_NormalColorPns;
			pVtx[2].col = g_NormalColorPns;
			pVtx[3].col = g_NormalColorPns;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPlayNumberSelect[0]->Unlock();
		}
		else if (GetKeyboardTrigger(DIK_A) == true || GetGamepadTrigger(BUTTON_LEFT, 0) == true || GetGamepad_LStick_Trigger(0, LSTICK_LEFT) == true)
		{
			//�I����
			PlaySound(SOUND_LABEL_CHOICE);

			//���_�o�b�t�@�����b�N
			g_pVtxBuffPlayNumberSelect[0]->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += g_PlayNumberSelect.CurrentSelectNumber * 4;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_PaleColorPns;
			pVtx[1].col = g_PaleColorPns;
			pVtx[2].col = g_PaleColorPns;
			pVtx[3].col = g_PaleColorPns;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPlayNumberSelect[0]->Unlock();

			//���ݒn��O��
			g_PlayNumberSelect.CurrentSelectNumber = (g_PlayNumberSelect.CurrentSelectNumber - 1 + NUM_PLAYNUMBER) % NUM_PLAYNUMBER;

			//���_�o�b�t�@�����b�N
			g_pVtxBuffPlayNumberSelect[0]->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * g_PlayNumberSelect.CurrentSelectNumber;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_NormalColorPns;
			pVtx[1].col = g_NormalColorPns;
			pVtx[2].col = g_NormalColorPns;
			pVtx[3].col = g_NormalColorPns;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPlayNumberSelect[0]->Unlock();
		}

		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_START, 0) || GetGamepadTrigger(BUTTON_A, 0))
		{//����L�[(ENTER�L�[)�������ꂽ

			//���艹
			PlaySound(SOUND_LABEL_ENTER);

			if (g_PlayNumberSelect.CurrentSelectNumber >= 0 && g_PlayNumberSelect.CurrentSelectNumber < PLAYNUMBER_MAX)
			{
				g_PlayNumberSelect.CurrentSelectNumber = g_PlayNumberSelect.CurrentSelectNumber + 1;			//�v���C�l���ɍ��킹�邽��

				SetFade(MODE_TUTORIAL);			//���[�h�̐ݒ�(�Q�[����ʂɈڍs)
			}
			else if (g_PlayNumberSelect.CurrentSelectNumber == PLAYNUMBER_MAX)
			{
				g_PlayNumberSelect.CurrentSelectNumber = 4;			//�v���C�l���ɍ��킹�邽��

				g_PlayNumberSelect.bUse = false;
			}
			g_PlayNumberSelect.bPush = true;
		}
		else if (GetKeyboardTrigger(DIK_B) || GetGamepadTrigger(BUTTON_B, 0))
		{
			SetFade(MODE_TITLE);			//���[�h�̐ݒ�(�Q�[����ʂɈڍs)
		}
	}
}


//========================================================================
//3D�p
//========================================================================
//������
void Init3DSelect(void)
{
	InitCamera();

	InitLight();

	InitPlayerBG();

	InitExit();

	//�I�u�W�F�N�g�̏�����
	InitObject00();

	//�^�C�g���p�}�b�v�̏�����
	InitObjectBG();
	InitObjectWall();

	//�X�e�[�W�̓ǂݍ���
	SetStage(2);

	SetExit(D3DXVECTOR3(-80.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 0, 0);
	SetExit(D3DXVECTOR3(80.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 0, 0);
	SetExit(D3DXVECTOR3(0.0f, 100.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 1, 0);
	SetExit(D3DXVECTOR3(-70.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 2, 0);
	SetExit(D3DXVECTOR3(70.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 3, 0);
}

//�I��
void Uninit3DSelect(void)
{
	UninitCamera();

	UninitLight();

	UninitPlayerBG();

	UninitExit();

	//�I�u�W�F�N�g�̏I��
	UninitObject00();

	//�^�C�g���p�I�u�W�F�N�g�̏I��
	UninitObjectBG();
	UninitObjectWall();
}

//�X�V
void Update3DSelect(void)
{
	UpdateCamera();

	UpdateLight();

	UpdatePlayerBG();

	UpdateExit();

	//�I�u�W�F�N�g�̍X�V
	UpdateObject00();

	//�^�C�g���p�I�u�W�F�N�g�̍X�V
	UpdateObjectBG();
	UpdateObjectWall();
}

//�`��
void Draw3DSelect(void)
{
	SetCamera(4);

	DrawPlayerBG();

	DrawExit();

	//�I�u�W�F�N�g�̕`��
	DrawObject00();

	//�^�C�g���p�I�u�W�F�N�g�̕`��
	DrawObjectBG();
	DrawObjectWall();
}

//========================================================================
// ���[�h�I�����̎擾
//========================================================================
PlayNumberSelect GetPlayNumberSelect(void)
{
	return g_PlayNumberSelect;
}