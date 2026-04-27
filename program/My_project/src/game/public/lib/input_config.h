#pragma once

#include "input.h"
#include "xinput.h"
#include "mouseinput.h"

// 入力設定管理クラス
class C_INPUT_CONFIG
{
public:

	enum INPUT_BUTTAN_SATATE
	{
		MOVE_LEFT,	//左移動
		MOVE_RIGHT,	//右移動
		MOVE_FRONT,	//全身
		MOVE_REAR,	//後退

		COM_ROT_L,	//カメラ左回転
		COM_ROT_R,	//カメラ右回転
		COM_ROT_U,	//カメラ上回転
		COM_ROT_D,	//カメラ下回転

		SELECT_L,	//セレクト左
		SELECT_R,	//セレクト右
		SELECT_U,	//セレクト上
		SELECT_D,	//セレクト下

		DECISION,	//決定
		CANCEL,		//キャンセル

		ATTACK,		//攻撃
		JUMP,		//ジャンプ
		STOP,
		TARGET,		//ターゲット

		I_CONFIG_STATE_NUM
	};

	enum INPUT_STICK_STATE
	{
		MOVE_LR,
		MOVE_FR,

		COM_ROT_LR,
		COM_ROT_UD,
	};

	enum CONFIG_MODE
	{
		COM_LR_REVERSE,
		COM_MOVE_CALC,

		MODE_NUM,
	};

	typedef struct
	{
		int pad;
		int key;
	}T_KEY_COMFIG;

	typedef struct
	{
		int pad;
	}T_STICK_COMFIG;

private:

	static T_KEY_COMFIG m_defaultKeyConfig[I_CONFIG_STATE_NUM];

	static T_KEY_COMFIG m_customKeyConfig[I_CONFIG_STATE_NUM];

	static int configMode[MODE_NUM];

public:

	static void Init();

	static void Updata();

	static bool IsButtanInputRep(INPUT_BUTTAN_SATATE _state);

	static bool IsButtanInputTrg(INPUT_BUTTAN_SATATE _state);

	static float IsStickInput(INPUT_STICK_STATE _state);
};

