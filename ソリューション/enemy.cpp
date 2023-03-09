//========================================================================================
//
// �G�̏���[enemy.cpp]
// Author: �O�� ���V��
//
//========================================================================================

#include "main.h"
#include "ENEMY.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"
#include "Effect.h"
#include "objectPoly.h"
#include "exit.h"
#include <stdio.h>
#include "sound.h"

#define ENEMY_LIFE (7)		//�I�u�W�F�N�g�̗̑�
#define ENEMY_DASHSPEED (2.95f) //�G�̈ړ����x
#define ENEMY_NORMALSPEED (2.0f) //�G�̈ړ����x

#define	DETECT_SPEED (5000.0f) //�T���g�̑��x
#define	PLAYERDETECT_SPEED (1000.0f) //�T���g�̑��x

#define TURN_DISTANCE_WALL (150.0f) //�Ȃ���܂ł̕ǂƂ̋���
#define TURN_DISTANCE_CORNER (300.0f) //�Ȃ���p�ƔF�����鋗��
#define MOVE_DISTANCE_WALL (100.0f) //���E�̕ǂƕۂ���

#define ATTACK_SEEK			(30)
#define ATTACK_COUNT		(200)

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshENEMY[MAX_ENEMY_MODEL] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatENEMY[MAX_ENEMY_MODEL] = {};				//�}�e���A���ւ̃|�C���^

ENEMY g_Enemy[MAX_ENEMY];					//�G�̏��

int g_nDetect;

//�v���g�^�C�v�錾
void EnemyPatrol(int nEnemy);
void EnemyDirection(int nEnemy);

const char *c_apModelEnemy[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\Enemy\\00_Enemy_Hip.x",
	"Data\\MODEL\\Enemy\\01_Enemy_Waist.x",
	"Data\\MODEL\\Enemy\\02_Enemy_Chest.x",
	"Data\\MODEL\\Enemy\\03_Enemy_Head.x",
	"Data\\MODEL\\Enemy\\04_Enemy_Right_Arm_UpperArm.x",
	"Data\\MODEL\\Enemy\\05_Enemy_Right_Arm_ForeArm.x",
	"Data\\MODEL\\Enemy\\06_Enemy_Right_Arm_Hand.x",
	"Data\\MODEL\\Enemy\\07_Enemy_Left_Arm_UpperArm.x",
	"Data\\MODEL\\Enemy\\08_Enemy_Left_Arm_ForeArm.x",
	"Data\\MODEL\\Enemy\\09_Enemy_Left_Arm_Hand.x",
	"Data\\MODEL\\Enemy\\10_Enemy_Right_Leg_Thigh.x",
	"Data\\MODEL\\Enemy\\11_Enemy_Right_Leg_Shin.x",
	"Data\\MODEL\\Enemy\\12_Enemy_Right_Leg_Foot.x",
	"Data\\MODEL\\Enemy\\13_Enemy_Left_Leg_Thigh.x",
	"Data\\MODEL\\Enemy\\14_Enemy_Left_Leg_Shin.x",
	"Data\\MODEL\\Enemy\\15_Enemy_Left_Leg_Foot.x",
	"Data\\MODEL\\Enemy\\16_Enemy_Eye.x",
	"Data\\MODEL\\Enemy\\16_Enemy_Eye.x",
	"Data\\MODEL\\Enemy\\16_Enemy_Eye.x",
	"Data\\MODEL\\Enemy\\16_Enemy_Eye.x",
	"Data\\MODEL\\Enemy\\16_Enemy_Eye.x"
};

const D3DXVECTOR3 TeleportPos[] = //�ړ���̍��W
{
	D3DXVECTOR3(-2150.0f, 0.0f, 455.0f),
	D3DXVECTOR3(-1721.0f, 0.0f, 1254.0f),
	D3DXVECTOR3(-1250.0f, 0.0f, 1315.0f),
	D3DXVECTOR3(-800.0f,  0.0f, 2058.0f),
	D3DXVECTOR3(-1352.0f, 0.0f, 1434.0f),
};

//====================================================================
//�G�̏���������
//====================================================================
void InitEnemy(void)
{
	int nCntObject;
	srand((unsigned int)timeGetTime());
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		g_Enemy[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].Tgpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Enemy[nCntObject].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Enemy[nCntObject].MoveState = ENEMYMOVE_NONE;
		g_Enemy[nCntObject].bUse = false;
		g_Enemy[nCntObject].state = ENEMYSTATE_PATROL;
		g_Enemy[nCntObject].StateCount = 0;
		g_Enemy[nCntObject].nCoolTurn = 0;
		g_Enemy[nCntObject].nTarget = -1;
		g_Enemy[nCntObject].bHit = false;
		g_Enemy[nCntObject].nTargetOld = -1;

		//���[�V�����̐ݒ菈��
		g_Enemy[nCntObject].MotionType = ENEMY_ACTION_MOVE;
		SetEnemyMotion(g_Enemy[nCntObject].MotionType, nCntObject);

		g_nDetect = 0;

		g_Enemy[nCntObject].g_nNextKey = 1;

		//�O���t�@�C������L�����N�^�[����ǂݍ��ޏ���
		LoadEnemyMotion(nCntObject);

		for (int nCntEnemy = 0; nCntEnemy < g_Enemy[nCntObject].nNumModel; nCntEnemy++)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(c_apModelEnemy[nCntEnemy],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatENEMY[nCntEnemy],
				NULL,
				&g_Enemy[nCntObject].aModel[nCntEnemy].g_dwNumMatEnemyBG,
				&g_pMeshENEMY[nCntEnemy]);

			D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

			//�}�e���A�����ɑ΂���|�C���^������
			pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[nCntEnemy]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntObject].aModel[nCntEnemy].g_dwNumMatEnemyBG; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Enemy[nCntObject].aModel[nCntEnemy].g_pTextureEnemyBG[nCntMat]);
				}
			}

		}
	}
}

//====================================================================
//�G�̏I������
//====================================================================
void UninitEnemy(void)
{
	for (int nCntNumObject = 0; nCntNumObject < MAX_ENEMY; nCntNumObject++)
	{
		for (int nCntModel = 0; nCntModel < g_Enemy[nCntNumObject].nNumModel; nCntModel++)
		{
			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntNumObject].aModel[nCntModel].g_dwNumMatEnemyBG; nCntMat++)
			{
				//�e�N�X�`���̔j��
				if (g_Enemy[nCntNumObject].aModel[nCntModel].g_pTextureEnemyBG[nCntMat] != NULL)
				{
					g_Enemy[nCntNumObject].aModel[nCntModel].g_pTextureEnemyBG[nCntMat]->Release();
					g_Enemy[nCntNumObject].aModel[nCntModel].g_pTextureEnemyBG[nCntMat] = NULL;
				}
			}
		}

		for (int nCntModel = 0; nCntModel < g_Enemy[nCntNumObject].nNumModel; nCntModel++)
		{
			//���b�V���̔j��
			if (g_pMeshENEMY[nCntNumObject] != NULL)
			{
				g_pMeshENEMY[nCntNumObject]->Release();
				g_pMeshENEMY[nCntNumObject] = NULL;
			}

			//�}�e���A���̔j��
			if (g_pBuffMatENEMY[nCntNumObject] != NULL)
			{
				g_pBuffMatENEMY[nCntNumObject]->Release();
				g_pBuffMatENEMY[nCntNumObject] = NULL;
			}
		}
	}
}

//====================================================================
//�G�̍X�V����
//====================================================================
void UpdateEnemy(void)
{
	g_nDetect++;
	for (int nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == true)
		{
			g_Enemy[nCntObject].posOld = g_Enemy[nCntObject].pos;
			g_Enemy[nCntObject].StateCount--;
			g_Enemy[nCntObject].nCoolTurn--;
			g_Enemy[nCntObject].nTargetOld = g_Enemy[nCntObject].nTarget;

			//�p�x�̏C���i���j
			if (g_Enemy[nCntObject].rotDest.y - g_Enemy[nCntObject].rot.y > D3DX_PI || g_Enemy[nCntObject].rotDest.y - g_Enemy[nCntObject].rot.y < -D3DX_PI)
			{
				g_Enemy[nCntObject].rot.y -= (g_Enemy[nCntObject].rotDest.y - g_Enemy[nCntObject].rot.y) * 0.03f;
			}
			else
			{
				g_Enemy[nCntObject].rot.y += (g_Enemy[nCntObject].rotDest.y - g_Enemy[nCntObject].rot.y) * 0.3f;
			}

			//�o���Ƃ̓����蔻��
			if (CollisionExi(&g_Enemy[nCntObject].pos, &g_Enemy[nCntObject].posOld, &g_Enemy[nCntObject].move, D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), 10.0f))
			{//����������背�|������
				TeleportationEnemy(&g_Enemy[nCntObject].pos);
			}

			//�����]���̃N�[���^�C��
			if (g_Enemy[nCntObject].nCoolTurn <= 0)
			{
				g_Enemy[nCntObject].nCoolTurn = 0;
			}

			//�v���C���[�T�m
			if (g_Enemy[nCntObject].state != ENEMYSTATE_ATTACK && g_Enemy[nCntObject].state != ENEMYSTATE_CHASE)
			{	
					float DetectRot = g_Enemy[nCntObject].rot.y - D3DXToRadian(45.0f) + D3DXToRadian(7.5f * (g_nDetect % 12));
					if (DetectPlayer(g_Enemy[nCntObject].pos, DetectRot, nCntObject) == true)
					{
						if (g_Enemy[nCntObject].MotionType != ENEMY_ACTION_DASH)
						{
							//���[�V�����̐ݒ菈��
							SetEnemyMotion(ENEMY_ACTION_DASH, nCntObject);

							//�G�̔�����
							PlaySound(SOUND_LABEL_SE_ENEMYFIND);
						}

						g_Enemy[nCntObject].state = ENEMYSTATE_CHASE;
					}
				
			}
			
			if (g_Enemy[nCntObject].state == ENEMYSTATE_PATROL)
			{
				
				EnemyPatrol(nCntObject);
				CollisionObjectWall(&g_Enemy[nCntObject].pos, &g_Enemy[nCntObject].posOld, &g_Enemy[nCntObject].move, D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1.0f);
				CollisionObjectPoly(&g_Enemy[nCntObject].pos, &g_Enemy[nCntObject].posOld, &g_Enemy[nCntObject].move, D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1.0f);
			

			}

			if (g_Enemy[nCntObject].state == ENEMYSTATE_CHASE)
			{//�ǐՏ�Ԃ̎�
				//�v���C���[�̃|�C���^���擾
				Player*pPlayer = GetPlayer();
				//�x�N�g�������߂�
				D3DXVECTOR3 vecEnemy = g_Enemy[nCntObject].Tgpos - g_Enemy[nCntObject].pos ;
				vecEnemy.y = atan2f(vecEnemy.x, vecEnemy.z);
#ifdef _DEBUG

				PrintDebugProc("���W�Fx%fz%f\n", g_Enemy[nCntObject].pos.x, g_Enemy[nCntObject].pos.z);
				PrintDebugProc("�ڕW���W�Fx%fz%f\n", g_Enemy[nCntObject].Tgpos.x, g_Enemy[nCntObject].Tgpos.z);
				PrintDebugProc("�ړ��p�x�F%f\n",vecEnemy.y);
#endif // _DEBUG
				g_Enemy[nCntObject].rotDest = vecEnemy;
				//���W�̍X�V
			
				g_Enemy[nCntObject].move = D3DXVECTOR3(sinf(g_Enemy[nCntObject].rot.y)*ENEMY_DASHSPEED, 0.0f, cosf(g_Enemy[nCntObject].rot.y)*ENEMY_DASHSPEED);
				g_Enemy[nCntObject].pos += g_Enemy[nCntObject].move;
		
				//�ڕW�n�_�ɓ��B�����Ƃ�
				if (vecEnemy.x < 10.0f && vecEnemy.x > -10.0f && vecEnemy.z < 10.0f && vecEnemy.z > -10.0f)
				{//�T����Ԃɐ؂�ւ���
					
					g_Enemy[nCntObject].state = ENEMYSTATE_SEEK;
					g_Enemy[nCntObject].StateCount = ATTACK_SEEK;
				
				}
				D3DXVECTOR3	vecPlayer;
				for (int nCnt = 0; nCnt < 4; nCnt++,pPlayer++)
				{
					if (pPlayer->bUse == true)
					{
						D3DXVECTOR3 rot = pPlayer->pos - g_Enemy[nCntObject].pos;
						rot.y = atan2f(rot.x, rot.z);
						if (DetectPlayer(g_Enemy[nCntObject].pos, rot.y, nCntObject) == true)
						{
							g_Enemy[nCntObject].Tgpos;
						}
						if (g_Enemy[nCntObject].Tgpos == pPlayer->pos)
						{
							if (g_Enemy[nCntObject].MotionType != ENEMY_ACTION_DASH)
							{
								//���[�V�����̐ݒ菈��
								SetEnemyMotion(ENEMY_ACTION_DASH, nCntObject);

								//�G�̔�����
								PlaySound(SOUND_LABEL_SE_ENEMYFIND);
							}

							pPlayer->bChase = true;
							g_Enemy[nCntObject].nTargetOld = g_Enemy[nCntObject].nTarget;
							g_Enemy[nCntObject].nTarget = nCnt;
						}
						vecPlayer = pPlayer->pos - g_Enemy[nCntObject].pos;
						//�ڕW�n�_�ɓ��B�����Ƃ�
						if (vecPlayer.x < 30.0f && vecPlayer.x > -30.0f && vecPlayer.z < 30.0f && vecPlayer.z > -30.0f)
						{
							if (g_Enemy[nCntObject].MotionType != ENEMY_ACTION_ATTACK)
							{
								//���[�V�����̐ݒ菈��
								SetEnemyMotion(ENEMY_ACTION_ATTACK, nCntObject);
							}

							g_Enemy[nCntObject].state = ENEMYSTATE_ATTACK;
							g_Enemy[nCntObject].StateCount = ATTACK_COUNT;
							PlayerHit(nCnt, 1);
							g_Enemy[nCntObject].bHit = true;
							pPlayer->bChase = false;
							g_Enemy[nCntObject].nTarget = -1;
							if (pPlayer->nLife > 0)
							{
								TeleportationEnemy(&g_Enemy[nCntObject].pos);
							}
						}
					}
				}
			}

			if (g_Enemy[nCntObject].state == ENEMYSTATE_SEEK)
			{//�T����Ԃ̎�
				g_Enemy[nCntObject].rotDest.y += D3DX_PI / 20;
			}

			//�p�x�̐��퉻
			if (g_Enemy[nCntObject].rot.y >= D3DX_PI)
			{
				g_Enemy[nCntObject].rot.y += -D3DX_PI*2;
			}
			else if (g_Enemy[nCntObject].rot.y <= -D3DX_PI)
			{
				g_Enemy[nCntObject].rot.y += D3DX_PI*2;
			}
			if (g_Enemy[nCntObject].rotDest.y > D3DX_PI)
			{
				g_Enemy[nCntObject].rotDest.y += -D3DX_PI*2;
			}
			else if (g_Enemy[nCntObject].rotDest.y < -D3DX_PI)
			{
				g_Enemy[nCntObject].rotDest.y += D3DX_PI*2;
			}
			//�^�[�Q�b�g�ύX���̏���
			if (g_Enemy[nCntObject].nTarget != g_Enemy[nCntObject].nTargetOld)
			{
				if (g_Enemy[nCntObject].nTargetOld >= 0)
				{
					Player*pPlayer = GetPlayer();
					for (int nCnt = 0; nCnt < g_Enemy[nCntObject].nTargetOld; nCnt++)
					{
						pPlayer++;
					}
					pPlayer->bChase = false;

				}
			}

			if (g_Enemy[nCntObject].StateCount <= 0)
			{
				g_Enemy[nCntObject].StateCount = 0;
				
				switch (g_Enemy[nCntObject].state)
				{
				case ENEMYSTATE_SEEK:

					if (g_Enemy[nCntObject].MotionType != ENEMY_ACTION_MOVE)
					{
						//���[�V�����̐ݒ菈��
						SetEnemyMotion(ENEMY_ACTION_MOVE, nCntObject);
					}

					g_Enemy[nCntObject].state = ENEMYSTATE_PATROL;
					if (g_Enemy[nCntObject].nTarget >= 0)
					{
						Player*pPlayer = GetPlayer();
						for (int nCnt = 0; nCnt < g_Enemy[nCntObject].nTarget; nCnt++)
						{
							pPlayer++;
						}
						pPlayer->bChase = false;
						g_Enemy[nCntObject].nTarget = -1;

					}
					
					break;
				case ENEMYSTATE_ATTACK:

					if (g_Enemy[nCntObject].MotionType != ENEMY_ACTION_MOVE)
					{
						//���[�V�����̐ݒ菈��
						SetEnemyMotion(ENEMY_ACTION_MOVE, nCntObject);
					}

					g_Enemy[nCntObject].state = ENEMYSTATE_PATROL;
					break;
				case ENEMYSTATE_ATTACK_STANDBY:
					g_Enemy[nCntObject].state = ENEMYSTATE_ATTACK;
					break;
				default:
					break;
				}
			}

			//���[�V�����̍X�V����
			UpdateEnemyMotion(nCntObject);
		}
	}
}

//====================================================================
//�G�̕`�揈��
//====================================================================
void DrawEnemy(void)
{
	int nCntObject;
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntObjectModel = 0; nCntObjectModel < MAX_ENEMY; nCntObjectModel++)
	{
		//���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&g_Enemy[nCntObjectModel].mtx);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntObjectModel].rot.y, g_Enemy[nCntObjectModel].rot.x, g_Enemy[nCntObjectModel].rot.z);
		D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].mtx, &g_Enemy[nCntObjectModel].mtx, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntObjectModel].pos.x, g_Enemy[nCntObjectModel].pos.y, g_Enemy[nCntObjectModel].pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].mtx, &g_Enemy[nCntObjectModel].mtx, &mtxTrans);

		//���[���h�}�g���N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntObjectModel].mtx);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);
		for (nCntObject = 0; nCntObject < g_Enemy[nCntObjectModel].nNumModel; nCntObject++)
		{
			D3DXMATRIX mtxParent;
			D3DXMATRIX mtxRotModel, mtxTransModel; //�v�Z�p�}�g���N�X

			//�p�[�c�̃}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.y, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.x, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &mtxRotModel);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.x, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.y, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &mtxTransModel);

			//�e�̃}�g���N�X�̐ݒ�
			if (g_Enemy[nCntObjectModel].aModel[nCntObject].nIndexModelParent != -1)
			{
				mtxParent = g_Enemy[nCntObjectModel].aModel[g_Enemy[nCntObjectModel].aModel[nCntObject].nIndexModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_Enemy[nCntObjectModel].mtx;
			}

			//�Z�o�����}�g���N�X���������킹��
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld,
				&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld,
				&mtxParent);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld);

			//���݂̃}�e���A��������
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^����������
			pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[nCntObject]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntObjectModel].aModel[nCntObject].g_dwNumMatEnemyBG; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Enemy[nCntObjectModel].bUse == true)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_Enemy[nCntObjectModel].aModel[nCntObject].g_pTextureEnemyBG[nCntMat]);

					//�G(�p�[�c)�̕`��
					g_pMeshENEMY[nCntObject]->DrawSubset(nCntMat);
				}
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�G�̐ݒ菈��
//====================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == false)
		{
			g_Enemy[nCntObject].pos = pos;
			g_Enemy[nCntObject].posOld = pos;
			g_Enemy[nCntObject].move = move;
			g_Enemy[nCntObject].rot = rot;

			g_Enemy[nCntObject].Tgpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Enemy[nCntObject].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Enemy[nCntObject].MoveState = ENEMYMOVE_NONE;
			g_Enemy[nCntObject].state = ENEMYSTATE_PATROL;
			g_Enemy[nCntObject].StateCount = 0;
			g_Enemy[nCntObject].nCoolTurn = 0;
			g_Enemy[nCntObject].nTarget = -1;
			g_Enemy[nCntObject].bHit = false;
			g_Enemy[nCntObject].nTargetOld = -1;

			//���[�V�����̐ݒ菈��
			g_Enemy[nCntObject].MotionType = ENEMY_ACTION_MOVE;
			SetEnemyMotion(g_Enemy[nCntObject].MotionType, nCntObject);

			//�O���t�@�C������L�����N�^�[����ǂݍ��ޏ���
			LoadEnemyMotion(nCntObject);

			g_Enemy[nCntObject].bUse = true;

			break;
		}
	}
}


//====================================================================
//�e�Ƃ̓����蔻�菈��
//====================================================================
void CollisionEnemyShadow(D3DXVECTOR3 *pPos)
{
	for (int nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == true)
		{
			if (
				pPos->y >= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMin.y &&
				pPos->y <= g_Enemy[nCntObject].pos.y + g_Enemy[nCntObject].vtxMax.y &&
				pPos->x >= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMin.x &&
				pPos->x <= g_Enemy[nCntObject].pos.x + g_Enemy[nCntObject].vtxMax.x &&
				pPos->z >= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMin.z &&
				pPos->z <= g_Enemy[nCntObject].pos.z + g_Enemy[nCntObject].vtxMax.z
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->y = g_Enemy[nCntObject].vtxMax.y;
			}
		}
	}
}
void TeleportationEnemy(D3DXVECTOR3 *pPos)
{
	int nCnt = 0;
	int nRand;
	Player*pPlayer;
	while (1)
	{
		nCnt++;
		nRand = rand() % 5;
		pPlayer = GetPlayer();
		float fDis = TeleportPos[nRand].x - pPlayer->pos.x + TeleportPos[nRand].z - pPlayer->pos.z;
		if (fDis < 0)
		{
			fDis *= -1;
		}
		if (fDis > 1000.0f)
		{
			*pPos = TeleportPos[nRand];
			break;
		}
		if (nCnt > 100)
		{
			break;
		}
	}
}
//====================================================================
//�G�̎擾
//====================================================================
ENEMY * GetEnemy(void)
{
	return &g_Enemy[0];
}

//====================================================================
//�G�̍폜����
//====================================================================
void FalseEnemy(void)
{
	for (int nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == true)
		{
			g_Enemy[nCntObject].bUse = false;
		}
	}
}

//====================================================================
//�ǂ̒T��
//====================================================================
float DetectWall(D3DXVECTOR3 pos, float fmoveRot, int nLife)
{
	DETECT Detect;
	Detect.Startpos = pos;
	Detect.pos = pos;
	Detect.fmoveRot = fmoveRot;

	Detect.posOld = Detect.pos;
	Detect.move = D3DXVECTOR3(sinf(Detect.fmoveRot)*DETECT_SPEED, 0.0f, cosf(Detect.fmoveRot)*DETECT_SPEED);
	Detect.pos += Detect.move;

	D3DXVECTOR3 posPoint = CollisionOuterProductObjectWall(&Detect.pos, &Detect.posOld, &Detect.move);
	D3DXVECTOR3 posPoint2 = CollisionOuterProductObjectPoly(&Detect.pos, &Detect.posOld, &Detect.move);
	if (pos != NULL)
	{//�ǂɓ��������Ƃ�
	 //����������o��
		float fDis = ((powf(Detect.Startpos.x, 2.0f) + powf(Detect.Startpos.z, 2.0f)) - (powf(posPoint.x, 2.0f) + powf(posPoint.z, 2.0f)));
		float fDis2 = ((powf(Detect.Startpos.x, 2.0f) + powf(Detect.Startpos.z, 2.0f)) - (powf(posPoint2.x, 2.0f) + powf(posPoint2.z, 2.0f)));
		if (fDis <= 0)
		{
			fDis *= -1.0f;
		}
		if (fDis2 <= 0)
		{
			fDis2 *= -1.0f;
		}
		if (fDis < fDis2)
		{
			//SetEffect(posPoint, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 60, 0);
			Detect.fDistance = sqrtf(fDis);
		}
		else
		{
			//	SetEffect(posPoint2, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 60, 0);
			Detect.fDistance = sqrtf(fDis2);
		}

		//SetEffect(posPoint, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 60, 0);
		return Detect.fDistance;
	}
	else
	{
		return 10000;
	}

}

//====================================================================
//�v���C���[�̒T��
//====================================================================
bool DetectPlayer(D3DXVECTOR3 pos, float fmoveRot, int nEnemy)
{
	DETECT Detect;
	Detect.pos = pos;
	Detect.fmoveRot = fmoveRot;

	Detect.posOld = Detect.pos;
	Detect.move = D3DXVECTOR3(sinf(Detect.fmoveRot)*PLAYERDETECT_SPEED, 0.0f, cosf(Detect.fmoveRot)*PLAYERDETECT_SPEED);
	Detect.pos += Detect.move;
	D3DXVECTOR3 posPoint[3];
	float fDis[3];
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			 posPoint[nCnt] = CollisionOuterProductObjectWall(&Detect.pos, &Detect.posOld, &Detect.move);
			 break;
		case 1:
			posPoint[nCnt] = CollisionOuterProductPlayer(&Detect.pos, &Detect.posOld, &Detect.move);
			break;
		case 2:
			posPoint[nCnt] = CollisionOuterProductObjectPoly(&Detect.pos, &Detect.posOld, &Detect.move);
			break;
		default:
			break;
		}
		fDis[nCnt] = posPoint[nCnt].x - g_Enemy[nEnemy].pos.x + posPoint[nCnt].z - g_Enemy[nEnemy].pos.z;
		if (fDis[nCnt] < 0)
		{
			fDis[nCnt] *= -1;
		}
	}
	
	
	if (fDis[1] < fDis[0] && fDis[1] < fDis[2] )
	{
		g_Enemy[nEnemy].Tgpos = posPoint[1];
		return true;
	}
	else
	{
		return false;
	}
}
//====================================================================
//���񏈗�
//====================================================================
void EnemyPatrol(int nEnemy)
{
	Player*pPlayer = GetPlayer();
	for (int nCnt = 0; nCnt < 4; nCnt++, pPlayer++)
	{
		if (pPlayer->bUse == true)
		{
			float fDis = (g_Enemy[nEnemy].pos.x - pPlayer->pos.x) + (g_Enemy[nEnemy].pos.z - pPlayer->pos.z);
			if (fDis < 0)
			{
				fDis *= -1.0f;
			}
			if (pPlayer->MoveState == PLAYER_MOVESTATE_DASH && fDis <= 700.0f)
			{
				D3DXVECTOR3 rot = pPlayer->pos - g_Enemy[nEnemy].pos;
				rot.y = atan2f(rot.x, rot.y);
				if (DetectPlayer(g_Enemy[nEnemy].pos, rot.y, nEnemy) == true)
				{
					g_Enemy[nEnemy].state = ENEMYSTATE_CHASE;
					break;
				}
			}
			if (pPlayer->MoveState == PLAYER_MOVESTATE_NORMAL && fDis <= 530.0f)
			{
				D3DXVECTOR3 rot = pPlayer->pos - g_Enemy[nEnemy].pos;
				rot.y = atan2f(rot.x, rot.y);
				if (DetectPlayer(g_Enemy[nEnemy].pos, rot.y, nEnemy) == true)
				{
					g_Enemy[nEnemy].state = ENEMYSTATE_CHASE;
					break;
				}
			}
		}
	}

		//�e���ʂɂ���ǂƂ̋����𑪒�
		g_Enemy[nEnemy].fDistanceN = DetectWall(g_Enemy[nEnemy].pos, 0.0f, 100);
		g_Enemy[nEnemy].fDistanceS = DetectWall(g_Enemy[nEnemy].pos, D3DX_PI, 100);
		g_Enemy[nEnemy].fDistanceW = DetectWall(g_Enemy[nEnemy].pos, D3DX_PI*-0.5f, 100);
		g_Enemy[nEnemy].fDistanceE = DetectWall(g_Enemy[nEnemy].pos, D3DX_PI*0.5f, 100);
		g_Enemy[nEnemy].fDistanceFront = DetectWall(g_Enemy[nEnemy].pos, g_Enemy[nEnemy].rot.y, 100);
		g_Enemy[nEnemy].fDistanceLeft = DetectWall(g_Enemy[nEnemy].pos, g_Enemy[nEnemy].rot.y + D3DX_PI*-0.5f, 100);
		g_Enemy[nEnemy].fDistanceRight = DetectWall(g_Enemy[nEnemy].pos, g_Enemy[nEnemy].rot.y + D3DX_PI*0.5f, 100);

#ifdef _DEBUG

		//PrintDebugProc("\nEnemy%d�k:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceN);
		//PrintDebugProc("Enemy%d��:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceS);
		//PrintDebugProc("Enemy%d��:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceW);
		//PrintDebugProc("Enemy%d��:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceE);

		//PrintDebugProc("\nEnemy%d�E:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceRight);
		//PrintDebugProc("Enemy%d��:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceLeft);
		//PrintDebugProc("Enemy%d�O:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceFront);

		PrintDebugProc("\nEnemy%d(��)(�E)(�O):(%f)(%f)(%f)\n", nEnemy, g_Enemy[nEnemy].fDistanceLeft, g_Enemy[nEnemy].fDistanceRight, g_Enemy[nEnemy].fDistanceFront);

#endif // _DEBUG

		//���g�̐i�ޕ����ɕǂ��������ꍇ

		if (g_Enemy[nEnemy].fDistanceFront <= TURN_DISTANCE_WALL || g_Enemy[nEnemy].MoveState == ENEMYMOVE_NONE)
		{
			EnemyDirection(nEnemy);
			g_Enemy[nEnemy].nCoolTurn = 30;

		}
		


		if (g_Enemy[nEnemy].fDistanceLeft >= TURN_DISTANCE_CORNER && 	g_Enemy[nEnemy].nCoolTurn <= 0)
		{
			EnemyDirection(nEnemy);
			g_Enemy[nEnemy].nCoolTurn = 120;
		}
		if (g_Enemy[nEnemy].fDistanceRight >= TURN_DISTANCE_CORNER && 	g_Enemy[nEnemy].nCoolTurn <= 0)
		{
			EnemyDirection(nEnemy);
			g_Enemy[nEnemy].nCoolTurn = 120;
		}

		if (g_Enemy[nEnemy].MoveState == ENEMYMOVE_N)
		{
			g_Enemy[nEnemy].rotDest.y = 0.0f;
		}
		else if (g_Enemy[nEnemy].MoveState == ENEMYMOVE_S)
		{
			g_Enemy[nEnemy].rotDest.y = D3DX_PI;
		}
		else if (g_Enemy[nEnemy].MoveState == ENEMYMOVE_W)
		{
			g_Enemy[nEnemy].rotDest.y = D3DX_PI * -0.5f;
		}
		else if (g_Enemy[nEnemy].MoveState == ENEMYMOVE_E)
		{
			g_Enemy[nEnemy].rotDest.y = D3DX_PI * 0.5f;
		}
		
		if (g_Enemy[nEnemy].MoveState != ENEMYMOVE_NONE)
		{//�ړ�����
			
			//���W�̍X�V
			g_Enemy[nEnemy].move = D3DXVECTOR3(sinf(g_Enemy[nEnemy].rot.y)*ENEMY_NORMALSPEED, 0.0f, cosf(g_Enemy[nEnemy].rot.y)*ENEMY_NORMALSPEED);

	
			if (g_Enemy[nEnemy].fDistanceLeft <= MOVE_DISTANCE_WALL && g_Enemy[nEnemy].fDistanceLeft < g_Enemy[nEnemy].fDistanceRight)
			{
				g_Enemy[nEnemy].move += D3DXVECTOR3(sinf(g_Enemy[nEnemy].rot.y + D3DX_PI * 0.5f)*ENEMY_NORMALSPEED, 0.0f, cosf(g_Enemy[nEnemy].rot.y + D3DX_PI * 0.5f)*ENEMY_NORMALSPEED);
			}
			
			else if (g_Enemy[nEnemy].fDistanceRight <= MOVE_DISTANCE_WALL && g_Enemy[nEnemy].fDistanceRight < g_Enemy[nEnemy].fDistanceLeft)
			{
				g_Enemy[nEnemy].move += D3DXVECTOR3(sinf(g_Enemy[nEnemy].rot.y + D3DX_PI * -0.5f)*ENEMY_NORMALSPEED, 0.0f, cosf(g_Enemy[nEnemy].rot.y + D3DX_PI * -0.5f)*ENEMY_NORMALSPEED);
			}

			g_Enemy[nEnemy].pos += g_Enemy[nEnemy].move;
		}
}
void EnemyDirection(int nEnemy)
{
	int nCount = 0;
	while (1)
	{//�����_���Ɉړ�����������
		nCount++;
		int nRand = rand() % 4;
		if (g_Enemy[nEnemy].fDistanceN >= TURN_DISTANCE_WALL  && nRand == 0 && g_Enemy[nEnemy].MoveState != ENEMYMOVE_S)
		{
			g_Enemy[nEnemy].MoveState = ENEMYMOVE_N;
			break;
		}
		else if (g_Enemy[nEnemy].fDistanceS >= TURN_DISTANCE_WALL  && nRand == 1 && g_Enemy[nEnemy].MoveState != ENEMYMOVE_N)
		{
			g_Enemy[nEnemy].MoveState = ENEMYMOVE_S;
			break;
		}
		else if (g_Enemy[nEnemy].fDistanceW >= TURN_DISTANCE_WALL  && nRand == 2 && g_Enemy[nEnemy].MoveState != ENEMYMOVE_E)
		{
			g_Enemy[nEnemy].MoveState = ENEMYMOVE_W;
			break;
		}
		else if (g_Enemy[nEnemy].fDistanceE >= TURN_DISTANCE_WALL  && nRand == 3 && g_Enemy[nEnemy].MoveState != ENEMYMOVE_W)
		{
			g_Enemy[nEnemy].MoveState = ENEMYMOVE_E;
			break;
		}
		else if (((g_Enemy[nEnemy].MoveState == ENEMYMOVE_N && g_Enemy[nEnemy].fDistanceN < TURN_DISTANCE_WALL ) ||
			(g_Enemy[nEnemy].MoveState == ENEMYMOVE_S && g_Enemy[nEnemy].fDistanceS < TURN_DISTANCE_WALL ) ||
			(g_Enemy[nEnemy].MoveState == ENEMYMOVE_W && g_Enemy[nEnemy].fDistanceW < TURN_DISTANCE_WALL ) ||
			(g_Enemy[nEnemy].MoveState == ENEMYMOVE_E && g_Enemy[nEnemy].fDistanceE < TURN_DISTANCE_WALL )))
		{

			g_Enemy[nEnemy].MoveState = ENEMYMOVE_NONE;
			
			break;
		}
		else if (nCount >= 200)
		{
			g_Enemy[nEnemy].MoveState = ENEMYMOVE_NONE;
			break;		//�e�X�g���̖������[�v���p�ɒǉ����܂����B
		}
		
	}
}

//====================================================================
//���[�V�����̍X�V����
//====================================================================
void UpdateEnemyMotion(int nCnt)
{
	g_Enemy[nCnt].nNumkey = g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].NumKey;

	//�S���f��(�p�[�c)�̍X�V
	for (int nCntModel = 0; nCntModel < g_Enemy[nCnt].nNumModel; nCntModel++)
	{
		//�L�[�̏�񂩂�ʒu�E�������Z�o
		float POSX = g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].g_nNextKey].aKey[nCntModel].fPosX - g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fPosX;
		float POSY = g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].g_nNextKey].aKey[nCntModel].fPosY - g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fPosY;
		float POSZ = g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].g_nNextKey].aKey[nCntModel].fPosZ - g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fPosZ;
		float ROTX = g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].g_nNextKey].aKey[nCntModel].fRotX - g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fRotX;
		float ROTY = g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].g_nNextKey].aKey[nCntModel].fRotY - g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fRotY;
		float ROTZ = g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].g_nNextKey].aKey[nCntModel].fRotZ - g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fRotZ;

		//�p�[�c�̈ʒu�E������ݒ�
		g_Enemy[nCnt].aModel[nCntModel].pos.x = g_Enemy[nCnt].aModel[nCntModel].Setpos.x + g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fPosX + POSX * ((float)g_Enemy[nCnt].nCounterMotion / (float)g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].nFrame);
		g_Enemy[nCnt].aModel[nCntModel].pos.y = g_Enemy[nCnt].aModel[nCntModel].Setpos.y + g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fPosY + POSY * ((float)g_Enemy[nCnt].nCounterMotion / (float)g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].nFrame);
		g_Enemy[nCnt].aModel[nCntModel].pos.z = g_Enemy[nCnt].aModel[nCntModel].Setpos.z + g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fPosZ + POSZ * ((float)g_Enemy[nCnt].nCounterMotion / (float)g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].nFrame);
		g_Enemy[nCnt].aModel[nCntModel].rot.x = g_Enemy[nCnt].aModel[nCntModel].Setrot.x + g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fRotX + ROTX * ((float)g_Enemy[nCnt].nCounterMotion / (float)g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].nFrame);
		g_Enemy[nCnt].aModel[nCntModel].rot.y = g_Enemy[nCnt].aModel[nCntModel].Setrot.y + g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fRotY + ROTY * ((float)g_Enemy[nCnt].nCounterMotion / (float)g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].nFrame);
		g_Enemy[nCnt].aModel[nCntModel].rot.z = g_Enemy[nCnt].aModel[nCntModel].Setrot.z + g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].aKey[nCntModel].fRotZ + ROTZ * ((float)g_Enemy[nCnt].nCounterMotion / (float)g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].nFrame);
	}
	g_Enemy[nCnt].nCounterMotion++;
	if (g_Enemy[nCnt].nCounterMotion >= g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].aKeyInfo[g_Enemy[nCnt].nkey].nFrame)
	{
		g_Enemy[nCnt].nCounterMotion = 0;
		g_Enemy[nCnt].nkey++;
		g_Enemy[nCnt].g_nNextKey++;

		if (g_Enemy[nCnt].g_nNextKey >= g_Enemy[nCnt].nNumkey)
		{
			if (g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].bLoop == true)
			{
				g_Enemy[nCnt].g_nNextKey = 0;
			}
			else
			{
				g_Enemy[nCnt].g_nNextKey = 0;
			}
		}
		if (g_Enemy[nCnt].nkey >= g_Enemy[nCnt].nNumkey)
		{
			if (g_Enemy[nCnt].aMotionInfo[g_Enemy[nCnt].MotionType].bLoop == true)
			{
				g_Enemy[nCnt].nkey = 0;
			}
			else
			{
				g_Enemy[nCnt].nkey = 0;
			}
		}
	}
}

//====================================================================
//���[�V�����̐ݒ菈��
//====================================================================
void SetEnemyMotion(ENEMY_MOTION_TYPE nType, int nCnt)
{
	g_Enemy[nCnt].MotionType = nType;
	g_Enemy[nCnt].bLoopMotion = g_Enemy[nCnt].aMotionInfo[nType].bLoop;	//���[�v���邩�ǂ���
	g_Enemy[nCnt].nNumkey = g_Enemy[nCnt].aMotionInfo[nType].NumKey;		//�L�[�̑���
	g_Enemy[nCnt].nkey = 0;											//���݂̃L�[No.
	g_Enemy[nCnt].nCounterMotion = 0;								//���[�V�����̃J�E���^�[
	g_Enemy[nCnt].g_nNextKey = g_Enemy[nCnt].nkey + 1;
	g_Enemy[nCnt].g_bMotion = false;
}

//====================================================================
//���[�V�����̃��[�h����
//====================================================================
void LoadEnemyMotion(int nEnemyBG)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen("", "r");

	//�t�@�C�����J��
	pFile = fopen("data\\TEXT\\motion_enemy.txt", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		int nCntModel = 0;
		int nCntParts = 0;
		int nCntMotion = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;

		char aString[128] = {};				//�S�~��
		char aStartMessage[128] = {};		//�X�^�[�g���b�Z�[�W
		char aModelMessage[128] = {};		//���f���p���b�Z�[�W
		char aCharaSetMessage[128] = {};	//�L�����Z�b�g���b�Z�[�W
		char aPartsSetMessage[128] = {};	//�p�[�c�Z�b�g���b�Z�[�W
		char aMotionSetMessage[128] = {};	//���[�V�����Z�b�g���b�Z�[�W
		char KeySetMessage[128] = {};		//�L�[�Z�b�g���b�Z�[�W
		char KeyStartMessage[128] = {};		//�L�[�X�^�[�g���b�Z�[�W
		char aNameMessage[128] = {};		//�ϐ����̃��b�Z�[�W
		char aPartsEndMessage[128] = {};	//�p�[�c�G���h���b�Z�[�W
		char aCharaEndMessage[128] = {};	//�L�����G���h���b�Z�[�W
		char aEndMessage[128] = {};			//�I�����b�Z�[�W
		char aType[128] = {};				//�I�����b�Z�[�W
		char aBool[128] = {};				//bool�ϊ��p���b�Z�[�W

											// �ǂݍ��݊J�n-----------------------------------------------------
		while (1)
		{//�uSCRIPT�v��T��
			fscanf(pFile, "%s", &aStartMessage[0]);
			if (strcmp(&aStartMessage[0], "SCRIPT") == 0)
			{
				// ���f�����ǂݍ���-----------------------------------------------------
				while (1)
				{//�uNUM_MODEL�v��T��
					fscanf(pFile, "%s", &aModelMessage[0]);
					if (strcmp(&aModelMessage[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Enemy[nEnemyBG].nNumModel);		//���f�����̐ݒ�
						break;
					}
				}

				// �L�����N�^�[���ǂݍ���-----------------------------------------------------
				while (1)
				{//�uPARTSSET�v��T��
					fscanf(pFile, "%s", &aPartsSetMessage[0]);
					if (strcmp(&aPartsSetMessage[0], "PARTSSET") == 0)
					{
						while (1)
						{//�e��ϐ���T��
							fscanf(pFile, "%s", &aNameMessage[0]);
							if (strcmp(&aNameMessage[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &nCntModel);	//�C���f�b�N�X��ݒ�
							}
							if (strcmp(&aNameMessage[0], "PARENT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Enemy[nEnemyBG].aModel[nCntModel].nIndexModelParent);	//�e���f���̃C���f�b�N�X��ݒ�
							}
							if (strcmp(&aNameMessage[0], "POS") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aModel[nCntModel].Setpos.x);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aModel[nCntModel].Setpos.y);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aModel[nCntModel].Setpos.z);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
							}
							if (strcmp(&aNameMessage[0], "ROT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aModel[nCntModel].Setrot.x);				////�����̏����ݒ�
								fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aModel[nCntModel].Setrot.y);				////�����̏����ݒ�
								fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aModel[nCntModel].Setrot.z);				////�����̏����ݒ�
							}
							if (strcmp(&aNameMessage[0], "END_PARTSSET") == 0)
							{
								break;
							}
						}
						nCntModel++;
						if (nCntModel >= g_Enemy[nEnemyBG].nNumModel)
						{
							break;
						}
					}
				}

				// ���[�V�������ǂݍ���-----------------------------------------------------
				while (1)
				{//�uMOTIONSET�v��T��
					fscanf(pFile, "%s", &aMotionSetMessage[0]);
					if (strcmp(&aMotionSetMessage[0], "MOTIONSET") == 0)
					{
						while (1)
						{//�e��ϐ���T��
							fscanf(pFile, "%s", &aNameMessage[0]);
							if (strcmp(&aNameMessage[0], "LOOP") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%s", &aBool[0]);	//���[�v���邩�ǂ�����ݒ�
								g_Enemy[nEnemyBG].aMotionInfo[nCntMotion].bLoop = (strcmp(&aBool[0], "1") == 0 ? true : false);			//bool�^�̏�����
							}
							if (strcmp(&aNameMessage[0], "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Enemy[nEnemyBG].aMotionInfo[nCntMotion].NumKey);	//�L�[�̑�����ݒ�
								break;
							}
						}

						// �L�[���ǂݍ���-----------------------------------------------------
						while (1)
						{//�uKEYSET�v��T��
							fscanf(pFile, "%s", &KeySetMessage[0]);
							if (strcmp(&KeySetMessage[0], "KEYSET") == 0)
							{
								while (1)
								{//�uFRAME�v��T��
									fscanf(pFile, "%s", &aNameMessage[0]);
									if (strcmp(&aNameMessage[0], "FRAME") == 0)
									{
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &g_Enemy[nEnemyBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].nFrame);	//�L�[�t���[����ݒ�
										break;
									}
								}

								while (1)
								{//�uKEY�v��T��
									fscanf(pFile, "%s", &KeyStartMessage[0]);
									if (strcmp(&KeyStartMessage[0], "KEY") == 0)
									{
										while (1)
										{//�e��ϐ���T��
											fscanf(pFile, "%s", &aNameMessage[0]);
											if (strcmp(&aNameMessage[0], "POS") == 0)
											{
												fscanf(pFile, "%s", &aString[0]);
												fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fPosX);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fPosY);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fPosZ);	//�ʒu��ݒ�
											}
											if (strcmp(&aNameMessage[0], "ROT") == 0)
											{
												fscanf(pFile, "%s", &aString[0]);
												fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fRotX);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fRotY);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &g_Enemy[nEnemyBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fRotZ);	//�ʒu��ݒ�
												break;
											}
										}
									}
									if (strcmp(&KeyStartMessage[0], "END_KEY") == 0)
									{
										nCntKey++;
										if (nCntKey >= g_Enemy[nEnemyBG].nNumModel)
										{
											break;
										}
									}
								}
							}
							if (strcmp(&KeySetMessage[0], "END_KEYSET") == 0)
							{
								nCntKey = 0;
								nCntKeySet++;
								if (nCntKeySet >= g_Enemy[nEnemyBG].aMotionInfo[nCntMotion].NumKey)
								{
									break;
								}
							}
						}
					}
					if (strcmp(&aMotionSetMessage[0], "END_MOTIONSET") == 0)
					{
						nCntKeySet = 0;
						nCntMotion++;
						if (nCntMotion >= ENEMY_ACTION_MAX)
						{
							break;
						}
					}
				}
			}
			if (strcmp(&aStartMessage[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}