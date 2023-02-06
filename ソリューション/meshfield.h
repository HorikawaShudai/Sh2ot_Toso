#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//メッシュフィールドの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//現在の位置
	D3DXVECTOR3 rot;	//向き
	D3DXMATRIX mtxWorld;//マトリックス
	bool bUse;			//使用しているかどうか
}MeshField;

//プロトタイプ宣言
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
#endif