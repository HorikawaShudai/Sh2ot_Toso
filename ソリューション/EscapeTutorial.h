#ifndef _ESCAPETUTORIAL_H_
#define _ESCAPETUTORIAL_H_

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

//プロトタイプ宣言
void InitEscapeTutorial();
void UninitEscapeTutorial();
void UpdateEscapeTutorial();
void DrawEscapeTutorial();
#endif