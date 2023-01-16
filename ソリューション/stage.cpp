#include "main.h"
#include "game.h"
#include "stage.h"
#include "object00.h"
#include <stdio.h>

//マクロ定義
#define START_OK ("STARTSETSTAGE")		//スタートメッセージがあるかどうかの確認
#define SETENEMY_OK ("SETENEMY")		//セットメッセージがあるかどうかの確認
#define SET_OBJECT00OK ("SETOBJECT00")	//セットメッセージがあるかどうかの確認
#define SET_OBJECT01OK ("SETOBJECT01")	//セットメッセージがあるかどうかの確認
#define ENDENEMY_OK ("ENDENEMY")		//エンドメッセージがあるかどうかの確認
#define END_OBJECT00OK ("ENDOBJECT00")	//エンドメッセージがあるかどうかの確認
#define END_OBJECT01OK ("ENDOBJECT01")	//エンドメッセージがあるかどうかの確認
#define END_SET_OK ("ENDSETSTAGE")		//エンドメッセージがあるかどうかの確認

//ステージの構造体
typedef struct
{
	D3DXVECTOR3 pos;							//現在の位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 rot;							//向き
	int nType;							//向き
	bool bUse;									//使用しているかどうか
}Stage;
//
////敵の構造体
//typedef struct
//{
//	ENEMY_NTYPE nType;						//種類
//	int nCount;
//	bool bUse;									//使用しているかどうか
//}Stage_Enemy;

//ステージの構造体
typedef struct
{
	int nType;				//種類
	int nCount;
	bool bUse;									//使用しているかどうか
}Stage_Object00;

////ステージの構造体
//typedef struct
//{
//	OBJECT01_NTYPE nType;				//種類
//	int nCount;
//	bool bUse;									//使用しているかどうか
//}Stage_Object01;

Stage g_Stage[MAX_STAGEOBJECT];
//Stage_Enemy g_StageEnemy[MAX_STAGEOBJECT];
Stage_Object00 g_StageObject00[MAX_STAGEOBJECT];
//Stage_Object01 g_StageObject01[MAX_STAGEOBJECT];
int g_SelectStage;

//====================================================================
//オブジェクト00の設定処理
//====================================================================
void SetStage(int nStageNumber)
{
	g_SelectStage = 0;

	for (int nCntStage = 0; nCntStage < MAX_STAGEOBJECT; nCntStage++)
	{
		g_Stage[nCntStage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage[nCntStage].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage[nCntStage].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage[nCntStage].bUse = false;

		//g_StageEnemy[nCntStage].nType = ENEMY_NTYPE00;
		//g_StageEnemy[nCntStage].nCount = -1;
		//g_StageEnemy[nCntStage].bUse = false;

		g_StageObject00[nCntStage].nType = OBJECT00_NTYPE00;
		g_StageObject00[nCntStage].nCount = -1;
		g_StageObject00[nCntStage].bUse = false;

		//g_StageObject01[nCntStage].nType = OBJECT01_NTYPE00;
		//g_StageObject01[nCntStage].nCount = -1;
		//g_StageObject01[nCntStage].bUse = false;
	}

	//ステージを読み込む
	LoadStage(nStageNumber);
	g_SelectStage = nStageNumber;

	for (int nCntStage = 0; nCntStage < MAX_STAGEOBJECT; nCntStage++)
	{
		////敵の配置
		//if (g_StageEnemy[nCntStage].bUse == true)
		//{
		//	SetEnemy(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_StageEnemy[nCntStage].nType);
		//}

		//敵の配置
		if (g_StageObject00[nCntStage].bUse == true)
		{
			SetObject00(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_Stage[nCntStage].nType);
		}

		////敵の配置
		//if (g_StageObject01[nCntStage].bUse == true)
		//{
		//	SetObject01(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_StageObject01[nCntStage].nType);
		//}
	}

	//当たり判定のあるオブジェクトの配置
	//SetObject00(D3DXVECTOR3(100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE00);
	//SetObject00(D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE01);
	//SetObject00(D3DXVECTOR3(-100.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE02);
	//SetObject00(D3DXVECTOR3(-200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE03);
	//SetObject00(D3DXVECTOR3(-250.0f, -50.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT00_NTYPE03);

	//当たり判定のないオブジェクトの配置
	//SetObject01(D3DXVECTOR3(-100.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT01_NTYPE02);

	//敵の配置
	//SetEnemy(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_NTYPE00);
	//SetEnemy(D3DXVECTOR3(-50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_NTYPE01);
	//SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_NTYPE02);
	//SetEnemy(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_NTYPE03);
	//SetEnemy(D3DXVECTOR3(-100.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_NTYPE03);
}

//====================================================================
//ブロックのロード処理
//====================================================================
void LoadStage(int nStageNumber)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("data\\TEXT\\Stage00.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		char aString[128] = {};			//ゴミ箱
		char aStartMessage[32] = {};	//スタートメッセージ
		char aSetMessage[32] = {};		//セットメッセージ
		char aEndMessage[32] = {};		//終了メッセージ
		char aType[32] = {};		//終了メッセージ

		fscanf(pFile, "%s", &aStartMessage[0]);
		if (strcmp(&aStartMessage[0], START_OK) == 0)
		{
			int nCntStage = 0;
			for (int nCntStage = 0; nCntStage < MAX_STAGEOBJECT; nCntStage++)
			{
				//開始の合図
				fscanf(pFile, "%s", &aSetMessage[0]);

					////敵の配置--------------------------
					//if (g_StageEnemy[nCntStage].bUse == false)
					//{

					//		if (strcmp(&aSetMessage[0], SETENEMY_OK) == 0)
					//		{
					//			fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.x);		//POSの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.y);		//POSの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.z);		//POSの設定

					//			fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.x);	//MOVEの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.y);	//MOVEの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.z);	//MOVEの設定

					//			fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.x);		//ROTの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.y);		//ROTの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.z);		//ROTの設定

					//			fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
					//			fscanf(pFile, "%s", &aType[0]);						//TYPEの設定
					//			if (strcmp(&aType[0], "ENEMY_NTYPE00") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE00;
					//			}
					//			else if (strcmp(&aType[0], "ENEMY_NTYPE01") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE01;
					//			}
					//			else if (strcmp(&aType[0], "ENEMY_NTYPE02") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE02;
					//			}
					//			else if (strcmp(&aType[0], "ENEMY_NTYPE03") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE03;
					//			}
					//			else if (strcmp(&aType[0], "ENEMY_NTYPE04") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE04;
					//			}
					//			else if (strcmp(&aType[0], "ENEMY_NTYPE05") == 0)
					//			{
					//				g_StageEnemy[nCntStage].nType = ENEMY_NTYPE05;
					//			}

					//			//終了の合図
					//			fscanf(pFile, "%s", &aEndMessage[0]);
					//			if (strcmp(&aEndMessage[0], ENDENEMY_OK) != 0)
					//			{
					//				break;
					//			}

					//			g_StageEnemy[nCntStage].nCount++;
					//			g_StageEnemy[nCntStage].bUse = true;

					//		}
					//	
					//}

					//オブジェクト00の配置--------------------------
					if (g_StageObject00[nCntStage].bUse == false)
					{

							if (strcmp(&aSetMessage[0], SET_OBJECT00OK) == 0)
							{
								fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
								fscanf(pFile, "%f", &g_Stage[nCntStage].pos.x);		//POSの設定
								fscanf(pFile, "%f", &g_Stage[nCntStage].pos.y);		//POSの設定
								fscanf(pFile, "%f", &g_Stage[nCntStage].pos.z);		//POSの設定

								fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
								fscanf(pFile, "%f", &g_Stage[nCntStage].move.x);	//MOVEの設定
								fscanf(pFile, "%f", &g_Stage[nCntStage].move.y);	//MOVEの設定
								fscanf(pFile, "%f", &g_Stage[nCntStage].move.z);	//MOVEの設定

								fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
								fscanf(pFile, "%f", &g_Stage[nCntStage].rot.x);		//ROTの設定
								fscanf(pFile, "%f", &g_Stage[nCntStage].rot.y);		//ROTの設定
								fscanf(pFile, "%f", &g_Stage[nCntStage].rot.z);		//ROTの設定

								fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
								fscanf(pFile, "%d", &g_Stage[nCntStage].nType);		//TYPEの設定

								//終了の合図
								fscanf(pFile, "%s", &aEndMessage[0]);
								if (strcmp(&aEndMessage[0], END_OBJECT00OK) != 0)
								{
									break;
								}

								g_StageObject00[nCntStage].nCount++;
								g_StageObject00[nCntStage].bUse = true;

							}
						
					}

					////オブジェクト01の配置--------------------------
					//if (g_StageObject01[nCntStage].bUse == false)
					//{

					//		if (strcmp(&aSetMessage[0], SET_OBJECT01OK) == 0)
					//		{
					//			fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.x);		//POSの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.y);		//POSの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].pos.z);		//POSの設定

					//			fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.x);	//MOVEの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.y);	//MOVEの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].move.z);	//MOVEの設定

					//			fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.x);		//ROTの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.y);		//ROTの設定
					//			fscanf(pFile, "%f", &g_Stage[nCntStage].rot.z);		//ROTの設定

					//			fscanf(pFile, "%s", &aString[0]);					//ゴミ箱
					//			fscanf(pFile, "%s", &aType[0]);						//TYPEの設定
					//			if (strcmp(&aType[0], "OBJECT01_NTYPE00") == 0)
					//			{
					//				g_StageObject01[nCntStage].nType = OBJECT01_NTYPE00;
					//			}
					//			else if (strcmp(&aType[0], "OBJECT01_NTYPE01") == 0)
					//			{
					//				g_StageObject01[nCntStage].nType = OBJECT01_NTYPE01;
					//			}
					//			else if (strcmp(&aType[0], "OBJECT01_NTYPE02") == 0)
					//			{
					//				g_StageObject01[nCntStage].nType = OBJECT01_NTYPE02;
					//			}

					//			//終了の合図
					//			fscanf(pFile, "%s", &aEndMessage[0]);
					//			if (strcmp(&aEndMessage[0], END_OBJECT01OK) != 0)
					//			{
					//				break;
					//			}

					//			g_StageObject01[nCntStage].nCount++;
					//			g_StageObject01[nCntStage].bUse = true;

					//		}

					//}

				if (strcmp(&aSetMessage[0], END_SET_OK) == 0)
				{
					break;
				}
			}
		}
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
	//bool = (strcmp(&bool[0], "true") == 0 ? true : false);			//bool型の書き方
}

//====================================================================
//選択ステージの入手処理
//====================================================================
int GetSelectStage(void)
{
	return g_SelectStage;
}
