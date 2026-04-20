#include "game/object/static/goal.h"

C_GOAL::C_GOAL()
{

}

C_GOAL::~C_GOAL()
{

}

void C_GOAL::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(0.1f, 0.1f, 0.1f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
}

void C_GOAL::Request(T_OBJECT_DATA _objectData)
{
	m_pos = m_objectData.initPos = _objectData.initPos;
	m_objectData.modelScale = _objectData.modelScale;
	m_objectData.modelRot = _objectData.modelRot;
	m_objectType = OBJECT_TYPE_FLAG;
	m_redius = 16;
}

void C_GOAL::Load()
{
	//広域データから必要な情報を
	m_golobalData = C_GLOBAL_DATA::GetInstace();

	m_flagData = m_golobalData->GetFlagData();

	m_playerData = m_golobalData->GetPlayerData();

	//モデルの複製
	DuplicateModel(m_modelHndl);

	//
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_flagData->GoalPos = m_pos;
	UpdateModel();
	SetUpCollInfo();
}

void C_GOAL::Step()
{

}

void C_GOAL::Update()
{
	//モデル情報の更新
	UpdateModel();
	UpdataCollInfo();
}

void C_GOAL::Draw()
{
	DrawModel();
#ifdef DEBUG_MODE
	DrawSphere3D(m_pos, static_cast<float>(m_redius), 16, GetColor(255, 0, 255), GetColor(255, 0, 255), FALSE);
#endif
}

void C_GOAL::Exit()
{
	//モデル情報の削除
	DeleteModel();
	DeleteCollInfo();
}

void C_GOAL::HitCalc()
{
	m_playerData->isGoal = true;
}