#include "game/voxel/voxel_world.h"


//
void C_VOXEL_WORLD::Init()
{
	m_chunkNumX = 0;
	m_chunkNumZ = 0;

	m_chunkSizeX = 0;
	m_chunkSizeY = 0;
	m_chunkSizeZ = 0;
}

//ワールドの生成
void C_VOXEL_WORLD::CreateWorld(int _chunkNumX, int _chunkNumZ, int _chunkSizeX, int _chunkSizeY, int _chunkSizeZ)
{
	m_chunkNumX = _chunkNumX;
	m_chunkNumZ = _chunkNumZ;

	m_chunkCountX = 0;
	m_chunkCountZ = 0;

	m_chunkSizeX = _chunkSizeX;
	m_chunkSizeY = _chunkSizeY;
	m_chunkSizeZ = _chunkSizeZ;

	for (int x = 0; x < m_chunkNumX; x++)
	{
		for (int z = 0; z < m_chunkNumZ; z++)
		{
			C_VOXEL_WORLD::CreateChunk(DEF_WORLD_POS[x][z], _chunkSizeX, _chunkSizeY, _chunkSizeZ, C_VOXEL::BLOCK);
		}
	}

	for (int x = 0; x < m_chunkNumX; x++)
	{
		for (int z = 0; z < m_chunkNumZ; z++)
		{
			CheckDrawFlag(DEF_WORLD_POS[x][z], m_chunkSizeX, m_chunkSizeY, m_chunkSizeZ);
		}
	}
}

//
void C_VOXEL_WORLD::CreateWorld(string _filePath)
{

}

//
void C_VOXEL_WORLD::CreateChunk(T_CHUNK_POS _chunkPos, int _chunkSizeX, int _chunkSizeY, int _chunkSizeZ, C_VOXEL::VOXEL_TYPE _voxelType)
{
	C_VOXEL::T_VOXEL_DATA voxelData = { 0 };
	T_CHUNK_POS chunkPos = { 0 };

	chunkPos = _chunkPos;

	m_voxelWorld.insert(make_pair(chunkPos, make_unique<C_VOXEL_CHUNK>(_chunkSizeX, _chunkSizeY, _chunkSizeZ)));

	for (int x = 0; x < _chunkSizeX; x++)
	{
		for (int y = 0; y < _chunkSizeY; y++)
		{
			for (int z = 0; z < _chunkSizeZ; z++)
			{
				voxelData.size = BLOCK_SIZE / 2;
				voxelData.pos.x = static_cast<float>(x) * static_cast<float>(BLOCK_SIZE) * static_cast<float>(_chunkPos.x);
				voxelData.pos.y = static_cast<float>(-y) * static_cast<float>(BLOCK_SIZE);
				voxelData.pos.z = static_cast<float>(z) * static_cast<float>(BLOCK_SIZE) * static_cast<float>(_chunkPos.z);
				voxelData.voxelType = _voxelType;
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
void C_VOXEL_WORLD::CheckDrawFlag(T_CHUNK_POS _chunkPos, int _chunkSizeX, int _chunkSizeY, int _chunkSizeZ)
{
	for (int x = 0; x < _chunkSizeX; x++)
	{
		for (int y = 0; y < _chunkSizeY; y++)
		{
			for (int z = 0; z < _chunkSizeZ; z++)
			{
				if (x < _chunkSizeX - 1)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x + 1, y, z, C_VOXEL::RIGHT);
				if (x > 0)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x - 1, y, z, C_VOXEL::LEFT);
				if (y < _chunkSizeY - 1)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y + 1, z, C_VOXEL::DOWN);
				if (y > 0)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y - 1, z, C_VOXEL::UP);
				if (z < _chunkSizeZ - 1)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y, z + 1, C_VOXEL::FRONT);
				if (z > 0)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y, z - 1, C_VOXEL::REAR);
			}
		}
	}
}

//
void C_VOXEL_WORLD::Step()
{


	CheckDrawFlag(DEF_WORLD_POS[0][1], m_chunkSizeX, m_chunkSizeY, m_chunkSizeZ);

	m_chunkCountX++;

	if (m_chunkCountX >= m_chunkNumX)
	{
		m_chunkCountX = m_chunkNumX - 1;
		m_chunkCountZ++;
		if (m_chunkCountZ >= m_chunkCountZ)
		{
			m_chunkCountX = 0;
			m_chunkCountZ = 0;
		}
	}
}

//
void C_VOXEL_WORLD::Update()
{

}

//ポリゴンの描画フラグの更新
void C_VOXEL_WORLD::DrawVoxel(T_CHUNK_POS _chunkPos)
{
	for (int x = 0; x < m_chunkSizeX; x++)
	{
		for (int y = 0; y < m_chunkSizeY; y++)
		{
			for (int z = 0; z < m_chunkSizeZ; z++)
			{
				m_voxelWorld.at(_chunkPos)->GetVoxel(x, y, z)->Draw();
			}
		}
	}
}

//
void C_VOXEL_WORLD::Draw()
{
	//for (int x = 0; x < m_chunkNumX; x++)
	//{
	//	for (int z = 0; z < m_chunkNumZ; z++)
	//	{
	//		DrawVoxel(DEF_WORLD_POS[x][z]);
	//	}
	//}
	DrawVoxel(DEF_WORLD_POS[0][1]);
}

//
void C_VOXEL_WORLD::Exit()
{
	for (int x = 0; x < m_chunkNumX; x++)
	{
		for (int z = 0; z < m_chunkNumZ; z++)
		{
		}
	}
}
