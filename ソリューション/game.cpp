#include "game.h"
#include "edit.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"
#include "stage.h"
#include "player.h"
#include "debugproc.h"
#include "enemy.h"
#include "stamina.h"
#include "life.h"
#include "field.h"
#include "score_item.h"
#include "score.h"
#include "PlayNumberSelect.h"
#include "key.h"
#include "keyUI.h"
#include "Effect.h"

//�O���[�o���ϐ��錾
bool g_bPause = false;
bool g_bEdit = false;
GAMESTATE gGameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//====================================================================
//�Q�[����ʂ̏���������
//====================================================================
void InitGame()
{
	g_bPause = false;
	g_bEdit = false;

	DWORD time = timeGetTime();
	srand((unsigned int)time);
	SetGameState(GAMESTATE_READY, 60);

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//���̏���������
	InitField();

	//���b�V���ǂ̏���������
	InitMeshWall();

	//�I�u�W�F�N�g�̏���������
	InitObject00();

	//�v���C���[�̏���������
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	//�X�^�~�i�̏���������
	InitStamina();

	//���C�t�̏���������
	InitLife();

	//���ӁF�G�̍��W��n100+50�������Ƃ���
	SetEnemy(D3DXVECTOR3(50.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//�X�R�A�̏�����
	InitScore();

	//���̏���������
	InitKey();

	//��UI�̏���������
	InitKeyUI();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�X�R�A�A�C�e���̏�����
	InitItem();
	SetItem(D3DXVECTOR3(0.0f,0.0f,-40.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), 0);
	SetItem(D3DXVECTOR3(40.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(100.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(150.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(-50.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(-100.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(-150.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(-200.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(200.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(250.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(250.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(150.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(-50.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(50.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	SetStage(0);
}

//====================================================================
//�Q�[����ʂ̏I������
//====================================================================
void UninitGame()
{
	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//���̏I������
	UninitField();

	//���b�V���ǂ̏I������
	UninitMeshWall();

	//�I�u�W�F�N�g�̏I������
	UninitObject00();

	//�v���C���[�̏I������
	UninitPlayer();

	//�G�̏I������
	UninitEnemy();

	//�X�^�~�i�̏I������
	UninitStamina();

	//���C�t�̏I������
	UninitLife();

	//�X�R�A�̏I������
	UninitScore();

	//�A�C�e���̏I������
	UninitItem();

	//���̏I������
	UninitKey();

	//��UI�̏I������
	UninitKeyUI();

	//�G�t�F�N�g�̏I������
	UninitEffect();
}

//====================================================================
//�Q�[����ʂ̍X�V����
//====================================================================
void UpdateGame()
{

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F2) == true)
	{//f2�������ꂽ�Ƃ�
		g_bEdit = g_bEdit ? false : true;
	}
#endif

	if (g_bPause == false && g_bEdit == false)
	{//�|�[�Y��Ԃ���Ȃ��Ƃ����G�f�B�b�g��Ԃ���Ȃ��Ƃ�
		FADE Fade = GetFade();

		if (Fade == FADE_NONE)
		{
			if (GetKeyboardPress(DIK_RETURN))
			{//ENTER�L�[���������Ƃ����U���g�Ƀt�F�[�h
				SetFade(MODE_RESULT);
			}
		}
	}

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	//���b�V���̕ǂ̍X�V����
	UpdateMeshWall();

	if (g_bEdit == true)
	{//�G�f�B�b�g���[�h�̎�

		//�G�f�B�b�g�̍X�V����
		UpdateEdit();

		//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̍X�V����
		UpdateEditObject00();

		PrintDebugProc("�J�����̎��_�ړ��yW�z�yA�z�yS�z�yD�z\n");
		PrintDebugProc("�J�����̒����_�ړ� �yI�z�yJ�z�yK�z�yL�z\n");
		PrintDebugProc("�J�����̏㉺�ړ� �y��SHIFT�z�y��CTRL�z\n");
		PrintDebugProc("�v���C���[�̈ړ��ړ� �yT�z�yF�z�yG�z�yH�z\n");
	}
	else
	{//�ʏ탂�[�h�̎�

		//���̍X�V����
		UpdateField();

		//�I�u�W�F�N�g�̍X�V����
		UpdateObject00();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�̍X�V����
		UpdateEnemy();

		//�X�^�~�i�̍X�V����
		UpdateStamina();

		//���C�t�̍X�V����
		UpdateLife();


		//�X�R�A�̍X�V����
		UpdateScore();

		//�X�R�A�A�C�e���̍X�V����
		UpdateItem();

		//���̍X�V����
		UpdateKey();

		//��UI�̍X�V����
		UpdateKeyUI();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();
	}
}

//====================================================================
//�Q�[����ʂ̕`�揈��
//====================================================================
void DrawGame()
{
	D3DVIEWPORT9 viewportDef;

	//�f�o�C�X�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//���݂̃r���[�|�[�g���擾
	pDevice->GetViewport(&viewportDef);
	 
	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		//�J�����̃Z�b�g����
		SetCamera(nCnt);

		//���b�V���E�H�[���̕`�揈��
		DrawMeshWall();

		if (g_bEdit == true)
		{
			//�G�f�B�b�g���[�h�̃I�u�W�F�N�g����
			DrawEditObject00();
		}

		//���̕`�揈��
		DrawField();

		//�I�u�W�F�N�g�̕`�揈��
		DrawObject00();

		//�v���C���[�̕`�揈��
		DrawPlayer();

		//�G�̕`�揈��
		DrawEnemy();

		//�X�^�~�i�̕`�揈��
		DrawStamina();

		//���C�t�̕`�揈��
		DrawLife();

		//�X�R�A�̕`�揈��
		DrawScore();

		//�X�R�A�A�C�e���̕`�揈��
		DrawItem();

		//���̕`�揈��
		DrawKey();

		//��UI�̕`�揈��
		DrawKeyUI();

		//�G�t�F�N�g�̕`�揈��
		DrawEffect();
	}

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);
}

//====================================================================
//�Q�[���̏�Ԃ̐ݒ�
//====================================================================
void SetGameState(GAMESTATE state, int nCounter)
{
	gGameState = state;
	g_nCounterGameState = nCounter;
}

//====================================================================
//�Q�[�����[�h�̏���
//====================================================================
GAMESTATE GetGameState()
{
	return gGameState;
}

//====================================================================
//�|�[�Y��Ԃ̐ݒ菈��
//====================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}