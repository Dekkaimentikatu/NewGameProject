#include "game/object/static/board.h"

C_BOARD::~C_BOARD()
{

}

void C_BOARD::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_scale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
}

void C_BOARD::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl, int imageHndl)
{
	m_pos = m_startPos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	m_modelHndl = _modelHndl;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_isActive = true;
	m_imageHndl = imageHndl;
}

void C_BOARD::Load()
{
	DuplicateModel(m_modelHndl);
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	UpdateModel();
	SetUpCollInfo();
	m_objectType = OBJECT_TYPE_BLCOK;
	MV1SetTextureGraphHandle(m_modelHndl, 0, m_imageHndl, FALSE);
}

void C_BOARD::Step()
{
	
}

void C_BOARD::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_BOARD::Draw()
{
	DrawModel();
}

void C_BOARD::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_BOARD::HitCalc()
{

}