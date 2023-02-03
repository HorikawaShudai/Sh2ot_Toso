#include "EscapeRanking.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "numberUI.h"
#include "RankingUI.h"
#include "RankingNumber.h"
#include "time.h"

//�O���[�o���ϐ��錾

//====================================================================
//�������[�h�̃����L���O��ʂ̏���������
//====================================================================
void InitEscapeRanking()
{
	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//�X�e�[�W�̓ǂݍ���
	SetStage(3);

	InitNumberUI();

	InitRankingUI();

	InitRanKingNumber();

	InitTime();
}

//====================================================================
//�������[�h�̃����L���O��ʂ̏I������
//====================================================================
void UninitEscapeRanking()
{
	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	UninitNumberUI();

	UninitRankingUI();

	UninitRanKingNumber();

	UninitTime();
}

//====================================================================
//�������[�h�̃����L���O��ʂ̍X�V����
//====================================================================
void UpdateEscapeRanking()
{
	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	UpdateNumberUI();

	UpdateRankingUI();

	UpdateRanKingNumber();

	UpdateTime();
}

//====================================================================
//�������[�h�̃����L���O��ʂ̕`�揈��
//====================================================================
void DrawEscapeRanking()
{
	D3DVIEWPORT9 viewportDef;

	//�f�o�C�X�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���݂̃r���[�|�[�g���擾
	pDevice->GetViewport(&viewportDef);

	//�J�����̃Z�b�g����
	SetCamera(4);

	DrawNumberUI();

	DrawRankingUI();

	DrawRanKingNumber();

	DrawTime();

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);
}
