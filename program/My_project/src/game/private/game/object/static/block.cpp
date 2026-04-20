#include "game/object/static/block.h"

C_BLOCK::C_BLOCK()
{

}

C_BLOCK::~C_BLOCK()
{

}

void C_BLOCK::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_scale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
}

void C_BLOCK::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl)
{
	m_pos = m_startPos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	m_modelHndl = _modelHndl;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_isActive = true;
}

void C_BLOCK::Load()
{
	DuplicateModel(m_modelHndl);
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	UpdateModel();
	SetUpCollInfo();
	m_objectType = OBJECT_TYPE_BLCOK;
}

void C_BLOCK::Step()
{

}

void C_BLOCK::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_BLOCK::Draw()
{
	DrawModel();
}

void C_BLOCK::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_BLOCK::HitCalc()
{

}