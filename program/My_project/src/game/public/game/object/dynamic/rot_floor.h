#pragma once
#include "game/base/object.h"
#include "game/data/global_data.h"

constexpr float ROT_SPEED = 0.5f;

class C_ROT_FLOOR : public C_OBJECT_BASE
{
private:

	C_GLOBAL_DATA* c_globalData;
	C_GLOBAL_DATA::T_PLAYER_DATA* m_playerData;

	int m_moveDir;

	int m_graphicHndl;

	float m_moveLen;

	VECTOR m_moveRot;

	float m_speedUp;

public:

	C_ROT_FLOOR(int _moveDir = 0, int _graphicHndl = 0, float _moveLen = 0.0f,
		VECTOR _moveRot = { 0 }, float _speedUp = 0.0f) :
		m_moveDir(_moveDir), m_graphicHndl(_graphicHndl), m_moveLen(_moveLen),
		m_speedUp(_speedUp), m_moveRot(_moveRot), c_globalData(nullptr), m_playerData(nullptr){}

	~C_ROT_FLOOR(){}

	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation,
		int _modelHndl, int _moveDir, float _movelen);
	void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl);
	void HitCalc();
};

