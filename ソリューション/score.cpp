//============================
//
//�X�R�A����(score.cpp)
//Author:���� �F�M
//
//============================
#include "score.h"  

//�}�N����`
#define NUM_PLACE		(3)		  //�X�R�A�̌���
#define MAX_SCORE		(128)
#define SCORE_INTERVAL  (80.0f) //�X�R�A�̌��Ԃ̕������߂�
#define SCORE_POS_X		(850.0f)  //�X�R�A��X�ʒu
#define SCORE_POS_Y		(40.0f)  //�X�R�A��Y�ʒu
#define SCORE_WIDTH		(40.0f)  //�X�R�A�̕�
#define SCORE_HEIGHT	(40.0f)	 //�X�R�A�̍���

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore;  //�X�R�A�̈ʒu
int g_nScore;			//�X�R�A�̒l
float g_nWindth;		//���̒l
float g_nHeight;    //�����̒l

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

	//�X�R�A�̏���������
		g_posScore = D3DXVECTOR3(SCORE_POS_X, SCORE_POS_Y, 0.0f);  //�ʒu��������

		g_nScore = 0;		//�X�R�A�̒l

		g_nWindth = (0.0f);

		g_nHeight = (0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH + (nCntScore * SCORE_INTERVAL), g_posScore.y - SCORE_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH + (nCntScore * SCORE_INTERVAL),g_posScore.y -  SCORE_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH + (nCntScore * SCORE_INTERVAL), g_posScore.y + SCORE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH + (nCntScore * SCORE_INTERVAL), g_posScore.y + SCORE_HEIGHT, 0.0f);

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

	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//===============================
//�X�R�A�̐ݒ菈��
//===============================
void SetScore(int nScore)
{
	LPDIRECT3DDEVICE9 pDevice;
	int aTexU[NUM_PLACE];  //�e���̐������i�[
	int nCntScore;
	g_nScore = nScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	aTexU[0] = g_nScore % 1000 / 100;
	aTexU[1] = g_nScore % 100 / 10;
	aTexU[2] = g_nScore % 10 / 1;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

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
void AddScore(int nType)
{
	LPDIRECT3DDEVICE9 pDevice;
	int aTexU[NUM_PLACE];  //�e���̐������i�[
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�����鏈��
	switch (nType)
	{
	case 0:

		g_nScore += 1;

		break;
	}

	//�X�R�A�̏��
	if (g_nScore >= 999)
	{
		g_nScore = 999;
	}
	
	aTexU[0] = g_nScore % 1000 / 100;
	aTexU[1] = g_nScore % 100 / 10;
	aTexU[2] = g_nScore % 10 / 1;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

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
int GetScore(void)
{
	return g_nScore;
}

//==================================
//�X�R�A�̐ݒ�
//==================================
void SetPosScore(D3DXVECTOR3 pos, float nWINDTH, float nHeight)
{
	int nCntScore;

	g_posScore = pos;

	g_nWindth = nWINDTH;

	g_nHeight = nHeight;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH + (nCntScore * SCORE_INTERVAL), g_posScore.y - SCORE_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH + (nCntScore * SCORE_INTERVAL), g_posScore.y - SCORE_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH + (nCntScore * SCORE_INTERVAL), g_posScore.y + SCORE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH + (nCntScore * SCORE_INTERVAL), g_posScore.y + SCORE_HEIGHT, 0.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

