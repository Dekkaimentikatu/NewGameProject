#include "scene/scene_manager.h"
#include "lib/input_config.h"

#include "lib/fade.h"
#include "lib/fps.h"
#include "lib/input.h"
#include "lib/xinput.h"

#include "lib/bgm_manager.h"
#include "lib/se_manager.h"

#include "scene/scene_factory.h"

#include "game/data/global_data.h"
#include "effekseer/effekseer.h"

#include "lib/3Dhndlmanager.h"
#include "lib/2Dhndlmanager.h"

void C_SCENE_MANAGER::Init()
{
	c_sceneData = C_SCENE_DATA::GetInstance();		//シーン間データ共有クラスのインスタンスを格納

	c_sceneData->Init();							//シーン間データ共有クラスの各変数を初期化

	m_pravSceneType = c_sceneData->GetSceneType();	//前回のシーンのタイプを現在のシーンのタイプに更新

	c_scene = C_SCENE_FACTORY::Create(c_sceneData->GetSceneType());	//次のシーンクラスインスタンスの生成

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();
	C_SE_MANAGER* seMgr = C_SE_MANAGER::GetInstance();

	//ここより下に初期化処理を書く

	C_FADE::Init();			//フェードイン/フェードアウト管理クラスの初期化

	C_INPUT_CONFIG::Init();

	C_FPS::Init();			//FPS管理クラスの初期化

	c_golobalData->Init();

	CEffekseerCtrl::Init(1000, 20000);
}

void C_SCENE_MANAGER::Load()
{
	//ここに読込処理を書く
	CEffekseerCtrl::LoadData("data/effect/Blow.efk");


	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();
	C_SE_MANAGER* seMgr = C_SE_MANAGER::GetInstance();

	bgmMgr->Load();
	seMgr->Load();
}

void C_SCENE_MANAGER::Step()
{
	//ここに大域で呼び出すクラスの更新処理を行う

	//フェードイン/フェードアウトの更新
	C_FADE::Update();

	C_INPUT_CONFIG::Updata();

	CEffekseerCtrl::UpdateAutoCamera();
}

void C_SCENE_MANAGER::Loop()
{
	//if (c_scene->GetSceneState() == C_SCENE_BASE::STEP && c_sceneData->GetIsWait())return;

	//ここには基本的に各シーンのループ処理を行う
	c_scene->Loop();

	//例外的な処理

	//FPS管理クラスの待機処理
	C_FPS::Wait();
}

void C_SCENE_MANAGER::Draw()
{
	//ここには基本的に各シーンの描画処理を行う
	if(c_scene->GetSceneState() != C_SCENE_BASE::END)c_scene->Draw();

	//例外的に行う処理

	//フェードイン/フェードアウトの描画
	C_FADE::Draw();

	//FPS管理クラスの描画
	C_FPS::Disp();

	CEffekseerCtrl::Draw();
}

void C_SCENE_MANAGER::Exit()
{
	//ここよりも上に終了処理を書く
	if (c_scene != nullptr)
	{
		c_scene->Exit();
		delete c_scene;			//念のためインスタンスの削除をしておく
		c_scene = nullptr;		//ポインタの初期化
	}

	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();
	C_SE_MANAGER* seMgr = C_SE_MANAGER::GetInstance();
	C_2D_HNDL_MANAGER* hndl2dMgr = C_2D_HNDL_MANAGER::GetInstance();
	C_3D_HNDL_MANAGER* hndl3dMgr = C_3D_HNDL_MANAGER::GetInstance();

	bgmMgr->Exit();
	seMgr->Exit();
	hndl2dMgr->DeleteAll2DData();
	hndl3dMgr->DeleteAll3DModel();

	bgmMgr->DeleteInstance();
	seMgr->DeleteInstance();
	hndl2dMgr->DeleteInstance();
	hndl3dMgr->DeleteInstance();

	c_sceneData->DeleteInstance();			//シーン間データ共有クラスのインスタンスを削除

	c_golobalData->DeleteInstance();

	CEffekseerCtrl::Exit();
}

bool C_SCENE_MANAGER::SceneNowPravTypeCmp()
{
	//前回と現在のシーンのタイプを比べる
	return m_pravSceneType == c_sceneData->GetSceneType() ? true : false;
}

bool C_SCENE_MANAGER::IsSceneTypeEND()
{
	//前回のシーンのタイプがENDであるかどうかを判定
	return m_pravSceneType == C_SCENE_DATA::SCENE_TYPE::END ? true : false;
}

void C_SCENE_MANAGER::Next()
{
	if (!c_sceneData->GetIsEnd())return;	//終了フラグが折れているなら処理を行わない

	if (c_scene != nullptr)delete c_scene;	//前回のシーンクラスのインスタンスの削除
	c_scene = nullptr;				//ポインタの初期化

	c_scene = C_SCENE_FACTORY::Create(c_sceneData->GetSceneType());	//次のシーンクラスインスタンスの生成

	CEffekseerCtrl::Exit();

	CEffekseerCtrl::Init(10000, 20000);

	m_pravSceneType = c_sceneData->GetSceneType();	//前回のシーンのタイプを現在のシーンのタイプに更新
	c_sceneData->SetIsEnd(false);

	c_golobalData->ResetPlayerData();
}