#ifndef _NUMBERUI_H_
#define _NUMBERUI_H_

#include "main.h"

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nNumberUI;		//����
	float Width;		//��
	float Height;		//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}NumberUI;

//�v���g�^�C�v�錾
void InitNumberUI(void);
void UninitNumberUI(void);
void UpdateNumberUI(void);
void DrawNumberUI(void);
void SetNumberUI(D3DXVECTOR3 pos, float SizeX, float SizeY, int NumberUI);
#endif