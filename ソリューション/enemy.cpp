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

#define ENEMY_LIFE (7)		//�I�u�W�F�N�g�̗̑�
#define ENEMY_SPEED (3.0f) //�G�̈ړ����x

#define	DETECT_SPEED (5.0f) //�T���g�̑��x
#define	PLAYERDETECT_SPEED (15.0f) //�T���g�̑��x

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureENEMY[64][ENEMY_NTYPE_MAX] = {};	//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshENEMY[ENEMY_NTYPE_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatENEMY[ENEMY_NTYPE_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatENEMY[ENEMY_NTYPE_MAX] = {};						//�}�e���A���̐�

ENEMY g_Enemy[MAX_ENEMY];					//�G�̏��
int EditIndexEnemy;								//�G�f�B�b�g���[�h�p�̔ԍ�

//�v���g�^�C�v�錾
void EnemyPatrol(int nEnemy);
void EnemyDirection(int nEnemy);

const char *c_apModelEnemy[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\wall.x",
	"Data\\MODEL\\pc.x",
	"Data\\MODEL\\desk.x",
	"Data\\MODEL\\fan.x",
	"Data\\MODEL\\locker.x",
	"Data\\MODEL\\whiteboard.x",
	"Data\\MODEL\\officechair.x",
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
		g_Enemy[nCntObject].nType = ENEMY_NTYPE00;
		g_Enemy[nCntObject].state = ENEMYSTATE_PATROL;
		g_Enemy[nCntObject].StateCount = 0;
		g_Enemy[nCntObject].nCoolTurn = 0;

		g_Enemy[nCntObject].aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].aModel[0].nType = 0;
		g_Enemy[nCntObject].aModel[0].nIdxModelParent = -1;

		g_Enemy[nCntObject].aModel[1].pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		g_Enemy[nCntObject].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntObject].aModel[1].nType = 0;
		g_Enemy[nCntObject].aModel[1].nIdxModelParent = 0;
	}
	EditIndexEnemy = 0;

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_NTYPE_MAX; nCntEnemy++)
	{
		D3DXLoadMeshFromX(c_apModelEnemy[nCntEnemy],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatENEMY[nCntEnemy],
			NULL,
			&g_dwNumMatENEMY[nCntEnemy],
			&g_pMeshENEMY[nCntEnemy]);
	}

	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < ENEMY_NTYPE_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureENEMY[nCntMat][nCntNumObject]);
			}
		}
	}
}

//====================================================================
//�G�̏I������
//====================================================================
void UninitEnemy(void)
{
	for (int nCntNumObject = 0; nCntNumObject < ENEMY_NTYPE_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureENEMY[nCntTex][nCntNumObject] != NULL)
			{
				g_pTextureENEMY[nCntTex][nCntNumObject]->Release();
				g_pTextureENEMY[nCntTex][nCntNumObject] = NULL;
			}
		}

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

//====================================================================
//�G�̍X�V����
//====================================================================
void UpdateEnemy(void)
{
	for (int nCntObject = 0; nCntObject < MAX_ENEMY; nCntObject++)
	{
		if (g_Enemy[nCntObject].bUse == true)
		{
			g_Enemy[nCntObject].posOld = g_Enemy[nCntObject].pos;
			g_Enemy[nCntObject].StateCount--;
			g_Enemy[nCntObject].nCoolTurn--;
		

			//�p�x�̏C���i���j
			if (g_Enemy[nCntObject].rotDest.y - g_Enemy[nCntObject].rot.y > D3DX_PI || g_Enemy[nCntObject].rotDest.y - g_Enemy[nCntObject].rot.y < -D3DX_PI)
			{
				g_Enemy[nCntObject].rot.y -= (g_Enemy[nCntObject].rotDest.y - g_Enemy[nCntObject].rot.y) * 0.03f;
			}
			else
			{
				g_Enemy[nCntObject].rot.y += (g_Enemy[nCntObject].rotDest.y - g_Enemy[nCntObject].rot.y) * 0.3f;
			}
		

			//�����]���̃N�[���^�C��
			if (g_Enemy[nCntObject].nCoolTurn <= 0)
			{
				g_Enemy[nCntObject].nCoolTurn = 0;
			}

			//�v���C���[�T�m
			if (g_Enemy[nCntObject].state != ENEMYSTATE_ATTACK)
			{
				for (int nDetect = 0; nDetect < 6; nDetect++)
				{
					float DetectRot = g_Enemy[nCntObject].rot.y - D3DXToRadian(45.0f) + D3DXToRadian(15.0f * nDetect);
					if (DetectPlayer(&g_Enemy[nCntObject].Tgpos, g_Enemy[nCntObject].pos, DetectRot, 400) == true)
					{
						g_Enemy[nCntObject].state = ENEMYSTATE_CHASE;
						break;
					}
				}
			}
			
			if (g_Enemy[nCntObject].state == ENEMYSTATE_PATROL)
			{
				EnemyPatrol(nCntObject);

				CollisionObject00(&g_Enemy[nCntObject].pos, &g_Enemy[nCntObject].posOld, &g_Enemy[nCntObject].move, D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1.0f);

			}

			if (g_Enemy[nCntObject].state == ENEMYSTATE_CHASE)
			{//�ǐՏ�Ԃ̎�
				//�v���C���[�̃|�C���^���擾
				Player*pPlayer = GetPlayer();
				//�x�N�g�������߂�
				D3DXVECTOR3 vecEnemy = g_Enemy[nCntObject].Tgpos - g_Enemy[nCntObject].pos ;
				vecEnemy.y = atan2f(vecEnemy.x, vecEnemy.z);
				
				PrintDebugProc("���W�Fx%fz%f\n", g_Enemy[nCntObject].pos.x, g_Enemy[nCntObject].pos.z);
				PrintDebugProc("�ڕW���W�Fx%fz%f\n", g_Enemy[nCntObject].Tgpos.x, g_Enemy[nCntObject].Tgpos.z);
				PrintDebugProc("�ړ��p�x�F%f\n",vecEnemy.y);
				g_Enemy[nCntObject].rotDest = vecEnemy;
				//���W�̍X�V
			
				g_Enemy[nCntObject].move = D3DXVECTOR3(sinf(g_Enemy[nCntObject].rot.y)*ENEMY_SPEED, 0.0f, cosf(g_Enemy[nCntObject].rot.y)*ENEMY_SPEED);
				g_Enemy[nCntObject].pos += g_Enemy[nCntObject].move;
		
				//�ڕW�n�_�ɓ��B�����Ƃ�
				if (vecEnemy.x < 10.0f && vecEnemy.x > -10.0f && vecEnemy.z < 10.0f && vecEnemy.z > -10.0f)
				{//�T����Ԃɐ؂�ւ���
					g_Enemy[nCntObject].state = ENEMYSTATE_SEEK;
					g_Enemy[nCntObject].StateCount = 30;
				
				}
				D3DXVECTOR3	vecPlayer;
				for (int nCnt = 0; nCnt < 4; nCnt++,pPlayer++)
				{
					if (pPlayer->bUse == true)
					{
						vecPlayer = pPlayer->pos - g_Enemy[nCntObject].pos;
						//�ڕW�n�_�ɓ��B�����Ƃ�
						if (vecPlayer.x < 10.0f && vecPlayer.x > -10.0f && vecPlayer.z < 10.0f && vecPlayer.z > -10.0f)
						{
							g_Enemy[nCntObject].state = ENEMYSTATE_ATTACK;
							g_Enemy[nCntObject].StateCount = 30;
							PlayerHit(nCnt, 1);
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

			if (g_Enemy[nCntObject].StateCount <= 0)
			{
				g_Enemy[nCntObject].StateCount = 0;
				switch (g_Enemy[nCntObject].state)
				{
				case ENEMYSTATE_SEEK:
					g_Enemy[nCntObject].state = ENEMYSTATE_PATROL;
					break;
				case ENEMYSTATE_ATTACK:
					g_Enemy[nCntObject].state = ENEMYSTATE_PATROL;
					break;
				default:
					break;
				}
			}
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
		for (nCntObject = 0; nCntObject < NUM_ENEMYMODEL; nCntObject++)
		{
			D3DXMATRIX mtxParent;
			D3DXMATRIX mtxRotModel, mtxTransModel; //�v�Z�p�}�g���N�X

												   //�p�[�c�̃}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.y, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.x, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].mtx, &g_Enemy[nCntObjectModel].mtx, &mtxRotModel);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.x, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.y, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &mtxTransModel);

			//�e�̃}�g���N�X�̐ݒ�
			if (g_Enemy[nCntObjectModel].aModel[nCntObject].nIdxModelParent != -1)
			{
				mtxParent = g_Enemy[nCntObjectModel].aModel[g_Enemy[nCntObjectModel].aModel[nCntObject].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_Enemy[nCntObjectModel].mtx;
			}

			//�Z�o�����}�g���N�X���������킹��
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &mtxParent);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld);

			//���݂̃}�e���A��������
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^����������
			pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[g_Enemy[nCntObjectModel].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[g_Enemy[nCntObjectModel].nType]; nCntMat++)
			{

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Enemy[nCntObjectModel].bUse == true)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureENEMY[nCntMat][g_Enemy[nCntObjectModel].aModel[nCntObject].nType]);

					//�G(�p�[�c)�̕`��
					g_pMeshENEMY[g_Enemy[nCntObjectModel].aModel[nCntObject].nType]->DrawSubset(nCntMat);
				}
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̓G�̍X�V����
//====================================================================
void UpdateEditEnemy(void)
{
	//�L�[�{�[�h�̈ړ�����
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Enemy[EditIndexEnemy].pos.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Enemy[EditIndexEnemy].pos.z -= 1.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Enemy[EditIndexEnemy].pos.x += 1.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Enemy[EditIndexEnemy].pos.x -= 1.0f;
	}

	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_Enemy[EditIndexEnemy].rot.y += 1.57f;

		if (g_Enemy[EditIndexEnemy].rot.y >= 6.28f)
		{
			g_Enemy[EditIndexEnemy].rot.y = 0.0f;
		}
	}

	if (GetKeyboardTrigger(DIK_RSHIFT) == true)
	{
		g_Enemy[EditIndexEnemy].nType++;

		if (g_Enemy[EditIndexEnemy].nType > ENEMY_NTYPE_MAX - 1)
		{
			g_Enemy[EditIndexEnemy].nType = 0;
		}
	}
	if (GetKeyboardTrigger(DIK_RCONTROL) == true)
	{
		g_Enemy[EditIndexEnemy].nType--;

		if (g_Enemy[EditIndexEnemy].nType < 0)
		{
			g_Enemy[EditIndexEnemy].nType = ENEMY_NTYPE_MAX - 1;
		}
	}


	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetEnemy(g_Enemy[EditIndexEnemy].pos, g_Enemy[EditIndexEnemy].move, g_Enemy[EditIndexEnemy].rot, g_Enemy[EditIndexEnemy].nType);
	}
}

//====================================================================
//�G�f�B�b�g���[�h�̓G�̕`�揈��
//====================================================================
void DrawEditEnemy(void)
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
		for (nCntObject = 0; nCntObject < NUM_ENEMYMODEL; nCntObject++)
		{
			D3DXMATRIX mtxParent;
			D3DXMATRIX mtxRotModel, mtxTransModel; //�v�Z�p�}�g���N�X

												   //�p�[�c�̃}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.y, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.x, g_Enemy[nCntObjectModel].aModel[nCntObject].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].mtx, &g_Enemy[nCntObjectModel].mtx, &mtxRotModel);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.x, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.y, g_Enemy[nCntObjectModel].aModel[nCntObject].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &mtxTransModel);

			//�e�̃}�g���N�X�̐ݒ�
			if (g_Enemy[nCntObjectModel].aModel[nCntObject].nIdxModelParent != -1)
			{
				mtxParent = g_Enemy[nCntObjectModel].aModel[g_Enemy[nCntObjectModel].aModel[nCntObject].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_Enemy[nCntObjectModel].mtx;
			}

			//�Z�o�����}�g���N�X���������킹��
			D3DXMatrixMultiply(&g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld, &mtxParent);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntObjectModel].aModel[nCntObject].mtxWorld);

			//���݂̃}�e���A��������
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^����������
			pMat = (D3DXMATERIAL*)g_pBuffMatENEMY[g_Enemy[nCntObjectModel].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatENEMY[g_Enemy[nCntObjectModel].nType]; nCntMat++)
			{

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_Enemy[nCntObjectModel].bUse == true)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureENEMY[nCntMat][g_Enemy[nCntObjectModel].aModel[nCntObject].nType]);

					//�G(�p�[�c)�̕`��
					g_pMeshENEMY[g_Enemy[nCntObjectModel].aModel[nCntObject].nType]->DrawSubset(nCntMat);
				}
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//====================================================================
//�G�̐ݒ菈��
//====================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nType)
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
			g_Enemy[nCntObject].nType = nType;

			//switch (nType)
			//{
			//case 0:
			//	g_Enemy[nCntObject].nType = ENEMY_NTYPE00;
			//	break;
			//}

			g_Enemy[nCntObject].bUse = true;
			EditIndexEnemy++;

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

//====================================================================
//�G�̎擾
//====================================================================
ENEMY * GetEnemy(void)
{
	return &g_Enemy[0];
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
	Detect.nLife = nLife;

	while (1)
	{
		Detect.posOld = Detect.pos;
		Detect.move = D3DXVECTOR3(sinf(Detect.fmoveRot)*DETECT_SPEED, 0.0f, cosf(Detect.fmoveRot)*DETECT_SPEED);
		Detect.pos += Detect.move;
		Detect.nLife--;
		
		if (CollisionObject00(&Detect.pos, &Detect.posOld, &Detect.move, D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1.0f) == true)
		{//�ǂɓ��������Ƃ�
		 //����������o��
			float fDis = ((powf(Detect.Startpos.x, 2.0f) + powf(Detect.Startpos.z, 2.0f)) - (powf(Detect.pos.x, 2.0f) + powf(Detect.pos.z, 2.0f)));
			if (fDis <= 0)
			{
				fDis *= -1.0f;
			}
			Detect.fDistance = sqrtf(fDis);
			SetEffect(Detect.pos, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 60, 0);
			return Detect.fDistance;
		}

		if (Detect.nLife <= 0)
		{
			return FLT_MAX;
		}
	}
}

//====================================================================
//�v���C���[�̒T��
//====================================================================
bool DetectPlayer(D3DXVECTOR3*postg, D3DXVECTOR3 pos, float fmoveRot, int nLife)
{
	DETECT Detect;
	Player*pPlayer = GetPlayer();
	Detect.Startpos = pos;
	Detect.pos = pos;
	Detect.fmoveRot = fmoveRot;
	Detect.nLife = nLife;

	while (1)
	{
		Detect.posOld = Detect.pos;
		Detect.move = D3DXVECTOR3(sinf(Detect.fmoveRot)*PLAYERDETECT_SPEED, 0.0f, cosf(Detect.fmoveRot)*PLAYERDETECT_SPEED);
		Detect.pos += Detect.move;
		Detect.nLife--;

		if (CollisionObject00(&Detect.pos, &Detect.posOld, &Detect.move, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f) == true)
		{//�ǂɓ��������Ƃ�
		 //����������o��
			float fDis = (powf(Detect.Startpos.x, 2.0f) + powf(Detect.Startpos.z, 2.0f) - (powf(Detect.pos.x, 2.0f)) + powf(Detect.pos.z, 2.0f));
			if (fDis <= 0)
			{
				fDis *= -1.0f;
			}
			Detect.fDistance = sqrtf(fDis);
			return false;
		}
		Detect.nTarget = CollisionPlayer(Detect.pos, Detect.posOld, 1.0f, 0.0f, 0.0f);
		if (Detect.nTarget  > -1)
		{
			for (int nCntPlayer = 0; nCntPlayer < Detect.nTarget; nCntPlayer++)
			{
				pPlayer++;
			}
			*postg = pPlayer->pos;
			return true;

		}
		if (Detect.nLife <= 0)
		{
			return false;
		}
	}
}
//====================================================================
//���񏈗�
//====================================================================
void EnemyPatrol(int nEnemy)
{
	
		//�e���ʂɂ���ǂƂ̋����𑪒�
		g_Enemy[nEnemy].fDistanceN = DetectWall(g_Enemy[nEnemy].pos, 0.0f, 100);
		g_Enemy[nEnemy].fDistanceS = DetectWall(g_Enemy[nEnemy].pos, D3DX_PI, 100);
		g_Enemy[nEnemy].fDistanceW = DetectWall(g_Enemy[nEnemy].pos, D3DX_PI*-0.5f, 100);
		g_Enemy[nEnemy].fDistanceE = DetectWall(g_Enemy[nEnemy].pos, D3DX_PI*0.5f, 100);
		g_Enemy[nEnemy].fDistanceFront = DetectWall(g_Enemy[nEnemy].pos, g_Enemy[nEnemy].rot.y, 500);
		g_Enemy[nEnemy].fDistanceLeft = DetectWall(g_Enemy[nEnemy].pos, g_Enemy[nEnemy].rot.y + D3DX_PI*-0.5f, 100);
		g_Enemy[nEnemy].fDistanceRight = DetectWall(g_Enemy[nEnemy].pos, g_Enemy[nEnemy].rot.y + D3DX_PI*0.5f, 100);

		PrintDebugProc("\nEnemy%d�k:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceN);
		PrintDebugProc("Enemy%d��:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceS);
		PrintDebugProc("Enemy%d��:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceW);
		PrintDebugProc("Enemy%d��:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceE);

		PrintDebugProc("\nEnemy%d�E:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceRight);
		PrintDebugProc("Enemy%d��:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceLeft);
		PrintDebugProc("Enemy%d�O:%f\n", nEnemy, g_Enemy[nEnemy].fDistanceFront);

		//���g�̐i�ޕ����ɕǂ��������ꍇ
		if (((g_Enemy[nEnemy].MoveState == ENEMYMOVE_N && g_Enemy[nEnemy].fDistanceN <= 150.0f) ||
			(g_Enemy[nEnemy].MoveState == ENEMYMOVE_S && g_Enemy[nEnemy].fDistanceS <= 150.0f) ||
			(g_Enemy[nEnemy].MoveState == ENEMYMOVE_E && g_Enemy[nEnemy].fDistanceE <= 150.0f) ||
			(g_Enemy[nEnemy].MoveState == ENEMYMOVE_W && g_Enemy[nEnemy].fDistanceW <= 150.0f) ||
			 g_Enemy[nEnemy].MoveState == ENEMYMOVE_NONE))
		{
			EnemyDirection(nEnemy);
			g_Enemy[nEnemy].nCoolTurn = 30;

		}
		


		if (g_Enemy[nEnemy].fDistanceLeft >= 500.0f && 	g_Enemy[nEnemy].nCoolTurn <= 0)
		{
			EnemyDirection(nEnemy);
			g_Enemy[nEnemy].nCoolTurn = 120;
		}
		if (g_Enemy[nEnemy].fDistanceRight >= 500.0f&& 	g_Enemy[nEnemy].nCoolTurn <= 0)
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
			g_Enemy[nEnemy].move = D3DXVECTOR3(sinf(g_Enemy[nEnemy].rot.y)*ENEMY_SPEED, 0.0f, cosf(g_Enemy[nEnemy].rot.y)*ENEMY_SPEED);

			if (g_Enemy[nEnemy].fDistanceLeft <= 300.0f && g_Enemy[nEnemy].fDistanceLeft <= g_Enemy[nEnemy].fDistanceRight)
			{
				g_Enemy[nEnemy].move += D3DXVECTOR3(sinf(g_Enemy[nEnemy].rot.y + D3DX_PI * 0.5f)*ENEMY_SPEED, 0.0f, cosf(g_Enemy[nEnemy].rot.y + D3DX_PI * 0.5f)*ENEMY_SPEED);
			}
			else if (g_Enemy[nEnemy].fDistanceRight <= 300.0f && g_Enemy[nEnemy].fDistanceRight <= g_Enemy[nEnemy].fDistanceLeft)
			{
				g_Enemy[nEnemy].move += D3DXVECTOR3(sinf(g_Enemy[nEnemy].rot.y + D3DX_PI * -0.5f)*ENEMY_SPEED, 0.0f, cosf(g_Enemy[nEnemy].rot.y + D3DX_PI * -0.5f)*ENEMY_SPEED);
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
		if (g_Enemy[nEnemy].fDistanceN >= 150.0f && nRand == 0 && g_Enemy[nEnemy].MoveState != ENEMYMOVE_S)
		{
			g_Enemy[nEnemy].MoveState = ENEMYMOVE_N;
			break;
		}
		else if (g_Enemy[nEnemy].fDistanceS >= 150.0f && nRand == 1 && g_Enemy[nEnemy].MoveState != ENEMYMOVE_N)
		{
			g_Enemy[nEnemy].MoveState = ENEMYMOVE_S;
			break;
		}
		else if (g_Enemy[nEnemy].fDistanceW >= 150.0f && nRand == 2 && g_Enemy[nEnemy].MoveState != ENEMYMOVE_E)
		{
			g_Enemy[nEnemy].MoveState = ENEMYMOVE_W;
			break;
		}
		else if (g_Enemy[nEnemy].fDistanceE >= 150.0f && nRand == 3 && g_Enemy[nEnemy].MoveState != ENEMYMOVE_W)
		{
			g_Enemy[nEnemy].MoveState = ENEMYMOVE_E;
			break;
		}
		else if (((g_Enemy[nEnemy].MoveState == ENEMYMOVE_N && g_Enemy[nEnemy].fDistanceN < 150.0f) ||
			(g_Enemy[nEnemy].MoveState == ENEMYMOVE_S && g_Enemy[nEnemy].fDistanceS < 150.0f) ||
			(g_Enemy[nEnemy].MoveState == ENEMYMOVE_W && g_Enemy[nEnemy].fDistanceW < 150.0f) ||
			(g_Enemy[nEnemy].MoveState == ENEMYMOVE_E && g_Enemy[nEnemy].fDistanceE < 150.0f)))
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