#include "game/object/static/start.h"

C_START::~C_START()
{

}

void C_START::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_scale = VGet(0.1f, 0.1f, 0.1f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
}

void C_START::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl)
{
	m_pos = m_startPos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	m_modelHndl = _modelHndl;
	m_objectType = OBJECT_TYPE_FLAG;
	m_redius = 16;
}

void C_START::Load()
{
	m_golobalData = C_GLOBAL_DATA::GetInstace();

	m_flagData = m_golobalData->GetFlagData();
	DuplicateModel(m_modelHndl);
	m_scale = VGet(0.1f, 0.1f, 0.1f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_flagData->StartPos = m_pos;
	UpdateModel();
	SetUpCollInfo();
}

void C_START::Step()
{

}

void C_START::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_START::Draw()
{
	DrawModel();
#ifdef DEBUG_MODE
	DrawSphere3D(m_pos, static_cast<float>(m_redius), 16, GetColor(255, 0, 255), GetColor(255, 0, 255), FALSE);
#endif
}

void C_START::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_START::HitCalc()
{
	m_flagData->StartPos = m_pos;
}