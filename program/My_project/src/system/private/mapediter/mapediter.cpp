#include "mapediter/mapediter.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "lib/3Dhndlmanager.h"

#include "lib/input.h"
#include "game/object/static/sky.h"

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
	c_objectArray.clear();
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
	
	C_3D_HNDL_MANAGER* instance = C_3D_HNDL_MANAGER::GetInstance();
	instance->Load3DModel(SKY_MODEL_PATH);
	instance->Load3DModel("data/model/field/pointer.mv1");
}

void C_MAP_EDITER::LoadSync()
{
	C_3D_HNDL_MANAGER* instance = C_3D_HNDL_MANAGER::GetInstance();
	m_hndl = instance->Get3DModelHndl("data/model/field/pointer.mv1");
	MV1SetPosition(m_hndl, m_pos);
	MV1SetScale(m_hndl, VGet(0.1f, 0.1f, 0.1f));
	memcpy(m_filePath, const_cast<char*>(FILE_PATH), sizeof(char[256]));
	memcpy(m_prevfilePath, const_cast<char*>(FILE_PATH), sizeof(char[256]));
	m_stageLoader.LoadMapData(c_objectArray, m_filePath);

	C_OBJECT_BASE* tmp = new C_SKY;
	tmp->Init();
	tmp->Load();

	c_objectArray.push_back(tmp);
}

void C_MAP_EDITER::Step()
{
	// ウィンドウの背景を半透明に設定
	ImGui::SetNextWindowBgAlpha(0.5f);
	// ウィンドウの位置を設定
	ImGui::SetNextWindowPos(ImVec2(880, 0), ImGuiCond_Always);
	// ウィンドウのサイズを設定
	ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
	// ウィンドウのタイトルを設定して開始
	ImGui::Begin("Stats");
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
	if (ImGui::CollapsingHeader("Loadcsv"))
	{
		ImGui::InputText("FilePath", m_filePath, sizeof(m_filePath));
		ImGui::SameLine();
		if (ImGui::Button("Load")) {
			m_stageLoader.SaveMapData(m_prevfilePath);
			m_stageLoader.DeleteObjectAll();
			DeleteObjectAll();

			memcpy(m_prevfilePath, m_filePath, sizeof(m_filePath));

			m_stageLoader.LoadMapData(c_objectArray, m_filePath);
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
	ImGui::SameLine();
	if (ImGui::Button("Ando")) {
		m_stageLoader.AndoAddObject(c_objectArray);
	}
	ImGui::SameLine();
	if (ImGui::Button("Redo")) {
		m_stageLoader.RedoAddObject(c_objectArray);
	}
	ImGui::End();



	MV1SetPosition(m_hndl, m_pos);
}

void C_MAP_EDITER::AddObject()
{
	T_STAGE_DATA tmp = { 0 };
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
	m_stageLoader.AddObject(tmp, c_objectArray);
}

void C_MAP_EDITER::DeleteObject()
{
	for (auto itr = c_objectArray.begin(); itr != c_objectArray.end(); ++itr)
	{
		if ((*itr)->GetPos().x == m_pos.x &&
			(*itr)->GetPos().y == m_pos.y &&
			(*itr)->GetPos().z == m_pos.z)
		{
			//オブジェクトを削除
			(*itr)->Exit();
			delete (*itr);
			c_objectArray.erase(itr);
			m_stageLoader.DeleteObject(m_pos);
			return;
		}
	}

}

void C_MAP_EDITER::Update()
{
	for (auto itr = c_objectArray.begin(); itr != c_objectArray.end(); ++itr)
	{
		(*itr)->Update();
	}

	MV1SetPosition(m_hndl, m_pos);
}

void C_MAP_EDITER::Draw()
{
	for (auto itr = c_objectArray.begin(); itr != c_objectArray.end(); ++itr)
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
	for (auto itr = c_objectArray.begin(); itr != c_objectArray.end(); ++itr)
	{
		(*itr)->Exit();
		delete (*itr);
	}

	c_objectArray.clear();
}

void C_MAP_EDITER::Exit()
{
	C_3D_HNDL_MANAGER* instance = C_3D_HNDL_MANAGER::GetInstance();

	DeleteObjectAll();
	instance->Delete3DModel(SKY_MODEL_PATH);
	instance->Delete3DModel("data/model/field/pointer.mv1");
	m_stageLoader.SaveMapData(m_filePath);
	m_stageLoader.Exit();
	SetupToolBar(NULL, NULL);
}