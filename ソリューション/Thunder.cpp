//====================================================================
//
//���̕\������
//Auther:�x�씋��
//
//====================================================================
#include "Thunder.h"
#include "Billboard.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffThunder = NULL;		//���̒��_�o�b�t�@�̃|�C���^
THUNDER g_Thunder;
D3DXMATRIX g_mtxWorldThunder;							//���̃��[���h�}�g���b�N�X

//====================================================
//���̏���������
//====================================================
void InitThunder(void)
{
	g_Thunder.bUse = false;
	g_Thunder.nCnt = 0;
	g_Thunder.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Thunder.pos = D3DXVECTOR3(100.0f, +0.0f, 500.0f);


	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffThunder,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffThunder->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-1280.0f, +720.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+1280.0f, +720.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-1280.0f, -720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+1280.0f, -720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(g_Thunder.col);
	pVtx[1].col = D3DXCOLOR(g_Thunder.col);
	pVtx[2].col = D3DXCOLOR(g_Thunder.col);
	pVtx[3].col = D3DXCOLOR(g_Thunder.col);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffThunder->Unlock();
}
//====================================================
//���̏I������
//====================================================
void UninitThunder(void)
{
	if (g_pVtxBuffThunder != NULL)
	{
		g_pVtxBuffThunder->Release();
		g_pVtxBuffThunder = NULL;
	}
}

//====================================================
//���̍X�V����
//====================================================
void UpdateThunder(void)
{
	if (g_Thunder.bUse == true)
	{
		g_Thunder.col.a -= 0.007f;
		if (g_Thunder.col.a < -0.0f)
		{
			g_Thunder.bUse = false;
		}
	}

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffThunder->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(g_Thunder.col);
	pVtx[1].col = D3DXCOLOR(g_Thunder.col);
	pVtx[2].col = D3DXCOLOR(g_Thunder.col);
	pVtx[3].col = D3DXCOLOR(g_Thunder.col);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffThunder->Unlock();
}

//====================================================
//���̕`�揈��
//====================================================
void DrawThunder(void)
{
	if (g_Thunder.bUse == true)
	{
		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�̎擾�p

								//Z�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldThunder);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&g_mtxWorldThunder, NULL, &mtxView);
		g_mtxWorldThunder._41 = 0.0f;
		g_mtxWorldThunder._42 = 0.0f;
		g_mtxWorldThunder._43 = 0.0f;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Thunder.pos.x, g_Thunder.pos.y, g_Thunder.pos.z);
		D3DXMatrixMultiply(&g_mtxWorldThunder, &g_mtxWorldThunder, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldThunder);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffThunder, 0, sizeof(VERTEX_3D));

		pDevice->SetFVF(FVF_VERTEX_3D);


		pDevice->SetTexture(0, NULL);

		//��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//Z�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}

void SetThunder(void)
{
	g_Thunder.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Thunder.bUse = true;
}