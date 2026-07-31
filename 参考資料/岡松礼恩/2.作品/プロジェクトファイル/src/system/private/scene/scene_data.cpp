#include "scene/scene_data.h"

C_SCENE_DATA* C_SCENE_DATA::m_classInstance = nullptr;

C_SCENE_DATA* C_SCENE_DATA::GetInstance()
{
	if (m_classInstance == nullptr)
	{
		m_classInstance = new C_SCENE_DATA();
	}

	return m_classInstance;
}

void C_SCENE_DATA::DeleteInstance()
{
	if (m_classInstance != nullptr)
	{
		delete m_classInstance;

		m_classInstance = nullptr;
	}
}

void C_SCENE_DATA::Init()
{
	m_sceneType = TITLE;

	m_isEnd = false;

	m_isWait = false;
}