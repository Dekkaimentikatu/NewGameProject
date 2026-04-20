#include "game/base/object.h"
#include "lib/3Dhndlmanager.h"
#include "lib/2Dhndlmanager.h"

void C_OBJECT_BASE::Init()
{
	m_objectData = { 0 };

	m_modelHndl = -1;	//モデルハンドル

	m_isActive = false;	//生存フラグ
}