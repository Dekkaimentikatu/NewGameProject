#pragma once
#include "game/base/character.h"

constexpr float BOSS_MOVE_SPEED = 0.1f;

constexpr float BOSS_SCALE_X = 0.25f;
constexpr float BOSS_SCALE_Y = 0.25f;
constexpr float BOSS_SCALE_Z = 0.25f;

constexpr int BOSS_RADIUS = 32;
constexpr int BOSS_ATTACK_RADIUS = 32;

constexpr int BOSS_HP_MAX = 150;

constexpr int BOSS_ATT = 10;

constexpr float BOSS_ANIM_PLAYSPEED = 0.5f;

class C_BOSS : public C_CHARACTER
{
protected:

	void KnockBackCalc();	//ノックバック処理

	enum BOSS_STATE
	{
		BOSS_STATE_WAIT,			//待機
		BOSS_STATE_MOVE,			//移動
		BOSS_STATE_ATTACK,			//攻撃
		BOSS_STATE_JUMP_ATTACK,		//ジャンプ攻撃
		BOSS_STATE_ROT_ATTACK,		//回転攻撃
		BOSS_STATE_HIT,			//ダメージ
		BOSS_STATE_NUM,
	};

	BOSS_STATE m_state;			//状態

	BOSS_STATE m_prevState;		//前の状態

	int m_moveCount[BOSS_STATE_NUM];	//各状態のカウント

	//待機処理
	void WaitCalc();

	//移動処理
	void MoveCalc();

	//攻撃処理
	void AttackCalc();

	//ジャンプ攻撃処理
	void JumpAttackCalc();

	//回転攻撃処理
	void RotAttackCalc();

	//被弾処理
	void HitCalc();

public:

	void Init();	//初期化

	void Load();	//読込

	void Step();	//更新

	void Update();	//更新確定

	void Draw();	//描画

	void Exit();	//終了

	//ダメージ判定処理
	void DamageCalc(int att);

	void AddPos(VECTOR _addPos);

	VECTOR GetAttackPos();

	//リクエスト処理
	void Request(T_OBJECT_DATA _objectData);

	//ATT取得
	int GetAtt();
};
