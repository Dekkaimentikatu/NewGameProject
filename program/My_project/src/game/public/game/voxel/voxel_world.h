#pragma once

#include <unordered_map>
#include <memory>
#include "game/voxel/voxel.h"

using namespace std;

class C_VOXEL_CHUNK;

class C_VOXEL_WOELD
{
private:

	struct ChunkPos
	{
		int x;
		int z;

		bool operator==(const ChunkPos& other) const
		{
			return x == other.x
				&& z == other.z;
		}
	};

	typedef struct
	{
		//チャンクのアドレス
		C_VOXEL_CHUNK* m_chunk;
		//ワールド上の座標
		ChunkPos m_chunkPos;
	}T_CHUNK_DATA;

	vector<T_CHUNK_DATA> m_voxel_world;

public:

	//
	void Init();
	//
	void CreateChunk(int _chunkNumX, int _chunkNumY, int _chunkSizeX, int _chunkSizeY, int _chunkSizeZ);
	//void CreateChunk(string _filePath);
	//
	void Step();
	//
	void Update();
	//
	void Draw();
	//
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
