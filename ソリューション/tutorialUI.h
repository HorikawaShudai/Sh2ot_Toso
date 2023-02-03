#ifndef _TUTORIALUI_H_
#define _TUTORIALUI_H_

#include "main.h"

//�v���C���[�̏��
typedef enum
{
	TUTORIALUI_NORMAL = 0,		//�ʏ�
	TUTORIALUI_PERFECT,		//�p�[�t�F�N�g
	TUTORIALUI_ALLPERFECT,		//�I�[���p�[�t�F�N�g
	TUTORIALUI_MAX
}TUTORIALUI;

//�v���g�^�C�v�錾
void InitTutorialUI(void);
void UninitTutorialUI(void);
void UpdateTutorialUI(void);
void DrawTutorialUI(void);
void SetTutorialUI(TUTORIALUI SetClear, bool Clear);
#endif

