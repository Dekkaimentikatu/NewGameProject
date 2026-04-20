#include "game/UI/result.h"

//初期化
void C_RESULT::Init(VECTOR _pos)
{
	c_drawGrap = C_DRAW_GRAPH::GetInstance();

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_pos = _pos;

	m_hndl1 = 0;
}

//読込
void C_RESULT::LoadAnSync()
{
	m_hndl1 = c_drawGrap->LoadGraphData("data/graphic/result.png");
}

//更新
void C_RESULT::Step()
{

}

//更新確定処理
void C_RESULT::Update()
{

}

//描画
void C_RESULT::Draw()
{
	c_drawGrap->DrawRota(m_hndl1, 0, m_pos, 1.0f);
}

//終了
void C_RESULT::Exit()
{

}

void C_RESULT::SetSize(int _sizeX, int _sizeY)
{

}