//=============================================
//���C������	
//=============================================
//�C���N���[�h
#include"main.h"
#include "input.h"
#include "debugproc.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "Fade.h"
#include "PlayNumberSelect.h"
#include "PlayModeSelect.h"
#include "VillainRanking.h"
#include "EscapeRanking.h"
#include "EscapeClearResult.h"
#include "EscapeOverResult.h"
#include "EscapeTutorial.h"
#include "VillainTutorial.h"
#include "RankingNumber.h"
#include "input.h"
#include "sound.h"

//�}�N����`
#define CLASS_NAME "WindowClass"     //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "����"  //�E�B���h�E�̖��O
#define ID_TIMER (131)
#define TIMER_INTERVAL (1000/60)


//�v���g�^�C�v�錾
LRESULT CALLBACK WindowPloc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LPDIRECT3DDEVICE9 GetDevice(void);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

void DrawFPS(void);

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
bool bWire;				//���C���[�t���[�����g���Ă��邩�ǂ���
bool g_bNightVision;			//����̊m�ۂ��g���Ă��邩�ǂ���
int g_nCountFPS = 0;

MODE g_mode = MODE_GAME;	//�J�n���_�̃��[�h

 //=============================================
 //���C���֐�
//=============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePlev, LPSTR lpCmdline, int nCmdShow)
{
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,//�E�B���h�E�X�^�C��
		WindowPloc, //�E�B���h�E�v���V�[�W��
		0, //�ʏ�g�p���Ȃ�
		0, //�ʏ�g�p���Ȃ�
		hInstance, //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),//�}�E�X�J�[�\��
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};



	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd; //�E�B���h�E�n���h��
	MSG msg;



	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,//�E�B���h�E�����X���W
		CW_USEDEFAULT,//�E�B���h�E�����Y���W
		(rect.right - rect.left),//��
		(rect.bottom - rect.top),//����
		NULL,//�e�E�B���h�E�̃n���h��
		NULL,//���j���[�n���h���܂��͎q�E�B���h�E��ID
		hInstance,//�C���X�^���X�n���h��
		NULL);

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();//���ݎ������擾
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();
	ShowWindow(hWnd, nCmdShow);//�E�B���h�E�̕\����Ԃ�ݒ�
	DispatchMessage(&msg);

	srand(dwExecLastTime);

	//�������ݒ�
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	};

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
			 //FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60���̂P�b�o��
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();
				//�`�揈��
				Draw();

				dwFrameCount++; //�t���[���J�E���g�����Z
			}

		}
	}
	Uninit();
	return (int)msg.wParam;

	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;

	return 0;


}
//=============================================
//�E�B���h�E�v���V�[�W��
//=============================================
LRESULT CALLBACK WindowPloc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;


	switch (uMsg)
	{
	case WM_DESTROY: //�E�B���h�E��j��
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //�L�[�������ꂽ��
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E��j��
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�B���h�E��j��
			DestroyWindow(hWnd);
		}
		else if (nID == IDNO)
		{
			return 0;
		}
		break;
	case WM_LBUTTONDOWN: //���N���b�N
						 //�ΏۃE�B���h�E�Ƀt�H�[�J�X
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//=============================================
//����������
//=============================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//DirectX�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp)); //�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct#D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�T�E���h�̏�����
	InitSound(hWnd);

	//�����x�̐ݒ�

	//�f�o�C�X�̏���������
	if (FAILED(InitDevice(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	bWire = false;  //���C���[�t���[�����g���Ă��Ȃ���Ԃ�
	g_bNightVision = false;  //����̊m�ۂ��g���Ă��Ȃ���Ԃ�

	//�f�[�^�����[�h����
	LoadData();

	SetMode(g_mode);

	InitFade(g_mode);

	//�f�o�b�O�v���b�N�̏�����
	InitDebugProc();

	

	//�e��I�u�W�F�N�g�����������͂���
	return S_OK;
}
//=============================================
//�I������
//=============================================
void Uninit(void)
{
	//�e��I�u�W�F�N�g�̏I������
	UninitFade();

	//�f�o�C�X�̏I������
	UninitDevice();

	//�f�o�b�O�v���b�N�̏I������
	UninitDebugProc();

	//DirectX3d�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//DirectX3d�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
//=============================================
//�X�V����
//=============================================
void Update(void)
{
	//�e��I�u�W�F�N�g�̍X�V����

	//�f�o�C�X�̍X�V
	UpdateDevice();

	//�f�o�b�O�v���b�N�̍X�V����
	UpdateDebugProc();

#ifdef _DEBUG

	//F11�������ꂽ�Ƃ��̏���
	if (GetKeyboardTrigger(DIK_F11) == true)
	{//���C���[�t���[����L���ɂ��邩�ǂ���
		bWire = (bWire == false) ? true : false;
	}
	if (bWire == true)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//�J�����O�̐ݒ�
	}

	else
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);//�J�����O�̐ݒ�
	}

	//F8�������ꂽ�Ƃ��̏���
	if (GetKeyboardTrigger(DIK_F8) == true)
	{//���C���[�t���[����L���ɂ��邩�ǂ���
		g_bNightVision = (g_bNightVision == false) ? true : false;
	}

#endif

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_NUMBERSELECT:
		UpdatePlayNumberSelect();
		break;
	case MODE_TUTORIAL:
		UpdateEscapeTutorial();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		if (GetClear() != 0)
		{
			//UpdateResult();
			UpdateEscapeClearResult();
		}
		else
		{
			UpdateEscapeOverResult();
		}
		break;
	case MODE_RANKING:
		if (GetPlayModeSelect().CurrentModeNumber == 0)
		{
			UpdateEscapeRanking();
		}
		else
		{
			UpdateVillainRanking();
		}
		break;
	}

	UpdateFade();
}
//=============================================
//�`�揈��
//=============================================
void Draw(void)
{
	//��ʃN���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//���������ꍇ
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_NUMBERSELECT:
			DrawPlayNumberSelect();
			break;
		case MODE_TUTORIAL:
			DrawEscapeTutorial();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			if (GetClear() != 0)
			{
				DrawResult();
				DrawEscapeClearResult();
			}
			else
			{
				DrawEscapeOverResult();
			}
			break;
		case MODE_RANKING:
			if (GetPlayModeSelect().CurrentModeNumber == 0)
			{
				DrawEscapeRanking();
			}
			else
			{
				DrawVillainRanking();
			}
			break;
		}

		DrawFade();
		DrawFPS();

		//�f�o�b�O�v���b�N�̕`�揈��
		DrawDebugProc();

		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
//=============================================
//�f�o�b�O�\��
//=============================================
void DrawFPS(void)
{
	//�f�o�b�O�ύX��FPS
	PrintDebugProc("\n\n\nFPS:[%d]", g_nCountFPS);
}

//=============================================
//�f�o�C�X�̎擾
//=============================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_NUMBERSELECT:
		UninitPlayNumberSelect();
		break;
	case MODE_TUTORIAL:
		UninitEscapeTutorial();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		if (GetClear() != 0)
		{
			//UninitResult();
			UninitEscapeClearResult();
		}
		else
		{
			UninitEscapeOverResult();
		}
		break;
	case MODE_RANKING:
		if (GetPlayModeSelect().CurrentModeNumber == 0)
		{
			UninitEscapeRanking();
		}
		else
		{
			UninitVillainRanking();
		}
		break;
	}

	g_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_NUMBERSELECT:
		InitPlayNumberSelect();
		break;
	case MODE_TUTORIAL:
		InitEscapeTutorial();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		if (GetClear() != 0)
		{
			//InitResult();
			InitEscapeClearResult();
		}
		else
		{
			InitEscapeOverResult();
		}
		break;
	case MODE_RANKING:
		if (GetPlayModeSelect().CurrentModeNumber == 0)
		{
			InitEscapeRanking();
		}
		else
		{
			InitVillainRanking();
		}
		break;
	}
}

//====================================================================
//���[�h������
//====================================================================
MODE GetMode(void)
{
	return g_mode;
}

//====================================================================
//����̊m�ۏ�������
//====================================================================
bool GetNightVersion(void)
{
	return g_bNightVision;
}