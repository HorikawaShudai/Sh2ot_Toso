//========================================================================================
//
// 外部ファイルからオブジェクトを読み込む処理[stage.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "game.h"
#include "stage.h"
#include "object00.h"
#include "objectBG.h"
#include "objectLight.h"
#include "edit.h"
#include <stdio.h>

//マクロ定義
#define START_OK ("STARTSETSTAGE")				//スタートメッセージがあるかどうかの確認
#define SETENEMY_OK ("SETENEMY")				//セットメッセージがあるかどうかの確認
#define SET_OBJECT00OK ("SETOBJECT00")			//セットメッセージがあるかどうかの確認
#define SET_OBJECTBGOK ("SETOBJECTBG")			//セットメッセージがあるかどうかの確認
#define SET_OBJECTLIGHTOK ("SETOBJECTLIGHT")	//セットメッセージがあるかどうかの確認
#define ENDENEMY_OK ("ENDENEMY")				//エンドメッセージがあるかどうかの確認
#define END_OBJECT00OK ("ENDOBJECT00")			//エンドメッセージがあるかどうかの確認
#define END_OBJECTBGOK ("ENDOBJECTBG")			//エンドメッセージがあるかどうかの確認
#define END_OBJECTLIGHTOK ("ENDOBJECTLIGHT")	//エンドメッセージがあるかどうかの確認
#define END_SET_OK ("ENDSETSTAGE")				//エンドメッセージがあるかどうかの確認

//ステージの構造体
typedef struct
{
	D3DXVECTOR3 pos;							//現在の位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 rot;							//向き
	int nType;							//向き
	bool bUse;									//使用しているかどうか
}Stage;

//ステージの構造体
typedef struct
{
	int nCount;
	bool bUse;									//使用しているかどうか
}Stage_Object00;

//ステージの構造体
typedef struct
{
	int nCount;
	bool bUse;									//使用しているかどうか
}Stage_ObjectBG;

//ステージの構造体
typedef struct
{
	int nCount;
	bool bUse;									//使用しているかどうか
}Stage_ObjectLight;

Stage g_Stage[MAX_STAGEOBJECT];
//Stage_Enemy g_StageEnemy[MAX_STAGEOBJECT];
Stage_Object00 g_StageObject00[MAX_STAGEOBJECT];
Stage_ObjectBG g_StageObjectBG[MAX_STAGEOBJECT];
Stage_ObjectBG g_StageObjectLight[MAX_STAGEOBJECT];
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

		g_StageObject00[nCntStage].nCount = -1;
		g_StageObject00[nCntStage].bUse = false;

		g_StageObjectBG[nCntStage].nCount = -1;
		g_StageObjectBG[nCntStage].bUse = false;

		g_StageObjectLight[nCntStage].nCount = -1;
		g_StageObjectLight[nCntStage].bUse = false;
	}

	//ステージを読み込む
	LoadStage(nStageNumber);
	g_SelectStage = nStageNumber;

	for (int nCntStage = 0; nCntStage < MAX_STAGEOBJECT; nCntStage++)
	{
		//オブジェクト00の配置
		if (g_StageObject00[nCntStage].bUse == true)
		{
			SetObject00(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_Stage[nCntStage].nType);
		}

		//オブジェクトBGの配置
		if (g_StageObjectBG[nCntStage].bUse == true)
		{
			SetObjectBG(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_Stage[nCntStage].nType);
		}

		//オブジェクトLightの配置
		if (g_StageObjectLight[nCntStage].bUse == true)
		{
			SetObjectLight(g_Stage[nCntStage].pos, g_Stage[nCntStage].move, g_Stage[nCntStage].rot, g_Stage[nCntStage].nType);
		}
	}
}

//====================================================================
//ブロックのロード処理
//====================================================================
void LoadStage(int nStageNumber)
{
	FILE *pFile; //ファイルポインタを宣言
	
	//ファイルを開く
	pFile = fopen("", "r");

	if (nStageNumber == 0)
	{
		//ファイルを開く
		pFile = fopen(SET_STAGE_TEXT, "r");
	}

	else if (nStageNumber == 1)
	{
		//ファイルを開く
		pFile = fopen("Data\\TEXT\\Title.txt", "r");
	}

	else if (nStageNumber == 2)
	{
		//ファイルを開く
		pFile = fopen("Data\\TEXT\\playnumber.txt","r");
	}

	else if (nStageNumber == 3)
	{
		//ファイルを開く
		pFile = fopen("Data\\TEXT\\result_tousou.txt", "r");
	}

	else if (nStageNumber == 4)
	{
		////ファイルを開く
		//pFile = fopen("Data\\TEXT\\tutorial_tousou.txt", "r");
	}

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

					//オブジェクトBGの配置--------------------------
					if (g_StageObjectBG[nCntStage].bUse == false)
					{

							if (strcmp(&aSetMessage[0], SET_OBJECTBGOK) == 0)
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
								if (strcmp(&aEndMessage[0], END_OBJECTBGOK) != 0)
								{
									break;
								}

								g_StageObjectBG[nCntStage].nCount++;
								g_StageObjectBG[nCntStage].bUse = true;

							}

					}

					//オブジェクトLightの配置--------------------------
					if (g_StageObjectLight[nCntStage].bUse == false)
					{

						if (strcmp(&aSetMessage[0], SET_OBJECTLIGHTOK) == 0)
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
							if (strcmp(&aEndMessage[0], END_OBJECTLIGHTOK) != 0)
							{
								break;
							}

							g_StageObjectLight[nCntStage].nCount++;
							g_StageObjectLight[nCntStage].bUse = true;

						}

					}

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
