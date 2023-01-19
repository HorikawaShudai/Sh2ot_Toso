//======================================================================================
//
// �X�^�~�i����[title.cpp]
// Author:
//
//======================================================================================
#include "stamina.h"
#include "player.h"

//**********************************************
//�}�N����`
//**********************************************
#define NUM_TEX			(1)			// �e�N�X�`���̐�

#define STAMINA_WIDTH	(400.0f)	// �X�^�~�i�̕�(�X�^�~�i�̍ő�l)
#define STAMINA_HEIGHT	(10.0f)		// �X�^�~�i�̍���

#define DEC_SPEED		(2.0f)		// �X�^�~�i�̌���X�s�[�h
#define RECOVERY_SPEED	(0.7f)		// �X�^�~�i�̉񕜃X�s�[�h
#define TIRED_VALUE		(150)		// �ԃQ�[�W�ɓ��鐔�l

//**********************************************
// �e�N�X�`����
//**********************************************
const char *c_apStaminaTexName[NUM_TEX] =
{
	"Data\\TEXTURE\\Stamina.png",			//�X�^�~�i�Q�[�W
};

//**********************************************
//�v���g�^�C�v�錾
//**********************************************
void InitStaminaGauge(void);						//�X�^�~�i�Q�[�W�̏�����

void UpdateStaminaGauge(void);						//�X�^�~�i�Q�[�W�̍X�V
void StaminaIAD(int nCntStamina);								//�X�^�~�i�̑���

//**********************************************
//�O���[�o���ϐ�
//**********************************************
LPDIRECT3DTEXTURE9 g_apTextureStamina[NUM_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStamina = NULL;			//���_�o�b�t�@�ւ̃|�C���^

Stamina g_aStamina[NUM_PLAYER];					//�X�^�~�i���

//============================================================================
//����������
//============================================================================
void InitStamina(void)
{
	//�ϐ��錾
	int nCntStamina;

	//�f�o�C�X�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�O���[�o���錾�̏�����
	for (nCntStamina = 0; nCntStamina < NUM_PLAYER; nCntStamina++)
	{
		g_aStamina[nCntStamina].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 700.0f, 0.0f);			//�ʒu
		g_aStamina[nCntStamina].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);						//�F
		g_aStamina[nCntStamina].nFalseTime = 0;													//�X�^�~�i���g���Ă��Ȃ��Ƃ��̃J�E���g
		g_aStamina[nCntStamina].fStamina = STAMINA_WIDTH;										//�X�^�~�i
		g_aStamina[nCntStamina].bUse = false;													//�g���Ă��Ȃ����
	}

	//�e�N�X�`���ǂݍ���
	for (nCntStamina = 0; nCntStamina < NUM_TEX; nCntStamina++)
	{
		D3DXCreateTextureFromFile(pDevice, c_apStaminaTexName[nCntStamina], &g_apTextureStamina[nCntStamina]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TEX,
		D3DUSAGE_WRITEONLY, { FVF_VERTEX_2D }, D3DPOOL_MANAGED,
		&g_pVtxBuffStamina,
		NULL);
	
	InitStaminaGauge();			//�X�^�~�i�Q�[�W
}

//============================================================================
//�I������
//============================================================================
void UninitStamina(void)
{
	for (int nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureStamina[nCntTitle] != NULL)
		{
			g_apTextureStamina[nCntTitle]->Release();
			g_apTextureStamina[nCntTitle] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStamina != NULL)
	{
		g_pVtxBuffStamina->Release();
		g_pVtxBuffStamina = NULL;
	}
}

//============================================================================
//�X�V����
//============================================================================
void UpdateStamina(void)
{
	//�I������
	UpdateStaminaGauge();
}

//============================================================================
//�`�揈��
//============================================================================
void DrawStamina(void)
{
	//�f�o�C�X�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStamina, 0, sizeof(VERTEX_2D));

	for (int nCntTitle = 0; nCntTitle < NUM_TEX; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureStamina[nCntTitle]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}
}

//============================================================================
// �X�^�~�i�̃Z�b�g����
//============================================================================
void SetStamina(D3DXVECTOR3 pos)
{
	for (int nCntStamina = 0; nCntStamina < 128; nCntStamina++)
	{
		if (g_aStamina[nCntStamina].bUse == false)
		{
			g_aStamina[nCntStamina].pos = pos;
		}
	}
}

//************************************
//������������
//************************************
// �X�^�~�i�Q�[�W�̏�����
void InitStaminaGauge(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//Player *pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStamina = 0; nCntStamina < NUM_PLAYER; nCntStamina++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fStamina,	g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fStamina,	g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fStamina,	g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fStamina,	g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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

		pVtx += 4;			//���_����4�����炷
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffStamina->Unlock();
}

//************************************
//�X�V�������̏���
//************************************
// �X�^�~�i�̓���
void UpdateStaminaGauge(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;
	
	//�v���C���[���̎擾
	Player *pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStamina = 0; nCntStamina < NUM_PLAYER; nCntStamina++)
	{
		if (pPlayer->bUse == true/* && g_aStamina[nCntStamina].bUse == true*/)
		{//�g���Ă����ꍇ
			//�X�^�~�i�̑���
			StaminaIAD(nCntStamina);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fStamina, g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fStamina, g_aStamina[nCntStamina].pos.y - STAMINA_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x - g_aStamina[nCntStamina].fStamina, g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aStamina[nCntStamina].pos.x + g_aStamina[nCntStamina].fStamina, g_aStamina[nCntStamina].pos.y + STAMINA_HEIGHT, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_aStamina[nCntStamina].col.r, g_aStamina[nCntStamina].col.g, g_aStamina[nCntStamina].col.b, g_aStamina[nCntStamina].col.a);
			pVtx[1].col = D3DXCOLOR(g_aStamina[nCntStamina].col.r, g_aStamina[nCntStamina].col.g, g_aStamina[nCntStamina].col.b, g_aStamina[nCntStamina].col.a);
			pVtx[2].col = D3DXCOLOR(g_aStamina[nCntStamina].col.r, g_aStamina[nCntStamina].col.g, g_aStamina[nCntStamina].col.b, g_aStamina[nCntStamina].col.a);
			pVtx[3].col = D3DXCOLOR(g_aStamina[nCntStamina].col.r, g_aStamina[nCntStamina].col.g, g_aStamina[nCntStamina].col.b, g_aStamina[nCntStamina].col.a);
		}

		pVtx += 4;			//���_����4�����炷
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffStamina->Unlock();
}

// �X�^�~�i�̑�������
void StaminaIAD(int nCntStamina)
{
	//�v���C���[���̎擾
	Player *pPlayer = GetPlayer();

	//�v���C���[�̏�Ԃ��_�b�V����Ԃ̏ꍇ
	if (pPlayer->MoveState == PLAYER_MOVESTATE_DASH)
	{
		g_aStamina[nCntStamina].fStamina -= 1.5f;			//�X�^�~�i�����炷

		g_aStamina[nCntStamina].col.a = 0.5f;				//�X�^�~�i�Q�[�W��\��
	}
	else if(g_aStamina[nCntStamina].fStamina <= STAMINA_WIDTH)
	{//�X�^�~�i�������Ă����ꍇ

		g_aStamina[nCntStamina].fStamina += 0.7f;			//�X�^�~�i���񕜂���


		if (g_aStamina[nCntStamina].fStamina < TIRED_VALUE)
		{
			g_aStamina[nCntStamina].col.r = 1.0f;
		}

		if (g_aStamina[nCntStamina].fStamina > TIRED_VALUE)
		{
			g_aStamina[nCntStamina].col.r = 0.5f;

			//�ʏ��Ԃɂ���
			pPlayer->MoveState = PLAYER_MOVESTATE_NORMAL;
		}
	}

	//��J��ԈȊO�̏ꍇ
	if (pPlayer->MoveState != PLAYER_MOVESTATE_FATIGE && g_aStamina[nCntStamina].fStamina >= STAMINA_WIDTH)
	{
		//�J�E���g��i�߂�
		g_aStamina[nCntStamina].nFalseTime++;

		if (g_aStamina[nCntStamina].nFalseTime > 120)
		{
			g_aStamina[nCntStamina].col.a -= 0.01f;			//a�l�����炷
		}
	}

	//�X�^�~�i�Q�[�W��0�ȉ��ɍs���Ȃ��悤��
	if (g_aStamina[nCntStamina].fStamina <= 0.0f)
	{
		g_aStamina[nCntStamina].fStamina = 0.0f;

		//��J��Ԃɂ���
		pPlayer->MoveState = PLAYER_MOVESTATE_FATIGE;
	}

	//�F�̂�0.0f�ȉ��A1.0f�ȏ�s���Ȃ��悤��
	if (g_aStamina[nCntStamina].col.a <= 0.0f)
	{//0.0f�ȉ�
		g_aStamina[nCntStamina].col.a = 0.0f;

		g_aStamina[nCntStamina].nFalseTime = 0;
	}
	else if (g_aStamina[nCntStamina].col.a >= 1.0f)
	{//1.0f�ȏ�
		g_aStamina[nCntStamina].col.a = 1.0f;
	}
}