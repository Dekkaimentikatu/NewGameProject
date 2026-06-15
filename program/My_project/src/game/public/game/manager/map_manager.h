#pragma once
#include "game/base/manager_base.h"
#include "game/stage/stage_loader.h"
#include "game/voxel/voxel_world.h"

constexpr int X_MAX = 32;
constexpr int Y_MAX = 32;
constexpr int Z_MAX = 32;

class C_MAP_MANAGER : public C_OBJECT_MANAGER_BASE
{
public:

	enum SELECT_STAGE {
		SELECT_STAGE_1,
		SELECT_STAGE_2,
		SELECT_STAGE_3,
		SELECT_STAGE_MAX,
	};

private:

	C_VOXEL_WORLD c_world;

	C_STAGE_LOADER m_stageLoader;	//ステージローダー

public:

	C_MAP_MANAGER(){}

	//初期化
	void Init();

	//リソース読込
	void LoadAnSync();	

	//読込
	void LoadSync();

	//更新
	void Step();

	//更新確定
	void Update();

	//描画
	void Draw();

	//終了
	void Exit();
};


static const char* MAP_FILE_PATH[C_MAP_MANAGER::SELECT_STAGE_MAX] = { "data/csv/stage/stage1.csv",
																	  "data/csv/stage/stage2.csv",
																	  "data/csv/stage/stage3.csv" };
