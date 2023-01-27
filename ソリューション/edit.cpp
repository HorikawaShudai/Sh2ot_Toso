#include "edit.h"
#include "debugproc.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"
#include "objectBG.h"
#include <stdio.h>

//====================================================================
//エディット画面の初期化処理
//====================================================================
void InitEdit()
{
	InitObject00();
	InitObjectBG();
}

//====================================================================
//エディット画面の終了処理
//====================================================================
void UninitEdit()
{
	UninitObject00();
	UninitObjectBG();
}

//====================================================================
//エディット画面の更新処理
//====================================================================
void UpdateEdit()
{
	if (GetKeyboardTrigger(DIK_F9) == true)
	{//f9が押されたとき
		SaveEdit();
	}

	PrintDebugProc("【エディットモード中】オブジェクト移動 【↑】【←】【↓】【→】\n");
	PrintDebugProc("オブジェクト上下移動 【右SHIFT】【右CTRL】\n");
	PrintDebugProc("オブジェクト切り替え 【9】\n");
	PrintDebugProc("オブジェクト角度切り替え 【0】\n");
	PrintDebugProc("オブジェクト設置 【ENTER】\n");
	PrintDebugProc("オブジェクト保存 【F9】\n");
}

//====================================================================
//エディット画面の描画処理
//====================================================================
void DrawEdit()
{

}

//====================================================================
//エディット画面のセーブ処理
//====================================================================
void SaveEdit()
{
	Object00 *pObject00 = GetObject00();
	ObjectBG *pObjectBG = GetObjectBG();
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(SET_STAGE_TEXT, "w");

	if (pFile != NULL)
	{//ファイルが開けた場合

		//ステージをセーブする開始の合図
		fprintf(pFile, "%s\n\n", "STARTSETSTAGE");

		for (int nCntObject00 = 0; nCntObject00 < MAX_OBJECT00; nCntObject00++, pObject00++)
		{
			if (pObject00->bUse == true)
			{//使用されている場合

				//オブジェクトをセーブする開始の合図
				fprintf(pFile, "%s\n", "SETOBJECT00");

				//各種変数の情報セーブ
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "POS", pObject00->pos.x, pObject00->pos.y, pObject00->pos.z);
				fprintf(pFile, "%s		%.3f %.3f %.3f\n", "MOVE", pObject00->move.x, pObject00->move.y, pObject00->move.z);
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "ROT", pObject00->rot.x, pObject00->rot.y, pObject00->rot.z);
				fprintf(pFile, "%s		%d\n", "nType", pObject00->nType);

				//オブジェクトをセーブした終了の合図
				fprintf(pFile, "%s\n\n", "ENDOBJECT00");
			}
		}

		for (int nCntObjectBG = 0; nCntObjectBG < MAX_OBJECTBG; nCntObjectBG++, pObjectBG++)
		{
			if (pObjectBG->bUse == true)
			{//使用されている場合

			 //オブジェクトをセーブする開始の合図
				fprintf(pFile, "%s\n", "SETOBJECTBG");

				//各種変数の情報セーブ
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "POS", pObjectBG->pos.x, pObjectBG->pos.y, pObjectBG->pos.z);
				fprintf(pFile, "%s		%.3f %.3f %.3f\n", "MOVE", pObjectBG->move.x, pObjectBG->move.y, pObjectBG->move.z);
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "ROT", pObjectBG->rot.x, pObjectBG->rot.y, pObjectBG->rot.z);
				fprintf(pFile, "%s		%d\n", "nType", pObjectBG->nType);

				//オブジェクトをセーブした終了の合図
				fprintf(pFile, "%s\n\n", "ENDOBJECTBG");
			}
		}

		//ステージをセーブした終了の合図
		fprintf(pFile, "%s", "ENDSETSTAGE");

		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}