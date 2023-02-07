//========================================================================================
//
// �X�|�b�g���C�g����[SpotLight.h]
// Author: ��{�@�ėB
//
//========================================================================================
#include "main.h"
#include "SpotLight.h"
#include "input.h"
#include "debugproc.h"
#include "effect.h"

#define MAX_LIGHT (3)	//�g�p���郉�C�g�̐�

//�O���[�o���ϐ�
D3DLIGHT9 g_SpotLight[MAX_LIGHT];	//���C�g�̏��

//====================================================================
//�X�|�b�g���C�g�̏���������
//====================================================================
void InitSpotLight(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir[MAX_LIGHT];	//�ݒ�p�����x�N�g��

	//���C�g�̏����N���A����
	ZeroMemory(&g_SpotLight, sizeof(D3DLIGHT9));

	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		//���C�g�̎�ނ�ݒ�
		g_SpotLight[nCntlight].Type = D3DLIGHT_POINT;

		//���C�g�̊g�U����ݒ�
		g_SpotLight[nCntlight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SpotLight[nCntlight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SpotLight[nCntlight].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SpotLight[nCntlight].Position = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_SpotLight[nCntlight].Falloff = 100.0f;
		g_SpotLight[nCntlight].Range = 500.0f;
		g_SpotLight[nCntlight].Attenuation0 = 0.0f;
		g_SpotLight[nCntlight].Attenuation1 = 0.01f;
		g_SpotLight[nCntlight].Attenuation2 = 0.0f;
		g_SpotLight[nCntlight].Theta = 1.0f;
		g_SpotLight[nCntlight].Phi = 2.0f;

		//���C�g�̕�����ݒ�
		switch (nCntlight)
		{
		case 0:
			vecDir[nCntlight] = D3DXVECTOR3(0.2f, 0.2f, 0.5f);
			break;
		case 1:
			vecDir[nCntlight] = D3DXVECTOR3(0.2f, 0.5f, 0.2f);
			break;
		case 2:
			vecDir[nCntlight] = D3DXVECTOR3(0.5f, 0.2f, 0.2f);
			break;
		}
		D3DXVec3Normalize(&vecDir[nCntlight], &vecDir[nCntlight]);	//�x�N�g���𐳋K������
		g_SpotLight[nCntlight].Direction = vecDir[nCntlight];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntlight, &g_SpotLight[nCntlight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntlight, TRUE);
	}
}

//====================================================================
//�X�|�b�g���C�g�̏I������
//====================================================================
void UninitSpotLight(void)
{

}

//====================================================================
//�X�|�b�g���C�g�̍X�V����
//====================================================================
void UpdateSpotLight(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_SpotLight[nCntlight].Position.z += 1.0f;
		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_SpotLight[nCntlight].Position.z -= 1.0f;
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_SpotLight[nCntlight].Position.x -= 1.0f;
		}
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_SpotLight[nCntlight].Position.x += 1.0f;
		}
		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			g_SpotLight[nCntlight].Position.y += 1.0f;
		}
		if (GetKeyboardPress(DIK_LCONTROL) == true)
		{
			g_SpotLight[nCntlight].Position.y -= 1.0f;
		}

		PrintDebugProc("\n%f  %f  %f\n", g_SpotLight[nCntlight].Position.x, g_SpotLight[nCntlight].Position.y, g_SpotLight[nCntlight].Position.z);

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntlight, &g_SpotLight[nCntlight]);
	}
	SetEffect(g_SpotLight[0].Position, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 30, 0);
}