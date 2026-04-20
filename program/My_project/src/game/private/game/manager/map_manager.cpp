#include "game/manager/map_manager.h"
#include "game/collision/collision_manager.h"
#include "game/object/static/sky.h"

void C_MAP_MANAGER::Init()
{
	c_objectArray.clear();

	c_globalData = C_GLOBAL_DATA::GetInstace();
}

void C_MAP_MANAGER::LoadAnSync()
{
	m_stageLoader.LoadMapResource();
}

void C_MAP_MANAGER::LoadSync()
{
	int tmp = c_globalData->GetStageData()->stage_index;
	m_stageLoader.LoadMapData(c_objectArray, const_cast<char*>(MAP_FILE_PATH[tmp]));

	C_SKY* sky = new C_SKY();
	sky->Init();
	sky->Load();
	c_objectArray.push_back(sky);

	for (auto itr = c_objectArray.begin(); itr != c_objectArray.end(); ++itr)
	{
		C_COLLISION_MANAGER::AddObject(*itr);
	}
}

void C_MAP_MANAGER::Step()
{
	for (auto itr = c_objectArray.begin(); itr != c_objectArray.end(); ++itr)
	{
		(*itr)->Step();
	}
}

void C_MAP_MANAGER::Update()
{
	for (auto itr = c_objectArray.begin(); itr != c_objectArray.end(); ++itr)
	{
		(*itr)->Update();
	}
}

void C_MAP_MANAGER::Draw()
{
	for (auto itr = c_objectArray.begin(); itr != c_objectArray.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

void C_MAP_MANAGER::Exit()
{
	for (auto itr = c_objectArray.begin(); itr != c_objectArray.end(); ++itr)
	{
		(*itr)->Exit();
		delete (*itr);
	}

	c_objectArray.clear();
	m_stageLoader.Exit();
}