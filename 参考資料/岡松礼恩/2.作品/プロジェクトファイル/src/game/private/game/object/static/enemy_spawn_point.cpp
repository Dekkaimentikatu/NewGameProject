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
	m_golobalData = C_GLOBAL_DATA::GetInstace();
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_objectType = OBJECT_TYPE_STATIC;
}

void C_ENEMY_SPAWN_POINT::Request(T_OBJECT_DATA _objectData)
{
	//
	m_pos = _objectData.initPos;
	m_objectData = _objectData;
	m_objectType = OBJECT_TYPE_STATIC;
	m_redius = 16;
	C_GLOBAL_DATA::T_ENEMY_SPOWN tmp;
	tmp.pos = m_pos;
	tmp.rot = m_objectData.modelRot;
	tmp.scale = m_objectData.modelScale;

	m_golobalData->GetEnemySpawnPointList()->push_back(tmp);
}

void C_ENEMY_SPAWN_POINT::Load()
{
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