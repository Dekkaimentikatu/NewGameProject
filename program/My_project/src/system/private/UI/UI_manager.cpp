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


//初期化
void C_UI_MANAGER::Init()
{
	c_golobalData = C_GLOBAL_DATA::GetInstace();
	t_stageData = c_golobalData->GetStageData();
	c_sceneData = C_SCENE_DATA::GetInstance();

	C_UI_HPBER* tmp1 = nullptr;

	C_UI_STMBER* tmp2 = nullptr;

	C_STOP_EFFECT* tmp3 = nullptr;

	C_LOAD_ANIM* tmp4 = nullptr;

	C_TITLE_BACK* tmp5 = nullptr;

	C_BACK_GROUND* tmp6 = nullptr;

	C_RESULT* tmp7 = nullptr;

	C_RESPAWN_BACK* tmp8 = nullptr;

	C_SELECT_DISP* tmp9 = nullptr;

	switch (c_sceneData->GetSceneType())
	{
	case C_SCENE_DATA::SCENE_TYPE::TITLE:

		tmp4 = new C_LOAD_ANIM;
		tmp4->Init(VGet(1180.0f, 700.0f, 0.0f));
		c_UIObject.push_back(tmp4);

		tmp6 = new C_BACK_GROUND;
		tmp6->Init(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f));
		c_UIObject.push_back(tmp6);

		tmp5 = new C_TITLE_BACK;
		tmp5->Init(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f));
		c_UIObject.push_back(tmp5);

		break;

	case C_SCENE_DATA::SCENE_TYPE::SELECT:

		tmp4 = new C_LOAD_ANIM;
		tmp4->Init(VGet(1180.0f, 700.0f, 0.0f));
		c_UIObject.push_back(tmp4);

		tmp6 = new C_BACK_GROUND;
		tmp6->Init(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f));
		c_UIObject.push_back(tmp6);

		tmp9 = new C_SELECT_DISP;
		tmp9->Init(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f));
		c_UIObject.push_back(tmp9);

		break;

	case C_SCENE_DATA::SCENE_TYPE::PLAY:

		tmp3 = new C_STOP_EFFECT;

		tmp3->Init(VGet(static_cast<float>(WINDOW_CENTER_WIDTH),
			static_cast<float>(WINDOW_CENTER_HEIGHT), 0.0f));
		c_UIObject.push_back(tmp3);

		tmp1 = new C_UI_HPBER;
		tmp1->Init(VGet(60.0f, 32.0f, 0.0f));
		c_UIObject.push_back(tmp1);

		tmp2 = new C_UI_STMBER;
		tmp2->Init(VGet(128.0f, 128.0f, 0.0f));
		c_UIObject.push_back(tmp2);

		tmp4 = new C_LOAD_ANIM;
		tmp4->Init(VGet(1180.0f, 700.0f, 0.0f));
		c_UIObject.push_back(tmp4);

		tmp8 = new C_RESPAWN_BACK;
		tmp8->Init(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f));
		c_UIObject.push_back(tmp8);

		break;

	case C_SCENE_DATA::SCENE_TYPE::RESULT:

		tmp4 = new C_LOAD_ANIM;
		tmp4->Init(VGet(1180.0f, 700.0f, 0.0f));
		c_UIObject.push_back(tmp4);

		tmp6 = new C_BACK_GROUND;
		tmp6->Init(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f));
		c_UIObject.push_back(tmp6);

		tmp7 = new C_RESULT;
		tmp7->Init(VGet(WINDOW_CENTER_WIDTH, WINDOW_CENTER_HEIGHT, 0.0f));
		c_UIObject.push_back(tmp7);

		break;

	case C_SCENE_DATA::SCENE_TYPE::END:

		break;

	}

}

void C_UI_MANAGER::LoadSync()
{
	for (auto itr = c_UIObject.begin(); itr != c_UIObject.end(); ++itr)
	{
		(*itr)->LoadSync();
	}
}

//読込
void C_UI_MANAGER::LoadAnSync()
{
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