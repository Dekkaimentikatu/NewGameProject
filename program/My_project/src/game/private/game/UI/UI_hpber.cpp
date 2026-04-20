#include "game/UI/UI_hpber.h"

//初期化
void C_UI_HPBER::Init(VECTOR _pos)
{
	c_drawGrap = C_DRAW_GRAPH::GetInstance();

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_playerData = c_golobalData->GetPlayerData();

	m_pos = _pos;

	m_hndl1 = m_hndl2 = 0;

	m_sizeX = HP_GRAPH_SIZEX;
	m_sizeY = HP_GRAPH_SIZEY;
}

//読込
void C_UI_HPBER::LoadAnSync()
{
	m_hndl1 = c_drawGrap->LoadGraphData("data/graphic/hp_ber.png");
	m_hndl2 = c_drawGrap->LoadGraphData("data/graphic/hp_ber_frame.png");
}

//更新
void C_UI_HPBER::Step()
{
	m_sizeX = HP_GRAPH_SIZEX * m_playerData->hp / m_playerData->hp_max;
}

//更新確定処理
void C_UI_HPBER::Update()
{

}

//描画
void C_UI_HPBER::Draw()
{
	c_drawGrap->DrawRect(m_hndl2, 0, m_pos, 0, 0, HP_GRAPH_SIZEX, m_sizeY);
	c_drawGrap->DrawRect(m_hndl1, 0, m_pos, 0, 0, m_sizeX, m_sizeY);
}

//終了
void C_UI_HPBER::Exit()
{

}

void C_UI_HPBER::SetSize(int _sizeX, int _sizeY)
{
	m_sizeX = HP_GRAPH_SIZEX * (_sizeX / _sizeY);
}