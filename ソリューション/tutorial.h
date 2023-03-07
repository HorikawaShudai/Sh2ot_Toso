#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//チュートリアルの状態
typedef enum
{
	TUTORIAL_STATE_GUYDE = 0,
	TUTORIAL_STATE_STANDBY,
	TUTORIAL_STATE_WAIT,
	TUTORIAL_STATE_PLAY,
	TUTORIAL_STATE_MAX,
}TUTORIAL_STATE;

//チュートリアルガイドの状態の構造体(列挙)
typedef enum
{
	TUTORIAL_GUYDE_ESCAPE = 0,
	TUTORIAL_GUYDE_KEY,
	TUTORIAL_GUYDE_HEALTH
}TUTORIAL_GUYDE;

//チュートリアル内容の構造体(列挙)
typedef enum
{
	MODE_MOVE = 0,		//プレイヤーの移動
	MODE_DASH,			//ダッシュ
	MODE_VIBE,			//バイブ
	MODE_STELTH,		//ステルス
	MODE_GET_KEY,		//鍵をとる
	MODE_ESCAPE,		//脱出
	MODE_GOEXIT,		//出口から出る
	MODE_END,			//チュートリアル項目の終了
	MODE__TUTORIAL_MAX,
}TUTORIAL_MODE;

#endif