#pragma once
#include <DxLib.h>
#include "player_camera.h"

constexpr VECTOR DEFAULT_EYE_POS = { 0.0f, 40.0f, -100.0f };
constexpr VECTOR DEFAULT_FOCUS_POS = { 0.0f, 0.0f, 0.0f };
constexpr VECTOR DEFAULT_UP_VEC = { 0.0f, 1.0f, 0.0f };

class C_PALYER_CAMERA_VEC;

class C_CAMERA_MANAGER_
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

	C_PALYER_CAMERA_VEC c_playerCamera;

	// 現在のカメラID
	tagCAMERA_ID m_currentCameraID;

public:

	// コンストラクタ
	C_CAMERA_MANAGER_(tagCAMERA_ID _currentCameraID = CAMERA_ID_NUM):
	m_currentCameraID(_currentCameraID){}
	// デストラクタ
	~C_CAMERA_MANAGER_(){}

	//初期化処理
	void Init(VECTOR pos, VECTOR focus, VECTOR up);
	void Init();
	// 終了処理
	void Exit();
	// 更新処理
	void Step(VECTOR focus, VECTOR pos, float rot, int _padID);
	// 更新処理
	void Update();
	// 描画処理
	void Draw();

	//リスポーン
	void Respawn(VECTOR pos, VECTOR focus, VECTOR up);


	C_PALYER_CAMERA_VEC* GetPlayerCamera() { return &c_playerCamera; }

	// カメラタイプ変更
	void ChangeCamera(tagCAMERA_ID ID);
	// 現在のカメラタイプ取得
	tagCAMERA_ID GetCameraID() { return m_currentCameraID; }
	// カメラのニア・ファー設定
	void SetNearFar(float nearLen, float farLen);

	VECTOR GetPlayerCamaraRota() { return c_playerCamera.GetCameraRot(); }

	void SetPlayerCameraRot(VECTOR _rot) { c_playerCamera.SetCameraRot(_rot); }

	C_PALYER_CAMERA_VEC::CAMERA_EVENT_STATE GetPlayerCamEventState() { return c_playerCamera.GetEventState(); }
};
