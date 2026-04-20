#include "InputKey.h"


char InputKey::m_buf[256];
char InputKey::m_beforeBuf[256];


//---------------------------------
//		初期化
//---------------------------------
void	InputKey::Init()
{
	memset(m_buf, 0, 256);
	memset(m_beforeBuf, 0, 256);
}


//---------------------------------
//		キー入力情報更新
//---------------------------------
void	InputKey::UpdateKey()
{
	memcpy(m_beforeBuf, m_buf, 256);
	GetHitKeyStateAll(m_buf);
}


//---------------------------------
//		キー入力情報取得
//---------------------------------
bool	InputKey::IsPushKeyLaw(int key)
{
	return m_buf[key] == 1;
}


//---------------------------------
//		キー入力情報取得
//---------------------------------
bool	InputKey::IsPushKeyTrg(int key)
{
	return (m_buf[key] == 1 && m_beforeBuf[key] != 1);
}


//---------------------------------
//		キー入力情報取得
//---------------------------------
bool	InputKey::IsPushKeyRel(int key)
{
	return (m_buf[key] != 1 && m_beforeBuf[key] == 1);
}


//---------------------------------
//		キー入力情報取得
//---------------------------------
bool	InputKey::IsPushKeyLaw(int* key, int checkNum)
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
bool	InputKey::IsPushKeyTrg(int* key, int checkNum)
{
	int* p;
	bool	isPush = false;

	for (int i = 0; i < checkNum; i++)
	{
		p = key + i;
		// 1つでもヒットして、かつ1F前に押されていなければOK
		if (m_buf[*p] == 1 && m_beforeBuf[*p] == 0)
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
bool	InputKey::IsPushKeyRel(int* key, int checkNum)
{
	int* p;
	bool	isPush = false;

	for (int i = 0; i < checkNum; i++)
	{
		p = key + i;
		// 1つでもヒットして、かつ1F前に押されていなければOK
		if (m_buf[*p] == 0 && m_beforeBuf[*p] == 1)
		{
			return true;
		}
	}

	// ここまできた場合はヒットなし
	return false;
}