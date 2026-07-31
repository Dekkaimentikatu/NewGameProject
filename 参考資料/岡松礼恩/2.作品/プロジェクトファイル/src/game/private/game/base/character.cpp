#include "game/base/character.h"

void C_CHARACTER::DeathCalc()
{
	if (m_hp <= 0)m_isActive = false;
}

void C_CHARACTER::AttachAnim(int _animIndex, int _animSrcModelHndl)
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

void C_CHARACTER::DettuchAnim()
{
	MV1DetachAnim(m_modelHndl, m_animIndex);	//アニメーションのデタッチ
}

void C_CHARACTER::UppdateAnim()
{
	m_animPlayTime += m_animPlaySpeed;	//アニメーションの再生時間を更新

	MV1SetAttachAnimTime(m_modelHndl, m_animIndex, m_animPlayTime);	//アニメーションの初期化
}

void C_CHARACTER::LoopAnim()
{
	if (m_animPlayTime >= m_animAllPlayTime)	//再生時間が総再生時間を超えているか
	{
		m_animPlayTime = 0.0f;	//アニメーションの再生時間を初期化

		MV1SetAttachAnimTime(m_modelHndl, m_animIndex, m_animPlayTime);	//アニメーションの初期化
	}
}

void C_CHARACTER::EndAnim()
{
	if (m_animPlayTime >= m_animAllPlayTime)	//再生時間が総再生時間を超えているか
	{
		m_animPlayTime = 0.0f;	//アニメーションの再生時間を初期化

		MV1SetAttachAnimTime(m_modelHndl, m_animIndex, m_animAllPlayTime);	//アニメーションの初期化

		DettuchAnim();	//アニメーションのデタッチ
	}
}