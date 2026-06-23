#include "game/manager/map_manager.h"
#include "game/collision/collision_manager.h"
#include "game/object/static/sky.h"
#include "game/object/static/block.h"

#include "hndlmanager/3Dhndlmanager.h"
#include "draw_polygon/draw_polygon.h"

using namespace std;

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
	/*int tmp = c_globalData->GetStageData()->stage_index;*/
	//m_stageLoader.LoadMapData(const_cast<char*>(MAP_FILE_PATH[tmp]));
	//m_stageLoader.LoadObject(c_objectList);

	C_VOXEL::T_VOXEL_DATA tmp = { 0 };
	tmp.scale = VGet(0.1f, 0.1f, 0.1f);

	c_world = make_shared<C_VOXEL_WORLD>();

	c_world->CreateWorld();

	shared_ptr<C_OBJECT_BASE> sky = make_shared<C_SKY>();
	sky->Init();
	sky->Load();
	c_objectList.push_back(sky);

	C_COLLISION_MANAGER* instance = C_COLLISION_MANAGER::GetInstance();
	instance->CopyVoxelWorld(c_world);

	//for (auto itr = c_chunk.GetChunkBegin(); itr != c_chunk.GetChunkEnd(); ++itr)
	//{
	//	if((*itr)->GetIsActive())C_COLLISION_MANAGER::AddObject(*itr);
	//}
}

void C_MAP_MANAGER::Step()
{
	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		(*itr)->Step();
	}

	c_world->Step();
}

void C_MAP_MANAGER::Update()
{
	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		(*itr)->Update();
	}

	c_world->Update();
}

void C_MAP_MANAGER::Draw()
{
	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		(*itr)->Draw();
	}

	c_world->Draw();
}

void C_MAP_MANAGER::Exit()
{
	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		(*itr)->Exit();
	}

	c_world->Exit();

	C_3D_HNDL_MANAGER* incetanse = C_3D_HNDL_MANAGER::GetInstance();
	incetanse->Delete3DModel(SKY_MODEL_PATH);

	c_objectList.clear();
	m_stageLoader.Exit();
}