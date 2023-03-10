//========================================================================================
//
// 背景用プレイヤーの処理[playerBG.cpp]
// Author: 坂本　翔唯
//
//========================================================================================
#include "main.h"
#include "game.h"
#include "result.h"
#include "playerBG.h"
#include "camera.h"
#include "billboard.h"
#include "object00.h"
#include "particle.h"
#include "input.h"
#include "debugproc.h"
#include "fade.h"
#include "PlayNumberSelect.h"
#include <stdio.h>
#include "player.h"

#define PLAYERBG_SPEED (3.25f)			//プレイヤーのスピード
#define PLAYERBG_ROT_SPEED (0.2f)		//プレイヤーの回転スピード
#define PLAYERBG_JUMP (12.0f)			//プレイヤーのジャンプ力
#define PLAYERBG_LIFE (3)				//プレイヤーの初期ライフ
#define PLAYERBG_COLLISIONSIZE (15.0f)	//プレイヤーの当たり判定の大きさ
#define MAX_PLAYREBG (4)			//背景に使うプレイヤーの最大数

//グローバル変数
LPD3DXMESH g_pMeshPlayerBG[32] = {};				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatPlayerBG[32] = {};			//マテリアルへのポインタ
PlayerBG g_PlayerBG[MAX_PLAYREBG];					//プレイヤーの情報

const char *c_apPlayerBG[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\player\\00_hip.x",
	"Data\\MODEL\\player\\01_body.x",
	"Data\\MODEL\\player\\02_Head.x",
	"Data\\MODEL\\player\\03_R_Shoulder.x",
	"Data\\MODEL\\player\\04_R_upperarm.x",
	"Data\\MODEL\\player\\05_R_forearm.x",
	"Data\\MODEL\\player\\06_R_Hand.x",
	"Data\\MODEL\\player\\07_L_Shoulder.x",
	"Data\\MODEL\\player\\08_L_upperarm.x",
	"Data\\MODEL\\player\\09_L_forearm.x",
	"Data\\MODEL\\player\\10_L_Hand.x",
	"Data\\MODEL\\player\\11_R_Thigh.x",
	"Data\\MODEL\\player\\12_R_Shin.x",
	"Data\\MODEL\\player\\13_R_Leg.x",
	"Data\\MODEL\\player\\14_L_Thigh.x",
	"Data\\MODEL\\player\\15_L_Shin.x",
	"Data\\MODEL\\player\\16_L_Leg.x"
};

//====================================================================
//プレイヤーの初期化処理
//====================================================================
void InitPlayerBG(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntPlayerBG = 0; nCntPlayerBG < MAX_PLAYREBG; nCntPlayerBG++)
	{
		g_PlayerBG[nCntPlayerBG].pos = D3DXVECTOR3(-60.0f + nCntPlayerBG * 40.0f, 0.0f, 100.0f);
		g_PlayerBG[nCntPlayerBG].posOld = g_PlayerBG[nCntPlayerBG].pos;
		g_PlayerBG[nCntPlayerBG].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PlayerBG[nCntPlayerBG].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PlayerBG[nCntPlayerBG].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PlayerBG[nCntPlayerBG].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_PlayerBG[nCntPlayerBG].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_PlayerBG[nCntPlayerBG].g_bMotion = true;

		g_PlayerBG[nCntPlayerBG].g_nNextKey = 1;

		switch (nCntPlayerBG)
		{
		case 0:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_WAIT1;
			SetPlayerMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		case 1:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_WAIT2;
			SetPlayerMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		case 2:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_WAIT3;
			SetPlayerMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		case 3:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_WAIT4;
			SetPlayerMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		}
		g_PlayerBG[nCntPlayerBG].bUse = true;

		//外部ファイルからキャラクター情報を読み込む処理
		LoadPlayerMotion(nCntPlayerBG);

		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX(c_apPlayerBG[nCntModel],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatPlayerBG[nCntModel],
				NULL,
				&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG,
				&g_pMeshPlayerBG[nCntModel]);


			//マテリアル情報に対するポインタを所得
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayerBG[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat]);
				}
			}
		}
	}
}

//====================================================================
//プレイヤーの終了処理
//====================================================================
void UninitPlayerBG(void)
{
	for (int nCntPlayerBG = 0; nCntPlayerBG < MAX_PLAYREBG; nCntPlayerBG++)
	{
		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			for (int nCntMat = 0; nCntMat < (int)g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG; nCntMat++)
			{
				//テクスチャの破棄
				if (g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat] != NULL)
				{
					g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat]->Release();
					g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat] = NULL;
				}
			}
		}

		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			//メッシュの破棄
			if (g_pMeshPlayerBG[nCntModel] != NULL)
			{
				g_pMeshPlayerBG[nCntModel]->Release();
				g_pMeshPlayerBG[nCntModel] = NULL;
			}

			//マテリアルの破棄
			if (g_pBuffMatPlayerBG[nCntModel] != NULL)
			{
				g_pBuffMatPlayerBG[nCntModel]->Release();
				g_pBuffMatPlayerBG[nCntModel] = NULL;
			}
		}
	}
}

//====================================================================
//プレイヤーの更新処理
//====================================================================
void UpdatePlayerBG(void)
{
	PlayNumberSelect nPlayerNumber = GetPlayNumberSelect();

	//ステージセレクト中の決定時に人数が変わるのを防ぐ処理
	if (GetPlayNumberSelect().bPush == false)
	{
		for (int nCntPlayerBG = 0; nCntPlayerBG < MAX_PLAYREBG; nCntPlayerBG++)
		{
			g_PlayerBG[nCntPlayerBG].bUse = false;
		}
		for (int nCntPlayerBG = 0; nCntPlayerBG <= nPlayerNumber.CurrentSelectNumber; nCntPlayerBG++)
		{
			g_PlayerBG[nCntPlayerBG].bUse = true;
		}
	}

	//モーションの更新処理
	for (int nCntPlayerBG = 0; nCntPlayerBG < MAX_PLAYREBG; nCntPlayerBG++)
	{
		UpdatePlayerMotion(nCntPlayerBG);
	}
}

//====================================================================
//モーションの更新処理
//====================================================================
void UpdatePlayerMotion(int nCnt)
{
	g_PlayerBG[nCnt].nNumkey = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].NumKey;

	//全モデル(パーツ)の更新
	for (int nCntModel = 0; nCntModel < g_PlayerBG[nCnt].nNumModel; nCntModel++)
	{
		//キーの情報から位置・向きを算出
		float POSX = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fPosX - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosX;
		float POSY = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fPosY - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosY;
		float POSZ = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fPosZ - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosZ;
		float ROTX = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fRotX - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotX;
		float ROTY = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fRotY - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotY;
		float ROTZ = g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].g_nNextKey].aKey[nCntModel].fRotZ - g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotZ;

		//パーツの位置・向きを設定
		g_PlayerBG[nCnt].aModel[nCntModel].pos.x = g_PlayerBG[nCnt].aModel[nCntModel].Setpos.x + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosX + POSX * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
		g_PlayerBG[nCnt].aModel[nCntModel].pos.y = g_PlayerBG[nCnt].aModel[nCntModel].Setpos.y + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosY + POSY * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
		g_PlayerBG[nCnt].aModel[nCntModel].pos.z = g_PlayerBG[nCnt].aModel[nCntModel].Setpos.z + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fPosZ + POSZ * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
		g_PlayerBG[nCnt].aModel[nCntModel].rot.x = g_PlayerBG[nCnt].aModel[nCntModel].Setrot.x + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotX + ROTX * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
		g_PlayerBG[nCnt].aModel[nCntModel].rot.y = g_PlayerBG[nCnt].aModel[nCntModel].Setrot.y + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotY + ROTY * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
		g_PlayerBG[nCnt].aModel[nCntModel].rot.z = g_PlayerBG[nCnt].aModel[nCntModel].Setrot.z + g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].aKey[nCntModel].fRotZ + ROTZ * ((float)g_PlayerBG[nCnt].nCounterMotion / (float)g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame);
	}
	g_PlayerBG[nCnt].nCounterMotion++;
	if (g_PlayerBG[nCnt].nCounterMotion >= g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].aKeyInfo[g_PlayerBG[nCnt].nkey].nFrame)
	{
		g_PlayerBG[nCnt].nCounterMotion = 0;
		g_PlayerBG[nCnt].nkey++;
		g_PlayerBG[nCnt].g_nNextKey++;

		if (g_PlayerBG[nCnt].g_nNextKey >= g_PlayerBG[nCnt].nNumkey)
		{
			if (g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].bLoop == true)
			{
				g_PlayerBG[nCnt].g_nNextKey = 0;
			}
			else
			{
				g_PlayerBG[nCnt].g_nNextKey = 0;
			}
		}
		if (g_PlayerBG[nCnt].nkey >= g_PlayerBG[nCnt].nNumkey)
		{
			if (g_PlayerBG[nCnt].aMotionInfo[g_PlayerBG[nCnt].MotionType].bLoop == true)
			{
				g_PlayerBG[nCnt].nkey = 0;
			}
			else
			{
				g_PlayerBG[nCnt].nkey = 0;
			}
		}
	}
}

//====================================================================
//モーションの設定処理
//====================================================================
void SetPlayerMotion(PLAYER_MOTION_TYPE nType, int nCnt)
{
	if (g_PlayerBG[nCnt].g_bMotion == true)
	{
		g_PlayerBG[nCnt].bLoopMotion = g_PlayerBG[nCnt].aMotionInfo[nType].bLoop;	//ループするかどうか
		g_PlayerBG[nCnt].nNumkey = g_PlayerBG[nCnt].aMotionInfo[nType].NumKey;		//キーの総数
		g_PlayerBG[nCnt].nkey = 0;											//現在のキーNo.
		g_PlayerBG[nCnt].nCounterMotion = 0;								//モーションのカウンター
		g_PlayerBG[nCnt].g_nNextKey = g_PlayerBG[nCnt].nkey + 1;
		g_PlayerBG[nCnt].g_bMotion = false;
	}
}

//====================================================================
//モーションのロード処理
//====================================================================
void LoadPlayerMotion(int nPlayerBG)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("", "r");

	//ファイルを開く
	pFile = fopen("data\\TEXT\\motion_player.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		int nCntModel = 0;
		int nCntParts = 0;
		int nCntMotion = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;

		char aString[128] = {};				//ゴミ箱
		char aStartMessage[128] = {};		//スタートメッセージ
		char aModelMessage[128] = {};		//モデル用メッセージ
		char aCharaSetMessage[128] = {};	//キャラセットメッセージ
		char aPartsSetMessage[128] = {};	//パーツセットメッセージ
		char aMotionSetMessage[128] = {};	//モーションセットメッセージ
		char KeySetMessage[128] = {};		//キーセットメッセージ
		char KeyStartMessage[128] = {};		//キースタートメッセージ
		char aNameMessage[128] = {};		//変数名のメッセージ
		char aPartsEndMessage[128] = {};	//パーツエンドメッセージ
		char aCharaEndMessage[128] = {};	//キャラエンドメッセージ
		char aEndMessage[128] = {};			//終了メッセージ
		char aType[128] = {};				//終了メッセージ
		char aBool[128] = {};				//bool変換用メッセージ

		// 読み込み開始-----------------------------------------------------
		while (1)
		{//「SCRIPT」を探す
			fscanf(pFile, "%s", &aStartMessage[0]);
			if (strcmp(&aStartMessage[0], "SCRIPT") == 0)
			{
				// モデル数読み込み-----------------------------------------------------
				while (1)
				{//「NUM_MODEL」を探す
					fscanf(pFile, "%s", &aModelMessage[0]);
					if (strcmp(&aModelMessage[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_PlayerBG[nPlayerBG].nNumModel);		//モデル数の設定
						break;
					}
				}

				// キャラクター情報読み込み-----------------------------------------------------
				while (1)
				{//「PARTSSET」を探す
					fscanf(pFile, "%s", &aPartsSetMessage[0]);
					if (strcmp(&aPartsSetMessage[0], "PARTSSET") == 0)
					{
						while (1)
						{//各種変数を探す
							fscanf(pFile, "%s", &aNameMessage[0]);
							if (strcmp(&aNameMessage[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &nCntModel);	//インデックスを設定
							}
							if (strcmp(&aNameMessage[0], "PARENT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_PlayerBG[nPlayerBG].aModel[nCntModel].nIndexModelParent);	//親モデルのインデックスを設定
							}
							if (strcmp(&aNameMessage[0], "POS") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setpos.x);				//位置(オフセット)の初期設定
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setpos.y);				//位置(オフセット)の初期設定
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setpos.z);				//位置(オフセット)の初期設定
							}
							if (strcmp(&aNameMessage[0], "ROT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setrot.x);				////向きの初期設定
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setrot.y);				////向きの初期設定
								fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aModel[nCntModel].Setrot.z);				////向きの初期設定
							}
							if (strcmp(&aNameMessage[0], "END_PARTSSET") == 0)
							{
								break;
							}
						}
						nCntModel++;
						if (nCntModel >= g_PlayerBG[nPlayerBG].nNumModel)
						{
							break;
						}
					}
				}

				// モーション情報読み込み-----------------------------------------------------
				while (1)
				{//「MOTIONSET」を探す
					fscanf(pFile, "%s", &aMotionSetMessage[0]);
					if (strcmp(&aMotionSetMessage[0], "MOTIONSET") == 0)
					{
						while (1)
						{//各種変数を探す
							fscanf(pFile, "%s", &aNameMessage[0]);
							if (strcmp(&aNameMessage[0], "LOOP") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%s", &aBool[0]);	//ループするかどうかを設定
								g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].bLoop = (strcmp(&aBool[0], "1") == 0 ? true : false);			//bool型の書き方
							}
							if (strcmp(&aNameMessage[0], "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].NumKey);	//キーの総数を設定
								break;
							}
						}

						// キー情報読み込み-----------------------------------------------------
						while (1)
						{//「KEYSET」を探す
							fscanf(pFile, "%s", &KeySetMessage[0]);
							if (strcmp(&KeySetMessage[0], "KEYSET") == 0)
							{
								while (1)
								{//「FRAME」を探す
									fscanf(pFile, "%s", &aNameMessage[0]);
									if (strcmp(&aNameMessage[0], "FRAME") == 0)
									{
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].nFrame);	//キーフレームを設定
										break;
									}
								}

								while (1)
								{//「KEY」を探す
									fscanf(pFile, "%s", &KeyStartMessage[0]);
									if (strcmp(&KeyStartMessage[0], "KEY") == 0)
									{
										while (1)
										{//各種変数を探す
											fscanf(pFile, "%s", &aNameMessage[0]);
											if (strcmp(&aNameMessage[0], "POS") == 0)
											{
												fscanf(pFile, "%s", &aString[0]);
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fPosX);	//位置を設定
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fPosY);	//位置を設定
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fPosZ);	//位置を設定
											}
											if (strcmp(&aNameMessage[0], "ROT") == 0)
											{
												fscanf(pFile, "%s", &aString[0]);
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fRotX);	//位置を設定
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fRotY);	//位置を設定
												fscanf(pFile, "%f", &g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].fRotZ);	//位置を設定
												break;
											}
										}
									}
									if (strcmp(&KeyStartMessage[0], "END_KEY") == 0)
									{
										nCntKey++;
										if (nCntKey >= g_PlayerBG[nPlayerBG].nNumModel)
										{
											break;
										}
									}
								}
							}
							if (strcmp(&KeySetMessage[0], "END_KEYSET") == 0)
							{
								nCntKey = 0;
								nCntKeySet++;
								if (nCntKeySet >= g_PlayerBG[nPlayerBG].aMotionInfo[nCntMotion].NumKey)
								{
									break;
								}
							}
						}
					}
					if (strcmp(&aMotionSetMessage[0], "END_MOTIONSET") == 0)
					{
						nCntKeySet = 0;
						nCntMotion++;
						if (nCntMotion >= PLAYERBG_ACTION_MAX)
						{
							break;
						}
					}
				}
			}
			if (strcmp(&aStartMessage[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}

//====================================================================
//プレイヤーの描画処理
//====================================================================
void DrawPlayerBG(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (int nCntPlayerBG = 0; nCntPlayerBG < MAX_PLAYREBG; nCntPlayerBG++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_PlayerBG[nCntPlayerBG].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_PlayerBG[nCntPlayerBG].rot.y, g_PlayerBG[nCntPlayerBG].rot.x, g_PlayerBG[nCntPlayerBG].rot.z);
		D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].mtxWorld, &g_PlayerBG[nCntPlayerBG].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_PlayerBG[nCntPlayerBG].pos.x, g_PlayerBG[nCntPlayerBG].pos.y, g_PlayerBG[nCntPlayerBG].pos.z);
		D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].mtxWorld, &g_PlayerBG[nCntPlayerBG].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_PlayerBG[nCntPlayerBG].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

		//全モデル(パーツ)の描画
		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用マトリックス
			D3DXMATRIX mtxParent;	//親のマトリックス

			//パーツのマトリックスを初期化
			D3DXMatrixIdentity(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld);

			//パーツの向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].rot.y, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].rot.x, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &mtxRotModel);

			//パーツの位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].pos.x, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].pos.y, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの「親のマトリックス」を設定
			if (g_PlayerBG[nCntPlayerBG].aModel[nCntModel].nIndexModelParent != -1)
			{//親モデルがある場合
				mtxParent = g_PlayerBG[nCntPlayerBG].aModel[g_PlayerBG[nCntPlayerBG].aModel[nCntModel].nIndexModelParent].mtxWorld;	//親モデルのインデックスのマトリックスを指定する
			}
			else
			{//親モデルがない場合
				mtxParent = g_PlayerBG[nCntPlayerBG].mtxWorld;	//プレイヤーのマトリックスを指定する
			}

			//算出した「パーツのワールドマトリックス」と「親のマトリックス」を掛け合わせる
			D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld,
				&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld,
				&mtxParent);

			//パーツのワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld);

			//マテリアルデータへのポインタを所得する
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayerBG[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_PlayerBG[nCntPlayerBG].bUse == true)
				{
					//テクスチャの設定
					pDevice->SetTexture(0, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat]);

					//プレイヤー(パーツ)の描画
					g_pMeshPlayerBG[nCntModel]->DrawSubset(nCntMat);
				}
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//プレイヤー情報の所得
//====================================================================
PlayerBG * GetPlayerBG(void)
{
	return &g_PlayerBG[0];
}

//====================================================================
//プレイヤーの初期化処理(リザルト用)
//====================================================================
void InitResultPlayer(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntPlayerBG = 0; nCntPlayerBG < GetExitCount(); nCntPlayerBG++)
	{
		g_PlayerBG[nCntPlayerBG].pos = D3DXVECTOR3(950.0f - nCntPlayerBG * 20.0f, 0.0f, -240.0f - nCntPlayerBG * 20.0f);
		g_PlayerBG[nCntPlayerBG].posOld = g_PlayerBG[nCntPlayerBG].pos;
		g_PlayerBG[nCntPlayerBG].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PlayerBG[nCntPlayerBG].NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PlayerBG[nCntPlayerBG].rot = D3DXVECTOR3(0.0f, -0.7f, 0.0f);
		g_PlayerBG[nCntPlayerBG].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_PlayerBG[nCntPlayerBG].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_PlayerBG[nCntPlayerBG].g_bMotion = true;

		g_PlayerBG[nCntPlayerBG].g_nNextKey = 1;

		switch (nCntPlayerBG)
		{
		case 0:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_RUNPOZE;
			SetPlayerMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		case 1:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_RUNPOZE;
			SetPlayerMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		case 2:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_RUNPOZE;
			SetPlayerMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		case 3:
			g_PlayerBG[nCntPlayerBG].MotionType = PLAYERBG_ACTION_RUNPOZE;
			SetPlayerMotion(g_PlayerBG[nCntPlayerBG].MotionType, nCntPlayerBG);
			break;
		}
		g_PlayerBG[nCntPlayerBG].bUse = true;

		//外部ファイルからキャラクター情報を読み込む処理
		LoadPlayerMotion(nCntPlayerBG);

		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX(c_apPlayerBG[nCntModel],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatPlayerBG[nCntModel],
				NULL,
				&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG,
				&g_pMeshPlayerBG[nCntModel]);


			//マテリアル情報に対するポインタを所得
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayerBG[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat]);
				}
			}
		}
	}
}

//====================================================================
//プレイヤーの終了処理(リザルト用)
//====================================================================
void UninitResultPlayer(void)
{
	for (int nCntPlayerBG = 0; nCntPlayerBG < GetExitCount(); nCntPlayerBG++)
	{
		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			for (int nCntMat = 0; nCntMat < (int)g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG; nCntMat++)
			{
				//テクスチャの破棄
				if (g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat] != NULL)
				{
					g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat]->Release();
					g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat] = NULL;
				}
			}
		}

		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			//メッシュの破棄
			if (g_pMeshPlayerBG[nCntModel] != NULL)
			{
				g_pMeshPlayerBG[nCntModel]->Release();
				g_pMeshPlayerBG[nCntModel] = NULL;
			}

			//マテリアルの破棄
			if (g_pBuffMatPlayerBG[nCntModel] != NULL)
			{
				g_pBuffMatPlayerBG[nCntModel]->Release();
				g_pBuffMatPlayerBG[nCntModel] = NULL;
			}
		}
	}
}

//====================================================================
//プレイヤーの更新処理(リザルト用)
//====================================================================
void UpdateResultPlayer(void)
{
	//モーションの更新処理
	for (int nCntPlayerBG = 0; nCntPlayerBG <  GetExitCount(); nCntPlayerBG++)
	{
		UpdatePlayerMotion(nCntPlayerBG);
	}
}

//====================================================================
//プレイヤーの描画処理(リザルト用)
//====================================================================
void DrawResultPlayer(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (int nCntPlayerBG = 0; nCntPlayerBG <  GetExitCount(); nCntPlayerBG++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_PlayerBG[nCntPlayerBG].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_PlayerBG[nCntPlayerBG].rot.y, g_PlayerBG[nCntPlayerBG].rot.x, g_PlayerBG[nCntPlayerBG].rot.z);
		D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].mtxWorld, &g_PlayerBG[nCntPlayerBG].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_PlayerBG[nCntPlayerBG].pos.x, g_PlayerBG[nCntPlayerBG].pos.y, g_PlayerBG[nCntPlayerBG].pos.z);
		D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].mtxWorld, &g_PlayerBG[nCntPlayerBG].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_PlayerBG[nCntPlayerBG].mtxWorld);

		//現在のマテリアルを所得
		pDevice->GetMaterial(&matDef);

		//全モデル(パーツ)の描画
		for (int nCntModel = 0; nCntModel < g_PlayerBG[nCntPlayerBG].nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用マトリックス
			D3DXMATRIX mtxParent;	//親のマトリックス

									//パーツのマトリックスを初期化
			D3DXMatrixIdentity(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld);

			//パーツの向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].rot.y, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].rot.x, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &mtxRotModel);

			//パーツの位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].pos.x, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].pos.y, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの「親のマトリックス」を設定
			if (g_PlayerBG[nCntPlayerBG].aModel[nCntModel].nIndexModelParent != -1)
			{//親モデルがある場合
				mtxParent = g_PlayerBG[nCntPlayerBG].aModel[g_PlayerBG[nCntPlayerBG].aModel[nCntModel].nIndexModelParent].mtxWorld;	//親モデルのインデックスのマトリックスを指定する
			}
			else
			{//親モデルがない場合
				mtxParent = g_PlayerBG[nCntPlayerBG].mtxWorld;	//プレイヤーのマトリックスを指定する
			}

			//算出した「パーツのワールドマトリックス」と「親のマトリックス」を掛け合わせる
			D3DXMatrixMultiply(&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld,
				&g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld,
				&mtxParent);

			//パーツのワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &g_PlayerBG[nCntPlayerBG].aModel[nCntModel].mtxWorld);

			//マテリアルデータへのポインタを所得する
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayerBG[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_dwNumMatPlayerBG; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (g_PlayerBG[nCntPlayerBG].bUse == true)
				{
					//テクスチャの設定
					pDevice->SetTexture(0, g_PlayerBG[nCntPlayerBG].aModel[nCntModel].g_pTexturePlayerBG[nCntMat]);

					//プレイヤー(パーツ)の描画
					g_pMeshPlayerBG[nCntModel]->DrawSubset(nCntMat);
				}
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}