#include "game/object/static/board.h"
#include "lib/3Dhndlmanager.h"

C_BOARD::~C_BOARD()
{

}

void C_BOARD::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
}

void C_BOARD::Request(T_OBJECT_DATA _objectData)
{
	C_3D_HNDL_MANAGER* instace = C_3D_HNDL_MANAGER::GetInstance();
	m_modelHndl = instace->Get3DModelHndl(BOARD_MODEL_PATH);
	m_pos = m_objectData.initPos = _objectData.initPos;
	m_objectData.modelScale = _objectData.modelScale;
	m_objectData.modelRot = _objectData.modelRot;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_isActive = true;
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