#pragma once
#include "game/base/object.h"
#include "game/camera/camera_manager.h"

static constexpr int POINT_PAD_ID = DX_INPUT_PAD1;

static constexpr float POINT_MOVE_SPEED = 1.0f;

static constexpr float POINT_ROTATE_SPEED = 0.1f;

static constexpr float POINT_JUMP_SPEED = 0.5f;

class C_EDITER_CAMERA_POINT : public C_OBJECT_BASE
{
private:

	//座標
	VECTOR m_camPos;
	//回転
	VECTOR m_camRot;
	//注視点
	VECTOR m_camFocus;
	//カメラの上方向
	VECTOR m_camUp;
	//カメラ
	C_CAMERA_MANAGER_ c_camManager;

public:

	C_EDITER_CAMERA_POINT();
	virtual ~C_EDITER_CAMERA_POINT();
	void Init() override;
	void Load() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Exit() override;
	void HitCalc();
};