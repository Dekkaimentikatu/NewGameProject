#include "game/voxel/voxel_world.h"
#include "game/voxel/voxel_chunk.h"

//
void C_VOXEL_WOELD::Init()
{

}

//
void C_VOXEL_WOELD::CreateChunk(int _chunkNumX, int _chunkNumY, int _chunkSizeX, int _chunkSizeY, int _chunkSizeZ)
{
	C_VOXEL_CHUNK chunk(_chunkSizeX, _chunkSizeY, _chunkSizeZ);
	C_VOXEL::T_VOXEL_DATA voxelData = { 0 };

	for (int x = 0; x < _chunkSizeX; x++)
	{
		for (int y = 0; y < _chunkSizeY; y++)
		{
			for (int z = 0; z < _chunkSizeZ; z++)
			{
				voxelData.size = BLOCK_SIZE / 2;
				voxelData.pos.x = static_cast<float>(x) * BLOCK_SIZE;
				voxelData.pos.y = static_cast<float>(-y) * BLOCK_SIZE;
				voxelData.pos.z = static_cast<float>(z) * BLOCK_SIZE;
				shared_ptr<C_VOXEL> object = make_shared<C_VOXEL>();
				object->Init();
				object->Request(voxelData);
				object->Load();
				chunk.SetVoxel(x, y, z, object);
			}
		}
	}
	T_CHUNK_DATA chunkData = { 0 };
}

//
void C_VOXEL_WOELD::CreateChunk(string _filePath)
{

}

//
void C_VOXEL_WOELD::Step()
{

}

//
void C_VOXEL_WOELD::Update()
{

}

//
void C_VOXEL_WOELD::Draw()
{

}

//
void C_VOXEL_WOELD::Exit()
{

}
