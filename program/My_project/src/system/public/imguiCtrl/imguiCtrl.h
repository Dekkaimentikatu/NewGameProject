#pragma once
#include <DxLib.h>			// DxLib‚ğg—p‚·‚é‚½‚ß‚É•K{
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

class C_ImGui_Ctrl
{
private:

	//
	ID3D11Device* c_pd3dDevice;
	//
	ID3D11DeviceContext* c_pd3dDeviceContext;

public:

	C_ImGui_Ctrl(){}
	~C_ImGui_Ctrl(){}

	//‰Šú‰»
	void Init(WNDPROC WinProc);

	//
	void Add();

	//
	void Draw();

	void Exit();
};