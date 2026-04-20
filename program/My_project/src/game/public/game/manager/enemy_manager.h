#pragma once

#include "game/base/manager_base.h"

#include "game/actor/enemy/enemy.h"
#include "game/actor/boss/boss.h"

#include "lib/rand.h"

class C_ENEMY_MANAGER : public C_ACOTR_MANAGER_BASE
{
private:

	C_ENEMY_MANAGER* m_instance;

	VECTOR m_targetPos;

	int m_modelHndl;	//モデルハンドル

public:

	C_ENEMY_MANAGER(C_ENEMY_MANAGER* _instance = nullptr, VECTOR _targetPos = { 0 },
		int _modelHndl = 0):
	m_instance(_instance), m_targetPos(_targetPos), m_modelHndl(_modelHndl){}
	~C_ENEMY_MANAGER(){}

	void Init();	//初期化

	void LoadAnSync();	//リソース読込

	void LoadSync();	//読込

	void Step();	//更新

	void Update();	//更新確定

	void Draw();	//描画

	void Exit();	//終了

	void SetTargetPos(VECTOR _targetPos);		//目標座標の設定

	bool GetIsEnd();
};