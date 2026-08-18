#include "game/voxel/voxel_world.h"
#include "game/voxel/voxel.h"
#include "hndlmanager/2Dhndlmanager.h"
#include "math/mymath.h"
#include "collision/3Dcollision.h"

using namespace std;

//
void C_VOXEL_WORLD::Init()
{

}

//ワールドの生成
void C_VOXEL_WORLD::CreateWorld()
{
	for (int x = 0; x < CHUNK_NUM_X; x++)
	{
		for (int z = 0; z < CHUNK_NUM_Z; z++)
		{
			C_VOXEL_WORLD::CreateChunk(DEF_WORLD_POS[x][z], C_VOXEL::BLOCK);
		}
	}

	for (int x = 0; x < CHUNK_NUM_X; x++)
	{
		for (int z = 0; z < CHUNK_NUM_Z; z++)
		{
			CheckDrawFlag(DEF_WORLD_POS[x][z]);
		}
	}
}

//
void C_VOXEL_WORLD::CreateWorld(string _filePath)
{

}

//
void C_VOXEL_WORLD::CreateChunk(T_CHUNK_POS _chunkPos, C_VOXEL::VOXEL_TYPE _voxelType)
{
	C_VOXEL::T_VOXEL_DATA voxelData = { 0 };
	T_CHUNK_POS chunkPos = { 0 };
	C_2D_HNDL_MANAGER* instance2D = C_2D_HNDL_MANAGER::GetInstance();

	chunkPos = _chunkPos;

	m_voxelWorld.insert(make_pair(chunkPos, make_shared<C_VOXEL_CHUNK>(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z)));

	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				VECTOR offset = CalcDrawOffset(_chunkPos, VGet(x, y, z));
				voxelData.size = BLOCK_SIZE * 0.5f;
				voxelData.pos.x = static_cast<float>(x) * static_cast<float>(BLOCK_SIZE) + static_cast<float>(BLOCK_SIZE) * 0.5f + offset.x;
				voxelData.pos.y = static_cast<float>(y) * static_cast<float>(BLOCK_SIZE) + static_cast<float>(BLOCK_SIZE) * 0.5f;
				voxelData.pos.z = static_cast<float>(z) * static_cast<float>(BLOCK_SIZE) + static_cast<float>(BLOCK_SIZE) * 0.5f + offset.z;
				//voxelData.pos.x = static_cast<float>(x) * static_cast<float>(BLOCK_SIZE) + static_cast<float>(BLOCK_SIZE) * 0.5f - BLOCK_SIZE * CHUNK_SIZE_X * 0.5f;
				//voxelData.pos.y = static_cast<float>(y) * static_cast<float>(BLOCK_SIZE) + static_cast<float>(BLOCK_SIZE) * 0.5f;
				//voxelData.pos.z = static_cast<float>(z) * static_cast<float>(BLOCK_SIZE) + static_cast<float>(BLOCK_SIZE) * 0.5f - BLOCK_SIZE * CHUNK_SIZE_Z * 0.5f;
				if(y < 3)voxelData.voxelType = _voxelType;
				else voxelData.voxelType = C_VOXEL::AIR;
				voxelData.grapHndl = instance2D->Get2DImageHndl(VOXEL_GRAP_PATH);
				shared_ptr<C_VOXEL> object = make_shared<C_VOXEL>();
				object->Init();
				object->Request(voxelData);
				object->Load();
				m_voxelWorld.at(chunkPos)->SetVoxel(x, y, z, object);
			}
		}
	}
}

//ボクセルのポリゴン描画フラグの更新
void C_VOXEL_WORLD::CheckDrawFlag(T_CHUNK_POS _chunkPos)
{
	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				if (x < CHUNK_SIZE_X - 1)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x + 1, y, z, C_VOXEL::LEFT);
				if (x > 0)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x - 1, y, z, C_VOXEL::RIGHT);
				if (y < CHUNK_SIZE_Y - 1)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y + 1, z, C_VOXEL::UP);
				if (y > 0)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y - 1, z, C_VOXEL::DOWN);
				if (z < CHUNK_SIZE_Z - 1)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y, z + 1, C_VOXEL::REAR);
				if (z > 0)m_voxelWorld.at(_chunkPos)->CheckDrawFlag(x, y, z, x, y, z - 1, C_VOXEL::FRONT);
			}
		}
	}
}

//
void C_VOXEL_WORLD::Step()
{
	for (int x = 0; x < CHUNK_NUM_X; x++)
	{
		for (int z = 0; z < CHUNK_NUM_Z; z++)
		{
			CheckDrawFlag(DEF_WORLD_POS[x][z]);
		}
	}
}

//
void C_VOXEL_WORLD::Update()
{

}

//ポリゴンの描画オフセットの計算
VECTOR C_VOXEL_WORLD::CalcDrawOffset(T_CHUNK_POS _chunkPos, VECTOR _offset)
{
	VECTOR drawOffset = { 0 };

	if (_chunkPos.x < 0)
	{
		drawOffset.x = static_cast<float>(CHUNK_SIZE_X) * static_cast<float>(BLOCK_SIZE) * _chunkPos.x;
	}
	else if (_chunkPos.x > 1) drawOffset.x = static_cast<float>(CHUNK_SIZE_X) * static_cast<float>(BLOCK_SIZE) * _chunkPos.x;

	if (_chunkPos.z < 0)
	{
		drawOffset.z = static_cast<float>(CHUNK_SIZE_Z) * static_cast<float>(BLOCK_SIZE) * _chunkPos.z;
	}
	else if (_chunkPos.z > 1) drawOffset.z = static_cast<float>(CHUNK_SIZE_Z) * static_cast<float>(BLOCK_SIZE) * _chunkPos.z;

	return drawOffset;
}

//ポリゴンの描画フラグの更新
void C_VOXEL_WORLD::DrawVoxel(T_CHUNK_POS _chunkPos)
{
	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				m_voxelWorld.at(_chunkPos)->GetVoxel(x, y, z)->Draw();
			}
		}
	}
}

//
void C_VOXEL_WORLD::Draw()
{
	for (int x = 0; x < CHUNK_NUM_X; x++)
	{
		for (int z = 0; z < CHUNK_NUM_Z; z++)
		{
			DrawVoxel(DEF_WORLD_POS[x][z]);
		}
	}
}

//
void C_VOXEL_WORLD::Exit()
{
	for (int x = 0; x < CHUNK_NUM_X; x++)
	{
		for (int z = 0; z < CHUNK_NUM_Z; z++)
		{
		}
	}
}

bool RayVsAABB(VECTOR origin, VECTOR dir, VECTOR minB, VECTOR maxB, float& tEnter, float& tExit)
{
    tEnter = 0.0f;
    tExit = FLT_MAX;

    for (int axis = 0; axis < 3; axis++)
    {
        float o;
        float d;
        float minV;
        float maxV;

        switch (axis)
        {
        case 0:
            o = origin.x;
            d = dir.x;
            minV = minB.x;
            maxV = maxB.x;
            break;

        case 1:
            o = origin.y;
            d = dir.y;
            minV = minB.y;
            maxV = maxB.y;
            break;

        default:
            o = origin.z;
            d = dir.z;
            minV = minB.z;
            maxV = maxB.z;
            break;
        }

        if (fabsf(d) < 1e-6f)
        {
            if (o < minV || o > maxV)
                return false;

            continue;
        }

        float invD = 1.0f / d;

        float t1 = (minV - o) * invD;
        float t2 = (maxV - o) * invD;

        if (t1 > t2)
            std::swap(t1, t2);

        tEnter = (std::max)(tEnter, t1);
        tExit = (std::min)(tExit, t2);

        if (tEnter > tExit)
            return false;
    }

    return true;
}

bool C_VOXEL_WORLD::IsSolidVoxel(int* _x, int* _y, int* _z, T_CHUNK_POS& _pos)
{
	//チャンクを取得
	weak_ptr<C_VOXEL_CHUNK> chunk = GetChunk(_pos);

	//チャンクが存在しない場合は空のボクセルとみなす
	if (chunk.expired())return false;

	//ローカル座標を計算
	int localX = C_MY_MATH::Mod(*_x, CHUNK_SIZE_X - 1);
	int localY = C_MY_MATH::Mod(*_y, CHUNK_SIZE_Y - 1);
	int localZ = C_MY_MATH::Mod(*_z, CHUNK_SIZE_Z - 1);

    //置くべきボクセルの座標が範囲外なら処理を抜ける
    if (localX >= CHUNK_SIZE_X || localX < 0)return false;
    if (localY >= CHUNK_SIZE_Y || localY < 0)return false;
    if (localZ >= CHUNK_SIZE_Z || localZ < 0)return false;

	//ローカル座標が範囲外の場合は空のボクセルとみなす
	if(chunk.lock()->GetVoxel(localX, localY, localZ)->GetVoxelType() != C_VOXEL::AIR)
    {
		*_x = localX;
		*_y = localY;
		*_z = localZ;
        return true;
	}
    else return false;
}

bool C_VOXEL_WORLD::RaycastWorld(VECTOR origin, VECTOR dir, float maxDistance)
{
    return true;
}


T_RAYCAST_HIT C_VOXEL_WORLD::RaycastVoxel(VECTOR origin, VECTOR dir, float maxDistance, T_CHUNK_POS _chunkPos)
{
	T_RAYCAST_HIT hit = {0};
	hit.isHit = false;

    int x = (int)floor(origin.x);
    int y = (int)floor(origin.y);
    int z = (int)floor(origin.z);

    int stepX = (dir.x >= 0.0f) ? 1 : -1;
    int stepY = (dir.y >= 0.0f) ? 1 : -1;
    int stepZ = (dir.z >= 0.0f) ? 1 : -1;

    float tDeltaX =
        (dir.x != 0.0f) ? fabsf(1.0f / dir.x) : FLT_MAX;

    float tDeltaY =
        (dir.y != 0.0f) ? fabsf(1.0f / dir.y) : FLT_MAX;

    float tDeltaZ =
        (dir.z != 0.0f) ? fabsf(1.0f / dir.z) : FLT_MAX;

    float nextX =
        (stepX > 0) ? (float)(x + 1) : (float)x;

    float nextY =
        (stepY > 0) ? (float)(y + 1) : (float)y;

    float nextZ =
        (stepZ > 0) ? (float)(z + 1) : (float)z;

    float tMaxX =
        (dir.x != 0.0f)
        ? (nextX - origin.x) / dir.x
        : FLT_MAX;

    float tMaxY =
        (dir.y != 0.0f)
        ? (nextY - origin.y) / dir.y
        : FLT_MAX;

    float tMaxZ =
        (dir.z != 0.0f)
        ? (nextZ - origin.z) / dir.z
        : FLT_MAX;

    VECTOR lastNormal = { 0,0,0 };

	T_CHUNK_POS pos = _chunkPos;

    while (true)
    {
        if (IsSolidVoxel(&x, &y, &z, pos))
        {
            float hitT;

            if (lastNormal.x != 0)
                hitT = tMaxX - tDeltaX;
            else if (lastNormal.y != 0)
                hitT = tMaxY - tDeltaY;
            else
                hitT = tMaxZ - tDeltaZ;

			//衝突フラグを立てる
            hit.isHit = true;

			//ヒットしたボクセルの座標を設定
            hit.voxelX = x;
            hit.voxelY = y;
            hit.voxelZ = z;

			//ヒットしたボクセルのチャンク座標を設定
            hit.pos = pos;

            //ヒットしたボクセルの法線を設定
            hit.normal = lastNormal;

            return hit;
        }

        if (tMaxX < tMaxY)
        {
            if (tMaxX < tMaxZ)
            {
                x += stepX;

                lastNormal =
                {
                    (float)-stepX,
                    0.0f,
                    0.0f
                };

                if (tMaxX > maxDistance)
                    break;

                tMaxX += tDeltaX;
            }
            else
            {
                z += stepZ;

                lastNormal =
                {
                    0.0f,
                    0.0f,
                    (float)-stepZ
                };

                if (tMaxZ > maxDistance)
                    break;

                tMaxZ += tDeltaZ;
            }
        }
        else
        {
            if (tMaxY < tMaxZ)
            {
                y -= stepY;

                lastNormal =
                {
                    0.0f,
                    (float)stepY,
                    0.0f
                };

                if (tMaxY > maxDistance)
                    break;

                tMaxY -= tDeltaY;
            }
            else
            {
                z += stepZ;

                lastNormal =
                {
                    0.0f,
                    0.0f,
                    (float)-stepZ
                };

                if (tMaxZ > maxDistance)
                    continue;

                tMaxZ += tDeltaZ;
            }
        }
    }

    return hit;
}