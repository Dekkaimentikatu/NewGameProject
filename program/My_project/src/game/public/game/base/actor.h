#pragma once

#include "effekseer/effekseer.h"

#include "object.h"

#include "game/data/global_data.h"

class C_ACTOR_BASE : public C_OBJECT_BASE
{
protected:

	//HP
	int m_hp;

	//HP最大値
	int m_hpMax;

	//攻撃力
	int m_att;

	//ジャンプ中フラグ
	bool m_isJump;

	//当たり判定フラグ
	bool m_isHit;

	//攻撃中フラグ
	bool m_isAttack;

	//目標の座標
	VECTOR m_targetPos;

	//カメラの回転
	VECTOR m_cameraRot;

	//リスポーンフラグ
	bool m_isRespawn;

	//当たり判定待機時間
	int m_hitWait;

	//攻撃待機時間
	float m_attackWait;

	//攻撃判定の半径
	int m_attackRedius;



public:

	//コンストラクタ
	C_ACTOR_BASE(VECTOR _targetPos = { 0 }, VECTOR _modelRot = { 0 }, bool _isRespawn = false) :
		m_targetPos(_targetPos), m_cameraRot(_modelRot), m_isRespawn(_isRespawn) { }

	//デストラクタ
	virtual ~C_ACTOR_BASE() {}

	//初期化
	virtual void Init();

	//読込
	virtual void Load() = 0;

	//更新
	virtual void Step() = 0;

	//更新確定
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;

	//終了
	virtual void Exit() = 0;

	//ダメージ判定処理
	virtual void DamageCalc(int att) { m_hp -= att; }

	//ATT取得
	virtual int GetAtt();

	//攻撃中フラグ設定
	inline void SetIsAttack(const bool _isAttack)
	{
		m_isAttack = _isAttack;
	}

	//攻撃中フラグ取得
	inline bool GetIsAttack() const
	{
		return m_isAttack;
	}

	//攻撃判定の半径取得
	inline int GetAttackRedius() const
	{
		return m_attackRedius;
	}

	//HP取得
	inline int GetHp() const
	{
		return m_hp;
	}

	//HP設定
	inline void SetHp(int _hp)
	{
		m_hp = _hp;
	}

	inline void SetTargetPos(VECTOR _targetPos)
	{
		m_targetPos = _targetPos;
	}

	inline VECTOR GetTargetPos()
	{
		return m_targetPos;
	}

	inline VECTOR GetCameraRot() const
	{
		return m_cameraRot;
	}

	inline void SetCameraRota(VECTOR _cameraRota)
	{
		m_cameraRot = _cameraRota;
	}

	inline void SetStatus(int _hpMax)
	{
		m_hpMax = _hpMax;
		m_hp = m_hpMax;
	}

	void Request(T_OBJECT_DATA _objectData);

	//攻撃判定の座標取得
	inline virtual VECTOR GetAttackPos() const
	{
		VECTOR tmp = VGet(0.0f, 0.0f, static_cast<float>(m_redius));
		MATRIX	mat1, mat2;
		mat1 = MGetTranslate(tmp);
		mat2 = MGetRotY(m_objectData.modelRot.y);
		mat1 = MMult(mat1, mat2);
		tmp = VGet(-mat1.m[3][0], mat1.m[3][1], -mat1.m[3][2]);

		return VAdd(m_pos, tmp);
	}
};

