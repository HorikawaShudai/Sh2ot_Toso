#include "main.h"
#include "ActionHelpUI.h"
#include "player.h"
#include "sound.h"

//�}�N����`
#define ACTIONHELPUI_SIZE (5.0f)	//�w���vUI�̑傫��

//�v���g�^�C�v�錾

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureActionHelpUI[ACTIONHELPUI_MAX];				//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffActionHelpUI;		//���_�o�b�t�@�̃|�C���^
ActionHelpUI g_aActionHelpUI[MAX_ACTIONHELPUI];

//====================================================================
//�w���vUI�̏���������
//====================================================================
void InitActionHelpUI(void)
{
	int nCntUI;
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\GetUi.png",
		&g_pTextureActionHelpUI[ACTIONHELPUI_KEY]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL\\OpenUi.png",
		&g_pTextureActionHelpUI[ACTIONHELPUI_DOOR]);

	for (nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		g_aActionHelpUI[nCntUI].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_aActionHelpUI[nCntUI].fSize = ACTIONHELPUI_SIZE;
		g_aActionHelpUI[nCntUI].bUse = false;
		g_aActionHelpUI[nCntUI].nType = ACTIONHELPUI_KEY;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ACTIONHELPUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffActionHelpUI,
		NULL);

	VERTEX_3D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffActionHelpUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		//���_���W�̐ݒ� 
		pVtx[0].pos = D3DXVECTOR3(-g_aActionHelpUI[nCntUI].fSize, +g_aActionHelpUI[nCntUI].fSize, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+g_aActionHelpUI[nCntUI].fSize, +g_aActionHelpUI[nCntUI].fSize, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aActionHelpUI[nCntUI].fSize, -g_aActionHelpUI[nCntUI].fSize, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+g_aActionHelpUI[nCntUI].fSize, -g_aActionHelpUI[nCntUI].fSize, 0.0f);

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
	g_pVtxBuffActionHelpUI->Unlock();
}

//====================================================================
//�w���vUI�̏I������
//====================================================================
void UninitActionHelpUI(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < ACTIONHELPUI_MAX; nCntTex++)
	{
		if (g_pTextureActionHelpUI[nCntTex] != NULL)
		{
			g_pTextureActionHelpUI[nCntTex]->Release();
			g_pTextureActionHelpUI[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffActionHelpUI != NULL)
	{
		g_pVtxBuffActionHelpUI->Release();
		g_pVtxBuffActionHelpUI = NULL;
	}
}

//====================================================================
//�w���vUI�̍X�V����
//====================================================================
void UpdateActionHelpUI(void)
{
	int nCntUI;

	for (nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		if (g_aActionHelpUI[nCntUI].bUse == true)
		{

		}
	}

	VERTEX_3D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffActionHelpUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		if (g_aActionHelpUI[nCntUI].bUse == true)
		{
			//���_���W�̐ݒ� 
			pVtx[0].pos = D3DXVECTOR3(-g_aActionHelpUI[nCntUI].fSize, +g_aActionHelpUI[nCntUI].fSize, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_aActionHelpUI[nCntUI].fSize, +g_aActionHelpUI[nCntUI].fSize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aActionHelpUI[nCntUI].fSize, -g_aActionHelpUI[nCntUI].fSize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_aActionHelpUI[nCntUI].fSize, -g_aActionHelpUI[nCntUI].fSize, 0.0f);
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffActionHelpUI->Unlock();
}

//====================================================================
//�w���vUI�̕`�揈��
//====================================================================
void DrawActionHelpUI(int nCntPlayer,bool GetKey)
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

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aActionHelpUI[nCntUI].mtxWorld);

		//�r���[�}�g���b�N�X������
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂ�������
		D3DXMatrixInverse(&g_aActionHelpUI[nCntUI].mtxWorld, NULL, &mtxView);	//�t�s������߂�
		g_aActionHelpUI[nCntUI].mtxWorld._41 = 0.0f;
		g_aActionHelpUI[nCntUI].mtxWorld._42 = 0.0f;
		g_aActionHelpUI[nCntUI].mtxWorld._43 = 0.0f;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aActionHelpUI[nCntUI].pos.x, g_aActionHelpUI[nCntUI].pos.y, g_aActionHelpUI[nCntUI].pos.z);

		D3DXMatrixMultiply(&g_aActionHelpUI[nCntUI].mtxWorld, &g_aActionHelpUI[nCntUI].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aActionHelpUI[nCntUI].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffActionHelpUI, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		if (GetKey == true && pPlayer->ExitHelpUI == true)
		{
			pDevice->SetTexture(0, g_pTextureActionHelpUI[ACTIONHELPUI_DOOR]);
		}
		else if(GetKey == false && pPlayer->KeyHelpUI == true)
		{
			pDevice->SetTexture(0, g_pTextureActionHelpUI[ACTIONHELPUI_KEY]);
		}

		if (g_aActionHelpUI[nCntUI].bUse == true &&(pPlayer->ExitHelpUI == true || pPlayer->KeyHelpUI == true))
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

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//====================================================================
//�w���vUI�̐ݒ菈��
//====================================================================
int SetActionHelpUI(D3DXVECTOR3 pos, float Size, ACTIONHELPUI_TYPE Type)
{
	int nIdx = -1;

	for (int nCntUI = 0; nCntUI < MAX_ACTIONHELPUI; nCntUI++)
	{
		if (g_aActionHelpUI[nCntUI].bUse == false)
		{
			g_aActionHelpUI[nCntUI].pos = pos;
			g_aActionHelpUI[nCntUI].fSize = Size;
			g_aActionHelpUI[nCntUI].nType = Type;
			g_aActionHelpUI[nCntUI].bUse = true;
			nIdx = nCntUI;
			break;
		}
	}

	return nIdx;
}

//====================================================================
//�w���vUI�̍폜����
//====================================================================
void FalseActionHelpUI(int Idx)
{
	g_aActionHelpUI[Idx].bUse = false;
}

//====================================================================
//�w���vUI�̏���
//====================================================================
ActionHelpUI * GetActionHelpUI(void)
{
	return &g_aActionHelpUI[0];
}