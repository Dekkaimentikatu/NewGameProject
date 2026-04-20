#include "lib/xinput.h"


XINPUT_STATE C_XINPUT::t_nowInputState[4] = {0};

XINPUT_STATE C_XINPUT::t_pravInputState[4] = {0};

double C_XINPUT::m_deadZone[4] = {1.0};

int C_XINPUT::Init()
{
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		t_nowInputState[i].ThumbLX = 0;
		t_nowInputState[i].ThumbRX = 0;
		t_nowInputState[i].ThumbLY = 0;
		t_nowInputState[i].ThumbRY = 0;
	}

	return 0;

	
}

bool C_XINPUT::GetConnectPad(const int _padID)
{
	return GetJoypadNum() >= _padID ? true : false;	//接続されていればtrueを返す
}

int C_XINPUT::Update(const int _padID)
{
	t_pravInputState[_padID - 1] = t_nowInputState[_padID - 1];		//前回の入力状況を最新の入力情報に更新

	if (GetJoypadXInputState(_padID, &t_nowInputState[_padID - 1]) == -1)return -1;	//最新の入力状況を取得
																					//エラーが発生すると-1を返す
	return 1;
}

int C_XINPUT::UpdateAll()
{
	for (int i = 1; i <= GetJoypadNum(); i++)			//接続されているコントローラーの分だけ更新
	{
		t_pravInputState[i - 1] = t_nowInputState[i - 1];		//前回の入力状況を最新の入力情報に更新

		if (GetJoypadXInputState(i, &t_nowInputState[i - 1]) == -1)return -1;	//最新の入力状況を取得
		//エラーが発生すると-1を返す
	}

	return 1;
}

bool C_XINPUT::GetButtanInputRep(const int _padID, const int _keyID)
{
	return t_nowInputState[_padID - 1].Buttons[_keyID] == 1 ? true : false;	//入力があればtrueを返す
}

bool C_XINPUT::GetButtanInputTrg(const int _padID, const int _keyID)
{
	//入力がある且つ前回入力されていなければtrueを返す
	return t_nowInputState[_padID - 1].Buttons[_keyID] == 1 &&
	t_pravInputState[_padID - 1].Buttons[_keyID] == 0 ? true : false;
}

bool C_XINPUT::GetLAnalogInput(const int _padID)
{
	return t_nowInputState[_padID - 1].ThumbLX != static_cast<short>(0) ||
	t_nowInputState[_padID - 1].ThumbLY != static_cast<short>(0) ? true : false;	//入力されていればtrueを返す
}

float C_XINPUT::GetLAnalogXInput(const int _padID)
{
	if (t_nowInputState[_padID - 1].ThumbLX == 0)return 0.0f;	//何も入力されていなければ処理を行わない

	float input = 0.0f;

	if (t_nowInputState[_padID - 1].ThumbLX > THUMB_LIMIT)
	{
		//入力の強度を最大値で除算
		input = static_cast<float>(t_nowInputState[_padID - 1].ThumbLX) / static_cast<float>(THUMB_MAX);
	}
	else if (t_nowInputState[_padID - 1].ThumbLX < -THUMB_LIMIT)
	{
		//入力の強度を最小値で除算
		input = static_cast<float>(-t_nowInputState[_padID - 1].ThumbLX) / static_cast<float>(THUMB_MIN);
	}



	return input;		//除算の結果を返す
}

float C_XINPUT::GetLAnalogYInput(const int _padID)
{
	if (t_nowInputState[_padID - 1].ThumbLY == 0)return 0.0f;	//何も入力されていなければ処理を行わない

	float input = 0.0f;

	if (t_nowInputState[_padID - 1].ThumbLY > THUMB_LIMIT)
	{
		//入力の強度を最大値で除算
		input = static_cast<float>(t_nowInputState[_padID - 1].ThumbLY) / static_cast<float>(THUMB_MAX);
	}
	else if (t_nowInputState[_padID - 1].ThumbLY < -THUMB_LIMIT)
	{
		//入力の強度を最小値で除算
		input = static_cast<float>(-t_nowInputState[_padID - 1].ThumbLY) / static_cast<float>(THUMB_MIN);
	}

	return input;		//除算の結果を返す
}

float C_XINPUT::GetLAnalogAngle(const int _padID)
{
	float angle = atan2f(static_cast<double>(t_nowInputState[_padID].ThumbLY),
		static_cast<double>(t_nowInputState[_padID - 1].ThumbLX)) + M_PI;

	return angle;
}

bool C_XINPUT::GetRAnalogInput(const int _padID)
{
	return t_nowInputState[_padID - 1].ThumbRX != static_cast<short>(0) ||
		t_nowInputState[_padID - 1].ThumbRY != static_cast<short>(0) ? true : false;	//入力されていればtrueを返す
}

float C_XINPUT::GetRAnalogXInput(const int _padID)
{
	if (t_nowInputState[_padID - 1].ThumbRX == 0)return 0.0f;	//何も入力されていなければ処理を行わない

	float input = 0.0f;

	if (t_nowInputState[_padID - 1].ThumbRX > THUMB_LIMIT)
	{
		//入力の強度を最大値で除算
		input = static_cast<float>(t_nowInputState[_padID - 1].ThumbRX) / static_cast<float>(THUMB_MAX);
	}
	else if (t_nowInputState[_padID - 1].ThumbRX < -THUMB_LIMIT)
	{
		//入力の強度を最小値で除算
		input = static_cast<float>(-t_nowInputState[_padID - 1].ThumbRX) / static_cast<float>(THUMB_MIN);
	}

	return input;		//除算の結果を返す
}

float C_XINPUT::GetRAnalogYInput(const int _padID)
{
	if (t_nowInputState[_padID - 1].ThumbRY == 0)return 0.0f;	//何も入力されていなければ処理を行わない

	float input = 0.0f;

	if (t_nowInputState[_padID - 1].ThumbRY > THUMB_LIMIT)
	{
		//入力の強度を最大値で除算
		input = static_cast<float>(t_nowInputState[_padID - 1].ThumbRY) / static_cast<float>(THUMB_MAX);
	}
	else if (t_nowInputState[_padID - 1].ThumbRY < -THUMB_LIMIT)
	{
		//入力の強度を最小値で除算
		input = static_cast<float>(-t_nowInputState[_padID - 1].ThumbRY) / static_cast<float>(THUMB_MIN);
	}

	return input;		//除算の結果を返す
}

float C_XINPUT::GetRAnalogAngle(const int _padID)
{
	float angle = atan2f(static_cast<double>(t_nowInputState[_padID].ThumbRX),
		static_cast<double>(t_nowInputState[_padID - 1].ThumbRY)) / M_PI;

	return angle;
}

float C_XINPUT::GetLTriggerInput(const int _padID)
{
	return static_cast<float>(t_nowInputState[_padID - 1].LeftTrigger) / TRIGGER_MAX;	//入力の強度を最大値で除算
}

float C_XINPUT::GetRTriggerInput(const int _padID)
{
	return static_cast<float>(t_nowInputState[_padID - 1].RightTrigger) / TRIGGER_MAX;	//入力の強度を最大値で除算
}

int C_XINPUT::SetDeadZone(const int _padID, double _zone)
{
	if (SetJoypadDeadZone(_padID, _zone) == -1)return -1;	//最新の入力状況を取得
	//エラーが発生すると-1を返す

	m_deadZone[_padID - 1] = _zone;		//値を格納

	return 1;		//値を返して処理を終える
}

int C_XINPUT::SetDeadZoneAll(double _zone)
{
	for (int i = 1; i <= GetJoypadNum(); i++)			//接続されているコントローラーの分だけ更新
	{
		if (SetJoypadDeadZone(i, _zone) == -1)return -1;	//最新の入力状況を取得
		//エラーが発生すると-1を返す

		m_deadZone[i - 1] = _zone;		//値を格納
	}

	return 1;		//値を返して処理を終える
}