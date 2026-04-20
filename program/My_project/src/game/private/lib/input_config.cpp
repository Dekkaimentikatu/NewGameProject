#include "lib/input_config.h"
#include "lib/xinput.h"
#include "lib/input.h"
#include "lib/mouseinput.h"

C_INPUT_CONFIG::T_KEY_COMFIG C_INPUT_CONFIG::m_defaultKeyConfig[I_CONFIG_STATE_NUM] =
{
	-1, KEY_INPUT_A,
	-1, KEY_INPUT_D,
	-1, KEY_INPUT_W,
	-1, KEY_INPUT_S,

	-1, KEY_INPUT_LEFT,
	-1, KEY_INPUT_RIGHT,
	-1, KEY_INPUT_UP,
	-1, KEY_INPUT_DOWN,

	XINPUT_BUTTON_A, KEY_INPUT_Z,
	XINPUT_BUTTON_B, KEY_INPUT_X,

	XINPUT_BUTTON_X, KEY_INPUT_RETURN,
	XINPUT_BUTTON_A, KEY_INPUT_SPACE,
	XINPUT_BUTTON_Y, KEY_INPUT_T,
};

C_INPUT_CONFIG::T_KEY_COMFIG C_INPUT_CONFIG::m_customKeyConfig[I_CONFIG_STATE_NUM] =
{

};

int C_INPUT_CONFIG::configMode[MODE_NUM]
{
	1,
	0
};

void C_INPUT_CONFIG::Init()
{
	C_INPUT::Init();
	C_XINPUT::Init();

	memcpy(m_customKeyConfig, m_defaultKeyConfig, sizeof(m_defaultKeyConfig));
		
}

void C_INPUT_CONFIG::Updata()
{
	C_XINPUT::UpdateAll();
	C_INPUT::Update();
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

float C_INPUT_CONFIG::IsStickInput(INPUT_STICK_STATE _state)
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

	return 0.0f;
}