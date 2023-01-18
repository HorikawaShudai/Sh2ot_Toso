#include "main.h"
#include "game.h"
#include "result.h"
#include "player.h"
#include "camera.h"
#include "object00.h"
#include "input.h"
#include "debugproc.h"
#include "fade.h"

#define PLAYER_SPEED (1.5f)			//�v���C���[�̃X�s�[�h
#define PLAYER_ROT_SPEED (0.2f)			//�v���C���[�̉�]�X�s�[�h
#define PLAYER_JUMP (12.0f)				//�v���C���[�̃W�����v��
#define PLAYER_LIFE (3)					//�v���C���[�̏������C�t
#define PLAYER_COLLISIONSIZE (15.0f)	//�v���C���[�̓����蔻��̑傫��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer[100] = {};	//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshPlayer[32] = {};				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer[32] = {};			//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0;						//�}�e���A���̐�
Player g_Player;								//�v���C���[�̏��
int g_nIndexPlayerShadow = -1;					//�e�̃C���f�b�N�X(�ԍ�)

int WaitMotionCounter;							//�ҋ@���[�V�����̃J�E���^�[
int WaitMotion;									//�ҋ@���[�V����
int MoveMotionCounter;							//�ړ����[�V�����̃J�E���^�[
int MoveMotion;									//�ړ����[�V����
int JumpMotionCounter;							//�W�����v���[�V�����̃J�E���^�[
int JumpMotion;									//�W�����v���[�V����
bool bWait;										//�ҋ@���Ă邩�ǂ����̔��f
float JunpPawer;								//�ҋ@���Ă邩�ǂ����̔��f

//====================================================================
//�v���C���[�̏���������
//====================================================================
void InitPlayer(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nNumVtx;		//���_��
	DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, -20.0f);
	g_Player.posOld = D3DXVECTOR3(0.0f, 300.0f, -400.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_Player.vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_Player.State = PLAYER_NORMAL;
	g_Player.nLife = PLAYER_LIFE;
	g_Player.bJump = false;
	g_Player.bUse = true;
	g_Player.pMatH.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.pMatD.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	g_Player.pMatW.MatD3D.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	WaitMotionCounter = 0;
	WaitMotion = 1;
	MoveMotionCounter = 0;
	MoveMotion = 1;
	JumpMotionCounter = 0;
	JumpMotion = 1;
	bWait = true;
	JunpPawer = 0.0f;

	g_Player.nNumModel = 1;

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\player.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer[0],
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer[0]);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//���_��������
		nNumVtx = g_pMeshPlayer[nCntModel]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y������
		dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer[nCntModel]->GetFVF());

		//���_�o�b�t�@�����b�N
		g_pMeshPlayer[nCntModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

			if (g_Player.vtxMin.x > vtx.x)
			{
				g_Player.vtxMin.x = vtx.x;
			}
			if (g_Player.vtxMin.y > vtx.y)
			{
				g_Player.vtxMin.y = vtx.y;
			}
			if (g_Player.vtxMin.z > vtx.z)
			{
				g_Player.vtxMin.z = vtx.z;
			}

			if (g_Player.vtxMax.x < vtx.x)
			{
				g_Player.vtxMax.x = vtx.x;
			}
			if (g_Player.vtxMax.y < vtx.y)
			{
				g_Player.vtxMax.y = vtx.y;
			}
			if (g_Player.vtxMax.z < vtx.z)
			{
				g_Player.vtxMax.z = vtx.z;
			}

			pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		//���_�o�b�t�@���A�����b�N
		g_pMeshPlayer[nCntModel]->UnlockVertexBuffer();

		D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

							//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatPlayer[nCntModel]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTexturePlayer[nCntMat]);
			}
		}
	}
}

//====================================================================
//�v���C���[�̏I������
//====================================================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//���b�V���̔j��
		if (g_pMeshPlayer != NULL)
		{
			g_pMeshPlayer[nCntModel]->Release();
			g_pMeshPlayer[nCntModel] = NULL;
		}

		//�}�e���A���̔j��
		if (g_pBuffMatPlayer != NULL)
		{
			g_pBuffMatPlayer[nCntModel]->Release();
			g_pBuffMatPlayer[nCntModel] = NULL;
		}
	}
}

//====================================================================
//�v���C���[�̍X�V����
//====================================================================
void UpdatePlayer(void)
{
	//�v���C���[�̏��
	switch (g_Player.State)
	{
	case PLAYER_NORMAL:
		break;

	case PLAYER_WAIT:
		g_Player.nWaitCounter--;
		if (g_Player.nWaitCounter < 0)
		{
			g_Player.State = PLAYER_NORMAL;
		}
		break;

	case PLAYER_DAMAGE:
		g_Player.nDamageCounter--;
		if (g_Player.nDamageCounter < 0)
		{
			g_Player.State = PLAYER_WAIT;
		}
		break;

	case PLAYER_HIT:
		g_Player.nHitCounter--;
		if (g_Player.nHitCounter < 0)
		{
			g_Player.State = PLAYER_DAMAGE;
		}
		break;
	}

	//�v���C���[�̃��[�V����
	PlayerMotion();

	g_Player.posOld = g_Player.pos;

	//�����W��
	g_Player.move.x = g_Player.move.x * 0.5f;
	g_Player.move.z = g_Player.move.z * 0.5f;

	//�l�̐؂�̂�
	if (g_Player.move.x <= 0.005f && g_Player.move.x >= -0.005f)
	{
		g_Player.move.x = 0.0f;
	}
	if (g_Player.move.z <= 0.005f && g_Player.move.z >= -0.005f)
	{
		g_Player.move.z = 0.0f;
	}

	//�d�͂̒ǉ�
	g_Player.move.y -= 10.0f;

	//�v���C���[�̈ړ����͏���
	PlayerMoveInput();

	//�W�����v����
	if (g_Player.bJump == false)
	{//�W�����v�����Ă��Ȃ��Ƃ�
		if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
		{//�W�����v�{�^�����͎�
			g_Player.move.y = PLAYER_JUMP;	//�W�����v����
			g_Player.bJump = true;			//�W�����v���g�p���Ă����Ԃɂ���
		}
	}

	//�ʒu�X�V(���͂ɂ�铮��)
	g_Player.pos += g_Player.move;

	//���̒ǉ�
	if (g_Player.pos.y < 0.0f)
	{//���ɂӂꂽ�Ƃ�
		g_Player.pos.y = 0.0f;	//���̏�ɖ߂�
		g_Player.move.y = 0.0f;	//
	}

	//��葬�x�ȏ�ŗ������Ă��鎞�ɃW�����v���o���Ȃ���Ԃɂ���
	if (g_Player.move.y < 0.0f)
	{
		if (g_Player.bJump == false)
		{
			g_Player.bJump = true;			//�W�����v���g�p���Ă����Ԃɂ���
		}
	}

	//�ړ����Ƀv���C���[�̌�����␳����
	PlayerRotUpdate();

	//�I�u�W�F�N�g�Ƃ̓����蔻��
	if (CollisionObject00(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.vtxMin, g_Player.vtxMax, 10.0f) == false)
	{
		if (g_Player.bJump == true)
		{
			g_Player.bJump = false;	//�W�����v���g�p���Ă��Ȃ���Ԃɂ���
		}
	}

	//����������̌����̕␳
	if (g_Player.rot.y > D3DX_PI * 1.0f)
	{
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_Player.rot.y < -D3DX_PI * 1.0f)
	{
		g_Player.rot.y += D3DX_PI * 2.0f;
	}

	PrintDebugProc("fff", g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
}

//====================================================================
//�v���C���[�̃��[�V��������(�ȈՔ�)
//====================================================================
void PlayerMotion(void)
{

}

//====================================================================
//�v���C���[�̈ړ����͏���
//====================================================================
void PlayerMoveInput(void)
{
	g_Player.NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�L�[�{�[�h�̈ړ�����
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_Player.NormarizeMove.z += 1.0f * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.NormarizeMove.x += 1.0f * sinf(Getrot().y) * PLAYER_SPEED;

	}
	if (GetKeyboardPress(DIK_G) == true)
	{
		g_Player.NormarizeMove.z += -1.0f * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.NormarizeMove.x += -1.0f * sinf(Getrot().y) * PLAYER_SPEED;
	}
	if (GetKeyboardPress(DIK_F) == true)
	{
		g_Player.NormarizeMove.x += -1.0f * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.NormarizeMove.z -= -1.0f * sinf(Getrot().y) * PLAYER_SPEED;

	}
	if (GetKeyboardPress(DIK_H) == true)
	{
		g_Player.NormarizeMove.x += 1.0f * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.NormarizeMove.z -= 1.0f * sinf(Getrot().y) * PLAYER_SPEED;
	}

	if (GetKeyboardPress(DIK_T) == false && GetKeyboardPress(DIK_F) == false && GetKeyboardPress(DIK_G) == false && GetKeyboardPress(DIK_H) == false)
	{
		//���X�e�B�b�N�ɂ��O��ړ�	
		g_Player.move.z += GetGamepad_Stick_Left(0).y * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.move.x += GetGamepad_Stick_Left(0).y * sinf(Getrot().y) * PLAYER_SPEED;

		//���X�e�B�b�N�ɂ�鍶�E�ړ�
		g_Player.move.x += GetGamepad_Stick_Left(0).x * cosf(Getrot().y) * PLAYER_SPEED;
		g_Player.move.z -= GetGamepad_Stick_Left(0).x * sinf(Getrot().y) * PLAYER_SPEED;
	}

	if (GetKeyboardPress(DIK_T) == true || GetKeyboardPress(DIK_F) == true || GetKeyboardPress(DIK_G) == true || GetKeyboardPress(DIK_H) == true)
	{
		JunpPawer = g_Player.NormarizeMove.y;
		g_Player.NormarizeMove.y = 0.0f;

		D3DXVec3Normalize(&g_Player.NormarizeMove, &g_Player.NormarizeMove);

		g_Player.NormarizeMove.x *= PLAYER_SPEED;
		g_Player.NormarizeMove.y = JunpPawer;
		g_Player.NormarizeMove.z *= PLAYER_SPEED;
	}

	g_Player.move += g_Player.NormarizeMove;
}

//====================================================================
//�v���C���[�̌����̕␳
//====================================================================
void PlayerRotUpdate(void)
{
	//�ړ������Ɍ��������킹�鏈��
	float fRotMove, fRotDest, fRotDiff;

	fRotMove = g_Player.rot.y;
	fRotDest = Getrot().y;

	if (GetKeyboardPress(DIK_E) == true)
	{
		g_Player.rot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_Player.rot.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_T) == true || GetGamepad_Stick_Left(0).y > 0.1f)
	{
		if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.25f;
		}
		else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.25f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y));
		}
	}
	else if (GetKeyboardPress(DIK_G) == true || GetGamepad_Stick_Left(0).y < -0.1f)
	{
		if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.75f;
		}
		else
		{
			fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
			fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).x > 0.1f)
	{
		fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
		fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_F) == true || GetGamepad_Stick_Left(0).x < -0.1f)
	{
		fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
		fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y)) + D3DX_PI * -0.5f;
	}

	////���X�e�B�b�N�ɂ��O��ړ�	
	//g_Player.move.z += GetGamepad_Stick_Left(0).y * cosf(Getrot().y) * PLAYER_SPEED;
	//g_Player.move.x += GetGamepad_Stick_Left(0).y * sinf(Getrot().y) * PLAYER_SPEED;

	////���X�e�B�b�N�ɂ�鍶�E�ړ�
	//g_Player.move.x += GetGamepad_Stick_Left(0).x * cosf(Getrot().y) * PLAYER_SPEED;
	//g_Player.move.z -= GetGamepad_Stick_Left(0).x * sinf(Getrot().y) * PLAYER_SPEED;

	//fRotMove = atan2f(sinf(g_Player.rot.y), cosf(g_Player.rot.y));
	//fRotDest = atan2f(sinf(Getrot().y), cosf(Getrot().y) + D3DX_PI * GetGamepad_Stick_Left(0).x);

	fRotDiff = fRotDest - fRotMove;

	if (fRotDiff > D3DX_PI * 1.0f)
	{
		fRotDiff -= D3DX_PI * 2.0f;
	}
	else if (fRotDiff < -D3DX_PI * 1.0f)
	{
		fRotDiff += D3DX_PI * 2.0f;
	}

	fRotMove += fRotDiff * PLAYER_ROT_SPEED;

	if (fRotMove > D3DX_PI * 1.0f)
	{
		fRotMove -= D3DX_PI * 2.0f;
	}
	else if (fRotMove < -D3DX_PI * 1.0f)
	{
		fRotMove += D3DX_PI * 2.0f;
	}

	if (GetKeyboardPress(DIK_T) == true || GetKeyboardPress(DIK_F) == true || GetKeyboardPress(DIK_G) == true || GetKeyboardPress(DIK_H) == true || GetGamepad_Stick_Left(0).y != 0.0f || GetGamepad_Stick_Left(0).x != 0.0f)
	{
		g_Player.rot.y = fRotMove;
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻��
//====================================================================
void CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float Size, float MaxY, float MinY)
{
	if (
		pos.z + Size >= g_Player.pos.z - PLAYER_COLLISIONSIZE &&
		pos.z - Size <= g_Player.pos.z + PLAYER_COLLISIONSIZE &&
		pos.x + Size >= g_Player.pos.x - PLAYER_COLLISIONSIZE &&
		pos.x - Size <= g_Player.pos.x + PLAYER_COLLISIONSIZE &&
		pos.y + MaxY >= g_Player.pos.y + g_Player.vtxMin.y &&
		pos.y + MinY <= g_Player.pos.y + g_Player.vtxMax.y
		)
	{//�e�ƃv���C���[����������(Z��)
		PlayerHit();
	}
}

//====================================================================
//�v���C���[�̃q�b�g����
//====================================================================
void PlayerHit(void)
{

}

//====================================================================
//�v���C���[�̕`�揈��
//====================================================================
void DrawPlayer(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�S���f��(�p�[�c)�̕`��
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{

		//�}�e���A���f�[�^�ւ̃|�C���^����������
		pMat = (D3DXMATERIAL*)g_pBuffMatPlayer[nCntModel]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
		{
			switch (g_Player.State)
			{
			case PLAYER_NORMAL:
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				break;

			case PLAYER_WAIT:
				pDevice->SetMaterial(&g_Player.pMatW.MatD3D);
				break;

			case PLAYER_DAMAGE:
				pDevice->SetMaterial(&g_Player.pMatD.MatD3D);
				break;

			case PLAYER_HIT:
				pDevice->SetMaterial(&g_Player.pMatH.MatD3D);
				break;
			}

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePlayer[nCntMat]);

			if (g_Player.bUse == true)
			{
				//�v���C���[(�p�[�c)�̕`��
				g_pMeshPlayer[nCntModel]->DrawSubset(nCntMat);
			}
		}
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//���̃��C�t�̐ݒ�
//====================================================================
void SetNextLife(void)
{
	g_Player.nNextLife = g_Player.nLife;
}

//====================================================================
//�v���C���[���̏���
//====================================================================
Player * GetPlayer(void)
{
	return &g_Player;
}