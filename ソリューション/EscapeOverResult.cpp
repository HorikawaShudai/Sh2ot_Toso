#include "EscapeOverResult.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "Object00.h"
#include "ObjectBG.h"
#include "ResultUI.h"
#include "fade.h"
#include "input.h"

//�O���[�o���ϐ��錾

//====================================================================
//�������[�h�̃Q�[���I�[�o�[���U���g��ʂ̏���������
//====================================================================
void InitEscapeOverResult()
{
	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	InitObjectBG();

	//�X�e�[�W�̓ǂݍ���
	SetStage(4);

	InitResultUI();
}

//====================================================================
//�������[�h�̃Q�[���I�[�o�[���U���g��ʂ̏I������
//====================================================================
void UninitEscapeOverResult()
{
	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	UninitObjectBG();

	UninitResultUI();
}

//====================================================================
//�������[�h�̃Q�[���I�[�o�[���U���g��ʂ̍X�V����
//====================================================================
void UpdateEscapeOverResult()
{
	FADE Fade = GetFade();

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	UpdateObjectBG();

	UpdateResultUI();

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(BUTTON_A, 0))
		{
			SetFade(MODE_RANKING);
		}
	}
}

//====================================================================
//�������[�h�̃Q�[���I�[�o�[���U���g��ʂ̕`�揈��
//====================================================================
void DrawEscapeOverResult()
{
	D3DVIEWPORT9 viewportDef;

	//�f�o�C�X�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���݂̃r���[�|�[�g���擾
	pDevice->GetViewport(&viewportDef);

	//�J�����̃Z�b�g����
	SetCamera(4);

	DrawObjectBG();

	DrawResultUI();

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);
}
