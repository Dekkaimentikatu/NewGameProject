#include "game/object/static/block.h"
#include "lib/3Dhndlmanager.h"

C_BLOCK::C_BLOCK()
{

}

C_BLOCK::~C_BLOCK()
{

}

void C_BLOCK::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
}

void C_BLOCK::Request(T_OBJECT_DATA _objectData)
{
	m_pos = m_objectData.initPos = _objectData.initPos;
	m_objectData.modelScale = _objectData.modelScale;
	m_objectData.modelRot = _objectData.modelRot;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_isActive = true;
}

void C_BLOCK::Load()
{
	C_3D_HNDL_MANAGER* instace = C_3D_HNDL_MANAGER::GetInstance();
	DuplicateModel(instace->Get3DModelHndl("data/model/field/Floor_1.mv1"));
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