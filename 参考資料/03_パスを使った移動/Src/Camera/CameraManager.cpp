#include "CameraManager.h"
#include <DxLib.h>

//	定義関連------------------------------
// 基本となる視点・注視点・アップベクトル
static const VECTOR DEFAULT_EYE_POS = { 0.0f, 10.0f, -20.0f };
static const VECTOR DEFAULT_FOCUS_POS = { 0.0f, 0.0f, 0.0f };
static const VECTOR DEFAULT_UP_VEC = { 0.0f, 1.0f, 0.0f };
//----------------------------------------


//-------------------------------
//		コンストラクタ
//-------------------------------
CameraManager::CameraManager()
{
	// ひとまず初期はゲーム中カメラを
	m_currentCameraID = CAMERA_ID_PLAY;
}


//-------------------------------
//		デストラクタ
//-------------------------------
CameraManager::~CameraManager()
{
}


//-------------------------------
//		初期化
//-------------------------------
void CameraManager::Init()
{
	m_playCam.Init(DEFAULT_EYE_POS, DEFAULT_FOCUS_POS, DEFAULT_UP_VEC);
	m_debugCam.Init(DEFAULT_EYE_POS, DEFAULT_FOCUS_POS, DEFAULT_UP_VEC);
}


//-------------------------------
//		初期化
//-------------------------------
void CameraManager::Init(VECTOR pos, VECTOR focus, VECTOR up)
{
	m_playCam.Init(pos, focus, up);
	m_debugCam.Init(pos, focus, up);
}


//-------------------------------
//		終了処理
//-------------------------------
void CameraManager::Exit()
{
	m_playCam.Exit();
	m_debugCam.Exit();
}


//-------------------------------
//		毎フレーム呼ぶ処理
//-------------------------------
void CameraManager::Step(VECTOR focus, float rot, Field &field)
{
	// カメラのタイプに合わせて、更新処理を変更する
	switch (m_currentCameraID)
	{
	case CAMERA_ID_PLAY:
		m_playCam.Step(focus, rot);
		m_playCam.SetPosition(field.HitCheck(m_playCam.GetFocus(), m_playCam.GetPosition()));
		break;
	case CAMERA_ID_DEBUG:
		m_debugCam.Step();
		break;
	}
}


//-------------------------------
//		更新処理
//-------------------------------
void CameraManager::Update()
{
	// カメラのタイプに合わせて、描画処理を変更する
	switch (m_currentCameraID)
	{
	case CAMERA_ID_PLAY:
		m_playCam.Update();
		break;
	case CAMERA_ID_DEBUG:
		m_debugCam.Update();
		break;
	}
}


//-------------------------------
//		描画処理
//-------------------------------
void CameraManager::Draw()
{
	// カメラのタイプに合わせて、描画処理を変更する
	switch (m_currentCameraID)
	{
	case CAMERA_ID_PLAY:
		break;
	case CAMERA_ID_DEBUG:
		m_debugCam.Draw();
		break;
	}
}


//-------------------------------
//		描画処理
//-------------------------------
void CameraManager::ChangeCamera(tagCAMERA_ID ID)
{
	m_currentCameraID = ID;
	switch (m_currentCameraID)
	{
	case CAMERA_ID_DEBUG:
		m_debugCam.Init(m_playCam.GetPosition(), m_playCam.GetFocus(), m_playCam.GetUpvec());
		break;
	}
}



//-------------------------------
//		カメラのニア・ファー設定
//-------------------------------
void CameraManager::SetNearFar(float nearLen, float farLen)
{
	SetCameraNearFar(nearLen, farLen);
}

