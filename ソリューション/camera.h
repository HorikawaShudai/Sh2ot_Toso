//========================================================================================
//
// カメラ処理[camera.h]
// Author: 
//
//========================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//カメラ状態の列挙型の定義
typedef enum
{
	CAMERASTATE_NONE = 0,
	CAMERASTATE_UP,
	CAMERASTATE_DOWN,
	CAMERASTATE_MAX
} CAMERASTATE;

//カメラの構造体を定義
typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rot2;
	D3DXVECTOR3 rot2Old;
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DVIEWPORT9 viewport;		//ビューポート
	CAMERASTATE State;

	float fposYmove;
	bool bUse;					//使われているか
}Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdx);

D3DXVECTOR3 Getrot(int nPlayer);
Camera *GetCamera(void);
int GetCurrentCamera(void);
void MoveTitleCamera(int nCnt);

#endif