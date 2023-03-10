#ifndef _POLYGONBG_H_
#define _POLYGONBG_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;		//�F
	float fWidth;		//��
	float fHeight;		//����
	int nLife;			//����
	int nType;			//���
	float KuroPolyA;	//�����|���S���̃��l
	bool bUse;			//�g�p���Ă��邩�ǂ���
}PolygonBG;

//�v���g�^�C�v�錾
void InitPolygonBG(void);
void UninitPolygonBG(void);
void UpdatePolygonBG(void);
void DrawPolygonBG(void);
void SetPolygonBG(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR Col, int nLife,int Type);
#endif