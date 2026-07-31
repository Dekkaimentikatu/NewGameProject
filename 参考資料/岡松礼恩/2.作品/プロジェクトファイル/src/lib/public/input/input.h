#pragma once
#ifndef _INPUT_DATA_H_
#define _INPUT_DATA_H_

#include <DxLib.h>
#include <memory>

//利用する可能性のあるキーのマクロのコピペ用
//KEY_INPUT_Q
//KEY_INPUT_W
//KEY_INPUT_E
//KEY_INPUT_A
//KEY_INPUT_S
//KEY_INPUT_D
//KEY_INPUT_Z
//KEY_INPUT_X
//KEY_INPUT_C
//KEY_INPUT_SPACE

constexpr int INPUT_NUM = 256;

class C_INPUT	//入力管理用のクラス
{
protected:

	static char m_inputBuf[INPUT_NUM];	//現在の入力状況を一時的に保存するための変数

	static char m_inputOldBuf[INPUT_NUM];	//前回の入力状況を一時的に保存するための変数

	static int m_isPush;			//現在入力されたかどうかを保存する変数

	static int m_isOldPush;			//前回入力されたかどうかを保存する変数

public:

	//キー入力初期化
	static void Init();
	//キー入力情報更新
	static void Update();
	//キー入力判定(通常判定)
	static bool IsInputRep(unsigned int key);
	//キー入力判定(トリガー判定)
	static bool IsInputTrg(unsigned int key);
};

#endif _INPUT_DATA_H_

