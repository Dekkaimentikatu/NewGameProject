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



int C_ACTOR_BASE::GetAtt()
{
	return m_att;
}