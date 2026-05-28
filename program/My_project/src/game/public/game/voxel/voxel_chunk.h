#pragma once
#include <memory>
#include "array/3Darray.h"
#include "game/voxel/voxel.h"

constexpr int CHUNK_SIZE_X = 16;

constexpr int CHUNK_SIZE_Y = 16;

constexpr int CHUNK_SIZE_Z = 16;

class C_VOXEL_CHUNK
{
private:

	C_3D_ARRAY<shared_ptr<C_VOXEL>> m_chunk;

public:

	C_VOXEL_CHUNK(): m_chunk(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z){}

	~C_VOXEL_CHUNK(){}

	shared_ptr<C_VOXEL> GetVoxel(int _x, int _y, int _z);

	void SetVoxel(int _x, int _y, int _z, shared_ptr<C_VOXEL> _voxel);

	void SetVoxelType(int _x, int _y, int _z, C_VOXEL::VOXEL_TYPE _voxelType);

	void CheckDrawFlag(int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, C_VOXEL::DRAW_POLY_FLAG _flag);

	C_3D_ARRAY<shared_ptr<C_VOXEL>>::iterator GetChunkBegin() { return m_chunk.begin(); }

	C_3D_ARRAY<shared_ptr<C_VOXEL>>::iterator GetChunkEnd() { return m_chunk.end(); }
};
