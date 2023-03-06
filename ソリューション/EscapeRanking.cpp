//========================================================================================
//
// �����L���O����[EscapeRanking.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "EscapeRanking.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "numberUI.h"
#include "RankingUI.h"
#include "RankingNumber.h"
#include "object00.h"
#include "objectBG.h"
#include "objectLight.h"
#include "objectWall.h"
#include "objectPoly.h"
#include "time.h"
#include "meshfield.h"
#include "numberUI.h"

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

	//�I�u�W�F�N�g�̏���������
	InitObject00();
	InitObjectBG();
	InitObjectLight();
	InitObjectWall();
	InitObjectPoly();

	//�X�e�[�W�̓ǂݍ���
	SetStage(0);

	InitNumberUI();

	InitRankingUI();

	InitNumberUI();

	InitRanKingNumber();

	InitMeshField();
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

	//�I�u�W�F�N�g�̏I������
	UninitObject00();
	UninitObjectBG();
	UninitObjectLight();
	UninitObjectWall();
	UninitObjectPoly();

	UninitNumberUI();

	UninitRankingUI();

	UninitNumberUI();

	UninitRanKingNumber();

	UninitMeshField();
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

	//�I�u�W�F�N�g�̍X�V����
	UpdateObject00();
	UpdateObjectBG();
	UpdateObjectLight();
	UpdateObjectWall();
	UpdateObjectPoly();

	UpdateNumberUI();

	UpdateRankingUI();

	UpdateNumberUI();

	UpdateRanKingNumber();

	UpdateMeshField();
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

	DrawMeshField();

	//�I�u�W�F�N�g�̕`�揈��
	DrawObject00();
	DrawObjectBG();
	DrawObjectLight();
	DrawObjectWall();
	DrawObjectPoly();

	DrawNumberUI();

	DrawRankingUI();

	DrawNumberUI();

	DrawRanKingNumber();

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);
}
