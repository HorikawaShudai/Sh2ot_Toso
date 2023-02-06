#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//���b�V���t�B�[���h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 rot;	//����
	D3DXMATRIX mtxWorld;//�}�g���b�N�X
	bool bUse;			//�g�p���Ă��邩�ǂ���
}MeshField;

//�v���g�^�C�v�錾
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
#endif