#include "game/object/dynamic/holo_block.h"
#include "lib/2Ddirection/easing/easing.h"
#include "block_common.h"

void C_HOLO_BLOCK::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_isActive = true;	//生存フラグ
	m_speedUp = MAX_TIME;
	m_isHit = false;	//当たり判定リセット
}

void C_HOLO_BLOCK::Load()
{
	c_globalData = C_GLOBAL_DATA::GetInstace();
	m_playerData = c_globalData->GetPlayerData();
	DuplicateModel(m_modelHndl);
	UpdateModel();
	SetUpCollInfo();
}

void C_HOLO_BLOCK::Request(T_OBJECT_DATA _objectData)
{
	m_pos = m_objectData.initPos = _objectData.initPos;
	m_objectData.modelScale = _objectData.modelScale;
	m_objectData.modelRot = _objectData.modelRot;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_moveLen = _objectData.moveLen;
}

void C_HOLO_BLOCK::Step()
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

	//当たり判定があったかどうかで移動方向を変更
	if (m_isHit)
	{
		m_moveVec.y = static_cast<float>(-BOSS_MOVE_SPEED);
	}
	else
	{
		m_moveVec.y = 0;
	}

	//移動ベクトルにイージング処理
	m_moveVec = VScale(m_moveVec, C_EASING::InQuad<float>(m_speedUp, MAX_TIME));
	//位置更新
	m_pos = VAdd(m_pos, m_moveVec);

	//元の位置まで戻ったら位置固定
	if (m_isHit && m_pos.y < m_objectData.initPos.y - m_moveLen)
	{
		m_pos.y = m_objectData.initPos.y;
		m_moveVec = { 0 };
		m_isHit = false;	//当たり判定リセット
	}


}

void C_HOLO_BLOCK::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_HOLO_BLOCK::Draw()
{
	DrawModel();
}

void C_HOLO_BLOCK::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}



void C_HOLO_BLOCK::HitCalc()
{
	m_isHit = true;
}