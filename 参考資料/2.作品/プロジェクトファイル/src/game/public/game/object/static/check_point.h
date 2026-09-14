#pragma once
#include "game/base/object.h"
#include "game/data/global_data.h"

static const char* CHECK_POINT_MODEL_PATH = "data/model/field/goal.mv1";

class C_CHECK_POINT : public C_OBJECT_BASE
{
private:

	C_GLOBAL_DATA* m_golobalData;

	C_GLOBAL_DATA::T_FLAG_DATA* m_flagData;

public:

	C_CHECK_POINT();
	~C_CHECK_POINT();
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(T_OBJECT_DATA _objectData);
	void HitCalc();
};

