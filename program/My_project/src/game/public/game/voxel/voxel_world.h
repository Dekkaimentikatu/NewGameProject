#pragma once

#include <map>
#include <memory>
#include <compare>
#include "game/voxel/voxel.h"
#include "game/voxel/voxel_chunk.h"

constexpr const char* VOXEL_WORLD_FILE_PATH = "data/map/voxel_world.dat";
constexpr const char* VOXEL_GRAP_PATH = "data/graphic/Voxel_Grap_1.png";

class C_VOXEL_CHUNK;

constexpr int BLOCK_SIZE = 20;

constexpr int CHUNK_NUM_X = 1;

constexpr int CHUNK_NUM_Y = 1;


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

typedef struct T_RAYCAST_HIT
{
	//ヒットしたかどうか
	bool isHit;

	//ヒットしたボクセルの座標
	int voxelX;
	int voxelY;
	int voxelZ;

	//ヒットしたボクセルのチャンク座標
	VECTOR pos;

	//ヒットしたボクセルの法線
	VECTOR normal;
};

static const T_CHUNK_POS DEF_WORLD_POS[CHUNK_NUM_X][CHUNK_NUM_Y] = { 0, 0,};

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
	//ボクセルの存在判定
	bool IsSolidVoxel(int x, int y, int z);

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

	//レイキャスト処理
	T_RAYCAST_HIT RaycastVoxel(VECTOR origin, VECTOR dir, float maxDistance);

	// チャンクをポインタで取得（存在しない場合は nullptr を返す）
	std::weak_ptr<C_VOXEL_CHUNK> GetChunk(const T_CHUNK_POS& _chunkPos)
	{
		return m_voxelWorld.at(_chunkPos);
	}
};
