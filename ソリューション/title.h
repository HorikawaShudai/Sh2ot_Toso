//==================
//�^�C�g������
//==================
#ifndef _Title_H_
#define _Title_H_

typedef enum
{
	TITLESTATE_NONE = 0,
	TITLESTATE_NORMAL,
	TITLESTATE_START,
	TITLESTATE_END,
	TITLESTATE_MAX,
}TITLESTATE;

//�v���g�^�C�v�錾
void InitTitle();
void UninitTitle();
void UpdateTitle();
void DrawTitle();
void SetTitleState(TITLESTATE state, int nCounter);
TITLESTATE GetTitleState();
int GetPlayerNumber();

#endif // !_TITLE_H_
