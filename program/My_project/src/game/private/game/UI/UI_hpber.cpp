#include "game/UI/UI_hpber.h"
#include "lib/2Dhndlmanager.h"

//初期化
void C_UI_HPBER::Init(VECTOR _pos)
{
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
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	m_hndl1 = inctanse->Get2DImageHndl(HP_GRAPH_PATH[0]);
	m_hndl2 = inctanse->Get2DImageHndl(HP_GRAPH_PATH[1]);
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
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	inctanse->DrawRect(&m_hndl2, m_pos, 0, 0, HP_GRAPH_SIZEX, m_sizeY);
	inctanse->DrawRect(&m_hndl1, m_pos, 0, 0, m_sizeX, m_sizeY);
}

//終了
void C_UI_HPBER::Exit()
{

}

void C_UI_HPBER::SetSize(int _sizeX, int _sizeY)
{
	m_sizeX = HP_GRAPH_SIZEX * (_sizeX / _sizeY);
}