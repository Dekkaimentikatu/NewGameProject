#include "scene/scene_editer.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "lib/input_config.h"

C_SCENE_EDITER::~C_SCENE_EDITER()
{
	//追加で行う必要のある終了処理を書く
	//各メソッドでポインタの二重解放などへの安全対策をしておくこと
}

void C_SCENE_EDITER::Init()
{
	c_sceneData = C_SCENE_DATA::GetInstance();	//C_SCENE_DATAクラスのインスタンスを取得

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	c_mapEditer.Init();

	m_sky.Init();

	//カメラの初期化
	m_cam.Init();

	c_UIManager.Init();

	//ここよりも上に処理を書く

	//フェードインのリクエスト
	C_FADE::RequestFadeIn();

	//全ての処理を終えた後にステータスを更新
	m_sceneState = LOAD;
}

void C_SCENE_EDITER::LoadAnSync()
{
	//リソースの読み込み処理を書く
	c_mapEditer.LoadAnSync();
	c_UIManager.LoadAnSync();
}

void C_SCENE_EDITER::LoadSync()
{
	c_UIManager.LoadSync();
}

void C_SCENE_EDITER::LoadWait()
{
	//リソースの読み込み完了を待つ処理を書く
	c_UIManager.StepLoading();
}

void C_SCENE_EDITER::LoadEnd()
{
	//リソースの読み込み完了後の処理を書く
	c_mapEditer.LoadSync();

	m_cam.Load();

	m_sky.Load();

	//ここよりも上に処理を書く
}

void C_SCENE_EDITER::StartWait()
{
	C_FADE::RequestFadeIn();	//フェードインのリクエスト
	m_sceneState = STEP;
}

void C_SCENE_EDITER::Step()
{
	m_loadState = LOAD_OUT;

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	c_mapEditer.Step();

	m_sky.Step();

	m_cam.Step();

	m_sky.Update();

	m_cam.Update();
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

void C_SCENE_EDITER::EndWait()
{
	C_FADE::RequestFadeOut();	//フェードアウトのリクエスト

	m_sceneState = END;			//ステータスを更新
}

void C_SCENE_EDITER::Exit()
{
	c_mapEditer.Exit();

	m_sky.Exit();

	m_cam.Exit();
	//ここで各インスタンスの終了処理を行う

	c_UIManager.Exit();

	c_golobalData->ResetPlayerData();
}

void C_SCENE_EDITER::DrawLoading()
{
	c_UIManager.DrawLoading();
}

void C_SCENE_EDITER::DrawPlay()
{
	c_UIManager.Draw();

	m_sky.Draw();

	c_mapEditer.Draw();

	m_cam.Draw();
}