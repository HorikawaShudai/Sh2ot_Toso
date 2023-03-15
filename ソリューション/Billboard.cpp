//====================================================================
//
//�r���{�[�h�\������
//Auther:�x�씋��
//
//====================================================================
#include "Billboard.h"
#include "Input.h"

//�}�N����`
#define MAX_RAIN	(400)	//�J�̍ő吔
#define RAIN_HEIGHT	(10.0f)	//�J�̍���
#define RAIN_WIDTH	(0.2f)	//�J�̕�

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMoon = NULL;			//���̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRain = NULL;			//�J�̒��_�o�b�t�@�̃|�C���^
D3DXMATRIX g_mtxWorldBillboard;							//�r���{�[�h�̃��[���h�}�g���b�N�X
MOON g_Moon;											//���̍\����
RAIN g_Rain[MAX_RAIN];									//�J�̍\����
bool g_bRain;

//�v���g�^�C�v�錾
void InitMoon(void);
void InitRain(void);
void UpdateMoon(void);
void UpdateRain(void);
void DrawMoon(void);
void DrawRain(void);
void SetRain(void);

//====================================================
//�r���{�[�h�̏���������
//====================================================
void InitBillboard(void)
{
	InitMoon();
	InitRain();
}
//====================================================
//�r���{�[�h�̏I������
//====================================================
void UninitBillboard(void)
{
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
	if (g_pVtxBuffMoon != NULL)
	{
		g_pVtxBuffMoon->Release();
		g_pVtxBuffMoon = NULL;
	}
	if (g_pVtxBuffRain != NULL)
	{
		g_pVtxBuffRain->Release();
		g_pVtxBuffRain = NULL;
	}
}

//====================================================
//�r���{�[�h�̍X�V����
//====================================================
void UpdateBillboard(void)
{
	UpdateMoon();
	UpdateRain();
}

//====================================================
//�r���{�[�h�̕`�揈��
//====================================================
void DrawBillboard(void)
{
	DrawMoon();
	DrawRain();
}

//====================================================
//���̏���������
//====================================================
void InitMoon(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Moon.pos = D3DXVECTOR3(1400.0f, 1400.0f, 1300.0f);
	g_Moon.bUse = false;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMoon,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffMoon->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\Red_moon.png",
		&g_pTextureBillboard);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-100.0f, +100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+100.0f, +100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+100.0f, -100.0f, 0.0f);

	//nor�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMoon->Unlock();
}


//====================================================
//���̍X�V����
//====================================================
void UpdateMoon(void)
{
}

//====================================================
//���̕`�揈��
//====================================================
void DrawMoon(void)
{
	if (g_Moon.bUse == true)
	{
		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�̎擾�p

		//Z�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldBillboard);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);
		g_mtxWorldBillboard._41 = 0.0f;
		g_mtxWorldBillboard._42 = 0.0f;
		g_mtxWorldBillboard._43 = 0.0f;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Moon.pos.x, g_Moon.pos.y, g_Moon.pos.z);
		D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMoon, 0, sizeof(VERTEX_3D));

		pDevice->SetFVF(FVF_VERTEX_3D);


		pDevice->SetTexture(0, g_pTextureBillboard);

		//�r���{�[�h
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//Z�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}

//====================================================
//�J�̏���������
//====================================================
void InitRain(void)
{

	g_bRain = true;

	//�\���̂̏�����
	for (int nCnt = 0; nCnt < MAX_RAIN; nCnt++)
	{
		g_Rain[nCnt].bUse = false;
		g_Rain[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Rain[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_RAIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRain,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffRain->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_RAIN; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-RAIN_WIDTH, +RAIN_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+RAIN_WIDTH, +RAIN_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-RAIN_WIDTH, -RAIN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+RAIN_WIDTH, -RAIN_HEIGHT, 0.0f);

		//nor�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRain->Unlock();
}
//================================================================
//�J�̍X�V����
//================================================================
void UpdateRain(void)
{
	if (g_bRain == true)
	{
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();
		SetRain();

		for (int nRain = 0; nRain < MAX_RAIN; nRain++)
		{
			if (g_Rain[nRain].bUse == true)
			{
				g_Rain[nRain].pos += g_Rain[nRain].move;

				if (g_Rain[nRain].pos.y < 0.0f)
				{
					g_Rain[nRain].bUse = false;
				}
			}
		}
	}
}

//====================================================
//�J�̕`�揈��
//====================================================
void DrawRain(void)
{
	if (g_bRain == true)
	{
		for (int nCnt = 0; nCnt < MAX_RAIN; nCnt++)
		{
			if (g_Rain[nCnt].bUse == true)
			{
				//�f�o�C�X�̎擾
				LPDIRECT3DDEVICE9 pDevice = GetDevice();

				D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�̎擾�p

				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_mtxWorldBillboard);

				//�r���[�}�g���b�N�X���擾
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
				D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);
				g_mtxWorldBillboard._41 = 0.0f;
				g_mtxWorldBillboard._42 = 0.0f;
				g_mtxWorldBillboard._43 = 0.0f;

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Rain[nCnt].pos.x, g_Rain[nCnt].pos.y, g_Rain[nCnt].pos.z);
				D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

				//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffRain, 0, sizeof(VERTEX_3D));

				pDevice->SetFVF(FVF_VERTEX_3D);


				pDevice->SetTexture(0, NULL);

				//�r���{�[�h
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
		}
	}
}

//====================================================
//�J�̐ݒ菈��
//====================================================
void SetRain(void)
{
	int randPosX;			//rand�p�̕ϐ�
	int randPosZ;			//rand�p�̕ϐ�
	int randMove;			//rand�p�̕ϐ�

	for (int nCnt = 0; nCnt < MAX_RAIN; nCnt++)
	{
		if (g_Rain[nCnt].bUse == false)
		{
			randPosX = rand() % 601;
			randPosZ = rand() % 501;
			randMove = rand() % 11;

			g_Rain[nCnt].pos = D3DXVECTOR3((float)randPosX - 50.0f, 250.0f, (float)randPosZ + 50.0f);
			g_Rain[nCnt].move = D3DXVECTOR3(0.0f, -15.0f + (float)-randMove, 0.0f);
			g_Rain[nCnt].bUse = true;
			break;
		}
	}
}

//=========================================================================
//�J�̕\���擾����
//=========================================================================
bool GetbRain(void)
{
	return g_bRain;
}

//=========================================================================
//�r���{�[�h�̕\���ݒ�
//=========================================================================
void SetBoolBillboard(bool bRain, bool bMoon)
{
	g_bRain = bRain;
	g_Moon.bUse = bMoon;
}