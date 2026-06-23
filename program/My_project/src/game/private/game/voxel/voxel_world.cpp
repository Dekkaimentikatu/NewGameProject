#include "game/voxel/voxel_world.h"
#include "game/voxel/voxel.h"

using namespace std;

//
void C_VOXEL_WORLD::Init()
{

}

//ワールドの生成
void C_VOXEL_WORLD::CreateWorld()
{
	for (int x = 0; x < CHUNK_NUM_X; x++)
	{
		for (int z = 0; z < CHUNK_NUM_Y; z++)
		{
			C_VOXEL_WORLD::CreateChunk(DEF_WORLD_POS[x][z], C_VOXEL::BLOCK);
		}
	}

	for (int x = 0; x < CHUNK_NUM_X; x++)
	{
		for (int z = 0; z < CHUNK_NUM_Y; z++)
		{
			CheckDrawFlag(DEF_WORLD_POS[x][z]);
		}
	}
}

//
void C_VOXEL_WORLD::CreateWorld(string _filePath)
{

}

//
void C_VOXEL_WORLD::CreateChunk(T_CHUNK_POS _chunkPos, C_VOXEL::VOXEL_TYPE _voxelType)
{
	C_VOXEL::T_VOXEL_DATA voxelData = { 0 };
	T_CHUNK_POS chunkPos = { 0 };

	chunkPos = _chunkPos;

	m_voxelWorld.insert(make_pair(chunkPos, make_shared<C_VOXEL_CHUNK>(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z)));

	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				VECTOR offset = CalcDrawOffset(_chunkPos, VGet(x, y, z));
				voxelData.size = BLOCK_SIZE / 2;
				voxelData.pos.x = static_cast<float>(x) * static_cast<float>(BLOCK_SIZE) + static_cast<float>(BLOCK_SIZE / 2) + offset.x;
				voxelData.pos.y = static_cast<float>(y) * static_cast<float>(BLOCK_SIZE);
				voxelData.pos.z = static_cast<float>(z) * static_cast<float>(BLOCK_SIZE) + static_cast<float>(BLOCK_SIZE / 2) + offset.z;
				if(y == 0)voxelData.voxelType = _voxelType;
				else voxelData.voxelType = C_VOXEL::AIR;
				shared_ptr<C_VOXEL> object = make_shared<C_VOXEL>();
				object->Init();
				object->Request(voxelData);
				object->Load();
				m_voxelWorld.at(chunkPos)->SetVoxel(x, y, z, object);
			}
		}
	}
}

//ボクセルのポリゴン描画フラグの更新
void C_VOXEL_WORLD::CheckDrawFlag(T_CHUNK_POS _chunkPos)
{
	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				if (x < CHUNK_SIZE_X - 1)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x + 1, y, z, C_VOXEL::LEFT);
				if (x > 0)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x - 1, y, z, C_VOXEL::RIGHT);
				if (y < CHUNK_SIZE_Y - 1)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y + 1, z, C_VOXEL::DOWN);
				if (y > 0)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y - 1, z, C_VOXEL::UP);
				if (z < CHUNK_SIZE_Z - 1)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y, z + 1, C_VOXEL::REAR);
				if (z > 0)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y, z - 1, C_VOXEL::FRONT);
			}
		}
	}
}

//
void C_VOXEL_WORLD::Step()
{
	for (int x = 0; x < CHUNK_NUM_X; x++)
	{
		for (int z = 0; z < CHUNK_NUM_Y; z++)
		{
			CheckDrawFlag(DEF_WORLD_POS[x][z]);
		}
	}
}

//
void C_VOXEL_WORLD::Update()
{

}

//ポリゴンの描画オフセットの計算
VECTOR C_VOXEL_WORLD::CalcDrawOffset(T_CHUNK_POS _chunkPos, VECTOR _offset)
{
	VECTOR drawOffset = { 0 };

	if (_chunkPos.x < 0)
	{
		drawOffset.x = static_cast<float>(CHUNK_SIZE_X) * static_cast<float>(BLOCK_SIZE) * _chunkPos.x;
	}
	else if (_chunkPos.x > 1) drawOffset.x = static_cast<float>(CHUNK_SIZE_X) * static_cast<float>(BLOCK_SIZE) * _chunkPos.x;

	if (_chunkPos.z < 0)
	{
		drawOffset.z = static_cast<float>(CHUNK_SIZE_Z) * static_cast<float>(BLOCK_SIZE) * _chunkPos.z;
	}
	else if (_chunkPos.z > 1) drawOffset.z = static_cast<float>(CHUNK_SIZE_Z) * static_cast<float>(BLOCK_SIZE) * _chunkPos.z;

	return drawOffset;
}

//ポリゴンの描画フラグの更新
void C_VOXEL_WORLD::DrawVoxel(T_CHUNK_POS _chunkPos)
{
	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				m_voxelWorld.at(_chunkPos)->GetVoxel(x, y, z)->Draw();
			}
		}
	}
}

//
void C_VOXEL_WORLD::Draw()
{
	for (int x = 0; x < CHUNK_NUM_X; x++)
	{
		for (int z = 0; z < CHUNK_NUM_Y; z++)
		{
			DrawVoxel(DEF_WORLD_POS[x][z]);
		}
	}
}

//
void C_VOXEL_WORLD::Exit()
{
	for (int x = 0; x < CHUNK_NUM_X; x++)
	{
		for (int z = 0; z < CHUNK_NUM_Y; z++)
		{
		}
	}
}
