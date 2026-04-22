#include "game/actor/enemy/enemy.h"
#include "effekseer/effekseer.h"
#include "lib/se_manager.h"
#include "lib/3Dhndlmanager.h"


void C_ENEMY::Init()
{
	//グローバルデータのインスタンスを取得する
	c_globalData = C_GLOBAL_DATA::GetInstace();
	//プレイヤーデータのポインタを取得する
	t_playerData = c_globalData->GetPlayerData();

	//アクターの初期化
	C_ACTOR_BASE::Init();

	//拡大縮小率の初期化
	m_objectData.modelScale = VGet(0.1f, 0.1f, 0.1f);

	//当たり判定用の半径の初期化
	m_redius = 16;
	
	//攻撃判定用の半径の初期化
	m_attackRedius = 16;

	//HPの初期化
	m_hp = 1;

	//攻撃力の初期化
	m_att = 5;

	//状態の初期化
	m_nowState = ENEMY_STATE_MOVE;

	//アニメーションの状態の初期化
	m_animPlaySpeed = 1.0f;

	//被弾待機時間の初期化
	m_hitWait = 0;

	//各行動のカウントの初期化
	memset(m_waitCount, 0, sizeof(m_waitCount));

	//アニメーションの初期化
	AttachAnim(ANIM_WAIT);
}

void C_ENEMY::Load()
{
	//スポーン地点を保存する
	m_startPos = m_pos;

	//拡大縮小率の設定
	m_objectData.modelScale = VGet(0.1f, 0.1f, 0.1f);

	//モデルの更新
	UpdateModel();

	//オブジェクトの種類を敵に設定する
	m_objectType = OBJECT_TYPE_ENEMY;

	//ターゲットの位置をプレイヤーの位置に設定する
	m_targetPos = t_playerData->pos;

	//攻撃待機時間を設定
	m_waitCount[ENEMY_STATE_ATTACK] = ENEMY_ATTACK_WAIT_MAX;
}

void C_ENEMY::Step()
{
	//ターゲットの位置をプレイヤーの位置に更新する
	m_targetPos = t_playerData->pos;

	//状態ごとの処理
	switch (m_nowState)
	{
	case C_ENEMY::ENEMY_STATE_MOVE:
		MoveCalc();
		AttackCalc();
		break;
	case C_ENEMY::ENEMY_STATE_ATTACK:
		AttackCalc();
		break;
	case C_ENEMY::ENEMY_STATE_HIT:
		HitCalc();
		break;
	}

	//時間停止状態の処理
	StopCalc();

	//落下処理
	FallCalc();

	//座標の更新
	m_pos = VAdd(m_pos, m_moveVec);

	//リスポーン処理
	RespawnCalc();

	//アニメーションの更新
	if (m_prevState != m_nowState)
	{
		m_prevState = m_nowState;
		DettuchAnim();
		AttachAnim(m_nowAnimState);
	}
}

void C_ENEMY::RespawnCalc()
{
	//プレイヤーがリスポーンしたら敵もリスポーンする
	if (t_playerData->isRespawn)
	{
		m_pos = m_startPos;
		m_hp = 1;
		m_isActive = true;
	}

	//一定の高さ以下に落ちたらデスポーンする
	if (m_pos.y <= -500.0f)
	{
		m_isActive = false;
	}

	//HPが0以下になったらデスポーンする
	if (m_hp <= 0)
	{
		m_isActive = false;
	}
}

void C_ENEMY::StopCalc()
{
	//時間停止状態の移動速度のイージング
	if (!t_playerData->isStop)
	{
		m_easingSpeed += ENEMY_SPEED_UP_ADD;
		if (m_easingSpeed >= ENEMY_SPEED_UP_MAX)m_easingSpeed = ENEMY_SPEED_UP_MAX;
	}
	else
	{
		m_easingSpeed -= ENEMY_SPEED_UP_ADD;
		if (m_easingSpeed <= ENEMY_SPEED_UP_MIN)m_easingSpeed = ENEMY_SPEED_UP_MIN;
	}
}

void C_ENEMY::FallCalc()
{
	m_fallSubCount += m_easingSpeed;

	//落下速度の更新
	if (m_fallSubCount >= 1.0f)
	{
		m_fallSpeed -= ENEMY_GRAVITY * m_easingSpeed;
		m_fallSubCount = 0.0f;
	}

	//落下速度が一定以上にならないようにする
	if (m_fallSpeed < ENEMY_FALL_SPEED_MAX)
	{
		m_fallSpeed = ENEMY_FALL_SPEED_MAX;
	}

	//落下処理
	m_moveVec.y += m_fallSpeed;

	//被弾判定待機時間をデクリメント
	m_hitWait--;
}

void C_ENEMY::Update()
{
	UpdateModel();

	//時間停止状態ならアニメーションを行わない
	if (t_playerData->isStop)return;
	{
		UppdateAnim();

		LoopAnim();
	}

	//攻撃判定フラグを折る
	m_isAttack = false;
}

void C_ENEMY::Draw()
{
	if (!m_isActive)return;

	DrawModel();

	//デバッグ用の当たり判定の描画
#ifdef DEBUG_MODE
	DrawSphere3D(GetCenter(), static_cast<float>(m_redius), 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

	if (!m_isAttack)return;

	DrawSphere3D(GetAttackPos(), static_cast<float>(m_attackRedius), 16, GetColor(0, 255, 0), GetColor(255, 0, 0), FALSE);
#endif
}

void C_ENEMY::Exit()
{
	//アニメーションのデタッチ
	DettuchAnim();

	//モデルの削除
	DeleteModel();

	//エフェクトのハンドルをリセット
	m_effHndl = 0;
}

//移動処理
void C_ENEMY::MoveCalc()
{
	////時間停止状態なら移動処理を行わない
	if (t_playerData->isStop)
	{
		m_moveVec = { 0 };
		return;
	}

	VECTOR tmp = { 0 };

	//スポーン地点とプレイヤーの位置の差分を計算する
	tmp = VSub(m_startPos, m_targetPos);

	//高さは考慮しない
	tmp.y = 0.0f;

	//スポーン地点とプレイヤーの位置の距離を計算する
	float len = VSize(tmp);

	//スポーン地点とプレイヤーの距離が一定以上ならスポーン地点に向かう
	if (len > 72.0f)
	{
		tmp = VSub(m_startPos, m_pos);
		len = VSize(tmp);
		tmp = VNorm(tmp);
		m_moveVec = VScale(tmp, ENEMY_MOVE_SPEED * m_easingSpeed);

		if (len < 5)
		{
			m_pos.x = m_startPos.x;
			m_pos.z = m_startPos.z;
			m_objectData.modelRot.y = 0.0f;
			m_moveVec = { 0 };
		}
	}
	//スポーン地点とプレイヤーの距離が一定以下ならプレイヤーに向かう
	else
	{
		//移動処理
		tmp = VSub(m_targetPos, m_pos);
		m_objectData.modelRot.y = atan2f(-tmp.x, -tmp.z);
		tmp = VNorm(tmp);
		m_moveVec = VScale(tmp, ENEMY_MOVE_SPEED * m_easingSpeed);
		m_nowState = ENEMY_STATE_MOVE;
	}
}

//攻撃処理
void C_ENEMY::AttackCalc()
{
	//SEマネージャーのインスタンスを取得する
	C_SE_MANAGER* seManager = C_SE_MANAGER::GetInstance();

	//時間停止状態なら攻撃処理を行わない
	if (t_playerData->isStop)return;
	if (!m_isActive)return;

	//攻撃状態のカウントを減らす
	m_waitCount[ENEMY_STATE_ATTACK]--;

	//プレイヤーとの距離を計算する
	float len = VSize(VSub(m_targetPos, m_pos));

	//攻撃状態でない、プレイヤーとの距離が一定以下、攻撃状態のカウントが0以下なら攻撃状態に移行する
	if (m_nowState != ENEMY_STATE_ATTACK && len <= 32.0f && m_waitCount[ENEMY_STATE_ATTACK] <= 0.0f)
	{
		m_moveVec = { 0 };

		m_waitCount[ENEMY_STATE_ATTACK] = 30;

		m_nowAnimState = ANIM_ATTACK;
		m_nowState = ENEMY_STATE_ATTACK;
	}

	//攻撃状態で攻撃待機時間が0以下なら攻撃判定フラグを立てて移動状態に移行する
	if (m_nowState == ENEMY_STATE_ATTACK && m_waitCount[ENEMY_STATE_ATTACK] <= 0.0f)
	{
		m_waitCount[ENEMY_STATE_ATTACK] = 90;
		m_nowState = ENEMY_STATE_MOVE;
		m_nowAnimState = ANIM_WAIT;
		m_isAttack = true;
		seManager->Play(C_SE_MANAGER::SEID_ATTACK);
	}
}

//被弾処理
void C_ENEMY::HitCalc()
{
	KnockBackCalc();
}

void C_ENEMY::KnockBackCalc()
{
	//カウントを増やす
	m_konckBackSubCount += m_easingSpeed;

	//カウントが1の時
	if (m_konckBackSubCount >= 1.0f)
	{
		//ノックバックを徐々に減衰させる
		m_knockBackSpeed = VScale(m_knockBackSpeed, ENEMY_KONCKBACK_SPEED_DECELERATION);
		m_konckBackSubCount = 0.0f;
	}

	//イージングの計算
	VECTOR tmp = VScale(m_knockBackSpeed, m_easingSpeed);

	//ノックバックの移動ベクトルを計算
	m_pos = VAdd(m_pos, tmp);

	//一定速度よりも遅くなったらノックバック終了
	if (VSize(m_knockBackSpeed) <= ENEMY_KONCKBACK_SPEED_LEN_MIN)
	{
		m_knockBackSpeed = { 0 };
		m_nowState = ENEMY_STATE_MOVE;
		m_hp -= m_damegeAtt;
		int tmp = CEffekseerCtrl::Request(m_effektHndl[1], GetCenter(), false);
		CEffekseerCtrl::SetScale(tmp, VGet(5.0f, 5.0f, 5.0f));
	}
}

void C_ENEMY::SetKonckBackSpeed(VECTOR _knockBackSpeed)
{
	// 二点間の距離を取得
	VECTOR vec = VSub(m_pos, _knockBackSpeed);

	//座標の差を正規化
	vec = VNorm(vec);

	//移動ベクトルにめり込んだ距離を乗算
	vec = VScale(vec, ENEMY_KONCKBACK_SPEED);

	vec.y = ENEMY_KONCKBACK_SPEED_Y;

	m_knockBackSpeed = vec;
}

//ダメージ判定処理
void C_ENEMY::DamageCalc(int att)
{
	//被弾後の無敵時間が0以下ならダメージ処理を行う
	if (m_hitWait <= 0)
	{
		//hpを減らす
		m_damegeAtt = att;
		//被弾後の無敵時間を30に設定する
		m_hitWait = 30;
		//状態を被弾状態にする
		m_nowState = ENEMY_STATE_HIT;
		//アニメーションを被弾アニメーションにする
		m_nowAnimState = ANIM_HIT;
		//エフェクトを再生する
		int tmp = CEffekseerCtrl::Request(m_effektHndl[0], GetCenter(), false);
		CEffekseerCtrl::SetScale(tmp, VGet(5.0f, 5.0f, 5.0f));

		KnockBackCalc();
	}
}

void C_ENEMY::AddPos(VECTOR _addPos)
{
	//加算する座標が0の場合は処理を行わない
	if (_addPos.x == 0.0f && _addPos.y == 0.0f && _addPos.z == 0.0f) return;

	//座標を加算する
	m_pos = VAdd(m_pos, _addPos);
	//移動ベクトルをリセットする
	m_moveVec.y = 0.0f;
	//落下速度をリセットする
	m_fallSpeed = 0.0f;
	//ジャンプ攻撃フラグを折る
	m_isJump = false;
}

//リクエスト処理
void C_ENEMY::Request(T_OBJECT_DATA _objectData)
{
	m_objectData = _objectData;
	C_3D_HNDL_MANAGER* instance = C_3D_HNDL_MANAGER::GetInstance();
	m_modelHndl = instance->Get3DModelHndl(ENEMY_MODEL_PATH);
}

int C_ENEMY::GetAtt() const
{
	//攻撃力を返す
	return m_att;
}