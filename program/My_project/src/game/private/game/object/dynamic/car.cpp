#include "game/object/dynamic/car.h"
#include "lib/2Ddirection/easing/easing.h"
#include "block_common.h"

C_CAR::C_CAR()
{

}

C_CAR::~C_CAR()
{

}

void C_CAR::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_scale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(10.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_speedUp = MAX_TIME;
}

void C_CAR::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation,
	int _modelHndl, int _moveDir, float _endLen)
{
	m_pos = m_startPos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	m_scale = VGet(0.2f, 0.2f, 0.2f);	//スケール
	m_modelHndl = _modelHndl;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_endLen = static_cast<int>(_endLen);
	m_isActive = true;
	m_isHit = false;
}

void C_CAR::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl)
{
	m_pos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
}

void C_CAR::Load()
{
	c_globalData = C_GLOBAL_DATA::GetInstace();
	m_playerData = c_globalData->GetPlayerData();
	DuplicateModel(m_modelHndl);
	UpdateModel();
	SetUpCollInfo();
}

void C_CAR::Step()
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

	//移動処理
	m_moveVec = VScale(MoveCalc(), BOSS_MOVE_SPEED);
	m_moveVec = VScale(m_moveVec, C_EASING::InQuad<float>(m_speedUp, MAX_TIME));
	m_pos = VAdd(m_pos, m_moveVec);

	VECTOR lenVec = VSub(m_pos, m_startPos);
	float len = VSize(lenVec);

	//範囲外に出たら初期位置に戻す
	if (len > m_endLen || m_playerData->isRespawn)
	{
		m_pos = m_startPos;
	}

	m_isHit = false;
}

VECTOR C_CAR::MoveCalc()
{
	//移動方向計算
	VECTOR moveDir = { 0.0f, 0.0f, -1.0f };

	MATRIX dir = MGetTranslate(moveDir);

	MATRIX mRotY = MGetRotY(m_modelRota.y);

	MATRIX mRotX = MGetRotX(m_modelRota.x);

	MATRIX mResult = MMult(dir, mRotY);

	mResult = MMult(mResult, mRotX);

	VECTOR vResult = { 0 };

	vResult.x = mResult.m[3][0];
	vResult.y = mResult.m[3][1];
	vResult.z = mResult.m[3][2];

	vResult = VNorm(vResult);

	return vResult;
}

void C_CAR::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_CAR::Draw()
{
	DrawModel();
}

void C_CAR::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_CAR::HitCalc()
{
	m_isHit = true;
}