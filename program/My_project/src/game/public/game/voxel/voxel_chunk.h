#pragma once
#include <memory>
#include "array/3Darray.h"
#include "game/base/object.h"

constexpr int CHUNK_SIZE_X = 32;

constexpr int CHUNK_SIZE_Y = 16;

constexpr int CHUNK_SIZE_Z = 32;

class C_VOXEL_CHUNK
{
private:

	C_3D_ARRAY<shared_ptr<C_OBJECT_BASE>> m_chunk;

public:

	C_VOXEL_CHUNK(): m_chunk(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z){}

	~C_VOXEL_CHUNK(){}

	shared_ptr<C_OBJECT_BASE> GetVoxel(int _x, int _y, int _z);

	void SetVoxel(int _x, int _y, int _z, shared_ptr<C_OBJECT_BASE> _voxel);

	C_3D_ARRAY<shared_ptr<C_OBJECT_BASE>>::iterator GetChunkBegin() { return m_chunk.begin(); }

	C_3D_ARRAY<shared_ptr<C_OBJECT_BASE>>::iterator GetChunkEnd() { return m_chunk.end(); }
};
