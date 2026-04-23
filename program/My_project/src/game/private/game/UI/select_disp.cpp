#include "game/UI/select_disp.h"
#include "lib/XInput.h"
#include "lib/Input.h"

#include "lib/2Dhndlmanager.h"

//初期化
void C_SELECT_DISP::Init(VECTOR _pos)
{
	c_golobalData = C_GLOBAL_DATA::GetInstace();

	m_index = c_golobalData->GetStageData()->stage_index;

	m_pos = _pos;

	m_pos.x = m_pos.x - (600.0f * m_index);

	memset(m_hndl,0, sizeof(m_hndl));
}

//読込
void C_SELECT_DISP::LoadAnSync()
{
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	for (int i = 0; i < C_MAP_MANAGER::SELECT_STAGE_MAX; i++)
	{
		m_hndl[i] = inctanse->Get2DImageHndl(DISP_GRAPH_PATH[i]);
	}
}

//更新
void C_SELECT_DISP::Step()
{
	if (C_XINPUT::GetButtanInputTrg(DX_INPUT_PAD1, XINPUT_BUTTON_DPAD_RIGHT))
	{
		m_index++;
		m_dispMove.x = -DISP_MOVE_SPEED;
	}
	else if (C_XINPUT::GetButtanInputTrg(DX_INPUT_PAD1, XINPUT_BUTTON_DPAD_LEFT))
	{
		m_index--;
		m_dispMove.x = DISP_MOVE_SPEED;
	}

	if (m_index < 0)
	{
		m_index = 0;
	}
	else if (m_index > C_MAP_MANAGER::SELECT_STAGE_MAX - 1)
	{
		m_index = C_MAP_MANAGER::SELECT_STAGE_MAX - 1;
	}

	if (m_pos.x == static_cast<float>(WINDOW_CENTER_WIDTH - DISP_MOVE_LIMIT * m_index))
	{
		m_dispMove.x = 0.0f;
		m_pos.x = static_cast<float>(WINDOW_CENTER_WIDTH - DISP_MOVE_LIMIT * m_index);
	}

	for (int i = 0; i < C_MAP_MANAGER::SELECT_STAGE_MAX; i++)
	{
		m_dispScale[i] = 0.8f;
		m_dispPos[i] = VAdd(m_pos, VGet(i * DISP_MOVE_LIMIT, 0, 0));
	}

	if (m_pos.x < static_cast<float>(WINDOW_CENTER_WIDTH - DISP_MOVE_LIMIT * 2))
	{
		m_pos.x = static_cast<float>(WINDOW_CENTER_WIDTH - DISP_MOVE_LIMIT * 2);
	}
	else if (m_pos.x > static_cast<float>(WINDOW_CENTER_WIDTH))
	{
		m_pos.x = static_cast<float>(WINDOW_CENTER_WIDTH);
	}
	m_pos = VAdd(m_pos, m_dispMove);

	c_golobalData->GetStageData()->stage_index = m_index;

	if(m_dispMove.x == 0.0f)m_dispScale[m_index] = 1.0f;
	else c_golobalData->GetStageData()->stage_index = C_MAP_MANAGER::SELECT_STAGE_MAX;
}

//更新確定処理
void C_SELECT_DISP::Update()
{

}

//描画
void C_SELECT_DISP::Draw()
{
	C_2D_HNDL_MANAGER* inctanse = C_2D_HNDL_MANAGER::GetInstance();
	for (int i = 0; i < C_MAP_MANAGER::SELECT_STAGE_MAX; i++)
	{
		inctanse->DrawRota(m_hndl, m_dispPos[i], i,m_dispScale[i]);
	}
}

//終了
void C_SELECT_DISP::Exit()
{

}

void C_SELECT_DISP::SetSize(int _sizeX, int _sizeY)
{

}