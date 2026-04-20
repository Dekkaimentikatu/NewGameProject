#include "lib/se_manager.h"

using namespace std;

C_SE_MANAGER* C_SE_MANAGER::m_instance = nullptr;

//定義関連
static const char* SE_PATH[C_SE_MANAGER::SE_NUM] =
{
	"data/se/attack.mp3",
	"data/se/jump.mp3",
};

//グローバル変数を作成


C_SE_MANAGER* C_SE_MANAGER::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new C_SE_MANAGER;
	}

	return m_instance;
}

void C_SE_MANAGER::DeleteInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}


//ハンドル初期化関数
void C_SE_MANAGER::Init()
{
	m_hndl.clear();
}
//データ読込関数
void C_SE_MANAGER::Load()
{
	for (int i = 0; i < SE_NUM; i++)
	{
		int hndl = LoadSoundMem(SE_PATH[i]);
		m_hndl.push_back(hndl);
	}
}

//終了前に行う必要がある処理関数
void C_SE_MANAGER::Exit()
{
	for (int i = 0; i < m_hndl.size(); i++)
	{
		if (m_hndl[i] != -1)
		{
			DeleteSoundMem(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}
}

//再生
bool C_SE_MANAGER::Play(int soundID, int type, bool isStart)
{
	if (soundID >= SE_NUM)return false;
	int Err = PlaySoundMem(m_hndl[soundID], type);

	if (Err == -1)return false;
	else return true;
}

//停止
void C_SE_MANAGER::Stop(int soundID)
{
	if (soundID >= SE_NUM)return;
	StopSoundMem(m_hndl[soundID]);
}

//全データ停止
void C_SE_MANAGER::StopAll()
{
	for (int i = 0; i < SE_NUM; i++)
	{
		StopSoundMem(i);
	}
}

bool C_SE_MANAGER::IsPlay(int soundID)
{
	int Err = CheckSoundMem(m_hndl[soundID]);
	if (Err == 1)return true;
	else return false;
}