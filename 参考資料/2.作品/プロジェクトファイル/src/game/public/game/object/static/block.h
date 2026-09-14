#pragma once
#include "game/base/object.h"

static const char* BLOCK_MODEL_PATH = "data/model/field/Floor_1.mv1";

class C_BLOCK : public C_OBJECT_BASE
{
private:

public:

	C_BLOCK();
	~C_BLOCK();
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(T_OBJECT_DATA _objectData);
	void HitCalc();
};

