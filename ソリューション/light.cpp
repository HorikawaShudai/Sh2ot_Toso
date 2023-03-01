//========================================================================================
//
// ���C�g����[light.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "main.h"
#include "light.h"
#include "game.h"

#define MAX_LIGHT (256)	//�g�p���郉�C�g�̐�

//�O���[�o���ϐ�
D3DLIGHT9 g_light[MAX_LIGHT];	//���C�g�̏��
bool g_bUse[MAX_LIGHT];			//���C�g���g�p���Ă��邩�ǂ���
int g_Light_LightIdx[MAX_LIGHT];//���C�g�̎g�p�ԍ�

////====================================================================
////���C�g�̏���������
////====================================================================
//void InitLight(void)
//{
//	//�f�o�C�X�̏���
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	D3DXVECTOR3 vecDir[MAX_LIGHT];	//�ݒ�p�����x�N�g��
//
//	//���C�g�̏����N���A����
//	ZeroMemory(&g_light, sizeof(D3DLIGHT9));
//
//	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
//	{
//		//���C�g�̎�ނ�ݒ�
//		g_light[nCntlight].Type = D3DLIGHT_DIRECTIONAL;
//
//		//���C�g�̊g�U����ݒ�
//		g_light[nCntlight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//���C�g�̕�����ݒ�
//		switch (nCntlight)
//		{
//		case 0:
//			vecDir[nCntlight] = D3DXVECTOR3(0.2f, -0.8f, -0.5f);
//			break;
//		case 1:
//			vecDir[nCntlight] = D3DXVECTOR3(-0.5f, -0.8f, -0.5f);
//			break;
//		case 2:
//			vecDir[nCntlight] = D3DXVECTOR3(0.0f, -0.8f, 0.6f);
//			break;
//		}
//		D3DXVec3Normalize(&vecDir[nCntlight], &vecDir[nCntlight]);	//�x�N�g���𐳋K������
//		g_light[nCntlight].Direction = vecDir[nCntlight];
//
//		//���C�g��ݒ肷��
//		pDevice->SetLight(nCntlight, &g_light[nCntlight]);
//
//		//���C�g��L���ɂ���
//		pDevice->LightEnable(nCntlight, TRUE);
//	}
//}

//====================================================================
//���C�g�̏���������
//====================================================================
void InitLight(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir[MAX_LIGHT];	//�ݒ�p�����x�N�g��

	//���C�g�̏����N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		//�e��ϐ��̏�����
		g_light[nCntlight].Type = D3DLIGHT_DIRECTIONAL;						//���C�g�̎�ނ�ݒ�
		g_light[nCntlight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//���C�g�̊g�U����ݒ�
		g_light[nCntlight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//���C�g�̔��ːF��ݒ�
		g_light[nCntlight].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//���C�g�̊�����ݒ�
		g_light[nCntlight].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���C�g�̈ʒu��ݒ�
		vecDir[nCntlight] = D3DXVECTOR3(0.2f, -0.8f, -0.5f);				//���C�g�̕�����ݒ�
		g_light[nCntlight].Range = 1000.0f;									//���C�g�͈̔͂�ݒ�
		g_light[nCntlight].Falloff = 1.0f;									//���C�g�̉~�̊O����������܂ł̏Ɩ��̌�����ݒ�
		g_light[nCntlight].Attenuation0 = 0.0f;								//���C�g�̌����O��ݒ�
		g_light[nCntlight].Attenuation1 = 0.01f;							//���C�g�̌����P��ݒ�
		g_light[nCntlight].Attenuation2 = 0.0f;								//���C�g�̌����Q��ݒ�
		g_light[nCntlight].Theta = 0.0f;									//���C�g�̓����̉~��ݒ�
		g_light[nCntlight].Phi = 1.0f;										//���C�g�̊O���̉~��ݒ�
		g_Light_LightIdx[nCntlight] = -1;									//���C�g�̎g�p�ԍ��̐ݒ�

		D3DXVec3Normalize(&vecDir[nCntlight], &vecDir[nCntlight]);	//�x�N�g���𐳋K������
		g_light[nCntlight].Direction = vecDir[nCntlight];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntlight, &g_light[nCntlight]);

		//���C�g�𖳌��ɂ���
		pDevice->LightEnable(nCntlight, FALSE);
		g_bUse[nCntlight] = false;
	}

	//�f�t�H���g�̃��C�g��ݒu����
	for (int nCntlight = 0; nCntlight < 3; nCntlight++)
	{
		g_Light_LightIdx[nCntlight] = SetIndexLight();		//���C�g�̎g�p�ԍ����w�肷��

		if ((GetMode() == MODE_GAME) ||
			(GetMode() == MODE_TUTORIAL) ||
			(GetMode() == MODE_RESULT && GetClear() == false))
		{
			//���C�g�̕�����ݒ�
			switch (nCntlight)
			{
			case 0:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 1:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 2:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
				break;
			}
		}
		else if (GetMode() == MODE_NUMBERSELECT)
		{
			//���C�g�̕�����ݒ�
			switch (nCntlight)
			{
			case 0:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 1:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 2:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
				break;
			}
		}
		else
		{
			//���C�g�̕�����ݒ�
			switch (nCntlight)
			{
			case 0:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 1:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 2:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
				break;
			}
		}
	}
}

//====================================================================
//���C�g�̏I������
//====================================================================
void UninitLight(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		if (g_bUse[nCntlight] == true)
		{
			//���C�g�𖳌��ɂ���
			pDevice->LightEnable(nCntlight, FALSE);
			g_bUse[nCntlight] = false;
		}
	}
}

//====================================================================
//���C�g�̍X�V����
//====================================================================
void UpdateLight(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

#ifdef _DEBUG
	//�r�W�������I���̎��A�f�t�H���g�̃��C�g�𖾂邭����
	for (int nCntlight = 0; nCntlight < 3; nCntlight++)
	{
		if (GetNightVersion() == false)
		{
			if ((GetMode() == MODE_GAME) ||
				(GetMode() == MODE_TUTORIAL) ||
				(GetMode() == MODE_RESULT && GetClear() == false))
			{
				//���C�g�̕�����ݒ�
				switch (nCntlight)
				{
				case 0:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f,1.0f);
					break;
				case 1:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
					break;
				case 2:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
					break;
				}
			}
			else if (GetMode() == MODE_NUMBERSELECT)
			{
				//���C�g�̕�����ݒ�
				switch (nCntlight)
				{
				case 0:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
					break;
				case 1:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
					break;
				case 2:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
					break;
				}
			}
			else
			{
				//���C�g�̕�����ݒ�
				switch (nCntlight)
				{
				case 0:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
					break;
				case 1:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
					break;
				case 2:
					SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
					break;
				}
			}
		}
		else
		{
			//���C�g�̕�����ݒ�
			switch (nCntlight)
			{
			case 0:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 1:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.8f, -0.5f), 100.0f, 1.0f);
				break;
			case 2:
				SetLight(g_Light_LightIdx[nCntlight], D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.6f), 100.0f, 1.0f);
				break;
			}
		}
	}
#endif

	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		if (g_bUse[nCntlight] == true)
		{
			//���C�g��ݒ肷��
			pDevice->SetLight(nCntlight, &g_light[nCntlight]);
		}
	}
}

//====================================================================
//���C�g�̔ԍ��ݒ菈��
//====================================================================
int SetIndexLight(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nLightIndex = -1;
	int nCntlight;

	for (nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		if (g_bUse[nCntlight] == false)
		{
			nLightIndex = nCntlight;

			//���C�g��L���ɂ���
			pDevice->LightEnable(nCntlight, TRUE);
			g_bUse[nCntlight] = true;
			break;
		}
	}

	return nLightIndex;
}

//====================================================================
//���C�g�̏��ݒ菈��
//====================================================================
void SetLight(int nIdxLight, D3DLIGHTTYPE nType, D3DXCOLOR Diffuse, D3DXVECTOR3 pos, D3DXVECTOR3 nVecDir, float nRange,float nPhi)
{
	D3DXVECTOR3 vecDir;	//�ݒ�p�����x�N�g��

	g_light[nIdxLight].Type = nType;			//���C�g�̎�ނ�ݒ�
	g_light[nIdxLight].Diffuse = Diffuse;		//���C�g�̊g�U����ݒ�
	g_light[nIdxLight].Position = pos;			//���C�g�̈ʒu��ݒ�
	vecDir = nVecDir;							//���C�g�̕�����ݒ�
	g_light[nIdxLight].Range = nRange;			//���C�g�͈̔͂�ݒ�
	g_light[nIdxLight].Phi = nPhi;				//���C�g�̊O���̉~��ݒ�

	D3DXVec3Normalize(&vecDir, &vecDir);	//�x�N�g���𐳋K������
	g_light[nIdxLight].Direction = vecDir;
}