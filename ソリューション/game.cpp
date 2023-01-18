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

	InitMeshWall();

	InitObject00();

	InitPlayer();

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

	UninitMeshWall();

	UninitObject00();

	UninitPlayer();
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
			if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(BUTTON_A, 0) || GetGamepadPress(BUTTON_A, 0))
			{
				SetFade(MODE_RESULT);
			}
		}
	}

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	UpdateMeshWall();

	if (g_bEdit == true)
	{
		UpdateEdit();

		UpdateEditObject00();

		PrintDebugProc("�J�����̎��_�ړ��yW�z�yA�z�yS�z�yD�z\n");
		PrintDebugProc("�J�����̒����_�ړ� �yI�z�yJ�z�yK�z�yL�z\n");
		PrintDebugProc("�J�����̏㉺�ړ� �y��SHIFT�z�y��CTRL�z\n");
		PrintDebugProc("�v���C���[�̈ړ��ړ� �yT�z�yF�z�yG�z�yH�z\n");
	}
	else
	{
		UpdateObject00();

		UpdatePlayer();
	}
}

//====================================================================
//�Q�[����ʂ̕`�揈��
//====================================================================
void DrawGame()
{
	//�J�����̕`�揈��
	SetCamera();

	DrawMeshWall();

	if (g_bEdit == true)
	{
		DrawEditObject00();
	}
	DrawObject00();
	DrawPlayer();
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