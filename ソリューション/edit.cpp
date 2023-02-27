//========================================================================================
//
// �X�e�[�W�̃G�f�B�b�g����[edit.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "edit.h"
#include "debugproc.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"
#include "objectBG.h"
#include "objectLight.h"
#include "objectWall.h"
#include "objectPoly.h"
#include <stdio.h>

//====================================================================
//�G�f�B�b�g��ʂ̏���������
//====================================================================
void InitEdit()
{
	InitObject00();
	InitObjectBG();
	InitObjectLight();
	InitObjectWall();
	InitObjectPoly();
}

//====================================================================
//�G�f�B�b�g��ʂ̏I������
//====================================================================
void UninitEdit()
{
	UninitObject00();
	UninitObjectBG();
	UninitObjectLight();
	UninitObjectWall();
	UninitObjectPoly();
}

//====================================================================
//�G�f�B�b�g��ʂ̍X�V����
//====================================================================
void UpdateEdit()
{
	if (GetKeyboardTrigger(DIK_F9) == true)
	{//f9�������ꂽ�Ƃ�
		SaveEdit();
	}

	PrintDebugProc("�y�G�f�B�b�g���[�h���z�I�u�W�F�N�g�ړ� �y���z�y���z�y���z�y���z\n");
	PrintDebugProc("�I�u�W�F�N�g�㉺�ړ� �y�ESHIFT�z�y�ECTRL�z\n");
	PrintDebugProc("�Q�[�����[�h�Ƃ̐؂�ւ� �yF2�z\n");
	PrintDebugProc("�I�u�W�F�N�g�̎�ސ؂�ւ� �yF3�z\n");
	PrintDebugProc("�i�C�g�r�W�����̃I��/�I�t �yF8�z\n");
	PrintDebugProc("�I�u�W�F�N�g�؂�ւ� �y9�z\n");
	PrintDebugProc("�I�u�W�F�N�g�p�x�؂�ւ� �y0�z\n");
	PrintDebugProc("�I�u�W�F�N�g�ݒu �yENTER�z\n");
	PrintDebugProc("�I�u�W�F�N�g�ۑ� �yF9�z\n");
}

//====================================================================
//�G�f�B�b�g��ʂ̕`�揈��
//====================================================================
void DrawEdit()
{

}

//====================================================================
//�G�f�B�b�g��ʂ̃Z�[�u����
//====================================================================
void SaveEdit()
{
	Object00 *pObject00 = GetObject00();
	ObjectBG *pObjectBG = GetObjectBG();
	ObjectLight *pObjectLight = GetObjectLight();
	ObjectWall *pObjectWall = GetObjectWall();
	ObjectPoly *pObjectPoly = GetObjectPoly();
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(SET_STAGE_TEXT, "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		//�X�e�[�W���Z�[�u����J�n�̍��}
		fprintf(pFile, "%s\n\n", "STARTSETSTAGE");

		for (int nCntObjectWall = 0; nCntObjectWall < MAX_OBJECTWALL; nCntObjectWall++, pObjectWall++)
		{
			if (pObjectWall->bUse == true)
			{//�g�p����Ă���ꍇ

			 //�I�u�W�F�N�g���Z�[�u����J�n�̍��}
				fprintf(pFile, "%s\n", "SETOBJECTWALL");

				//�e��ϐ��̏��Z�[�u
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "POS", pObjectWall->pos.x, pObjectWall->pos.y, pObjectWall->pos.z);
				fprintf(pFile, "%s		%.3f %.3f %.3f\n", "MOVE", pObjectWall->move.x, pObjectWall->move.y, pObjectWall->move.z);
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "ROT", pObjectWall->rot.x, pObjectWall->rot.y, pObjectWall->rot.z);
				fprintf(pFile, "%s		%d\n", "nType", pObjectWall->nType);

				//�I�u�W�F�N�g���Z�[�u�����I���̍��}
				fprintf(pFile, "%s\n\n", "ENDOBJECTWALL");
			}
		}

		for (int nCntObjectPoly = 0; nCntObjectPoly < MAX_OBJECTPOLY; nCntObjectPoly++, pObjectPoly++)
		{
			if (pObjectPoly->bUse == true)
			{//�g�p����Ă���ꍇ

			 //�I�u�W�F�N�g���Z�[�u����J�n�̍��}
				fprintf(pFile, "%s\n", "SETOBJECTPOLY");

				//�e��ϐ��̏��Z�[�u
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "POS", pObjectPoly->pos.x, pObjectPoly->pos.y, pObjectPoly->pos.z);
				fprintf(pFile, "%s		%.3f\n", "WIDTH", pObjectPoly->fWidth);
				fprintf(pFile, "%s			%.3f\n", "HEIGHT", pObjectPoly->fHeight);

				//�I�u�W�F�N�g���Z�[�u�����I���̍��}
				fprintf(pFile, "%s\n\n", "ENDOBJECTPOLY");
			}
		}

		for (int nCntObject00 = 0; nCntObject00 < MAX_OBJECT00; nCntObject00++, pObject00++)
		{
			if (pObject00->bUse == true)
			{//�g�p����Ă���ꍇ

				//�I�u�W�F�N�g���Z�[�u����J�n�̍��}
				fprintf(pFile, "%s\n", "SETOBJECT00");

				//�e��ϐ��̏��Z�[�u
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "POS", pObject00->pos.x, pObject00->pos.y, pObject00->pos.z);
				fprintf(pFile, "%s		%.3f %.3f %.3f\n", "MOVE", pObject00->move.x, pObject00->move.y, pObject00->move.z);
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "ROT", pObject00->rot.x, pObject00->rot.y, pObject00->rot.z);
				fprintf(pFile, "%s		%d\n", "nType", pObject00->nType);

				//�I�u�W�F�N�g���Z�[�u�����I���̍��}
				fprintf(pFile, "%s\n\n", "ENDOBJECT00");
			}
		}

		for (int nCntObjectBG = 0; nCntObjectBG < MAX_OBJECTBG; nCntObjectBG++, pObjectBG++)
		{
			if (pObjectBG->bUse == true)
			{//�g�p����Ă���ꍇ

			 //�I�u�W�F�N�g���Z�[�u����J�n�̍��}
				fprintf(pFile, "%s\n", "SETOBJECTBG");

				//�e��ϐ��̏��Z�[�u
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "POS", pObjectBG->pos.x, pObjectBG->pos.y, pObjectBG->pos.z);
				fprintf(pFile, "%s		%.3f %.3f %.3f\n", "MOVE", pObjectBG->move.x, pObjectBG->move.y, pObjectBG->move.z);
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "ROT", pObjectBG->rot.x, pObjectBG->rot.y, pObjectBG->rot.z);
				fprintf(pFile, "%s		%d\n", "nType", pObjectBG->nType);

				//�I�u�W�F�N�g���Z�[�u�����I���̍��}
				fprintf(pFile, "%s\n\n", "ENDOBJECTBG");
			}
		}

		for (int nCntObjectLight = 0; nCntObjectLight < MAX_OBJECTLIGHT; nCntObjectLight++, pObjectLight++)
		{
			if (pObjectLight->bUse == true)
			{//�g�p����Ă���ꍇ

			 //�I�u�W�F�N�g���Z�[�u����J�n�̍��}
				fprintf(pFile, "%s\n", "SETOBJECTLIGHT");

				//�e��ϐ��̏��Z�[�u
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "POS", pObjectLight->pos.x, pObjectLight->pos.y, pObjectLight->pos.z);
				fprintf(pFile, "%s		%.3f %.3f %.3f\n", "MOVE", pObjectLight->move.x, pObjectLight->move.y, pObjectLight->move.z);
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "ROT", pObjectLight->rot.x, pObjectLight->rot.y, pObjectLight->rot.z);
				fprintf(pFile, "%s		%d\n", "nType", pObjectLight->nType);

				//�I�u�W�F�N�g���Z�[�u�����I���̍��}
				fprintf(pFile, "%s\n\n", "ENDOBJECTLIGHT");
			}
		}

		//�X�e�[�W���Z�[�u�����I���̍��}
		fprintf(pFile, "%s", "ENDSETSTAGE");

		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}