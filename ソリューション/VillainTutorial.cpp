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
#include "VillainTutorial.h"
#include "ActionHelpUI.h"
#include "player.h"
#include "sound.h"

//�O���[�o���ϐ��錾
TUTORIAL_STATE g_VillainTutorialState;
int g_VillainCounter;
TUTORIAL_MODE g_VillainTutorial;
bool bpVillainMove[NUM_PLAYER];
bool bpVillainCamMove[NUM_PLAYER];

//====================================================================
//�`���[�g���A����ʂ̏���������
//====================================================================
void InitVillainTutorial()
{
	g_VillainTutorialState = TUTORIAL_STATE_STANDBY;
	g_VillainTutorial = MODE_MOVE;
	g_VillainCounter = 0;

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		bpVillainMove[nCntPlayer] = true;
		bpVillainCamMove[nCntPlayer] = true;
	}

	for (int nCntPlayer = 0; nCntPlayer < GetPlayNumberSelect().CurrentSelectNumber; nCntPlayer++)
	{
		bpVillainMove[nCntPlayer] = false;
		bpVillainCamMove[nCntPlayer] = false;
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

	SetExit(D3DXVECTOR3(-1000.0f, 0.0f, 0.8f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 0);
	SetExit(D3DXVECTOR3(-1070.0f, 0.0f, 0.8f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), 0, 0);
	SetExit(D3DXVECTOR3(-935.0f, 0.0f, 0.8f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), 0, 0);

	//�X�R�A�A�C�e���̏�����
	InitItem();

	InitActionHelpUI();

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

	//�X�e�[�W�̓ǂݍ���
	SetStage(4);
}

//====================================================================
//�`���[�g���A����ʂ̏I������
//====================================================================
void UninitVillainTutorial()
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

	UninitActionHelpUI();

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
void UpdateVillainTutorial()
{
	FADE pFade = GetFade();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	int nPlayer = GetCurrentCamera();

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_RETURN))
	{//ENTER�L�[���������Ƃ����U���g�Ƀt�F�[�h
		SetFade(MODE_GAME);
	}

	if (GetKeyboardTrigger(DIK_V))
	{
		switch (g_VillainTutorialState)
		{
		case TUTORIAL_STATE_STANDBY:
			g_VillainTutorialState = TUTORIAL_STATE_WAIT;
			break;
		case TUTORIAL_STATE_WAIT:
			g_VillainTutorialState = TUTORIAL_STATE_PLAY;
			break;
		case TUTORIAL_STATE_PLAY:
			g_VillainTutorialState = TUTORIAL_STATE_STANDBY;
			break;
		}
	}

#endif

	//UpdateSpotLight();

	switch (g_VillainTutorialState)
	{
	case TUTORIAL_STATE_STANDBY:	//�X�^���o�C���
		SetPaperBG00(true);
		SetTutorialUI(true, 0);
		for (int nCntTutorial = 1; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber + 1; nCntTutorial++)
		{
			SetTutorialUI(false, nCntTutorial);
			MovePosCheckUI(nPlayer, true);
		}
		for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
		{
			SetPaperBG01(false, nCntTutorial);
		}

		g_VillainCounter = 0;
		break;
	case TUTORIAL_STATE_WAIT:	//�ҋ@���
		SetPaperBG00(true);
		SetTutorialUI(true, 0);
		g_VillainCounter++;
		if (g_VillainCounter > 100)
		{
			//�`�F�b�N�{�b�N�X��l�����I�t�ɂ���
			for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
			{
				SetCheckUI(nCntTutorial, false);
			}
			g_VillainTutorialState = TUTORIAL_STATE_PLAY;
		}
		break;
	case TUTORIAL_STATE_PLAY:	//�v���C���
		SetPaperBG00(false);
		SetTutorialUI(false, 0);

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
	if (g_VillainTutorialState == TUTORIAL_STATE_PLAY)
	{
		//�v���C���[�̍X�V����
		UpdatePlayer();

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
	}
	UpdateActionHelpUI();

	UpdateTime();

	UpdatePaperBG00();
	UpdatePaperBG01();

	UpdateTutorialUI();

	UpdateCheckboxUI();

	UpdatePolygonBG();

	switch (g_VillainTutorial)
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
void DrawVillainTutorial()
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

	DrawPaperBG00();
	DrawPaperBG01();

	DrawTutorialUI();

	//�`�F�b�N�{�b�N�X�̕`��
	DrawCheckboxUI();
}

//====================================================================
//�`���[�g���A����ʂ̏�ԊǗ�
//====================================================================
TUTORIAL_STATE GetVillainTutorial()
{
	return g_VillainTutorialState;
}

//====================================================================
//�`���[�g���A����ʂ̏�ԊǗ�
//====================================================================
void SetVillainTutorial(TUTORIAL_STATE nSet)
{
	g_VillainTutorialState = nSet;
}

//====================================================================
//�`���[�g���A�����ڂ̏�ԊǗ�
//====================================================================
void DoVillainTutorial(TUTORIAL_MODE nMode)
{
	g_VillainTutorial = nMode;
}

//=====================================
//�`���[�g���A�����ڂ̏���^���鏈��
//=====================================
TUTORIAL_MODE GetDoVillainTutorial(void)
{
	return g_VillainTutorial;
}

//==============================
//�ړ��������ǂ����̃`�F�b�N�p
//==============================
void MoveVCheck(int nCnt, bool check)
{
	//�v���C���[�����������Ƃ�
	bpVillainMove[nCnt] = check;
}

//==================================
//�J���������������ǂ����̃`�F�b�N
//==================================
void CamMoveVCheck(int nCnt, bool camcheck)
{
	//�J���������������Ƃ�
	bpVillainCamMove[nCnt] = camcheck;

	//�v���C���[�ƃJ�������������Ƃ���
	if (bpVillainMove[nCnt] == true && bpVillainCamMove[nCnt] == true)
	{
		//�`�F�b�N�����鏈��
		SetCheckUI(nCnt, true);
	}
}

