#include "game.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"


bool g_bPause = false;
GAMESTATE gGameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//====================================================================
//�Q�[����ʂ̏���������
//====================================================================
void InitGame()
{
	g_bPause = false;

	DWORD time = timeGetTime();
	srand((unsigned int)time);
	SetGameState(GAMESTATE_READY, 60);

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	InitMeshWall();

	InitObject00();
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
}

//====================================================================
//�Q�[����ʂ̍X�V����
//====================================================================
void UpdateGame()
{
	if (g_bPause == false)
	{//�|�[�Y��Ԃ���Ȃ��Ƃ�
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

	UpdateObject00();
}

//====================================================================
//�Q�[����ʂ̕`�揈��
//====================================================================
void DrawGame()
{
	//�J�����̕`�揈��
	SetCamera();

	DrawMeshWall();

	DrawObject00();
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