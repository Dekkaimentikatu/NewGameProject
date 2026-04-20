#pragma once
#include "game/base/object.h"
#include "game/data/global_data.h"

class C_DARTS : public C_OBJECT_BASE
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

	C_DARTS();
	~C_DARTS();

	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(T_OBJECT_DATA _objectData);
	void HitCalc();
};

