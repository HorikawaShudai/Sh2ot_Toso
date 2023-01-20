//============================
//
//�X�R�A�A�C�e������(model.cpp)
//Author:���� �F�M
//
//============================
#include "main.h"
#include "camera.h"
//#include "shadow.h"
//#include "enemy.h"
#include "player.h"
#include "score.h"
#include "score_item.h"

//�}�N����`
#define NUM_ITEM (100)  //�g���A�C�e���̗�

//�O���[�o��
ITEM g_Item[MAX_ITEM]; //�X�R�A�A�C�e���̏��
ITEMDATA g_Itemdata[NUM_ITEM]; //�X�R�A�A�C�e���f�[�^
int ItemCnt;  //�X�R�A�A�C�e���̐�
FILE *pFile;
//int g_BulletCnt;							//�e�̐��𐔂���
//int g_nldxShadow = -1; //�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)

//====================
//�X�R�A�A�C�e���̏�����
//====================
void InitItem(void)
{
	int nCntItem;

	int nNumVtx;  //���_��

	DWORD dwSizeFVF;  //���_�t�H�[�}�b�g�̃T�C�Y

	BYTE *pVtxBUff;  //���_�o�b�t�@�̃|�C���^

	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		//�e��ϐ��̏�����
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�A�C�e���̈ʒu��������
		g_Item[nCntItem].bUse = false;  //�g���Ă��邩�ǂ�����������
	}
	//g_BulletCnt = 0;

	////�e��ݒ�
	//g_nldxShadow = SetShadow();


	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("Data\\MODEL\\jewelry.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Itemdata[0].pBuffMat,
		NULL,
		&g_Itemdata[0].dwNumMat,
		&g_Itemdata[0].pMesh);

	D3DXMATERIAL *pMat; //�}�e���A���ւ̃|�C���^

						//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Itemdata[0].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Itemdata[0].dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C���l�[�������݂���
		 //�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Itemdata[0]._apTexture[nCntMat]);
		}
	}

	////X�t�@�C���̓ǂݍ���
	//D3DXLoadMeshFromX("data\\MODEL\\sword.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_pBuffMatEnemy[1],
	//	NULL,
	//	&g_dwNumMatEnemy[1],
	//	&g_pMeshEnemy[1]);

	////X�t�@�C���̓ǂݍ���
	//D3DXLoadMeshFromX("data\\MODEL\\apart.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_pBuffMatEnemy[2],
	//	NULL,
	//	&g_dwNumMatEnemy[2],
	//	&g_pMeshEnemy[2]);

	//���_���̎擾
	nNumVtx = g_Itemdata[0].pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_Itemdata[0].pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	g_Itemdata[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

	//�X�R�A�A�C�e���̍ő�l�E�ŏ��l�𔲂��o��
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

		if (vtx.x > g_Item[0].VtxMax.x)
		{
			g_Itemdata[0].VtxMax.x = vtx.x;
		}

		if (vtx.x <g_Item[0].VtxMin.x)
		{
			g_Itemdata[0].VtxMin.x = vtx.x;
		}

		if (vtx.y > g_Item[0].VtxMax.y)
		{
			g_Itemdata[0].VtxMax.y = vtx.y;
		}

		if (vtx.y < g_Item[0].VtxMin.y)
		{
			g_Itemdata[0].VtxMin.y = vtx.y;
		}

		if (vtx.z > g_Item[0].VtxMax.z)
		{
			g_Itemdata[0].VtxMax.z = vtx.z;
		}

		if (vtx.z < g_Item[0].VtxMin.z)
		{
			g_Itemdata[0].VtxMin.z = vtx.z;
		}

		pVtxBUff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���ڂ����i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_Itemdata[0].pMesh->UnlockVertexBuffer();
}

//====================
//�X�R�A�A�C�e���̏I������
//====================
void UninitItem(void)
{
	for (int nCntdata = 0; nCntdata < NUM_ITEM; nCntdata++)
	{
		//���b�V���̔j��
		if (g_Itemdata[nCntdata].pMesh != NULL)
		{
			g_Itemdata[nCntdata].pMesh->Release();
			g_Itemdata[nCntdata].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_Itemdata[nCntdata].pBuffMat != NULL)
		{
			g_Itemdata[nCntdata].pBuffMat->Release();
			g_Itemdata[nCntdata].pBuffMat = NULL;
		}

		for (int nCntTex = 0; nCntTex < 20; nCntTex++)
		{
			if (g_Itemdata[nCntdata]._apTexture[nCntTex] != NULL)
			{
				g_Itemdata[nCntdata]._apTexture[nCntTex]->Release();
				g_Itemdata[nCntdata]._apTexture[nCntTex] = NULL;
			}
		}
	}
}

////====================
////�X�R�A�A�C�e���̍X�V����
////====================
//void UpdateItem(void)
//{
//	int nCntItem;
//
//	if (ItemCnt <= 0)
//	{
//		//�X�R�A�A�C�e���̃��X�|�[������
//		ReturnItem();
//	}
//
//	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
//	{
//		if (g_Item[nCntItem].bUse == true)
//		{
//			//�Â��ʒu���X�V
//			g_Item[nCntItem].posold = g_Item[nCntItem].pos;
//
//		}
//	}
//
//	//�X�R�A�A�C�e���̊p�x
//	AngleEnemy();
//
//	//�X�R�A�A�C�e���̏��
//	EnemyState();
//}
//
////====================
////�X�R�A�A�C�e���̕`�揈��
////====================
//void DrawItem(void)
//{
//	int nCnt;
//
//	//�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
//
//	D3DMATERIAL9 matDef;  //���݂̃}�e���A���ۑ��p
//
//	D3DXMATERIAL *pMat;	  //�}�e���A���f�[�^�ւ̃|�C���^
//
//						  /*D3DXMATERIAL *RedMat;*/
//
//						  /*RedMat->MatD3D.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//						  RedMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//						  RedMat->MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);*/
//
//
//	for (nCnt = 0; nCnt < NUM_ITEM; nCnt++)
//	{
//		if (g_Item[nCnt].bUse == true)
//		{
//			//���[���h�}�g���b�N�X�̏�����
//			D3DXMatrixIdentity(&g_Item[nCnt].mtxWorld);
//
//			//�����𔽉f
//			D3DXMatrixRotationYawPitchRoll(&mtxRot,
//				g_Item[nCnt].rot.y, g_Item[nCnt].rot.x, g_Item[nCnt].rot.z);
//
//			D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld,
//				&g_Item[nCnt].mtxWorld,
//				&mtxRot);
//
//			//�ʒu�𔽉f
//			D3DXMatrixTranslation(&mtxTrans,
//				g_Item[nCnt].pos.x, g_Item[nCnt].pos.y, g_Item[nCnt].pos.z);
//
//			D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxTrans);
//
//			//���[���h�}�g���b�N�X�̐ݒ�
//			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCnt].mtxWorld);
//
//			//���݂̃}�e���A�����擾
//			pDevice->GetMaterial(&matDef);
//
//			//�}�e���A���f�[�^�ւ̃|�C���^���擾
//			pMat = (D3DXMATERIAL*)g_Item[nCnt].Itemdata.pBuffMat->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_Item[nCnt].Itemdata.dwNumMat; nCntMat++)
//			{
//				//�e�N�X�`���̐ݒ�
//				pDevice->SetTexture(0, g_Itemdata[nCnt]._apTexture[nCntMat]);
//
//				//�X�R�A�A�C�e��(�p�[�c)�̕`��
//				g_Item[nCnt].Itemdata.pMesh->DrawSubset(nCntMat);
//			}
//
//			//�ۑ����Ă����}�e���A����߂�
//			pDevice->SetMaterial(&matDef);
//		}
//	}
//}
//
////======================================
////�X�R�A�A�C�e���̐ݒ�
////======================================
//void SetEnemy(D3DXVECTOR3 pos)
//{
//	int nCnt;
//
//	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾
//
//	for (nCnt = 0; nCnt < NUM_ITEM; nCnt++)
//	{
//		if (g_Item[nCnt].bUse == false)
//		{
//			g_Item[nCnt].pos = pos;
//			g_Item[nCnt].bUse = true;
//
//			g_Item[nCnt].Itemdata.pBuffMat = g_Item[0].Itemdata.pBuffMat;
//			g_Item[nCnt].Itemdata.dwNumMat = g_Item[0].Itemdata.dwNumMat;
//
//			g_Item[nCnt].Itemdata.pMesh = g_Item[0].Itemdata.pMesh;
//
//			for (int nCntMat = 0; nCntMat < 20; nCntMat++)
//			{
//				g_Item[nCnt].Itemdata._apTexture[nCntMat] = g_Itemdata[0]._apTexture[nCntMat];
//			}
//
//			//�X�R�A�A�C�e���̐��𐔂��鏈��
//			ItemCnt++;
//
//			break;
//		}
//	}
//
//}

////====================================
////�X�R�A�A�C�e���̏����擾
////====================================
//ENEMY *GetEnemy(void)
//{
//	return &g_Enemy[0];
//}

////===========================================
////�X�R�A�A�C�e���̃q�b�g����
////===========================================
//void HitEnemy(int nCntEnemy, int nDamage)
//{
//	//int nCntRed;  //�Ԃ���Ԃ𐔂��鏈��
//
//	g_Enemy[nCntEnemy].nLife -= nDamage;
//
//	if (g_Enemy[nCntEnemy].nLife <= 0)
//	{//�X�R�A�A�C�e�������񂾏���
//
//	 /*SetExplosion(g_Enemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/
//		SetParticle(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, (g_Enemy[nCntEnemy].pos.y), g_Enemy[nCntEnemy].pos.z),
//			D3DXVECTOR3(g_Enemy[nCntEnemy].move.x, g_Enemy[nCntEnemy].move.y + MOVE_PPARTICL, g_Enemy[nCntEnemy].move.z),
//			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
//			1.0f,
//			PARTICLE_DAMAGE,
//			PARTICLE_PUSELIF);
//
//		//�X�R�A�����Z���鏈��
//		AddScore(g_Enemy[nCntEnemy].type);
//
//		//�e����������
//		ResetShadow(g_Enemy[nCntEnemy].nldxShadow);
//
//		//�X�R�A�A�C�e���̎p����������
//		g_Enemy[nCntEnemy].bUse = false;
//
//		//�X�R�A�A�C�e���̐������炷����
//		EnemyCnt--;
//
//		//�����g���悤�ɂ���
//		g_Enemy[nCntEnemy].bSound = true;
//
//	}
//
//	else
//	{//�X�R�A�A�C�e���̃��C�t���c���Ă��鏈��
//
//		g_Enemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;
//
//		EnemyState();
//
//		/*	pMat[nCntEnemy].MatD3D.Ambient = D3DXCOLOR(1.0f,0.0f,0.0f, 1.0f);
//
//		pMat[nCntEnemy].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//
//		pMat[nCntEnemy].MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);*/
//
//		/*for (nCntRed = 0; nCntRed < 560; nCntRed++)
//		{
//		if (nCntRed < 560)
//		{
//		pMat->MatD3D.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		}
//		}*/
//	}
//}
//
//
//////=============================
//////�|���S���̈ʒu��^���鏈��
//////=============================
////D3DXVECTOR3 PosEnemy(void)
////{
////	int nCnt;
////
////	for(nCnt = 0; nCnt < MAX_ENEMY)
////  return g_Enemy[nCnt].pos;
////	
////}
////
//////===========================
//////�|���S���̌����������鏈��
//////===========================
////D3DXVECTOR3 RotEnemy(void)
////{
////	
////		return g_Enemy[nCnt].rot;
////}
//
////==================================
////�X�R�A�A�C�e���̈ړ�����
////==================================
//void MoveEnemy(void)
//{
//	//D3DXVECTOR3 Camrot = Getrot();
//
//	//float fRotMove = g_Enemy[nCntEnemy].rot.y;
//	//float fRotDest = g_Enemy[nCntEnemy].rot.y; //�ڕW�̊p�x
//	//float fRotDiff = 0.0f; //�ڕW�ƌ��݊p�x�̍���
//
//	//for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
//	//{
//	//	if (g_Enemy[nCnt].VtxMin.y > 0)
//	//	{
//	//		g_Enemy[nCnt].pos.y -= 0.1f;
//	//	}
//
//	//	if(g_Enemy[nCnt].VtxMin.y <= 0)
//	//	{
//	//		g_Enemy[nCnt].pos.y = 0.0f;
//	//	}
//	//}
//
//	////���ˊԊu��������
//	//if (g_BulletCnt > 0)
//	//{
//	//	g_BulletCnt--;
//	//}
//
//	//if (g_posModel.x <= -90.0f)
//	//{
//	//	g_posModel.x = -90.0f;
//	//}
//
//	//if (g_posModel.x >= 90.0f)
//	//{
//	//	g_posModel.x = 90.0f;
//	//}
//
//	//if (g_posModel.y <= 0.0f)
//	//{
//	//	g_posModel.y = 0.0f;
//	//}
//
//	//if (g_posModel.y >= 90.0f)
//	//{
//	//	g_posModel.y = 90.0f;
//	//}
//
//	//if (g_posModel.z >= 90.0f && g_posModel.x >= -90.0f)
//	//{
//	//	g_posModel.z = 90.0f;
//	//}
//
//	//if (g_posModel.z <= -90.0f && g_posModel.x <= 90.0f)
//	//{
//	//	g_posModel.z = -90.0f;
//	//}
//
//	//
//
//	////�ˌ�����
//	//if (GetKeyboardTrigger(DIK_SPACE) == true && g_BulletCnt <= 0)
//	//{//�X�y�[�X�L�[�������ꂽ�Ƃ�����
//
//	// //�A�����ˊԊu
//	//	g_BulletCnt = SHOTSPACE;
//
//	//	SetBullet(D3DXVECTOR3(g_posModel.x, g_posModel.y, g_posModel.z),
//	//		D3DXVECTOR3(sinf(g_rotModel.y), 0.0f, cosf(g_rotModel.y)),
//	//		g_rotModel, 1, BULLETTYPE_PLAYER,
//	//		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//	//}
//
//	////�e�̈ʒu��ݒ�
//	//SetPositionShadow(g_nldxShadow, D3DXVECTOR3(g_posModel.x, 0.0f, g_posModel.z));
//}
//
////==================================
////�X�R�A�A�C�e���̊p�x����
////==================================
//void AngleEnemy(void)
//{
//	D3DXVECTOR3 Posplayer = PosPlayer();
//	int nTime = GetTime();
//
//	for (int nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
//	{
//		D3DXVECTOR3 vecLine0 = D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x + 100.0f, 0.0f, g_Enemy[nCntEnemy].pos.z + 100.0f) - D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
//		D3DXVECTOR3 vecToPos0 = D3DXVECTOR3(Posplayer.x, Posplayer.y, Posplayer.z) - D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x + 100.0f, 0.0f, g_Enemy[nCntEnemy].pos.z + 100.0f);
//
//		D3DXVECTOR3 vecLine1 = D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x - 100.0f, 0.0f, g_Enemy[nCntEnemy].pos.z + 100.0f) - D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
//		D3DXVECTOR3 vecToPos1 = D3DXVECTOR3(Posplayer.x, Posplayer.y, Posplayer.z) - D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x - 100.0f, 0.0f, g_Enemy[nCntEnemy].pos.z + 100.0f);
//
//		/*	if ((vecLine0.z * vecToPos0.x) - (vecLine0.x * vecToPos0.z) >= -1
//		&& (vecLine1.z * vecToPos1.x) - (vecLine1.x * vecToPos1.z) <= 1)*/
//		if (Posplayer.z <= g_Enemy[nCntEnemy].pos.z + ENEMY_SIGHT_Z && Posplayer.z >= g_Enemy[nCntEnemy].pos.z - ENEMY_SIGHT_Z &&
//			Posplayer.x >= g_Enemy[nCntEnemy].pos.x - ENEMY_SIGHT_X && Posplayer.x <= g_Enemy[nCntEnemy].pos.x + ENEMY_SIGHT_X)
//		{
//			float fRotMove = g_Enemy[nCntEnemy].rot.y;
//			float fRotDest = g_Enemy[nCntEnemy].rot.y; //�ڕW�̊p�x
//			float fRotDiff = 0.0f; //�ڕW�ƌ��݊p�x�̍���
//
//								   ////���_���Œ肷��ꍇ
//			g_Enemy[nCntEnemy].rot.y = atan2f
//			(//�Ίp���̊p�x
//				g_Enemy[nCntEnemy].pos.x - Posplayer.x,
//				g_Enemy[nCntEnemy].pos.z - Posplayer.z
//			);
//
//			//�ڕW�̊p�x�Ƃ̍��������߂鏈��
//			fRotDiff = fRotDest - fRotMove;
//
//			////�ڕW�̊p�x�̕␳
//			//if (fRotDiff > D3DX_PI)
//			//{
//			//	fRotDiff += -D3DX_PI * 2;
//			//}
//
//			//else if (fRotDiff < -D3DX_PI)
//			//{
//			//	fRotDiff += D3DX_PI * 2;
//			//}
//
//			//��������
//			g_Enemy[nCntEnemy].move.x += (0.0f - g_Enemy[nCntEnemy].move.x) * 0.15f;
//			g_Enemy[nCntEnemy].move.y += (0.0f - g_Enemy[nCntEnemy].move.y) * 0.15f;
//			g_Enemy[nCntEnemy].move.z += (0.0f - g_Enemy[nCntEnemy].move.z) * 0.15f;
//
//			//�ړ��ʂ��ʒu�ɑ������
//			g_Enemy[nCntEnemy].pos += g_Enemy[nCntEnemy].move;
//
//			////�ړI�̈ʒu�܂ŕ␳���鏈��
//			//	fRotDiff = fRotDest - fRotMove;
//
//			//	DiffEnemy[nCntEnemy].x = g_Enemy[nCntEnemy].posDest.x - g_Enemy[nCntEnemy].pos.x;
//
//			//	DiffEnemy[nCntEnemy].z = g_Enemy[nCntEnemy].posDest.z - g_Enemy[nCntEnemy].pos.z;
//
//			////�ړI�̈ʒu�܂ŕ␳���鏈��
//			//g_Enemy[nCntEnemy].pos.x += DiffEnemy[nCntEnemy].x * 0.05f;
//
//			//g_Enemy[nCntEnemy].pos.z += DiffEnemy[nCntEnemy].z * 0.05f;
//
//			////�ړI�̃v���C���[�܂ł̌�����ݒ�
//			//g_Enemy[nCntEnemy].rot.y += fRotDiff * 0.05f;
//
//			////�v���C���[�̊p�x�̕␳
//			//if (g_Enemy[nCntEnemy].rot.y > D3DX_PI)
//			//{
//			//	g_Enemy[nCntEnemy].rot.y += -D3DX_PI * 2;
//			//}
//
//			//else if (g_Enemy[nCntEnemy].rot.y < -D3DX_PI)
//			//{
//			//	g_Enemy[nCntEnemy].rot.y += D3DX_PI * 2;
//			//}
//
//			if (nTime <= 99 && nTime >= 70)
//			{
//				//�X�R�A�A�C�e�����v���C���[�̕����ֈړ������鏈��
//				g_Enemy[nCntEnemy].move.x = -sinf(g_Enemy[nCntEnemy].rot.y) * ENEMY_SPEED;
//				g_Enemy[nCntEnemy].move.z = -cosf(g_Enemy[nCntEnemy].rot.y) * ENEMY_SPEED;
//			}
//
//			if (nTime <= 69 && nTime >= 40)
//			{
//				//�X�R�A�A�C�e�����v���C���[�̕����ֈړ������鏈��
//				g_Enemy[nCntEnemy].move.x = -sinf(g_Enemy[nCntEnemy].rot.y) * 3.0f;
//				g_Enemy[nCntEnemy].move.z = -cosf(g_Enemy[nCntEnemy].rot.y) * 3.0f;
//			}
//
//			if (nTime <= 39 && nTime >= 15)
//			{
//				//�X�R�A�A�C�e�����v���C���[�̕����ֈړ������鏈��
//				g_Enemy[nCntEnemy].move.x = -sinf(g_Enemy[nCntEnemy].rot.y) * 4.5f;
//				g_Enemy[nCntEnemy].move.z = -cosf(g_Enemy[nCntEnemy].rot.y) * 4.5f;
//			}
//
//			if (nTime <= 15 && nTime >= 0)
//			{
//				//�X�R�A�A�C�e�����v���C���[�̕����ֈړ������鏈��
//				g_Enemy[nCntEnemy].move.x = -sinf(g_Enemy[nCntEnemy].rot.y) * 6.5f;
//				g_Enemy[nCntEnemy].move.z = -cosf(g_Enemy[nCntEnemy].rot.y) * 6.5f;
//			}
//		}
//
//		else
//		{
//			float fRotMove = g_Enemy[nCntEnemy].rot.y;
//			float fRotDest = g_Enemy[nCntEnemy].rot.y; //�ڕW�̊p�x
//			float fRotDiff = 0.0f; //�ڕW�ƌ��݊p�x�̍���
//
//								   ////���_���Œ肷��ꍇ
//			g_Enemy[nCntEnemy].rot.y = atan2f
//			(//�Ίp���̊p�x
//				g_Enemy[nCntEnemy].pos.x - Posplayer.x,
//				g_Enemy[nCntEnemy].pos.z - Posplayer.z
//			);
//
//			//�ڕW�̊p�x�Ƃ̍��������߂鏈��
//			fRotDiff = fRotDest - fRotMove;
//
//			////�ڕW�̊p�x�̕␳
//			//if (fRotDiff > D3DX_PI)
//			//{
//			//	fRotDiff += -D3DX_PI * 2;
//			//}
//
//			//else if (fRotDiff < -D3DX_PI)
//			//{
//			//	fRotDiff += D3DX_PI * 2;
//			//}
//
//			//��������
//			g_Enemy[nCntEnemy].move.x += (0.0f - g_Enemy[nCntEnemy].move.x) * 0.15f;
//			g_Enemy[nCntEnemy].move.y += (0.0f - g_Enemy[nCntEnemy].move.y) * 0.15f;
//			g_Enemy[nCntEnemy].move.z += (0.0f - g_Enemy[nCntEnemy].move.z) * 0.15f;
//
//			//�ړ��ʂ��ʒu�ɑ������
//			g_Enemy[nCntEnemy].pos += g_Enemy[nCntEnemy].move;
//
//			////�ړI�̈ʒu�܂ŕ␳���鏈��
//			//	fRotDiff = fRotDest - fRotMove;
//
//			//	DiffEnemy[nCntEnemy].x = g_Enemy[nCntEnemy].posDest.x - g_Enemy[nCntEnemy].pos.x;
//
//			//	DiffEnemy[nCntEnemy].z = g_Enemy[nCntEnemy].posDest.z - g_Enemy[nCntEnemy].pos.z;
//
//			////�ړI�̈ʒu�܂ŕ␳���鏈��
//			//g_Enemy[nCntEnemy].pos.x += DiffEnemy[nCntEnemy].x * 0.05f;
//
//			//g_Enemy[nCntEnemy].pos.z += DiffEnemy[nCntEnemy].z * 0.05f;
//
//			////�ړI�̃v���C���[�܂ł̌�����ݒ�
//			//g_Enemy[nCntEnemy].rot.y += fRotDiff * 0.05f;
//
//			////�v���C���[�̊p�x�̕␳
//			//if (g_Enemy[nCntEnemy].rot.y > D3DX_PI)
//			//{
//			//	g_Enemy[nCntEnemy].rot.y += -D3DX_PI * 2;
//			//}
//
//			//else if (g_Enemy[nCntEnemy].rot.y < -D3DX_PI)
//			//{
//			//	g_Enemy[nCntEnemy].rot.y += D3DX_PI * 2;
//			//}
//
//			//�X�R�A�A�C�e�����v���C���[�̕����ֈړ������鏈��
//			g_Enemy[nCntEnemy].move.x = -sinf(g_Enemy[nCntEnemy].rot.y) * 12.0f;
//			g_Enemy[nCntEnemy].move.z = -cosf(g_Enemy[nCntEnemy].rot.y) * 12.0f;
//		}
//	}
//}
//
////=============================================
////�J�������v���C���[�̌��Ɉړ������鏈��
////=============================================
//void auteCamEnemy(void)
//{
//	/*if()*/
//}
//
////===========================
////�X�R�A�A�C�e���̏�ԂɊւ��鏈��
////===========================
//void EnemyState(void)
//{
//
//	for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
//	{
//
//		switch (g_Enemy[nCnt].state)
//		{
//		case ENEMYSTATE_NORMAL:
//
//			g_Enemy[nCnt].nCounterstate = 60;
//
//			break;
//
//		case ENEMYSTATE_DAMEGE:
//
//			g_Enemy[nCnt].nCounterstate--;
//
//			if (g_Enemy[nCnt].nCounterstate <= 0)
//			{
//				g_Enemy[nCnt].state = ENEMYSTATE_NORMAL;
//
//			}
//
//			break;
//		}
//
//	}
//}
//
////=====================================
////�X�R�A�A�C�e���ƃX�R�A�A�C�e���̓����蔻��
////=====================================
//void ColisionEneEne(void)
//{
//	int nCntEnemy;
//
//	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
//	{//�X�R�A�A�C�e�����g�p����Ă���
//
//		if (g_Enemy[nCntEnemy].bUse == true)
//		{//	�X�R�A�A�C�e�����g�p����Ă���
//
//			if (g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z
//				&& g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z >= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z)
//			{
//				//������̓����蔻��
//				if (g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x
//					&& g_Enemy[nCntEnemy].posold.x + g_Enemy[nCntEnemy].VtxMax.x <= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x)
//				{//�X�R�A�A�C�e���ƒe���������� 
//
//				 //	//�ʒu�������ɌŒ�
//					g_Enemy[nCntEnemy].pos.x = g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x - g_Enemy[nCntEnemy].VtxMax.x;
//				}
//
//				//�E����̓����蔻��
//				if (g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x <= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x
//					&& g_Enemy[nCntEnemy].posold.x + g_Enemy[nCntEnemy].VtxMin.x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x)
//				{//�X�R�A�A�C�e���ƒe���������� 
//
//				 //�ʒu���E���ɌŒ�
//					g_Enemy[nCntEnemy].pos.x = g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x - g_Enemy[nCntEnemy].VtxMin.x;
//				}
//
//			}
//
//			if (g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x <= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x
//				&& g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMax.x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].VtxMin.x)
//			{
//				//��O����̓����蔻��
//				if (g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z >= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z
//					&& g_Enemy[nCntEnemy].posold.z + g_Enemy[nCntEnemy].VtxMax.z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z)
//				{//�X�R�A�A�C�e���ƒe���������� 
//
//				 //	//�ʒu����O���ɌŒ�
//					g_Enemy[nCntEnemy].pos.z = g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z - g_Enemy[nCntEnemy].VtxMax.z;
//				}
//
//				//������̓����蔻��
//				if (g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMin.z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z
//					&& g_Enemy[nCntEnemy].posold.z + g_Enemy[nCntEnemy].VtxMin.z >= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z)
//				{//�X�R�A�A�C�e���ƒe���������� 
//
//				 //�ʒu�������ɌŒ�
//					g_Enemy[nCntEnemy].pos.z = g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].VtxMax.z - g_Enemy[nCntEnemy].VtxMin.z;
//				}
//			}
//		}
//	}
//}
//
////=============================
////�X�R�A�A�C�e���̐���n������
////=============================
//int EnemyCount(void)
//{
//	return EnemyCnt;
//}
//
////====================
////�X�R�A�A�C�e�����A����
////====================
//void ReturnEnemy(void)
//{
//	
//		SetEnemy(D3DXVECTOR3(g_LoadEnemy[nCnt], g_LoadEnemy[nCnt + 1], g_LoadEnemy[nCnt + 2]), ENEMYTYPE_NOEMAL, 1);
//}
//
//
//
