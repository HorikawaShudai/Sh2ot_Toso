//========================================================================================
//
// ���U���g�̃Q�[���I�[�o�[����[EscapeOverResult.cpp]
// Author: ��{�@�ėB
//
//========================================================================================

#include "EscapeOverResult.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "Object00.h"
#include "ObjectBG.h"
#include "ObjectLight.h"
#include "ResultUI.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//�}�N����`
#define INIT_SCREENTEX_X0  (0.0f)	   //�e�N�X�`��X���̍ŏ��̈ʒu
#define INIT_SCREENTEX_Y0  (0.0f)      //�e�N�X�`��Y���̍ŏ��̈ʒu

#define INIT_SCREENTEX_X1  (1280.0f)  //�e�N�X�`��X���̉E���̈ʒu
#define INIT_SCREENTEX_Y1  (720.0f)   //�e�N�X�`��Y���̍ŏ��̈ʒu

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureOver = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOver = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int ntransition;									//�J�ڂ���܂ł̎���								

//====================================================================
//�������[�h�̃Q�[���I�[�o�[���U���g��ʂ̏���������
//====================================================================
void InitEscapeOverResult()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�J�ڂ��鎞�Ԃ܂ł̏�����
	ntransition = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RESULT\\GAME_OVER.png",
		&g_pTextureOver);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOver,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffOver->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(INIT_SCREENTEX_X0,INIT_SCREENTEX_Y0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(INIT_SCREENTEX_X1,INIT_SCREENTEX_Y0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(INIT_SCREENTEX_X0,INIT_SCREENTEX_Y1, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(INIT_SCREENTEX_X1,INIT_SCREENTEX_Y1, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	InitObject00();
	InitObjectBG();
	InitObjectLight();

	//�X�e�[�W�̓ǂݍ���
	SetStage(5);

	//�Q�[���I�[�o�[BGM(�m�C�Y)
	PlaySound(SOUND_LABEL_BGM_GAMEOVER);
	//InitResultUI();
}

//====================================================================
//�������[�h�̃Q�[���I�[�o�[���U���g��ʂ̏I������
//====================================================================
void UninitEscapeOverResult()
{
	//�T�E���h���~�߂�
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureOver != NULL)
	{
		g_pTextureOver->Release();
		g_pTextureOver = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffOver != NULL)
	{
		g_pVtxBuffOver->Release();
		g_pVtxBuffOver = NULL;
	}

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	UninitObject00();
	UninitObjectBG();
	UninitObjectLight();

	//UninitResultUI();
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

	UpdateObject00();
	UpdateObjectBG();
	UpdateObjectLight();

	//UpdateResultUI();

	//�^�C�g����ʂ֑J��
	if (Fade == FADE_NONE)
	{
		if (GetKeyboardPress(DIK_RETURN) || GetGamepadPress(BUTTON_A, 0) || ntransition >= 420)
		{
			SetFade(MODE_TITLE);
		}
		//�J�ڂ��鎞�Ԃ܂ł����Z
		ntransition++;
	}
}

//====================================================================
//�������[�h�̃Q�[���I�[�o�[���U���g��ʂ̕`�揈��
//====================================================================
void DrawEscapeOverResult()
{
	//�f�o�C�X�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVIEWPORT9 viewportDef;

	//���݂̃r���[�|�[�g���擾
	pDevice->GetViewport(&viewportDef);

	//�J�����̃Z�b�g����
	SetCamera(4);

	DrawObject00();
	DrawObjectBG();
	DrawObjectLight();

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);

	pDevice->SetStreamSource(0, g_pVtxBuffOver, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureOver);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
