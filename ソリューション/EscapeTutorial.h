#ifndef _ESCAPETUTORIAL_H_
#define _ESCAPETUTORIAL_H_

<<<<<<< HEAD
//�t�F�[�h�̏��
typedef enum
{
	TUTORIAL_STATE_STANDBY = 0,
	TUTORIAL_STATE_WAIT,
	TUTORIAL_STATE_PLAY,
	TUTORIAL_STATE_MAX,
}TUTORIAL_STATE;
=======
//�`���[�g���A�����e�̍\����(��)
typedef enum
{
	MODE_MOVE = 0,		//�v���C���[�̈ړ�
	MODE_CAM_MOVE,		//�J�����̈ړ�
	MODE_DASH,			//�_�b�V��
	MODE_VIBE,			//�o�C�u
	MODE_STELTH,		//�X�e���X
	MODE_GET_KEY,		//�����Ƃ�
	MODE_ESCAPE,		//�E�o
	MODE__TUTORIAL_MAX,
}TUTORIAL_MODE;
>>>>>>> 3c1ab6ec40d2986d361626d60a22a57874703004

//�v���g�^�C�v�錾
void InitEscapeTutorial();
void UninitEscapeTutorial();
void UpdateEscapeTutorial();
void DrawEscapeTutorial();
TUTORIAL_STATE GetEscapeTutorial();
void SetEscapeTutorial(TUTORIAL_STATE nSet);
#endif