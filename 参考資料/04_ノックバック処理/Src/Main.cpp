#include "DxLib.h"
#include <math.h>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Field/Field.h"
#include "Input/Inputkey.h"
#include "Camera/CameraManager.h"

//	定義関連=================================================
// プレイヤーと敵の当たり判定
void HitCheckEnemyToPlayer(Player& player, Enemy& enemy);
// プレイヤーの攻撃と敵の当たり判定
void HitCheckEnemyToPlayerAttack(Player& player, Enemy& enemy);
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
	CField	field;
	CCameraManager camera;
	int state = 0;

	camera.Init();
	camera.SetNearFar(5.0f, 3000.0f);

	// ゲームメインループ
	while (ProcessMessage() != -1)
	{
		// エスケープキーが押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

		// モニターの絵を全て消す
		ClearDrawScreen();

		// ここからゲームの命令を書く=============================
		InputKey::UpdateKey();
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
				player.SetCameraRot(camera.GetPlayerCameraRot());
				player.Step();
				vec = field.HitCheck(player.GetCenter(), player.GetRadius());
				player.ReflectCollision(vec);
				player.Update();
				// エネミー処理
				enemy.Step(player.GetPosition());
				vec = field.HitCheck(enemy.GetCenter(), enemy.GetRadius());
				enemy.ReflectCollision(vec);
				enemy.Update();

				// プレイヤーとエネミーの当たり判定
				HitCheckEnemyToPlayer(player, enemy);
				HitCheckEnemyToPlayerAttack(player, enemy);

				camera.Step(player.GetPosition(), player.GetRot().y, field);
				camera.Update();

				// 通常の描画開始-------------------
				player.Draw();
				enemy.Draw();
				field.Draw();
				camera.Draw();
				// 通常の描画終了-------------------
			}
			break;
		}

		// ここまでゲームの命令を書く=============================

		// 画面をモニターへ転送
		ScreenFlip();

	}

	player.Exit();
	enemy.Exit();
	camera.Exit();
	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}


//------------------------------
//		プレイヤーと敵の当たり判定
//------------------------------
void HitCheckEnemyToPlayer(Player& player, Enemy& enemy)
{
	VECTOR plPos = player.GetPosition();
	VECTOR enPos = enemy.GetPosition();

	// 二点間の距離を取得
	VECTOR vec = VSub(enPos, plPos);
	float len = VSize(vec);

	// 一定範囲より短ければヒット
	if (len < 10.0f)
	{
		// 今回は敵の方を押し返す
		vec = VNorm(vec);
		vec = VScale(vec, 10.0f - len);
		enemy.ReflectCollision(vec);
	}
}


//------------------------------
//		プレイヤーの攻撃と敵の当たり判定
//------------------------------
void HitCheckEnemyToPlayerAttack(Player& player, Enemy& enemy)
{
	//プレイヤーが攻撃していなければ処理を行わない
	if (!player.IsAttack())return;

	//プレイヤーの攻撃判定の座標を取得
	VECTOR plAttackPos = player.GetAttackPos();
	//エネミーの座標を取得
	VECTOR enPos = enemy.GetPosition();

	//二点間の距離を取得
	VECTOR vec = VSub(enPos, plAttackPos);
	float len = VSize(vec);

	//一定範囲より短ければヒット
	if (len < 10.0f)
	{
		//二点間の距離を正規化
		vec = VNorm(vec);
		//上に飛ばす
		vec.y = 1.5f;
		//威力の調整
		vec = VScale(vec, 1.3f);

		//ノックバックベクトルをエネミーに与える
		enemy.HitCalc(vec);
	}
}