#pragma once

#include "scene.h"

class C_SCENE_RESULT : public C_SCENE_BASE
{
private:

	void Init();		//初期化処理

	void LoadAnSync();	//リソース読込処理

	void LoadSync();

	void LoadWait();	//読込待機処理

	void LoadEnd();		//読込完了処理

	void StartWait();	//更新前待機処理

	void Step();		//更新処理

	void DrawLoading();

	void DrawPlay();

	void EndWait();		//終了前待機処理

public:

	~C_SCENE_RESULT() override;	//デストラクタ

	void Exit();
};
