//============================
//
//���C�t����(life.cpp)
//Author:���� �F�M
//
//============================
#include "Life.h"
#include "fade.h"
#include "life.h"
#include "player.h"
#include "PlayNumberSelect.h"

//�}�N����`
#define NUM_PLACE     (3)			//���C�t�̐�
#define MAX_PLAYER    (NUM_PLAYER)	//�v���C���[�̍ő吔

#define LIFEPOS_X_0     (30.0f)		//1�l�ڃ��C�t��X�ʒu
#define LIFEPOS_Y_0     (50.0f)		//1�l�ڃ��C�t��Y�ʒu

#define LIFEPOS_X_1     (670.0f)	//2�l�ڃ��C�t��X�ʒu
#define LIFEPOS_Y_1     (50.0f)		//2�l�ڃ��C�t��Y�ʒu

#define LIFEPOS_X_2     (30.0f)		//3�l�ڃ��C�t��X�ʒu
#define LIFEPOS_Y_2     (400.0f)	//3�l�ڃ��C�t��Y�ʒu

#define LIFEPOS_X_3     (670.0f)	//4�l�ڃ��C�t��X�ʒu
#define LIFEPOS_Y_3     (400.0f)	//4�l�ڃ��C�t��Y�ʒu

#define LIFE_WIDTH    (20.0f)		//���C�t�̕�
#define LIFE_HEIGHT	  (20.0f)		//���C�t�̍���
#define LIFE_INTERVAL (50.0f)		//���C�t���m�̊Ԋu

//���C�t�̍\����
typedef struct
{
	D3DXVECTOR3 pos;  //���C�t�̈ʒu
	int nLife;  //���C�t�̐�
	bool bUse[NUM_PLACE];  //�g���Ă��邩�ǂ���
}LIFE;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL; //���_�o�b�t�@�ւ̃|�C���^
LIFE g_anLife[MAX_PLAYER];			//���C�t�̏��
int g_NumPlayerLife;

//=============================
//  ���C�t�̏�����
//=============================
void InitLife(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//�ϐ��錾
	int nCntLife;

	//�O���[�o���錾�̏�����
	g_NumPlayerLife = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\LIFE.png",
		&g_pTextureLife);

	//���C�t�̏���������
	for (nCntLife = 0; nCntLife < PlayNumber.CurrentSelectNumber; nCntLife++)
	{
		for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
		{
		if (nCntLife == 0)
		{
			g_anLife[nCntLife].pos = D3DXVECTOR3(LIFEPOS_X_0, LIFEPOS_Y_0, 0.0f);  //1�l�ڂ̈ʒu��������
		}

		if (nCntLife == 1)
		{
			g_anLife[nCntLife].pos = D3DXVECTOR3(LIFEPOS_X_1, LIFEPOS_Y_1, 0.0f);  //2�l�ڂ̈ʒu��������
		}

		if (nCntLife == 2)
		{
			g_anLife[nCntLife].pos = D3DXVECTOR3(LIFEPOS_X_2, LIFEPOS_Y_2, 0.0f);  //3�l�ڂ̈ʒu��������
		}

		if (nCntLife == 3)
		{
			g_anLife[nCntLife].pos = D3DXVECTOR3(LIFEPOS_X_3, LIFEPOS_Y_3, 0.0f);  //4�l�ڂ̈ʒu��������
		}
			g_anLife[nCntLife].nLife = 3;		//���C�t�̒l��������
			g_anLife[nCntLife].bUse[nCnt] = true;  //�g���Ă��Ȃ����Ƃ�
		}
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE * MAX_PLAYER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_anLife[nCnt].pos.x - LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_anLife[nCnt].pos.y - LIFE_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_anLife[nCnt].pos.x + LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_anLife[nCnt].pos.y - LIFE_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_anLife[nCnt].pos.x - LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_anLife[nCnt].pos.y + LIFE_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_anLife[nCnt].pos.x + LIFE_WIDTH + (nCntLife * LIFE_INTERVAL), g_anLife[nCnt].pos.y + LIFE_HEIGHT, 0.0f);

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

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

			pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//=====================
//���C�t�̏I������
//=====================
void UninitLife(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//==========================
//���C�t�̍X�V����
//=========================
void UpdateLife(void)
{

}

//======================
//���C�t�̕`�揈��
//======================
void DrawLife(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//�ϐ��錾
	int nCount = 0;
	int nCntLife;

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLife);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber + 1; nCnt++)
	{
		for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
		{
			if (g_anLife[nCnt].bUse[nCntLife] == true)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
			}
			nCount++;
		}
	}
}

//===================================
//���C�t�̐ݒ菈��
//===================================
void SetLife(int nLife,int nPlayer)
{
	g_anLife[nPlayer].bUse[nLife] = false;
}

