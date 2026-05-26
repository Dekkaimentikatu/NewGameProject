#include "game/voxel/voxel_chunk.h"

shared_ptr<C_VOXEL> C_VOXEL_CHUNK::GetVoxel(int _x, int _y, int _z)
{
	if (_x > CHUNK_SIZE_X ||
		_y > CHUNK_SIZE_Y ||
		_z > CHUNK_SIZE_Z)return nullptr;

	return m_chunk(_x, _y, _z);
}

void C_VOXEL_CHUNK::SetVoxel(int _x, int _y, int _z, shared_ptr<C_VOXEL> _voxel)
{
	if (_x > CHUNK_SIZE_X ||
		_y > CHUNK_SIZE_Y ||
		_z > CHUNK_SIZE_Z)return;

	m_chunk(_x, _y, _z) = _voxel;
}

void C_VOXEL_CHUNK::CheckDrawFlag(int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, C_VOXEL::DRAW_POLY_FLAG _flag)
{
	if (this->GetVoxel(_x1, _y1, _z1)->GetVoxelType() == this->GetVoxel(_x2, _y2, _z2)->GetVoxelType())
	{
		this->GetVoxel(_x1, _y1, _z1)->OffFlag(_flag);
	}
	else
	{
		this->GetVoxel(_x1, _y1, _z1)->OnFlag(_flag);
	}

	if (this->GetVoxel(_x1, _y1, _z1)->GetFlag() ^ C_VOXEL::DIR_MASK)this->GetVoxel(_x1, _y1, _z1)->SetIsActive(true);
	else this->GetVoxel(_x1, _y1, _z1)->SetIsActive(false);
}