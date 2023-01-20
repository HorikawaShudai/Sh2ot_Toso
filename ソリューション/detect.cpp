//==========================================
//
//�T�m����
//
//==========================================
#include "detect.h"
#include "enemy.h"
#include "object00.h"
#include "debugproc.h"

//�}�N����`
#define MAX_DETECT (40)
#define DETECT_SPEED (20.0f)

DETECT g_aDitect[MAX_ENEMY][MAX_DETECT];
//==========================================
//����������
//==========================================
void InitDetect(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		for (int nCntDetect = 0; nCntDetect < MAX_DETECT; nCntDetect++)
		{
			g_aDitect[nCntEnemy][nCntDetect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aDitect[nCntEnemy][nCntDetect].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aDitect[nCntEnemy][nCntDetect].fmoveRot = 0.0f;
			g_aDitect[nCntEnemy][nCntDetect].fDistance = 0.0f;
			g_aDitect[nCntEnemy][nCntDetect].nLife = 0;
			g_aDitect[nCntEnemy][nCntDetect].bUse = false;
			g_aDitect[nCntEnemy][nCntDetect].type = DETECTTYPE_WALL;
		}
	}
}
//==========================================
//�I������
//==========================================
void UninitDetect(void)
{

}
//==========================================
//�X�V����
//==========================================
void UpdateDetect(void)
{
	ENEMY*pEnemy = GetEnemy();
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		for (int nCntDetect = 0; nCntDetect < MAX_DETECT; nCntDetect++)
		{
			if (g_aDitect[nCntEnemy][nCntDetect].bUse == true)
			{
			
				while (1)
				{//�ǂɓ����邩�������s����܂ŌJ��Ԃ�
					g_aDitect[nCntEnemy][nCntDetect].posOld = g_aDitect[nCntEnemy][nCntDetect].pos;
					g_aDitect[nCntEnemy][nCntDetect].move = D3DXVECTOR3(sinf(DETECT_SPEED)*g_aDitect[nCntEnemy][nCntDetect].fmoveRot, 0.0f, cosf(DETECT_SPEED)*g_aDitect[nCntEnemy][nCntDetect].fmoveRot);
					g_aDitect[nCntEnemy][nCntDetect].pos += g_aDitect[nCntEnemy][nCntDetect].move;
					g_aDitect[nCntEnemy][nCntDetect].nLife--;
					if (g_aDitect[nCntEnemy][nCntDetect].nLife <= 0)
					{//�������s�����Ƃ�
						g_aDitect[nCntEnemy][nCntDetect].bUse = false;
						PrintDebugProc("�ǂ܂ł̋����F�T�m�͈͊O\n");
						break;
					}
					if (CollisionObject00(&g_aDitect[nCntEnemy][nCntDetect].pos, &g_aDitect[nCntEnemy][nCntDetect].posOld, &g_aDitect[nCntEnemy][nCntDetect].move, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f) == true)
					{//�ǂɓ��������Ƃ�
						g_aDitect[nCntEnemy][nCntDetect].bUse = false;
						//����������o��
						float fDis = (powf(pEnemy->pos.x, 2.0f) + powf(pEnemy->pos.z, 2.0f) - (powf(g_aDitect[nCntEnemy][nCntDetect].pos.x, 2.0f)) + powf(g_aDitect[nCntEnemy][nCntDetect].pos.z, 2.0f));
						if (fDis <= 0)
						{
							fDis *= -1.0f;
						}
						g_aDitect[nCntEnemy][nCntDetect].fDistance = sqrtf(fDis);
						PrintDebugProc("�ǂ܂ł̋����F%f\n", g_aDitect[nCntEnemy][nCntDetect].fDistance);
						
						break;
					}
				}
			}
			
		}
	}
}
//==========================================
//�ݒ菈��
//==========================================
void SetDetect(D3DXVECTOR3 pos, int nEnemy, float fmoveRot, int nLife, DETECTTYPE type)
{
	for (int nCount = 0; nCount < MAX_DETECT; nCount++)
	{
		if (g_aDitect[nEnemy][nCount].bUse == false)
		{
			g_aDitect[nEnemy][nCount].pos = pos;
			g_aDitect[nEnemy][nCount].fmoveRot = fmoveRot;
			g_aDitect[nEnemy][nCount].nLife = nLife;
			g_aDitect[nEnemy][nCount].type = type;
			g_aDitect[nEnemy][nCount].bUse = true;
			break;
		}
	}
}

