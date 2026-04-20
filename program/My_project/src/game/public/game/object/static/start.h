#pragma once
#include "game/base/object.h"
#include "game/data/global_data.h"

class C_START : public C_OBJECT_BASE
{
private:

	C_GLOBAL_DATA* m_golobalData;

	C_GLOBAL_DATA::T_FLAG_DATA* m_flagData;

public:

	C_START(C_GLOBAL_DATA* _golobalData = nullptr,
		C_GLOBAL_DATA::T_FLAG_DATA* _flagData = nullptr) :
		m_golobalData(_golobalData), m_flagData(_flagData) {};
	~C_START();
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl);
	void HitCalc();
};

