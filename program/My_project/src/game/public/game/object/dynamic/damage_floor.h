#pragma once
#include "game/base/object.h"
#include "game/data/global_data.h"

constexpr float ATTACK_WAIT_MAX = 120.0f;

constexpr int ATTACK_POWER = 500;

constexpr int ATTACK_MODE = 1;

static const char* DAMAGE_FLOOR_MODEL_PATH = "data/model/field/damage_floor.mv1";

class C_DAMAGE_FLOOR : public C_OBJECT_BASE
{
private:

	C_GLOBAL_DATA* c_globalData;
	C_GLOBAL_DATA::T_PLAYER_DATA* m_playerData;

	int m_moveDir;

	float m_speedUp;

	int m_grapHndl[2];

public:
	C_DAMAGE_FLOOR(C_GLOBAL_DATA* _globalData = nullptr,
		C_GLOBAL_DATA::T_PLAYER_DATA* _playerData = nullptr, int _moveDir = 0, float _speedUp = 0.0f):
		c_globalData(_globalData), m_playerData(_playerData), 
		m_moveDir(_moveDir), m_speedUp(_speedUp), m_grapHndl() { }

	~C_DAMAGE_FLOOR();

	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(T_OBJECT_DATA _objectData);
	void HitCalc();
};

