#include "game/UI/load_anim.h"
#include "lib/2Dhndlmanager.h"

//初期化
void C_LOAD_ANIM::Init(VECTOR _pos)
{
	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_pos = _pos;

	m_index = 0;
}

//
void C_LOAD_ANIM::LoadSync()
{
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();

	for (int i = 0; i < LOAD_GRAPH_MAX; i++)
	{
		m_hndl[i] = inctanse->Get2DImageHndl(LOAD_GRAPH_PATH, i);
	}
}

//読込
void C_LOAD_ANIM::LoadAnSync()
{

}

void C_LOAD_ANIM::StepLoading()
{
	m_index++;
	if (m_index >= LOAD_GRAPH_MAX)m_index = 0;
}

//更新
void C_LOAD_ANIM::Step()
{

}

//更新確定処理
void C_LOAD_ANIM::Update()
{

}

void C_LOAD_ANIM::DrawLoading()
{
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	inctanse->DrawRota(m_hndl, m_pos, m_index, 5.0f);
}

//描画
void C_LOAD_ANIM::Draw()
{

}

//終了
void C_LOAD_ANIM::Exit()
{
	for (int i = 0; i < LOAD_GRAPH_MAX; i++)
	{
		m_hndl[i] = 0;
	}

	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	inctanse->Delete2DData(LOAD_GRAPH_PATH);
}

void C_LOAD_ANIM::SetSize(int _sizeX, int _sizeY)
{

}