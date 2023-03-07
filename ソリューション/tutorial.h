#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//�`���[�g���A���̏��
typedef enum
{
	TUTORIAL_STATE_GUYDE = 0,
	TUTORIAL_STATE_STANDBY,
	TUTORIAL_STATE_WAIT,
	TUTORIAL_STATE_PLAY,
	TUTORIAL_STATE_MAX,
}TUTORIAL_STATE;

//�`���[�g���A���K�C�h�̏�Ԃ̍\����(��)
typedef enum
{
	TUTORIAL_GUYDE_ESCAPE = 0,
	TUTORIAL_GUYDE_KEY,
	TUTORIAL_GUYDE_HEALTH
}TUTORIAL_GUYDE;

//�`���[�g���A�����e�̍\����(��)
typedef enum
{
	MODE_MOVE = 0,		//�v���C���[�̈ړ�
	MODE_DASH,			//�_�b�V��
	MODE_VIBE,			//�o�C�u
	MODE_STELTH,		//�X�e���X
	MODE_GET_KEY,		//�����Ƃ�
	MODE_ESCAPE,		//�E�o
	MODE_GOEXIT,		//�o������o��
	MODE_END,			//�`���[�g���A�����ڂ̏I��
	MODE__TUTORIAL_MAX,
}TUTORIAL_MODE;

#endif