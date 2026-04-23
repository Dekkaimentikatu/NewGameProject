#include "game/UI/stop_effect.h"
#include "lib/2Dhndlmanager.h"

constexpr int SPEFF_GRAPH_SIZEX = 512;
constexpr int SPEFF_GRAPH_SIZEY = 16;

//初期化
void C_STOP_EFFECT::Init(VECTOR _pos)
{
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
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	m_hndl1 = inctanse->Get2DImageHndl(STOP_GRAPH_PATH);
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
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	m_hndl1 = inctanse->DrawRota(&m_hndl1, m_pos);
}

//終了
void C_STOP_EFFECT::Exit()
{

}

void C_STOP_EFFECT::SetSize(int _sizeX, int _sizeY)
{

}