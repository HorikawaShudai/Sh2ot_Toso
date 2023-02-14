#ifndef _ESCAPETUTORIAL_H_
#define _ESCAPETUTORIAL_H_

//�t�F�[�h�̏��
typedef enum
{
	TUTORIAL_STATE_STANDBY = 0,
	TUTORIAL_STATE_WAIT,
	TUTORIAL_STATE_PLAY,
	TUTORIAL_STATE_MAX,
}TUTORIAL_STATE;

//�v���g�^�C�v�錾
void InitEscapeTutorial();
void UninitEscapeTutorial();
void UpdateEscapeTutorial();
void DrawEscapeTutorial();
TUTORIAL_STATE GetEscapeTutorial();
void SetEscapeTutorial(TUTORIAL_STATE nSet);
#endif