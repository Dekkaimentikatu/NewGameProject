#pragma once
#include "game/base/object.h"
#include "game/data/global_data.h"

constexpr float S_ROT_SPEED = 0.05f;

class C_CIRCULAR_MOTION : public C_OBJECT_BASE
{
private:

	C_GLOBAL_DATA* c_globalData;
	C_GLOBAL_DATA::T_PLAYER_DATA* m_playerData;

	int m_moveDir;

	float m_moveLen;


	VECTOR m_moveRot;

	float m_speedUp;

	VECTOR MoveCalc();

public:

	C_CIRCULAR_MOTION(int _moveDir = 0, float _moveLen = 0.0f, VECTOR _moveRot = { 0 }
		, float _speedUp = 0.0f) :
		m_moveDir(_moveDir), m_moveLen(_moveLen), m_speedUp(_speedUp),
		m_moveRot(_moveRot), c_globalData(nullptr), m_playerData(nullptr) {
	}
	~C_CIRCULAR_MOTION() {}

	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(T_OBJECT_DATA _objectData);
	void HitCalc();
};

