#pragma once
#define _USE_MATH_DEFINES


#include <DxLib.h>
#include <math.h>

// XInputボタン入力定義
//XINPUT_BUTTON_DPAD_UP			// デジタル方向ボタン上
//XINPUT_BUTTON_DPAD_DOWN		// デジタル方向ボタン下
//XINPUT_BUTTON_DPAD_LEFT		// デジタル方向ボタン左
//XINPUT_BUTTON_DPAD_RIGHT		// デジタル方向ボタン右
//XINPUT_BUTTON_START			// STARTボタン
//XINPUT_BUTTON_BACK			// BACKボタン
//XINPUT_BUTTON_LEFT_THUMB		// 左スティック押し込み
//XINPUT_BUTTON_RIGHT_THUMB		// 右スティック押し込み
//XINPUT_BUTTON_LEFT_SHOULDER	// LBボタン
//XINPUT_BUTTON_RIGHT_SHOULDER	// RBボタン
//XINPUT_BUTTON_A				// Aボタン
//XINPUT_BUTTON_B				// Bボタン
//XINPUT_BUTTON_X				// Xボタン
//XINPUT_BUTTON_Y				// Yボタン

//スティックの最大入力値
constexpr short THUMB_MAX = 32767;
//スティックの最小入力値
constexpr short THUMB_MIN = -32768;
//スティックの入力受付制限
constexpr short THUMB_LIMIT = 3000;
//トリガーボタンの最大入力値
constexpr float TRIGGER_MAX = 255.0f;

class C_XINPUT
{
private:

	static XINPUT_STATE t_nowInputState[4];

	static XINPUT_STATE t_pravInputState[4];

	static double m_deadZone[4];

public:

	//コントローラー入力情報の初期化
	static int Init();

	//指定したコントローラーの入力情報を更新
	static int Update(const int _padID);

	//全てのコントローラーの入力情報を更新
	static int UpdateAll();	

	//指定したIDのコントローラーが接続されているかを取得
	static bool GetConnectPad(const int _padID);

	//ボタン入力(通常判定)
	static bool GetButtanInputRep(const int _padID,const int _keyID);

	//ボタン入力(トリガー判定)
	static bool GetButtanInputTrg(const int _padID, const int _keyID);

	//左アナログスティックが入力されているかを取得
	static bool GetLAnalogInput(const int _padID);

	//左アナログスティックのX軸の入力強度を0.0~1.0の範囲に変換して出力
	static float GetLAnalogXInput(const int _padID);	

	//左アナログスティックのY軸の入力強度を0.0~1.0の範囲に変換して出力
	static float GetLAnalogYInput(const int _padID);		

	//左アナログスティックの角度を取得
	static float GetLAnalogAngle(const int _padID);		

	//右アナログスティックが入力されているかを取得
	static bool GetRAnalogInput(const int _padID);		

	//右アナログスティックのX軸の入力強度を0.0~1.0の範囲に変換して出力
	static float GetRAnalogXInput(const int _padID);		

	//右アナログスティックのY軸の入力強度を0.0~1.0の範囲に変換して出力
	static float GetRAnalogYInput(const int _padID);		

	//右アナログスティックの角度を取得
	static float GetRAnalogAngle(const int _padID);		

	//左トリガーの入力強度を0.0~1.0の範囲に変換して出力
	static float GetLTriggerInput(const int _padID);		

	//右トリガーの入力強度を0.0~1.0の範囲に変換して出力
	static float GetRTriggerInput(const int _padID);		

	//指定したコントローラーのデットゾーンを調整
	//0.0から1.0の間で調整
	static int SetDeadZone(const int _padID, double _zone);	

	//全てのコントローラーのデットゾーンを一括で調整
	//0.0から1.0の間で調整
	static int SetDeadZoneAll(double _zone);

};

	
