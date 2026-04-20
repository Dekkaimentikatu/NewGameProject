#include "scene/scene_play.h"
#include "game/data/global_data.h"
#include "lib/bgm_manager.h"

C_SCENE_PLAY::~C_SCENE_PLAY()
{
	//追加で行う必要のある終了処理を書く
	//各メソッドでポインタの二重解放などへの安全対策をしておくこと
}

void C_SCENE_PLAY::Init()
{
	c_sceneData = C_SCENE_DATA::GetInstance();	//C_SCENE_DATAクラスのインスタンスを取得

	c_playerManager.Init();

	c_enemyManager.Init();

	c_mapManager.Init();

	c_UIManager.Init();

	m_playState = START;

	//ここよりも上に処理を書く 

	//フェードインのリクエスト
	C_FADE::RequestFadeIn();

	//全ての処理を終えた後にステータスを更新
	m_sceneState = LOAD;
}

void C_SCENE_PLAY::LoadAnSync()
{
	//リソースの読み込み処理を書く
	c_mapManager.LoadAnSync();
	c_playerManager.LoadAnSync();
	c_enemyManager.LoadAnSync();
	c_UIManager.LoadAnSync();
}

void C_SCENE_PLAY::LoadSync()
{
	c_UIManager.LoadSync();
}

void C_SCENE_PLAY::LoadWait()
{
	//リソースの読み込み完了を待つ処理を書く
	c_UIManager.StepLoading();
}

void C_SCENE_PLAY::LoadEnd()
{
	//リソースの読み込み完了後の処理を書く
	c_mapManager.LoadSync();
	c_playerManager.LoadSync();
	c_enemyManager.LoadSync();

#ifndef DEBUG_MODE

	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();

	bgmMgr->Play(C_BGM_MANAGER::BGMID_GAME, DX_PLAYTYPE_LOOP);

#endif

	//ここよりも上に処理を書く

}

void C_SCENE_PLAY::StartWait()
{
	c_cameraManager.Init();
	c_cameraManager.SetNearFar(0.25f, 3000.0f);

	C_FADE::RequestFadeIn();	//フェードインのリクエスト
	m_sceneState = STEP;

}

void C_SCENE_PLAY::Step()
{
	m_loadState = LOAD_OUT;

	C_GLOBAL_DATA* tmp = C_GLOBAL_DATA::GetInstace();

	switch (m_playState)
	{
	case C_SCENE_PLAY::START:

		if (!C_FADE::IsEndFadeIn())return;	//フェードインが終わっていなければ抜ける

		if (c_cameraManager.GetPlayerCamEventState() == C_PALYER_CAMERA_VEC::CAM_EVENT_PLAYWAIT)
		{
			C_FADE::RequestFadeOut();
			m_playState = PLAYWAIT;
		}
		break;

	case C_SCENE_PLAY::PLAYWAIT:

		if (C_FADE::IsEndFadeOut())
		{
			C_FADE::RequestFadeIn();
			c_cameraManager.GetPlayerCamera()->SetEventState(C_PALYER_CAMERA_VEC::CAM_EVENT_PLAY);
			m_playState = PLAY;
		}
		break;

	case C_SCENE_PLAY::PLAY:

		//プレイヤー更新
		c_playerManager.Step(c_cameraManager.GetPlayerCamera()->GetCameraRot());

		//エネミー更新
		c_enemyManager.Step();

		//マップ更新
		c_mapManager.Step();

		if (tmp->GetPlayerData()->isRespawn)
		{
			m_playState = RESPAWN;
		}

		if (tmp->GetPlayerData()->isGoal)
		{
			m_playState = GOAL;
			c_cameraManager.GetPlayerCamera()->SetEventState(C_PALYER_CAMERA_VEC::CAM_EVENT_GOAL);
		}

		break;
	case C_SCENE_PLAY::RESPAWN:

		if (!C_FADE::IsEndFadeIn())return;	//フェードインが終わっていなければ抜ける
		else
		{
			m_playState = PLAY;
			c_cameraManager.Respawn(VAdd(DEFAULT_EYE_POS, c_playerManager.GetPlayerInstance()->GetTargetPos()),
				c_playerManager.GetPlayerInstance()->GetCenter(),
				DEFAULT_UP_VEC);
		}

		break;
	case C_SCENE_PLAY::GOAL:

		if (c_cameraManager.GetPlayerCamEventState() == C_PALYER_CAMERA_VEC::CAM_EVENT_NUM)
		{
			c_sceneData->SetSceneType(C_SCENE_DATA::SELECT);	//次に遷移したいシーンのタイプを代入

			m_sceneState = ENDWAIT;		//ステータスを更新

			C_FADE::RequestFadeOut();	//フェードアウトのリクエスト
		}

		break;
	case C_SCENE_PLAY::FADE:

		break;
	}

	c_UIManager.Step();

	CEffekseerCtrl::SetAutoProjectionMtx();

	C_COLLISION_MANAGER::CollisionCalc();

	//当たり判定を行った後に更新確定処理を行う
	CEffekseerCtrl::UpdateAutoCamera();

	c_playerManager.Update();

	c_enemyManager.Update();

	c_mapManager.Update();

	c_cameraManager.Step(c_playerManager.GetPlayerInstance()->GetTargetPos(),
		c_playerManager.GetPlayerInstance()->GetCenter(),
		c_playerManager.GetPlayerInstance()->GetRot().y,
		DX_INPUT_PAD1);

	c_cameraManager.Update();

	//ここよりも上に処理を書く

	//遷移テスト用の処理
	if (C_INPUT::IsInputTrg(KEY_INPUT_Z))
	{
		c_sceneData->SetSceneType(C_SCENE_DATA::SELECT);	//次に遷移したいシーンのタイプを代入

		m_sceneState = ENDWAIT;		//ステータスを更新
	}

	//ステージクリア
	if (tmp->GetPlayerData()->isGoal)
	{

	}
}

void C_SCENE_PLAY::EndWait()
{
	C_BGM_MANAGER* bgmMgr = C_BGM_MANAGER::GetInstance();
	bgmMgr->Stop(C_BGM_MANAGER::BGMID_GAME);	//BGM停止

	m_sceneState = END;			//ステータスを更新
}

void C_SCENE_PLAY::Exit()
{
	c_playerManager.Exit();	//3Dモデルのアンロード

	c_enemyManager.Exit();

	c_UIManager.Exit();

	c_mapManager.Exit();

	c_cameraManager.Exit();

	C_COLLISION_MANAGER::Exit();

	//ここで各インスタンスの終了処理を行う
}

void C_SCENE_PLAY::DrawLoading()
{
	c_UIManager.DrawLoading();
}

void C_SCENE_PLAY::DrawPlay()
{
	c_enemyManager.Draw();

	c_mapManager.Draw();

	switch (m_playState)
	{
	case C_SCENE_PLAY::PLAY:
	case C_SCENE_PLAY::RESPAWN:
	case C_SCENE_PLAY::GOAL:
		c_playerManager.Draw();
		c_UIManager.Draw();
		break;
	}



	//c_UIManager.DrawDebug();

	//c_playerManager.DebugDraw();

	CEffekseerCtrl::Draw();
	//ここで描画処理を行う
}