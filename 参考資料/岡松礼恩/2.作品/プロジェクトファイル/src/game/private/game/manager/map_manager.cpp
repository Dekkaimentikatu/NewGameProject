#include "game/manager/map_manager.h"
#include "game/collision/collision_manager.h"
#include "game/object/static/sky.h"

#include "hndlmanager/3Dhndlmanager.h"

void C_MAP_MANAGER::Init()
{
	c_objectList.clear();

	c_globalData = C_GLOBAL_DATA::GetInstace();
}

void C_MAP_MANAGER::LoadAnSync()
{
	m_stageLoader.LoadMapResource();
	C_3D_HNDL_MANAGER* incetanse = C_3D_HNDL_MANAGER::GetInstance();
	incetanse->Load3DModel(SKY_MODEL_PATH);

}

void C_MAP_MANAGER::LoadSync()
{
	int tmp = c_globalData->GetStageData()->stage_index;
	m_stageLoader.LoadMapData(const_cast<char*>(MAP_FILE_PATH[tmp]));
	m_stageLoader.LoadObject(c_objectList);

	shared_ptr<C_OBJECT_BASE> sky = make_shared<C_SKY>();
	sky->Init();
	sky->Load();
	c_objectList.push_back(sky);

	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		C_COLLISION_MANAGER::AddObject(*itr);
	}
}

void C_MAP_MANAGER::Step()
{
	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		(*itr)->Step();
	}
}

void C_MAP_MANAGER::Update()
{
	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		(*itr)->Update();
	}
}

void C_MAP_MANAGER::Draw()
{
	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

void C_MAP_MANAGER::Exit()
{
	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		(*itr)->Exit();
	}

	C_3D_HNDL_MANAGER* incetanse = C_3D_HNDL_MANAGER::GetInstance();
	incetanse->Delete3DModel(SKY_MODEL_PATH);

	c_objectList.clear();
	m_stageLoader.Exit();
}