#include "game/camera/camera_manager.h"

void C_CAMERA_MANAGER_::Init(VECTOR pos, VECTOR focus, VECTOR up)
{
	c_playerCamera.Init(pos, focus, up);
}

void C_CAMERA_MANAGER_::Init(C_PALYER_CAMERA_VEC::CAMERA_EVENT_STATE _eventState)
{
	c_playerCamera.Init(DEFAULT_EYE_POS, DEFAULT_FOCUS_POS, DEFAULT_UP_VEC, _eventState);
}

void C_CAMERA_MANAGER_::InitEdit()
{
	c_playerCamera.Init(DEFAULT_EYE_POS, DEFAULT_FOCUS_POS, DEFAULT_UP_VEC);
	c_playerCamera.SetEventState(C_PALYER_CAMERA_VEC::CAM_EVENT_PLAY);
}

// 終了処理
void C_CAMERA_MANAGER_::Exit()
{
	c_playerCamera.Exit();
}

// 更新処理
void C_CAMERA_MANAGER_::Step(VECTOR focus, VECTOR pos, float rot, int _padID)
{
	c_playerCamera.Step(focus, pos, rot, _padID);
}

// 更新処理
void C_CAMERA_MANAGER_::Update()
{
	c_playerCamera.Update();
}

// 描画処理
void C_CAMERA_MANAGER_::Draw()
{

}

// カメラタイプ変更
void C_CAMERA_MANAGER_::ChangeCamera(tagCAMERA_ID ID)
{

}

// カメラのニア・ファー設定
void C_CAMERA_MANAGER_::SetNearFar(float nearLen, float farLen)
{
	SetCameraNearFar(nearLen, farLen);
}

// リスポーン処理
void C_CAMERA_MANAGER_::Respawn(VECTOR pos, VECTOR focus, VECTOR up)
{
	c_playerCamera.Respwan(pos, focus, up);
}