#pragma once
#include "game/base/actor.h"

class C_CHARACTER : public C_ACTOR_BASE
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

	C_CHARACTER(int _animIndex = 0, float _animPlayTime = 0, float _animAllPlayTime = 0,
	float _animPlaySpeed = 0, int _nowAnimState = 0, int _prveAnimState = 0):
	m_animIndex(_animIndex), m_animPlayTime(_animPlayTime), m_animAllPlayTime(_animAllPlayTime),
	m_animPlaySpeed(_animPlaySpeed), m_nowAnimState(_nowAnimState), m_prveAnimState(_prveAnimState){}
};