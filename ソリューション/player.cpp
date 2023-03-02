//========================================================================================
//
// �v���C���[�̏���[player.cpp]
// Author: ���}���@�V
// Author: ��{�@�ėB
// Author: �O�엳�V��
//
//========================================================================================
#include "main.h"
#include "game.h"
#include "result.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "object00.h"
#include "input.h"
#include "debugproc.h"
#include "fade.h"
#include "life.h"
#include "PlayNumberSelect.h"
#include "PlayModeSelect.h"
#include "score_item.h"
#include "stamina.h"
#include "key.h"
#include "keyUI.h"
#include "exit.h"
#include "light.h"
#include "CheckboxUI.h"
#include "PolygonBG.h"
#include "EscapeTutorial.h"
#include "sound.h"

//�}�N����`
#define PLAYER_STEALTHSPEED		(0.3f)			//�v���C���[�̃X�e���X�X�s�[�h
#define PLAYER_SPEED			(1.5f)			//�v���C���[�̃X�s�[�h
#define PLAYER_DASHSPEED		(2.0f)			//�v���C���[�̃_�b�V���X�s�[�h
#define PLAYER_ROT_SPEED		(0.2f)			//�v���C���[�̉�]�X�s�[�h
#define PLAYER_JUMP				(12.0f)			//�v���C���[�̃W�����v��
#define PLAYER_LIFE				(3)				//�v���C���[�̏������C�t
#define PLAYER_COLLISIONSIZE	(15.0f)			//�v���C���[�̓����蔻��̑傫��
#define PLAYER_LIGHT			(350.0f)		//�v���C���[�̓����蔻��̑傫��
#define ENEMY_SE_SPEED			(60)			//�G�̑�����炷�Ԋu
#define PLAYER_SE_WALK			(40)			//�v���C���[�̑�����炷�Ԋu(����)
#define PLAYER_SE_DASH			(30)			//�v���C���[�̑�����炷�Ԋu(�_�b�V��)
#define PLAYER_DISTANCE_SE		(800.0f)		//�G�̉�����������悤�ɂȂ鋗��
#define PLAYER_DISTANCE_VIB		(600.0f)		//�o�C�u���[�V�������I���ɂȂ鋗��
#define PLAYER_DISTANCE_APPEAR	(500.0f)		//�G��������悤�ɂȂ鋗��
#define PLAYER_WAITCOUNTER		(120)			//�v���C���[�̑ҋ@��Ԃ̒���
#define PLAYER_DAMAGECOUNTER	(120)			//�v���C���[�̃_���[�W��Ԃ̒���
#define PLAYER_DEATHCOUNTER		(1000)			//�v���C���[�̎��S��Ԃ̒���
#define PLAYER_HITCOUNTER		(60)			//�v���C���[�̃q�b�g��Ԃ̒���

//�v���g�^�C�v
void UpdatePlayer0(void);
void UpdatePlayer1(void);

void ResPlayerMove(int nCnt);					//�v���C���[���ꂼ��ɑΉ�
void ResPlayerrot(int nCnt);					//�v���C���[���ꂼ��ɑΉ�

												//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer[100] = {};	//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshPlayer[32] = {};				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer[32] = {};			//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0;						//�}�e���A���̐�
Player g_aPlayer[NUM_PLAYER];					//�v���C���[�̏��
int g_nIndexPlayerShadow = -1;					//�e�̃C���f�b�N�X(�ԍ�)
bool g_bPlayerOps;
bool g_GameEnd;
bool bMove;										//�v���C���[���ړ��������ǂ���
int g_Rand_PolygonColor_R;
int g_Rand_PolygonColor_G;
int g_Rand_PolygonColor_B;
int g_Rand_PolygonColor_A;
int g_Rand_PolygonType;
int g_ExitCount;
int nEnemySECount;

//====================================================================
//�v���C���[�̏���������
//====================================================================
void InitPlayer(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].bExit = true;
	}

	for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].pos = D3DXVECTOR3(-1050.0f + nCntPlayer * 30.0f, 0.0f, -621.11f);
		g_aPlayer[nCntPlayer].posOld = D3DXVECTOR3(0.0f, 300.0f, -400.0f);
		g_aPlayer[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].State = PLAYER_NORMAL;
		g_aPlayer[nCntPlayer].MoveState = PLAYER_MOVESTATE_STEALTH;
		g_aPlayer[nCntPlayer].nLife = PLAYER_LIFE;
		g_aPlayer[nCntPlayer].bUse = true;
		g_aPlayer[nCntPlayer].bGetKey = false;
		g_aPlayer[nCntPlayer].VibrtionTrueCount = 0;
		g_aPlayer[nCntPlayer].VibrtionFalseCount = 0;
		g_aPlayer[nCntPlayer].LightIdx00 = SetIndexLight();		//���C�g�̃Z�b�g����
		g_aPlayer[nCntPlayer].nWaitCounter = PLAYER_WAITCOUNTER;
		g_aPlayer[nCntPlayer].nDamageCounter = PLAYER_DAMAGECOUNTER;
		g_aPlayer[nCntPlayer].nDeathCounter = PLAYER_DEATHCOUNTER;
		g_aPlayer[nCntPlayer].bChase = false;

		g_aPlayer[nCntPlayer].bCheck = false;  //�`�F�b�N�{�b�N�X�����Ă��Ȃ���Ԃ�
		g_aPlayer[nCntPlayer].bExit = false;
		g_aPlayer[nCntPlayer].bVibrtion = false;
		g_aPlayer[nCntPlayer].bAppear = false;
#if _DEBUG
		g_aPlayer[nCntPlayer].bAppear = true;
#endif

		g_bPlayerOps = false;
		g_GameEnd = false;
		bMove = false;
		g_aPlayer[nCntPlayer].nStelthCnt = 0;
		g_aPlayer[nCntPlayer].nVibCnt = 0;
		g_aPlayer[nCntPlayer].KeyHelpUI = false;
		g_aPlayer[nCntPlayer].ExitHelpUI = false;

		g_aPlayer[nCntPlayer].nPlayerSECount = 0;

		g_Rand_PolygonColor_R = 0;
		g_Rand_PolygonColor_G = 0;
		g_Rand_PolygonColor_B = 0;
		g_Rand_PolygonColor_A = 0;
		g_Rand_PolygonType = 0;
		g_ExitCount = 0;

		nEnemySECount = 0;

		g_aPlayer[nCntPlayer].nNumModel = 1;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\player.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatPlayer[nCntPlayer],
			NULL,
			&g_dwNumMatPlayer,
			&g_pMeshPlayer[nCntPlayer]);

		for (int nCntModel = 0; nCntModel < g_aPlayer[nCntPlayer].nNumModel; nCntModel++)
		{
			D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

								//�}�e���A�����ɑ΂���|�C���^������
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayer[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_pTexturePlayer[nCntMat]);
				}
			}
		}
	}
}

//====================================================================
//�v���C���[�̏I������
//====================================================================
void UninitPlayer(void)
{
	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	for (int nCntModel = 0; nCntModel < PlayNumber.CurrentSelectNumber; nCntModel++)
	{
		//���b�V���̔j��
		if (g_pMeshPlayer[nCntModel] != NULL)
		{
			g_pMeshPlayer[nCntModel]->Release();
			g_pMeshPlayer[nCntModel] = NULL;
		}

		//�}�e���A���̔j��
		if (g_pBuffMatPlayer[nCntModel] != NULL)
		{
			g_pBuffMatPlayer[nCntModel]->Release();
			g_pBuffMatPlayer[nCntModel] = NULL;
		}

		//�o�C�u���[�V�������I�t�ɂ���
		GetGamepad_Vibrtion_false(0);
	}
}

//====================================================================
//�v���C���[�̍X�V����
//====================================================================
void UpdatePlayer(void)
{
	//#ifdef _DEBUG
	////��
	//UpdatePlayer0();
	//#endif

	//����
	UpdatePlayer1();
}

//====================================================================
//�v���C���[�̍X�V����(��̃R���g���[���Ή�)
//====================================================================
void UpdatePlayer0(void)
{
	//�`���[�g���A���̍��ڏ���^���鏈��
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();

	//�|�C���^���̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	int CurrentCamera = GetCurrentCamera();

	//�J�����ԍ����v���C���[�ɑ��
	int nSelectPlayer = GetCurrentCamera();

	//�v���C���[�̏�ԊǗ�
	PlayerState(nSelectPlayer);

	if (g_aPlayer[nSelectPlayer].bUse == true && g_aPlayer[nSelectPlayer].State == PLAYER_NORMAL)
	{
#ifdef _DEBUG
		//�o�C�u���[�V����
		if (GetKeyboardTrigger(DIK_F6) == true)
		{
			PlayerSetVibrtion(nSelectPlayer, 60, 0, 60000, 0);
		}
		if (GetKeyboardTrigger(DIK_F7) == true)
		{
			GetGamepad_Vibrtion_false(nSelectPlayer);
		}
#endif

		//�o�C�u���[�V�����̍X�V����
		PlayerVibrtionUpdate(nSelectPlayer);

		g_aPlayer[nSelectPlayer].posOld = g_aPlayer[nSelectPlayer].pos;

		//�����W��
		g_aPlayer[nSelectPlayer].move.x = g_aPlayer[nSelectPlayer].move.x * 0.5f;
		g_aPlayer[nSelectPlayer].move.z = g_aPlayer[nSelectPlayer].move.z * 0.5f;

		//�l�̐؂�̂�
		if (g_aPlayer[nSelectPlayer].move.x <= 0.005f && g_aPlayer[nSelectPlayer].move.x >= -0.005f)
		{
			g_aPlayer[nSelectPlayer].move.x = 0.0f;
		}
		if (g_aPlayer[nSelectPlayer].move.z <= 0.005f && g_aPlayer[nSelectPlayer].move.z >= -0.005f)
		{
			g_aPlayer[nSelectPlayer].move.z = 0.0f;
		}

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_F5) == true)
		{//�L�[�������ꂽ�ꍇ
			g_bPlayerOps = g_bPlayerOps ? false : true;			//�ώ@�p���[�h�ɕύX
		}
#endif

		if (g_bPlayerOps == false)
		{
			//�v���C���[�̈ړ����͏���----------
			PlayerMoveInput(nSelectPlayer);

			//�ړ����Ƀv���C���[�̌�����␳����----------
			PlayerRotUpdate(nSelectPlayer);
		}

		//�ʒu�X�V(���͂ɂ�铮��)
		g_aPlayer[nSelectPlayer].pos += g_aPlayer[nSelectPlayer].move;

		//�I�u�W�F�N�g�Ƃ̓����蔻��
		CollisionObject00(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 50.0f, 10.0f), 10.0f);
		CollisionObjectWall(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 50.0f, 10.0f), 10.0f);
		//	CollisionObjectPoly(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 50.0f, 10.0f), 10.0f);
		//�O�ς̓����蔻��
		//CollisionOuterProductObject00(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move);

		if (GetPlayModeSelect().CurrentModeNumber == 1)
		{
			//�A�C�e���Ƃ̓����蔻��
			CollisionItem(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-20.0f, -20.0f, -20.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f), 20.0f, nSelectPlayer);
		}

		//�o���Ƃ̓����蔻��
		CollisionExi(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);

		//�v���C���[�ƓG�Ƃ̋���
		PlayerDistance(nSelectPlayer);

		//�v���C���[���ێ����郉�C�g�̍X�V����
		SetLight(g_aPlayer[nSelectPlayer].LightIdx00, D3DLIGHT_SPOT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(g_aPlayer[nSelectPlayer].pos.x, g_aPlayer[nSelectPlayer].pos.y + 50.0f, g_aPlayer[nSelectPlayer].pos.z), D3DXVECTOR3(sinf(Getrot(CurrentCamera).y), sinf(Getrot(CurrentCamera).x), cosf(Getrot(CurrentCamera).y)), PLAYER_LIGHT, 1.0f);

		//�w���vUI�̕\��
		if (g_aPlayer[nSelectPlayer].bGetKey == false)
		{
			CollisionKeyHelpUI(&g_aPlayer[nSelectPlayer].pos, 30.0f);
		}
		if (g_aPlayer[nSelectPlayer].bGetKey == true)
		{
			CollisionExitHelpUI(&g_aPlayer[nSelectPlayer].pos, 30.0f);
		}

		//���̓��菈��
		if (g_aPlayer[nSelectPlayer].bGetKey == false)
		{//�v���C���[�����������Ă��Ȃ��ꍇ
			if (GetKeyboardTrigger(DIK_E) == true || GetGamepadTrigger(BUTTON_A, nSelectPlayer) || GetGamepadTrigger(BUTTON_B, nSelectPlayer))
			{//E�L�[����
				if (CollisionKey(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nSelectPlayer) == true)
				{//�������o�����ꍇ
					g_aPlayer[nSelectPlayer].bGetKey = true;	//��������Ԃɂ���
					SetKeyUI(nSelectPlayer, true);				//��UI��\������

					g_aPlayer[nSelectPlayer].bCheck = true;

					//�����Q�b�g�����Ƃ�
					if (do_Tutorial == MODE_GET_KEY)
					{
						//�`�F�b�N�����鏈��
						SetCheckUI(nSelectPlayer, true);
					}
				}
			}
		}

		//�E�o����
		if (g_aPlayer[nSelectPlayer].bGetKey == true)
		{//�v���C���[�����������Ă���ꍇ
			if (GetKeyboardTrigger(DIK_E) == true || GetGamepadTrigger(BUTTON_A, nSelectPlayer) || GetGamepadTrigger(BUTTON_B, nSelectPlayer))
			{//E�L�[����
				if (CollisionExit(&g_aPlayer[nSelectPlayer].pos, &g_aPlayer[nSelectPlayer].posOld, &g_aPlayer[nSelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nSelectPlayer) == true)
				{//�������o�����ꍇ

					g_aPlayer[nSelectPlayer].bGetKey = false;	//������肵�ĂȂ���Ԃɂ���
					SetKeyUI(nSelectPlayer, false);			//��UI���\���ɂ���

															//�`���[�g���A�����[�h�E�o�̎�
					if (do_Tutorial == MODE_ESCAPE)
					{
						//�`�F�b�N������
						SetCheckUI(nSelectPlayer, true);

						do_Tutorial = MODE_GOEXIT;
					}

					if (do_Tutorial == MODE_GOEXIT)
					{
						do_Tutorial = MODE_END;
					}
				}
			}
		}

		//����������̌����̕␳
		if (g_aPlayer[nSelectPlayer].rot.y > D3DX_PI * 1.0f)
		{
			g_aPlayer[nSelectPlayer].rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_aPlayer[nSelectPlayer].rot.y < -D3DX_PI * 1.0f)
		{
			g_aPlayer[nSelectPlayer].rot.y += D3DX_PI * 2.0f;
		}

		//�̗͂����邩�ǂ����e�X�g�p
		if (GetKeyboardTrigger(DIK_M) == true)
		{
			PlayerHit(nSelectPlayer, 1);
		}

		//�Q�[���I������
		if (g_GameEnd == false)
		{
			if (g_aPlayer[0].bExit == true && g_aPlayer[1].bExit == true && g_aPlayer[2].bExit == true && g_aPlayer[3].bExit == true)
			{
				//�`���[�g���A�����[�h�E�o�̎�
				if (GetMode() == MODE_TUTORIAL)
				{
					g_GameEnd = true;
					SetFade(MODE_GAME);
				}
				if (GetMode() == MODE_GAME)
				{
					g_GameEnd = true;
					SetGameState(GAMESTATE_CLEAR_END, 60);
				}
			}

			if (g_aPlayer[0].bUse == false && g_aPlayer[1].bUse == false && g_aPlayer[2].bUse == false && g_aPlayer[3].bUse == false)
			{
				g_GameEnd = true;
				SetGameState(GAMESTATE_GAMEOVER_END, 60);
			}
		}

#ifdef _DEBUG
		PrintDebugProc("�yF3�z�Ńv���C���[�؂�ւ��F�y�v���C���[%d�z\n", nSelectPlayer + 1);

		for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
		{
			PrintDebugProc("�v���C���[%d�l�ڂ̍��W�yX : %f | Y : %f | Z : %f�z\n", nCntPlayer, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);
			PrintDebugProc("�v���C���[%d�l�ڂ̈ړ��ʁyX : %f | Y : %f | Z : %f�z\n", nCntPlayer, g_aPlayer[nCntPlayer].move.x, g_aPlayer[nCntPlayer].move.y, g_aPlayer[nCntPlayer].move.z);
		}
#endif
	}
}

//====================================================================
//�v���C���[�̈ړ����͏���
//====================================================================
void PlayerMoveInput(int nCnt)
{
	//���̎擾
	Stamina *pStamina = GetStamina();
	Camera *pCamera = GetCamera();
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	int CurrentCamera = GetCurrentCamera();
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();
	MODE mode = GetMode();


	//�΂߈ړ��̑��x�C���p�̊֐�������������
	g_aPlayer[nCnt].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (g_aPlayer[nCnt].State != PLAYER_EXSIT)
	{//�v���C���[�̏�Ԃ��E�o��ԈȊO�̏ꍇ
	 //�L�[�{�[�h�̈ړ�����
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.z += 1.0f * cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.x += 1.0f * sinf(Getrot(CurrentCamera).y);

		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.z += -1.0f * cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.x += -1.0f * sinf(Getrot(CurrentCamera).y);
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.x += -1.0f * cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.z -= -1.0f * sinf(Getrot(CurrentCamera).y);

		}
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.x += 1.0f * cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.z -= 1.0f * sinf(Getrot(CurrentCamera).y);
		}

		if (GetKeyboardPress(DIK_W) == false && GetKeyboardPress(DIK_S) == false && GetKeyboardPress(DIK_A) == false && GetKeyboardPress(DIK_D) == false)
		{//�L�[�{�[�h�Ɠ����ɓ��͂ł��Ȃ��悤�ɂ���
			if (GetGamepad_Stick_Left(0).y > 0.0f)
			{//���X�e�B�b�N�̏����
				g_aPlayer[nCnt].NormarizeMove.z += cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.x += sinf(Getrot(CurrentCamera).y);

				g_aPlayer[CurrentCamera].bCheck = true;

				//�ړ�������`�F�b�N�����鏈��
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//�ړ�������Ԃɂ���
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(0).y < 0.0f)
			{//���X�e�B�b�N�̉�����
				g_aPlayer[nCnt].NormarizeMove.z -= cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.x -= sinf(Getrot(CurrentCamera).y);

				g_aPlayer[CurrentCamera].bCheck = true;

				//�ړ�������`�F�b�N�����鏈��
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//�ړ�������Ԃɂ���
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(0).x > 0.0f)
			{//���X�e�B�b�N�̉E����
			 //���X�e�B�b�N�ɂ�鍶�E�ړ�
				g_aPlayer[nCnt].NormarizeMove.x += cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.z -= sinf(Getrot(CurrentCamera).y);

				g_aPlayer[CurrentCamera].bCheck = true;

				//�ړ�������`�F�b�N�����鏈��
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//�ړ�������Ԃɂ���
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(0).x < 0.0f)
			{//���X�e�B�b�N�̍�����
			 //���X�e�B�b�N�ɂ�鍶�E�ړ�
				g_aPlayer[nCnt].NormarizeMove.x -= cosf(Getrot(CurrentCamera).y);
				g_aPlayer[nCnt].NormarizeMove.z += sinf(Getrot(CurrentCamera).y);

				g_aPlayer[CurrentCamera].bCheck = true;

				//�ړ�������`�F�b�N�����鏈��
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//�ړ�������Ԃɂ���
					MoveTCheck(nCnt, true);
				}
			}
		}

		//�m�[�}���C�Y�ɂ���Ď΂߈ړ��̑��x���C������
		g_aPlayer[nCnt].NormarizeMove.y = 0.0f;

		D3DXVec3Normalize(&g_aPlayer[nCnt].NormarizeMove, &g_aPlayer[nCnt].NormarizeMove);

		//�L�[�{�[�h�̎��̑��x�ݒ�
		if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_SPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_SPEED;
		}

		//���X�e�B�b�N�̑��x�����ƈړ��̎O�i�K�̎g����������
		if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) != 0 && GetGamepadPress(BUTTON_R, 0) || GetKeyboardPress(DIK_SPACE) == true)
		{//���͂��Ă��Ԃ���A�{�^���������Ă���Ƃ�
			if (pStamina[nCnt].bFatige == false)			//�v���C���[��������Ԃ��ǂ���
			{//��J��Ԃł͂Ȃ������ꍇ

				g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_DASHSPEED;
				g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_DASHSPEED;

				//�v���C���[���_�b�V����Ԃɂ���
				g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_DASH;

				//�_�b�V��������`�F�b�N��Ԃɂ��鏈��
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_DASH)
				{
					SetCheckUI(nCnt, true);
				}
			}
		}
		else if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) < 0.95f)
		{//���X�e�B�b�N��|���؂��Ă��Ȃ���Ԃ̂Ƃ�

			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_STEALTHSPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_STEALTHSPEED;

			g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;

			//�v���C���[���X�e���X��Ԃɂ���
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;

			//�`���[�g���A���X�e���X��Ԃ̎��̏���
			if (mode == MODE_TUTORIAL && do_Tutorial == MODE_STELTH && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_STEALTH)
			{
				if (g_aPlayer[nCnt].move != D3DXVECTOR3(0.0f, 0.0f, 0.0f) && g_aPlayer[nCnt].nStelthCnt > 299)
				{
					{
						//�`�F�b�N�����鏈��
						SetCheckUI(nCnt, true);
					}
				}
				g_aPlayer[nCnt].nStelthCnt++;
			}

			//�J������Ԃ𖳂�
			pCamera[nCnt].State = CAMERASTATE_NONE;
		}
		else if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) != 0)
		{//���͂��Ă����Ԃ̂Ƃ�

			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_SPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_SPEED;

			//�v���C���[��ʏ��Ԃɂ���
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_NORMAL;

			//�J������Ԃ𖳂�
			pCamera[nCnt].State = CAMERASTATE_NONE;
		}
		else
		{//���͂��Ă��Ȃ��ꍇ

		 //�v���C���[���X�e���X��Ԃɂ���
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;

			//�J������Ԃ𖳂�
			pCamera[nCnt].State = CAMERASTATE_NONE;
		}

		g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;
	}
	else if (g_aPlayer[nCnt].State == PLAYER_EXSIT)
	{//�v���C���[�̏�Ԃ��E�o��Ԃ̎�

		D3DXVECTOR3 posDest;			//�ړI�̈ʒu

		D3DXVECTOR3 posDiff = D3DXVECTOR3(-1000.0f, 0.0f, -4000.0f);

		posDest = posDiff - g_aPlayer[nCnt].pos;

		g_aPlayer[nCnt].pos.x += posDest.x * 0.005f;
		g_aPlayer[nCnt].pos.z += posDest.z * 0.0006f;
	}
}

//====================================================================
//�v���C���[�̌����̕␳
//====================================================================
void PlayerRotUpdate(int nCnt)
{
	//�ړ������Ɍ��������킹�鏈��
	float fRotMove, fRotDest, fRotDiff;

	int CurrentCamera = GetCurrentCamera();

	fRotMove = g_aPlayer[nCnt].rot.y;
	fRotDest = Getrot(CurrentCamera).y;

	if (GetKeyboardPress(DIK_C) == true)
	{
		g_aPlayer[nCnt].rot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_aPlayer[nCnt].rot.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_W) == true || GetGamepad_Stick_Left(0).y > 0.1f)
	{
		if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * 0.25f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * -0.25f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y));
		}
	}
	else if (GetKeyboardPress(DIK_S) == true || GetGamepad_Stick_Left(0).y < -0.1f)
	{
		if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * -0.75f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).x > 0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(0).x < -0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(Getrot(CurrentCamera).y), cosf(Getrot(CurrentCamera).y)) + D3DX_PI * -0.5f;
	}

	fRotDiff = fRotDest - fRotMove;

	if (fRotDiff > D3DX_PI * 1.0f)
	{
		fRotDiff -= D3DX_PI * 2.0f;
	}
	else if (fRotDiff < -D3DX_PI * 1.0f)
	{
		fRotDiff += D3DX_PI * 2.0f;
	}

	fRotMove += fRotDiff * PLAYER_ROT_SPEED;

	if (fRotMove > D3DX_PI * 1.0f)
	{
		fRotMove -= D3DX_PI * 2.0f;
	}
	else if (fRotMove < -D3DX_PI * 1.0f)
	{
		fRotMove += D3DX_PI * 2.0f;
	}

	if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).y != 0.0f || GetGamepad_Stick_Left(0).x != 0.0f)
	{
		g_aPlayer[nCnt].rot.y = fRotMove;
	}
}

//====================================================================
//�v���C���[�̍X�V����(�����̃R���g���[���Ή�)
//====================================================================
void UpdatePlayer1(void)
{
	//�`���[�g���A���̍��ڏ���^���鏈��
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();
	MODE mode = GetMode();

	//�|�C���^���̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	Camera *pCamera = GetCamera();
	int CurrentCamera = GetCurrentCamera();

	//�J�����ԍ����v���C���[�ɑ��
	//nCntPlayer = CurrentCamera;

	for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
	{
		//�v���C���[�̏�ԊǗ�
		PlayerState(nCntPlayer);

		if (g_aPlayer[nCntPlayer].bUse == true && pCamera[nCntPlayer].bUse == true && g_aPlayer[nCntPlayer].State == PLAYER_NORMAL)
		{
#ifdef _DEBUG
			//�o�C�u���[�V����
			if (GetKeyboardTrigger(DIK_F6) == true)
			{
				PlayerSetVibrtion(nCntPlayer, 60, 0, 60000, 0);
			}
			if (GetKeyboardTrigger(DIK_F7) == true)
			{
				GetGamepad_Vibrtion_false(nCntPlayer);
			}
#endif

			//�o�C�u���[�V�����̍X�V����
			PlayerVibrtionUpdate(nCntPlayer);

			g_aPlayer[nCntPlayer].posOld = g_aPlayer[nCntPlayer].pos;

			//�����W��
			g_aPlayer[nCntPlayer].move.x = g_aPlayer[nCntPlayer].move.x * 0.5f;
			g_aPlayer[nCntPlayer].move.z = g_aPlayer[nCntPlayer].move.z * 0.5f;

			//�l�̐؂�̂�
			if (g_aPlayer[nCntPlayer].move.x <= 0.005f && g_aPlayer[nCntPlayer].move.x >= -0.005f)
			{
				g_aPlayer[nCntPlayer].move.x = 0.0f;
			}
			if (g_aPlayer[nCntPlayer].move.z <= 0.005f && g_aPlayer[nCntPlayer].move.z >= -0.005f)
			{
				g_aPlayer[nCntPlayer].move.z = 0.0f;
			}

#ifdef _DEBUG
			if (GetKeyboardTrigger(DIK_F5) == true)
			{//�L�[�������ꂽ�ꍇ
				g_bPlayerOps = g_bPlayerOps ? false : true;			//�ώ@�p���[�h�ɕύX
			}
#endif

			if (g_bPlayerOps == false)
			{
				//�v���C���[�̈ړ����͏���----------
				ResPlayerMove(nCntPlayer);

				//�ړ����Ƀv���C���[�̌�����␳����----------
				ResPlayerrot(nCntPlayer);
			}

			//�ʒu�X�V(���͂ɂ�铮��)
			g_aPlayer[nCntPlayer].pos += g_aPlayer[nCntPlayer].move;

			//�I�u�W�F�N�g�Ƃ̓����蔻��
			CollisionObject00(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 50.0f, 10.0f), 10.0f);
			CollisionObjectWall(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 50.0f, 10.0f), 10.0f);
			//�O�ς̓����蔻��
			//CollisionOuterProductObject00(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move);

			if (GetPlayModeSelect().CurrentModeNumber == 1)
			{
				//�A�C�e���Ƃ̓����蔻��
				CollisionItem(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-20.0f, -20.0f, -20.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f), 20.0f, nCntPlayer);
			}

			if (g_aPlayer[nCntPlayer].bExit == false)
			{//�E�o���Ă��Ȃ���Ԃ̎�

			 //�o���Ƃ̓����蔻��
				CollisionExi(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);
			}

			//�v���C���[�ƓG�Ƃ̋���
			PlayerDistance(nCntPlayer);

			//�v���C���[���ێ����郉�C�g�̍X�V����
			SetLight(g_aPlayer[nCntPlayer].LightIdx00, D3DLIGHT_SPOT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y + 50.0f, g_aPlayer[nCntPlayer].pos.z), D3DXVECTOR3(sinf(Getrot(nCntPlayer).y), sinf(Getrot(nCntPlayer).x), cosf(Getrot(nCntPlayer).y)), PLAYER_LIGHT, 1.0f);

			//�w���vUI�̕\��
			if (g_aPlayer[nCntPlayer].bGetKey == false)
			{
				g_aPlayer[nCntPlayer].KeyHelpUI = CollisionKeyHelpUI(&g_aPlayer[nCntPlayer].pos, 200.0f);
			}
			if (g_aPlayer[nCntPlayer].bGetKey == true)
			{
				g_aPlayer[nCntPlayer].ExitHelpUI = CollisionExitHelpUI(&g_aPlayer[nCntPlayer].pos, 350.0f);
			}

			//���̓��菈��
			if (g_aPlayer[nCntPlayer].bGetKey == false)
			{//�v���C���[�����������Ă��Ȃ��ꍇ
				if (GetKeyboardTrigger(DIK_E) == true || GetGamepadTrigger(BUTTON_A, nCntPlayer) || GetGamepadTrigger(BUTTON_B, nCntPlayer))
				{//E�L�[����
					if (CollisionKey(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nCntPlayer) == true)
					{//�������o�����ꍇ
						g_aPlayer[nCntPlayer].bGetKey = true;	//��������Ԃɂ���
						SetKeyUI(nCntPlayer, true);				//��UI��\������
						g_aPlayer[nCntPlayer].KeyHelpUI = false;

						//���̓��艹
						PlaySound(SOUND_LABEL_SE_GETKEY);

						g_aPlayer[nCntPlayer].bCheck = true;

						//�����Q�b�g�����Ƃ�
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_GET_KEY)
						{
							//�`�F�b�N�����鏈��
							SetCheckUI(nCntPlayer, true);
						}
					}
				}
			}

			//�E�o����
			if (g_aPlayer[nCntPlayer].bGetKey == true)
			{//�v���C���[�����������Ă���ꍇ
				if (GetKeyboardTrigger(DIK_E) == true || GetGamepadTrigger(BUTTON_A, nCntPlayer) || GetGamepadTrigger(BUTTON_B, nCntPlayer))
				{//E�L�[����
					if (CollisionExit(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nCntPlayer) == true)
					{//�������o�����ꍇ

						//�h�A�̃J�M���������鉹
						PlaySound(SOUND_LABEL_SE_UNLOCKKEY);

						//�h�A�̊J��
						PlaySound(SOUND_LABEL_SE_DOOR);

						g_aPlayer[nCntPlayer].bGetKey = false;	//������肵�ĂȂ���Ԃɂ���
						SetKeyUI(nCntPlayer, false);			//��UI���\���ɂ���
						g_aPlayer[nCntPlayer].ExitHelpUI = false;

						//�`���[�g���A�����[�h�E�o�̎�
						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_ESCAPE)
						{
							//�`�F�b�N������
							SetCheckUI(nCntPlayer, true);

							do_Tutorial = MODE_GOEXIT;
						}

						if (mode == MODE_TUTORIAL && do_Tutorial == MODE_GOEXIT)
						{
							do_Tutorial = MODE_END;
						}
					}
				}
			}

			//�v���C���[���J�M�������Ă��Ȃ��Ƃ�
			else
			{//�v���C���[�����������Ă���ꍇ
				if (GetKeyboardTrigger(DIK_E) == true || GetGamepadTrigger(BUTTON_A, nCntPlayer) || GetGamepadTrigger(BUTTON_B, nCntPlayer))
				{//E�L�[����
					if (CollisionExit(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, nCntPlayer) == true)
					{//�������o�����ꍇ
						//���������Ă��Ȃ��Ƃ��̉�
						PlaySound(SOUND_LABEL_SE_NOKEY);
					}
				}
			}

			//����������̌����̕␳
			if (g_aPlayer[nCntPlayer].rot.y > D3DX_PI * 1.0f)
			{
				g_aPlayer[nCntPlayer].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aPlayer[nCntPlayer].rot.y < -D3DX_PI * 1.0f)
			{
				g_aPlayer[nCntPlayer].rot.y += D3DX_PI * 2.0f;
			}

			//�̗͂����邩�ǂ����e�X�g�p
			if (GetKeyboardTrigger(DIK_M) == true)
			{
				PlayerHit(nCntPlayer, 1);
			}
		}
	}

	//�Q�[���I������
	if (g_GameEnd == false)
	{
		if ((g_aPlayer[0].bExit == true || g_aPlayer[0].bUse == false) &&
			(g_aPlayer[1].bExit == true || g_aPlayer[1].bUse == false) &&
			(g_aPlayer[2].bExit == true || g_aPlayer[2].bUse == false) &&
			(g_aPlayer[3].bExit == true || g_aPlayer[3].bUse == false))
		{//�S���E�o���Ă���Ƃ�

			for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
			{
				if (g_aPlayer[nCntPlayer].bExit == true)
				{
					g_ExitCount++;
				}
			}

			//�`���[�g���A�����[�h�E�o�̎�
			if (GetMode() == MODE_TUTORIAL)
			{
				g_GameEnd = true;
				SetFade(MODE_GAME);
			}
			if (GetMode() == MODE_GAME)
			{
				g_GameEnd = true;
				SetGameState(GAMESTATE_CLEAR_END, 60);
			}
		}

		if ((g_aPlayer[0].bUse == false) && 
			(g_aPlayer[1].bUse == false) && 
			(g_aPlayer[2].bUse == false) && 
			(g_aPlayer[3].bUse == false))
		{//�S�����S���Ă���Ƃ�
			g_GameEnd = true;
			SetGameState(GAMESTATE_GAMEOVER_END, 60);
		}
	}

#ifdef _DEBUG
	for (int nCntPlayerPlayer = 0; nCntPlayerPlayer < PlayNumber.CurrentSelectNumber; nCntPlayerPlayer++)
	{
		PrintDebugProc("�v���C���[%d�l�ڂ̍��W�yX : %f | Y : %f | Z : %f�z\n", nCntPlayerPlayer + 1, g_aPlayer[nCntPlayerPlayer].pos.x, g_aPlayer[nCntPlayerPlayer].pos.y, g_aPlayer[nCntPlayerPlayer].pos.z);
		PrintDebugProc("�v���C���[%d�l�ڂ̈ړ��ʁyX : %f | Y : %f | Z : %f�z\n", nCntPlayerPlayer + 1, g_aPlayer[nCntPlayerPlayer].move.x, g_aPlayer[nCntPlayerPlayer].move.y, g_aPlayer[nCntPlayerPlayer].move.z);
		PrintDebugProc("�v���C���[���E�o�������y%d�z\n", g_ExitCount);
	}
#endif
}

//====================================================================
//�v���C���[�̈ړ����͏���(����)
//====================================================================
void ResPlayerMove(int nCnt)
{
	//���̎擾
	Stamina *pStamina = GetStamina();
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	Camera *pCamera = GetCamera();
	int CurrentCamera = GetCurrentCamera();
	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();
	MODE mode = GetMode();

	//�΂߈ړ��̑��x�C���p�̊֐�������������
	g_aPlayer[nCnt].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (g_aPlayer[nCnt].State != PLAYER_EXSIT)
	{//�v���C���[�̏�Ԃ��E�o��ԈȊO�̏ꍇ
	 //�L�[�{�[�h�̈ړ�����
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.z += 1.0f * cosf(pCamera[nCnt].rot.y);
			g_aPlayer[nCnt].NormarizeMove.x += 1.0f * sinf(pCamera[nCnt].rot.y);

		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.z += -1.0f * cosf(pCamera[nCnt].rot.y);
			g_aPlayer[nCnt].NormarizeMove.x += -1.0f * sinf(pCamera[nCnt].rot.y);
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.x += -1.0f * cosf(pCamera[nCnt].rot.y);
			g_aPlayer[nCnt].NormarizeMove.z -= -1.0f * sinf(pCamera[nCnt].rot.y);

		}
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.x += 1.0f * cosf(pCamera[nCnt].rot.y);
			g_aPlayer[nCnt].NormarizeMove.z -= 1.0f * sinf(pCamera[nCnt].rot.y);
		}

		if (GetKeyboardPress(DIK_W) == false && GetKeyboardPress(DIK_S) == false && GetKeyboardPress(DIK_A) == false && GetKeyboardPress(DIK_D) == false)
		{//�L�[�{�[�h�Ɠ����ɓ��͂ł��Ȃ��悤�ɂ���
			if (GetGamepad_Stick_Left(nCnt).y > 0.0f)
			{//���X�e�B�b�N�̏����
				g_aPlayer[nCnt].NormarizeMove.z += cosf(pCamera[nCnt].rot.y);
				g_aPlayer[nCnt].NormarizeMove.x += sinf(pCamera[nCnt].rot.y);

				g_aPlayer[nCnt].nPlayerSECount++;

				if (g_aPlayer[nCnt].nPlayerSECount > PLAYER_SE_WALK && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_NORMAL)
				{
					//�v���C���[�̕���
					PlaySound(SOUND_LABEL_SE_WALK);

					g_aPlayer[nCnt].nPlayerSECount = 0;
				}

				else
				{

				}

				//�ړ�������`�F�b�N�����鏈��
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//�ړ�������Ԃɂ���
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(nCnt).y < 0.0f)
			{//���X�e�B�b�N�̉�����
				g_aPlayer[nCnt].NormarizeMove.z -= cosf(pCamera[nCnt].rot.y);
				g_aPlayer[nCnt].NormarizeMove.x -= sinf(pCamera[nCnt].rot.y);

				g_aPlayer[nCnt].nPlayerSECount++;

				if (g_aPlayer[nCnt].nPlayerSECount > PLAYER_SE_WALK && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_NORMAL)
				{
					//�v���C���[�̕���
					PlaySound(SOUND_LABEL_SE_WALK);

					g_aPlayer[nCnt].nPlayerSECount = 0;
				}

				else
				{

				}

				//�ړ�������`�F�b�N�����鏈��
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//�ړ�������Ԃɂ���
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(nCnt).x > 0.0f)
			{//���X�e�B�b�N�̉E����
			 //���X�e�B�b�N�ɂ�鍶�E�ړ�
				g_aPlayer[nCnt].NormarizeMove.x += cosf(pCamera[nCnt].rot.y);
				g_aPlayer[nCnt].NormarizeMove.z -= sinf(pCamera[nCnt].rot.y);

				g_aPlayer[nCnt].nPlayerSECount++;

				if (g_aPlayer[nCnt].nPlayerSECount > PLAYER_SE_WALK && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_NORMAL)
				{
					//�v���C���[�̕���
					PlaySound(SOUND_LABEL_SE_WALK);

					g_aPlayer[nCnt].nPlayerSECount = 0;
				}

				else
				{

				}

				//�ړ�������`�F�b�N�����鏈��
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//�ړ�������Ԃɂ���
					MoveTCheck(nCnt, true);
				}
			}
			if (GetGamepad_Stick_Left(nCnt).x < 0.0f)
			{//���X�e�B�b�N�̍�����
			 //���X�e�B�b�N�ɂ�鍶�E�ړ�
				g_aPlayer[nCnt].NormarizeMove.x -= cosf(pCamera[nCnt].rot.y);
				g_aPlayer[nCnt].NormarizeMove.z += sinf(pCamera[nCnt].rot.y);

				g_aPlayer[nCnt].nPlayerSECount++;

				if (g_aPlayer[nCnt].nPlayerSECount > PLAYER_SE_WALK && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_NORMAL)
				{
					//�v���C���[�̕���
					PlaySound(SOUND_LABEL_SE_WALK);

					g_aPlayer[nCnt].nPlayerSECount = 0;
				}

				else
				{

				}

				//�ړ�������`�F�b�N�����鏈��
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_MOVE)
				{
					//�ړ�������Ԃɂ���
					MoveTCheck(nCnt, true);
				}
			}
		}

		//�m�[�}���C�Y�ɂ���Ď΂߈ړ��̑��x���C������
		g_aPlayer[nCnt].NormarizeMove.y = 0.0f;

		D3DXVec3Normalize(&g_aPlayer[nCnt].NormarizeMove, &g_aPlayer[nCnt].NormarizeMove);

		//�L�[�{�[�h�̎��̑��x�ݒ�
		if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true)
		{
			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_SPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_SPEED;
		}

		//���X�e�B�b�N�̑��x�����ƈړ��̎O�i�K�̎g����������
		if (fabsf(GetGamepad_Stick_Left(nCnt).y) + fabsf(GetGamepad_Stick_Left(nCnt).x) != 0 && GetGamepadPress(BUTTON_R, nCnt) || GetKeyboardPress(DIK_SPACE) == true)
		{//���͂��Ă��Ԃ���A�{�^���������Ă���Ƃ�
			if (pStamina[nCnt].bFatige == false)			//�v���C���[��������Ԃ��ǂ���
			{//��J��Ԃł͂Ȃ������ꍇ

				g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_DASHSPEED;
				g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_DASHSPEED;

				g_aPlayer[nCnt].nPlayerSECount++;

				if (g_aPlayer[nCnt].nPlayerSECount > PLAYER_SE_DASH && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_DASH)
				{
					//�_�b�V����Ԃ̉�
					PlaySound(SOUND_LABEL_SE_WALK);

					g_aPlayer[nCnt].nPlayerSECount = 0;
				}

				else
				{

				}

				//�v���C���[���_�b�V����Ԃɂ���
				g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_DASH;

				//�_�b�V��������`�F�b�N��Ԃɂ��鏈��
				if (mode == MODE_TUTORIAL && do_Tutorial == MODE_DASH)
				{
					SetCheckUI(nCnt, true);
				}
			}
		}
		else if (fabsf(GetGamepad_Stick_Left(nCnt).y) + fabsf(GetGamepad_Stick_Left(nCnt).x) < 0.95f)
		{//���X�e�B�b�N��|���؂��Ă��Ȃ���Ԃ̂Ƃ�

			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_STEALTHSPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_STEALTHSPEED;

			g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;

			//�v���C���[���X�e���X��Ԃɂ���
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;

			//�`���[�g���A���X�e���X��Ԃ̎��̏���
			if (mode == MODE_TUTORIAL && do_Tutorial == MODE_STELTH && g_aPlayer[nCnt].MoveState == PLAYER_MOVESTATE_STEALTH)
			{
				if (g_aPlayer[nCnt].move != D3DXVECTOR3(0.0f, 0.0f, 0.0f) && g_aPlayer[nCnt].nStelthCnt > 299)
				{
					{
						//�`�F�b�N�����鏈��
						SetCheckUI(nCnt, true);
					}
				}
				g_aPlayer[nCnt].nStelthCnt++;
			}
		}
		else if (fabsf(GetGamepad_Stick_Left(nCnt).y) + fabsf(GetGamepad_Stick_Left(nCnt).x) != 0)
		{//���͂��Ă����Ԃ̂Ƃ�

			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_SPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_SPEED;

			//�v���C���[��ʏ��Ԃɂ���
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_NORMAL;
		}
		else
		{//���͂��Ă��Ȃ��ꍇ

		 //�v���C���[���X�e���X��Ԃɂ���
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;
		}
	}
	else if (g_aPlayer[nCnt].State == PLAYER_EXSIT)
	{//�v���C���[�̏�Ԃ��E�o��Ԃ̎�

		D3DXVECTOR3 posDest;			//�ړI�̈ʒu

		D3DXVECTOR3 posDiff = D3DXVECTOR3(-1000.0f, 0.0f, -4000.0f);

		posDest = posDiff - g_aPlayer[nCnt].pos;

		g_aPlayer[nCnt].pos.x += posDest.x * 0.005f;
		g_aPlayer[nCnt].pos.z += posDest.z * 0.0006f;
	}

	g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;
}

//====================================================================
//�v���C���[�̌����␳(����)
//====================================================================
void ResPlayerrot(int nCnt)
{
	Camera *pCamera = GetCamera();

	//�ړ������Ɍ��������킹�鏈��
	float fRotMove, fRotDest, fRotDiff;

	fRotMove = g_aPlayer[nCnt].rot.y;
	fRotDest = pCamera[nCnt].rot.y;

	if (GetKeyboardPress(DIK_C) == true)
	{
		g_aPlayer[nCnt].rot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_aPlayer[nCnt].rot.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_W) == true || GetGamepad_Stick_Left(nCnt).y > 0.1f)
	{
		if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(nCnt).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * 0.25f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(nCnt).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * -0.25f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y));
		}
	}
	else if (GetKeyboardPress(DIK_S) == true || GetGamepad_Stick_Left(nCnt).y < -0.1f)
	{
		if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(nCnt).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(nCnt).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * -0.75f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(nCnt).x > 0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(nCnt).x < -0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(pCamera[nCnt].rot.y), cosf(pCamera[nCnt].rot.y)) + D3DX_PI * -0.5f;
	}

	fRotDiff = fRotDest - fRotMove;

	if (fRotDiff > D3DX_PI * 1.0f)
	{
		fRotDiff -= D3DX_PI * 2.0f;
	}
	else if (fRotDiff < -D3DX_PI * 1.0f)
	{
		fRotDiff += D3DX_PI * 2.0f;
	}

	fRotMove += fRotDiff * PLAYER_ROT_SPEED;

	if (fRotMove > D3DX_PI * 1.0f)
	{
		fRotMove -= D3DX_PI * 2.0f;
	}
	else if (fRotMove < -D3DX_PI * 1.0f)
	{
		fRotMove += D3DX_PI * 2.0f;
	}

	if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(nCnt).y != 0.0f || GetGamepad_Stick_Left(nCnt).x != 0.0f)
	{
		g_aPlayer[nCnt].rot.y = fRotMove;
	}
}

//====================================================================
//�v���C���[�̏�ԊǗ�
//====================================================================
void PlayerState(int nCnt)
{
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//�v���C���[�̏��
	switch (g_aPlayer[nCnt].State)
	{
	case PLAYER_NORMAL:
		break;

	case PLAYER_WAIT:
		g_aPlayer[nCnt].nWaitCounter--;
		if (g_aPlayer[nCnt].nWaitCounter < 0)
		{
			g_aPlayer[nCnt].nWaitCounter = PLAYER_WAITCOUNTER;
			g_aPlayer[nCnt].State = PLAYER_NORMAL;
		}
		break;

	case PLAYER_HIT:
		g_aPlayer[nCnt].nHitCounter--;
		g_Rand_PolygonColor_R = rand() % 11;
		g_Rand_PolygonColor_G = rand() % 4;
		g_Rand_PolygonColor_B = rand() % 11;
		g_Rand_PolygonColor_A = rand() % 11;
		g_Rand_PolygonType = rand() % 4;
		if (g_aPlayer[nCnt].nHitCounter == 59)
		{
			switch (PlayNumber.CurrentSelectNumber)
			{
			case 1:
				SetPolygonBG(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 640.0f, 360.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				break;
			case 2:
				SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 360.0f, 0.0f), 320.0f, 360.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				break;
			case 3:
				if (nCnt == 2)
				{//3
					SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				}
				else
				{//12
					SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				}
				break;
			case 4:
				if (nCnt == 3)
				{//4
					SetPolygonBG(D3DXVECTOR3(960.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				}
				else if (nCnt == 2)
				{//3
					SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				}
				else
				{//12
					SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, g_Rand_PolygonType);
				}
				break;
			}
		}
		if (g_aPlayer[nCnt].nHitCounter % 10 == 0)
		{
			switch (PlayNumber.CurrentSelectNumber)
			{
			case 1:
				SetPolygonBG(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 640.0f, 360.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				break;
			case 2:
				SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 360.0f, 0.0f), 320.0f, 360.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				break;
			case 3:
				if (nCnt == 2)
				{//3
					SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				}
				else
				{//12
					SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				}
				break;
			case 4:
				if (nCnt == 3)
				{//4
					SetPolygonBG(D3DXVECTOR3(960.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				}
				else if (nCnt == 2)
				{//3
					SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				}
				else
				{//12
					SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR((float)g_Rand_PolygonColor_R * 0.1f, (float)g_Rand_PolygonColor_G * 0.1f, (float)g_Rand_PolygonColor_B * 0.1f, (float)g_Rand_PolygonColor_A * 0.1f), 30, g_Rand_PolygonType);
				}
				break;
			}
		}
		if (g_aPlayer[nCnt].nHitCounter < 0)
		{
			g_aPlayer[nCnt].State = PLAYER_WAIT;
		}
		break;

	case PLAYER_DAMAGE:
		g_aPlayer[nCnt].nDamageCounter--;
		if (g_aPlayer[nCnt].nDamageCounter < 0)
		{
			g_aPlayer[nCnt].State = PLAYER_DEATH;
		}
		break;

	case PLAYER_DEATH:
		switch (PlayNumber.CurrentSelectNumber)
		{
		case 1:
			SetPolygonBG(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 640.0f, 360.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 30, 4);
			break;
		case 2:
			SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 360.0f, 0.0f), 320.0f, 360.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 30, 4);
			break;
		case 3:
			if (nCnt == 2)
			{//3
				SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 30, 4);
			}
			else
			{//12
				SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 30, 4);
			}
			break;
		case 4:
			if (nCnt == 3)
			{//4
				SetPolygonBG(D3DXVECTOR3(960.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 30, 4);
			}
			else if (nCnt == 2)
			{//3
				SetPolygonBG(D3DXVECTOR3(320.0f, 540.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 30, 4);
			}
			else
			{//12
				SetPolygonBG(D3DXVECTOR3(320.0f + nCnt * 640.0f, 180.0f, 0.0f), 320.0f, 180.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 30, 4);
			}
			break;
		}
		//���񂾃v���C���[�̃o�C�u���[�V�������I�t�ɂ���
		GetGamepad_Vibrtion_false(nCnt);
		break;
	case PLAYER_EXSIT:

		D3DXVECTOR3 posDest;			//�ړI�̈ʒu

		D3DXVECTOR3 posDiff = D3DXVECTOR3(-1000.0f, 0.0f, -4000.0f);

		posDest = posDiff - g_aPlayer[nCnt].pos;

		g_aPlayer[nCnt].pos.x += posDest.x * 0.005f;
		g_aPlayer[nCnt].pos.z += posDest.z * 0.0006f;
		SetLife(0, nCnt);
		break;
	}
}

//====================================================================
//�v���C���[�̃o�C�u���[�V�����̍X�V����
//====================================================================
void PlayerVibrtionUpdate(int nCnt)
{
	if (g_aPlayer[nCnt].bVibrtion == true)
	{
		g_aPlayer[nCnt].VibrtionTrueCount++;

		if (g_aPlayer[nCnt].VibrtionTrueCount >= g_aPlayer[nCnt].VibrtionTime)
		{
			g_aPlayer[nCnt].bVibrtion = false;
			g_aPlayer[nCnt].VibrtionTrueCount = 0;
			GetGamepad_Vibrtion_false(nCnt);
		}
	}
	else if (g_aPlayer[nCnt].VibrtionFalseCount > 0)
	{
		g_aPlayer[nCnt].VibrtionFalseCount--;
	}
}

//====================================================================
//�v���C���[�̃o�C�u���[�V�����̐ݒ菈��
//====================================================================
void PlayerSetVibrtion(int nCnt, int nTrueCounter, int nFalseCounter, int nLeftPower, int RightPoewr)
{
	if (g_aPlayer[nCnt].bVibrtion == false)
	{
		g_aPlayer[nCnt].bVibrtion = true;
		g_aPlayer[nCnt].VibrtionTime = nTrueCounter;
		g_aPlayer[nCnt].VibrtionFalseCount = nFalseCounter;
		GetGamepad_Vibrtion(nCnt, nLeftPower, RightPoewr);
	}
}

//====================================================================
//�v���C���[�ƓG�Ƃ̋�������
//====================================================================
void PlayerDistance(int nCnt)
{
	ENEMY *pEnemy = GetEnemy();

	TUTORIAL_MODE do_Tutorial = GetDoEscapeTutorial();

	MODE mode = GetMode();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, PLAYER_DISTANCE_APPEAR, 0.0f, -10.0f, 50.0f) == true)
			{//�G�̕\������
				g_aPlayer[nCnt].bAppear = true;
				break;
			}
			else
			{
				g_aPlayer[nCnt].bAppear = false;
#if _DEBUG
				g_aPlayer[nCnt].bAppear = true;
#endif // _DEBUG

			}
		}
	}

	pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, PLAYER_DISTANCE_VIB, 0.0f, -10.0f, 50.0f) == true)
			{//�o�C�u���[�V��������
				if (g_aPlayer[nCnt].VibrtionFalseCount <= 0)
				{
					PlayerSetVibrtion(nCnt, 10, 10, 40000, 40000);

					if (mode == MODE_TUTORIAL && do_Tutorial == MODE_VIBE)
					{
						g_aPlayer[nCnt].nVibCnt++;
						if (g_aPlayer[nCnt].nVibCnt > 5)
						{
							SetCheckUI(nCnt, true);
						}
					}

					else if (do_Tutorial != MODE_VIBE)
					{

					}
				}
			}
			else
			{
				//GetGamepad_Vibrtion_false(nCnt);
			}

			if (CollisionCircle(g_aPlayer[nCnt].pos, pEnemy->pos, PLAYER_DISTANCE_SE, 0.0f, -10.0f, 50.0f) == true)
			{//�T�E���h����
				nEnemySECount++;

				if (nEnemySECount > ENEMY_SE_SPEED)
				{
					PlaySound(SOUND_LABEL_SE_ENEMYMOVE);

					nEnemySECount = 0;
				}
			}
			else
			{

			}
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻��
//====================================================================
int CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY)
{
	//���ӁFint�̕Ԃ�l��Hit�̊֐����ĂԂ��ƁI
	int nCntHit = -1;
	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == true)
		{
			if (
				pos.z + Size >= g_aPlayer[nCntPlayer].pos.z - PLAYER_COLLISIONSIZE &&
				pos.z - Size <= g_aPlayer[nCntPlayer].pos.z + PLAYER_COLLISIONSIZE &&
				pos.x + Size >= g_aPlayer[nCntPlayer].pos.x - PLAYER_COLLISIONSIZE &&
				pos.x - Size <= g_aPlayer[nCntPlayer].pos.x + PLAYER_COLLISIONSIZE &&
				pos.y + MaxY >= g_aPlayer[nCntPlayer].pos.y - 10.0f &&
				pos.y + MinY <= g_aPlayer[nCntPlayer].pos.y + 10.0f
				)
			{//�v���C���[����������(Z��)
				nCntHit = nCntPlayer;
			}
		}
	}
	return nCntHit;
}
//====================================================================
//�v���C���[�Ƃ̊O�ς̓����蔻��
//====================================================================
D3DXVECTOR3 CollisionOuterProductPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	//�ړ��x�N�g��������o��
	D3DXVECTOR3 vecMove = *pPos - *pPosOld;
	//���W�ۊǗp
	int nPosCount = 0;
	D3DXVECTOR3 pos[MAX_OBJECT00 * 4] = {};
	for (int nCnt = 0; nCnt < MAX_OBJECT00; nCnt++)
	{
		if (g_aPlayer[nCnt].bUse == true)
		{
			for (int nLine = 0; nLine < 4; nLine++)
			{
				bool bHit = false;
				bool bHit1 = false;
				bool bHit2 = false;

				D3DXVECTOR3 pos0, pos1;
				switch (nLine)
				{//���Ђ̓����蔻��
				case 0:
					pos0 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + -25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + 25.0f);
					pos1 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + 25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + 25.0f);
					break;
				case 1:
					pos0 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + 25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + 25.0f);
					pos1 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + 25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + -25.0f);
					break;
				case 2:
					pos0 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + 25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + -25.0f);
					pos1 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + -25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + -25.0f);
					break;
				case 3:
					pos0 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + -25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + -25.0f);
					pos1 = D3DXVECTOR3(g_aPlayer[nCnt].pos.x + -25.0f, g_aPlayer[nCnt].pos.y, g_aPlayer[nCnt].pos.z + 25.0f);
					break;
				default:
					break;
				}

				//�x�N�g���̖ڕW�n�_

				D3DXVECTOR3 vecLine = pos1 - pos0;

				D3DXVECTOR3 vecToPos = *pPos - pos0;

				D3DXVECTOR3 vecToPos2 = *pPosOld - pos0;

				float A, B, fRate;
				A = (vecToPos.z * vecMove.x) - (vecToPos.x * vecMove.z);
				B = (vecLine.z * vecMove.x) - (vecLine.x * vecMove.z);
				if (B != 0)
				{
					fRate = A / B;
				}
				else
				{
					fRate = 10.0f;
				}

				if (fRate >= 0.0f &&fRate <= 1.0f)
				{//vecLine�����؂����Ƃ�
					if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) < 0)
					{
						bHit1 = true;
					}

					if ((vecLine.z * vecToPos2.x) - (vecLine.x * vecToPos2.z) < 0)
					{
						bHit2 = true;
					}

					if (bHit1 != bHit2)
					{
						bHit = true;
					}

					bHit1 = false;
					bHit2 = false;

					if ((vecLine.z * vecToPos.x) + (vecLine.x * vecToPos.z) > 0)
					{
						bHit1 = true;
					}

					if ((vecLine.z * vecToPos2.x) + (vecLine.x * vecToPos2.z) > 0)
					{
						bHit2 = true;
					}

					if (bHit1 != bHit2)
					{
						bHit = true;
					}
				}
				if (bHit == true)
				{
					pos[nPosCount] = g_aPlayer[nCnt].pos;
					nPosCount++;
				}
			}
		}

	}
	if (nPosCount > 1)
	{
		for (int nCheck = 0; nCheck < nPosCount - 1; nCheck++)
		{//�����̍�������o���ď����Ƀ\�[�g

			for (int nCnt = (nCheck + 1); nCnt < nPosCount; nCnt++)
			{
				D3DXVECTOR3 Temp = pos[nCnt];
				float fDis1, fDis2;
				fDis1 = (pos[nCheck].x - pPosOld->x) + (pos[nCheck].z - pPosOld->z);
				fDis2 = (pos[nCnt].x - pPosOld->x) + (pos[nCnt].z - pPosOld->z);
				if (fDis1 < 0)
				{
					fDis1 *= -1.0f;
				}
				if (fDis2 < 0)
				{
					fDis2 *= -1.0f;
				}
				if (fDis1 > fDis2)
				{
					pos[nCnt] = pos[nCheck];
					pos[nCheck] = Temp;
				}
			}
		}
	}


	return pos[0];
}

//====================================================================
//�~�̓����蔻��
//====================================================================
bool CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn, float MinY, float MaxY)
{//������[pos1:����][pos2:����][nRadiusOut:�O���̔��a][nRadiusIn:�����̔��a][MinY:���̍���][MaxY:��̍���]
	bool nHit = false;

	if (sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.z - pos2.z) * (pos1.z - pos2.z)) <= nRadiusOut
		&& sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
			+ (pos1.z - pos2.z) * (pos1.z - pos2.z)) >= nRadiusIn
		&& pos1.y + MinY < pos2.y
		&& pos1.y + MaxY > pos2.y)
	{//�~�̔��肪��������
		nHit = true;
	}

	return nHit;
}

//====================================================================
//�v���C���[�̃q�b�g����
//====================================================================
void PlayerHit(int nCnt, int nDamage)
{
	if (g_aPlayer[nCnt].bUse == true && g_aPlayer[nCnt].State == PLAYER_NORMAL)
	{
		g_aPlayer[nCnt].nLife -= nDamage;

		if (g_aPlayer[nCnt].nLife > 0)
		{
			//�_���[�W��(���C�t���}�b�N�X���A2�̎�)
			PlaySound(SOUND_LABEL_SE_DAMAGE);
		}

		else
		{
			////�_���[�W��(���C�t��1�̎�)
			//PlaySound(SOUND_LABEL_SE_DAMAGE);
		}

		if (g_aPlayer[nCnt].nLife <= 0)
		{
			g_aPlayer[nCnt].nLife = 0;
		}

		//���C�t�̃Z�b�g����
		SetLife(nDamage, nCnt);

		if (g_aPlayer[nCnt].nLife <= 0)
		{
			g_aPlayer[nCnt].bUse = false;
			g_aPlayer[nCnt].State = PLAYER_DAMAGE;
			g_aPlayer[nCnt].nDamageCounter = PLAYER_DAMAGECOUNTER;
		}

		else
		{
			g_aPlayer[nCnt].State = PLAYER_HIT;
			g_aPlayer[nCnt].nHitCounter = PLAYER_HITCOUNTER;

			//�_���[�W��̃m�C�Y�̉�
			PlaySound(SOUND_LABEL_SE_NOIZE);
		}
		g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;
	}
}

//====================================================================
//�v���C���[�̕`�揈��
//====================================================================
void DrawPlayer(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
										//D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

										//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aPlayer[nCntPlayer].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nCntPlayer].rot.y, g_aPlayer[nCntPlayer].rot.x, g_aPlayer[nCntPlayer].rot.z);

		D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorld, &g_aPlayer[nCntPlayer].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);

		D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorld, &g_aPlayer[nCntPlayer].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nCntPlayer].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//�S���f��(�p�[�c)�̕`��
		//for (int nCntModel = 0; nCntModel < g_aPlayer[nCntPlayer].nNumModel; nCntModel++)
		//{

		//	//�}�e���A���f�[�^�ւ̃|�C���^����������
		//	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer[nCntModel]->GetBufferPointer();

		//	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
		//	{
		//		//�}�e���A���̐ݒ�
		//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//		//�e�N�X�`���̐ݒ�
		//		pDevice->SetTexture(0, g_pTexturePlayer[nCntMat]);

		//		if (g_aPlayer[nCntPlayer].bUse == true)
		//		{
		//			//�v���C���[(�p�[�c)�̕`��
		//			g_pMeshPlayer[nCntModel]->DrawSubset(nCntMat);
		//		}
		//	}
		//}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�������ԏI�����̏���
//====================================================================
void PlayerAllDown(void)
{
	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].bUse = false;
	}
}

//====================================================================
//�v���C���[���̏���
//====================================================================
Player * GetPlayer(void)
{
	return &g_aPlayer[0];
}