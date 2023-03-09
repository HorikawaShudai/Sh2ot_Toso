#include "game.h"
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
#include "paperBG00.h"
#include "paperBG01.h"
#include "tutorialUI.h"
#include "CheckboxUI.h"
#include "EscapeTutorial.h"
#include "ActionHelpUI.h"
#include "player.h"
#include "sound.h"
#include "particle.h"
#include "ChasePolygon.h"
#include "NeedKeyPolygon.h"

//�O���[�o���ϐ��錾
TUTORIAL_STATE g_EscapeTutorialState;
TUTORIAL_GUYDE g_EscapeTutorialGuyde;
int g_EscapeCounter;
TUTORIAL_MODE g_EscapeTutorial;
bool bpEscapeMove[NUM_PLAYER];
bool bpEscapeCamMove[NUM_PLAYER];

//====================================================================
//�`���[�g���A����ʂ̏���������
//====================================================================
void InitEscapeTutorial()
{
	g_EscapeTutorialState = TUTORIAL_STATE_GUYDE;
	g_EscapeTutorialGuyde = TUTORIAL_GUYDE_ESCAPE;
	g_EscapeTutorial = MODE_MOVE;
	g_EscapeCounter = 0;

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		bpEscapeMove[nCntPlayer] = true;
		bpEscapeCamMove[nCntPlayer] = true;
	}

	for (int nCntPlayer = 0; nCntPlayer < GetPlayNumberSelect().CurrentSelectNumber; nCntPlayer++)
	{
		bpEscapeMove[nCntPlayer] = false;
		bpEscapeCamMove[nCntPlayer] = false;
	}

	DWORD time = timeGetTime();
	srand((unsigned int)time);

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

	////�X�R�A�̏�����
	//InitScore();

	//���̏���������
	InitKey();

	//��UI�̏���������
	InitKeyUI();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�p�[�e�B�N���̏�����
	InitParticle();

	//�o���̏���������
	InitExit();

	////�X�R�A�A�C�e���̏�����
	//InitItem();

	InitNeedKeyPolygon();

	InitActionHelpUI();

	InitChasePolygon();

	InitPolygonBG();

	InitTime();

	InitPaperBG00();
	InitPaperBG01();

	InitTutorialUI();

	//�`�F�b�N�{�b�N�X�̏�����
	InitCheckboxUI();

	//�t�H�O�̏�����
	InitFog();

	//�t�H�O�̐ݒ�
	SetFog(D3DFOG_LINEAR, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), 10.0f, 1000.0f, 0.1f);

	//�o����ǂݍ���
	LoadExit(2);

	//�X�e�[�W�̓ǂݍ���
	SetStage(4);
}

//====================================================================
//�`���[�g���A����ʂ̏I������
//====================================================================
void UninitEscapeTutorial()
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

	////�X�R�A�̏I������
	//UninitScore();

	////�A�C�e���̏I������
	//UninitItem();

	//���̏I������
	UninitKey();

	//��UI�̏I������
	UninitKeyUI();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�o���̏I������
	UninitExit();

	UninitNeedKeyPolygon();

	UninitActionHelpUI();

	UninitChasePolygon();

	UninitTime();

	UninitPaperBG00();
	UninitPaperBG01();

	UninitTutorialUI();

	UninitCheckboxUI();

	UninitPolygonBG();

	//�t�H�O�̏I������
	UninitFog();
}

//====================================================================
//�`���[�g���A����ʂ̍X�V����
//====================================================================
void UpdateEscapeTutorial()
{
	FADE pFade = GetFade();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	int nPlayer = GetCurrentCamera();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_V))
	{
		switch (g_EscapeTutorialState)
		{
		case TUTORIAL_STATE_GUYDE:
			g_EscapeTutorialState = TUTORIAL_STATE_STANDBY;
			break;
		case TUTORIAL_STATE_STANDBY:
			g_EscapeTutorialState = TUTORIAL_STATE_WAIT;
			break;
		case TUTORIAL_STATE_WAIT:
			g_EscapeTutorialState = TUTORIAL_STATE_PLAY;
			break;
		case TUTORIAL_STATE_PLAY:
			break;
		}
	}

#endif

	//�K�C�h�̃y�[�W��i�܂��鏈��
	if (GetKeyboardTrigger(DIK_C) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
	{

		switch (g_EscapeTutorialGuyde)
		{
		case TUTORIAL_GUYDE_ESCAPE:
			g_EscapeTutorialGuyde = TUTORIAL_GUYDE_KEY;

			//�����߂��鉹
			PlaySound(SOUND_LABEL_PAPER);
			break;

		case TUTORIAL_GUYDE_KEY:
			g_EscapeTutorialGuyde = TUTORIAL_GUYDE_HEALTH;

			//�����߂��鉹
			PlaySound(SOUND_LABEL_PAPER);
			break;

		case TUTORIAL_GUYDE_HEALTH:
			g_EscapeTutorialGuyde = TUTORIAL_GUYDE_MAX;
			break;
		}
	}

	//�K�C�h�̃y�[�W��߂�����
	if (GetKeyboardTrigger(DIK_B) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
	{
		switch (g_EscapeTutorialGuyde)
		{
		case TUTORIAL_GUYDE_HEALTH:
			g_EscapeTutorialGuyde = TUTORIAL_GUYDE_KEY;

			//�����߂��鉹
			PlaySound(SOUND_LABEL_PAPER);
			break;

		case TUTORIAL_GUYDE_KEY:
			g_EscapeTutorialGuyde = TUTORIAL_GUYDE_ESCAPE;

			//�����߂��鉹
			PlaySound(SOUND_LABEL_PAPER);
			break;

		case TUTORIAL_GUYDE_ESCAPE:
			
			break;
		}
	}

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadTrigger(BUTTON_START, 0) == true)
		{//ENTER�L�[���������Ƃ����U���g�Ƀt�F�[�h
			SetFade(MODE_GAME);
		}
	}
	//UpdateSpotLight();

	switch (g_EscapeTutorialState)
	{
	case TUTORIAL_STATE_GUYDE:	//�X�^���o�C���

			//�`�F�b�N�{�b�N�X��l�����I�t�ɂ���
			for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
			{
				SetCheckUI(nCntTutorial, false);
			}

			if (g_EscapeTutorialGuyde == TUTORIAL_GUYDE_MAX)
			{
				if (GetKeyboardTrigger(DIK_N) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
				{
					g_EscapeTutorialState = TUTORIAL_STATE_STANDBY;
				}
			}

		break;

	case TUTORIAL_STATE_STANDBY:	//�X�^���o�C���
		SetPaperBG00(true);
		SetTutorialUI(true,0);
		for (int nCntTutorial = 1; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber + 1; nCntTutorial++)
		{
			SetTutorialUI(false, nCntTutorial);
			MovePosCheckUI(nPlayer, true);
		}
		for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
		{
			SetPaperBG01(false, nCntTutorial);
		}

		g_EscapeCounter = 0;
		break;
	case TUTORIAL_STATE_WAIT:	//�ҋ@���
		SetPaperBG00(true);
		SetTutorialUI(true,0);
		g_EscapeCounter++;
		if (g_EscapeCounter > 100)
		{
			//�`�F�b�N�{�b�N�X��l�����I�t�ɂ���
			for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
			{
				SetCheckUI(nCntTutorial, false);
			}
			g_EscapeTutorialState = TUTORIAL_STATE_PLAY;
		}
		break;
	case TUTORIAL_STATE_PLAY:	//�v���C���
		SetPaperBG00(false);
		SetTutorialUI(false,0);

		for (int nCntTutorial = 1; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber + 1; nCntTutorial++)
		{
			SetTutorialUI(true, nCntTutorial);
			MovePosCheckUI(nPlayer, false);
		}
		for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
		{
			SetPaperBG01(true, nCntTutorial);
		}
		break;
	}

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	//���b�V���̕ǂ̍X�V����
	UpdateMeshWall();

	//���̍X�V����
	UpdateMeshField();

	//�I�u�W�F�N�g�̍X�V����
	UpdateObject00();
	UpdateObjectBG();

	//�`���[�g���A�����s��ʂ̎��݈̂ړ��\
	if (g_EscapeTutorialState == TUTORIAL_STATE_PLAY)
	{
		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�X�^�~�i�̍X�V����
		UpdateStamina();

		//���C�t�̍X�V����
		UpdateLife();

		////�X�R�A�̍X�V����
		//UpdateScore();

		////�X�R�A�A�C�e���̍X�V����
		//UpdateItem();

		//���̍X�V����
		UpdateKey();

		//��UI�̍X�V����
		UpdateKeyUI();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�p�[�e�B�N���̍X�V
		UpdateParticle();

		//�o���̍X�V����
		UpdateExit();
	}
	UpdateNeedKeyPolygon();

	UpdateActionHelpUI();

	UpdateChasePolygon();

	UpdateTime();

	UpdatePaperBG00();
	UpdatePaperBG01();

	UpdateTutorialUI();

	UpdateCheckboxUI();

	UpdatePolygonBG();

	switch (g_EscapeTutorial)
	{
	case MODE_MOVE:
		break;

	case MODE_DASH:

		break;

	case MODE_STELTH:

		break;

	case MODE_VIBE:

		break;

	case MODE_GET_KEY:

		break;

	case MODE_ESCAPE:

		break;

	case MODE_GOEXIT:

		break;

	case MODE_END:

		if (pFade == FADE_NONE)
		{
			SetFade(MODE_GAME);			//���[�h�̐ݒ�(�Q�[����ʂɈڍs)
		}

		break;

	}
}

//====================================================================
//�`���[�g���A����ʂ̕`�揈��
//====================================================================
void DrawEscapeTutorial()
{
	D3DVIEWPORT9 viewportDef;

	//�f�o�C�X�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	Player *pPlayer = GetPlayer();

	//���݂̃r���[�|�[�g���擾
	pDevice->GetViewport(&viewportDef);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++, pPlayer++)
	{
		//�J�����̃Z�b�g����
		SetCamera(nCnt);

		//�v���C���[���ێ����郉�C�g�̕`�揈��
		DrawLight(nCnt);

		//���b�V���E�H�[���̕`�揈��
		DrawMeshWall();

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

		DrawNeedKeyPolygon(nCnt);

		//�w���vUI�̕`�揈��
		DrawActionHelpUI(nCnt, pPlayer->bGetKey);

		//�X�^�~�i�̕`�揈��
		DrawStamina();

		//���C�t�̕`�揈��
		DrawLife();

		DrawTime();

		////�X�R�A�̕`�揈��
		//DrawScore();

		////�X�R�A�A�C�e���̕`�揈��
		//DrawItem();

		//���̕`�揈��
		DrawKey();

		//�G�t�F�N�g�̕`�揈��
		DrawEffect();

		//�p�[�e�B�N���̕`��
		DrawParticle();

		DrawChasePolygon(nCnt);

		//��UI�̕`�揈��
		DrawKeyUI();

		DrawPolygonBG();

		//�t�H�O�̕`��
		DrawFog();
	}

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);

	DrawPaperBG00();
	DrawPaperBG01();

	DrawTutorialUI();

	if (g_EscapeTutorial != MODE_GOEXIT || g_EscapeTutorialState != TUTORIAL_STATE_PLAY)
	{
		//�`�F�b�N�{�b�N�X�̕`��
		DrawCheckboxUI();
	}
}

//====================================================================
//�`���[�g���A����ʂ̏�ԊǗ�
//====================================================================
TUTORIAL_STATE GetEscapeTutorial()
{
	return g_EscapeTutorialState;
}

//====================================================================
//�`���[�g���A����ʃK�C�h�̏�ԊǗ�
//====================================================================
TUTORIAL_GUYDE GetEscapeTutorialGuyde()
{
	return g_EscapeTutorialGuyde;
}


//====================================================================
//�`���[�g���A����ʂ̏�ԊǗ�
//====================================================================
void SetEscapeTutorial(TUTORIAL_STATE nSet)
{
	g_EscapeTutorialState = nSet;
}

//====================================================================
//�`���[�g���A�����ڂ̏�ԊǗ�
//====================================================================
void DoEscapeTutorial(TUTORIAL_MODE nMode)
{
	g_EscapeTutorial = nMode;
}

//=====================================
//�`���[�g���A�����ڂ̏���^���鏈��
//=====================================
TUTORIAL_MODE GetDoEscapeTutorial(void)
{
	return g_EscapeTutorial;
}

//==============================
//�ړ��������ǂ����̃`�F�b�N�p
//==============================
void MoveTCheck(int nCnt,bool check)
{
	//�v���C���[�����������Ƃ�
	bpEscapeMove[nCnt] = check;
}

//==================================
//�J���������������ǂ����̃`�F�b�N
//==================================
void CamMoveTCheck(int nCnt,bool camcheck)
{
	//�J���������������Ƃ�
	bpEscapeCamMove[nCnt] = camcheck;

	//�v���C���[�ƃJ�������������Ƃ���
	if (bpEscapeMove[nCnt] == true && bpEscapeCamMove[nCnt] == true)
	{
		//�`�F�b�N�����鏈��
		SetCheckUI(nCnt, true);
	}
}

