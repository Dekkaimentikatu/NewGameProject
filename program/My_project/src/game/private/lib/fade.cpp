#include "lib/fade.h"

C_FADE::T_FADE_DATA C_FADE::c_fadeData;

//データの初期化
void C_FADE::Init()
{
	c_fadeData.m_state = T_FADE_DATA::FADE_OUT_WAIT;
	c_fadeData.m_count = FADE_ALPHA_MAX;
}
//データの変遷全体を制御
void C_FADE::Update()
{
	switch (c_fadeData.m_state)
	{
	case T_FADE_DATA::FADE_NOM:
		//値を固定
		c_fadeData.m_count = 0;
		break;
	case T_FADE_DATA::FADE_IN:
		//徐々に明るくなる
		c_fadeData.m_count -= FADE_SPEED;
		//0になったらフェードイン終了
		if (c_fadeData.m_count <= 0)
		{
			c_fadeData.m_count = 0;		//安全策
			c_fadeData.m_state = T_FADE_DATA::FADE_NOM;
		}
		break;
	case T_FADE_DATA::FADE_OUT:
		//徐々に暗くなる
		c_fadeData.m_count += FADE_SPEED;
		//255になったらフェードアウト終了
		if (c_fadeData.m_count >= FADE_ALPHA_MAX)
		{
			c_fadeData.m_count = FADE_ALPHA_MAX;	//安全策
			c_fadeData.m_state = T_FADE_DATA::FADE_OUT_WAIT;
		}
		break;
	case T_FADE_DATA::FADE_OUT_WAIT:
		//値を固定
		c_fadeData.m_count = FADE_ALPHA_MAX;
		break;
	}
}
// 状態変遷の中にあるすべての描画を管理
void C_FADE::Draw()
{
	switch (c_fadeData.m_state)
	{
	case T_FADE_DATA::FADE_NOM:
	case T_FADE_DATA::FADE_IN:
	case T_FADE_DATA::FADE_OUT:
	case T_FADE_DATA::FADE_OUT_WAIT:

		//まずはここでアルファ値をセットする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, c_fadeData.m_count);

		//フェード用の黒い四角を用意する
		DrawBox(0, 0, FADE_SIZE_X, FADE_SIZE_Y,
			GetColor(0, 0, 0), TRUE);

		//ほかの画像に影響を出さないよう、初期設定に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, FADE_ALPHA_MAX);
		break;
	}
}

//フェードインリクエスト
void C_FADE::RequestFadeIn()
{
	//フェードアウト終了後ならリクエスト
	if (!IsFadeState(T_FADE_DATA::FADE_OUT_WAIT))return;
	c_fadeData.m_state = T_FADE_DATA::FADE_IN;
}

//フェードアウトリクエスト
void C_FADE::RequestFadeOut()
{
	//フェードイン終了後ならリクエスト
	if (!IsFadeState(T_FADE_DATA::FADE_NOM))return;
	c_fadeData.m_state = T_FADE_DATA::FADE_OUT;
}

//フェードインが終了したか
bool C_FADE::IsEndFadeIn()
{
	//フェードイン時はまだやっている
	if (c_fadeData.m_state == T_FADE_DATA::FADE_IN)
	{
		return false;
	}
	//他は少なくともフェードインではない
	else return true;
}

//フェードアウトが終了したか
bool C_FADE::IsEndFadeOut()
{
	//フェードアウト時はまだやっている
	if (c_fadeData.m_state == T_FADE_DATA::FADE_OUT)
	{
		return false;
	}
	//他は少なくともフェードアウトではない
	else return true;
}

//今どの状態か
bool C_FADE::IsFadeState(T_FADE_DATA::tagFadeState _state)
{
	if (c_fadeData.m_state == _state)
	{
		return true;
	}
	else return false;
}