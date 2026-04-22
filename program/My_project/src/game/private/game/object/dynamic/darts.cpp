#include "game/object/dynamic/darts.h"
#include "lib/2Ddirection/easing/easing.h"
#include "block_common.h"
#include "lib/3Dhndlmanager.h"

C_DARTS::C_DARTS()
{

}

C_DARTS::~C_DARTS()
{

}

void C_DARTS::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(10.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_speedUp = MAX_TIME;
}

void C_DARTS::Request(T_OBJECT_DATA _objectData)
{
	C_3D_HNDL_MANAGER* instace = C_3D_HNDL_MANAGER::GetInstance();
	m_modelHndl = instace->Get3DModelHndl(_DARTS_MODEL_PATH);
	m_pos = _objectData.initPos;
	m_objectData = _objectData;
	m_objectData.modelScale = VGet(0.2f, 0.2f, 0.2f);	//スケール
	m_objectType = OBJECT_TYPE_BLCOK;
	m_isActive = true;
	m_isHit = false;
}

void C_DARTS::Load()
{
	c_globalData = C_GLOBAL_DATA::GetInstace();
	m_playerData = c_globalData->GetPlayerData();
	DuplicateModel(m_modelHndl);
	UpdateModel();
	SetUpCollInfo();
}

void C_DARTS::Step()
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

	VECTOR lenVec = VSub(m_pos, m_objectData.initPos);
	float len = VSize(lenVec);

	//範囲外に出たら初期位置に戻す
	if (len > m_objectData.moveLen || m_playerData->isRespawn)
	{
		m_pos = m_objectData.initPos;
	}

	m_isHit = false;
}

VECTOR C_DARTS::MoveCalc()
{
	//移動方向計算
	VECTOR moveDir = { 0.0f, 0.0f, -1.0f };

	MATRIX dir = MGetTranslate(moveDir);

	MATRIX mRotY = MGetRotY(m_objectData.modelRot.y);

	MATRIX mRotX = MGetRotX(m_objectData.modelRot.x);

	MATRIX mResult = MMult(dir, mRotY);

	mResult = MMult(mResult, mRotX);

	VECTOR vResult = { 0 };

	vResult.x = mResult.m[3][0];
	vResult.y = mResult.m[3][1];
	vResult.z = mResult.m[3][2];

	if (m_isHit)vResult.y = -2.0f;
	else vResult.y = -0.02f;

	vResult = VNorm(vResult);

	return vResult;
}

void C_DARTS::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_DARTS::Draw()
{
	DrawModel();
}

void C_DARTS::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_DARTS::HitCalc()
{
	m_isHit = true;
}