#pragma once
#include <DxLib.h>
#include <vector>

using namespace std;

class C_BGM_MANAGER
{
public:

	//定義関連
	enum tagSound {
		BGMID_TITLE,	//タイトル画面のBGM
		BGMID_GAME,		//ゲーム本編のBGM
		BGMID_RESULT,
		BGMID_SELECT,

		BGM_NUM,		//使用する音の数
	};

private:

	C_BGM_MANAGER() = default;

	~C_BGM_MANAGER() = default;

	vector<int> m_hndl;	//サウンドハンドル

	static C_BGM_MANAGER* m_instance;

public:

	//ハンドル初期化関数
	void Init();

	//データ読込関数
	void Load();

	//終了前に行う必要がある処理関数
	void Exit();

	//再生
	bool Play(int soundID, int type = DX_PLAYTYPE_BACK, bool isStart = true);

	//停止
	void Stop(int soundID);

	//全データ停止
	void StopAll();

	bool IsPlay(int soundID);

	static C_BGM_MANAGER* GetInstance();

	static void DeleteInstance();
};

