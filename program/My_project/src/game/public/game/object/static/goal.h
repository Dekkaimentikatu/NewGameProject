#pragma once
#include "game/base/object.h"
#include "game/data/global_data.h"

class C_GOAL : public C_OBJECT_BASE
{
private:

	C_GLOBAL_DATA* m_golobalData;

	C_GLOBAL_DATA::T_FLAG_DATA* m_flagData;

	C_GLOBAL_DATA::T_PLAYER_DATA* m_playerData;

public:

	C_GOAL();
	~C_GOAL();
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl);
	void HitCalc();
};

