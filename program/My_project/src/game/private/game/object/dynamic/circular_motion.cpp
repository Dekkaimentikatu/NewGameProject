#include <math.h>
#include "game/object/dynamic/circular_motion.h"
#include "lib/2Ddirection/easing/easing.h"
#include "block_common.h"


void C_CIRCULAR_MOTION::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_scale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(10.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_speedUp = MAX_TIME;
}

void C_CIRCULAR_MOTION::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation,
	int _modelHndl, int _grapHndl, int _moveDir, float _moveLen)
{
	m_pos = m_startPos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	m_moveRot = _rotation;
	m_modelHndl = _modelHndl;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_moveLen = _moveLen;
	m_moveDir = _moveDir;
	m_isActive = true;
}

void C_CIRCULAR_MOTION::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl)
{
	m_pos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	m_modelHndl = _modelHndl;
	m_isActive = true;
}

void C_CIRCULAR_MOTION::Load()
{
	c_globalData = C_GLOBAL_DATA::GetInstace();
	m_playerData = c_globalData->GetPlayerData();
	DuplicateModel(m_modelHndl);
	m_pos = MoveCalc();
	m_moveVec = VSub(m_startPos, m_pos);
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
	VECTOR vResult = VGet(m_moveLen * cosf(m_moveRot.y) + m_startPos.x, 0.0f, 
		m_moveLen * sinf(m_moveRot.y) + m_startPos.z);

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

	DrawLine3D(m_pos, m_startPos, GetColor(255, 0, 0));
}

void C_CIRCULAR_MOTION::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_CIRCULAR_MOTION::HitCalc()
{

}