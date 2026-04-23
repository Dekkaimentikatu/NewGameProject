#include "game/UI/result.h"
#include "lib/2Dhndlmanager.h"

//初期化
void C_RESULT::Init(VECTOR _pos)
{

	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_pos = _pos;

	m_hndl1 = 0;
}

//読込
void C_RESULT::LoadAnSync()
{
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	m_hndl1 = inctanse->Get2DImageHndl(RESULT_GRAPH_PATH);
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
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	inctanse->DrawRota(&m_hndl1, m_pos, 0, 1.0f);
}

//終了
void C_RESULT::Exit()
{

}

void C_RESULT::SetSize(int _sizeX, int _sizeY)
{

}