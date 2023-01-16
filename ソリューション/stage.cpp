#include "main.h"
#include "game.h"
#include "stage.h"
#include "object00.h"
#include <stdio.h>

//�}�N����`
#define START_OK ("STARTSETSTAGE")		//�X�^�[�g���b�Z�[�W�����邩�ǂ����̊m�F
#define SETENEMY_OK ("SETENEMY")		//�Z�b�g���b�Z�[�W�����邩�ǂ����̊m�F
#define SET_OBJECT00OK ("SETOBJECT00")	//�Z�b�g���b�Z�[�W�����邩�ǂ����̊m�F
#define SET_OBJECT01OK ("SETOBJECT01")	//�Z�b�g���b�Z�[�W�����邩�ǂ����̊m�F
#define ENDENEMY_OK ("ENDENEMY")		//�G���h���b�Z�[�W�����邩�ǂ����̊m�F
#define END_OBJECT00OK ("ENDOBJECT00")	//�G���h���b�Z�[�W�����邩�ǂ����̊m�F
#define END_OBJECT01OK ("ENDOBJECT01")	//�G���h���b�Z�[�W�����邩�ǂ����̊m�F
#define END_SET_OK ("ENDSETSTAGE")		//�G���h���b�Z�[�W�����邩�ǂ����̊m�F

//�X�e�[�W�̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//���݂̈ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 rot;							//����
	int nType;							//����
	bool bUse;									//�g�p���Ă��邩�ǂ���
}Stage;
//
////�G�̍\����
//typedef struct
//{
//	ENEMY_NTYPE nType;						//���
//	int nCount;
//	bool bUse;									//�g�p���Ă��邩�ǂ���
//}Stage_Enemy;

//�X�e�[�W�̍\����
typedef struct
{
	int nType;				//���
	int nCount;
	bool bUse;									//�g�p���Ă��邩�ǂ���
}Stage_Object00;

////�X�e�[�W�̍\����
//typedef struct
//{
//	OBJECT01_NTYPE nType;				//���
//	int nCount;
//	bool bUse;									//�g�p���Ă��邩�ǂ���
//}Stage_Object01;

Stage g_Stage[MAX_STAGEOBJECT];
//Stage_Enemy g_StageEnemy[MAX_STAGEOBJECT];
Stage_Object00 g_StageObject00[MAX_STAGEOBJECT];
//Stage_Object01 g_StageObject01[MAX_STAGEOBJECT];
int g_SelectStage;

//====================================================================
//�I�u�W�F�N�g00�̐ݒ菈��
//====================================================================
void SetStage(int nStageNumber)
{
	g_SelectStage = 0;

	for (int nCntStage = 0; nCntStage < MAX_STAGEOBJECT; nCntStage++)
	{
		g_Stage[nCntStage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage[nCntStage].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage[nCntStage].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage[nCntStage].bUse = false;

		//g_StageEnemy[nCntStage].nType = ENEMY_NTYPE00;
		//g_StageEnemy[nCntStage].nCount = -1;
		//g_StageEnemy[nCntStage].bUse = false;

		g_StageObject00[nCntStage].nType = OBJECT00_NTYPE00;
		g_StageObject00[nCntStage].nCount = -1;
		g_StageObject00[nCntStage].bUse = false;

		//g_StageObject01[nCntStage].nType = OBJECT01_NTYPE00;
		//g_StageObject01[nCntStage].nCount = -1;
		//g_StageObject01[nCntStage].bUse = false;
	}

	//�X�e�[�W��ǂݍ���
	LoadStage(nStageNumber);
	g_SelectStage = nStageNumber;

	for (int nCntStage = 0; nCntStage < MAX_STAGEOBJECT; nCntStage++)
	{
		////�G�̔z�u
		//if (g_StageEnemy[nCntStage].bUse == true)
		//{
		//	SetEnemy(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_StageEnemy[nCntStage].nType);
		//}

		//�G�̔z�u
		if (g_StageObject00[nCntStage].bUse == true)
		{
			SetObject00(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_Stage[nCntStage].nType);
		}

		////�G�̔z�u
		//if (g_StageObject01[nCntStage].bUse == true)
		//{
		//	SetObject01(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_StageObject01[nCntStage].nType);
		//}
	}

	//�����蔻��̂���I�u�W�F�N�g�̔z�u
	//SetObject00(D3DXVECTOR3(100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE00);
	//SetObject00(D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE01);
	//SetObject00(D3DXVECTOR3(-100.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE02);
	//SetObject00(D3DXVECTOR3(-200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE03);
	//SetObject00(D3DXVECTOR3(-250.0f, -50.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE03);

	//�����蔻��̂Ȃ��I�u�W�F�N�g�̔z�u
	//SetObject01(D3DXVECTOR3(-100.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT01_NTYPE02);

	//�G�̔z�u
	//SetEnemy(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_NTYPE00);
	//SetEnemy(D3DXVECTOR3(-50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_NTYPE01);
	//SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_NTYPE02);
	//SetEnemy(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_NTYPE03);
	//SetEnemy(D3DXVECTOR3(-100.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_NTYPE03);
}

//====================================================================
//�u���b�N�̃��[�h����
//====================================================================
void LoadStage(int nStageNumber)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen("data\\TEXT\\Stage00.txt", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		char aString[128] = {};			//�S�~��
		char aStartMessage[32] = {};	//�X�^�[�g���b�Z�[�W
		char aSetMessage[32] = {};		//�Z�b�g���b�Z�[�W
		char aEndMessage[32] = {};		//�I�����b�Z�[�W
		char aType[32] = {};		//�I�����b�Z�[�W

		fscanf(pFile, "%s", &aStartMessage[0]);
		if (strcmp(&aStartMessage[0], START_OK) == 0)
		{
			int nCntStage = 0;
			for (int nCntStage = 0; nCntStage < MAX_STAGEOBJECT; nCntStage++)
			{
				//�J�n�̍��}
				fscanf(pFile, "%s", &aSetMessage[0]);

					////�G�̔z�u--------------------------
					//if (g_StageEnemy[nCntStage].bUse == false)
					//{

					//		if (strcmp(&aSetMessage[0], SETENEMY_OK) == 0)
					//		{
					//			fscanf(pFile, "%s", &aString[0]);					//�S�~��
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.x);		//POS�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.y);		//POS�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.z);		//POS�̐ݒ�

					//			fscanf(pFile, "%s", &aString[0]);					//�S�~��
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.x);	//MOVE�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.y);	//MOVE�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.z);	//MOVE�̐ݒ�

					//			fscanf(pFile, "%s", &aString[0]);					//�S�~��
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.x);		//ROT�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.y);		//ROT�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.z);		//ROT�̐ݒ�

					//			fscanf(pFile, "%s", &aString[0]);					//�S�~��
					//			fscanf(pFile, "%s", &aType[0]);						//TYPE�̐ݒ�
					//			if (strcmp(&aType[0], "ENEMY_NTYPE00") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE00;
					//			}
					//			else if (strcmp(&aType[0], "ENEMY_NTYPE01") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE01;
					//			}
					//			else if (strcmp(&aType[0], "ENEMY_NTYPE02") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE02;
					//			}
					//			else if (strcmp(&aType[0], "ENEMY_NTYPE03") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE03;
					//			}
					//			else if (strcmp(&aType[0], "ENEMY_NTYPE04") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE04;
					//			}
					//			else if (strcmp(&aType[0], "ENEMY_NTYPE05") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE05;
					//			}

					//			//�I���̍��}
					//			fscanf(pFile, "%s", &aEndMessage[0]);
					//			if (strcmp(&aEndMessage[0], ENDENEMY_OK) != 0)
					//			{
					//				break;
					//			}

					//			g_StageEnemy[nCntStage].nCount++;
					//			g_StageEnemy[nCntStage].bUse = true;

					//		}
					//	
					//}

					//�I�u�W�F�N�g00�̔z�u--------------------------
					if (g_StageObject00[nCntStage].bUse == false)
					{

							if (strcmp(&aSetMessage[0], SET_OBJECT00OK) == 0)
							{
								fscanf(pFile, "%s", &aString[0]);					//�S�~��
								fscanf(pFile, "%f", &g_Stage[nCntStage].pos.x);		//POS�̐ݒ�
								fscanf(pFile, "%f", &g_Stage[nCntStage].pos.y);		//POS�̐ݒ�
								fscanf(pFile, "%f", &g_Stage[nCntStage].pos.z);		//POS�̐ݒ�

								fscanf(pFile, "%s", &aString[0]);					//�S�~��
								fscanf(pFile, "%f", &g_Stage[nCntStage].move.x);	//MOVE�̐ݒ�
								fscanf(pFile, "%f", &g_Stage[nCntStage].move.y);	//MOVE�̐ݒ�
								fscanf(pFile, "%f", &g_Stage[nCntStage].move.z);	//MOVE�̐ݒ�

								fscanf(pFile, "%s", &aString[0]);					//�S�~��
								fscanf(pFile, "%f", &g_Stage[nCntStage].rot.x);		//ROT�̐ݒ�
								fscanf(pFile, "%f", &g_Stage[nCntStage].rot.y);		//ROT�̐ݒ�
								fscanf(pFile, "%f", &g_Stage[nCntStage].rot.z);		//ROT�̐ݒ�

								fscanf(pFile, "%s", &aString[0]);					//�S�~��
								fscanf(pFile, "%d", &g_Stage[nCntStage].nType);		//TYPE�̐ݒ�

								//�I���̍��}
								fscanf(pFile, "%s", &aEndMessage[0]);
								if (strcmp(&aEndMessage[0], END_OBJECT00OK) != 0)
								{
									break;
								}

								g_StageObject00[nCntStage].nCount++;
								g_StageObject00[nCntStage].bUse = true;

							}
						
					}

					////�I�u�W�F�N�g01�̔z�u--------------------------
					//if (g_StageObject01[nCntStage].bUse == false)
					//{

					//		if (strcmp(&aSetMessage[0], SET_OBJECT01OK) == 0)
					//		{
					//			fscanf(pFile, "%s", &aString[0]);					//�S�~��
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.x);		//POS�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.y);		//POS�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.z);		//POS�̐ݒ�

					//			fscanf(pFile, "%s", &aString[0]);					//�S�~��
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.x);	//MOVE�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.y);	//MOVE�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.z);	//MOVE�̐ݒ�

					//			fscanf(pFile, "%s", &aString[0]);					//�S�~��
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.x);		//ROT�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.y);		//ROT�̐ݒ�
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.z);		//ROT�̐ݒ�

					//			fscanf(pFile, "%s", &aString[0]);					//�S�~��
					//			fscanf(pFile, "%s", &aType[0]);						//TYPE�̐ݒ�
					//			if (strcmp(&aType[0], "OBJECT01_NTYPE00") == 0)
					//			{
					//				g_StageObject01[nCntStage].nType = OBJECT01_NTYPE00;
					//			}
					//			else if (strcmp(&aType[0], "OBJECT01_NTYPE01") == 0)
					//			{
					//				g_StageObject01[nCntStage].nType = OBJECT01_NTYPE01;
					//			}
					//			else if (strcmp(&aType[0], "OBJECT01_NTYPE02") == 0)
					//			{
					//				g_StageObject01[nCntStage].nType = OBJECT01_NTYPE02;
					//			}

					//			//�I���̍��}
					//			fscanf(pFile, "%s", &aEndMessage[0]);
					//			if (strcmp(&aEndMessage[0], END_OBJECT01OK) != 0)
					//			{
					//				break;
					//			}

					//			g_StageObject01[nCntStage].nCount++;
					//			g_StageObject01[nCntStage].bUse = true;

					//		}

					//}

				if (strcmp(&aSetMessage[0], END_SET_OK) == 0)
				{
					break;
				}
			}
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
	//bool = (strcmp(&bool[0], "true") == 0 ? true : false);			//bool�^�̏�����
}

//====================================================================
//�I���X�e�[�W�̓��菈��
//====================================================================
int GetSelectStage(void)
{
	return g_SelectStage;
}
