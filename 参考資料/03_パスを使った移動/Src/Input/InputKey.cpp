#include "InputKey.h"


char CInputKey::m_buf[256];
char CInputKey::m_oldBuf[256];


//---------------------------------
//		初期化
//---------------------------------
void	CInputKey::Init()
{
	memset(m_buf, 0, 256);
	memset(m_oldBuf, 0, 256);
}


//---------------------------------
//		キー入力情報更新
//---------------------------------
void	CInputKey::UpdateKey()
{
	memcpy(m_oldBuf, m_buf, 256);
	GetHitKeyStateAll(m_buf);
}


//---------------------------------
//		キー入力情報取得
//---------------------------------
bool	CInputKey::IsPushKeyLaw(int key)
{
	return m_buf[key] == 1;
}


//---------------------------------
//		キー入力情報取得
//---------------------------------
bool	CInputKey::IsPushKeyTrg(int key)
{
	return (m_buf[key] == 1 && m_oldBuf[key] != 1);
}


//---------------------------------
//		キー入力情報取得
//---------------------------------
bool	CInputKey::IsPushKeyRel(int key)
{
	return (m_buf[key] != 1 && m_oldBuf[key] == 1);
}


//---------------------------------
//		キー入力情報取得
//---------------------------------
bool	CInputKey::IsPushKeyLaw(int* key, int checkNum)
{
	int* p;
	bool	isPush = false;

	for (int i = 0; i < checkNum; i++)
	{
		p = key + i;
		// 1つでもヒットしていたらOK
		if (m_buf[*p] == 1)
		{
			return true;
		}
	}

	// ここまできた場合はヒットなし
	return false;
}


//---------------------------------
//		キー入力情報取得
//---------------------------------
bool	CInputKey::IsPushKeyTrg(int* key, int checkNum)
{
	int* p;
	bool	isPush = false;

	for (int i = 0; i < checkNum; i++)
	{
		p = key + i;
		// 1つでもヒットして、かつ1F前に押されていなければOK
		if (m_buf[*p] == 1 && m_oldBuf[*p] == 0)
		{
			return true;
		}
	}

	// ここまできた場合はヒットなし
	return false;
}


//---------------------------------
//		キー入力情報取得
//---------------------------------
bool	CInputKey::IsPushKeyRel(int* key, int checkNum)
{
	int* p;
	bool	isPush = false;

	for (int i = 0; i < checkNum; i++)
	{
		p = key + i;
		// 1つでもヒットして、かつ1F前に押されていなければOK
		if (m_buf[*p] == 0 && m_oldBuf[*p] == 1)
		{
			return true;
		}
	}

	// ここまできた場合はヒットなし
	return false;
}