#include "game/object/dynamic/rot_floor.h"
#include "lib/2Ddirection/easing/easing.h"
#include "block_common.h"


void C_ROT_FLOOR::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_scale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_speedUp = MAX_TIME;
}

void C_ROT_FLOOR::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation,
	int _modelHndl, int _moveDir, float _moveLen)
{
	m_pos = m_startPos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	m_moveRot = _rotation;
	m_modelHndl = _modelHndl;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_moveLen = _moveLen;
	m_att = 500;
	m_moveDir = _moveDir;
	m_isActive = true;
}

void C_ROT_FLOOR::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl)
{
	m_pos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
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

	m_modelRota.y += m_moveRot.y;
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