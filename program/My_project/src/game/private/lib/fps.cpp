#include "lib/fps.h"

C_FPS_DATA C_FPS::c_fps;

//変数初期化
void C_FPS::Init()
{
	c_fps.m_frameRate = 0.0f;
	c_fps.m_nowTime = GetNowCount();
	c_fps.m_prevTime = 0;
	c_fps.m_prevDrawTime = 0;
	c_fps.m_count = 0;
}

//FPS表示
void C_FPS::Disp()
{
	//1フレーム進む
	c_fps.m_count++;
	//現在の時間を取得
	c_fps.m_nowTime = GetNowCount();
	//前回の時間と現在の時間の差を取得
	int diftime = c_fps.m_nowTime - c_fps.m_prevTime;

	//差異が1秒以上あれば計算開始(1秒に1回フレームレートの表示を更新)
	if (diftime >= M_SECOND)
	{
		//ある程度正常に動けば、m_countは60になる
		float frameCount = (float)(c_fps.m_count * M_SECOND);
		//表示するfpsを更新
		c_fps.m_frameRate = frameCount / diftime;
		//カウントは0に初期化
		c_fps.m_count = 0;
		//ひとつ前の時間を更新
		c_fps.m_prevTime = c_fps.m_nowTime;
	}

	//文字の表示　引数（横座標　縦座標　色　文字）
	DrawFormatString(FONT_X,FONT_Y,GetColor(RED,GREEN,BLUE),"FPS:%.2lf",c_fps.m_frameRate);
}

//60FPSに固定
void C_FPS::Wait()
{
	int tookTime = c_fps.m_nowTime - c_fps.m_prevTime;		//かかった時間
	int waitTime = c_fps.m_count * M_SECOND / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);		//待機
	}
}

//次の処理へ進んでいいか判断
bool C_FPS::IsNextFrame()
{
	//現在の時間を取得
	c_fps.m_nowTime = GetNowCount();
	//前回の時間と現在の時間の差を取得
	int diftime = c_fps.m_nowTime - c_fps.m_prevTime;

	//差異が1秒以上あれば計算開始(1秒に1回フレームレートの表示を更新)
	if (diftime >= M_SECOND / FPS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//
void C_FPS::Step()
{
	c_fps.m_prevTime = c_fps.m_nowTime;
}