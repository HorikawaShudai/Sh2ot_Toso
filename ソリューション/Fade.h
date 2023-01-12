//==================
//�t�F�[�h����
//==================
#ifndef _Fade_H_
#define _Fade_H_

#include "main.h"

typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX,
}FADE;//�t�F�[�h�̏��

//�v���g�^�C�v�錾
void InitFade(MODE modeNext);
void UninitFade();
void UpdateFade();
void DrawFade();
void SetFade(MODE modeNext);
FADE GetFade();

#endif // !_Fade_H_