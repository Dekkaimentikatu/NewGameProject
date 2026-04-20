#include "game/UI/respawn_back.h"

//初期化
void C_RESPAWN_BACK::Init(VECTOR _pos)
{
	c_drawGrap = C_DRAW_GRAPH::GetInstance();

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_playerData = c_golobalData->GetPlayerData();

	m_pos = _pos;

	m_hndl1 = 0;
}

//読込
void C_RESPAWN_BACK::LoadAnSync()
{
	m_hndl1 = c_drawGrap->LoadGraphData("data/graphic/respawn_back.png");
}

//更新
void C_RESPAWN_BACK::Step()
{

}

//更新確定処理
void C_RESPAWN_BACK::Update()
{

}

//描画
void C_RESPAWN_BACK::Draw()
{
	if(m_playerData->isRespawn)c_drawGrap->DrawRota(m_hndl1, 0, m_pos, 1.0f);
}

//終了
void C_RESPAWN_BACK::Exit()
{

}

void C_RESPAWN_BACK::SetSize(int _sizeX, int _sizeY)
{

}