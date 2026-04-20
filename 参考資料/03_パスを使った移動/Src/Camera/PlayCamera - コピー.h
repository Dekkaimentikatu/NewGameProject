#pragma once
#include <DxLib.h>

class CPlayCamera
{
private:
	VECTOR m_vPos;		// 視点
	VECTOR m_vFocus;	// 注視点
	VECTOR m_vUp;		// カメラの上方向
	VECTOR m_vCamRot;	// カメラ回転角度

public:
	// コンストラクタ・デストラクタ
	CPlayCamera();
	~CPlayCamera();

	// 初期化
	//	@vPos		:	視点
	//	@vFocus	:	注視点
	//	@vUp		:	上方向
	void Init(VECTOR vPos, VECTOR vFocus, VECTOR vUp);

	// 終了処理
	void Exit();

	// 毎フレーム呼ぶ処理
	//	@vFocus	:	プレイヤーの座標
	//	@fRot		:	プレイヤーの回転角度
	void Step(VECTOR vFocus, float fRot);
	// 更新処理
	void Update();

	//	取得・設定関連===============
	// 視点取得
	VECTOR GetPosition(){ return m_vPos; }
	// 注視点取得
	VECTOR GetFocus(){ return m_vFocus; }
	// アップベクトル取得
	VECTOR GetUpvec(){ return m_vUp; }
	// カメラ角度取得
	VECTOR GetCameraRot(){ return m_vCamRot; }
};