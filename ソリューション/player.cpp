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
#include "score_item.h"

#define PLAYER_STEALTHSPEED (1.0f)		//�v���C���[�̃X�e���X�X�s�[�h
#define PLAYER_SPEED (3.0f)				//�v���C���[�̃X�s�[�h
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

//====================================================================
//�v���C���[�̏���������
//====================================================================
void InitPlayer(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].pos = D3DXVECTOR3(nCntPlayer * 100.0f, 0.0f, -20.0f);
		g_aPlayer[nCntPlayer].posOld = D3DXVECTOR3(0.0f, 300.0f, -400.0f);
		g_aPlayer[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].State = PLAYER_NORMAL;
		g_aPlayer[nCntPlayer].MoveState = PLAYER_MOVESTATE_STEALTH;
		g_aPlayer[nCntPlayer].nLife = PLAYER_LIFE;
		g_aPlayer[nCntPlayer].bUse = true;

		g_SelectPlayer = 0;

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
	
	for (int nCntModel = 0; nCntModel < 1; nCntModel++)
	{
		//���b�V���̔j��
		if (g_pMeshPlayer[nCntModel] == NULL)
		{
			g_pMeshPlayer[nCntModel]->Release();
			g_pMeshPlayer[nCntModel] = NULL;
		}

		//�}�e���A���̔j��
		if (g_pBuffMatPlayer != NULL)
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
	if (GetKeyboardTrigger(DIK_F3) == true)
	{
		g_SelectPlayer++;
		if (g_SelectPlayer >= NUM_PLAYER)
		{
			g_SelectPlayer = 0;
		}
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

	//�v���C���[�̈ړ����͏���----------
	PlayerMoveInput(g_SelectPlayer);

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

	//�A�C�e���Ƃ̓����蔻��
	CollisionItem(&g_aPlayer[g_SelectPlayer].pos, &g_aPlayer[g_SelectPlayer].posOld, &g_aPlayer[g_SelectPlayer].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f);

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
	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		PrintDebugProc("�v���C���[%d�l�ڂ̍��W�yX : %f | Y : %f | Z : %f�z\n", nCntPlayer, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);
	}
	PrintDebugProc("���X�e�B�b�N�̏o�́y%f�z", GetGamepad_Stick_Left(0).y);
	PrintDebugProc("���X�e�B�b�N�̏o�́y%f�z", GetGamepad_Stick_Left(0).x);
}

//====================================================================
//�v���C���[�̈ړ����͏���
//====================================================================
void PlayerMoveInput(int nCnt)
{
	//�΂߈ړ��̑��x�C���p�̊֐�������������
	g_aPlayer[nCnt].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�L�[�{�[�h�̈ړ�����
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.z += 1.0f * cosf(Getrot().y);
		g_aPlayer[nCnt].NormarizeMove.x += 1.0f * sinf(Getrot().y);

	}
	if (GetKeyboardPress(DIK_G) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.z += -1.0f * cosf(Getrot().y);
		g_aPlayer[nCnt].NormarizeMove.x += -1.0f * sinf(Getrot().y);
	}
	if (GetKeyboardPress(DIK_F) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.x += -1.0f * cosf(Getrot().y);
		g_aPlayer[nCnt].NormarizeMove.z -= -1.0f * sinf(Getrot().y);

	}
	if (GetKeyboardPress(DIK_H) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.x += 1.0f * cosf(Getrot().y);
		g_aPlayer[nCnt].NormarizeMove.z -= 1.0f * sinf(Getrot().y);
	}

	if (GetKeyboardPress(DIK_T) == false && GetKeyboardPress(DIK_F) == false && GetKeyboardPress(DIK_G) == false && GetKeyboardPress(DIK_H) == false)
	{//�L�[�{�[�h�Ɠ����ɓ��͂ł��Ȃ��悤�ɂ���
		if (GetGamepad_Stick_Left(0).y > 0.0f)
		{//���X�e�B�b�N�̏����
			g_aPlayer[nCnt].NormarizeMove.z += cosf(Getrot().y);
			g_aPlayer[nCnt].NormarizeMove.x += sinf(Getrot().y);
		}
		if (GetGamepad_Stick_Left(0).y < 0.0f)
		{//���X�e�B�b�N�̉�����
			g_aPlayer[nCnt].NormarizeMove.z -= cosf(Getrot().y);
			g_aPlayer[nCnt].NormarizeMove.x -= sinf(Getrot().y);
		}
		if (GetGamepad_Stick_Left(0).x > 0.0f)
		{//���X�e�B�b�N�̉E����
			//���X�e�B�b�N�ɂ�鍶�E�ړ�
			g_aPlayer[nCnt].NormarizeMove.x += cosf(Getrot().y);
			g_aPlayer[nCnt].NormarizeMove.z -= sinf(Getrot().y);
		}
		if (GetGamepad_Stick_Left(0).x < 0.0f)
		{//���X�e�B�b�N�̍�����
			//���X�e�B�b�N�ɂ�鍶�E�ړ�
			g_aPlayer[nCnt].NormarizeMove.x -= cosf(Getrot().y);
			g_aPlayer[nCnt].NormarizeMove.z += sinf(Getrot().y);
		}
	}

	//�m�[�}���C�Y�ɂ���Ď΂߈ړ��̑��x���C������
	g_aPlayer[nCnt].NormarizeMove.y = 0.0f;

	D3DXVec3Normalize(&g_aPlayer[nCnt].NormarizeMove, &g_aPlayer[nCnt].NormarizeMove);

	//�L�[�{�[�h�̎��̑��x�ݒ�
	if (GetKeyboardPress(DIK_T) == true || GetKeyboardPress(DIK_F) == true || GetKeyboardPress(DIK_G) == true || GetKeyboardPress(DIK_H) == true)
	{
		g_aPlayer[nCnt].NormarizeMove.x *= PLAYER_SPEED;
		g_aPlayer[nCnt].NormarizeMove.z *= PLAYER_SPEED;
	}

	//���X�e�B�b�N�̑��x�����ƈړ��̎O�i�K�̎g����������
	if (fabsf(GetGamepad_Stick_Left(0).y) + fabsf(GetGamepad_Stick_Left(0).x) != 0 && GetGamepadPress(BUTTON_A, 0))
	{//���͂��Ă��Ԃ���A�{�^���������Ă���Ƃ�

		if (g_aPlayer[nCnt].MoveState != PLAYER_MOVESTATE_FATIGE)
		{//��J��ԈȊO�̂Ƃ�

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

	fRotMove = g_aPlayer[nCnt].rot.y;
	fRotDest = Getrot().y;

	if (GetKeyboardPress(DIK_E) == true)
	{
		g_aPlayer[nCnt].rot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_aPlayer[nCnt].rot.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_T) == true || GetGamepad_Stick_Left(0).y > 0.1f)
	{
		if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.25f;
		}
		else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.25f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y));
		}
	}
	else if (GetKeyboardPress(DIK_G) == true || GetGamepad_Stick_Left(0).y < -0.1f)
	{
		if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.75f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
	{
		fRotMove = atan2f(sinf(g_aPlayer[nCnt].rot.y), cosf(g_aPlayer[nCnt].rot.y));
		fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.5f;
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

	if (GetKeyboardPress(DIK_T) == true || GetKeyboardPress(DIK_F) == true || GetKeyboardPress(DIK_G) == true || GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).y != 0.0f || GetGamepad_Stick_Left(0).x != 0.0f)
	{
		g_aPlayer[nCnt].rot.y = fRotMove;
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻��
//====================================================================
void CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY)
{
	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
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
			PlayerHit(nCntPlayer,1);
		}
	}
}

//====================================================================
//�v���C���[�̃q�b�g����
//====================================================================
void PlayerHit(int nCnt,int nDamage)
{
	g_aPlayer[nCnt].nLife -= nDamage;

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

//====================================================================
//�v���C���[�̕`�揈��
//====================================================================
void DrawPlayer(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
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