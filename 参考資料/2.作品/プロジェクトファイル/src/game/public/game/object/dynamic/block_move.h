#pragma once
#include "game/base/object.h"
#include "game/data/global_data.h"

static const char* BLOCK_MOVE_MODEL_PATH = "data/model/field/Floor_2.mv1";

class C_BLOCK_MOVE : public C_OBJECT_BASE
{
private:

	C_GLOBAL_DATA* c_globalData;
	C_GLOBAL_DATA::T_PLAYER_DATA* m_playerData;

	bool m_moveDir;

	float m_speedUp;

	int m_moveLen;

	VECTOR m_initMoveVec;

	VECTOR m_moveRot;

	VECTOR Circular();

	VECTOR Translation();

	VECTOR MoveCalc();

public:

	C_BLOCK_MOVE(bool _moveDir = false, int _moveLen = 0, VECTOR _initMoveVec = { 0 }, 
		VECTOR _moveRot = { 0 }, float _speedUp = 0.0f) :
		m_moveDir(_moveDir), m_moveLen(_moveLen), m_initMoveVec(_initMoveVec), m_moveRot(_moveRot),
		m_speedUp(_speedUp), c_globalData(nullptr), m_playerData(nullptr){};

	~C_BLOCK_MOVE();

	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(T_OBJECT_DATA _objectData);
	void HitCalc();
};

