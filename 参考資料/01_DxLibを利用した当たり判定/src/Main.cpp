#include "DxLib.h"
#include <math.h>
#include "Player/Player.h"
#include "Field/Field.h"
#include "Input/InputKey.h"

//	定義関連=================================================


//===========================================================


// プログラムは WinMain から始まります
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウを通常モードで開くか、フルスクリーンで開くか
	ChangeWindowMode(TRUE);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;

	// 一番最初に１回だけやる処理
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetCameraNearFar(5.0f, 3000.0f);


	// インスタンス作成
	Player	player;
	Field	field;

	// データロード
	player.LoadData();
	field.LoadData();

	player.Reset();

	// ゲームメインループ
	while (ProcessMessage() != -1)
	{
		// エスケープキーが押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

		// モニターの絵を全て消す
		ClearDrawScreen();

		// ここからゲームの命令を書く=============================
		InputKey::UpdateKey();

		player.Calc();
		player.CalcCamera();

		//当たり判定
		VECTOR out = field.HitCheck(player.GetCenter(), player.GetRadius());

		player.ReflectCollision(out);

		// 描画
		player.Draw();
		field.Draw();
		// ここまでゲームの命令を書く=============================

		// 画面をモニターへ転送
		ScreenFlip();

	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}
