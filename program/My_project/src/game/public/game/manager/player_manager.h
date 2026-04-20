#pragma once

# include<algorithm>

#include "game/base/manager_base.h"
#include "game/actor/player/player.h"
#include "game/camera/camera_manager.h"

class C_PLAYER_MANAGER : public C_ACOTR_MANAGER_BASE
{
private:

	C_CAMERA_MANAGER_ c_cameraManager;	//カメラマネージャー

	vector<C_ACTOR_BASE*> m_targetPosList;	//ターゲットの位置リスト

	float m_debugRot;

	int m_targetPosListIndex;

	int m_modelHndl;	//モデルハンドル

	int m_isInput;

public:

	C_PLAYER_MANAGER(float _debugRot = 0.0f, int _targetPosListIndex = 0,
		int _modelHndl = 0, int _isInput = 0x0000) :
		m_debugRot(_debugRot), m_targetPosListIndex(_targetPosListIndex),
		m_modelHndl(_modelHndl), m_isInput(_isInput){
	}

	void Init();	//初期化

	void LoadAnSync();	//リソース読込

	void LoadSync();	//読込

	void Step();	//更新

	void Step(VECTOR _camRota);

	void Update();	//更新確定

	void Draw();	//描画

	void DebugDraw();	//デバッグ描画

	void Exit();	//終了

	void HitCalc();	//当たり判定処理

	void ReflectCollision(VECTOR addVec);

	C_ACTOR_BASE* GetPlayerInstance(int _index = 0) 
	{
		auto itr = c_actorArray.begin();
		return (*itr);
	}
};