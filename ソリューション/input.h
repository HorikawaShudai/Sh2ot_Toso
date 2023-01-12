#ifndef _INPUT_H_
#define _INPUT_H_



#include "main.h"
//==================
//入力処理
//==================
//プロトタイプ宣言
typedef enum
{
	Button_UP = 0,
	Button_DOWN,
	Button_LEFT,
	Button_Right,
	Button_START,
	Button_BACK,
	Button_LStickKey,
	Button_RStickKey,
	Button_LB,
	Button_RB,
	Button_UNKOWN_0,
	Button_UNKOWN_1,
	Button_A,
	Button_B,
	Button_X,
	Button_Y,
	Button_test,
	Button_MAX
}JOYKEY;

typedef enum
{
	
	MOUSE_LEFT = 0,
	MOUSE_RIGTH,
	MOUSE_CENTER,
	MOUSE_BUTTON1,
	MOUSE_MAX
}MOUSE;

//デバイス

HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

HRESULT InitMouse(HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
bool GetMousePress(MOUSE nKey);
D3DXVECTOR3 GetMouseMove(void);

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
bool GetKeyboardRepeat(int nKey);

bool GetGamepadPress(JOYKEY Key, int nPlayer);
bool GetGamepadTrigger(JOYKEY Key, int nPlayer);

bool GetGamepadPedalL(int nPlayer);
bool GetGamepadPedalR(int nPlayer);
bool GetGamepadPedalTriggerL(int nPlayer);
bool GetGamepadPedalTriggerR(int nPlayer);
D3DXVECTOR3 GetGamePadStickL(int nPlayer, float Dead);
D3DXVECTOR3 GetGamePadStickR(int nPlayer, float Dead);


void GetMouseDebug();
#endif // !_INPUT_H_