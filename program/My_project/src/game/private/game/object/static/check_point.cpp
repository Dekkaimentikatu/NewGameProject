#include "game/object/static/check_point.h"
#include "lib/3Dhndlmanager.h"

C_CHECK_POINT::C_CHECK_POINT()
{

}

C_CHECK_POINT::~C_CHECK_POINT()
{

}

void C_CHECK_POINT::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル

}

void C_CHECK_POINT::Request(T_OBJECT_DATA _objectData)
{
	C_3D_HNDL_MANAGER* instace = C_3D_HNDL_MANAGER::GetInstance();
	m_modelHndl = instace->Get3DModelHndl(CHECK_POINT_MODEL_PATH);
	m_pos = m_objectData.initPos = _objectData.initPos;
	m_objectData.modelScale = _objectData.modelScale;
	m_objectData.modelRot = _objectData.modelRot;
	m_objectType = OBJECT_TYPE_FLAG;
	m_redius = 16;
	m_isActive = true;
}

void C_CHECK_POINT::Load()
{
	m_golobalData = C_GLOBAL_DATA::GetInstace();

	m_flagData = m_golobalData->GetFlagData();

	DuplicateModel(m_modelHndl);

	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	UpdateModel();
	SetUpCollInfo();
}

void C_CHECK_POINT::Step()
{

}

void C_CHECK_POINT::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_CHECK_POINT::Draw()
{
	DrawModel();

#ifdef DEBUG_MODE

	DrawSphere3D(m_pos, static_cast<float>(m_redius), 16, GetColor(255, 0, 255), GetColor(255, 0, 255), FALSE);

#endif

}



	
void C_CHECK_POINT::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_CHECK_POINT::HitCalc()
{
	m_flagData->StartPos = m_pos;
}