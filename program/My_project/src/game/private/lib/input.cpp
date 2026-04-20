#include "lib/input.h"


char C_INPUT::m_inputBuf[INPUT_NUM] = {0};

char C_INPUT::m_inputOldBuf[INPUT_NUM] = { 0 };

int C_INPUT::m_isPush = 0;

int C_INPUT::m_isOldPush = 0;

//キー入力初期化
void C_INPUT::Init()
{
	memset(m_inputBuf, 0, INPUT_NUM);
	memset(m_inputOldBuf, 0, INPUT_NUM);

	m_isOldPush = m_isPush = 0;
}

//キー入力情報更新
void C_INPUT::Update()
{
	memcpy(m_inputOldBuf, m_inputBuf, INPUT_NUM);
	GetHitKeyStateAll(m_inputBuf);
	m_isOldPush = m_isPush;
	m_isPush = CheckHitKeyAll() != 0;
}

//キー入力判定(通常判定)
bool C_INPUT::IsInputRep(unsigned int key)
{
	if (key < static_cast<unsigned int>(INPUT_NUM))return m_inputBuf[key] == 1;
	else return false;
}

//キー入力判定(トリガー判定)
bool C_INPUT::IsInputTrg(unsigned int key)
{
	if (key < static_cast<unsigned int>(INPUT_NUM))
	{
		return (m_inputBuf[key] == 1 && m_inputOldBuf[key] != 1);
	}
	else return false;
}