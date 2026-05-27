#include "game/manager/map_manager.h"
#include "game/collision/collision_manager.h"
#include "game/object/static/sky.h"
#include "game/object/static/block.h"

#include "hndlmanager/3Dhndlmanager.h"
#include "draw_polygon/draw_polygon.h"

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

	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				tmp.size = BLOCK_SIZE / 2;
				tmp.pos.x = static_cast<float>(x) * BLOCK_SIZE;
				tmp.pos.y = static_cast<float>(-y) * BLOCK_SIZE;
				tmp.pos.z = static_cast<float>(z) * BLOCK_SIZE;
				shared_ptr<C_VOXEL> object = make_shared<C_VOXEL>();
				object->Init();
				object->Request(tmp);
				object->Load();
				c_chunk.SetVoxel(x, y, z, object);
			}
		}
	}

	shared_ptr<C_OBJECT_BASE> sky = make_shared<C_SKY>();
	sky->Init();
	sky->Load();
	c_objectList.push_back(sky);

	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				if (x < CHUNK_SIZE_X - 1)c_chunk.CheckDrawFlag(x, y, z, x + 1, y, z, C_VOXEL::LEFT);
				if (x != 0)c_chunk.CheckDrawFlag(x, y, z, x - 1, y, z, C_VOXEL::RIGHT);
				if (y < CHUNK_SIZE_Y - 1)c_chunk.CheckDrawFlag(x, y, z, x, y + 1, z, C_VOXEL::DOWN);
				if (y != 0)c_chunk.CheckDrawFlag(x, y, z, x, y - 1, z, C_VOXEL::UP);
				if (z < CHUNK_SIZE_Z - 1)c_chunk.CheckDrawFlag(x, y, z, x, y, z + 1, C_VOXEL::REAR);
				if (z != 0)c_chunk.CheckDrawFlag(x, y, z, x, y, z - 1, C_VOXEL::FRONT);
			}
		}
	}

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

	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				if (x < CHUNK_SIZE_X - 1)c_chunk.CheckDrawFlag(x, y, z, x + 1, y, z, C_VOXEL::LEFT);
				if (x != 0)c_chunk.CheckDrawFlag(x, y, z, x - 1, y, z, C_VOXEL::RIGHT);
				if (y < CHUNK_SIZE_Y - 1)c_chunk.CheckDrawFlag(x, y, z, x, y + 1, z, C_VOXEL::DOWN);
				if (y != 0)c_chunk.CheckDrawFlag(x, y, z, x, y - 1, z, C_VOXEL::UP);
				if (z < CHUNK_SIZE_Z - 1)c_chunk.CheckDrawFlag(x, y, z, x, y, z + 1, C_VOXEL::REAR);
				if (z != 0)c_chunk.CheckDrawFlag(x, y, z, x, y, z - 1, C_VOXEL::FRONT);
			}
		}
	}
}

void C_MAP_MANAGER::Update()
{
	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		(*itr)->Update();
	}

	for (auto itr = c_chunk.GetChunkBegin(); itr != c_chunk.GetChunkEnd(); ++itr)
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

	for (auto itr = c_chunk.GetChunkBegin(); itr != c_chunk.GetChunkEnd(); ++itr)
	{
		if((*itr)->GetIsActive())(*itr)->Draw();
	}


}

void C_MAP_MANAGER::Exit()
{
	for (auto itr = c_objectList.begin(); itr != c_objectList.end(); ++itr)
	{
		(*itr)->Exit();
	}

	for (auto itr = c_chunk.GetChunkBegin(); itr != c_chunk.GetChunkEnd(); ++itr)
	{
		(*itr)->Exit();
	}

	C_3D_HNDL_MANAGER* incetanse = C_3D_HNDL_MANAGER::GetInstance();
	incetanse->Delete3DModel(SKY_MODEL_PATH);

	c_objectList.clear();
	m_stageLoader.Exit();
}