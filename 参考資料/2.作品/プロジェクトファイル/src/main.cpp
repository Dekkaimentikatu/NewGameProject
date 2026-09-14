#include <DxLib.h>			// DxLibを使用するために必須
#include "common.h"
#include "scene/scene_manager.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

// ImGuiのプロシージャを流すための宣言
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ImGuiにプロシージャの情報を流す
LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {

		SetUseHookWinProcReturnValue(TRUE);
		return true;
	}
}

//
ID3D11Device* c_pd3dDevice;
//
ID3D11DeviceContext* c_pd3dDeviceContext;

// ゲームプログラムは WinMain から始まります
int  WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
 _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{


#if _DEBUG

	ChangeWindowMode(TRUE);			// ウィンドウモードにするかどうか
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);		// ウィンドウの解像度を設定する

#else

	// リリース版はログを出さない
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(FALSE);			// ウィンドウモードにするかどうか
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);		// ウィンドウの解像度を設定する

#endif

#ifdef DEBUG_MODE

	SetWindowSizeExtendRate(1.0);

#endif

	// ＤＸライブラリ初期化処理　基本的にはこれより後でDxLib関数を使う
	if (DxLib_Init() == -1) return -1;

	//DxLib
	{
		SetDrawScreen(DX_SCREEN_BACK);	// 画面のちらつきを無くす
		SetUseZBuffer3D(TRUE);		// Zバッファを使用するかどうか
		SetWriteZBuffer3D(TRUE);	// Zバッファに書き込むかどうか
		SetTransColor(255, 0, 255);		// 透過色指定　今回は緑色を透過
	}

	//ImGui
	{
		ImGui::CreateContext();
		c_pd3dDevice = (ID3D11Device*)(GetUseDirect3D11Device());
		c_pd3dDeviceContext = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();
		ImGui_ImplWin32_Init(GetMainWindowHandle());
		ImGui_ImplDX11_Init(c_pd3dDevice, c_pd3dDeviceContext);
		SetHookWinProc(WndProc);
		ImGui::GetIO().Fonts->AddFontFromFileTTF("c:/Windows/Fonts/meiryo.ttc", 18.0f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
	}

	C_SCENE_MANAGER c_sceneManager;

	// 初期化関連
	//ゲーム全体を管理する情報の初期化

	c_sceneManager.Init();
	c_sceneManager.Load();

	//ゲームメインループ
	while (ProcessMessage() != -1)	// 問題が発生したら終了
	{
		WaitTimer(1);
		// 「escキー」が押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; 
		if (c_sceneManager.IsSceneTypeEND())break;

		// 画面を一度何もない状態へ
		ClearDrawScreen();

		// ゲーム本体の命令はこれより下に書く

		c_sceneManager.Step();	//シーン管理マネージャーの更新処理

		c_sceneManager.Loop();	//シーン管理マネージャーのループ処理

		c_sceneManager.Draw();	//シーン管理マネージャーの描画処理

		c_sceneManager.Next();	//シーンマネージャーの遷移処理

		// ゲーム本体の命令はこれより上に書く

		// 作成した画面をモニターへ転送
		ScreenFlip();
	}

	// 終了前処理==================

	c_sceneManager.Exit();

	//ImGui
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	//DxLib
	{
		DxLib_End();			// ＤＸライブラリ使用の終了処理
	}
	//=============================

	return 0;				// プログラムの終了 
}
