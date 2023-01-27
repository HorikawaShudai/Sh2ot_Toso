#include "main.h"
#include "game.h"
#include "result.h"
#include "player.h"
#include "camera.h"
#include "object00.h"
#include "input.h"
#include "debugproc.h"
#include "fade.h"
#include "life.h"
#include "PlayNumberSelect.h"
#include "score_item.h"
#include "stamina.h"
#include "key.h"
#include "keyUI.h"
#include "exit.h"

//�}�N����`
#define PLAYER_STEALTHSPEED (0.5f)		//�v���C���[�̃X�e���X�X�s�[�h
#define PLAYER_SPEED (2.0f)				//�v���C���[�̃X�s�[�h
#define PLAYER_DASHSPEED (5.0f)				//�v���C���[�̃_�b�V���X�s�[�h
#define PLAYER_ROT_SPEED (0.2f)			//�v���C���[�̉�]�X�s�[�h
#define PLAYER_JUMP (12.0f)				//�v���C���[�̃W�����v��
#define PLAYER_LIFE (3)					//�v���C���[�̏������C�t
#define PLAYER_COLLISIONSIZE (15.0f)	//�v���C���[�̓����蔻��̑傫��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer[100] = {};	//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshPlayer[32] = {};				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer[32] = {};			//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0;						//�}�e���A���̐�
Player g_aPlayer[NUM_PLAYER];					//�v���C���[�̏��
int g_nIndexPlayerShadow = -1;					//�e�̃C���f�b�N�X(�ԍ�)
int g_SelectPlayer;								//���삷��v���C���[
bool g_bPlayerOps;

//====================================================================
//�v���C���[�̏���������
//====================================================================
void InitPlayer(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

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

		g_SelectPlayer = 0;
		g_bPlayerOps = false;
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
	}
}

//====================================================================
//�v���C���[�̍X�V����
//====================================================================
void UpdatePlayer(void)
{
	//�|�C���^���̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	int CurrentCamera = GetCurrentCamera();

	/*if (GetKeyboardTrigger(DIK_F3) == true)
	{
		g_SelectPlayer = CurrentCamera;

		if (g_SelectPlayer >= PlayNumber.CurrentSelectNumber)
		{
			g_SelectPlayer = 0;
		}
	}*/

	//�J�����ԍ����v���C���[�ɑ��
	g_SelectPlayer = CurrentCamera;

	if (GetKeyboardTrigger(DIK_F6) == true)
	{
		GetGamepad_Left_Vibrtion(0);
	}
	if (GetKeyboardTrigger(DIK_F7) == true)
	{
		GetGamepad_Left_Vibrtion_false(0);
	}

	//�v���C���[�̏��
	switch (g_aPlayer[g_SelectPlayer].State)
	{
	case PLAYER_NORMAL:
		break;

	case PLAYER_WAIT:
		g_aPlayer[g_SelectPlayer].nWaitCounter--;
		if (g_aPlayer[g_SelectPlayer].nWaitCounter < 0)
		{
			g_aPlayer[g_SelectPlayer].State = PLAYER_NORMAL;
		}
		break;

	case PLAYER_DAMAGE:
		g_aPlayer[g_SelectPlayer].nDamageCounter--;
		if (g_aPlayer[g_SelectPlayer].nDamageCounter < 0)
		{
			g_aPlayer[g_SelectPlayer].State = PLAYER_WAIT;
		}
		break;

	case PLAYER_HIT:
		g_aPlayer[g_SelectPlayer].nHitCounter--;
		if (g_aPlayer[g_SelectPlayer].nHitCounter < 0)
		{
			g_aPlayer[g_SelectPlayer].State = PLAYER_DAMAGE;
		}
		break;
	}

	g_aPlayer[g_SelectPlayer].posOld = g_aPlayer[g_SelectPlayer].pos;

	//�����W��
	g_aPlayer[g_SelectPlayer].move.x = g_aPlayer[g_SelectPlayer].move.x * 0.5f;
	g_aPlayer[g_SelectPlayer].move.z = g_aPlayer[g_SelectPlayer].move.z * 0.5f;

	//�l�̐؂�̂�
	if (g_aPlayer[g_SelectPlayer].move.x <= 0.005f && g_aPlayer[g_SelectPlayer].move.x >= -0.005f)
	{
		g_aPlayer[g_SelectPlayer].move.x = 0.0f;
	}
	if (g_aPlayer[g_SelectPlayer].move.z <= 0.005f && g_aPlayer[g_SelectPlayer].move.z >= -0.005f)
	{
		g_aPlayer[g_SelectPlayer].move.z = 0.0f;
	}

	//�d�͂̒ǉ�
	g_aPlayer[g_SelectPlayer].move.y -= 10.0f;

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F5) == true)
	{//�L�[�������ꂽ�ꍇ
		g_bPlayerOps = g_bPlayerOps ? false : true;			//�ώ@�p���[�h�ɕύX
	}
#endif

	if (g_bPlayerOps == false)
	{
		//�v���C���[�̈ړ����͏���----------
		PlayerMoveInput(g_SelectPlayer);
	}

	//�ʒu�X�V(���͂ɂ�铮��)
	g_aPlayer[g_SelectPlayer].pos += g_aPlayer[g_SelectPlayer].move;

	//���̒ǉ�
	if (g_aPlayer[g_SelectPlayer].pos.y < 0.0f)
	{//���ɂӂꂽ�Ƃ�
		g_aPlayer[g_SelectPlayer].pos.y = 0.0f;	//���̏�ɖ߂�
		g_aPlayer[g_SelectPlayer].move.y = 0.0f;	//
	}

	//�ړ����Ƀv���C���[�̌�����␳����----------
	PlayerRotUpdate(g_SelectPlayer);

	//�I�u�W�F�N�g�Ƃ̓����蔻��
	CollisionObject00(&g_aPlayer[g_SelectPlayer].pos, &g_aPlayer[g_SelectPlayer].posOld, &g_aPlayer[g_SelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);

	CollisionItem(&g_aPlayer[g_SelectPlayer].pos, &g_aPlayer[g_SelectPlayer].posOld, &g_aPlayer[g_SelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f, g_SelectPlayer);

	//���̓��菈��
	if (g_aPlayer[g_SelectPlayer].bGetKey == false)
	{//�v���C���[�����������Ă��Ȃ��ꍇ
		if (GetKeyboardTrigger(DIK_E) == true)
		{//E�L�[����
			if (CollisionKey(&g_aPlayer[g_SelectPlayer].pos, &g_aPlayer[g_SelectPlayer].posOld, &g_aPlayer[g_SelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, g_SelectPlayer) == true)
			{//�������o�����ꍇ
				g_aPlayer[g_SelectPlayer].bGetKey = true;	//��������Ԃɂ���
				SetKeyUI(g_SelectPlayer, true);				//��UI��\������
			}
		}
	}

	//�E�o����
	if (g_aPlayer[g_SelectPlayer].bGetKey == true)
	{//�v���C���[�����������Ă���ꍇ
		if (GetKeyboardTrigger(DIK_E) == true)
		{//E�L�[����
			if (CollisionExit(&g_aPlayer[g_SelectPlayer].pos, &g_aPlayer[g_SelectPlayer].posOld, &g_aPlayer[g_SelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 30.0f, g_SelectPlayer) == true)
			{//�������o�����ꍇ
				g_aPlayer[g_SelectPlayer].bGetKey = false;	//������肵�ĂȂ���Ԃɂ���
				SetKeyUI(g_SelectPlayer, false);			//��UI���\���ɂ���
			}
		}
	}

	//����������̌����̕␳
	if (g_aPlayer[g_SelectPlayer].rot.y > D3DX_PI * 1.0f)
	{
		g_aPlayer[g_SelectPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_aPlayer[g_SelectPlayer].rot.y < -D3DX_PI * 1.0f)
	{
		g_aPlayer[g_SelectPlayer].rot.y += D3DX_PI * 2.0f;
	}

	//�̗͂����邩�ǂ����e�X�g�p
	if (GetKeyboardTrigger(DIK_M) == true)
	{
		PlayerHit(g_SelectPlayer, 1);
	}

	PrintDebugProc("�yF3�z�Ńv���C���[�؂�ւ��F�y�v���C���[%d�z\n", g_SelectPlayer + 1);
	for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
	{
		PrintDebugProc("�v���C���[%d�l�ڂ̍��W�yX : %f | Y : %f | Z : %f�z\n", nCntPlayer, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);
		PrintDebugProc("�v���C���[%d�l�ڂ̈ړ��ʁyX : %f | Y : %f | Z : %f�z\n", nCntPlayer, g_aPlayer[nCntPlayer].move.x, g_aPlayer[nCntPlayer].move.y, g_aPlayer[nCntPlayer].move.z);
	}
	PrintDebugProc("���X�e�B�b�N�̏o�́y%f�z", GetGamepad_Stick_Left(0).y);
	PrintDebugProc("���X�e�B�b�N�̏o�́y%f�z", GetGamepad_Stick_Left(0).x);
	PrintDebugProc("�E�X�e�B�b�N�̏o�́y%f�z", GetGamepad_Stick_Right(0).y);
	PrintDebugProc("�E�X�e�B�b�N�̏o�́y%f�z", GetGamepad_Stick_Right(0).x);
}

//====================================================================
//�v���C���[�̈ړ����͏���
//====================================================================
void PlayerMoveInput(int nCnt)
{
	//���̎擾
	Stamina *pStamina = GetStamina();
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	int CurrentCamera = GetCurrentCamera();

	//�΂߈ړ��̑��x�C���p�̊֐�������������
	g_aPlayer[nCnt].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		}
		if (GetGamepad_Stick_Left(0).y < 0.0f)
		{//���X�e�B�b�N�̉�����
			g_aPlayer[nCnt].NormarizeMove.z -= cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.x -= sinf(Getrot(CurrentCamera).y);
		}
		if (GetGamepad_Stick_Left(0).x > 0.0f)
		{//���X�e�B�b�N�̉E����
			//���X�e�B�b�N�ɂ�鍶�E�ړ�
			g_aPlayer[nCnt].NormarizeMove.x += cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.z -= sinf(Getrot(CurrentCamera).y);
		}
		if (GetGamepad_Stick_Left(0).x < 0.0f)
		{//���X�e�B�b�N�̍�����
			//���X�e�B�b�N�ɂ�鍶�E�ړ�
			g_aPlayer[nCnt].NormarizeMove.x -= cosf(Getrot(CurrentCamera).y);
			g_aPlayer[nCnt].NormarizeMove.z += sinf(Getrot(CurrentCamera).y);
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
	if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) != 0 && GetGamepadPress(BUTTON_R, 0))
	{//���͂��Ă��Ԃ���A�{�^���������Ă���Ƃ�
		if (pStamina[nCnt].bFatige == false)			//�v���C���[��������Ԃ��ǂ���
		{//��J��Ԃł͂Ȃ������ꍇ

 			g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_DASHSPEED;
			g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_DASHSPEED;

			//�v���C���[���_�b�V����Ԃɂ���
			g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_DASH;
		}
	}
	else if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) < 0.95f)
	{//���X�e�B�b�N��|���؂��Ă��Ȃ���Ԃ̂Ƃ�

		g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_STEALTHSPEED;
		g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_STEALTHSPEED;

	g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;

		//�v���C���[���X�e���X��Ԃɂ���
		g_aPlayer[nCnt].MoveState = PLAYER_MOVESTATE_STEALTH;
	}
	else if(fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) != 0)
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

	g_aPlayer[nCnt].move += g_aPlayer[nCnt].NormarizeMove;
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
			{//�e�ƃv���C���[����������(Z��)
				nCntHit = nCntPlayer;
			}
		}
	}
	return nCntHit;
}

//====================================================================
//�v���C���[�̃q�b�g����
//====================================================================
void PlayerHit(int nCnt,int nDamage)
{
	if (g_aPlayer[nCnt].bUse == true)
	{
		g_aPlayer[nCnt].nLife -= nDamage;

		if (g_aPlayer[nCnt].nLife <= 0)
		{
			g_aPlayer[nCnt].nLife = 0;
		}

		//���C�t�̃Z�b�g����
		SetLife(g_aPlayer[nCnt].nLife, nCnt);

		if (g_aPlayer[nCnt].nLife <= 0)
		{
			g_aPlayer[nCnt].bUse = false;

		}

		else
		{
			g_aPlayer[nCnt].State = PLAYER_HIT;
		}
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
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

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
		for (int nCntModel = 0; nCntModel < g_aPlayer[nCntPlayer].nNumModel; nCntModel++)
		{

			//�}�e���A���f�[�^�ւ̃|�C���^����������
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayer[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturePlayer[nCntMat]);

				if (g_aPlayer[nCntPlayer].bUse == true)
				{
					//�v���C���[(�p�[�c)�̕`��
					g_pMeshPlayer[nCntModel]->DrawSubset(nCntMat);
				}
			}
		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�v���C���[���̏���
//====================================================================
Player * GetPlayer(void)
{
	return &g_aPlayer[0];
}