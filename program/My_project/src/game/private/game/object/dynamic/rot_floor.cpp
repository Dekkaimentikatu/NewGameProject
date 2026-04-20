#include "game/object/dynamic/rot_floor.h"
#include "lib/2Ddirection/easing/easing.h"
#include "block_common.h"


void C_ROT_FLOOR::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_speedUp = MAX_TIME;
}

void C_ROT_FLOOR::Request(T_OBJECT_DATA _objectData)
{
	m_pos = m_objectData.initPos = _objectData.initPos;
	m_objectData.modelScale = _objectData.modelScale;
	m_objectData.modelRot = _objectData.modelRot;
	m_moveRot = _objectData.modelRot;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_moveLen = _objectData.moveLen;
	m_isActive = true;
}

void C_ROT_FLOOR::Load()
{
	c_globalData = C_GLOBAL_DATA::GetInstace();
	m_playerData = c_globalData->GetPlayerData();
	DuplicateModel(m_modelHndl);
	UpdateModel();
	SetUpCollInfo();
}

void C_ROT_FLOOR::Step()
{
	//イージング加減速
	if (!m_playerData->isStop)
	{
		m_speedUp += PLAYBACK_SPEED;
		if (m_speedUp >= MAX_TIME)m_speedUp = MAX_TIME;
	}
	else
	{
		m_speedUp -= PLAYBACK_SPEED;
		if (m_speedUp <= MIN_TIME)m_speedUp = MIN_TIME;
	}

	//回転処理
	if (m_moveDir == 0)
	{
		m_moveRot.y = -ROT_SPEED * C_EASING::InQuad<float>(m_speedUp, MAX_TIME);
	}
	else
	{
		m_moveRot.y = ROT_SPEED * C_EASING::InQuad<float>(m_speedUp, MAX_TIME);
	}

	m_objectData.modelRot.y += m_moveRot.y;
}

void C_ROT_FLOOR::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_ROT_FLOOR::Draw()
{
	DrawModel();
}

void C_ROT_FLOOR::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_ROT_FLOOR::HitCalc()
{

}