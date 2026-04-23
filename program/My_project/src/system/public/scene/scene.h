#pragma once

#include <DxLib.h>				//DxLib
#include "scene_data.h"
#include "lib/fade.h"		//フェードイン/フェードアウト管理クラス
#include "lib/input.h"	//入力管理クラス
#include "lib/xinput.h"
#include "UI/UI_manager.h"
#include "game/data/global_data.h"

constexpr int LOAD_COUNT_MAX = 120;	//読込カウンタの最大値

class C_SCENE_BASE
{
public:

	enum SCENE_STATE			//シーンのステータス
	{
		INIT,				//初期化
		LOAD,				//読込
		STARTWAIT,			//更新前待機
		STEP,				//更新
		ENDWAIT,			//終了前待機
		END,				//終了

		SCENE_STATE_NUM,	//ステータスの総数
	};

	enum LOAD_STATE		//読込ステータス
	{
		LOAD_START,		//読込開始
		LOADING,		//読込中
		LOAD_END,		//読込完了
		LOAD_OUT,		//読込ではない
		LOAD_STATE_NUM,	//読込ステータスの総数
	};

protected:

	int m_loadCount;		//読込カウンタ

	SCENE_STATE m_sceneState;	//シーンのステータス管理用の変数

	C_SCENE_DATA* c_sceneData;	//シーン間データ共有用クラスのインスタンス格納用ポインタ変数

	C_GLOBAL_DATA* c_golobalData;

	C_UI_MANAGER c_UIManager;

	LOAD_STATE m_loadState;	//読込ステータス管理用の変数



	virtual void Init();		//初期化処理

	void Load();		//読込処理

	virtual void LoadAnSync();	//リソース読込処理

	virtual void LoadSync();

	virtual void LoadWait();	//読込待機処理

	virtual void LoadEnd();		//読込完了処理

	virtual void StartWait();	//更新前待機処理

	virtual void Step();		//更新処理

	virtual void DrawLoading();

	virtual void DrawPlay();

	virtual void EndWait();		//終了前待機処理

	void End();			//終了処理

public:

	//コンストラクタ
	C_SCENE_BASE(int _loadCount = 0, SCENE_STATE _sceneState = INIT, C_SCENE_DATA* _sceneData = nullptr, 
		C_GLOBAL_DATA* _golobalData = nullptr, LOAD_STATE _loadState = LOAD_START):
		m_loadCount(_loadCount), m_sceneState(_sceneState), c_sceneData(_sceneData), c_golobalData(_golobalData),
		m_loadState(_loadState){}

	virtual ~C_SCENE_BASE();	//デストラクタ

	void Loop();				//ループ処理

	void Draw();		//描画処理

	virtual void Exit();		//終了実行処理

	SCENE_STATE GetSceneState() { return m_sceneState; };

};

