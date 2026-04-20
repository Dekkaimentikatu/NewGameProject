#pragma once
#include <list>

#include "common.h"

#include "game/data/global_data.h"
#include "lib/drawgrap.h"
#include "scene/scene_data.h"
#include "lib/xinput.h"
#include "lib/input.h"
#include "lib/rand.h"

#include "game/base/UI_object.h"


using namespace std;

class C_UI_MANAGER
{
protected:

	C_GLOBAL_DATA* c_golobalData;
	C_GLOBAL_DATA::T_STAGE_DATA* t_stageData;
	C_SCENE_DATA* c_sceneData;

	list<C_UI_OBJECT_BASE*> c_UIObject;

	int m_posY;

	int m_rand[3];

public:

	C_UI_MANAGER(C_GLOBAL_DATA* globalData = nullptr, C_GLOBAL_DATA::T_STAGE_DATA* _stageData = nullptr,
		C_SCENE_DATA* sceneData = nullptr, int m_posY = 0) :
		c_golobalData(globalData), t_stageData(_stageData),
		c_sceneData(sceneData), m_posY(m_posY),m_rand(){}

	//初期化
	void Init();

	void LoadSync();

	//読込
	void LoadAnSync();

	void StepLoading();

	//更新
	void Step();

	//更新確定
	void Update();

	//
	void DrawLoading();

	//描画
	void Draw();

	//終了
	void Exit();

	void SelectCalc();

	void DrawDebug();
};