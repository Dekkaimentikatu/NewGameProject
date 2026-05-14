#include "../public/input_config.h"
#include "../public/input/xinput.h"
#include "../public/input/input.h"
#include "../public/input/mouseinput.h"

C_INPUT_CONFIG::T_KEY_COMFIG C_INPUT_CONFIG::m_defaultKeyConfig[I_CONFIG_STATE_NUM] =
{
	-1, KEY_INPUT_A,
	-1, KEY_INPUT_D,
	-1, KEY_INPUT_W,
	-1, KEY_INPUT_S,

	-1,	KEY_INPUT_LEFT,
	-1, KEY_INPUT_RIGHT,
	-1, KEY_INPUT_UP,
	-1, KEY_INPUT_DOWN,

	XINPUT_BUTTON_DPAD_LEFT,	KEY_INPUT_A,
	XINPUT_BUTTON_DPAD_RIGHT,	KEY_INPUT_D,
	XINPUT_BUTTON_DPAD_UP,		KEY_INPUT_W,
	XINPUT_BUTTON_DPAD_DOWN,	KEY_INPUT_S,

	XINPUT_BUTTON_A, KEY_INPUT_Z,
	XINPUT_BUTTON_B, KEY_INPUT_X,

	XINPUT_BUTTON_X, KEY_INPUT_E,
	XINPUT_BUTTON_A, KEY_INPUT_SPACE,
	XINPUT_BUTTON_B, KEY_INPUT_RETURN,
	XINPUT_BUTTON_Y, KEY_INPUT_T,
};

C_INPUT_CONFIG::T_KEY_COMFIG C_INPUT_CONFIG::m_customKeyConfig[I_CONFIG_STATE_NUM] =
{

};

int C_INPUT_CONFIG::configMode[MODE_NUM]
{
	1,
};

C_INPUT_CONFIG::T_MOVE_COMFIG C_INPUT_CONFIG::m_defaultMoveConfig[M_CONFIG_STATE_NUM]
{
	{KEY_INPUT_D, KEY_INPUT_A, KEY_INPUT_D, KEY_INPUT_A },
	{KEY_INPUT_W, KEY_INPUT_S, KEY_INPUT_W, KEY_INPUT_S },
	{KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_RIGHT, KEY_INPUT_LEFT},
	{KEY_INPUT_UP, KEY_INPUT_DOWN, KEY_INPUT_DOWN, KEY_INPUT_UP},
};

C_INPUT_CONFIG::T_MOVE_COMFIG C_INPUT_CONFIG::m_customMoveConfig[M_CONFIG_STATE_NUM]
{

};

void C_INPUT_CONFIG::Init()
{
	C_INPUT::Init();
	C_XINPUT::Init();
	C_MOUSE_INPUT::Init();

	memcpy(m_customKeyConfig, m_defaultKeyConfig, sizeof(m_defaultKeyConfig));
	memcpy(m_customMoveConfig, m_defaultMoveConfig, sizeof(m_defaultMoveConfig));
		
}

void C_INPUT_CONFIG::Updata()
{
	C_XINPUT::UpdateAll();
	C_INPUT::Update();
	C_MOUSE_INPUT::Update();
}

bool C_INPUT_CONFIG::IsButtanInputRep(INPUT_BUTTAN_SATATE _state)
{
	if (C_XINPUT::GetConnectPad(DX_INPUT_PAD1))
	{
		return C_XINPUT::GetButtanInputRep(DX_INPUT_PAD1, m_customKeyConfig[_state].pad);
	}
	else
	{
		return 	C_INPUT::IsInputRep(m_customKeyConfig[_state].key);
	}
}

bool C_INPUT_CONFIG::IsButtanInputTrg(INPUT_BUTTAN_SATATE _state)
{
	if (C_XINPUT::GetConnectPad(DX_INPUT_PAD1))
	{
		return C_XINPUT::GetButtanInputTrg(DX_INPUT_PAD1, m_customKeyConfig[_state].pad);
	}
	else
	{
		return 	C_INPUT::IsInputTrg(m_customKeyConfig[_state].key);
	}
}

float C_INPUT_CONFIG::IsMoveInput(INPUT_MOVE_STATE _state)
{
	if (C_XINPUT::GetConnectPad(DX_INPUT_PAD1))
	{
		switch (_state)
		{
		case C_INPUT_CONFIG::MOVE_LR:
			return C_XINPUT::GetLAnalogXInput(DX_INPUT_PAD1);
			break;
		case C_INPUT_CONFIG::MOVE_FR:
			return C_XINPUT::GetLAnalogYInput(DX_INPUT_PAD1);
			break;
		case C_INPUT_CONFIG::COM_ROT_LR:
			if (configMode[COM_LR_REVERSE] == 0) return C_XINPUT::GetRAnalogXInput(DX_INPUT_PAD1) * -1.0f;
			else return C_XINPUT::GetRAnalogXInput(DX_INPUT_PAD1);
			break;
		case C_INPUT_CONFIG::COM_ROT_UD:
			if (configMode[COM_LR_REVERSE] == 0) return C_XINPUT::GetRAnalogYInput(DX_INPUT_PAD1) * -1.0f;
			else return C_XINPUT::GetRAnalogYInput(DX_INPUT_PAD1);
			break;
		}
	}
	else
	{
		if (C_INPUT::IsInputRep(m_defaultMoveConfig[_state].key[0][configMode[COM_LR_REVERSE]]))return 1.0f;
		else if(C_INPUT::IsInputRep(m_defaultMoveConfig[_state].key[1][configMode[COM_LR_REVERSE]]))return -1.0f;
	}


	return 0.0f;
}