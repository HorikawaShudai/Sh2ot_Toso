#include "game.h"
#include "edit.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"
#include "objectBG.h"
#include "stage.h"
#include "player.h"
#include "debugproc.h"
#include "enemy.h"
#include "stamina.h"
#include "life.h"
#include "meshfield.h"
#include "meshfield.h"
#include "score_item.h"
#include "score.h"
#include "PlayNumberSelect.h"
#include "key.h"
#include "keyUI.h"
#include "Effect.h"
#include "exit.h"
#include "SpotLight.h"
#include "polygonBG.h"
#include "fog.h"
#include "time.h"

//�O���[�o���ϐ��錾
bool g_bPause = false;
bool g_bEdit = false;
bool g_bBG_Edit = false;
GAMESTATE gGameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//====================================================================
//�Q�[����ʂ̏���������
//====================================================================
void InitGame()
{
	g_bPause = false;
	g_bEdit = false;
	g_bBG_Edit = false;

	DWORD time = timeGetTime();
	srand((unsigned int)time);
	SetGameState(GAMESTATE_READY, 60);

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//InitSpotLight();

	//���̏���������
	InitMeshField();

	//���b�V���ǂ̏���������
	InitMeshWall();

	//�I�u�W�F�N�g�̏���������
	InitObject00();
	InitObjectBG();

	//�v���C���[�̏���������
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	//�X�^�~�i�̏���������
	InitStamina();

	//���C�t�̏���������
	InitLife();


	SetEnemy(D3DXVECTOR3(300.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(-2500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//�X�R�A�̏�����
	InitScore();

	//���̏���������
	InitKey();

	//��UI�̏���������
	InitKeyUI();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�o���̏���������
	InitExit();

	//�X�R�A�A�C�e���̏�����
	InitItem();

	InitPolygonBG();

	InitTime();

	//�t�H�O�̏�����
	InitFog();

	//�t�H�O�̐ݒ�
	SetFog(D3DFOG_LINEAR, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), 10.0f, 1000.0f, 0.1f);

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

	SetKey(D3DXVECTOR3(-1000.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(150.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(-50.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetKey(D3DXVECTOR3(50.0f, 0.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//�X�e�[�W�̓ǂݍ���
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

	//UninitSpotLight();

	//���̏I������
	UninitMeshField();

	//���b�V���ǂ̏I������
	UninitMeshWall();

	//�I�u�W�F�N�g�̏I������
	UninitObject00();
	UninitObjectBG();

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

	//�o���̏I������
	UninitExit();

	UninitTime();

	UninitPolygonBG();

	//�t�H�O�̏I������
	UninitFog();
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

	if (GetKeyboardTrigger(DIK_F3) == true)
	{//f2�������ꂽ�Ƃ�
		g_bBG_Edit = g_bBG_Edit ? false : true;
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

	//UpdateSpotLight();

	//���b�V���̕ǂ̍X�V����
	UpdateMeshWall();

	if (g_bEdit == true)
	{//�G�f�B�b�g���[�h�̎�

		//�G�f�B�b�g�̍X�V����
		UpdateEdit();

		if (g_bBG_Edit == false)
		{
			//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̍X�V����
			UpdateEditObject00();
		}
		else
		{
			//�G�f�B�b�g���[�h�̃I�u�W�F�N�gBG�̍X�V����
			UpdateEditObjectBG();
		}
	}
	else
	{//�ʏ탂�[�h�̎�

		PrintDebugProc("�J�����̎��_�ړ��yW�z�yA�z�yS�z�yD�z\n");
		PrintDebugProc("�J�����̒����_�ړ� �yI�z�yJ�z�yK�z�yL�z\n");
		PrintDebugProc("�J�����̏㉺�ړ� �y��SHIFT�z�y��CTRL�z\n");
		PrintDebugProc("�v���C���[�̈ړ��ړ� �yT�z�yF�z�yG�z�yH�z\n");
		PrintDebugProc("�f�o�b�O�\���̃I��/�I�t �yF1�z\n");
		PrintDebugProc("�G�f�B�b�g���[�h�̃I��/�I�t �yF2�z\n");
		PrintDebugProc("�Q�[���p�Ɣw�i�p�I�u�W�F�N�g�̐؂�ւ� �yF3�z\n");
		PrintDebugProc("�v���C���[�̎��_�؂�ւ� �yF4�z\n");
		PrintDebugProc("�v���C���[�J�����Ɗώ@�p�J�����̐؂�ւ� �yF5�z\n");
		PrintDebugProc("�o�C�u���[�V�������I���ɂ��� �yF6�z\n");
		PrintDebugProc("�o�C�u���[�V�������I�t�ɂ��� �yF7�z\n");
		PrintDebugProc("�i�C�g�r�W�����̃I��/�I�t �yF8�z\n");
		PrintDebugProc("�G�f�B�b�g���[�h���̃Z�[�u �yF9�z\n");
		PrintDebugProc("���C���[�t���[���̃I��/�I�t�yF11�z\n");

		//���̍X�V����
		UpdateMeshField();

		//�I�u�W�F�N�g�̍X�V����
		UpdateObject00();
		UpdateObjectBG();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�̍X�V����
		//UpdateEnemy();

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

		//�o���̍X�V����
		UpdateExit();

		UpdateTime();

		UpdatePolygonBG();
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

	Player *pPlayer = GetPlayer();

	//���݂̃r���[�|�[�g���擾
	pDevice->GetViewport(&viewportDef);
	 
	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++,pPlayer++)
	{
		//�J�����̃Z�b�g����
		SetCamera(nCnt);

		//���b�V���E�H�[���̕`�揈��
		DrawMeshWall();

		if (g_bEdit == true)
		{
			if (g_bBG_Edit == false)
			{
				//�G�f�B�b�g���[�h�̃I�u�W�F�N�g����
				DrawEditObject00();
			}
			else
			{
				//�G�f�B�b�g���[�h�̃I�u�W�F�N�g����
				DrawEditObjectBG();
			}
		}

		//���̕`�揈��
		DrawMeshField();

		//�I�u�W�F�N�g�̕`�揈��
		DrawObject00();
		DrawObjectBG();

		//�o���̕`�揈��
		DrawExit();

		//�v���C���[�̕`�揈��
		DrawPlayer();

		if (pPlayer->bAppear == true)
		{
			//�G�̕`�揈��
			DrawEnemy();
		}

		//�X�^�~�i�̕`�揈��
		DrawStamina();

		//���C�t�̕`�揈��
		DrawLife();

		DrawTime();

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

		DrawPolygonBG();

		//�t�H�O�̕`��
		DrawFog();
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