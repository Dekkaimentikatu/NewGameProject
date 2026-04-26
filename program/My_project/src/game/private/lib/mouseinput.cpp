#include "lib/mouseinput.h"

MOUSE_INPUT_DATA C_MOUSE_INPUT::c_mouseInputData;

//キー入力初期化
void C_MOUSE_INPUT::InitMouseInput()
{
	c_mouseInputData.m_nowPos = VGet(0, 0, 0);	//マウスの座標を初期化
	c_mouseInputData.m_prevPos = VGet(0, 0, 0);//前回のマウスの座標を初期化
	c_mouseInputData.m_movePos = VGet(0, 0, 0);	//マウスの移動量を初期化
	c_mouseInputData.m_posX = 0;	//マウスのX座標を初期化
	c_mouseInputData.m_posY = 0;	//マウスのY座標を初期化
	c_mouseInputData.m_nowButton = 0;	//マウスのボタンの状態を初期化
	c_mouseInputData.m_prevButton = 0;	//前回のマウスのボタンの状態を初期化
	c_mouseInputData.m_inputLog = -1;	//マウスのログを初期化
	c_mouseInputData.m_inputInfo = -1;	//マウスの入力情報を初期化
}

//キー入力情報更新
void C_MOUSE_INPUT::UpdateMouseInput()
{
	c_mouseInputData.m_inputInfo
		= GetMouseInputLog2
		(
			&c_mouseInputData.m_nowButton,
			&c_mouseInputData.m_posX,
			&c_mouseInputData.m_posY,
			&c_mouseInputData.m_inputLog
		);	//マウスの座標を取得

	c_mouseInputData.m_nowPos = VGet((float)c_mouseInputData.m_posX, (float)c_mouseInputData.m_posY, 0);

	if (GetMouseInputInfo() == 0 && IsMouseInputLogDOWN() == true)
	{
		c_mouseInputData.m_prevPos = c_mouseInputData.m_nowPos;
	}

	if (GetMouseInputInfo() == -1)
	{
		GetMousePoint(&c_mouseInputData.m_posX, &c_mouseInputData.m_posY);
	}
}

//キー入力判定(通常判定)
bool C_MOUSE_INPUT::IsMouseInputRep(unsigned int key)
{
	if (c_mouseInputData.m_nowButton & key)	//マウスのボタンの状態を取得
	{
		return true;	//マウスのボタンが押されている
	}
	else
	{
		return false;	//マウスのボタンが押されていない
	}

}

//キー入力判定(トリガー判定)
bool C_MOUSE_INPUT::IsMouseInputTrg(unsigned int key)
{
	if ((c_mouseInputData.m_nowButton & key) && !(c_mouseInputData.m_prevButton & key))	//マウスのボタンの状態を取得
	{
		return true;	//マウスのボタンが押された
	}
	else
	{
		return false;	//マウスのボタンが押されていない
	}
}

//マウスの座標を取得
VECTOR C_MOUSE_INPUT::GetNowMousePos()
{
	return c_mouseInputData.m_nowPos;	//マウスの座標を取得
}

//前回のマウスの座標を取得
VECTOR C_MOUSE_INPUT::GetPrevMousePos()
{
	return c_mouseInputData.m_prevPos;	//前回のマウスの座標を取得
}

//マウスの移動量を取得
VECTOR C_MOUSE_INPUT::GetMoveMouseVec()
{
	return c_mouseInputData.m_movePos;	//マウスの移動量を取得
}

//マウスのボタンの状態を取得
int C_MOUSE_INPUT::GetMouseButtonState()
{
	return c_mouseInputData.m_nowButton;	//マウスのボタンの状態を取得
}

int C_MOUSE_INPUT::GetMouseInputInfo()
{
	return c_mouseInputData.m_inputInfo;	//マウスの入力情報を取得
}

bool C_MOUSE_INPUT::IsMouseInputLogUP()
{
	return c_mouseInputData.m_inputLog == MOUSE_INPUT_LOG_UP && c_mouseInputData.m_inputInfo == 0 ? true : false;
}

bool C_MOUSE_INPUT::IsMouseInputLogDOWN()
{
	return c_mouseInputData.m_inputLog == MOUSE_INPUT_LOG_DOWN && c_mouseInputData.m_inputInfo == 0 ? true : false;
}