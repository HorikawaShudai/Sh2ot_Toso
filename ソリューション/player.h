//============================
//
//�v���C���[����(player.h)
//Author:���� �F�M
//
//============================

#ifndef _PLAYER_H_   //���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
D3DXVECTOR3 PosPlayer(void);
D3DXVECTOR3 RotPlayer(void);
void MovePlayer(void);
void AnglePlayer(void);

#endif

