#include "VillainRanking.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "numberUI.h"
#include "RankingUI.h"
#include "RankingNumber.h"

//�O���[�o���ϐ��錾

//====================================================================
//�������[�h�̃����L���O��ʂ̏���������
//====================================================================
void InitVillainRanking()
{
	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//�X�e�[�W�̓ǂݍ���
	SetStage(4);

	InitNumberUI();

	InitRankingUI();

	InitRanKingNumber();
}

//====================================================================
//�������[�h�̃����L���O��ʂ̏I������
//====================================================================
void UninitVillainRanking()
{
	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	UninitNumberUI();

	UninitRankingUI();

	UninitRanKingNumber();
}

//====================================================================
//�������[�h�̃����L���O��ʂ̍X�V����
//====================================================================
void UpdateVillainRanking()
{
	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	UpdateNumberUI();

	UpdateRankingUI();

	UpdateRanKingNumber();
}

//====================================================================
//�������[�h�̃����L���O��ʂ̕`�揈��
//====================================================================
void DrawVillainRanking()
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

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);
}
