//===============================
//
//�X�R�A����(score.h)
//Author:���� �F�M
//
//===============================
#ifndef _SCORE_H_   //���̃}�N����`������Ă��Ȃ�������
#define _SCORE_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nType);
int GetScore(void);
void SetPosScore(D3DXVECTOR3 pos,float nWINDTH,float nHeight);

#endif
