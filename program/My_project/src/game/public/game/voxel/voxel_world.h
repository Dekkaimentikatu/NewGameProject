#pragma once

#include <map>
#include <memory>
#include <compare>
#include "game/voxel/voxel.h"
#include "game/voxel/voxel_chunk.h"

class C_VOXEL_CHUNK;

constexpr int BLOCK_SIZE = 20;

constexpr int CHUNK_NUM_X = 2;

constexpr int CHUNK_NUM_Y = 2;


typedef struct T_CHUNK_POS
{
	int x;
	int z;

     bool operator==(const T_CHUNK_POS& other) const
    {
        return x == other.x &&
               z == other.z;
    }

    bool operator<(const T_CHUNK_POS& other) const
    {
        if (x != other.x)
            return x < other.x;

        return z < other.z;
    }
};

static const T_CHUNK_POS DEF_WORLD_POS[CHUNK_NUM_X][CHUNK_NUM_Y] = {{{ -1, -1,} ,{ -1, 1}},
																	{{ 1, -1}, { 1 , 1}}};

class C_VOXEL_WORLD
{
private:

	typedef struct
	{
		//チャンクのアドレス
		C_VOXEL_CHUNK* chunk;
		//ワールド上の座標
		T_CHUNK_POS chunkPos;
	}T_CHUNK_DATA;

	std::map<T_CHUNK_POS, std::shared_ptr<C_VOXEL_CHUNK>> m_voxelWorld;

	//チャンクの生成
	void CreateChunk(T_CHUNK_POS _chunkPos, C_VOXEL::VOXEL_TYPE _voxelType);
	//ボクセルのポリゴン描画フラグの更新
	void CheckDrawFlag(T_CHUNK_POS _chunkPos);
	//ポリゴンの描画フラグの更新
	void DrawVoxel(T_CHUNK_POS _chunkPos);
	//ポリゴンの描画オフセットの計算
	VECTOR CalcDrawOffset(T_CHUNK_POS _chunkPos, VECTOR _offset);

public:

	//初期化
	void Init();
	//ワールドの生成
	void CreateWorld();
	//ワールドの生成(データ読み込み)
	void CreateWorld(std::string _filePath);
	//更新処理
	void Step();
	//更新確定処理
	void Update();
	//描画処理
	void Draw();
	//終了処理
	void Exit();

	// チャンクをポインタで取得（存在しない場合は nullptr を返す）
	std::weak_ptr<C_VOXEL_CHUNK> GetChunk(const T_CHUNK_POS& _chunkPos)
	{
		return m_voxelWorld.at(_chunkPos);
	}
};
