#pragma once
#include <DxLib.h>

class CPlayCamera
{
private:
	VECTOR m_pos;		// 視点
	VECTOR m_focus;	// 注視点
	VECTOR m_up;		// カメラの上方向
	VECTOR m_camRot;	// カメラ回転角度

public:
	// コンストラクタ・デストラクタ
	CPlayCamera();
	~CPlayCamera();

	// 初期化
	//	@pos	:	視点
	//	@focus	:	注視点
	//	@up		:	上方向
	void Init(VECTOR pos, VECTOR focus, VECTOR up);

	// 終了処理
	void Exit();

	// 毎フレーム呼ぶ処理
	//	@focus	:	プレイヤーの座標
	//	@rot	:	プレイヤーの回転角度
	void Step(VECTOR focus, float rot);
	// 更新処理
	void Update();

	//	取得・設定関連===============
	// 視点取得
	VECTOR GetPosition(){ return m_pos; }
	// 視点設定
	void SetPosition(VECTOR pos){ m_pos = pos; }
	// 注視点取得
	VECTOR GetFocus(){ return m_focus; }
	// アップベクトル取得
	VECTOR GetUpvec(){ return m_up; }
	// カメラ角度取得
	VECTOR GetCameraRot(){ return m_camRot; }
};