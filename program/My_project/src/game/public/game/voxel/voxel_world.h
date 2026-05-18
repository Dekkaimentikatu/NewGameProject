#pragma once

#include <unordered_map>

using namespace std;

class C_VOXEL_CHUNK;

class C_VOXEL_WOELD
{
private:

	typedef struct
	{
		//チャンクのアドレス
		C_VOXEL_CHUNK* m_chunk;
		//ワールド上の座標
		int m_worldPos;
	}T_CHUNK_DATA;

	/*map<T_CHUNK_DATA, int> m_voxel_world;*/
	
};
