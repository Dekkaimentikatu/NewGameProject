#include "game/UI/UI_stmber.h"
#include "lib/2Dhndlmanager.h"

void C_UI_STMBER::Init(VECTOR _pos)
{
	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_playerData = c_golobalData->GetPlayerData();

	m_pos = _pos;

	m_hndl1 = m_hndl2 = 0;

	m_sizeX = STM_GRAPH_SIZEX;
	m_sizeY = STM_GRAPH_SIZEY;
}

void C_UI_STMBER::LoadAnSync()
{
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	m_hndl1 = inctanse->Get2DImageHndl(STM_GRAPH_PATH[0]);
	m_hndl2 = inctanse->Get2DImageHndl(STM_GRAPH_PATH[1]);
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
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	inctanse->DrawCircleGauge(&m_hndl2, m_pos, 100.0);
	inctanse->DrawCircleGauge(&m_hndl1, m_pos, m_percent);

}