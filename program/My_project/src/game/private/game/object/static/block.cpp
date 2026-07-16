#include "game/object/static/block.h"
#include "hndlmanager/3Dhndlmanager.h"
#include "draw_polygon/draw_polygon.h"

C_BLOCK::C_BLOCK()
{

}

C_BLOCK::~C_BLOCK()
{

}

void C_BLOCK::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(1.0f, 1.0f, 1.0f);	//スケール
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
}

void C_BLOCK::Request(T_OBJECT_DATA _objectData)
{
	m_pos = _objectData.initPos;
	m_objectData = _objectData;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_isActive = true;
}

void C_BLOCK::Load()
{
	C_3D_HNDL_MANAGER* instace = C_3D_HNDL_MANAGER::GetInstance();
	//DuplicateModel(instace->Get3DModelHndl(BLOCK_MODEL_PATH));
	UpdateModel();
	SetUpCollInfo();
	m_objectType = OBJECT_TYPE_BLCOK;
}

void C_BLOCK::Step()
{

}

void C_BLOCK::Update()
{
	UpdateModel();
	UpdateCollInfo();
}

void C_BLOCK::Draw()
{
	if (m_isActive)
	{

		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(m_pos, VGet(0.0f, 20.0f, 0.0f)),
			VGet(20.0f, 0.0f, 20.0f), VGet(-20, 0.0f, 20.0f),
			VGet(20.0f, 0.0f, -20.0f), VGet(-20.0f, 0.0f, -20.0f),
			DX_NONE_GRAPH, FALSE);

		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(m_pos, VGet(0.0f, -20.0f, 0.0f)),
			VGet(20.0f, 0.0f, 20.0f), VGet(-20, 0.0f, 20.0f),
			VGet(20.0f, 0.0f, -20.0f), VGet(-20.0f, 0.0f, -20.0f),
			DX_NONE_GRAPH, FALSE);

		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(m_pos, VGet(20.0f, 0.0f, 0.0f)),
			VGet(0.0f, 20.0f, 20.0f), VGet(0.0f, -20.0f, 20.0f),
			VGet(0.0f, 20.0f, -20.0f), VGet(0.0f, -20.0f, -20.0f),
			DX_NONE_GRAPH, FALSE);

		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(m_pos, VGet(-20.0f, 0.0f, 0.0f)),
			VGet(0.0f, 20.0f, 20.0f), VGet(0.0f, -20.0f, 20.0f),
			VGet(0.0f, 20.0f, -20.0f), VGet(0.0f, -20.0f, -20.0f),
			DX_NONE_GRAPH, FALSE);

		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(m_pos, VGet(0.0f, 0.0f, 20.0f)),
			VGet(20.0f, 20.0f, 0.0f), VGet(-20.0f, 20.0f, 0.0f),
			VGet(20.0f, -20.0f, 0.0f), VGet(-20.0f, -20.0f, 0.0f),
			DX_NONE_GRAPH, FALSE);

		C_DRAW_POLYGON::DrawPolygonSquare(VAdd(m_pos, VGet(0.0f, 0.0f, -20.0f)),
			VGet(20.0f, 20.0f, 0.0f), VGet(-20.0f, 20.0f, 0.0f),
			VGet(20.0f, -20.0f, 0.0f), VGet(-20.0f, -20.0f, 0.0f),
			DX_NONE_GRAPH, FALSE);
	}
}

void C_BLOCK::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_BLOCK::HitCalc()
{

}