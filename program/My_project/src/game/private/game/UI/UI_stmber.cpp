#include "game/UI/UI_stmber.h"

void C_UI_STMBER::Init(VECTOR _pos)
{
	c_drawGrap = C_DRAW_GRAPH::GetInstance();

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_playerData = c_golobalData->GetPlayerData();

	m_pos = _pos;

	m_hndl1 = m_hndl2 = 0;

	m_sizeX = STM_GRAPH_SIZEX;
	m_sizeY = STM_GRAPH_SIZEY;
}

void C_UI_STMBER::LoadAnSync()
{
	m_hndl1 = c_drawGrap->LoadGraphData("data/graphic/stop_gage.png");
	m_hndl2 = c_drawGrap->LoadGraphData("data/graphic/stop_gage_frame.png");
}

void C_UI_STMBER::Step()
{
	m_percent = 100.0 * (static_cast<double>(m_playerData->stm) / static_cast<double>(m_playerData->stm_max));
}

void C_UI_STMBER::Update()
{

}

void C_UI_STMBER::Draw()
{
	c_drawGrap->DrawCircleGauge(m_hndl2, 0, m_pos, 100.0);
	c_drawGrap->DrawCircleGauge(m_hndl1, 0, m_pos, m_percent);

}