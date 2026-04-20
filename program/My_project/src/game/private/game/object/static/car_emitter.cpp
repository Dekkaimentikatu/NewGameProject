#include "game/object/static/car_emitter.h"
#include "game/collision/collision_manager.h"
#include "game/object/dynamic/darts.h"

void C_CAR_EMITTER::RequestToObject()
{
	C_DARTS* tmp = new C_DARTS;

	tmp->Init();
	tmp->Request(m_objectData);
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

void C_CAR_EMITTER::Request(T_OBJECT_DATA _objectData)
{
	m_pos = m_objectData.initPos = _objectData.initPos;
	m_objectData.modelScale = _objectData.modelScale;
	m_objectData.modelRot = _objectData.modelRot;
	m_redius = 16;
	m_moveLen = _objectData.moveLen;
}

void C_CAR_EMITTER::HitCalc()
{

}