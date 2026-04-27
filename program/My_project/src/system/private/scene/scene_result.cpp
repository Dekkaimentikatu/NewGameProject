#include "scene/scene_result.h"
#include "lib/bgm_manager.h"
#include "lib/input_config.h"

C_SCENE_RESULT::~C_SCENE_RESULT()
{
	//追加で行う必要のある終了処理を書く
	//各メソッドでポインタの二重解放などへの安全対策をしておくこと
}

void C_SCENE_RESULT::Init()
{
	c_sceneData = C_SCENE_DATA::GetInstance();	//C_SCENE_DATAクラスのインスタンスを取得

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	c_UIManager.Init();

	//ここよりも上に処理を書く

	//フェードインのリクエスト
	C_FADE::RequestFadeIn();

	//全ての処理を終えた後にステータスを更新
	m_sceneState = LOAD;
}

void C_SCENE_RESULT::LoadAnSync()
{
	c_UIManager.LoadAnSync();
}

void C_SCENE_RESULT::LoadSync()
{
	c_UIManager.LoadSync();
}

void C_SCENE_RESULT::LoadWait()
{
	//リソースの読み込み完了を待つ処理を書く
	c_UIManager.StepLoading();
}

void C_SCENE_RESULT::LoadEnd()
{
	//リソースの読み込み完了後の処理を書く

#ifndef DEBUG_MODE

	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();

	bgmMgr->Play(C_BGM_MANAGER::BGMID_RESULT, DX_PLAYTYPE_LOOP);

#endif
}

void C_SCENE_RESULT::StartWait()
{

	C_FADE::RequestFadeIn();	//フェードインのリクエスト
	m_sceneState = STEP;

}

void C_SCENE_RESULT::Step()
{
	m_loadState = LOAD_OUT;


	//ここよりも上に処理を書く

	//シーン遷移処理
	if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::DECISION))
	{
		c_sceneData->SetSceneType(C_SCENE_DATA::END);	//次に遷移したいシーンのタイプを代入

		m_sceneState = ENDWAIT;		//ステータスを更新
	}

	if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::CANCEL))
	{
		c_sceneData->SetSceneType(C_SCENE_DATA::TITLE);	//次に遷移したいシーンのタイプを代入

		m_sceneState = ENDWAIT;		//ステータスを更新
	}
}

void C_SCENE_RESULT::EndWait()
{
	C_FADE::RequestFadeOut();	//フェードアウトのリクエスト

	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();

	bgmMgr->Stop(C_BGM_MANAGER::BGMID_RESULT);

	m_sceneState = END;			//ステータスを更新
}

void C_SCENE_RESULT::Exit()
{
	//ここで各インスタンスの終了処理を行う

	c_UIManager.Exit();

	c_golobalData->ResetPlayerData();
}

void C_SCENE_RESULT::DrawLoading()
{
	c_UIManager.DrawLoading();
}

void C_SCENE_RESULT::DrawPlay()
{
	c_UIManager.Draw();
	//ここで描画処理を行う
}