#include "imguiCtrl/imguiCtrl.h"

//ID3D11Device* C_ImGui_Ctrl::c_pd3dDevice = nullptr;
//ID3D11DeviceContext* C_ImGui_Ctrl::c_pd3dDeviceContext = nullptr;

void C_ImGui_Ctrl::Init(WNDPROC WinProc)
{
	ImGui::CreateContext();
	c_pd3dDevice = (ID3D11Device*)(GetUseDirect3D11Device());
	c_pd3dDeviceContext = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();
	ImGui_ImplWin32_Init(GetMainWindowHandle());
	ImGui_ImplDX11_Init(c_pd3dDevice, c_pd3dDeviceContext);
	SetHookWinProc(WinProc);
	ImGui::GetIO().Fonts->AddFontFromFileTTF("c:/Windows/Fonts/meiryo.ttc", 18.0f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
}

void C_ImGui_Ctrl::Add()
{
	ImGuiCond;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(400,300), ImGuiCond_Always);
	ImGui::Begin("Stats");
	ImGui::LabelText("", "FPS:%4.2f (%4.2f ms)", 0.0f);
	ImGui::LabelText("", "Camera Pos:(%.2f, %.2f, %.2f )", 0.0f, 0.0f, 0.0f);
	ImGui::Spacing();
	//if (ImGui::CollapsingHeader("PostEffect"))
	if (ImGui::Button("Open")) {
		// on click
	}
	ImGui::End();

	//ImGui::ShowDemoWindow();
}

void C_ImGui_Ctrl::Draw()
{

}

void C_ImGui_Ctrl::Exit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}