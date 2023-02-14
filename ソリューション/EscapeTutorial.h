#ifndef _ESCAPETUTORIAL_H_
#define _ESCAPETUTORIAL_H_

<<<<<<< HEAD
//フェードの状態
typedef enum
{
	TUTORIAL_STATE_STANDBY = 0,
	TUTORIAL_STATE_WAIT,
	TUTORIAL_STATE_PLAY,
	TUTORIAL_STATE_MAX,
}TUTORIAL_STATE;
=======
//チュートリアル内容の構造体(列挙)
typedef enum
{
	MODE_MOVE = 0,		//プレイヤーの移動
	MODE_CAM_MOVE,		//カメラの移動
	MODE_DASH,			//ダッシュ
	MODE_VIBE,			//バイブ
	MODE_STELTH,		//ステルス
	MODE_GET_KEY,		//鍵をとる
	MODE_ESCAPE,		//脱出
	MODE__TUTORIAL_MAX,
}TUTORIAL_MODE;
>>>>>>> 3c1ab6ec40d2986d361626d60a22a57874703004

//プロトタイプ宣言
void InitEscapeTutorial();
void UninitEscapeTutorial();
void UpdateEscapeTutorial();
void DrawEscapeTutorial();
TUTORIAL_STATE GetEscapeTutorial();
void SetEscapeTutorial(TUTORIAL_STATE nSet);
#endif