#include <math.h>
#include "game/object/dynamic/circular_motion.h"
#include "lib/2Ddirection/easing/easing.h"
#include "block_common.h"


void C_CIRCULAR_MOTION::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(10.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_speedUp = MAX_TIME;
}

void C_CIRCULAR_MOTION::Request(T_OBJECT_DATA _objectData)
{
	m_pos = m_objectData.initPos = _objectData.initPos;
	m_objectData.modelScale = _objectData.modelScale;
	m_objectData.modelRot = _objectData.modelRot;
	m_moveRot = _objectData.modelRot;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_moveLen = _objectData.moveLen;
	m_isActive = true;
}

void C_CIRCULAR_MOTION::Load()
{
	c_globalData = C_GLOBAL_DATA::GetInstace();
	m_playerData = c_globalData->GetPlayerData();
	DuplicateModel(m_modelHndl);
	m_pos = MoveCalc();
	m_moveVec = VSub(m_objectData.initPos, m_pos);
	m_moveVec = VNorm(m_moveVec);
	UpdateModel();
	SetUpCollInfo();
}

void C_CIRCULAR_MOTION::Step()
{
	//イージングの加減速
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

	//ヨー軸回転
	if (m_moveDir)
	{
		m_moveRot.y += -S_ROT_SPEED * C_EASING::InQuad<float>(m_speedUp, MAX_TIME);
	}
	else
	{
		m_moveRot.y += S_ROT_SPEED * C_EASING::InQuad<float>(m_speedUp, MAX_TIME);
	}

	//移動計算
	VECTOR tmp = m_pos;
	m_pos = MoveCalc();
	m_moveVec = VSub(tmp, m_pos);

	if (m_playerData->isRespawn)
	{

	}
}

VECTOR C_CIRCULAR_MOTION::MoveCalc()
{
	//ベクトルの外積で方向ベクトルを算出
	VECTOR vResult = VGet(m_moveLen * cosf(m_moveRot.y) + m_objectData.initPos.x, 0.0f, 
		m_moveLen * sinf(m_moveRot.y) + m_objectData.initPos.z);

	return vResult;
}

void C_CIRCULAR_MOTION::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_CIRCULAR_MOTION::Draw()
{
	DrawModel();

	DrawLine3D(m_pos, m_objectData.initPos, GetColor(255, 0, 0));
}

void C_CIRCULAR_MOTION::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_CIRCULAR_MOTION::HitCalc()
{

}