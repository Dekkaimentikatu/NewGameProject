#pragma once

#include "game/base/actor.h"

constexpr int PAD_ID = DX_INPUT_PAD1;

constexpr int STM_HEEL_SPD = 5;

constexpr float PLAYER_MOVE_SPEED = 1.3f;

constexpr float PLAYER_ROTATE_SPEED = 0.1f;

constexpr float PLAYER_JUMP_SPEED = 0.5f;

constexpr float PLAYER_FALLSPEED_MAX = 0.15f;

constexpr int PLAYER_RESPAWN_WAIT_MAX = 30;

constexpr int STM_SUB = 20;

constexpr int DODGE_WAIT_MAX = 40;

constexpr float PLAYER_GRAVITY = 0.04f;

constexpr float RESPAWN_POS_Y = -500.0f;

constexpr int JUMPING_WAIT_MAX = 10;

class C_PLAYER : public C_ACTOR_BASE
{
private:

	enum PLAYER_STATE
	{
		PLAYER_STATE_WAIT,		//待機
		PLAYER_STATE_MOVE,		//移動
		PLAYER_STATE_JUMP,		//ジャンプ
		PLAYER_STATE_ATTACK,	//攻撃
		PLAYER_STATE_HIT,		//被弾
		PLAYER_STATE_RESPAWN,	//攻撃
		PLAYER_STATE_NUM,		//状態数
	};

	enum PLAYER_INPUT_STATE
	{
		PLAYER_MOVE_FRONT = 0x0001,
		PLAYER_MOVE_REAR = 0x0002,
		PLAYER_MOVE_LEFT = 0x0004,
		PLAYER_MOVE_RIGHT = 0x0008,
	};

	enum ANIM_STATE
	{
		ANIM_STATE_ATTACK = 19,
		ANIM_STATE_JUMP = 4,
		ANIM_STATE_MOVE = 2,
		ANIM_STATE_WAIT = 1,

		ANIM_STATE_NUM,
	};

	C_GLOBAL_DATA::T_PLAYER_DATA* m_playerData;

	//現在のプレイヤーの状態
	PLAYER_STATE m_nowState;

	//過去のプレイヤーの状態
	PLAYER_STATE m_prevState;

	//スタミナの最大値
	int m_staminaMax;

	//スタミナ
	int m_stamina;

	//リスポーン待機時間
	int m_respawnWait;

	//ジャンプ中待機時間
	int m_jumpingWait;

	//ジャンプのスピード
	float m_fallSpeed;

	//X方向の移動速度
	int m_speedX;

	//Z方向の移動速度
	int m_speedZ;

	//ジャンプフラグ
	bool m_isJump;

	//待機処理
	void WaitCalc();

	//攻撃処理
	void AttackCalc();

	//停止処理
	void StopCalc();

	//落下処理
	void FallCalc();

	//リスポーン処理
	void ReSpawnCalc();

	//移動処理
	void MoveCalc();

	//ジャンプ処理
	void JumpCalc();

	//ジャンプ中処理
	void JumpingCalc();

	//当たり判定処理
	void HitCalc();

	//壁との当たり判定
	void HitCalcWall();

	//天井との当たり判定
	void HitCalcCeiling();

public:
	//デストラクタ
	~C_PLAYER() {}

	//初期化
	void Init();

	//読込
	void Load();

	//更新
	void Step();

	//更新確定
	void Update();

	//描画
	void Draw();

	//終了
	void Exit();

	//ダメージ判定処理
	void DamageCalc(int att);

	void AddPos(VECTOR _addPos);

	//ATT取得
	int GetAtt();
};