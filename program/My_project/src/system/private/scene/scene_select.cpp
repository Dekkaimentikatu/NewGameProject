#include "scene/scene_select.h"
#include "lib/bgm_manager.h"
#include "lib/input_config.h"

C_SCENE_SELECT::~C_SCENE_SELECT()
{
	//追加で行う必要のある終了処理を書く
	//各メソッドでポインタの二重解放などへの安全対策をしておくこと
}

void C_SCENE_SELECT::Init()
{
	c_sceneData = C_SCENE_DATA::GetInstance();	//C_SCENE_DATAクラスのインスタンスを取得

	c_UIManager.Init();

	//ここよりも上に処理を書く

	//フェードインのリクエスト
	C_FADE::RequestFadeIn();

	//全ての処理を終えた後にステータスを更新
	m_sceneState = LOAD;
}

void C_SCENE_SELECT::LoadAnSync()
{
	c_UIManager.LoadAnSync();
}

void C_SCENE_SELECT::LoadSync()
{
	c_UIManager.LoadSync();
}

void C_SCENE_SELECT::LoadWait()
{
	//リソースの読み込み完了を待つ処理を書く
	c_UIManager.StepLoading();
}

void C_SCENE_SELECT::LoadEnd()
{
	//リソースの読み込み完了後の処理を書く

#ifndef DEBUG_MODE

	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();

	bgmMgr->Play(C_BGM_MANAGER::BGMID_SELECT , DX_PLAYTYPE_LOOP);

#endif
}

void C_SCENE_SELECT::StartWait()
{
	C_FADE::RequestFadeIn();	//フェードインのリクエスト
	m_sceneState = STEP;
}

void C_SCENE_SELECT::Step()
{
	m_loadState = LOAD_OUT;

	//ここよりも上に処理を書く

	c_UIManager.Step();

	//シーン遷移処理
	if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::DECISION))
	{
		c_sceneData->SetSceneType(C_SCENE_DATA::PLAY);	//次に遷移したいシーンのタイプを代入

		m_sceneState = ENDWAIT;		//ステータスを更新
	}

	if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::CANCEL))
	{
		c_sceneData->SetSceneType(C_SCENE_DATA::RESULT);	//次に遷移したいシーンのタイプを代入

		m_sceneState = ENDWAIT;		//ステータスを更新
	}
}

void C_SCENE_SELECT::Exit()
{
	//ここで各インスタンスの終了処理を行う

	c_UIManager.Exit();
}

void C_SCENE_SELECT::EndWait()
{
	C_FADE::RequestFadeOut();	//フェードアウトのリクエスト

	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();

	bgmMgr->Stop(C_BGM_MANAGER::BGMID_SELECT);

	m_sceneState = END;			//ステータスを更新
}

void C_SCENE_SELECT::DrawLoading()
{
	c_UIManager.DrawLoading();
}

void C_SCENE_SELECT::DrawPlay()
{
	c_UIManager.Draw();
	//ここで描画処理を行う
}