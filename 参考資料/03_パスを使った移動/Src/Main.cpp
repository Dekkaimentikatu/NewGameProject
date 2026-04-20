#include "DxLib.h"
#include <math.h>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Field/Field.h"
#include "Input/InputKey.h"
#include "Camera/CameraManager.h"

//	定義関連=================================================


//===========================================================


// プログラムは WinMain から始まります
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウを通常モードで開くか、フルスクリーンで開くか
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;

	// 一番最初に１回だけやる処理
	SetDrawScreen(DX_SCREEN_BACK);
	SetTransColor(255, 0, 255);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	// インスタンス作成
	Player	player;
	Enemy enemy;
	Field	field;
	CameraManager cam;
	int state = 0;

	cam.Init();
	cam.SetNearFar(5.0f, 3000.0f);

	// ゲームメインループ
	while (ProcessMessage() != -1)
	{
		// エスケープキーが押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

		// モニターの絵を全て消す
		ClearDrawScreen();

		// ここからゲームの命令を書く=============================
		CInputKey::UpdateKey();
		switch (state)
		{
		case 0:
			// データロード
			player.LoadData();
			enemy.LoadData();
			field.LoadData();

			player.Reset();
			enemy.Reset();
			field.Set();
			state = 1;
			break;
		case 1:
			{
				VECTOR vec;
				// プレイヤー処理
				player.SetCameraRot(cam.GetPlayerCameraRot());
				player.Calc();
				vec = field.HitCheck(player.GetCenter(), player.GetRadius());
				player.ReflectCollision(vec);
				player.Update();
				// エネミー処理
				enemy.Calc(player.GetPosition());
				vec = field.HitCheck(enemy.GetCenter(), enemy.GetRadius());
				enemy.ReflectCollision(vec);
				enemy.Update();

				cam.Step(player.GetPosition(), player.GetRot().y, field);
				cam.Update();

				// 通常の描画開始-------------------
				player.Draw();
				enemy.Draw();
				field.Draw();
				cam.Draw();
				// 通常の描画終了-------------------
			}
			break;
		}

		// ここまでゲームの命令を書く=============================

		// 画面をモニターへ転送
		ScreenFlip();

	}

	cam.Exit();
	player.Exit();
	enemy.Exit();
	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}
