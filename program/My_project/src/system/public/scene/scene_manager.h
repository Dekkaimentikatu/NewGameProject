#pragma once

#include <memory>

#include "scene.h"
#include "scene_data.h"

using namespace std;

class C_SCENE_MANAGER
{
private:

	C_SCENE_DATA::SCENE_TYPE m_pravSceneType;	//前回のシーンのタイプ

	C_SCENE_DATA* c_sceneData;					//シーン間データ共有クラスのインスタンス格納用ポインタ変数

	C_SCENE_BASE* c_scene;						//各シーンのインスタンス格納用ポインタ変数

	C_GLOBAL_DATA* c_golobalData;				//大域データ管理クラス

	bool SceneNowPravTypeCmp();					//現在と前回のシーンのタイプを比べる

protected:

	C_DRAW_GRAPH* c_drawGraph;

public:

	void Init();			//初期化

	void Load();			//読込処理

	void Step();			//更新処理

	void Loop();			//ループ処理

	void Draw();			//描画処理
	
	void Exit();			//終了処理

	void Next();			//シーン遷移処理

	bool IsSceneTypeEND();	//前回のシーンのタイプがENDであるかどうかを判定
	
};
