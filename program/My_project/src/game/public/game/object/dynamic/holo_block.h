#pragma once
#include "game/base/object.h"
#include "game/data/global_data.h"

class C_HOLO_BLOCK : public C_OBJECT_BASE
{
private:

	C_GLOBAL_DATA* c_globalData;
	C_GLOBAL_DATA::T_PLAYER_DATA* m_playerData;

	float m_speedUp;

	int m_graphHndl1;

	int m_graphHndl2;

	int m_moveLen;

public:

	C_HOLO_BLOCK(float _speedUp = 0.0f, int _graphHndl1 = 0, int _graphHndl2 = 0,
		int _moveLen = 0):
		m_speedUp(_speedUp), m_graphHndl1(_graphHndl1), m_graphHndl2(_graphHndl2),
		c_globalData(nullptr), m_playerData(nullptr), m_moveLen(_moveLen) { }

	~C_HOLO_BLOCK(){}

	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation,
		int _modelHndl, int _graphHndl1, int _graphHndl2,int _moveLen);
	void HitCalc();
};

