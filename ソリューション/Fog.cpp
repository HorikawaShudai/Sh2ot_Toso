//==========================================================
//
// �t�H�O���� [fog.cpp]
// Author : �O�� ���V��
//
//==========================================================
#include "fog.h"

//�O���[�o���ϐ�
FOG g_Fog;

//======================================
//����������
//======================================
void InitFog()
{
	//���l�̃��Z�b�g
	g_Fog.FogMode = D3DFOG_NONE;
	g_Fog.FogStart = 0.0f;
	g_Fog.FogEnd = 0.0f;
	g_Fog.FogDensity = 0.0f;
	g_Fog.FogColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//======================================
//�I������
//======================================
void UninitFog()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //�t�H�O�̖�����
}

//======================================
//�X�V����
//======================================
void UpdateFog()
{

}

//======================================
//�`�揈��
//======================================
void DrawFog()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();
	if (g_Fog.FogMode != D3DFOG_NONE)
	{//�t�H�O���[�h���L���Ȏ�
		pDevice->SetRenderState(D3DRS_FOGCOLOR, g_Fog.FogColor);					//�F�̐ݒ�
		pDevice->SetRenderState(D3DRS_FOGTABLEMODE, g_Fog.FogMode);					//���[�h�̐ݒ�
		pDevice->SetRenderState(D3DRS_FOGSTART, *((LPDWORD)(&g_Fog.FogStart)));		//�J�n�n�_�̐ݒ�
		pDevice->SetRenderState(D3DRS_FOGEND, *((LPDWORD)(&g_Fog.FogEnd)));			//�I���n�_�̐ݒ�
		pDevice->SetRenderState(D3DRS_FOGDENSITY, *((LPDWORD)(&g_Fog.FogDensity)));	//�t�H�O���x�̐ݒ�
		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);								//�t�H�O�̗L����
	}
}

//======================================
//�ݒ菈��
//======================================
void SetFog(D3DFOGMODE FogMode, D3DXCOLOR FogColor, float FogStart, float FogEnd, float FogDensity)
{
	g_Fog.FogMode = FogMode;        //���[�h�̐ݒ�
	g_Fog.FogColor = FogColor;		//�F�̐ݒ�
	g_Fog.FogStart = FogStart;		//�J�n�n�_�̐ݒ�
	g_Fog.FogEnd = FogEnd;			//�I���n�_�̐ݒ�
	g_Fog.FogDensity = FogDensity;	//�t�H�O���x�̐ݒ�
}