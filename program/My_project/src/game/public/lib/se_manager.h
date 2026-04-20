#pragma once

#include <DxLib.h>
#include <vector>

class C_SE_MANAGER
{
public:

	//定義関連
	enum tagSound {
		SEID_ATTACK,	//タイトル画面のBGM
		SEID_JUMP,		//ゲーム本編のBGM

		SE_NUM,		//使用する音の数
	};

private:

	C_SE_MANAGER() = default;

	~C_SE_MANAGER() = default;

	std::vector<int> m_hndl;	//サウンドハンドル

	static C_SE_MANAGER* m_instance;

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

	static C_SE_MANAGER* GetInstance();

	static void DeleteInstance();
};

