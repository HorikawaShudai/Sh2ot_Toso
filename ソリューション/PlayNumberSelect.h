//======================================================================================
//
// �v���C�l���I���̏���[PlayNumberSelect.h]
// Author;���}���@�V
//
//======================================================================================
#ifndef _PLAYNUMBERSELECT_H_
#define _PLAYNUMBERSELECT_H_

#include "main.h"

//�}�N����`
#define NUM_PLAYNUMBER		(4)			//

//�v���C�l���I���̗񋓌^
typedef enum
{
	PLAYNUMBER_ONE,
	PLAYNUMBER_TWO,
	PLAYNUMBER_THREE,
	PLAYNUMBER_FOUR,
	PLAYNUMBER_MAX
} PLAYMODE;

//�v���C�I���̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	int CurrentSelectNumber = 4;
	bool bUse;							//�g���Ă��邩
	bool bPush;							//�I���������ǂ����̔��f
} PlayNumberSelect;

//�v���g�^�C�v�錾
void InitPlayNumberSelect(void);
void UninitPlayNumberSelect(void);
void UpdatePlayNumberSelect(void);
void DrawPlayNumberSelect(void);
PlayNumberSelect GetPlayNumberSelect(void);

#endif
