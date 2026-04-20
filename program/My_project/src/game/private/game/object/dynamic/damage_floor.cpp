#include "game/object/dynamic/damage_floor.h"
#include "lib/2Ddirection/easing/easing.h"
#include "block_common.h"


C_DAMAGE_FLOOR::~C_DAMAGE_FLOOR()
{

}

void C_DAMAGE_FLOOR::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_scale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(10.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_speedUp = MAX_TIME;
}

void C_DAMAGE_FLOOR::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation,
	int _modelHndl, int _moveDir, int grapHndl1, int grapHndl2)
{
	m_pos = m_startPos = _pos;
	m_pos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	m_modelHndl = _modelHndl;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_att = ATTACK_POWER;
	m_moveDir = _moveDir;
	if (_moveDir == ATTACK_MODE)m_isActive = true;
	else m_isActive = false;
	m_grapHndl[0] = grapHndl1;
	m_grapHndl[1] = grapHndl2;
}

void C_DAMAGE_FLOOR::Load()
{
	c_globalData = C_GLOBAL_DATA::GetInstace();
	m_playerData = c_globalData->GetPlayerData();
	DuplicateModel(m_modelHndl);
	MV1SetTextureGraphHandle(m_modelHndl, 1, m_grapHndl[m_moveDir], FALSE);
	UpdateModel();
	SetUpCollInfo();
}

void C_DAMAGE_FLOOR::Step()
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

	//攻撃と待機の切り替え
	m_attackWait += C_EASING::InQuad<float>(m_speedUp, MAX_TIME);

	if (m_attackWait > ATTACK_WAIT_MAX)
	{
		m_isAttack = !m_isAttack;
		m_attackWait = 0.0f;
		if (m_isAttack)m_moveDir = ATTACK_MODE;
		else m_moveDir = 0;
	}

	//テクスチャ切り替え
	MV1SetTextureGraphHandle(m_modelHndl, 1, m_grapHndl[m_moveDir], FALSE);
}

void C_DAMAGE_FLOOR::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_DAMAGE_FLOOR::Draw()
{
	DrawModel();
}

void C_DAMAGE_FLOOR::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_DAMAGE_FLOOR::HitCalc()
{

}