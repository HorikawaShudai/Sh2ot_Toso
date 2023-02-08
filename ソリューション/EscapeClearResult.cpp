#include "EscapeClearResult.h"
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
//�������[�h�̃N���A���U���g��ʂ̏���������
//====================================================================
void InitEscapeClearResult()
{
	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	InitObjectBG();

	//�X�e�[�W�̓ǂݍ���
	SetStage(3);

	InitResultUI();
}

//====================================================================
//�������[�h�̃N���A���U���g��ʂ̏I������
//====================================================================
void UninitEscapeClearResult()
{
	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	UninitObjectBG();

	UninitResultUI();
}

//====================================================================
//�������[�h�̃N���A���U���g��ʂ̍X�V����
//====================================================================
void UpdateEscapeClearResult()
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

	DrawObjectBG();

	DrawResultUI();

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);
}
