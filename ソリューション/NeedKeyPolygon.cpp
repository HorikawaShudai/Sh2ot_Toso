#include "main.h"
#include "NeedKeyPolygon.h"
#include "player.h"
#include "exit.h"
#include "PlayNumberSelect.h"
#include "exit.h"
#include "sound.h"

//�}�N����`
#define NEEDKEYPOLYGON_SIZE (5.0f)	//�w���vUI�̑傫��
#define NEEDKEYPOLYGONNUMBER_SIZE (2.0f)	//�w���vUI�̑傫��
#define NEEDKEYPOLYGONNUMBER_X (2.0f)	//�w���vUI�̑傫��
#define NEEDKEYPOLYGONNUMBER_Y (0.5f)	//�w���vUI�̑傫��

//�v���g�^�C�v�錾

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureNeedKeyPolygon[NEEDKEYPOLYGON_MAX];	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNeedKeyPolygon;					//���_�o�b�t�@�̃|�C���^
NeedKeyPolygon g_aNeedKeyPolygon[MAX_NEEDKEYPOLYGON];

//====================================================================
//�w���vUI�̏���������
//====================================================================
void InitNeedKeyPolygon(void)
{
	int nCntUI;
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ExitNumber.png",
		&g_pTextureNeedKeyPolygon[NEEDKEYPOLYGON_CENTER]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number00.png",
		&g_pTextureNeedKeyPolygon[NEEDKEYPOLYGON_LEFT]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number00.png",
		&g_pTextureNeedKeyPolygon[NEEDKEYPOLYGON_RIGHT]);

	for (nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		g_aNeedKeyPolygon[nCntUI].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		switch (nCntUI)
		{
		case 0:
			g_aNeedKeyPolygon[nCntUI].fSize = NEEDKEYPOLYGON_SIZE;
			break;
		case 1:
		case 2:
			g_aNeedKeyPolygon[nCntUI].fSize = NEEDKEYPOLYGONNUMBER_SIZE;
			break;
		}
		g_aNeedKeyPolygon[nCntUI].bUse = true;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_NEEDKEYPOLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNeedKeyPolygon,
		NULL);

	VERTEX_3D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffNeedKeyPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		//���_���W�̐ݒ� 
		pVtx[0].pos = D3DXVECTOR3(-g_aNeedKeyPolygon[nCntUI].fSize, +g_aNeedKeyPolygon[nCntUI].fSize, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+g_aNeedKeyPolygon[nCntUI].fSize, +g_aNeedKeyPolygon[nCntUI].fSize, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aNeedKeyPolygon[nCntUI].fSize, -g_aNeedKeyPolygon[nCntUI].fSize, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+g_aNeedKeyPolygon[nCntUI].fSize, -g_aNeedKeyPolygon[nCntUI].fSize, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffNeedKeyPolygon->Unlock();
}

//====================================================================
//�w���vUI�̏I������
//====================================================================
void UninitNeedKeyPolygon(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < NEEDKEYPOLYGON_MAX; nCntTex++)
	{
		if (g_pTextureNeedKeyPolygon[nCntTex] != NULL)
		{
			g_pTextureNeedKeyPolygon[nCntTex]->Release();
			g_pTextureNeedKeyPolygon[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffNeedKeyPolygon != NULL)
	{
		g_pVtxBuffNeedKeyPolygon->Release();
		g_pVtxBuffNeedKeyPolygon = NULL;
	}
}

//====================================================================
//�w���vUI�̍X�V����
//====================================================================
void UpdateNeedKeyPolygon(void)
{
	int nCntUI;

	for (nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		if (g_aNeedKeyPolygon[nCntUI].bUse == true)
		{

		}
	}

	VERTEX_3D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffNeedKeyPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		if (g_aNeedKeyPolygon[nCntUI].bUse == true)
		{
			switch (nCntUI)
			{
			case 0:
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			case 1:
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + GetPlayNumberSelect().CurrentSelectNumber * 0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + GetPlayNumberSelect().CurrentSelectNumber * 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + GetPlayNumberSelect().CurrentSelectNumber * 0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + GetPlayNumberSelect().CurrentSelectNumber * 0.1f, 1.0f);
				break;
			case 2:
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + GetKeyCount() * 0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + GetKeyCount() * 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + GetKeyCount() * 0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + GetKeyCount() * 0.1f, 1.0f);
				break;
			}
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffNeedKeyPolygon->Unlock();
}

//====================================================================
//�w���vUI�̕`�揈��
//====================================================================
void DrawNeedKeyPolygon(int nCntPlayer)
{
	//�v���C���[���̎擾
	Player *pPlayer = GetPlayer();
	pPlayer += nCntPlayer;

	int nCntUI;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;	//�r���[�}�g���b�N�X�����p

	////Z�e�X�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	////���C�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aNeedKeyPolygon[nCntUI].mtxWorld);

		//�r���[�}�g���b�N�X������
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂ�������
		D3DXMatrixInverse(&g_aNeedKeyPolygon[nCntUI].mtxWorld, NULL, &mtxView);	//�t�s������߂�
		g_aNeedKeyPolygon[nCntUI].mtxWorld._41 = 0.0f;
		g_aNeedKeyPolygon[nCntUI].mtxWorld._42 = 0.0f;
		g_aNeedKeyPolygon[nCntUI].mtxWorld._43 = 0.0f;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aNeedKeyPolygon[nCntUI].pos.x, g_aNeedKeyPolygon[nCntUI].pos.y, g_aNeedKeyPolygon[nCntUI].pos.z);

		D3DXMatrixMultiply(&g_aNeedKeyPolygon[nCntUI].mtxWorld, &g_aNeedKeyPolygon[nCntUI].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aNeedKeyPolygon[nCntUI].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffNeedKeyPolygon, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureNeedKeyPolygon[nCntUI]);

		if (g_aNeedKeyPolygon[nCntUI].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntUI,										//�v���~�e�B�u(�|���S��)��
				2);
		}
	}

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	////Z�e�X�g��L���ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////���C�g��L���ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//====================================================================
//�w���vUI�̐ݒ菈��
//====================================================================
void SetNeedKeyPolygon(D3DXVECTOR3 pos)
{
	g_aNeedKeyPolygon[0].pos = pos;
	g_aNeedKeyPolygon[1].pos = D3DXVECTOR3(pos.x - NEEDKEYPOLYGONNUMBER_X, pos.y - NEEDKEYPOLYGONNUMBER_Y + 0.5f, pos.z);
	g_aNeedKeyPolygon[2].pos = D3DXVECTOR3(pos.x + NEEDKEYPOLYGONNUMBER_X, pos.y + NEEDKEYPOLYGONNUMBER_Y + 0.5f, pos.z);
}

//====================================================================
//�w���vUI�̍폜����
//====================================================================
void FalseNeedKeyPolygon(void)
{
	for (int nCntUI = 0; nCntUI < MAX_NEEDKEYPOLYGON; nCntUI++)
	{
		g_aNeedKeyPolygon[nCntUI].bUse = false;
	}
}

//====================================================================
//�w���vUI�̏���
//====================================================================
NeedKeyPolygon * GetNeedKeyPolygon(void)
{
	return &g_aNeedKeyPolygon[0];
}