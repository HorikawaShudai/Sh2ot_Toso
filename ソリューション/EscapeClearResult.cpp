#include "EscapeClearResult.h"
#include "camera.h"
#include "light.h"
#include "stage.h"

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

	//�X�e�[�W�̓ǂݍ���
	SetStage(2);
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
}

//====================================================================
//�������[�h�̃N���A���U���g��ʂ̍X�V����
//====================================================================
void UpdateEscapeClearResult()
{
	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();
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

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);
}
