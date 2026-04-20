#include "game/actor/boss/boss.h"

void C_BOSS::Init()
{
	//アクターの初期化
	C_ACTOR_BASE::Init();

	/*m_pos = VGet(0.0f,0.0f, -100.0f);*/

	m_objectData.modelScale = VGet(BOSS_SCALE_X, BOSS_SCALE_Y, BOSS_SCALE_Z);

	m_redius = BOSS_RADIUS;

	m_attackRedius = BOSS_ATTACK_RADIUS;

	m_hp = BOSS_HP_MAX;

	m_att = BOSS_ATT;

	m_state = BOSS_STATE_WAIT;

	m_animPlaySpeed = BOSS_ANIM_PLAYSPEED;

	memset(m_moveCount, 0, sizeof(m_moveCount));
}

void C_BOSS::Load()
{
	m_pos = VGet(0.0f,0.0f,100.0f);

	UpdateModel();

	AttachAnim(0, 2);
}

void C_BOSS::Step()
{
	if (m_isAttack)
	{
		m_isAttack = false;
	}

	UppdateAnim();

	switch (m_state)
	{
	case C_BOSS::BOSS_STATE_WAIT:
		WaitCalc();
		break;
	case C_BOSS::BOSS_STATE_MOVE:
		MoveCalc();
		break;
	case C_BOSS::BOSS_STATE_ATTACK:
		AttackCalc();
		break;
	case C_BOSS::BOSS_STATE_JUMP_ATTACK:
		JumpAttackCalc();
		break;
	case C_BOSS::BOSS_STATE_ROT_ATTACK:
		RotAttackCalc();
		break;
	case C_BOSS::BOSS_STATE_HIT:
		HitCalc();
		break;
	}
}

void C_BOSS::Update()
{
	m_hitWait--;

	for (int i = 0; i < BOSS_STATE_NUM; i++)
	{
		m_moveCount[i]--;
		if (m_moveCount[i] < 0)m_moveCount[i] = 0;
	}

	m_pos = VAdd(m_pos, m_moveVec);

	UpdateModel();

	LoopAnim();


	if (m_hp <= 0)
	{
		m_isActive = false;
	}
}

void C_BOSS::Draw()
{
	if (!m_isActive)return;

	DrawModel();

	DrawSphere3D(GetCenter(), static_cast<float>(m_redius), 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

	if (!m_isAttack)return;

	DrawSphere3D(GetAttackPos(), static_cast<float>(m_attackRedius), 16, GetColor(0, 255, 0), GetColor(255, 0, 0), FALSE);
}

void C_BOSS::Exit()
{
	DettuchAnim();

	DeleteModel();

	m_effHndl = 0;
}

//待機処理
void C_BOSS::WaitCalc()
{

}

//移動処理
void C_BOSS::MoveCalc()
{
	//移動処理
	VECTOR tmp = VSub(m_targetPos, m_pos);

	tmp.y = 0.0f;

	float len = VSize(tmp);

	tmp = VNorm(tmp);

	m_objectData.modelRot.y = atan2f(-tmp.x, -tmp.z);

	m_moveVec = VScale(tmp, BOSS_MOVE_SPEED);

	if (len <= 40.0f)
	{
		m_moveVec = VGet(0, 0, 0);
		m_state = BOSS_STATE_ATTACK;
		m_moveCount[BOSS_STATE_ATTACK] = 60;


		DettuchAnim();

		AttachAnim(0, 0);
	}
	else if (len >= 60.0f && m_moveCount[BOSS_STATE_ROT_ATTACK] == 0)
	{
		m_state = BOSS_STATE_ROT_ATTACK;
		m_moveCount[BOSS_STATE_ROT_ATTACK] = 180;
	}
	else if (len > 100.0f && m_moveCount[BOSS_STATE_JUMP_ATTACK] == 0)
	{
		m_state = BOSS_STATE_JUMP_ATTACK;
		m_moveCount[BOSS_STATE_JUMP_ATTACK] = 120;
		m_pos.y = 30.0f;
	}
}

//攻撃処理
void C_BOSS::AttackCalc()
{
	//攻撃処理
	if (m_animPlayTime >= m_animAllPlayTime)
	{
		m_isAttack = true;

		m_att = 20;

		m_attackRedius = 32;

		DettuchAnim();

		AttachAnim(0, 2);

		m_moveCount[BOSS_STATE_ATTACK] = 120;

		m_prevState = m_state;

		m_state = BOSS_STATE_MOVE;

		//CEffekseerCtrl::Request(0, GetAttackPos(), false);
	}
}

//ジャンプ攻撃処理
void C_BOSS::JumpAttackCalc()
{
	//移動処理
	VECTOR tmp = VSub(m_targetPos, m_pos);

	tmp.y = 0.0f;

	float len = VSize(tmp);

	tmp = VNorm(tmp);

	m_objectData.modelRot.y = atan2f(-tmp.x, -tmp.z);

	m_moveVec = VScale(tmp, 1.0f);

	//攻撃処理
	if (m_moveCount[BOSS_STATE_JUMP_ATTACK] == 0)
	{
		m_isAttack = true;
		m_att = 30;
		m_attackRedius = 32;
	}

	if (m_pos.y > 0.0f && m_state == BOSS_STATE_JUMP_ATTACK && m_isAttack)
	{
		m_pos.y -= 0.5f;
		if (m_pos.y <= 0.0f) {
			m_pos.y = 0.0f;
			m_prevState = m_state;
			m_state = BOSS_STATE_MOVE;
			m_moveCount[BOSS_STATE_JUMP_ATTACK] = 120;
			//CEffekseerCtrl::Request(0, GetAttackPos(), false);
		}
	}
}

//回転攻撃処理
void C_BOSS::RotAttackCalc()
{
	//移動処理
	VECTOR tmp = VSub(m_targetPos, m_pos);

	tmp.y = 0.0f;

	float len = VSize(tmp);

	tmp = VNorm(tmp);

	m_objectData.modelRot.y += 0.01f;

	m_moveVec = VScale(tmp, 1.0f);

	//攻撃処理
	if (m_moveCount[BOSS_STATE_ROT_ATTACK] > 0)
	{
		m_isAttack = true;
		m_attackRedius = 64;
		m_att = 10;
	}
	else if (m_moveCount[BOSS_STATE_ROT_ATTACK] < 120/* || len <= 40*/)
	{
		m_prevState = m_state;
		m_state = BOSS_STATE_MOVE;
		m_moveCount[BOSS_STATE_ROT_ATTACK] = 180;
		//CEffekseerCtrl::Request(0, GetAttackPos(), false);
	}
}

//被弾処理
void C_BOSS::HitCalc()
{
	//ノックバックの移動ベクトルを計算
	m_pos = VAdd(m_pos, m_knockBackSpeed);

	//ノックバックを徐々に減衰させる
	m_knockBackSpeed = VScale(m_knockBackSpeed, 0.9f);

	//一定速度よりも遅くなったらノックバック終了
	if (VSize(m_knockBackSpeed) < 0.1f)
	{
		m_knockBackSpeed = { 0 };
		m_state = BOSS_STATE_MOVE;
	}
}

void C_BOSS::KnockBackCalc()
{
	//ノックバックの移動ベクトルを計算
	m_pos = VAdd(m_pos, m_knockBackSpeed);

	//ノックバックを徐々に減衰させる
	m_knockBackSpeed = VScale(m_knockBackSpeed, 0.9f);

	//一定速度よりも遅くなったらノックバック終了
	if (VSize(m_knockBackSpeed) < 0.1f)
	{
		m_state = BOSS_STATE_MOVE;
	}
}

//ダメージ判定処理
void C_BOSS::DamageCalc(int att)
{
	if (m_hitWait <= 0)
	{
		m_hp -= att;
		m_hitWait = 60;
		if(m_state == BOSS_STATE_ATTACK || m_state == BOSS_STATE_MOVE)m_state = BOSS_STATE_HIT;
	}
}

void C_BOSS::AddPos(VECTOR _addPos)
{
	m_pos = VAdd(m_pos, _addPos);
}

VECTOR C_BOSS::GetAttackPos()
{
	VECTOR tmp;

	tmp = VGet(0.0f, 0.0f, 10.0f);
	MATRIX	mat1, mat2;
	mat1 = MGetTranslate(tmp);
	mat2 = MGetRotY(m_objectData.modelRot.y);
	mat1 = MMult(mat1, mat2);
	tmp = VGet(-mat1.m[3][0], mat1.m[3][1], -mat1.m[3][2]);

	tmp = VAdd(m_pos, tmp);

	switch (m_prevState)
	{
	case C_BOSS::BOSS_STATE_JUMP_ATTACK:
	case C_BOSS::BOSS_STATE_ROT_ATTACK:
		tmp = m_pos;
	}

	return tmp;
}

int C_BOSS::GetAtt()
{
	return m_att;
}