//===============================
//
//�X�R�A����(score.h)
//Author:���� �F�M
//
//===============================
#ifndef _SCORE_H_   //���̃}�N����`������Ă��Ȃ�������
#define _SCORE_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�X�R�A�̍\����
typedef struct
{
	D3DXVECTOR3 posScore;  //�X�R�A�̈ʒu
	int nScore;			//�X�R�A�̒l
	float nWindth;		//���̒l
	float nHeight;		//�����̒l
}SCORE;

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore,int nPlayer);
void AddScore(int nType,int nPlayer);
int GetScore(int nPlayer);
void SetPosScore(D3DXVECTOR3 pos,float nWINDTH,float nHeight,int nPlayer);

#endif
