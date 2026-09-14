#include "scene/scene.h"

//このcppでは各シーンクラスのメンバメソッド内での書き方の見本を記述しています
//必要であればこのcppを参考にしてください

C_SCENE_BASE::~C_SCENE_BASE()
{
	//追加で行う必要のある終了処理を書く
	//各メソッドでポインタの二重解放などへの安全対策をしておくこと
}

void C_SCENE_BASE::Init()
{
	c_sceneData = C_SCENE_DATA::GetInstance();	//C_SCENE_DATAクラスのインスタンスを取得

	c_sceneData->SetIsEnd(false);	//終了確認フラグを折る

	//ここよりも下に処理を書く

	//ここよりも上に処理を書く
	//全ての処理を終えた後にステータスを更新

	C_FADE::RequestFadeIn();	//フェードインのリクエスト

	m_sceneState = LOAD;

	m_loadState = LOAD_START;	//ロードステートを初期化
}

void C_SCENE_BASE::Load()
{
	switch (m_loadState)
	{
	case C_SCENE_BASE::LOAD_START:
		SetUseASyncLoadFlag(TRUE);
		LoadAnSync();
		SetUseASyncLoadFlag(FALSE);
		LoadSync();
		m_loadState = LOADING;
		break;
	case C_SCENE_BASE::LOADING:
		m_loadCount++;	//ロードカウントを加算
		//非同期読み込みが全て終わったらステートを更新
		if (GetASyncLoadNum() == 0 && m_loadCount >= LOAD_COUNT_MAX)
		{
			C_FADE::RequestFadeOut();	//フェードアウトのリクエスト
			m_loadState = LOAD_END;
		}
		else LoadWait();
		break;
	case C_SCENE_BASE::LOAD_END:
		if (C_FADE::IsEndFadeOut())
		{
			LoadEnd();
			m_sceneState = STARTWAIT;
		}
		break;
	}
}

void C_SCENE_BASE::LoadAnSync()
{
	//リソースの読み込み処理を書く
}

void C_SCENE_BASE::LoadSync()
{

}

void C_SCENE_BASE::LoadWait()
{
	//リソースの読み込み完了を待つ処理を書く
}

void C_SCENE_BASE::LoadEnd()
{
	//リソースの読み込み完了後の処理を書く
}

void C_SCENE_BASE::StartWait()
{
	C_FADE::RequestFadeIn();	//フェードインのリクエスト
	m_sceneState = STEP;
}

void C_SCENE_BASE::Step()
{
	if (!C_FADE::IsEndFadeIn())return;	//フェードインが終わっていなければ抜ける
	else m_loadState = LOAD_OUT;
	//ここよりも下に処理を書く

	//ここよりも上に処理を書く

	//遷移テスト用の処理
	if (C_INPUT::IsInputTrg(KEY_INPUT_Z))
	{
		c_sceneData->SetSceneType(C_SCENE_DATA::TITLE);	//次に遷移したいシーンのタイプを代入

		m_sceneState = ENDWAIT;		//ステータスを更新
	}
}

void C_SCENE_BASE::EndWait()
{
	C_FADE::RequestFadeOut();	//フェードインのリクエスト

	m_sceneState = END;			//ステータスを更新
}

void C_SCENE_BASE::Exit()
{
	//ここで各インスタンスの終了処理を行う
}

void C_SCENE_BASE::End()
{
	//終了処理はif文の中に書く
	//フェードアウトの終了を確認して終了処理を開始
	if (C_FADE::IsEndFadeOut())
	{
		Exit(); //終了実行処理
		c_sceneData->SetIsEnd(true);	//終了確認フラグを立てる
	}
}

void C_SCENE_BASE::Loop()
{
	// 修正: メンバ関数ポインタを使用するために、this ポインタを利用して呼び出すように変更
	void (C_SCENE_BASE:: * stateFunc[])() = {
		&C_SCENE_BASE::Init,
		&C_SCENE_BASE::Load,
		&C_SCENE_BASE::StartWait,
		&C_SCENE_BASE::Step,
		&C_SCENE_BASE::EndWait,
		&C_SCENE_BASE::End
	};

	(this->*stateFunc[m_sceneState])();
}

void C_SCENE_BASE::DrawLoading()
{

}

void C_SCENE_BASE::DrawPlay()
{

}

void C_SCENE_BASE::Draw()
{
	switch (m_loadState)
	{
	case C_SCENE_BASE::LOADING:
		DrawLoading();
		break;
	case C_SCENE_BASE::LOAD_OUT:
		DrawPlay();
		break;
	}
}