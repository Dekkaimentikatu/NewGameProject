#pragma once

#include "effekseer/effekseer.h"

#include "object.h"

#include "game/data/global_data.h"

class C_ACTOR_BASE : public C_OBJECT_BASE
{
protected:

	//アニメーションのインデックス
	int m_animIndex;

	//アニメーションの再生時間
	float m_animPlayTime;

	//アニメーションの総再生時間
	float m_animAllPlayTime;

	//アニメーションの再生速度
	float m_animPlaySpeed;

	//現在再生しているアニメーション
	int m_nowAnimState;

	//前回再生していたアニメーション
	int m_prveAnimState;

	//目標の座標
	VECTOR m_targetPos;

	//カメラの回転
	VECTOR m_cameraRot;

	//リスポーンフラグ
	bool m_isRespawn;

	//死亡処理
	void DeathCalc();

	//アニメーションのアタッチ
	void AttachAnim(int _animIndex, int _animSrcModelHndl = -1);

	//アニメーションのデタッチ
	void DettuchAnim();

	//アニメーションの更新処理
	void UppdateAnim();

	//アニメーションのループ処理
	void LoopAnim();

	//アニメーションの終了処理
	void EndAnim();

	//ノックバック処理
	virtual void KnockBackCalc() {}

public:

	//コンストラクタ
	C_ACTOR_BASE(int _animIndex = 0, float _animPlayTime = 0.0f, float _animAllPlayTime = 0.0f,
		float _animPlaySpeed = 0.0f, int _nowAnimState = 0, int _prveAnimState = 0,
		VECTOR _targetPos = { 0 }, VECTOR _modelRot = { 0 }, bool _isRespawn = false) :
		m_animIndex(_animIndex), m_animPlayTime(_animPlayTime), m_animAllPlayTime(_animAllPlayTime),
		m_animPlaySpeed(_animPlaySpeed), m_nowAnimState(_nowAnimState), m_prveAnimState(_prveAnimState),
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
};

