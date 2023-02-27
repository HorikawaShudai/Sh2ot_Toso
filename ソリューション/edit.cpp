//========================================================================================
//
// ステージのエディット処理[edit.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "edit.h"
#include "debugproc.h"
#include "Fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshwall.h"
#include "object00.h"
#include "objectBG.h"
#include "objectLight.h"
#include "objectWall.h"
#include "objectPoly.h"
#include <stdio.h>

//====================================================================
//エディット画面の初期化処理
//====================================================================
void InitEdit()
{
	InitObject00();
	InitObjectBG();
	InitObjectLight();
	InitObjectWall();
	InitObjectPoly();
}

//====================================================================
//エディット画面の終了処理
//====================================================================
void UninitEdit()
{
	UninitObject00();
	UninitObjectBG();
	UninitObjectLight();
	UninitObjectWall();
	UninitObjectPoly();
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
	PrintDebugProc("ゲームモードとの切り替え 【F2】\n");
	PrintDebugProc("オブジェクトの種類切り替え 【F3】\n");
	PrintDebugProc("ナイトビジョンのオン/オフ 【F8】\n");
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
	ObjectLight *pObjectLight = GetObjectLight();
	ObjectWall *pObjectWall = GetObjectWall();
	ObjectPoly *pObjectPoly = GetObjectPoly();
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(SET_STAGE_TEXT, "w");

	if (pFile != NULL)
	{//ファイルが開けた場合

		//ステージをセーブする開始の合図
		fprintf(pFile, "%s\n\n", "STARTSETSTAGE");

		for (int nCntObjectWall = 0; nCntObjectWall < MAX_OBJECTWALL; nCntObjectWall++, pObjectWall++)
		{
			if (pObjectWall->bUse == true)
			{//使用されている場合

			 //オブジェクトをセーブする開始の合図
				fprintf(pFile, "%s\n", "SETOBJECTWALL");

				//各種変数の情報セーブ
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "POS", pObjectWall->pos.x, pObjectWall->pos.y, pObjectWall->pos.z);
				fprintf(pFile, "%s		%.3f %.3f %.3f\n", "MOVE", pObjectWall->move.x, pObjectWall->move.y, pObjectWall->move.z);
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "ROT", pObjectWall->rot.x, pObjectWall->rot.y, pObjectWall->rot.z);
				fprintf(pFile, "%s		%d\n", "nType", pObjectWall->nType);

				//オブジェクトをセーブした終了の合図
				fprintf(pFile, "%s\n\n", "ENDOBJECTWALL");
			}
		}

		for (int nCntObjectPoly = 0; nCntObjectPoly < MAX_OBJECTPOLY; nCntObjectPoly++, pObjectPoly++)
		{
			if (pObjectPoly->bUse == true)
			{//使用されている場合

			 //オブジェクトをセーブする開始の合図
				fprintf(pFile, "%s\n", "SETOBJECTPOLY");

				//各種変数の情報セーブ
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "POS", pObjectPoly->pos.x, pObjectPoly->pos.y, pObjectPoly->pos.z);
				fprintf(pFile, "%s		%.3f\n", "WIDTH", pObjectPoly->fWidth);
				fprintf(pFile, "%s			%.3f\n", "HEIGHT", pObjectPoly->fHeight);

				//オブジェクトをセーブした終了の合図
				fprintf(pFile, "%s\n\n", "ENDOBJECTPOLY");
			}
		}

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

		for (int nCntObjectLight = 0; nCntObjectLight < MAX_OBJECTLIGHT; nCntObjectLight++, pObjectLight++)
		{
			if (pObjectLight->bUse == true)
			{//使用されている場合

			 //オブジェクトをセーブする開始の合図
				fprintf(pFile, "%s\n", "SETOBJECTLIGHT");

				//各種変数の情報セーブ
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "POS", pObjectLight->pos.x, pObjectLight->pos.y, pObjectLight->pos.z);
				fprintf(pFile, "%s		%.3f %.3f %.3f\n", "MOVE", pObjectLight->move.x, pObjectLight->move.y, pObjectLight->move.z);
				fprintf(pFile, "%s			%.3f %.3f %.3f\n", "ROT", pObjectLight->rot.x, pObjectLight->rot.y, pObjectLight->rot.z);
				fprintf(pFile, "%s		%d\n", "nType", pObjectLight->nType);

				//オブジェクトをセーブした終了の合図
				fprintf(pFile, "%s\n\n", "ENDOBJECTLIGHT");
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