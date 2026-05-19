#include "game/manager/map_manager.h"
#include "game/collision/collision_manager.h"
#include "game/object/static/sky.h"
#include "game/object/static/block.h"

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
	/*int tmp = c_globalData->GetStageData()->stage_index;*/
	//m_stageLoader.LoadMapData(const_cast<char*>(MAP_FILE_PATH[tmp]));
	//m_stageLoader.LoadObject(c_objectList);

	C_OBJECT_BASE::T_OBJECT_DATA tmp = {0};
	tmp.modelScale = VGet(0.1f, 0.1f, 0.1f);

	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				tmp.initPos.x = static_cast<float>(x) * 40.0f;
				tmp.initPos.y = static_cast<float>(-y) * 40.0f;
				tmp.initPos.z = static_cast<float>(z) * 40.0f;
				shared_ptr<C_OBJECT_BASE> object = make_shared<C_BLOCK>();
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
				if (x != 0 && y != 0 && z != 0 && x < CHUNK_SIZE_X - 1 && y < CHUNK_SIZE_Y - 1 && z < CHUNK_SIZE_Z - 1)
				{
					if (c_chunk.GetVoxel(x + 1, y, z)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK &&
						c_chunk.GetVoxel(x - 1, y, z)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK &&
						c_chunk.GetVoxel(x, y + 1, z)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK &&
						c_chunk.GetVoxel(x, y - 1, z)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK &&
						c_chunk.GetVoxel(x, y, z + 1)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK &&
						c_chunk.GetVoxel(x, y, z - 1)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK)
					{
						c_chunk.GetVoxel(x, y, z)->SetIsActive(false);
					}
					else c_chunk.GetVoxel(x, y, z)->SetIsActive(true);
				}
			}
		}
	}

	for (auto itr = c_chunk.GetChunkBegin(); itr != c_chunk.GetChunkEnd(); ++itr)
	{
		if((*itr)->GetIsActive())C_COLLISION_MANAGER::AddObject(*itr);
	}
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
				if (x != 0 && y != 0 && z != 0 && x < CHUNK_SIZE_X - 1 && y < CHUNK_SIZE_Y - 1 && z < CHUNK_SIZE_Z - 1)
				{
					if (c_chunk.GetVoxel(x + 1, y, z)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK &&
						c_chunk.GetVoxel(x - 1, y, z)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK &&
						c_chunk.GetVoxel(x, y + 1, z)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK &&
						c_chunk.GetVoxel(x, y - 1, z)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK &&
						c_chunk.GetVoxel(x, y, z + 1)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK &&
						c_chunk.GetVoxel(x, y, z - 1)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK)
					{
						c_chunk.GetVoxel(x, y, z)->SetIsActive(false);
					}
					else c_chunk.GetVoxel(x, y, z)->SetIsActive(true);
				}

				c_chunk.GetVoxel(x, y, z)->Step();
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
		(*itr)->Draw();
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