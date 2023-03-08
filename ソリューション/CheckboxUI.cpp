#include "CheckboxUI.h"
#include "fade.h"
#include "player.h"
#include "PlayNumberSelect.h"
#include "EscapeTutorial.h"
#include "input.h"
#include "key.h"
#include "enemy.h"
#include "sound.h"

//�}�N����`
#define MAX_CHECK_TEX		(2)				//�`�F�b�N�{�b�N�X�̃e�N�X�`���ő吔

//�`�F�b�N�{�b�N�X�̈ʒu
//��E��v���C
#define CHECKUIPOS_X_0		(990.0f)		//�`�F�b�N�{�b�N�X��UI��X�ʒu(1�l��)
#define CHECKUIPOS_Y_0		(680.0f)		//�`�F�b�N�{�b�N�X��UI��Y�ʒu(1�l��)

#define CHECKUIPOS_X_1		(550.0f)		//�`�F�b�N�{�b�N�X��UI��X�ʒu(1�l��)
#define CHECKUIPOS_Y_1		(680.0f)		//�`�F�b�N�{�b�N�X��UI��Y�ʒu(1�l��)

#define CHECKUIPOS_X_2		(1140.0f)		//�`�F�b�N�{�b�N�X��UI��X�ʒu(2�l��)
#define CHECKUIPOS_Y_2		(680.0f)		//�`�F�b�N�{�b�N�X��UI��Y�ʒu(2�l��)

//�O�E�l�l�v���C
#define CHECKUIPOS_X_1_34	(550.0f)		//�`�F�b�N�{�b�N�X��UI��X�ʒu(1�l��)
#define CHECKUIPOS_Y_1_34	(320.0f)		//�`�F�b�N�{�b�N�X��UI��Y�ʒu(1�l��)

#define CHECKUIPOS_X_2_34	(1190.0f)		//�`�F�b�N�{�b�N�X��UI��X�ʒu(2�l��)
#define CHECKUIPOS_Y_2_34	(320.0f)		//�`�F�b�N�{�b�N�X��UI��Y�ʒu(2�l��)

#define CHECKUIPOS_X_3_34	(550.0f)		//�`�F�b�N�{�b�N�X��UI��X�ʒu(3�l��)
#define CHECKUIPOS_Y_3_34	(680.0f)		//�`�F�b�N�{�b�N�X��UI��Y�ʒu(3�l��)

#define CHECKUIPOS_X_4_34	(1190.0f)		//�`�F�b�N�{�b�N�X��UI��X�ʒu(4�l��)
#define CHECKUIPOS_Y_4_34	(680.0f)		//�`�F�b�N�{�b�N�X��UI��Y�ʒu(4�l��)

//�S�̂ɕ\�����Ă鎞
#define CHECKUIPOS_X_3_0	(100.0f)		//�`���[�g���A���p�����o�Ă���Ƃ���X�ʒu(1�l��)
#define CHECKUIPOS_Y_3_0	(550.0f)		//�`���[�g���A���p�����o�Ă���Ƃ���Y�ʒu(1�l��)

#define CHECKUIPOS_X_3_1	(200.0f)		//�`���[�g���A���p�����o�Ă���Ƃ���X�ʒu(2�l��)
#define CHECKUIPOS_Y_3_1	(550.0f)		//�`���[�g���A���p�����o�Ă���Ƃ���Y�ʒu(2�l��)

#define CHECKUIPOS_X_3_2	(900.0f)		//�`���[�g���A���p�����o�Ă���Ƃ���X�ʒu(3�l��)
#define CHECKUIPOS_Y_3_2	(550.0f)		//�`���[�g���A���p�����o�Ă���Ƃ���Y�ʒu(3�l��)

#define CHECKUIPOS_X_3_3	(1000.0f)		//�`���[�g���A���p�����o�Ă���Ƃ���X�ʒu(4�l��)
#define CHECKUIPOS_Y_3_3	(550.0f)		//�`���[�g���A���p�����o�Ă���Ƃ���Y�ʒu(4�l��)

#define CHECKUI_WIDTH		(40.0f)			//�`�F�b�N�{�b�N�X��UI�̕�
#define CHECKUI_HEIGHT		(40.0f)			//�`�F�b�N�{�b�N�X��UI�̍���
#define CHECKUI_INTERVAL	(50.0f)			//�`�F�b�N�{�b�N�X��UI���m�̊Ԋu

#define UP_CHECKBOXUI				(100.0f)	//�������o���Ƃ��̏㏸�x
#define UP_CHECKBOXUI_COUNTER_MAX	(100)		//�������o�������̃J�E���^�[
#define UP_CHECKBOXUI_WAITCOUNTER	(60)		//���ڒB�����̗]�C

//�`�F�b�N�{�b�N�XUI�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	 //��UI�̈ʒu
	int nCheckUI;		 //��UI�̐�
	bool bUse;			 //�g���Ă��邩�ǂ���
}CHECKUI;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureCheckUI[MAX_CHECK_TEX] = {};  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCheckUI = NULL;			//���_�o�b�t�@�ւ̃|�C���^
CHECKUI g_anCheckUI[NUM_PLAYER];							//�`�F�b�N�{�b�N�X��UI�̏��
int g_NumPlayerCheckUI;
bool btutorial;  //�`���[�g���A���p�����\������Ă��邩�ǂ���
int ChecboxUITrueCounter;			//�������o���Ƃ��̃J�E���^�[
int ChecboxUIWaitCount;				//�`�F�b�N�����ꂽ�Ƃ��̗]�C

//====================================================================
//�`�F�b�N�{�b�N�X�̏���������
//====================================================================
void InitCheckboxUI(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//�ϐ��錾
	int nCntCheckUI;

	//�O���[�o���錾�̏�����
	g_NumPlayerCheckUI = 0;
	ChecboxUITrueCounter = 0;
	ChecboxUIWaitCount = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\no_check.png",
		&g_pTextureCheckUI[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\use_check.png",
		&g_pTextureCheckUI[1]);

	for (nCntCheckUI = 0; nCntCheckUI < NUM_PLAYER; nCntCheckUI++)
	{
		g_anCheckUI[nCntCheckUI].bUse = true;  //�g���Ă��邱�Ƃ�
	}

	//��UI�̏���������
	for (nCntCheckUI = 0; nCntCheckUI < PlayNumber.CurrentSelectNumber; nCntCheckUI++)
	{
		if (nCntCheckUI == 0)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_0, CHECKUIPOS_Y_3_0, 0.0f);  //1�l�ڂ̈ʒu��������
		}

		if (nCntCheckUI == 1)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_1, CHECKUIPOS_Y_3_1, 0.0f);  //2�l�ڂ̈ʒu��������
		}

		if (nCntCheckUI == 2)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_2, CHECKUIPOS_Y_3_2, 0.0f);  //3�l�ڂ̈ʒu��������
		}

		if (nCntCheckUI == 3)
		{
			g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_3, CHECKUIPOS_Y_3_3, 0.0f);  //4�l�ڂ̈ʒu��������
		}
		g_anCheckUI[nCntCheckUI].nCheckUI = 3;		//��UI�̒l��������
		g_anCheckUI[nCntCheckUI].bUse = false;  //�g���Ă��Ȃ����Ƃ�
		btutorial = true;  //�`���[�g���A���p�����g���Ă��邱�Ƃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCheckUI,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCheckUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y - CHECKUI_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y - CHECKUI_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y + CHECKUI_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_anCheckUI[nCnt].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCnt].pos.y + CHECKUI_HEIGHT, 0.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCheckUI->Unlock();
}

//====================================================================
//�`�F�b�N�{�b�N�X�̏I������
//====================================================================
void UninitCheckboxUI(void)
{
	for (int nCnt = 0; nCnt < MAX_CHECK_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureCheckUI[nCnt] != NULL)
		{
			g_pTextureCheckUI[nCnt]->Release();
			g_pTextureCheckUI[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCheckUI != NULL)
	{
		g_pVtxBuffCheckUI->Release();
		g_pVtxBuffCheckUI = NULL;
	}
}

//====================================================================
//�`�F�b�N�{�b�N�X�̍X�V����
//====================================================================
void UpdateCheckboxUI(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//�v���C���[���̏���
	Player *pPlayer = GetPlayer();

	//�ϐ��錾
	int nCntCheckUI;

	switch (GetEscapeTutorial())
	{
	case TUTORIAL_STATE_STANDBY:
		//�X�^���o�C��Ԃ̎��Ƀ`�F�b�N���I���ɂ�����͏���
		for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++)
		{
			if ((GetKeyboardTrigger(DIK_N)) || (GetGamepadTrigger(BUTTON_A, nCntPlayer) || GetGamepadTrigger(BUTTON_B, nCntPlayer)) && ChecboxUITrueCounter >= UP_CHECKBOXUI_COUNTER_MAX)
			{
				SetCheckUI(nCntPlayer, true);
			}
		}

		//�������o������
		if (ChecboxUITrueCounter < UP_CHECKBOXUI_COUNTER_MAX)
		{
			ChecboxUITrueCounter++;
		}
		break;
	case TUTORIAL_STATE_WAIT:

		//�������܂�����
		if (ChecboxUITrueCounter > 0)
		{
			ChecboxUITrueCounter--;
		}
		break;
	}

	if (g_anCheckUI[0].bUse == true && g_anCheckUI[1].bUse == true && g_anCheckUI[2].bUse == true && g_anCheckUI[3].bUse == true)
	{
		switch (GetEscapeTutorial())
		{
		case TUTORIAL_STATE_PLAY:
			ChecboxUIWaitCount++;
			if (ChecboxUIWaitCount >= UP_CHECKBOXUI_WAITCOUNTER)
			{
				ChecboxUIWaitCount = 0;
				for (int nCntPlayer = 0; nCntPlayer < PlayNumber.CurrentSelectNumber; nCntPlayer++, pPlayer++)
				{
					pPlayer->MoveState = PLAYER_MOVESTATE_NORMAL;
					GetGamepad_Vibrtion_false(nCntPlayer);
				}

				switch (GetDoEscapeTutorial())
				{
				case MODE_MOVE:
					//�`���[�g���A���p�����J�����ړ���
					DoEscapeTutorial(MODE_DASH);
					break;
				case MODE_DASH:
					//�`���[�g���A���p�����o�C�u��
					DoEscapeTutorial(MODE_VIBE);

					SetEnemy(D3DXVECTOR3(-1050.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					break;
				case MODE_VIBE:
					//�`���[�g���A���p�����X�e���X��
					DoEscapeTutorial(MODE_STELTH);
					break;
				case MODE_STELTH:
					//�`���[�g���A���p���������Ƃ��
					DoEscapeTutorial(MODE_GET_KEY);

					FalseEnemy();

					for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
					{
						SetKey(D3DXVECTOR3(-1150.0f + (50.0f * nCntTutorial), 3.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), KEY_TYPE_ITEM);
					}

					break;
				case MODE_GET_KEY:
					//�`���[�g���A���p����E�o��
					DoEscapeTutorial(MODE_ESCAPE);
					break;
				case MODE_ESCAPE:
					//�`���[�g���A���p�����`���[�g���A�����ڂ̏I����
					DoEscapeTutorial(MODE_GOEXIT);
					break;
				case MODE_GOEXIT:
					//�`���[�g���A���p�����`���[�g���A�����ڂ̏I����
					DoEscapeTutorial(MODE_END);
					break;
				}
				//�`�F�b�N�{�b�N�X��l�����I�t�ɂ���
				for (int nCntTutorial = 0; nCntTutorial < GetPlayNumberSelect().CurrentSelectNumber; nCntTutorial++)
				{
					g_anCheckUI[nCntTutorial].bUse = false;
				}
				SetEscapeTutorial(TUTORIAL_STATE_STANDBY);
				//���̉�
				PlaySound(SOUND_LABEL_PAPER);
			}
			break;

		case TUTORIAL_STATE_STANDBY:
			SetEscapeTutorial(TUTORIAL_STATE_WAIT);
			//���̉�
			PlaySound(SOUND_LABEL_PAPER);
			break;
		}
	}

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCheckUI->Lock(0, 0, (void**)&pVtx, 0);

	//�`���[�g���A���p�����g���Ă��Ȃ�������
	if (btutorial == false)
	{
		//��UI�̏���������
		for (nCntCheckUI = 0; nCntCheckUI < PlayNumber.CurrentSelectNumber; nCntCheckUI++)
		{
			switch (PlayNumber.CurrentSelectNumber)
			{
			case 1:
				if (nCntCheckUI == 0)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_0, CHECKUIPOS_Y_0, 0.0f);  //1�l�ڂ̈ʒu��������
				}
				break;

			case 2:
				if (nCntCheckUI == 0)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_1, CHECKUIPOS_Y_1, 0.0f);  //1�l�ڂ̈ʒu��������
				}
				if (nCntCheckUI == 1)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_2, CHECKUIPOS_Y_1, 0.0f);  //2�l�ڂ̈ʒu��������
				}
				break;

			case 3:
				if (nCntCheckUI == 0)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_1_34, CHECKUIPOS_Y_1_34, 0.0f);  //1�l�ڂ̈ʒu��������
				}
				if (nCntCheckUI == 1)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_2_34, CHECKUIPOS_Y_2_34, 0.0f);  //2�l�ڂ̈ʒu��������
				}
				if (nCntCheckUI == 2)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_34, CHECKUIPOS_Y_3_34, 0.0f);  //3�l�ڂ̈ʒu��������
				}

				if (nCntCheckUI == 3)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_4_34, CHECKUIPOS_Y_4_34, 0.0f);  //4�l�ڂ̈ʒu��������
				}
				break;

			case 4:
				if (nCntCheckUI == 0)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_1_34, CHECKUIPOS_Y_1_34, 0.0f);  //1�l�ڂ̈ʒu��������
				}
				if (nCntCheckUI == 1)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_2_34, CHECKUIPOS_Y_2_34, 0.0f);  //2�l�ڂ̈ʒu��������
				}
				if (nCntCheckUI == 2)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_34, CHECKUIPOS_Y_3_34, 0.0f);  //3�l�ڂ̈ʒu��������
				}

				if (nCntCheckUI == 3)
				{
					g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_4_34, CHECKUIPOS_Y_4_34, 0.0f);  //4�l�ڂ̈ʒu��������
				}
				break;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH, g_anCheckUI[nCntCheckUI].pos.y - CHECKUI_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH, g_anCheckUI[nCntCheckUI].pos.y - CHECKUI_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH, g_anCheckUI[nCntCheckUI].pos.y + CHECKUI_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH, g_anCheckUI[nCntCheckUI].pos.y + CHECKUI_HEIGHT, 0.0f);

			pVtx += 4;

		}
	}

	//�`���[�g���A���p�����g���Ă�����
	else
	{
		//��UI�̏���������
		for (nCntCheckUI = 0; nCntCheckUI < PlayNumber.CurrentSelectNumber; nCntCheckUI++)
		{
			if (nCntCheckUI == 0)
			{
				g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_0, CHECKUIPOS_Y_3_0, 0.0f);  //1�l�ڂ̈ʒu��������
			}

			if (nCntCheckUI == 1)
			{
				g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_1, CHECKUIPOS_Y_3_1, 0.0f);  //2�l�ڂ̈ʒu��������
			}

			if (nCntCheckUI == 2)
			{
				g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_2, CHECKUIPOS_Y_3_2, 0.0f);  //3�l�ڂ̈ʒu��������
			}

			if (nCntCheckUI == 3)
			{
				g_anCheckUI[nCntCheckUI].pos = D3DXVECTOR3(CHECKUIPOS_X_3_3, CHECKUIPOS_Y_3_3, 0.0f);  //4�l�ڂ̈ʒu��������
			}

			////���_���W�̐ݒ�
			//pVtx[0].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y - CHECKUI_HEIGHT, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y - CHECKUI_HEIGHT, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + CHECKUI_HEIGHT, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + CHECKUI_HEIGHT, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + (UP_CHECKBOXUI * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter)) - CHECKUI_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + (UP_CHECKBOXUI * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter)) - CHECKUI_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x - CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + (UP_CHECKBOXUI * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter)) + CHECKUI_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_anCheckUI[nCntCheckUI].pos.x + CHECKUI_WIDTH + (nCntCheckUI * CHECKUI_INTERVAL), g_anCheckUI[nCntCheckUI].pos.y + (UP_CHECKBOXUI * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter)) + CHECKUI_HEIGHT, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter));
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter));
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter));
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * ((float)UP_CHECKBOXUI_COUNTER_MAX / (float)ChecboxUITrueCounter));

			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCheckUI->Unlock();
}

//====================================================================
//�`�F�b�N�{�b�N�X�̕`�揈��
//====================================================================
void DrawCheckboxUI(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C�l�����̎擾
	PlayNumberSelect PlayNumber = GetPlayNumberSelect();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCheckUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < PlayNumber.CurrentSelectNumber; nCnt++)
	{
		if (g_anCheckUI[nCnt].bUse == false)
		{//�`�F�b�N�����Ă��Ȃ��Ƃ�
		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCheckUI[0]);
		}

		else
		{//�`�F�b�N�������Ƃ�
		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCheckUI[1]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//============================
//�`�F�b�N�{�b�N�X�̐ݒ�
//============================
void SetCheckUI(int nPlayer, bool SetCheck)
{
	if (g_anCheckUI[nPlayer].bUse == false)
	{
		if (SetCheck == true)
		{
			//���̉�
			PlaySound(SOUND_LABEL_ENTER);
		}
	}

	g_anCheckUI[nPlayer].bUse = SetCheck;
}

//============================
//�`�F�b�N�{�b�N�X�̈ʒu�ݒ�
//============================
void MovePosCheckUI(int nPlayer, bool SetCheck)
{
	btutorial = SetCheck;
}

