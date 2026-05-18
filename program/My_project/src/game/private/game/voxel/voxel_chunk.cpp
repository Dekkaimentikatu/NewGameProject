#include "game/voxel/voxel_chunk.h"

shared_ptr<C_OBJECT_BASE> C_VOXEL_CHUNK::GetVoxel(int _x, int _y, int _z)
{
	if (_x > CHUNK_SIZE_X ||
		_y > CHUNK_SIZE_Y ||
		_z > CHUNK_SIZE_Z)return nullptr;

	return m_chunk(_x, _y, _z);
}

void C_VOXEL_CHUNK::SetVoxel(int _x, int _y, int _z, shared_ptr<C_OBJECT_BASE> _voxel)
{
	if (_x > CHUNK_SIZE_X ||
		_y > CHUNK_SIZE_Y ||
		_z > CHUNK_SIZE_Z)return;

	m_chunk(_x, _y, _z) = _voxel;
}