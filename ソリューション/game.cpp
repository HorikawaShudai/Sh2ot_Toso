#include "game.h"
#include "edit.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"
#include "objectBG.h"
#include "objectLight.h"
#include "ObjectWall.h"
#include "objectPoly.h"
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
#include "ActionHelpUI.h"
#include "sound.h"

//�G�f�B�b�g�Ɏg���I�u�W�F�N�g�̎�ނ̍\����
typedef enum
{
	EDIT_TYPE_NORMAL = 0,
	EDIT_TYPE_BG,
	EDIT_TYPE_POLY,
	EDIT_TYPE_WALL,
	EDIT_TYPE_LIGHT,
	EDIT_TYPE_MAX,
}EDIT_TYPE;

//�O���[�o���ϐ��錾
bool g_bPause = false;
bool g_bEdit = false;
int g_bBG_Edit = 0;
bool g_bGameClear = false;
GAMESTATE gGameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int GameSetEnemyCount = 0;

//====================================================================
//�Q�[����ʂ̏���������
//====================================================================
void InitGame()
{
	g_bPause = false;
	g_bEdit = false;
	g_bBG_Edit = 0;
	g_bGameClear = false;
	GameSetEnemyCount = 0;

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
	InitObjectLight();
	InitObjectWall();
	InitObjectPoly();

	//�v���C���[�̏���������
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	//�w���vUI�̏���������
	InitActionHelpUI();

	//�X�^�~�i�̏���������
	InitStamina();

	//���C�t�̏���������
	InitLife();

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
	SetFog(D3DFOG_LINEAR, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f), 10.0f, 1000.0f, 0.1f);
	
	//�v���C���[�̐��ɉ����ēG���Z�b�g����񐔂��w�肷��B
	switch (GetPlayNumberSelect().CurrentSelectNumber)
	{
	case 1:
		GameSetEnemyCount = 2;
		break;
	case 2:
		GameSetEnemyCount = 2;
		break;
	case 3:
		GameSetEnemyCount = 3;
		break;
	case 4:
		GameSetEnemyCount = 3;
		break;
	}

	//�G�ݒu�p�ϐ��̒l�̂Ԃ�G��ݒu����
	for (int nCnt = 0; nCnt < GameSetEnemyCount; nCnt++)
	{

	}
	SetEnemy(D3DXVECTOR3(-2162.46f, 0.0f, 1529.39f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(-832.0f, 0.0f, 1960.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(160.0f,  0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//�v���C���[�̐���������ݒu����
	for (int nCnt = 0; nCnt < GetPlayNumberSelect().CurrentSelectNumber; nCnt++)
	{
		int nKey;
		nKey = rand() % 9;
		SetKey(KeyPos[nKey], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	}

	//�X�e�[�W�̓ǂݍ���
	SetStage(0);
}

//====================================================================
//�Q�[����ʂ̏I������
//====================================================================
void UninitGame()
{
	////�T�E���h�̏I��
	//StopSound();

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
	UninitObjectLight();
	UninitObjectWall();
	UninitObjectPoly();

	//�v���C���[�̏I������
	UninitPlayer();

	//�G�̏I������
	UninitEnemy();

	//�w���vUI�̏I������
	UninitActionHelpUI();

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
	{//f3�������ꂽ�Ƃ�
		g_bBG_Edit++;
		if (g_bBG_Edit >= EDIT_TYPE_MAX)
		{
			g_bBG_Edit = 0;
		}
	}

	if (GetKeyboardTrigger(DIK_R) == true)
	{
		SetFade(MODE_GAME);
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

	//�I�u�W�F�N�g�̍X�V����
	UpdateObject00();
	UpdateObjectBG();
	UpdateObjectLight();
	UpdateObjectWall();
	UpdateObjectPoly();

	if (g_bEdit == true)
	{//�G�f�B�b�g���[�h�̎�

		//�G�f�B�b�g�̍X�V����
		UpdateEdit();

		switch (g_bBG_Edit)
		{
		case EDIT_TYPE_NORMAL:
			//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̍X�V����
			UpdateEditObject00();
			break;
		case EDIT_TYPE_BG:
			//�G�f�B�b�g���[�h�̃I�u�W�F�N�gBG�̍X�V����
			UpdateEditObjectBG();
			break;
		case EDIT_TYPE_POLY:
			//�G�f�B�b�g���[�h�̃I�u�W�F�N�gPoly�̍X�V����
			UpdateEditObjectPoly();
			break;
		case EDIT_TYPE_WALL:
			//�G�f�B�b�g���[�h�̃I�u�W�F�N�gWall�̍X�V����
			UpdateEditObjectWall();
			break;
		case EDIT_TYPE_LIGHT:
			//�G�f�B�b�g���[�h�̃I�u�W�F�N�gLight�̍X�V����
			UpdateEditObjectLight();
			break;
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

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�̍X�V����
		UpdateEnemy();

		//�w���vUI�̍X�V����
		UpdateActionHelpUI();

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

	switch (gGameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_CLEAR_END:		//�Q�[���N���A��
		g_nCounterGameState--;
		if (g_nCounterGameState <= 0)
		{
			gGameState = GAMESTATE_NORMAL;

			//�t�F�[�h�̏�Ԃ�ς���
			SetFade(MODE_RESULT);
			g_bGameClear = true;
		}
		break;

	case GAMESTATE_GAMEOVER_END:	//�Q�[���I�[�o�[��
		g_nCounterGameState--;
		if (g_nCounterGameState <= 0)
		{
			gGameState = GAMESTATE_NORMAL;

			//�t�F�[�h�̏�Ԃ�ς���
			SetFade(MODE_RESULT);
			g_bGameClear = false;
		}
		break;
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
			switch (g_bBG_Edit)
			{
			case EDIT_TYPE_NORMAL:
				//�G�f�B�b�g���[�h�̃I�u�W�F�N�g�̕`�揈��
				DrawEditObject00();
				break;
			case EDIT_TYPE_BG:
				//�G�f�B�b�g���[�h�̃I�u�W�F�N�gBG�̕`�揈��
				DrawEditObjectBG();
				break;
			case EDIT_TYPE_POLY:
				//�G�f�B�b�g���[�h�̃I�u�W�F�N�gPoly�̕`�揈��
				DrawEditObjectPoly();
				break;
			case EDIT_TYPE_WALL:
				//�G�f�B�b�g���[�h�̃I�u�W�F�N�gWall�̕`�揈��
				DrawEditObjectWall();
				break;
			case EDIT_TYPE_LIGHT:
				//�G�f�B�b�g���[�h�̃I�u�W�F�N�gLight�̕`�揈��
				DrawEditObjectLight();
				break;
			}
		}

		//���̕`�揈��
		DrawMeshField();

		//�I�u�W�F�N�g�̕`�揈��
		DrawObjectPoly();
		DrawObject00();
		DrawObjectBG();
		DrawObjectLight();
		DrawObjectWall();

		//�o���̕`�揈��
		DrawExit();

		//�v���C���[�̕`�揈��
		DrawPlayer();

		if (pPlayer->bAppear == true)
		{
			//�G�̕`�揈��
			DrawEnemy();
		}

		//�w���vUI�̕`�揈��
		DrawActionHelpUI();

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
//�N���A���̏���
//====================================================================
bool GetClear(void)
{
	return g_bGameClear;
}

//====================================================================
//�|�[�Y��Ԃ̐ݒ菈��
//====================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}