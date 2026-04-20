#pragma once
#include "PlayCamera.h"
#include "DebugCamera.h"
#include "../field/field.h"

class CCameraManager
{
public:

	// カメラのタイプ
	enum tagCAMERA_ID
	{
		CAMERA_ID_PLAY,		// ゲーム中のカメラ
		CAMERA_ID_DEBUG,	// デバッグ用のカメラ(今後作成)

		CAMERA_ID_NUM
	};

private:
	CPlayCamera m_playCam;				// プレイヤーカメラ
	CDebugCamera m_debugCam;			// デバッグカメラ
	tagCAMERA_ID m_currentCameraID;	// 現在のカメラID

public:
	// コンストラクタ・デストラクタ
	CCameraManager();
	~CCameraManager();

	// 初期化
	//	@pos		:	視点
	//	@focus		:	注視点
	//	@up		:	上方向
	void Init();
	void Init(VECTOR pos, VECTOR focus, VECTOR up);
	// 終了処理
	void Exit();
	// 更新処理
	void Step(VECTOR focus, float rot, CField &field);
	// 更新処理
	void Update();
	// 描画処理
	void Draw();

	//	取得・設定関連===============
	// カメラタイプ変更
	void ChangeCamera(tagCAMERA_ID ID);
	// 現在のカメラタイプ取得
	tagCAMERA_ID GetCameraID(){ return m_currentCameraID; }
	// カメラのニア・ファー設定
	void SetNearFar(float nearLen, float farLen);
	// プレイヤーカメラ角度取得
	VECTOR GetPlayerCameraRot(){ return m_playCam.GetCameraRot(); }
};