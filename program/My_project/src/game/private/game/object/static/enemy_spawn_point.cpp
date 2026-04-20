#include "game/object/static/enemy_spawn_point.h"

C_ENEMY_SPAWN_POINT::C_ENEMY_SPAWN_POINT()
{

}

C_ENEMY_SPAWN_POINT::~C_ENEMY_SPAWN_POINT()
{

}

void C_ENEMY_SPAWN_POINT::Init()
{
	//
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_scale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_objectType = OBJECT_TYPE_STATIC;
}

void C_ENEMY_SPAWN_POINT::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl)
{
	//
	m_pos = m_startPos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	m_objectType = OBJECT_TYPE_STATIC;
	m_redius = 16;
}

void C_ENEMY_SPAWN_POINT::Load()
{
	m_golobalData = C_GLOBAL_DATA::GetInstace();

	m_flagData = m_golobalData->GetFlagData();
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);

}

void C_ENEMY_SPAWN_POINT::Step()
{

}

void C_ENEMY_SPAWN_POINT::Update()
{

}

void C_ENEMY_SPAWN_POINT::Draw()
{
#ifdef DEBUG_MODE
	DrawSphere3D(GetCenter(), static_cast<float>(m_redius), m_redius, GetColor(0, 255, 255), GetColor(0, 255, 255), FALSE);
#endif
}

void C_ENEMY_SPAWN_POINT::Exit()
{

}

void C_ENEMY_SPAWN_POINT::HitCalc()
{

}