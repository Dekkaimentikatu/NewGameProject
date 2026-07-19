#include "game/base/actor.h"

C_ACTOR_BASE::C_ACTOR_BASE()
{
	Init();
}

void C_ACTOR_BASE::Init()
{
	C_OBJECT_BASE::Init();

	//攻撃力
	m_att = 0;

	//ジャンプ中フラグ
	m_isJump = false;

	//当たり判定フラグ
	m_isHit = false;

	//攻撃中フラグ
	m_isAttack = false;

	//目標の座標
	m_targetPos = { 0 };

	//カメラの回転
	m_cameraRot = { 0 };

	//押し戻し速度
	m_knockBackSpeed = { 0 };

	//リスポーンフラグ
	m_isRespawn = false;

	//当たり判定待機時間
	m_hitWait = 0;

	//攻撃待機時間
	m_attackWait = 0.0f;

	//攻撃判定の半径
	m_attackRedius = 0;
}

void C_ACTOR_BASE::Request(T_OBJECT_DATA _objectData)
{
	m_objectData = _objectData;		//オブジェクトデータの保存
}

int C_ACTOR_BASE::GetAtt()
{
	return m_att;
}