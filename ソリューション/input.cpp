#include "input.h"
#include <stdio.h>

//マクロ定義
#define NUM_KEY_MAX (256) //キーの最大数
#define PLAYER_MAX (4) //プレイヤーの最大数

//グローバル変数

//キーボード用

LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX]; 
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];
BYTE g_aKeyStateRelease[NUM_KEY_MAX];
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;
DIMOUSESTATE MouseState;


//ゲームパッド用
XINPUT_STATE g_JoykeyState[PLAYER_MAX];
XINPUT_STATE g_JoykeyStateTrigger[PLAYER_MAX];

//プロトタイプ宣言

//キーボード用
HRESULT InitKeyboard( HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);

//ゲームパッド用
HRESULT InitGamepad(void);
void UninitGamepad(void);
void UpdateGamepad(void);

//==============================
//初期化処理
//==============================


HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(InitMouse(hWnd)))
	{
		return E_FAIL;
	}
	if (FAILED(InitKeyboard(hWnd)))
	{
		return E_FAIL;
	}
	if (FAILED(InitGamepad()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//======================================
//終了処理
//======================================
void UninitInput(void)
{
	UninitKeyboard();//キーボードの終了処理
	UninitGamepad();//ゲームパッドの終了処理
	UninitMouse();
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//======================================
//更新処理
//======================================
void UpdateInput(void)
{
	UpdateKeyboard();//キーボードの更新処理
	UpdateGamepad();//ゲームパッドの更新処理
	UpdateMouse();
}
//======================================
//プレス情報
//======================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0X80) ? true : false;
 }
//======================================
//トリガー情報
//======================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0X80) ? true : false;
}
//======================================
//リリース情報
//======================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0X80) ? true : false;
}
//======================================
//リピート情報
//======================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0X80) ? true : false;
}
//======================================
//キーボード初期化
//======================================
HRESULT InitKeyboard(HWND hWnd)
{
	
	//入力デバイスの生成（キーボード）
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードのアクセス権を取得
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//======================================
//キーボード終了
//======================================
void UninitKeyboard(void)
{
	//入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); //キーボードへのアクセス権を破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//Directinputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//======================================
//キーボード更新
//======================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&g_aKeyState[nCntKey];
			g_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのPRESS情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
//======================================
//マウス初期化
//======================================
HRESULT InitMouse(HWND hWnd)
{
	//入力デバイスの生成（キーボード）
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;

	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE,&diprop.diph)))
	{
		return E_FAIL;
	}

	//マウスのアクセス権を取得
	g_pDevMouse->Acquire();

	return S_OK;
}
//======================================
//マウス終了
//======================================
void UninitMouse()
{
	//入力デバイスの破棄
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire(); //キーボードへのアクセス権を破棄
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	//Directinputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//======================================
//マウス更新
//======================================
void UpdateMouse()
{
	DIMOUSESTATE mouse;
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(mouse), &mouse)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//入力情報の保存
			MouseState = mouse;
		}
	}
	else
	{
		g_pDevMouse->Acquire();
	}
}
//======================================
//ゲームパッド初期化
//======================================
HRESULT InitGamepad(void)
{
	//Xinputのステートの設定
	XInputEnable(true);

	//ゼロクリア
	ZeroMemory(&g_JoykeyState, sizeof(g_JoykeyState));
	ZeroMemory(&g_JoykeyStateTrigger, sizeof(g_JoykeyStateTrigger));

	return S_OK;
}
//======================================
//ゲームパッド終了
//======================================
void UninitGamepad(void)
{
	//Xinputのステートの設定
	XInputEnable(false);
}
//======================================
//ゲームパッド更新
//======================================
void UpdateGamepad(void)
{
	int nCount;
	XINPUT_STATE JoykeyState;

	for ( nCount = 0; nCount < PLAYER_MAX; nCount++)
	{
		if (XInputGetState(nCount,&JoykeyState) == ERROR_SUCCESS)
		{
			g_JoykeyStateTrigger[nCount].Gamepad.wButtons = (g_JoykeyState[nCount].Gamepad.wButtons ^ JoykeyState.Gamepad.wButtons) & JoykeyState.Gamepad.wButtons;
		    g_JoykeyStateTrigger[nCount].Gamepad.bLeftTrigger = (g_JoykeyState[nCount].Gamepad.bLeftTrigger ^ JoykeyState.Gamepad.bLeftTrigger) & JoykeyState.Gamepad.bLeftTrigger;
			g_JoykeyStateTrigger[nCount].Gamepad.bRightTrigger = (g_JoykeyState[nCount].Gamepad.bRightTrigger ^ JoykeyState.Gamepad.bRightTrigger) & JoykeyState.Gamepad.bRightTrigger;

			g_JoykeyState[nCount] = JoykeyState;
		}
	}
	
}

bool GetGamepadPress(JOYKEY Key,int nPlayer)
{
	return (g_JoykeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
bool GetGamepadTrigger(JOYKEY Key, int nPlayer)
{
	return (g_JoykeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

bool GetGamepadPedalL(int nPlayer)
{
	return (g_JoykeyState[nPlayer].Gamepad.bLeftTrigger & (0x01 << '\0' )) ? true : false;
}
bool GetGamepadPedalR(int nPlayer)
{
	return (g_JoykeyState[nPlayer].Gamepad.bRightTrigger & (0x01 << '\0')) ? true : false;
}
bool GetGamepadPedalTriggerL(int nPlayer)
{
	return (g_JoykeyStateTrigger[nPlayer].Gamepad.bLeftTrigger & (0x01 << '\0')) ? true : false;
}
bool GetGamepadPedalTriggerR(int nPlayer)
{
	return (g_JoykeyStateTrigger[nPlayer].Gamepad.bRightTrigger & (0x01 << '\0')) ? true : false;
}

D3DXVECTOR3 GetGamePadStickL(int nPlayer, float Dead)
{
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)g_JoykeyState[nPlayer].Gamepad.sThumbLX / SHRT_MAX;
	if (fabsf(Stick.x) < Dead)
	{
		Stick.x = 0.0f;
	}

	Stick.y = (float)g_JoykeyState[nPlayer].Gamepad.sThumbLY / SHRT_MAX;
	if (fabsf(Stick.y) < Dead)
	{
		Stick.y = 0.0f;
	}
	Stick.y *= -1;

	return Stick;
}
D3DXVECTOR3 GetGamePadStickR(int nPlayer, float Dead)
{
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)g_JoykeyState[nPlayer].Gamepad.sThumbRX / (SHRT_MAX);
	if (fabsf(Stick.x) < Dead)
	{
		Stick.x = 0.0f;
	}

	Stick.y = (float)g_JoykeyState[nPlayer].Gamepad.sThumbRY / (SHRT_MAX);
	if (fabsf(Stick.y) < Dead)
	{
		Stick.y = 0.0f;
	}
	Stick.y *= -1;

	return Stick;
}

//=============================
//マウスのデバッグ
//=============================
void GetMouseDebug(void)
{
	//ローカル変数宣言
	char aStr[256];

	//フォントの取得
	LPD3DXFONT  pFont = GetFont();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		RECT rect = { 0,nCnt * 20,SCREEN_WIDTH,SCREEN_HEIGHT };

		if (nCnt < 4)
		{
			sprintf(&aStr[0], "マウスの情報:%d", MouseState.rgbButtons[nCnt]);
		}
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

}

//=============================
//マウスの入力
//=============================
bool GetMousePress(MOUSE nKey)
{
	return (MouseState.rgbButtons[nKey] & 0x80) ? true : false;
}

D3DXVECTOR3 GetMouseMove(void)
{
	return D3DXVECTOR3(((float)MouseState.lX) , (-(float)MouseState.lY) , (-(float)MouseState.lZ));
}