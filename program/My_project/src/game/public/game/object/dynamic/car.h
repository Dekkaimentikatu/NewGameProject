#pragma once
#include "game/base/object.h"
#include "game/data/global_data.h"

class C_CAR : public C_OBJECT_BASE
{
private:

	C_GLOBAL_DATA* c_globalData;
	C_GLOBAL_DATA::T_PLAYER_DATA* m_playerData;

	int m_moveDir;

	int m_endLen;

	float m_speedUp;

	bool m_isHit;

	VECTOR MoveCalc();

public:

	C_CAR();
	~C_CAR();

	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl, int _moveDir, float _endLen);
	void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl);
	void HitCalc();
};

