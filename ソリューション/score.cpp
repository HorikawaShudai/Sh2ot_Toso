//============================
//
//�X�R�A����(score.cpp)
//Author:���� �F�M
//
//============================
#include "score.h"  
#include "player.h"  
#include "playNumberSelect.h"  
#include "playModeSelect.h"  

//�}�N����`
#define NUM_PLACE		(3)			 //�X�R�A�̌���
#define MAX_SCORE		(128)		//�X�R�A�̍ő吔
#define SCORE_INTERVAL  (40.0f)		//�X�R�A�̌��Ԃ̕������߂�
#define SCORE_POS_X1	(500.0f)	//�X�R�A��X�ʒu
#define SCORE_POS_Y1	(20.0f)		//�X�R�A��Y�ʒu
#define SCORE_POS_X2	(1150.0f)	//�X�R�A��X�ʒu
#define SCORE_POS_Y2	(400.0f)	//�X�R�A��Y�ʒu
#define SCORE_WIDTH		(20.0f)		//�X�R�A�̕�
#define SCORE_HEIGHT	(20.0f)		//�X�R�A�̍���

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL; //���_�o�b�t�@�ւ̃|�C���^
SCORE g_aScore[NUM_PLAYER];

//=============================
//  �X�R�A�̏�����
//=============================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\time.png",
		&g_pTextureScore);

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		switch (nCntPlayer)
		{
		case 0:
			//�X�R�A�̏���������
			g_aScore[nCntPlayer].posScore = D3DXVECTOR3(SCORE_POS_X1, SCORE_POS_Y1, 0.0f);  //�ʒu��������
			g_aScore[nCntPlayer].nScore = 0;		//�X�R�A�̒l
			g_aScore[nCntPlayer].nWindth = SCORE_WIDTH;
			g_aScore[nCntPlayer].nHeight = SCORE_HEIGHT;
			break;
		case 1:
			//�X�R�A�̏���������
			g_aScore[nCntPlayer].posScore = D3DXVECTOR3(SCORE_POS_X2, SCORE_POS_Y1, 0.0f);  //�ʒu��������
			g_aScore[nCntPlayer].nScore = 0;		//�X�R�A�̒l
			g_aScore[nCntPlayer].nWindth = SCORE_WIDTH;
			g_aScore[nCntPlayer].nHeight = SCORE_HEIGHT;
			break;
		case 2:
			//�X�R�A�̏���������
			g_aScore[nCntPlayer].posScore = D3DXVECTOR3(SCORE_POS_X1, SCORE_POS_Y2, 0.0f);  //�ʒu��������
			g_aScore[nCntPlayer].nScore = 0;		//�X�R�A�̒l
			g_aScore[nCntPlayer].nWindth = SCORE_WIDTH;
			g_aScore[nCntPlayer].nHeight = SCORE_HEIGHT;
			break;
		case 3:
			//�X�R�A�̏���������
			g_aScore[nCntPlayer].posScore = D3DXVECTOR3(SCORE_POS_X2, SCORE_POS_Y2, 0.0f);  //�ʒu��������
			g_aScore[nCntPlayer].nScore = 0;		//�X�R�A�̒l
			g_aScore[nCntPlayer].nWindth = SCORE_WIDTH;
			g_aScore[nCntPlayer].nHeight = SCORE_HEIGHT;
			break;
		}
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE * NUM_PLAYER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aScore[nCntPlayer].posScore.x - g_aScore[nCntPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nCntPlayer].posScore.y - g_aScore[nCntPlayer].nHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aScore[nCntPlayer].posScore.x + g_aScore[nCntPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nCntPlayer].posScore.y - g_aScore[nCntPlayer].nHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aScore[nCntPlayer].posScore.x - g_aScore[nCntPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nCntPlayer].posScore.y + g_aScore[nCntPlayer].nHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aScore[nCntPlayer].posScore.x + g_aScore[nCntPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nCntPlayer].posScore.y + g_aScore[nCntPlayer].nHeight, 0.0f);

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

			pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//=====================
//�X�R�A�̏I������
//=====================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//�X�R�A�̍X�V����
void UpdateScore(void)
{

}

//�X�R�A�̕`�揈��
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();
	//�v���C���[�h���̎擾
	PlayModeSelect PlayMode = GetPlayModeSelect();

	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < NUM_PLACE * PlayNumber.CurrentSelectNumber; nCntScore++)
	{//�|���S���̕`��
		if (PlayMode.CurrentModeNumber == 1)
		{//�v���C���[�h���������[�h�̂Ƃ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
		}
	}
}

//===============================
//�X�R�A�̐ݒ菈��
//===============================
void SetScore(int nScore, int nPlayer)
{
	LPDIRECT3DDEVICE9 pDevice;
	int aTexU[NUM_PLACE * NUM_PLAYER];  //�e���̐������i�[
	int nCntScore;
	g_aScore[nPlayer].nScore = nScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	aTexU[0] = g_aScore[nPlayer].nScore % 1000 / 100;
	aTexU[1] = g_aScore[nPlayer].nScore % 100 / 10;
	aTexU[2] = g_aScore[nPlayer].nScore % 10 / 1;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nPlayer * NUM_PLACE * 4;

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//===============================
//�X�R�A�̉��Z
//===============================
void AddScore(int nType, int nPlayer)
{
	LPDIRECT3DDEVICE9 pDevice;
	int aTexU[NUM_PLACE * NUM_PLAYER];  //�e���̐������i�[
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�����鏈��
	switch (nType)
	{
	case 0:

		g_aScore[nPlayer].nScore += 1;

		break;
	}

	//�X�R�A�̏��
	if (g_aScore[nPlayer].nScore >= 999)
	{
		g_aScore[nPlayer].nScore = 999;
	}

	aTexU[0] = g_aScore[nPlayer].nScore % 1000 / 100;
	aTexU[1] = g_aScore[nPlayer].nScore % 100 / 10;
	aTexU[2] = g_aScore[nPlayer].nScore % 10 / 1;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nPlayer * NUM_PLACE * 4;

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

}

//================================
//�X�R�A���󂯎��
//===============================
int GetScore(int nPlayer)
{
	return g_aScore[nPlayer].nScore;
}

//==================================
//�X�R�A�̐ݒ�
//==================================
void SetPosScore(D3DXVECTOR3 pos, float nWINDTH, float nHeight,int nPlayer)
{
	int nCntScore;

	g_aScore[nPlayer].posScore = pos;

	g_aScore[nPlayer].nWindth = nWINDTH;

	g_aScore[nPlayer].nHeight = nHeight;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aScore[nPlayer].posScore.x - g_aScore[nPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nPlayer].posScore.y - g_aScore[nPlayer].nHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aScore[nPlayer].posScore.x + g_aScore[nPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nPlayer].posScore.y - g_aScore[nPlayer].nHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aScore[nPlayer].posScore.x - g_aScore[nPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nPlayer].posScore.y + g_aScore[nPlayer].nHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aScore[nPlayer].posScore.x + g_aScore[nPlayer].nWindth + (nCntScore * SCORE_INTERVAL), g_aScore[nPlayer].posScore.y + g_aScore[nPlayer].nHeight, 0.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

