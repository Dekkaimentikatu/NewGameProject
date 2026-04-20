#include "lib/bgm_manager.h"
#include <math.h>

C_BGM_MANAGER* C_BGM_MANAGER::m_instance = nullptr;

//定義関連
static const char* BGM_PATH[C_BGM_MANAGER::BGM_NUM] =
{
	"data/bgm/title.mp3",
	"data/bgm/play.mp3",
	"data/bgm/result.mp3",
	"data/bgm/select.mp3",
};

//グローバル変数を作成


C_BGM_MANAGER* C_BGM_MANAGER::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new C_BGM_MANAGER;
	}

	return m_instance;
}

void C_BGM_MANAGER::DeleteInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}


//ハンドル初期化関数
void C_BGM_MANAGER::Init()
{
	m_hndl.clear();
}
//データ読込関数
void C_BGM_MANAGER::Load()
{
	for (int i = 0; i < BGM_NUM; i++)
	{
		int hndl = LoadSoundMem(BGM_PATH[i]);
		m_hndl.push_back(hndl);
	}
}

//終了前に行う必要がある処理関数
void C_BGM_MANAGER::Exit()
{
	for (int i = 0; i < BGM_NUM; i++)
	{
		if (m_hndl[i] != -1)
		{
			DeleteSoundMem(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}
}

//再生
bool C_BGM_MANAGER::Play(int soundID, int type, bool isStart)
{
	if (soundID >= BGM_NUM)return false;
	int Err = PlaySoundMem(m_hndl[soundID], type);

	if (Err == -1)return false;
	else return true;
}

//停止
void C_BGM_MANAGER::Stop(int soundID)
{
	if (soundID >= BGM_NUM)return;
	StopSoundMem(m_hndl[soundID]);
}

//全データ停止
void C_BGM_MANAGER::StopAll()
{
	for (int i = 0; i < BGM_NUM; i++)
	{
		StopSoundMem(i);
	}
}

bool C_BGM_MANAGER::IsPlay(int soundID)
{
	int Err = CheckSoundMem(m_hndl[soundID]);
	if (Err == 1)return true;
	else return false;
}