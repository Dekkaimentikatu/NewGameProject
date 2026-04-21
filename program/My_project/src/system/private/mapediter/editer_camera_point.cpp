#include "mapediter/editer_camera_point.h"

#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

C_EDITER_CAMERA_POINT::C_EDITER_CAMERA_POINT()
{

}

C_EDITER_CAMERA_POINT::~C_EDITER_CAMERA_POINT()
{

}

void C_EDITER_CAMERA_POINT::Init()
{
	C_OBJECT_BASE::Init();
	m_camPos = VGet(0.0f, 0.0f, -50.0f);
	m_camFocus = { 0 };
	m_camRot = { 0 };
	m_camUp = { 0 };
	m_speed = POINT_MOVE_SPEED;
	c_camManager.InitEdit();
	SetCameraNearFar(0.25f, 3000.0f);
}

void C_EDITER_CAMERA_POINT::Load()
{
	
}

void C_EDITER_CAMERA_POINT::Step()
{
	//移動ベクトルの初期化
	VECTOR moveVec = { 0 };

	//
	if (C_XINPUT::GetConnectPad(POINT_PAD_ID))
	{
		moveVec.x = -m_speed * C_XINPUT::GetLAnalogXInput(POINT_PAD_ID);
		moveVec.z = -m_speed * C_XINPUT::GetLAnalogYInput(POINT_PAD_ID);

		if (C_XINPUT::GetButtanInputRep(POINT_PAD_ID, XINPUT_BUTTON_DPAD_UP))
		{
			m_objectData.initPos.y += m_speed;
		}
		else if (C_XINPUT::GetButtanInputRep(POINT_PAD_ID, XINPUT_BUTTON_DPAD_DOWN))
		{
			m_objectData.initPos.y -= m_speed;
		}
	}
	else
	{
		if (C_INPUT::IsInputRep(KEY_INPUT_UP))
		{
			moveVec.z -= m_speed;
		}
		if (C_INPUT::IsInputRep(KEY_INPUT_DOWN))
		{
			moveVec.z += m_speed;
		}
		if (C_INPUT::IsInputRep(KEY_INPUT_LEFT))
		{
			moveVec.x -= m_speed;
		}
		if (C_INPUT::IsInputRep(KEY_INPUT_RIGHT))
		{
			moveVec.x += m_speed;
		}
		if (C_INPUT::IsInputRep(KEY_INPUT_RSHIFT))
		{
			moveVec.y += m_speed;
		}
		if (C_INPUT::IsInputRep(KEY_INPUT_RCONTROL))
		{
			moveVec.y -= m_speed;
		}
	}

	// 移動しているようであれば更新
	if (moveVec.x != 0.0f || moveVec.z != 0.0f)
	{
		// 速度を正規化
		//m_moveVec = VNorm(m_moveVec);
		// 回転行列を利用してカメラ位置設定
		MATRIX	mat1, mat2;
		mat1 = MGetTranslate(moveVec);
		mat2 = MGetRotY(c_camManager.GetPlayerCamera()->GetCameraRot().y);
		mat1 = MMult(mat1, mat2);
		moveVec.x = mat1.m[3][0];
		moveVec.y = mat2.m[3][1];
		moveVec.z = mat1.m[3][2];
		// 移動速度からY軸回転角度を取得
		m_objectData.modelRot.y = atan2f(-moveVec.x, -moveVec.z);
	}

	m_objectData.initPos = VAdd(m_objectData.initPos, moveVec);

	c_camManager.Step(m_camPos, m_objectData.initPos, m_camRot.y, 1);

	// ウィンドウの背景を半透明に設定
	ImGui::SetNextWindowBgAlpha(0.5f);
	// ウィンドウの位置を設定
	ImGui::SetNextWindowPos(ImVec2(0, 700), ImGuiCond_Always);
	// ウィンドウのサイズを設定
	ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_Always);
	// ウィンドウのタイトルを設定して開始
	ImGui::Begin("CameraParameter");
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::LabelText("", "Camera Pos:(%.2f, %.2f, %.2f )", m_objectData.initPos.x, m_objectData.initPos.y, m_objectData.initPos.z);
	ImGui::SliderFloat("speed", &m_speed, 1.0f, 10.0f);
	ImGui::End();
}

void C_EDITER_CAMERA_POINT::Update()
{
	c_camManager.Update();
}

void C_EDITER_CAMERA_POINT::Draw()
{

}

void C_EDITER_CAMERA_POINT::Exit()
{
	c_camManager.Exit();
}

void C_EDITER_CAMERA_POINT::HitCalc()
{

}