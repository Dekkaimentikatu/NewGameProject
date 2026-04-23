#include "UI/UI_manager.h"
#include "game/UI/UI_hpber.h"
#include "game/UI/UI_stmber.h"
#include "game/UI/stop_effect.h"
#include "game/UI/load_anim.h"
#include "game/UI/title_back.h"
#include "game/UI/back_ground.h"
#include "game/UI/result.h"
#include "game/UI/respawn_back.h"
#include "game/UI/select_disp.h"

#include "lib/2Dhndlmanager.h"


//初期化
void C_UI_MANAGER::Init()
{
	c_golobalData = C_GLOBAL_DATA::GetInstace();
	t_stageData = c_golobalData->GetStageData();
	c_sceneData = C_SCENE_DATA::GetInstance();

	C_UI_OBJECT_BASE* tmp = nullptr;

	switch (c_sceneData->GetSceneType())
	{
	case C_SCENE_DATA::SCENE_TYPE::TITLE:


		Request(VGet(1180.0f, 700.0f, 0.0f), new C_LOAD_ANIM);

		Request(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f), new C_BACK_GROUND);

		Request(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f), new C_TITLE_BACK);

		break;

	case C_SCENE_DATA::SCENE_TYPE::SELECT:

		Request(VGet(1180.0f, 700.0f, 0.0f), new C_LOAD_ANIM);

		Request(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f), new C_BACK_GROUND);

		Request(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f), tmp = new C_SELECT_DISP);

		break;

	case C_SCENE_DATA::SCENE_TYPE::PLAY:

		Request(VGet(static_cast<float>(WINDOW_CENTER_WIDTH),
			static_cast<float>(WINDOW_CENTER_HEIGHT), 0.0f), new C_STOP_EFFECT);

		Request(VGet(60.0f, 32.0f, 0.0f), new C_UI_HPBER);

		Request(VGet(128.0f, 128.0f, 0.0f), new C_UI_STMBER);

		Request(VGet(1180.0f, 700.0f, 0.0f), new C_LOAD_ANIM);

		Request(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f), new C_RESPAWN_BACK);

		break;

	case C_SCENE_DATA::SCENE_TYPE::RESULT:

		Request(VGet(1180.0f, 700.0f, 0.0f), new C_LOAD_ANIM);

		Request(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f), new C_BACK_GROUND);

		Request(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f), new C_RESULT);

		break;

	case C_SCENE_DATA::SCENE_TYPE::END:

		break;

	}

}

void C_UI_MANAGER::Request(VECTOR _pos, C_UI_OBJECT_BASE* _object)
{
	C_UI_OBJECT_BASE* tmp = nullptr;
	tmp = _object;
	tmp->Init(_pos);
	c_UIObject.push_back(tmp);
}

void C_UI_MANAGER::LoadSync()
{
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	inctanse->Load2DImage(LOAD_GRAPH_PATH, LOAD_GRAPH_MAX, LOAD_GRAPH_X_NUM, LOAD_GRAPH_Y_NUM, LOAD_GRAPH_SIZE, LOAD_GRAPH_SIZE);

	for (auto itr = c_UIObject.begin(); itr != c_UIObject.end(); ++itr)
	{
		(*itr)->LoadSync();
	}
}

//読込
void C_UI_MANAGER::LoadAnSync()
{
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	inctanse->Load2DImage(STM_GRAPH_PATH[0]);
	inctanse->Load2DImage(STM_GRAPH_PATH[1]);
	inctanse->Load2DImage(HP_GRAPH_PATH[0]);
	inctanse->Load2DImage(HP_GRAPH_PATH[1]);
	inctanse->Load2DImage(TITLE_BACK_GRAPH_PATH);
	inctanse->Load2DImage(STOP_GRAPH_PATH);
	inctanse->Load2DImage(DISP_GRAPH_PATH[0]);
	inctanse->Load2DImage(DISP_GRAPH_PATH[1]);
	inctanse->Load2DImage(DISP_GRAPH_PATH[2]);
	inctanse->Load2DImage(RESULT_GRAPH_PATH);
	inctanse->Load2DImage(RESPAWN_GRAPH_PATH);
	inctanse->Load2DImage(BACK_GROUND_GRAPH_PATH);

	for (auto itr = c_UIObject.begin(); itr != c_UIObject.end(); ++itr)
	{
		(*itr)->LoadAnSync();
	}
}

void C_UI_MANAGER::StepLoading()
{
	for (auto itr = c_UIObject.begin(); itr != c_UIObject.end(); ++itr)
	{
		(*itr)->StepLoading();
	}
}

void C_UI_MANAGER::Step()
{
	for (auto itr = c_UIObject.begin(); itr != c_UIObject.end(); ++itr)
	{
		(*itr)->Step();
	}
}

//更新確定
void C_UI_MANAGER::Update()
{
	for (auto itr = c_UIObject.begin(); itr != c_UIObject.end(); ++itr)
	{
		(*itr)->Update();
	}
}

void C_UI_MANAGER::DrawLoading()
{
	for (auto itr = c_UIObject.begin(); itr != c_UIObject.end(); ++itr)
	{
		(*itr)->DrawLoading();
	}
}

//描画
void C_UI_MANAGER::Draw()
{
	for (auto itr = c_UIObject.begin(); itr != c_UIObject.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

//終了
void C_UI_MANAGER::Exit()
{
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	inctanse->Delete2DData(STM_GRAPH_PATH[0]);
	inctanse->Delete2DData(STM_GRAPH_PATH[1]);
	inctanse->Delete2DData(HP_GRAPH_PATH[0]);
	inctanse->Delete2DData(HP_GRAPH_PATH[1]);
	inctanse->Delete2DData(TITLE_BACK_GRAPH_PATH);
	inctanse->Delete2DData(STOP_GRAPH_PATH);
	inctanse->Delete2DData(DISP_GRAPH_PATH[0]);
	inctanse->Delete2DData(DISP_GRAPH_PATH[1]);
	inctanse->Delete2DData(DISP_GRAPH_PATH[2]);
	inctanse->Delete2DData(RESULT_GRAPH_PATH);
	inctanse->Delete2DData(RESPAWN_GRAPH_PATH);
	inctanse->Delete2DData(BACK_GROUND_GRAPH_PATH);

	for (auto itr = c_UIObject.begin(); itr != c_UIObject.end(); ++itr)
	{
		(*itr)->Exit();
		delete (*itr);
	}
}

void C_UI_MANAGER::SelectCalc()
{

}

void C_UI_MANAGER::DrawDebug()
{
	switch (c_sceneData->GetSceneType())
	{
	case C_SCENE_DATA::SCENE_TYPE::TITLE:

		break;

	case C_SCENE_DATA::SCENE_TYPE::SELECT:

		break;

	case C_SCENE_DATA::SCENE_TYPE::PLAY:

		break;

	case C_SCENE_DATA::SCENE_TYPE::RESULT:

		break;

	case C_SCENE_DATA::SCENE_TYPE::END:

		break;

	}

}