#include "game/UI/back_ground.h"

//初期化
void C_BACK_GROUND::Init(VECTOR _pos)
{
	c_drawGrap = C_DRAW_GRAPH::GetInstance();

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_pos = _pos;

	m_hndl1 = 0;
}

//読込
void C_BACK_GROUND::LoadAnSync()
{
	m_hndl1 = c_drawGrap->LoadGraphData("data/graphic/background.png");
}

//更新
void C_BACK_GROUND::Step()
{

}

//更新確定処理
void C_BACK_GROUND::Update()
{

}

//描画
void C_BACK_GROUND::Draw()
{
	c_drawGrap->DrawRota(m_hndl1, 0, m_pos, 1.0f, 0);
}

//終了
void C_BACK_GROUND::Exit()
{

}

void C_BACK_GROUND::SetSize(int _sizeX, int _sizeY)
{

}