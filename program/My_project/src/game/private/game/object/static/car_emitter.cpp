#include "game/object/static/car_emitter.h"
#include "game/collision/collision_manager.h"
#include "game/object/dynamic/darts.h"

void C_CAR_EMITTER::RequestToObject()
{
	C_DARTS* tmp = new C_DARTS;

	tmp->Init();
	tmp->Request(m_pos, m_scale, m_modelRota, m_modelHndl, m_moveDir,
		static_cast<float>(m_moveLen));
	tmp->Load();

	m_objectList.push_back(tmp);
}

void C_CAR_EMITTER::Init()
{
	C_OBJECT_BASE::Init();

	m_objectList.clear();

	m_objectType = OBJECT_TYPE_STATIC;
}

void C_CAR_EMITTER::Load()
{
	RequestToObject();
	auto itr = m_objectList.begin();
	C_COLLISION_MANAGER::AddObject(*itr);
}

void C_CAR_EMITTER::Step()
{
	for (auto itr = m_objectList.begin(); itr != m_objectList.end(); ++itr)
	{
		(*itr)->Step();
	}
}

void C_CAR_EMITTER::Update()
{
	for (auto itr = m_objectList.begin(); itr != m_objectList.end(); ++itr)
	{
		(*itr)->Update();
	}
}

void C_CAR_EMITTER::Draw()
{
	for (auto itr = m_objectList.begin(); itr != m_objectList.end(); ++itr)
	{
		(*itr)->Draw();
	}

#ifdef DEBUG_MODE

	DrawSphere3D(m_pos, static_cast<float>(m_redius), 16, GetColor(255, 0, 255), GetColor(255, 0, 255), FALSE);

#endif
}

void C_CAR_EMITTER::Exit()
{
	for (auto itr = m_objectList.begin(); itr != m_objectList.end(); ++itr)
	{
		(*itr)->Exit();
		delete (*itr);
	}

	m_objectList.clear();
}

void C_CAR_EMITTER::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl, int _moveLen)
{
	m_pos = m_startPos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	m_modelHndl = _modelHndl;
	m_redius = 16;
	m_moveLen = _moveLen;
}

void C_CAR_EMITTER::HitCalc()
{

}