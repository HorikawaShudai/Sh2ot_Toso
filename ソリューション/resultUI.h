#ifndef _RESULTUI_H_
#define _RESULTUI_H_

#include "main.h"

//�v���C���[�̏��
typedef enum
{
	RESULTUI_NORMAL = 0,		//�ʏ�
	RESULTUI_PERFECT,		//�p�[�t�F�N�g
	RESULTUI_ALLPERFECT,		//�I�[���p�[�t�F�N�g
	RESULTUI_MAX
}RESULTUI;

//�v���g�^�C�v�錾
void InitResultUI(void);
void UninitResultUI(void);
void UpdateResultUI(void);
void DrawResultUI(void);
void SetResultUI(RESULTUI SetClear, bool Clear);
#endif
