//========================================================================================
//
// ���U���g�̃Q�[���N���A����[EscapeClearResult.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "EscapeClearResult.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "Object00.h"
#include "ObjectBG.h"
#include "ResultUI.h"
#include "fade.h"
#include "input.h"
#include "meshdome.h"
#include "meshcylinder.h"
#include "numberUI.h"
#include "playerBG.h"
#include "sound.h"

//�O���[�o���ϐ��錾
int g_nFadeCount;		//�����J�ڗp�ϐ�

//====================================================================
//�������[�h�̃N���A���U���g��ʂ̏���������
//====================================================================
void InitEscapeClearResult()
{
	g_nFadeCount = 0;

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	InitMeshDome();

	InitMeshCylinder();

	InitObject00();
	InitObjectBG();
	InitResultPlayer();

	//�X�e�[�W�̓ǂݍ���
	SetStage(3);

	InitNumberUI();

	InitResultUI();

	PlaySound(SOUND_LABEL_BGM_CLEAR);
}

//====================================================================
//�������[�h�̃N���A���U���g��ʂ̏I������
//====================================================================
void UninitEscapeClearResult()
{
	StopSound();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	UninitMeshDome();

	UninitMeshCylinder();

	UninitObject00();
	UninitObjectBG();
	UninitResultPlayer();

	UninitNumberUI();

	UninitResultUI();

}

//====================================================================
//�������[�h�̃N���A���U���g��ʂ̍X�V����
//====================================================================
void UpdateEscapeClearResult()
{
	FADE Fade = GetFade();
	bool ClearUi = GetbResultUi();

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	UpdateMeshDome();

	UpdateMeshCylinder();

	UpdateObject00();
	UpdateObjectBG();
	UpdateResultPlayer();

	UpdateNumberUI();

	UpdateResultUI();



	if (ClearUi == false)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_A, 0))
		{
			//���艹
			PlaySound(SOUND_LABEL_ENTER);

			SetbResultUi(true);
		}
	}
	if (Fade == FADE_NONE && ClearUi == true)
	{
		g_nFadeCount++;
		if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_A, 0) || g_nFadeCount == 1200)
		{
			//���艹
			PlaySound(SOUND_LABEL_ENTER);

			SetFade(MODE_RANKING);
		}
	}
}

//====================================================================
//�������[�h�̃N���A���U���g��ʂ̕`�揈��
//====================================================================
void DrawEscapeClearResult()
{
	D3DVIEWPORT9 viewportDef;

	//�f�o�C�X�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���݂̃r���[�|�[�g���擾
	pDevice->GetViewport(&viewportDef);

	//�J�����̃Z�b�g����
	SetCamera(4);

	DrawMeshDome();

	DrawMeshCylinder();

	DrawObject00();
	DrawObjectBG();
	DrawResultPlayer();

	DrawNumberUI();

	DrawResultUI();

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);
}
