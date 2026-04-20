#pragma once
#include "game/base/object.h"

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
	void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl);
	void HitCalc();
};

