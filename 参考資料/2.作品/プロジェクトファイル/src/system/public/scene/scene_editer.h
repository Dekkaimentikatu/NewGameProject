#pragma once

#include "scene/scene.h"
#include "mapediter/mapediter.h"
#include "mapediter/editer_camera_point.h"
#include "game/object/static/sky.h"

class C_SCENE_EDITER : public C_SCENE_BASE
{
private:

	C_MAP_EDITER c_mapEditer;	//マップエディタ

	C_EDITER_CAMERA_POINT m_cam;

	C_SKY m_sky;

private:

	void Init();		//初期化処理

	void LoadAnSync();	//リソース読込処理

	void LoadSync();

	void LoadWait();	//読込待機処理

	void LoadEnd();		//読込完了処理

	void StartWait();	//更新前待機処理

	void Step();		//更新処理

	void DrawLoading();

	void DrawPlay();

	void EndWait();		//終了前待機処理

public:

	~C_SCENE_EDITER() override;	//デストラクタ

	void Exit();
};