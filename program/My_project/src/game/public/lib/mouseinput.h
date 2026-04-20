#pragma once

#include <DxLib.h>

#define CLICK_LEFT	(0b1)
#define CLICK_RIGHT	(0b10)

class MOUSE_INPUT_DATA
{
public:
	VECTOR m_nowPos;	//マウスの座標
	VECTOR m_prevPos;	//前回のマウスの座標
	VECTOR m_movePos;	//マウスの移動量
	int m_posX;	//マウスのX座標
	int m_posY;	//マウスのY座標
	int m_nowButton;	//マウスのボタンの状態
	int m_prevButton;	//前回のマウスのボタンの状態
	int m_inputLog;	//マウスのログ
	int m_inputInfo;	//マウスの入力情報
};

class C_MOUSE_INPUT
{
private:

	static MOUSE_INPUT_DATA c_mouseInputData;	//マウスの入力データの構造体
	
public:
	//キー入力初期化
	static void InitMouseInput();
	//キー入力情報更新
	static void UpdateMouseInput();
	//キー入力判定(通常判定)
	static bool IsMouseInputRep(unsigned int key);
	//キー入力判定(トリガー判定)
	static  bool IsMouseInputTrg(unsigned int key);

	//マウスの座標を取得
	static VECTOR GetNowMousePos();

	//前回のマウスの座標を取得
	static VECTOR GetPrevMousePos();

	//マウスの移動量を取得
	static VECTOR GetMoveMouseVec();

	//マウスのボタンの状態を取得
	static int GetMouseButtonState();


	static int GetMouseInputInfo();

	static bool IsMouseInputLogUP();

	static bool IsMouseInputLogDOWN();
};

