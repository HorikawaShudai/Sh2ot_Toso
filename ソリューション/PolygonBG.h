#ifndef _POLYGONBG_H_
#define _POLYGONBG_H_

#include "main.h"

typedef struct
{
	D3DXCOLOR col;		//�F
	int nLife;			//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}PolygonBG;

//�v���g�^�C�v�錾
void InitPolygonBG(void);
void UninitPolygonBG(void);
void UpdatePolygonBG(void);
void DrawPolygonBG(void);
void SetPolygonBG(D3DXCOLOR Col,int nLife);
#endif