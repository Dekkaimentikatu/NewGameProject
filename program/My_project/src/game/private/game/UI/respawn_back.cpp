#include "game/UI/respawn_back.h"
#include "lib//2Dhndlmanager.h"

//初期化
void C_RESPAWN_BACK::Init(VECTOR _pos)
{
	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_playerData = c_golobalData->GetPlayerData();

	m_pos = _pos;

	m_hndl1 = 0;
}

//読込
void C_RESPAWN_BACK::LoadAnSync()
{
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	m_hndl1 = inctanse->Get2DImageHndl(RESPAWN_GRAPH_PATH);
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
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	if (m_playerData->isRespawn)inctanse->DrawRota(&m_hndl1, m_pos, 0, 1.0f);
}

//終了
void C_RESPAWN_BACK::Exit()
{

}

void C_RESPAWN_BACK::SetSize(int _sizeX, int _sizeY)
{

}