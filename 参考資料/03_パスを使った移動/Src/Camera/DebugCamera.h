#pragma once
#include <DxLib.h>

class CDebugCamera
{
private:
	VECTOR m_pos;		// 視点
	VECTOR m_focus;	// 注視点
	VECTOR m_up;		// カメラの上方向

public:
	// コンストラクタ・デストラクタ
	CDebugCamera();
	~CDebugCamera();

	// 初期化
	//	@pos	:	視点
	//	@focus	:	注視点
	//	@up		:	上方向
	void Init(VECTOR pos, VECTOR focus, VECTOR up);

	// 終了処理
	void Exit();

	// 毎フレーム呼ぶ処理
	void Step();
	// 更新処理
	void Update();
	// 描画
	void Draw();

private:
	// 注視点の上下移動
	void MoveUpDown();
	// 注視点の前後移動
	void MoveFrontBack();
	// 注視点の左右移動
	void MoveLeftRight();
	// 注視点の左右回転
	void RotateLeftRight();
};