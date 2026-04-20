#include "mapediter/mapediter.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "lib/input.h"

// ツールバーのボタンの状態
//#define TOOLBUTTON_STATE_ENABLE // 入力可能な状態
//#define TOOLBUTTON_STATE_PRESSED // 押されている状態
//#define TOOLBUTTON_STATE_DISABLE // 入力不可能な状態
//#define TOOLBUTTON_STATE_PRESSED_DISABLE // 押されている状態で、入力不可能な状態

// ツールバーのボタンのタイプ
//#define TOOLBUTTON_TYPE_NORMAL // 普通のボタン
//#define TOOLBUTTON_TYPE_CHECK // 押すごとにＯＮ／ＯＦＦが切り替わるボタン


void C_MAP_EDITER::Init()
{
	m_objectArray.clear();
	m_pos = VGet(0.0f, 0.0f, 0.0f);
	m_scl = VGet(0.1f, 0.1f, 0.1f);
	m_rot = VGet(0.0f, 0.0f, 0.0f);
	m_moveDir = 0;
	m_editerMode = EDITER_MODE_LOADSTAGE;
	m_inputState = INPUT_MODE_X;
	m_inputHndl = -1;
}

void C_MAP_EDITER::LoadAnSync()
{
	m_stageLoader.LoadMapResource();
	m_hndl = MV1LoadModel("data/model/field/pointer.mv1");
}

void C_MAP_EDITER::LoadSync()
{
	MV1SetPosition(m_hndl, m_pos);
	MV1SetScale(m_hndl, VGet(0.1f, 0.1f, 0.1f));
	memcpy(m_filePath, const_cast<char*>(FILE_PATH), sizeof(char[256]));
	memcpy(m_prevfilePath, const_cast<char*>(FILE_PATH), sizeof(char[256]));
	m_stageLoader.LoadMapData(m_objectArray, m_filePath);
	//for (auto itr = m_objectArray.begin(); itr != m_objectArray.end(); ++itr)
	//{
	//	(*itr)->Load();
	//}
}

void C_MAP_EDITER::Step()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	// ウィンドウの背景を半透明に設定
	ImGui::SetNextWindowBgAlpha(0.5f);
	// ウィンドウの位置を設定
	ImGui::SetNextWindowPos(ImVec2(880, 0), ImGuiCond_Always);
	// ウィンドウのサイズを設定
	ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
	// ウィンドウのタイトルを設定して開始
	ImGui::Begin("Stats");
	ImGui::LabelText("", "FPS:%4.2f (%4.2f ms)", 0.0f);
	ImGui::LabelText("", "Camera Pos:(%.2f, %.2f, %.2f )", 0.0f, 0.0f, 0.0f);
	ImGui::Spacing();
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Object"))
	{
		ImGui::SliderInt("ID", &m_index, 0, C_STAGE_LOADER::OBJECT_ID_MAX - 1);
	}
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Pos"))
	{
		ImGui::InputFloat3("Pos", &m_pos.x, "%.3f");
	}
	if (ImGui::CollapsingHeader("Scale"))
	{
		ImGui::InputFloat3("Scale", &m_scl.x, "%.3f");
	}
	if (ImGui::CollapsingHeader("Rot"))
	{
		ImGui::InputFloat3("Rot", &m_rot.x, "%.3f");
	}
	ImGui::Separator();
	if (ImGui::CollapsingHeader("moveLen"))
	{
		ImGui::InputInt("Len", &m_moveLen, 1);
	}
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Loadcsv"))
	{
		ImGui::InputText("FilePath", m_filePath, sizeof(m_filePath));
		ImGui::SameLine();
		if (ImGui::Button("Load")) {
			m_stageLoader.SaveMapData(m_prevfilePath);
			m_stageLoader.DeleteObjectAll();
			DeleteObjectAll();

			memcpy(m_prevfilePath, m_filePath, sizeof(m_filePath));

			m_stageLoader.LoadMapData(m_objectArray, m_filePath);
		}
	}
	ImGui::Separator();
	if (ImGui::Button("Save")) {
		m_stageLoader.SaveMapData(m_filePath);
	}
	ImGui::SameLine();
	if (ImGui::Button("Add")) {
		AddObject();
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete")) {
		DeleteObject();
	}
	ImGui::End();

	MV1SetPosition(m_hndl, m_pos);
}

void C_MAP_EDITER::AddObject()
{
	T_STAGE_DATA tmp;
	tmp.objectID = m_index;
	tmp.posX = m_pos.x;
	tmp.posY = m_pos.y;
	tmp.posZ = m_pos.z;
	tmp.rotX = m_rot.x;
	tmp.rotY = m_rot.y;
	tmp.rotZ = m_rot.z;
	tmp.scaleX = m_scl.x;
	tmp.scaleY = m_scl.y;
	tmp.scaleZ = m_scl.z;
	tmp.moveDir = m_moveDir;
	tmp.moveLen = m_moveLen;
	m_stageLoader.AddObject(tmp, m_objectArray);
}

void C_MAP_EDITER::DeleteObject()
{
	for (auto itr = m_objectArray.begin(); itr != m_objectArray.end(); ++itr)
	{
		if ((*itr)->GetInitPos().x == m_pos.x &&
			(*itr)->GetInitPos().y == m_pos.y &&
			(*itr)->GetInitPos().z == m_pos.z)
		{
			//オブジェクトを削除
			(*itr)->Exit();
			delete (*itr);
			m_objectArray.erase(itr);
			m_stageLoader.DeleteObject(m_pos);
			return;
		}
	}

}

void C_MAP_EDITER::Updata()
{
	for (auto itr = m_objectArray.begin(); itr != m_objectArray.end(); ++itr)
	{
		(*itr)->Update();
	}

	MV1SetPosition(m_hndl, m_pos);
}

void C_MAP_EDITER::Draw()
{
	for (auto itr = m_objectArray.begin(); itr != m_objectArray.end(); ++itr)
	{
		(*itr)->Draw();
	}

	MV1DrawModel(m_hndl);

	RenderVertex();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void C_MAP_EDITER::DeleteObjectAll()
{
	for (auto itr = m_objectArray.begin(); itr != m_objectArray.end(); ++itr)
	{
		(*itr)->Exit();
		delete (*itr);
	}

	m_objectArray.clear();
}

void C_MAP_EDITER::Exit()
{
	DeleteObjectAll();
	MV1DeleteModel(m_hndl);
	m_stageLoader.SaveMapData(m_filePath);
	m_stageLoader.Exit();
	SetupToolBar(NULL, NULL);
}