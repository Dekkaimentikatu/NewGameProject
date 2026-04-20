#include "game/UI/back_ground.h"
#include "lib/2Dhndlmanager.h"

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
	C_2D_HNDL_MANAGER* instance = C_2D_HNDL_MANAGER::GetInstance();
	instance->Load2DImage("data/graphic/TitleBackGround.png");
	m_hndl1 = instance->Get2DImageHndl("data/graphic/TitleBackGround.png");
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
	C_2D_HNDL_MANAGER* instance = C_2D_HNDL_MANAGER::GetInstance();
	instance->DrawRota(&m_hndl1, m_pos, 0, 1.0f);
}

//終了
void C_BACK_GROUND::Exit()
{
	C_2D_HNDL_MANAGER* instance = C_2D_HNDL_MANAGER::GetInstance();
	instance->Delete2DData("data/graphic/TitleBackGround.png");
}

void C_BACK_GROUND::SetSize(int _sizeX, int _sizeY)
{

}