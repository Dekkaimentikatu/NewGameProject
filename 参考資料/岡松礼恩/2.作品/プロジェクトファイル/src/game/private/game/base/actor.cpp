#include "game/base/actor.h"

void C_ACTOR_BASE::Init()
{
	C_OBJECT_BASE::Init();

	m_hpMax = 0;				//HPの最大値

	m_hp = 0;					//HP

	m_isActive = true;			//生存フラグ

}

void C_ACTOR_BASE::Request(T_OBJECT_DATA _objectData)
{
	m_objectData = _objectData;		//オブジェクトデータの保存
}

int C_ACTOR_BASE::GetAtt()
{
	return m_att;
}