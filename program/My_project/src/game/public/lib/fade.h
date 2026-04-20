#pragma once

#include <DxLib.h>

constexpr int FADE_SPEED = 10;
constexpr int FADE_SIZE_X = 1920;
constexpr int FADE_SIZE_Y = 1080;
constexpr int FADE_ALPHA_MAX = 255;


class C_FADE
{
private:

	typedef struct {

		enum tagFadeState {
		FADE_NOM,
		FADE_IN,
		FADE_OUT,
		FADE_OUT_WAIT,
		};
		tagFadeState m_state;
		int m_count;

	}T_FADE_DATA;

	static T_FADE_DATA c_fadeData;

public:
	//データの初期化
	static void Init();
	//データの変遷全体を制御
	static void Update();
	// 状態変遷の中にあるすべての描画を管理
	static void Draw();
	//フェードインリクエスト
	static void RequestFadeIn();
	//フェードアウトリクエスト
	static void RequestFadeOut();
	//フェードインが終了したか
	static bool IsEndFadeIn();
	//フェードアウトが終了したか
	static bool IsEndFadeOut();
	//今どの状態か
	static bool IsFadeState(T_FADE_DATA::tagFadeState _state);
};

