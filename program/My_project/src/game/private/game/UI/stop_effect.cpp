#include "game/UI/stop_effect.h"

constexpr int SPEFF_GRAPH_SIZEX = 512;
constexpr int SPEFF_GRAPH_SIZEY = 16;

//初期化
void C_STOP_EFFECT::Init(VECTOR _pos)
{
	c_drawGrap = C_DRAW_GRAPH::GetInstance();

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_playerData = c_golobalData->GetPlayerData();

	m_pos = _pos;

	m_hndl1 = 0;

	m_sizeX = SPEFF_GRAPH_SIZEX;
	m_sizeY = SPEFF_GRAPH_SIZEY;
}

//読込
void C_STOP_EFFECT::LoadAnSync()
{
	m_hndl1 = c_drawGrap->LoadGraphData("data/graphic/stop_effect.png");
}

//更新
void C_STOP_EFFECT::Step()
{

}

//更新確定処理
void C_STOP_EFFECT::Update()
{

}

//描画
void C_STOP_EFFECT::Draw()
{
	if(m_playerData->isStop)c_drawGrap->DrawRota(m_hndl1, 0, m_pos);
}

//終了
void C_STOP_EFFECT::Exit()
{

}

void C_STOP_EFFECT::SetSize(int _sizeX, int _sizeY)
{

}