#pragma once

#include <map>
#include <memory>
#include <compare>
#include "game/voxel/voxel.h"
#include "game/voxel/voxel_chunk.h"

using namespace std;

class C_VOXEL_CHUNK;

constexpr int BLOCK_SIZE = 20;

struct T_CHUNK_POS
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

static const T_CHUNK_POS DEF_WORLD_POS[2][2] = {{{ -1, -1,} ,{ -1, 1}},
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

	map<T_CHUNK_POS, unique_ptr<C_VOXEL_CHUNK>> m_voxelWorld;

	int m_chunkNumX;
	int m_chunkNumZ;

	int m_chunkSizeX;
	int m_chunkSizeY;
	int m_chunkSizeZ;

public:

	//初期化
	void Init();
	//ワールドの生成
	void CreateWorld(int _chunkNumX, int _chunkNumZ, int _chunkSizeX, int _chunkSizeY, int _chunkSizeZ);
	//ワールドの生成(データ読み込み)
	void CreateWorld(string _filePath);
	//チャンクの生成
	void CreateChunk(T_CHUNK_POS _chunkPos, int _chunkSizeX, int _chunkSizeY, int _chunkSizeZ, C_VOXEL::VOXEL_TYPE _voxelType);
	//ボクセルのポリゴン描画フラグの更新
	void CheckDrawFlag(T_CHUNK_POS _chunkPos, int _chunkSizeX, int _chunkSizeY, int _chunkSizeZ);
	//更新処理
	void Step();
	//更新確定処理
	void Update();
	//ポリゴンの描画フラグの更新
	void DrawVoxel(T_CHUNK_POS _chunkPos);
	//描画処理
	void Draw();
	//終了処理
	void Exit();

};

//struct ChunkPos
//{
//    int x;
//    int z;
//
//    bool operator==(const ChunkPos& other) const
//    {
//        return x == other.x
//            && z == other.z;
//    }
//};
//
//template<>
//struct hash<ChunkPos>
//{
//    size_t operator()(const ChunkPos& p) const
//    {
//        return
//            (hash<int>()(p.x) << 1)
//            ^ hash<int>()(p.z);
//    }
//};
//
//static int FloorDiv(int a, int b)
//{
//    int result = a / b;
//
//    if ((a ^ b) < 0 && a % b)
//    {
//        --result;
//    }
//
//    return result;
//}
//
//static int Mod(int a, int b)
//{
//    int m = a % b;
//
//    if (m < 0)
//    {
//        m += b;
//    }
//
//    return m;
//}
//
//class C_VOXEL_WOELD
//{
//public:
//
//
//
//    C_VOXEL_CHUNK* GetChunk(int chunkX, int chunkZ);
//
//    C_VOXEL_CHUNK& CreateChunk(int chunkX, int chunkZ);
//
//    C_VOXEL& GetVoxel(int worldX, int worldY, int worldZ);
//
//    void SetVoxel(
//        int worldX,
//        int worldY,
//        int worldZ,
//        C_VOXEL::VOXEL_TYPE type);
//
//private:
//
//    std::unordered_map<
//        ChunkPos,
//        std::unique_ptr<C_VOXEL_CHUNK>
//    > chunks;
//};
