#pragma once
#include <memory>
#include "array/3Darray.h"
#include "game/voxel/voxel.h"

constexpr int CHUNK_SIZE_X = 32;

constexpr int CHUNK_SIZE_Y = 16;

constexpr int CHUNK_SIZE_Z = 32;

class C_VOXEL_CHUNK
{
private:

	//チャンク
	C_3D_ARRAY<std::shared_ptr<C_VOXEL>> m_chunk;

public:

	//コンストラクタ
	C_VOXEL_CHUNK(int _chunkNumX, int _chunkNumY, int _chunkSizeX): m_chunk(_chunkNumX, _chunkNumY, _chunkSizeX){}

	//デストラクタ
	~C_VOXEL_CHUNK(){}

	//ボクセルの取得
	std::shared_ptr<C_VOXEL> GetVoxel(int _x, int _y, int _z);

	//ボクセルの設定
	void SetVoxel(int _x, int _y, int _z, std::shared_ptr<C_VOXEL> _voxel);

	//ボクセルのタイプの設定
	void SetVoxelType(int _x, int _y, int _z, C_VOXEL::VOXEL_TYPE _voxelType);

	//ポリゴンの描画フラグの更新
	void CheckDrawFlag(int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, C_VOXEL::DRAW_POLY_FLAG _flag);

	//チャンクの先頭を取得
	C_3D_ARRAY<std::shared_ptr<C_VOXEL>>::iterator GetChunkBegin() { return m_chunk.begin(); }

	//チャンクの末尾を取得
	C_3D_ARRAY<std::shared_ptr<C_VOXEL>>::iterator GetChunkEnd() { return m_chunk.end(); }
};
