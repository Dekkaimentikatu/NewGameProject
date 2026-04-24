#pragma once

#include <math.h>

#include "lib/rand.h"

#include "game/base/character.h"

//攻撃待機時間の最大値
constexpr int ENEMY_ATTACK_WAIT_MAX = 30;

//イージングの加減速度の値
constexpr float ENEMY_SPEED_UP_ADD = 0.5f;

//イージングの上限
constexpr float ENEMY_SPEED_UP_MAX = 1.0f;

//イージングの下限
constexpr float ENEMY_SPEED_UP_MIN = 0.01f;

//移動速度
constexpr float ENEMY_MOVE_SPEED = 0.5f;

//重力
constexpr float ENEMY_GRAVITY = 0.04f;

//落下速度の最大値
constexpr float ENEMY_FALL_SPEED_MAX = -1.0f;

//ノックバック速度の減速率
constexpr float ENEMY_KONCKBACK_SPEED_DECELERATION = 0.9f;

//ノックバック速度の最低値
constexpr float ENEMY_KONCKBACK_SPEED_LEN_MIN = 2.0f;

//ノックバックの速度
constexpr float ENEMY_KONCKBACK_SPEED = 2.0f;

//ノックバックのY成分の速度
constexpr float ENEMY_KONCKBACK_SPEED_Y = 8.0f;

static const char* ENEMY_MODEL_PATH = "data/model/enemy/Enemy.mv1";

class C_ENEMY : public C_CHARACTER
{
private:

	//プレイヤーデータ構造体のポインタ
	C_GLOBAL_DATA::T_PLAYER_DATA* t_playerData;

	//ノックバック処理
	void KnockBackCalc();

	enum ENEMY_STATE
	{
		ENEMY_STATE_MOVE,
		ENEMY_STATE_ATTACK,
		ENEMY_STATE_JUMP_ATTACK,
		ENEMY_STATE_HIT,
		ENEMY_STATE_NUM,
	};

	enum ANIM_STATE
	{
		ANIM_ATTACK,
		ANIM_HIT,
		ANIM_WAIT,
	};

	//現在の敵の状態
	ENEMY_STATE m_nowState;	

	//過去の敵の状態
	ENEMY_STATE m_prevState;	

	//各状態の待機時間
	int m_waitCount[ENEMY_STATE_NUM];

	//ジャンプのスピード
	float m_fallSpeed;

	//エフェクトハンドル
	int m_effektHndl[2];	

	//初期回転座標
	VECTOR m_startRot;

	//イージング速度
	float m_easingSpeed;

	//ノックバックの減算カウント
	float m_konckBackSubCount;

	//落下速度の減算カウント
	float m_fallSubCount;

	//受けたダメージ
	int m_damegeAtt;

	//移動処理
	void MoveCalc();

	//攻撃処理
	void AttackCalc();

	//被弾処理
	void HitCalc();

	//リスポーン処理
	void RespawnCalc();

	//停止処理
	void StopCalc();

	//落下処理
	void FallCalc();

public:

	//コンストラクタ
	C_ENEMY(ENEMY_STATE _enemyState = ENEMY_STATE_MOVE,  float _fallSpeed = 0.0f,
		VECTOR _startRot = {0}, float _easingSpeed = 0.0f, int _damageAtt = 0, float _konckBackSubCount = 0.0f, 
		float _fallSubCount = 0.0f) :
	m_nowState(_enemyState), m_prevState(_enemyState), m_waitCount(), m_fallSpeed(_fallSpeed), m_effektHndl(),
	m_startRot(_startRot), m_easingSpeed(_easingSpeed), m_damegeAtt(_damageAtt), t_playerData(nullptr),
	m_konckBackSubCount(_konckBackSubCount), m_fallSubCount(_fallSubCount){ }

	//デストラクタ
	~C_ENEMY() {}

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

	//座標の加算
	void AddPos(VECTOR _addPos);

	//リクエスト処理
	void Request(T_OBJECT_DATA _objectData);

	//ATT取得
	int GetAtt() const;

	void SetKonckBackSpeed(VECTOR _knockBackSpeed);

	void SetEffectHndl(int _effektHndl, int _index) { m_effektHndl[_index] = _effektHndl; }


};

