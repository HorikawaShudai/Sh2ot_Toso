//========================================================================================
//
// �w�i�p�v���C���[�̏���[playerBG.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "main.h"
#include "game.h"
#include "result.h"
#include "playerBG.h"
#include "camera.h"
#include "billboard.h"
#include "object00.h"
#include "particle.h"
#include "input.h"
#include "debugproc.h"
#include "fade.h"
#include "PlayNumberSelect.h"
#include <stdio.h>

#define PLAYERBG_SPEED (3.25f)			//�v���C���[�̃X�s�[�h
#define PLAYERBG_ROT_SPEED (0.2f)		//�v���C���[�̉�]�X�s�[�h
#define PLAYERBG_JUMP (12.0f)			//�v���C���[�̃W�����v��
#define PLAYERBG_LIFE (3)				//�v���C���[�̏������C�t
#define PLAYERBG_COLLISIONSIZE (15.0f)	//�v���C���[�̓����蔻��̑傫��
#define MAX_PLAYREBG (4)			//�w�i�Ɏg���v���C���[�̍ő吔

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshPlayerBG[32] = {};				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayerBG[32] = {};			//�}�e���A���ւ̃|�C���^
PlayerBG g_PlayerBG[MAX_PLAYREBG];					//�v���C���[�̏��
int g_nIndexPlayerBGShadow = -1;					//�e�̃C���f�b�N�X(�ԍ�)

const char *c_apPlayerBG[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\player\\00_body_murabito.x",
	"Data\\MODEL\\player\\01_head_murabito.x",
	"Data\\MODEL\\player\\02_shoulderL_murabito.x",
	"Data\\MODEL\\player\\03_armL_murabito.x",
	"Data\\MODEL\\player\\06_handL_murabito.x",
	"Data\\MODEL\\player\\04_legL_murabito.x",
	"Data\\MODEL\\player\\05_footL_murabito.x",
	"Data\\MODEL\\player\\07_shoesL_murabito.x",
	"Data\\MODEL\\player\\08_shoulderR_murabito.x",
	"Data\\MODEL\\player\\09_armR_murabito.x",
	"Data\\MODEL\\player\\12_handR_murabito.x",
	"Data\\MODEL\\player\\10_legR_murabito.x",
	"Data\\MODEL\\player\\11_footR_murabito.x",
	"Data\\MODEL\\player\\13_shoesR_murabito.x"
};

//====================================================================
//�v���C���[�̏���������
//====================================================================
void InitPlayerBG(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntPlayerBG = 0; nCntPlayerBG < MAX_PLAYREBG; nCntPlayerBG++)
	{
		g_PlayerBG[nCntPlayerBG].pos = D3DXVECTOR3(-60.0f + nCntPlayerBG * 40.0f, 0.0f, 100.0f);
		g_PlayerBG[nCntPlayerBG].posOld = g_PlayerBG[nCntPlayerBG].pos;
		g_PlayerBG[nCntPlayerBG].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PlayerBG[nCntPlayerBG].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PlayerBG[nCntPlayerBG].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PlayerBG[nCntPlayerBG].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_PlayerBG[nCntPlayerBG].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_PlayerBG[nCntPlayerBG].g_bMotion = true;

		switch (nCntPlayerBG)
		{
		case 0:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_WAIT;
			SetMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		case 1:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_MOVE;
			SetMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		case 2:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_JUMP;
			SetMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		case 3:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_MOVE;
			SetMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		}

		g_PlayerBG[nCntPlayerBG].nLife = PLAYERBG_LIFE;
		g_PlayerBG[nCntPlayerBG].bJump = false;
		g_PlayerBG[nCntPlayerBG].bUse = true;

		g_PlayerBG[nCntPlayerBG].g_nNextKey = 1;

		//�O���t�@�C������L�����N�^�[����ǂݍ��ޏ���
		LoadMotion(nCntPlayerBG);

		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(c_apPlayerBG[nCntModel],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatPlayerBG[nCntModel],
				NULL,
				&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG,
				&g_pMeshPlayerBG[nCntModel]);


			//�}�e���A�����ɑ΂���|�C���^������
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayerBG[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat]);
				}
			}
		}
	}
}

//====================================================================
//�v���C���[�̏I������
//====================================================================
void UninitPlayerBG(void)
{
	for (int nCntPlayerBG = 0; nCntPlayerBG < MAX_PLAYREBG; nCntPlayerBG++)
	{
		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			for (int nCntMat = 0; nCntMat < (int)g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG; nCntMat++)
			{
				//�e�N�X�`���̔j��
				if (g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat] != NULL)
				{
					g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat]->Release();
					g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat] = NULL;
				}
			}
		}

		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			//���b�V���̔j��
			if (g_pMeshPlayerBG[nCntModel] != NULL)
			{
				g_pMeshPlayerBG[nCntModel]->Release();
				g_pMeshPlayerBG[nCntModel] = NULL;
			}

			//�}�e���A���̔j��
			if (g_pBuffMatPlayerBG[nCntModel] != NULL)
			{
				g_pBuffMatPlayerBG[nCntModel]->Release();
				g_pBuffMatPlayerBG[nCntModel] = NULL;
			}
		}
	}
}

//====================================================================
//�v���C���[�̍X�V����
//====================================================================
void UpdatePlayerBG(void)
{
	PlayNumberSelect nPlayerNumber = GetPlayNumberSelect();

	for (int nCntPlayerBG = 0; nCntPlayerBG < MAX_PLAYREBG; nCntPlayerBG++)
	{
		g_PlayerBG[nCntPlayerBG].bUse = false;
	}
	for (int nCntPlayerBG = 0; nCntPlayerBG <= nPlayerNumber.CurrentSelectNumber; nCntPlayerBG++)
	{
		g_PlayerBG[nCntPlayerBG].bUse = true;
	}


	for (int nCntPlayerBG = 0; nCntPlayerBG < MAX_PLAYREBG; nCntPlayerBG++)
	{
		g_PlayerBG[nCntPlayerBG].posOld = g_PlayerBG[nCntPlayerBG].pos;

		//�����W��
		g_PlayerBG[nCntPlayerBG].move.x = g_PlayerBG[nCntPlayerBG].move.x * 0.5f;
		g_PlayerBG[nCntPlayerBG].move.z = g_PlayerBG[nCntPlayerBG].move.z * 0.5f;

		//�l�̐؂�̂�
		if (g_PlayerBG[nCntPlayerBG].move.x <= 0.005f && g_PlayerBG[nCntPlayerBG].move.x >= -0.005f)
		{
			g_PlayerBG[nCntPlayerBG].move.x = 0.0f;
		}
		if (g_PlayerBG[nCntPlayerBG].move.z <= 0.005f && g_PlayerBG[nCntPlayerBG].move.z >= -0.005f)
		{
			g_PlayerBG[nCntPlayerBG].move.z = 0.0f;
		}

		////�v���C���[�̈ړ����͏���
		//PlayerBGMoveInput(nCntPlayerBG);

		//�W�����v����
		if (g_PlayerBG[nCntPlayerBG].bJump == false)
		{//�W�����v�����Ă��Ȃ��Ƃ�
			if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
			{//�W�����v�{�^�����͎�
				g_PlayerBG[nCntPlayerBG].move.y = PLAYERBG_JUMP;	//�W�����v����
				g_PlayerBG[nCntPlayerBG].bJump = true;			//�W�����v���g�p���Ă����Ԃɂ���
			}
		}
		else
		{
		}

		//�ʒu�X�V(���͂ɂ�铮��)
		g_PlayerBG[nCntPlayerBG].pos += g_PlayerBG[nCntPlayerBG].move;

		//���̒ǉ�
		if (g_PlayerBG[nCntPlayerBG].pos.y < 0.0f)
		{//���ɂӂꂽ�Ƃ�
			g_PlayerBG[nCntPlayerBG].pos.y = 0.0f;	//���̏�ɖ߂�
			g_PlayerBG[nCntPlayerBG].move.y = 0.0f;	//

			if (g_PlayerBG[nCntPlayerBG].bJump == true)
			{
				g_PlayerBG[nCntPlayerBG].bJump = false;	//�W�����v���g�p���Ă��Ȃ���Ԃɂ���
			}
		}

		//��葬�x�ȏ�ŗ������Ă��鎞�ɃW�����v���o���Ȃ���Ԃɂ���
		if (g_PlayerBG[nCntPlayerBG].move.y < 0.0f)
		{
			if (g_PlayerBG[nCntPlayerBG].bJump == false)
			{
				g_PlayerBG[nCntPlayerBG].bJump = true;			//�W�����v���g�p���Ă����Ԃɂ���
			}
		}

		////�ړ����Ƀv���C���[�̌�����␳����
		//PlayerBGRotUpdate(nCntPlayerBG);

		////�I�u�W�F�N�g�Ƃ̓����蔻��
		//if (CollisionObject00(&g_PlayerBG[nCntPlayerBG].pos, &g_PlayerBG[nCntPlayerBG].posOld, &g_PlayerBG[nCntPlayerBG].move, g_PlayerBG[nCntPlayerBG].vtxMin, g_PlayerBG[nCntPlayerBG].vtxMax, 20.0f) == false)
		//{
		//	if (g_PlayerBG[nCntPlayerBG].bJump == true)
		//	{
		//		g_PlayerBG[nCntPlayerBG].bJump = false;	//�W�����v���g�p���Ă��Ȃ���Ԃɂ���
		//	}
		//}

		////����������̌����̕␳
		//if (g_PlayerBG[nCntPlayerBG].rot.y > D3DX_PI * 1.0f)
		//{
		//	g_PlayerBG[nCntPlayerBG].rot.y -= D3DX_PI * 2.0f;
		//}
		//else if (g_PlayerBG[nCntPlayerBG].rot.y < -D3DX_PI * 1.0f)
		//{
		//	g_PlayerBG[nCntPlayerBG].rot.y += D3DX_PI * 2.0f;
		//}

		UpdateMotion(nCntPlayerBG);

		PrintDebugProc("%f %f %f\n", g_PlayerBG[nCntPlayerBG].pos.x, g_PlayerBG[nCntPlayerBG].pos.y, g_PlayerBG[nCntPlayerBG].pos.z);
	}
}

//====================================================================
//���[�V�����̍X�V����
//====================================================================
void UpdateMotion(int nCnt)
{
	g_PlayerBG[nCnt].nNumkey = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].NumKey;

	//�S���f��(�p�[�c)�̍X�V
	for (int nCntModel = 0; nCntModel < g_PlayerBG[nCnt].nNumModel; nCntModel++)
	{
		//�L�[�̏�񂩂�ʒu�E�������Z�o
		float POSX = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fPosX - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosX;
		float POSY = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fPosY - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosY;
		float POSZ = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fPosZ - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosZ;
		float ROTX = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fRotX - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotX;
		float ROTY = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fRotY - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotY;
		float ROTZ = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fRotZ - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotZ;

		//�p�[�c�̈ʒu�E������ݒ�
		g_PlayerBG[nCnt].aModel[nCntModel].pos.x = g_PlayerBG[nCnt].aModel[nCntModel].Setpos.x + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosX + POSX * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
		g_PlayerBG[nCnt].aModel[nCntModel].pos.y = g_PlayerBG[nCnt].aModel[nCntModel].Setpos.y + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosY + POSY * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
		g_PlayerBG[nCnt].aModel[nCntModel].pos.z = g_PlayerBG[nCnt].aModel[nCntModel].Setpos.z + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosZ + POSZ * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
		g_PlayerBG[nCnt].aModel[nCntModel].rot.x = g_PlayerBG[nCnt].aModel[nCntModel].Setrot.x + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotX + ROTX * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
		g_PlayerBG[nCnt].aModel[nCntModel].rot.y = g_PlayerBG[nCnt].aModel[nCntModel].Setrot.y + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotY + ROTY * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
		g_PlayerBG[nCnt].aModel[nCntModel].rot.z = g_PlayerBG[nCnt].aModel[nCntModel].Setrot.z + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotZ + ROTZ * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
	}
	g_PlayerBG[nCnt].nCounterMotion++;
	if (g_PlayerBG[nCnt].nCounterMotion >= g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame)
	{
		g_PlayerBG[nCnt].nCounterMotion = 0;
		g_PlayerBG[nCnt].nkey++;
		g_PlayerBG[nCnt].g_nNextKey++;

		if (g_PlayerBG[nCnt].g_nNextKey >= g_PlayerBG[nCnt].nNumkey)
		{
			if (g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].bLoop == true)
			{
				g_PlayerBG[nCnt].g_nNextKey = 0;
			}
			else
			{
				g_PlayerBG[nCnt].g_nNextKey = 0;
			}
		}
		if (g_PlayerBG[nCnt].nkey >= g_PlayerBG[nCnt].nNumkey)
		{
			if (g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].bLoop == true)
			{
				g_PlayerBG[nCnt].nkey = 0;
			}
			else
			{
				g_PlayerBG[nCnt].nkey = 0;
			}
		}
	}
}

//====================================================================
//���[�V�����̐ݒ菈��
//====================================================================
void SetMotion(MOTION_TYPE nType, int nCnt)
{
	if (g_PlayerBG[nCnt].g_bMotion == true)
	{
		g_PlayerBG[nCnt].bLoopMotion = g_PlayerBG[nCnt].aMotionInfo[nType].bLoop;	//���[�v���邩�ǂ���
		g_PlayerBG[nCnt].nNumkey = g_PlayerBG[nCnt].aMotionInfo[nType].NumKey;		//�L�[�̑���
		g_PlayerBG[nCnt].nkey = 0;											//���݂̃L�[No.
		g_PlayerBG[nCnt].nCounterMotion = 0;								//���[�V�����̃J�E���^�[
		g_PlayerBG[nCnt].g_nNextKey = g_PlayerBG[nCnt].nkey + 1;
		g_PlayerBG[nCnt].g_bMotion = false;
	}
}

//====================================================================
//�u���b�N�̃��[�h����
//====================================================================
void LoadMotion(int nPlayerBG)
{
	PlayerBG * pPlayerBG = GetPlayerBG();		//�v���C���[�̏��ւ̃|�C���^
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen("", "r");

	//�t�@�C�����J��
	pFile = fopen("data\\TEXT\\murabito.txt", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		int nCntModel = 0;
		int nCntParts = 0;
		int nCntMotion = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;

		char aString[128] = {};				//�S�~��
		char aStartMessage[128] = {};		//�X�^�[�g���b�Z�[�W
		char aModelMessage[128] = {};		//���f���p���b�Z�[�W
		char aCharaSetMessage[128] = {};	//�L�����Z�b�g���b�Z�[�W
		char aPartsSetMessage[128] = {};	//�p�[�c�Z�b�g���b�Z�[�W
		char aMotionSetMessage[128] = {};	//���[�V�����Z�b�g���b�Z�[�W
		char KeySetMessage[128] = {};		//�L�[�Z�b�g���b�Z�[�W
		char KeyStartMessage[128] = {};		//�L�[�X�^�[�g���b�Z�[�W
		char aNameMessage[128] = {};		//�ϐ����̃��b�Z�[�W
		char aPartsEndMessage[128] = {};	//�p�[�c�G���h���b�Z�[�W
		char aCharaEndMessage[128] = {};	//�L�����G���h���b�Z�[�W
		char aEndMessage[128] = {};			//�I�����b�Z�[�W
		char aType[128] = {};				//�I�����b�Z�[�W
		char aBool[128] = {};				//bool�ϊ��p���b�Z�[�W

											// �ǂݍ��݊J�n-----------------------------------------------------
		while (1)
		{//�uSCRIPT�v��T��
			fscanf(pFile, "%s", &aStartMessage[0]);
			if (strcmp(&aStartMessage[0], "SCRIPT") == 0)
			{
				// ���f�����ǂݍ���-----------------------------------------------------
				while (1)
				{//�uNUM_MODEL�v��T��
					fscanf(pFile, "%s", &aModelMessage[0]);
					if (strcmp(&aModelMessage[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_PlayerBG[nPlayerBG].nNumModel);		//���f�����̐ݒ�
						break;
					}
				}

				// �L�����N�^�[���ǂݍ���-----------------------------------------------------
				while (1)
				{//�uPARTSSET�v��T��
					fscanf(pFile, "%s", &aPartsSetMessage[0]);
					if (strcmp(&aPartsSetMessage[0], "PARTSSET") == 0)
					{
						while (1)
						{//�e��ϐ���T��
							fscanf(pFile, "%s", &aNameMessage[0]);
							if (strcmp(&aNameMessage[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &nCntModel);	//�C���f�b�N�X��ݒ�
							}
							if (strcmp(&aNameMessage[0], "PARENT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_PlayerBG[nPlayerBG].aModel[nCntModel].nIndexModelParent);	//�e���f���̃C���f�b�N�X��ݒ�
							}
							if (strcmp(&aNameMessage[0], "POS") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setpos.x);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setpos.y);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setpos.z);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
							}
							if (strcmp(&aNameMessage[0], "ROT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setrot.x);				////�����̏����ݒ�
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setrot.y);				////�����̏����ݒ�
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setrot.z);				////�����̏����ݒ�
							}
							if (strcmp(&aNameMessage[0], "END_PARTSSET") == 0)
							{
								break;
							}
						}
						nCntModel++;
						if (nCntModel >= g_PlayerBG[nPlayerBG].nNumModel)
						{
							break;
						}
					}
				}

				// ���[�V�������ǂݍ���-----------------------------------------------------
				while (1)
				{//�uMOTIONSET�v��T��
					fscanf(pFile, "%s", &aMotionSetMessage[0]);
					if (strcmp(&aMotionSetMessage[0], "MOTIONSET") == 0)
					{
						while (1)
						{//�e��ϐ���T��
							fscanf(pFile, "%s", &aNameMessage[0]);
							if (strcmp(&aNameMessage[0], "LOOP") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%s", &aBool[0]);	//���[�v���邩�ǂ�����ݒ�
								g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].bLoop = (strcmp(&aBool[0], "1") == 0 ? true : false);			//bool�^�̏�����
							}
							if (strcmp(&aNameMessage[0], "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].NumKey);	//�L�[�̑�����ݒ�
								break;
							}
						}

						// �L�[���ǂݍ���-----------------------------------------------------
						while (1)
						{//�uKEYSET�v��T��
							fscanf(pFile, "%s", &KeySetMessage[0]);
							if (strcmp(&KeySetMessage[0], "KEYSET") == 0)
							{
								while (1)
								{//�uFRAME�v��T��
									fscanf(pFile, "%s", &aNameMessage[0]);
									if (strcmp(&aNameMessage[0], "FRAME") == 0)
									{
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].nFrame);	//�L�[�t���[����ݒ�
										break;
									}
								}

								while (1)
								{//�uKEY�v��T��
									fscanf(pFile, "%s", &KeyStartMessage[0]);
									if (strcmp(&KeyStartMessage[0], "KEY") == 0)
									{
										while (1)
										{//�e��ϐ���T��
											fscanf(pFile, "%s", &aNameMessage[0]);
											if (strcmp(&aNameMessage[0], "POS") == 0)
											{
												fscanf(pFile, "%s", &aString[0]);
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fPosX);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fPosY);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fPosZ);	//�ʒu��ݒ�
											}
											if (strcmp(&aNameMessage[0], "ROT") == 0)
											{
												fscanf(pFile, "%s", &aString[0]);
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fRotX);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fRotY);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fRotZ);	//�ʒu��ݒ�
												break;
											}
										}
									}
									if (strcmp(&KeyStartMessage[0], "END_KEY") == 0)
									{
										nCntKey++;
										if (nCntKey >= g_PlayerBG[nPlayerBG].nNumModel)
										{
											break;
										}
									}
								}
							}
							if (strcmp(&KeySetMessage[0], "END_KEYSET") == 0)
							{
								nCntKey = 0;
								nCntKeySet++;
								if (nCntKeySet >= g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].NumKey)
								{
									break;
								}
							}
						}
					}
					if (strcmp(&aMotionSetMessage[0], "END_MOTIONSET") == 0)
					{
						nCntKeySet = 0;
						nCntMotion++;
						if (nCntMotion >= PLAYERBG_ACTION_MAX)
						{
							break;
						}
					}
				}
			}
			if (strcmp(&aStartMessage[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}

//====================================================================
//�v���C���[�̈ړ����͏���
//====================================================================
void PlayerBGMoveInput(int nCnt)
{
	g_PlayerBG[nCnt].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�L�[�{�[�h�̈ړ�����
	if (GetKeyboardPress(DIK_W) == true)
	{
		g_PlayerBG[nCnt].NormarizeMove.z += 1.0f * cosf(Getrot(4).y) * PLAYERBG_SPEED;
		g_PlayerBG[nCnt].NormarizeMove.x += 1.0f * sinf(Getrot(4).y) * PLAYERBG_SPEED;

	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_PlayerBG[nCnt].NormarizeMove.z += -1.0f * cosf(Getrot(4).y) * PLAYERBG_SPEED;
		g_PlayerBG[nCnt].NormarizeMove.x += -1.0f * sinf(Getrot(4).y) * PLAYERBG_SPEED;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_PlayerBG[nCnt].NormarizeMove.x += -1.0f * cosf(Getrot(4).y) * PLAYERBG_SPEED;
		g_PlayerBG[nCnt].NormarizeMove.z -= -1.0f * sinf(Getrot(4).y) * PLAYERBG_SPEED;

	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_PlayerBG[nCnt].NormarizeMove.x += 1.0f * cosf(Getrot(4).y) * PLAYERBG_SPEED;
		g_PlayerBG[nCnt].NormarizeMove.z -= 1.0f * sinf(Getrot(4).y) * PLAYERBG_SPEED;
	}

	if (GetKeyboardPress(DIK_W) == false && GetKeyboardPress(DIK_A) == false && GetKeyboardPress(DIK_S) == false && GetKeyboardPress(DIK_D) == false)
	{
		//���X�e�B�b�N�ɂ��O��ړ�	
		g_PlayerBG[nCnt].move.z += GetGamepad_Stick_Left(0).y * cosf(Getrot(4).y) * PLAYERBG_SPEED;
		g_PlayerBG[nCnt].move.x += GetGamepad_Stick_Left(0).y * sinf(Getrot(4).y) * PLAYERBG_SPEED;

		//���X�e�B�b�N�ɂ�鍶�E�ړ�
		g_PlayerBG[nCnt].move.x += GetGamepad_Stick_Left(0).x * cosf(Getrot(4).y) * PLAYERBG_SPEED;
		g_PlayerBG[nCnt].move.z -= GetGamepad_Stick_Left(0).x * sinf(Getrot(4).y) * PLAYERBG_SPEED;
	}

	if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_D) == true)
	{
		g_PlayerBG[nCnt].NormarizeMove.y = 0.0f;

		D3DXVec3Normalize(&g_PlayerBG[nCnt].NormarizeMove, &g_PlayerBG[nCnt].NormarizeMove);

		g_PlayerBG[nCnt].NormarizeMove.x *= PLAYERBG_SPEED;
		g_PlayerBG[nCnt].NormarizeMove.z *= PLAYERBG_SPEED;
	}

	g_PlayerBG[nCnt].move += g_PlayerBG[nCnt].NormarizeMove;
}

//====================================================================
//�v���C���[�̌����̕␳
//====================================================================
void PlayerBGRotUpdate(int nCnt)
{
	//�ړ������Ɍ��������킹�鏈��
	float fRotMove, fRotDest, fRotDiff;

	fRotMove = g_PlayerBG[nCnt].rot.y;
	fRotDest = Getrot(4).y;

	if (GetKeyboardPress(DIK_E) == true)
	{
		g_PlayerBG[nCnt].rot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_PlayerBG[nCnt].rot.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_W) == true || GetGamepad_Stick_Left(0).y > 0.1f)
	{
		if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_PlayerBG[nCnt].rot.y), cosf(g_PlayerBG[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(4).y), cosf(Getrot(4).y)) + D3DX_PI * 0.25f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_PlayerBG[nCnt].rot.y), cosf(g_PlayerBG[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(4).y), cosf(Getrot(4).y)) + D3DX_PI * -0.25f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_PlayerBG[nCnt].rot.y), cosf(g_PlayerBG[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(4).y), cosf(Getrot(4).y));
		}
	}
	else if (GetKeyboardPress(DIK_S) == true || GetGamepad_Stick_Left(0).y < -0.1f)
	{
		if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_PlayerBG[nCnt].rot.y), cosf(g_PlayerBG[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(4).y), cosf(Getrot(4).y)) + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_PlayerBG[nCnt].rot.y), cosf(g_PlayerBG[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(4).y), cosf(Getrot(4).y)) + D3DX_PI * -0.75f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_PlayerBG[nCnt].rot.y), cosf(g_PlayerBG[nCnt].rot.y));
			fRotDest = atan2f(sinf(Getrot(4).y), cosf(Getrot(4).y)) + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetGamepad_Stick_Left(0).x > 0.1f)
	{
		fRotMove = atan2f(sinf(g_PlayerBG[nCnt].rot.y), cosf(g_PlayerBG[nCnt].rot.y));
		fRotDest = atan2f(sinf(Getrot(4).y), cosf(Getrot(4).y)) + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_A) == true || GetGamepad_Stick_Left(0).x < -0.1f)
	{
		fRotMove = atan2f(sinf(g_PlayerBG[nCnt].rot.y), cosf(g_PlayerBG[nCnt].rot.y));
		fRotDest = atan2f(sinf(Getrot(4).y), cosf(Getrot(4).y)) + D3DX_PI * -0.5f;
	}

	////���X�e�B�b�N�ɂ��O��ړ�	
	//g_PlayerBG[nCnt].move.z += GetGamepad_Stick_Left(0).y * cosf(Getrot(4).y) * PLAYERBG_SPEED;
	//g_PlayerBG[nCnt].move.x += GetGamepad_Stick_Left(0).y * sinf(Getrot(4).y) * PLAYERBG_SPEED;

	////���X�e�B�b�N�ɂ�鍶�E�ړ�
	//g_PlayerBG[nCnt].move.x += GetGamepad_Stick_Left(0).x * cosf(Getrot(4).y) * PLAYERBG_SPEED;
	//g_PlayerBG[nCnt].move.z -= GetGamepad_Stick_Left(0).x * sinf(Getrot(4).y) * PLAYERBG_SPEED;

	//fRotMove = atan2f(sinf(g_PlayerBG[nCnt].rot.y), cosf(g_PlayerBG[nCnt].rot.y));
	//fRotDest = atan2f(sinf(Getrot(4).y), cosf(Getrot(4).y) + D3DX_PI * GetGamepad_Stick_Left(0).x);

	fRotDiff = fRotDest - fRotMove;

	if (fRotDiff > D3DX_PI * 1.0f)
	{
		fRotDiff -= D3DX_PI * 2.0f;
	}
	else if (fRotDiff < -D3DX_PI * 1.0f)
	{
		fRotDiff += D3DX_PI * 2.0f;
	}

	fRotMove += fRotDiff * PLAYERBG_ROT_SPEED;

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
		g_PlayerBG[nCnt].rot.y = fRotMove;
	}
}

//====================================================================
//�v���C���[�̕`�揈��
//====================================================================
void DrawPlayerBG(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntPlayerBG = 0; nCntPlayerBG < MAX_PLAYREBG; nCntPlayerBG++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_PlayerBG[nCntPlayerBG].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_PlayerBG[nCntPlayerBG].rot.y, g_PlayerBG[nCntPlayerBG].rot.x, g_PlayerBG[nCntPlayerBG].rot.z);

		D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].mtxWorld, &g_PlayerBG[nCntPlayerBG].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_PlayerBG[nCntPlayerBG].pos.x, g_PlayerBG[nCntPlayerBG].pos.y, g_PlayerBG[nCntPlayerBG].pos.z);

		D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].mtxWorld, &g_PlayerBG[nCntPlayerBG].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_PlayerBG[nCntPlayerBG].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//�S���f��(�p�[�c)�̕`��
		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;	//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;	//�e�̃}�g���b�N�X

									//�p�[�c�̃}�g���b�N�X��������
			D3DXMatrixIdentity(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld);

			//�p�[�c�̌����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].rot.y, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].rot.x, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].rot.z);

			D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &mtxRotModel);

			//�p�[�c�̈ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].pos.x, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].pos.y, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].pos.z);

			D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &mtxTransModel);

			//�p�[�c�́u�e�̃}�g���b�N�X�v��ݒ�
			if (g_PlayerBG[nCntPlayerBG].aModel[nCntModel].nIndexModelParent != -1)
			{//�e���f��������ꍇ
				mtxParent = g_PlayerBG[nCntPlayerBG].aModel[g_PlayerBG[nCntPlayerBG].aModel[nCntModel].nIndexModelParent].mtxWorld;	//�e���f���̃C���f�b�N�X�̃}�g���b�N�X���w�肷��
			}
			else
			{//�e���f�����Ȃ��ꍇ
				mtxParent = g_PlayerBG[nCntPlayerBG].mtxWorld;	//�v���C���[�̃}�g���b�N�X���w�肷��
			}

			//�Z�o�����u�p�[�c�̃��[���h�}�g���b�N�X�v�Ɓu�e�̃}�g���b�N�X�v���|�����킹��
			D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld,
				&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld,
				&mtxParent);

			//�p�[�c�̃��[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld);

			//�}�e���A���f�[�^�ւ̃|�C���^����������
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayerBG[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat]);

				if (g_PlayerBG[nCntPlayerBG].bUse == true)
				{
					//�v���C���[(�p�[�c)�̕`��
					g_pMeshPlayerBG[nCntModel]->DrawSubset(nCntMat);
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
PlayerBG * GetPlayerBG(void)
{
	return &g_PlayerBG[0];
}