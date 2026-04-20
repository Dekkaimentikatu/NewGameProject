#include "game/actor/player/player.h"
#include "lib/input_config.h"
#include "lib/fade.h"
#include "lib/se_manager.h"
#include "lib/3Dhndlmanager.h"

void C_PLAYER::Init()
{
	//グローバルデータの取得
	c_globalData = C_GLOBAL_DATA::GetInstace();

	//プレイヤーデータの取得
	m_playerData = c_globalData->GetPlayerData();

	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelRot = VGet(0.0f, 0.0f, 0.0f);	//回転
	m_objectData.modelScale = VGet(10.0f, 10.0f, 10.0f);	//スケール
	m_redius = 50;	//当たり判定の半径
	m_nowState = PLAYER_STATE_WAIT;	//状態を待機に設定

	//HP、スタミナ、攻撃力の初期化
	m_hp = m_hpMax = m_playerData->hp_max;

	m_stamina = m_staminaMax = m_playerData->stm_max;

	m_att = m_playerData->att;

	//生存フラグの初期化
	m_isActive = true;

	//ジャンプフラグの初期化
	m_isJump = false;

	//リスポーンフラグの初期化
	m_isRespawn = false;

	//アニメーション再生速度の初期化
	m_animPlaySpeed = 1.0f;

	//ジャンプ中待機時間の初期化
	m_jumpingWait = 0;
}

void C_PLAYER::Request(T_OBJECT_DATA _objectData)
{
	m_objectData = _objectData;
}

void C_PLAYER::Load()
{
	C_3D_HNDL_MANAGER* incetans = C_3D_HNDL_MANAGER::GetInstance();

	//座標、回転、スケールの設定
	m_pos = c_globalData->GetFlagData()->StartPos;	//位置

	m_objectData.modelScale = VGet(0.2f, 0.2f, 0.2f);

	m_objectData.modelRot.y = 3.14f;

	//カメラの回転の設定
	m_cameraRot.y = 3.14f;

	//当たり判定の半径の設定
	m_redius = 8;

	//攻撃判定の半径の設定
	m_attackRedius = 16;

	DuplicateModel(incetans->Get3DModelHndl("data/model/player/character-human.mv1"));

	//モデルの更新
	UpdateModel();

	//アニメーションの設定
	AttachAnim(ANIM_STATE_WAIT);

	//オブジェクトタイプをプレイヤーに設定
	m_objectType = OBJECT_TYPE_PLAYER;


}

void C_PLAYER::Step()
{
	//更新処理
	switch (m_nowState)
	{
	case C_PLAYER::PLAYER_STATE_WAIT:
		MoveCalc();
		AttackCalc();
		JumpCalc();
		break;
	case C_PLAYER::PLAYER_STATE_MOVE:
		MoveCalc();
		AttackCalc();
		JumpCalc();

		break;
	case C_PLAYER::PLAYER_STATE_JUMP:
		MoveCalc();
		JumpingCalc();
		break;
	case C_PLAYER::PLAYER_STATE_RESPAWN:
		WaitCalc();
		break;
	}

	//リスポーン処理
	ReSpawnCalc();

	//時間停止処理
	//StopCalc();

	//落下処理
	FallCalc();

	//現在の座標に移動量を加算
	m_pos = VAdd(m_pos, m_moveVec);

	//待機時間の更新
	m_attackWait--;
	m_hitWait--;

	//プレイヤーデータの更新
	m_playerData->hp = m_hp;
	m_playerData->pos = m_pos;
	m_playerData->isRespawn = m_isRespawn;

	//アニメーションの更新
	if (m_prevState != m_nowState)
	{
		m_prevState = m_nowState;
		DettuchAnim();
		AttachAnim(m_nowAnimState);
	}
}

//待機処理
void C_PLAYER::WaitCalc()
{
	//リスポーン待機時間をデクリメント
	m_respawnWait--;

	//待機
	if (m_respawnWait <= 0)
	{
		m_nowState = PLAYER_STATE_WAIT;
	}
}

void C_PLAYER::AttackCalc()
{
	//SEマネージャーのインスタンスを呼ぶ
	C_SE_MANAGER* seManager = C_SE_MANAGER::GetInstance();

	//攻撃処理
	if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::ATTACK))
	{
		m_attackWait = 30;
		//攻撃SEの再生
		seManager->Play(C_SE_MANAGER::SEID_ATTACK);
	}

	//攻撃判定の有無
	if (m_attackWait > 0)
	{
		m_isAttack = true;
		m_nowState = PLAYER_STATE_ATTACK;
		m_nowAnimState = ANIM_STATE_ATTACK;
	}
	else
	{
		m_isAttack = false;
	}
}

void C_PLAYER::StopCalc()
{
	//停止の切り替え
	if ((C_XINPUT::GetButtanInputTrg(PAD_ID, XINPUT_BUTTON_B) || C_INPUT::IsInputTrg(KEY_INPUT_RETURN)) &&
		m_playerData->stm == m_staminaMax)
	{
		m_playerData->isStop = true;
	}
	else if ((C_XINPUT::GetButtanInputTrg(PAD_ID, XINPUT_BUTTON_B) || C_INPUT::IsInputTrg(KEY_INPUT_RETURN)) &&
		m_playerData->isStop)
	{
		m_playerData->isStop = false;
	}

	//スタミナの更新
	//停止中はスタミナをデクリメント
	if (m_playerData->isStop)
	{
		m_playerData->stm--;
	}
	else
	{
		//スタミナがスタミナの最大値以下ならスタミナを回復
		if (m_playerData->stm < m_staminaMax)
		{
			m_playerData->stm += STM_HEEL_SPD;
			//スタミナがスタミナの最大値以上ならスタミナの最大値を代入
			if (m_playerData->stm > m_staminaMax)
			{
				m_playerData->stm = m_staminaMax;
			}
		}
	}

	//リスポーンしたら停止を解除
	if (m_isRespawn == true)
	{
		m_playerData->stm = m_staminaMax;
		m_playerData->isStop = false;
	}

	//スタミナが0以下になったら停止を解除
	if (m_playerData->stm <= 0)
	{
		m_stamina = 0;
		m_playerData->isStop = false;
	}
}

void C_PLAYER::FallCalc()
{
	//落下速度の更新
	m_fallSpeed -= PLAYER_GRAVITY;

	//落下速度が最大値を超えたら最大値で固定
	if (m_fallSpeed < -PLAYER_FALLSPEED_MAX)
	{
		m_fallSpeed = -PLAYER_FALLSPEED_MAX;
	}

	//落下処理
	m_moveVec.y += m_fallSpeed;
}

void C_PLAYER::ReSpawnCalc()
{
	//地面に到達したらリスポーン処理
	if (m_pos.y <= RESPAWN_POS_Y && m_isRespawn == false)
	{
		m_isRespawn = true;

		C_FADE::RequestFadeOut();
	}

	//HPが0以下ならリスポーン処理
	if (m_hp <= 0 && m_isRespawn == false)
	{
		m_isRespawn = true;

		C_FADE::RequestFadeOut();
	}

	//リスポーンフラグが立っている、フェード処理を行っていいない場合リスポーン終了処理
	if (m_isRespawn == true && C_FADE::IsEndFadeOut() && C_FADE::IsEndFadeIn())
	{
		//HPを最大にする
		m_hp = m_hpMax;

		//モデルの座標を設定
		m_pos = c_globalData->GetFlagData()->StartPos;

		//モデルのY軸回転を設定
		m_objectData.modelRot.y = 3.14f;

		//カメラの回転の設定
		m_cameraRot.y = 3.14f;

		//リスポーンフラグを折る
		m_isRespawn = false;

		//移動ベクトルを0にする
		m_moveVec = { 0 };

		//プレイヤーの状態を設定
 		m_nowState = PLAYER_STATE_RESPAWN;

		//アニメーションの状態を設定
		m_nowAnimState = ANIM_STATE_WAIT;

		//リスポーン後待機時間を設定
		m_respawnWait = PLAYER_RESPAWN_WAIT_MAX;

		//フェードインのリクエスト
		C_FADE::RequestFadeIn();
	}
}

void C_PLAYER::MoveCalc()
{
	//移動ベクトルの初期化
	m_moveVec.x = 0.0f;
	m_moveVec.z = 0.0f;

	//移動速度を
	float speed = PLAYER_MOVE_SPEED;

	//ジャンプ中は移動速度を上げる
	if (m_nowState == PLAYER_STATE_JUMP)speed = speed * 1.2f;

	if (C_XINPUT::GetConnectPad(PAD_ID))
	{
		m_moveVec.x = -speed * C_XINPUT::GetLAnalogXInput(PAD_ID);
		m_moveVec.z = -speed * C_XINPUT::GetLAnalogYInput(PAD_ID);
	}
	else
	{
		if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::MOVE_FRONT))
		{
			m_moveVec.z -= speed;
		}
		if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::MOVE_REAR))
		{
			m_moveVec.z += speed;
		}
		if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::MOVE_LEFT))
		{
			m_moveVec.x -= speed;
		}
		if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::MOVE_RIGHT))
		{
			m_moveVec.x += speed;
		}
	}

	// 移動しているようであれば更新
	if (m_moveVec.x != 0.0f || m_moveVec.z != 0.0f)
	{
		// 回転行列を利用してカメラ位置設定
		MATRIX	mat1, mat2;
		mat1 = MGetTranslate(m_moveVec);
		mat2 = MGetRotY(m_cameraRot.y);
		mat1 = MMult(mat1, mat2);
		m_moveVec.x = mat1.m[3][0];
		m_moveVec.z = mat1.m[3][2];
		// 移動速度からY軸回転角度を取得
		m_objectData.modelRot.y = atan2f(-m_moveVec.x, -m_moveVec.z);

		if (m_nowAnimState != ANIM_STATE_JUMP)
		{
			m_nowState = PLAYER_STATE_MOVE;
			m_nowAnimState = ANIM_STATE_MOVE;
		}
	}
	else if (m_nowAnimState != ANIM_STATE_JUMP)
	{
		m_nowState = PLAYER_STATE_WAIT;
		m_nowAnimState = ANIM_STATE_WAIT;
	}
}

void C_PLAYER::JumpCalc()
{
	//ジャンプ処理
	if (C_INPUT_CONFIG::IsButtanInputTrg(C_INPUT_CONFIG::JUMP))
	{
		m_fallSpeed = PLAYER_JUMP_SPEED;
		m_nowState = PLAYER_STATE_JUMP;
		m_nowAnimState = ANIM_STATE_JUMP;
		m_jumpingWait = 0;
		m_isJump = true;
	}
}

//ジャンプ中処理
void C_PLAYER::JumpingCalc()
{
	//SEマネージャーのインスタンスを取得
	C_SE_MANAGER* seManager = C_SE_MANAGER::GetInstance();

	//ジャンプ中待機時間
	if (m_isJump)m_jumpingWait++;

	//待機時間がマックスになったらSEを鳴らす
	if (m_jumpingWait >= JUMPING_WAIT_MAX)
	{
		seManager->Play(C_SE_MANAGER::SEID_JUMP);
		m_isJump = false;
		m_jumpingWait = 0;
	}
}

void C_PLAYER::HitCalc()
{
	m_moveVec.y = 0.0f;
	m_fallSpeed = 0.0f;
	if(m_nowState != PLAYER_STATE_RESPAWN)m_nowState = PLAYER_STATE_WAIT;
	m_nowAnimState = ANIM_STATE_WAIT;
}

//壁との当たり判定
void C_PLAYER::HitCalcWall()
{

}

//天井との当たり判定
void C_PLAYER::HitCalcCeiling()
{
	if(m_moveVec.y > 0.0f)m_moveVec.y = 0.0f;
	m_fallSpeed = -PLAYER_GRAVITY;
}

void C_PLAYER::Update()
{

	UpdateModel();

	UppdateAnim();

	LoopAnim();
}

void C_PLAYER::Draw()
{
	if (!m_isActive)return;

	DrawModel();

#ifdef DEBUG_MODE

	DrawSphere3D(GetCenter(), static_cast<float>(m_redius), 16, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

	if (!m_isAttack)return;

	DrawSphere3D(GetAttackPos(), static_cast<float>(m_attackRedius), 16, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
#endif
}

void C_PLAYER::Exit()
{
	DeleteModel();

	m_effHndl = 0;
}

void C_PLAYER::DamageCalc(int att)
{
	m_hp -= att;
}

void C_PLAYER::AddPos(VECTOR _addPos)
{
	if (_addPos.x == 0.0f && _addPos.y == 0.0f && _addPos.z == 0.0f) return;

	m_pos = VAdd(m_pos, _addPos);
}

int C_PLAYER::GetAtt()
{
	return m_att;
}