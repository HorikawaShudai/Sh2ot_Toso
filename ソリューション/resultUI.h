#ifndef _RESULTUI_H_
#define _RESULTUI_H_

#include "main.h"

//�v���C���[�̏��
typedef enum
{
	RESULTUI_ONLY = 0,		//1�l����(��l�v���C������)
	RESULTUI_TWO,			//��l�ȏ�S����������
	RESULTUI_PERFECT,		//�S�������̏ꍇ
	RESULTUI_MAX
}RESULTUI;

//�v���g�^�C�v�錾
void InitResultUI(void);
void UninitResultUI(void);
void UpdateResultUI(void);
void DrawResultUI(void);
void SetResultUI(RESULTUI SetClear);
void SetbResultUi(bool bReseultUi);
bool GetbResultUi(void);
#endif
