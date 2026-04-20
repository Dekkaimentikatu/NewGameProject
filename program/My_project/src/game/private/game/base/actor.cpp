#include "game/base/actor.h"

void C_ACTOR_BASE::Init()
{
	C_OBJECT_BASE::Init();

	m_hpMax = 0;				//HPの最大値

	m_hp = 0;					//HP

	m_animIndex = 0;			//アニメーションのインデックス

	m_animPlayTime = 0;			//アニメーションの再生時間

	m_animAllPlayTime = 0;		//アニメーションの総再生時間

	m_animPlaySpeed = 1;		//アニメーションの再生速度

	m_isActive = true;			//生存フラグ

}

void C_ACTOR_BASE::DeathCalc()
{
	if (m_hp <= 0)m_isActive = false;
}

void C_ACTOR_BASE::AttachAnim(int _animIndex, int _animSrcModelHndl)
{
	//ひとつ前のアニメーションと同じであれば再生しない
	if (m_prveAnimState == _animIndex)return;

	//現在のアニメーションに更新
	m_prveAnimState = _animIndex;

	//アニメーションの再生時間を初期化
	m_animPlayTime = 0.0f;

	//アニメーションのアタッチ
	m_animIndex = MV1AttachAnim(m_modelHndl, _animIndex, _animSrcModelHndl);

	//アニメーションの総再生時間を取得　
	m_animAllPlayTime = MV1GetAnimTotalTime(m_modelHndl, _animIndex);
}

void C_ACTOR_BASE::DettuchAnim()
{
	MV1DetachAnim(m_modelHndl, m_animIndex);	//アニメーションのデタッチ
}

void C_ACTOR_BASE::UppdateAnim()
{
	m_animPlayTime += m_animPlaySpeed;	//アニメーションの再生時間を更新

	MV1SetAttachAnimTime(m_modelHndl, m_animIndex, m_animPlayTime);	//アニメーションの初期化
}

void C_ACTOR_BASE::LoopAnim()
{
	if (m_animPlayTime >= m_animAllPlayTime)	//再生時間が総再生時間を超えているか
	{
		m_animPlayTime = 0.0f;	//アニメーションの再生時間を初期化

		MV1SetAttachAnimTime(m_modelHndl, m_animIndex, m_animPlayTime);	//アニメーションの初期化
	}
}

void C_ACTOR_BASE::EndAnim()
{
	if (m_animPlayTime >= m_animAllPlayTime)	//再生時間が総再生時間を超えているか
	{
		m_animPlayTime = 0.0f;	//アニメーションの再生時間を初期化

		MV1SetAttachAnimTime(m_modelHndl, m_animIndex, m_animAllPlayTime);	//アニメーションの初期化

		DettuchAnim();	//アニメーションのデタッチ
	}
}