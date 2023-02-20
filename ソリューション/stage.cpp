//========================================================================================
//
// �O���t�@�C������I�u�W�F�N�g��ǂݍ��ޏ���[stage.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "main.h"
#include "game.h"
#include "stage.h"
#include "object00.h"
#include "objectBG.h"
#include "objectLight.h"
#include "edit.h"
#include <stdio.h>

//�}�N����`
#define START_OK ("STARTSETSTAGE")				//�X�^�[�g���b�Z�[�W�����邩�ǂ����̊m�F
#define SETENEMY_OK ("SETENEMY")				//�Z�b�g���b�Z�[�W�����邩�ǂ����̊m�F
#define SET_OBJECT00OK ("SETOBJECT00")			//�Z�b�g���b�Z�[�W�����邩�ǂ����̊m�F
#define SET_OBJECTBGOK ("SETOBJECTBG")			//�Z�b�g���b�Z�[�W�����邩�ǂ����̊m�F
#define SET_OBJECTLIGHTOK ("SETOBJECTLIGHT")	//�Z�b�g���b�Z�[�W�����邩�ǂ����̊m�F
#define ENDENEMY_OK ("ENDENEMY")				//�G���h���b�Z�[�W�����邩�ǂ����̊m�F
#define END_OBJECT00OK ("ENDOBJECT00")			//�G���h���b�Z�[�W�����邩�ǂ����̊m�F
#define END_OBJECTBGOK ("ENDOBJECTBG")			//�G���h���b�Z�[�W�����邩�ǂ����̊m�F
#define END_OBJECTLIGHTOK ("ENDOBJECTLIGHT")	//�G���h���b�Z�[�W�����邩�ǂ����̊m�F
#define END_SET_OK ("ENDSETSTAGE")				//�G���h���b�Z�[�W�����邩�ǂ����̊m�F

//�X�e�[�W�̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//���݂̈ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 rot;							//����
	int nType;							//����
	bool bUse;									//�g�p���Ă��邩�ǂ���
}Stage;

//�X�e�[�W�̍\����
typedef struct
{
	int nCount;
	bool bUse;									//�g�p���Ă��邩�ǂ���
}Stage_Object00;

//�X�e�[�W�̍\����
typedef struct
{
	int nCount;
	bool bUse;									//�g�p���Ă��邩�ǂ���
}Stage_ObjectBG;

//�X�e�[�W�̍\����
typedef struct
{
	int nCount;
	bool bUse;									//�g�p���Ă��邩�ǂ���
}Stage_ObjectLight;

Stage g_Stage[MAX_STAGEOBJECT];
//Stage_Enemy g_StageEnemy[MAX_STAGEOBJECT];
Stage_Object00 g_StageObject00[MAX_STAGEOBJECT];
Stage_ObjectBG g_StageObjectBG[MAX_STAGEOBJECT];
Stage_ObjectBG g_StageObjectLight[MAX_STAGEOBJECT];
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

		g_StageObject00[nCntStage].nCount = -1;
		g_StageObject00[nCntStage].bUse = false;

		g_StageObjectBG[nCntStage].nCount = -1;
		g_StageObjectBG[nCntStage].bUse = false;

		g_StageObjectLight[nCntStage].nCount = -1;
		g_StageObjectLight[nCntStage].bUse = false;
	}

	//�X�e�[�W��ǂݍ���
	LoadStage(nStageNumber);
	g_SelectStage = nStageNumber;

	for (int nCntStage = 0; nCntStage < MAX_STAGEOBJECT; nCntStage++)
	{
		//�I�u�W�F�N�g00�̔z�u
		if (g_StageObject00[nCntStage].bUse == true)
		{
			SetObject00(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_Stage[nCntStage].nType);
		}

		//�I�u�W�F�N�gBG�̔z�u
		if (g_StageObjectBG[nCntStage].bUse == true)
		{
			SetObjectBG(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_Stage[nCntStage].nType);
		}

		//�I�u�W�F�N�gLight�̔z�u
		if (g_StageObjectLight[nCntStage].bUse == true)
		{
			SetObjectLight(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_Stage[nCntStage].nType);
		}
	}
}

//====================================================================
//�u���b�N�̃��[�h����
//====================================================================
void LoadStage(int nStageNumber)
{
	FILE *pFile; //�t�@�C���|�C���^��錾
	
	//�t�@�C�����J��
	pFile = fopen("", "r");

	if (nStageNumber == 0)
	{
		//�t�@�C�����J��
		pFile = fopen(SET_STAGE_TEXT, "r");
	}

	else if (nStageNumber == 1)
	{
		//�t�@�C�����J��
		pFile = fopen("Data\\TEXT\\Title.txt", "r");
	}

	else if (nStageNumber == 2)
	{
		//�t�@�C�����J��
		pFile = fopen("Data\\TEXT\\playnumber.txt","r");
	}

	else if (nStageNumber == 3)
	{
		//�t�@�C�����J��
		pFile = fopen("Data\\TEXT\\result_tousou.txt", "r");
	}

	else if (nStageNumber == 4)
	{
		////�t�@�C�����J��
		//pFile = fopen("Data\\TEXT\\tutorial_tousou.txt", "r");
	}

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

					//�I�u�W�F�N�gBG�̔z�u--------------------------
					if (g_StageObjectBG[nCntStage].bUse == false)
					{

							if (strcmp(&aSetMessage[0], SET_OBJECTBGOK) == 0)
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
								if (strcmp(&aEndMessage[0], END_OBJECTBGOK) != 0)
								{
									break;
								}

								g_StageObjectBG[nCntStage].nCount++;
								g_StageObjectBG[nCntStage].bUse = true;

							}

					}

					//�I�u�W�F�N�gLight�̔z�u--------------------------
					if (g_StageObjectLight[nCntStage].bUse == false)
					{

						if (strcmp(&aSetMessage[0], SET_OBJECTLIGHTOK) == 0)
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
							if (strcmp(&aEndMessage[0], END_OBJECTLIGHTOK) != 0)
							{
								break;
							}

							g_StageObjectLight[nCntStage].nCount++;
							g_StageObjectLight[nCntStage].bUse = true;

						}

					}

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
