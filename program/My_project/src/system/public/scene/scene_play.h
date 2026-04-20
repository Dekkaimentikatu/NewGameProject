#pragma once

#include "scene.h"

#include "game/object/static/sky.h"
#include "game/manager/player_manager.h"
#include "game/manager/enemy_manager.h"
#include "game/manager/map_manager.h"
#include "game/camera/camera_manager.h"
#include "game/collision/collision_manager.h"
#include "UI/UI_manager.h"
#include "effekseer/effekseer.h"

class C_SCENE_PLAY: public C_SCENE_BASE
{
private:

	C_PLAYER_MANAGER c_playerManager;

	C_ENEMY_MANAGER c_enemyManager;

	C_MAP_MANAGER c_mapManager;

	C_CAMERA_MANAGER_ c_cameraManager;

	enum PLAY_STATE
	{
		START,
		PLAYWAIT,
		PLAY,
		RESPAWN,
		GOAL,
		FADE,
	};

	PLAY_STATE m_playState;

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

	~C_SCENE_PLAY() override;	//デストラクタ

	void Exit();
};