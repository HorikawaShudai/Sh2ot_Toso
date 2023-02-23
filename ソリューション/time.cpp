//========================================================================================
//
// �^�C������[time.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "main.h"
#include "player.h"
#include "game.h"
#include "result.h"
#include "time.h"

//�}�N����`
#define NUM_PLACE (4)			//�^�C���̌���
#define X_SIZE (25)				//�^�C���̉���
#define Y_SIZE (25)				//�^�C���̏c��
#define WIDE_SIZE (50)			//�^�C�����m�̕�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//���_�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posTime[NUM_PLACE];					//�^�C���̈ʒu
int g_nCountTime;									//�^�C���̃J�E���g
int g_nTime;										//�^�C���̒l
int g_nMaxTime;										//�^�C���̍ő�l
int g_aTexU[NUM_PLACE];								//�e�N�X�`���̓ǂݍ��݈ʒu
bool g_bTimeCount;									//���Ԃ������߂邩�ǂ���
float g_TimeWait;									//���Ԃ��I��������̗]�C
float g_TimeStart;									//���Ԃ��I��������̕\��

//====================================================================
//�^�C���̏���������
//====================================================================
void InitTime(void)
{
	int nCntTime;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureTime);

	g_posTime[0] = D3DXVECTOR3(555.0f, 680.0f, 0.0f);	//10���̌��̈ʒu�ݒ�
	g_posTime[1] = D3DXVECTOR3(605.0f, 680.0f, 0.0f);	//�P���̌��̈ʒu�ݒ�
	g_posTime[2] = D3DXVECTOR3(680.0f, 680.0f, 0.0f);	//10�b�̌��̈ʒu�ݒ�
	g_posTime[3] = D3DXVECTOR3(730.0f, 680.0f, 0.0f);	//�P�b�̌��̈ʒu�ݒ�

	g_nCountTime = 0;

	g_bTimeCount = true;
	g_TimeWait = 0.0f;									//���Ԃ��I��������̗]�C
	g_TimeStart = 0.0f;									//���Ԃ��I��������̕\��


														//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
	{
		//���_���W�̐ݒ� 
		pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE, g_posTime[nCntTime].y - Y_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE, g_posTime[nCntTime].y - Y_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE, g_posTime[nCntTime].y + Y_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE, g_posTime[nCntTime].y + Y_SIZE, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���Ԃ̏���������
	g_aTexU[0] = 0;
	g_aTexU[1] = 4;
	g_aTexU[2] = 0;
	g_aTexU[3] = 0;

	g_nMaxTime = (g_aTexU[3] + g_aTexU[2] * 10 + g_aTexU[1] * 60 + g_aTexU[0] * 600) * 60;
	g_nTime = (g_aTexU[3] + g_aTexU[2] * 10 + g_aTexU[1] * 60 + g_aTexU[0] * 600);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//====================================================================
//�^�C���̏I������
//====================================================================
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

////====================================================================
////�^�C���̍X�V����(�v���X)
////====================================================================
//void UpdateTime(void)
//{
//	MODE g_Mode = GetMode();	//�Q�[�����[�h������
//	int nCntTime;
//
//	g_nCountTime++;
//	if (g_Mode == MODE_GAME)
//	{
//		if (g_nCountTime >= 60)
//		{
//			g_nCountTime = 0;
//			if (g_aTexU[3] >= 9)
//			{
//				g_aTexU[3] = 0;
//				if (g_aTexU[2] >= 5)
//				{
//					g_aTexU[2] = 0;
//					if (g_aTexU[1] >= 9)
//					{
//						g_aTexU[1] = 0;
//						if (g_aTexU[0] >= 5)
//						{
//							g_aTexU[0] = 0;
//						}
//						else
//						{
//							g_aTexU[0]++;
//						}
//					}
//					else
//					{
//						g_aTexU[1]++;
//					}
//				}
//				else
//				{
//					g_aTexU[2]++;
//				}
//			}
//			else
//			{
//				g_aTexU[3]++;
//			}
//		}
//	}
//
//	VERTEX_2D*pVtx;	//���_�|�C���^������
//
//					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
//	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
//	{
//		switch (g_Mode)
//		{
//		case MODE_GAME:
//			g_posTime[0] = D3DXVECTOR3(1075.0f, 100.0f, 0.0f);
//
//			g_posTime[1] = D3DXVECTOR3(1125.0f, 100.0f, 0.0f);
//
//			g_posTime[2] = D3DXVECTOR3(1200.0f, 100.0f, 0.0f);
//
//			g_posTime[3] = D3DXVECTOR3(1250.0f, 100.0f, 0.0f);
//
//			//���_���W�̐ݒ� 
//			pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE, g_posTime[nCntTime].y - Y_SIZE, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE, g_posTime[nCntTime].y - Y_SIZE, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE, g_posTime[nCntTime].y + Y_SIZE, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE, g_posTime[nCntTime].y + Y_SIZE, 0.0f);
//
//			break;
//		case MODE_RESULT:
//			g_posTime[0] = D3DXVECTOR3(550.0f, 420.0f, 0.0f);
//
//			g_posTime[1] = D3DXVECTOR3(650.0f, 420.0f, 0.0f);
//
//			g_posTime[2] = D3DXVECTOR3(800.0f, 420.0f, 0.0f);
//
//			g_posTime[3] = D3DXVECTOR3(900.0f, 420.0f, 0.0f);
//
//			//���_���W�̐ݒ� 
//			pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE * 2, g_posTime[nCntTime].y - Y_SIZE * 2, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE * 2, g_posTime[nCntTime].y - Y_SIZE * 2, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntTime].x - X_SIZE * 2, g_posTime[nCntTime].y + Y_SIZE * 2, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntTime].x + X_SIZE * 2, g_posTime[nCntTime].y + Y_SIZE * 2, 0.0f);
//
//		}
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f + g_aTexU[nCntTime] * 0.1f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(0.1f + g_aTexU[nCntTime] * 0.1f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f + g_aTexU[nCntTime] * 0.1f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(0.1f + g_aTexU[nCntTime] * 0.1f, 1.0f);
//
//		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
//	}
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffTime->Unlock();
//}

//====================================================================
//�^�C���̍X�V����(�}�C�i�X)
//====================================================================
void UpdateTime(void)
{
	if (g_bTimeCount == true)
	{//�^�C���̃J�E���g�_�E�����\�Ȏ�
		int nCntTime;
		g_nCountTime++;	//�J�E���g�𑝂₷

		if (g_nCountTime >= 60)
		{//60�t���[�����o�߂�����
			g_nCountTime = 0;	//�t���[�������Z�b�g����

			if (g_aTexU[3] <= 0)
			{//�P�b�̌����O�̎�
				g_aTexU[3] = 9;	//�P�b�̌����X�ɂ���

				if (g_aTexU[2] <= 0)
				{//10�b�̌����O�̎�
					g_aTexU[2] = 5;//10�b�̌����T�ɂ���

					if (g_aTexU[1] <= 0)
					{//�P���̌����O�̎�
						g_aTexU[1] = 9;

						if (g_aTexU[0] <= 0)
						{//10���̌����O�̎�
							g_aTexU[0] = 5;
						}
						else
						{//10���̌����O�ł͂Ȃ���
							g_aTexU[0]--;	//�P�b�̌�������������
						}
					}
					else
					{//�P���̌����O�ł͂Ȃ���
						g_aTexU[1]--;	//�P���̌�������������
					}
				}
				else
				{//10�b�̌����O�ł͂Ȃ���
					g_aTexU[2]--;	//10�b�̌�������������
				}
			}
			else
			{//�P�b�̌����O�ł͂Ȃ���
				g_aTexU[3]--;	//�P�b�̌�������������
			}
		}

		g_nTime = (g_aTexU[3] + g_aTexU[2] * 10 + g_aTexU[1] * 100 + g_aTexU[0] * 1000);

		VERTEX_2D*pVtx;	//���_�|�C���^������

		//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_aTexU[nCntTime] * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + g_aTexU[nCntTime] * 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_aTexU[nCntTime] * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + g_aTexU[nCntTime] * 0.1f, 1.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTime->Unlock();
	}

	if (g_aTexU[0] == 0 && g_aTexU[1] == 0 && g_aTexU[2] == 0 && g_aTexU[3] == 0)
	{//�������Ԃ��O�ɂȂ����Ƃ�
		PlayerAllDown();
	}
}

//====================================================================
//�^�C���̕`�揈��
//====================================================================
void DrawTime(void)
{
	int nCntTime;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);
	for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCntTime,							//�v���~�e�B�u(�|���S��)��
			2);
	}
}

//====================================================================
//�^�C���̎擾
//====================================================================
bool GetTime(void)
{
	return g_bTimeCount;
}