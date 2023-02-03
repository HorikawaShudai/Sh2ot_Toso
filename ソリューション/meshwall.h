//========================================================================================
//
// 壁のポリゴンの描画[meshcywall.h]
// Author: 坂本　翔唯
//
//========================================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//マクロ定義
#define MAX_MESHWALL			(128)

//壁ポリゴンの構造体定義
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXVECTOR3 move;					//移動量
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	bool bUse;							//使っているか
} MeshWall;

//プロトタイプ宣言
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

MeshWall GetMeshWall(void);

#endif