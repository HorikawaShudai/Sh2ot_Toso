#ifndef _ESCAPETUTORIAL_H_
#define _ESCAPETUTORIAL_H_

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

//�v���g�^�C�v�錾
void InitEscapeTutorial();
void UninitEscapeTutorial();
void UpdateEscapeTutorial();
void DrawEscapeTutorial();
#endif