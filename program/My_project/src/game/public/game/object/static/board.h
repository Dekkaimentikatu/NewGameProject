#pragma once
#include "game/base/object.h"


class C_BOARD : public C_OBJECT_BASE
{
private:

	int m_imageHndl;

public:

	C_BOARD():m_imageHndl(0){}
	~C_BOARD();
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl, int imageHndl);
	void HitCalc();
};
