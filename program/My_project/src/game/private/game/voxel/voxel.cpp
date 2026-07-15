#include "game/voxel/voxel.h"
#include "draw_polygon/draw_polygon.h"

//初期化
void C_VOXEL::Init()
{
	m_voxelData = { 0 };
	m_drawFlag |= DIR_MASK;
}

//読込
void C_VOXEL::Load()
{

}

//更新
void C_VOXEL::Step()
{

}

//更新確定
void C_VOXEL::Update()
{

}

//描画
void C_VOXEL::Draw()
{
	VECTOR pos = m_voxelData.pos;

	if (m_voxelData.voxelType == AIR)return;

	if (m_drawFlag & UP)
	{
		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(pos, VGet(0.0f, m_voxelData.size, 0.0f)),
			VGet(m_voxelData.size, 0.0f, m_voxelData.size), VGet(-m_voxelData.size, 0.0f, m_voxelData.size),
			VGet(m_voxelData.size, 0.0f, -m_voxelData.size), VGet(-m_voxelData.size, 0.0f, -m_voxelData.size),
			m_voxelData.grapHndl, TRUE);
	}

	if (m_drawFlag & DOWN)
	{
		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(pos, VGet(0.0f, -m_voxelData.size, 0.0f)),
			VGet(m_voxelData.size, 0.0f, m_voxelData.size), VGet(-m_voxelData.size, 0.0f, m_voxelData.size),
			VGet(m_voxelData.size, 0.0f, -m_voxelData.size), VGet(-m_voxelData.size, 0.0f, -m_voxelData.size),
			m_voxelData.grapHndl, TRUE);
	}

	if (m_drawFlag & LEFT)
	{
		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(pos, VGet(m_voxelData.size, 0.0f, 0.0f)),
			VGet(0.0f, m_voxelData.size, m_voxelData.size), VGet(0.0f, -m_voxelData.size, m_voxelData.size),
			VGet(0.0f, m_voxelData.size, -m_voxelData.size), VGet(0.0f, -m_voxelData.size, -m_voxelData.size),
			m_voxelData.grapHndl, TRUE);
	}

	if (m_drawFlag & RIGHT)
	{
		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(pos, VGet(-m_voxelData.size, 0.0f, 0.0f)),
			VGet(0.0f, m_voxelData.size, m_voxelData.size), VGet(0.0f, -m_voxelData.size, m_voxelData.size),
			VGet(0.0f, m_voxelData.size, -m_voxelData.size), VGet(0.0f, -m_voxelData.size, -m_voxelData.size),
			m_voxelData.grapHndl, TRUE);
	}

	if (m_drawFlag & REAR)
	{
		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(pos, VGet(0.0f, 0.0f, m_voxelData.size)),
			VGet(m_voxelData.size, m_voxelData.size, 0.0f), VGet(-m_voxelData.size, m_voxelData.size, 0.0f),
			VGet(m_voxelData.size, -m_voxelData.size, 0.0f), VGet(-m_voxelData.size, -m_voxelData.size, 0.0f),
			m_voxelData.grapHndl, TRUE);
	}

	if (m_drawFlag & FRONT)
	{
		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(pos, VGet(0.0f, 0.0f, -m_voxelData.size)),
			VGet(m_voxelData.size, m_voxelData.size, 0.0f), VGet(-m_voxelData.size, m_voxelData.size, 0.0f),
			VGet(m_voxelData.size, -m_voxelData.size, 0.0f), VGet(-m_voxelData.size, -m_voxelData.size, 0.0f),
			m_voxelData.grapHndl, TRUE);
	}
}

//終了
void C_VOXEL::Exit()
{

}