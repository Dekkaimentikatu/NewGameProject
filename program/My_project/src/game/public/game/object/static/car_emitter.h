#pragma once
#include "game/base/object.h"
#include <list>

using namespace std;

constexpr int OBJECT_MAX = 1;

class C_CAR_EMITTER : public C_OBJECT_BASE
{
private:

	list<C_OBJECT_BASE*> m_objectList;

	int m_moveDir;

	int m_moveLen;

	void RequestToObject();

public:

	C_CAR_EMITTER(int _moveDir = 0, int _moveLen = 0) :
		m_moveDir(_moveDir), m_moveLen(_moveLen) {
	}
	~C_CAR_EMITTER() {}

	void Init();

	void Load();

	void Step();

	void Update();

	void Draw();

	void Exit();

	void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl, int _moveLen);

	void HitCalc();

};


