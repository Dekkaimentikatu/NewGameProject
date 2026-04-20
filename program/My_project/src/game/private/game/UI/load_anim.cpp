#include "game/UI/load_anim.h"

constexpr int GRAPH_MAX = 8;

//初期化
void C_LOAD_ANIM::Init(VECTOR _pos)
{
	c_drawGrap = C_DRAW_GRAPH::GetInstance();

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_pos = _pos;

	m_hndl1 = 0;

	m_index = 0;
}

//
void C_LOAD_ANIM::LoadSync()
{
	m_hndl1 = c_drawGrap->LoadGraphData("data/graphic/load_anim.png", GRAPH_MAX, 4, 2, 32, 32);
}

//読込
void C_LOAD_ANIM::LoadAnSync()
{

}

void C_LOAD_ANIM::StepLoading()
{
	m_index++;
	if (m_index >= GRAPH_MAX)m_index = 0;
}

//更新
void C_LOAD_ANIM::Step()
{

}

//更新確定処理
void C_LOAD_ANIM::Update()
{

}

void C_LOAD_ANIM::DrawLoading()
{
	c_drawGrap->DrawRota(m_hndl1, m_index, m_pos, 5.0f);
}

//描画
void C_LOAD_ANIM::Draw()
{

}

//終了
void C_LOAD_ANIM::Exit()
{

}

void C_LOAD_ANIM::SetSize(int _sizeX, int _sizeY)
{

}