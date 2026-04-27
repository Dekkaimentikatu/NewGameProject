#include "scene/scene_title.h"
#include "lib/bgm_manager.h"
#include "lib/input_config.h"

C_SCENE_TITLE::~C_SCENE_TITLE()
{
	//追加で行う必要のある終了処理を書く
	//各メソッドでポインタの二重解放などへの安全対策をしておくこと
}

void C_SCENE_TITLE::Init()
{
	c_sceneData = C_SCENE_DATA::GetInstance();	//C_SCENE_DATAクラスのインスタンスを取得

	c_UIManager.Init();

	//ここよりも上に処理を書く

	//フェードインのリクエスト
	C_FADE::RequestFadeIn();

	//全ての処理を終えた後にステータスを更新
	m_sceneState = LOAD;
}

void C_SCENE_TITLE::LoadAnSync()
{
	c_UIManager.LoadAnSync();
}

void C_SCENE_TITLE::LoadSync()
{
	c_UIManager.LoadSync();
}

void C_SCENE_TITLE::LoadWait()
{
	//リソースの読み込み完了を待つ処理を書く
	c_UIManager.StepLoading();
}

void C_SCENE_TITLE::LoadEnd()
{
	//リソースの読み込み完了後の処理を書く

#ifndef DEBUG_MODE

	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();

	bgmMgr->Play(C_BGM_MANAGER::BGMID_TITLE, DX_PLAYTYPE_LOOP);

#endif
}

void C_SCENE_TITLE::StartWait()
{
	C_FADE::RequestFadeIn();	//フェードインのリクエスト
	m_sceneState = STEP;
}

void C_SCENE_TITLE::Step()
{
	m_loadState = LOAD_OUT;

	//ここよりも上に処理を書く

	//シーン遷移処理
	if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::DECISION))
	{
		c_sceneData->SetSceneType(C_SCENE_DATA::SELECT);	//次に遷移したいシーンのタイプを代入

		m_sceneState = ENDWAIT;		//ステータスを更新
	}

#ifdef DEBUG_MODE

	if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::CANCEL))
	{
		c_sceneData->SetSceneType(C_SCENE_DATA::EDITER);	//次に遷移したいシーンのタイプを代入

		m_sceneState = ENDWAIT;		//ステータスを更新
	}

#endif // DEBUG_MODE
}

void C_SCENE_TITLE::EndWait()
{
	C_FADE::RequestFadeOut();	//フェードアウトのリクエスト

	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();

	bgmMgr->Stop(C_BGM_MANAGER::BGMID_TITLE);

	m_sceneState = END;			//ステータスを更新
}

void C_SCENE_TITLE::Exit()
{
	//ここで各インスタンスの終了処理を行う

	c_UIManager.Exit();
}

void C_SCENE_TITLE::DrawLoading()
{
	c_UIManager.DrawLoading();
}

void C_SCENE_TITLE::DrawPlay()
{
	c_UIManager.Draw();
}