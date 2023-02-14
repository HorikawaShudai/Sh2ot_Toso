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

//�O���[�o���ϐ��錾

//====================================================================
//�Q�[����ʂ̏���������
//====================================================================
void InitEscapeTutorial()
{
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

	SetEnemy(D3DXVECTOR3(-2300.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//�X�R�A�̏�����
	InitScore();

	//���̏���������
	InitKey();

	SetKey(D3DXVECTOR3(-1000.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), KEY_TYPE_ITEM);

	//��UI�̏���������
	InitKeyUI();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�o���̏���������
	InitExit();

	SetExit(D3DXVECTOR3(-1000.0f,0.0f,0.8f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXIT_TYPE_BIGFRAME, 0);
	SetExit(D3DXVECTOR3(-1070.0f, 0.0f, 0.8f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), EXIT_TYPE_BIGDOOR_R, 0);
	SetExit(D3DXVECTOR3(-935.0f, 0.0f, 0.8f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), EXIT_TYPE_BIGDOOR_L, 0);

	//�X�R�A�A�C�e���̏�����
	InitItem();

	InitPolygonBG();

	InitTime();

	InitpaperBG00();
	InitpaperBG01();

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
//�Q�[����ʂ̏I������
//====================================================================
void UninitEscapeTutorial()
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

	UninitTime();

	UninitpaperBG00();
	UninitpaperBG01();

	UninitTutorialUI();

	UninitCheckboxUI();

	UninitPolygonBG();

	//�t�H�O�̏I������
	UninitFog();
}

//====================================================================
//�Q�[����ʂ̍X�V����
//====================================================================
void UpdateEscapeTutorial()
{

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_RETURN))
	{//ENTER�L�[���������Ƃ����U���g�Ƀt�F�[�h
		SetFade(MODE_GAME);
	}
#endif

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	//UpdateSpotLight();

	//���b�V���̕ǂ̍X�V����
	UpdateMeshWall();

	//���̍X�V����
	UpdateMeshField();

	//�I�u�W�F�N�g�̍X�V����
	UpdateObject00();
	UpdateObjectBG();

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

	UpdateTime();

	UpdatepaperBG00();
	UpdatepaperBG01();

	UpdateTutorialUI();

	UpdateCheckboxUI();

	UpdatePolygonBG();
}

//====================================================================
//�Q�[����ʂ̕`�揈��
//====================================================================
void DrawEscapeTutorial()
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

		DrawpaperBG00();
		DrawpaperBG01();

		/*DrawTutorialUI();*/

		DrawCheckboxUI();

		//�G�t�F�N�g�̕`�揈��
		DrawEffect();

		DrawPolygonBG();

		//�t�H�O�̕`��
		DrawFog();
	}

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);
}