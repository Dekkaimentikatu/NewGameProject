#pragma once

#include <DxLib.h>

//定数関連
constexpr int M_SECOND = 1000;
constexpr int FPS = 60;
constexpr int FONT_X = 16;
constexpr int FONT_Y = 16;
constexpr int RED = 255;
constexpr int GREEN = 255;
constexpr int BLUE = 255;

//変数表示構造体
class C_FPS_DATA {
public:
	float m_frameRate;	//FPS
	int m_nowTime;		//現在のシステム時間
	int m_prevTime;		//前回の時間
	int m_prevDrawTime;	//前回の描画した時間
	int m_count;		//カウンタ
};

class C_FPS
{
private:

	static C_FPS_DATA c_fps;

public:
	//FPS表示関連
	static void Disp();

	//変数初期化
	static void Init();

	//60FPSに固定
	static void Wait();

	//次の処理へ進んでいいか判断
	static bool IsNextFrame();

	//
	static void Step();
};

