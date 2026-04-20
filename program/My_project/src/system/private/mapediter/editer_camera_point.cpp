#include "mapediter/editer_camera_point.h"



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

	c_camManager.Init();
	c_camManager.GetPlayerCamera()->SetEventState(C_PALYER_CAMERA_VEC::CAM_EVENT_PLAY);
	SetCameraNearFar(0.25f, 3000.0f);
}


void C_EDITER_CAMERA_POINT::Request(T_OBJECT_DATA _objectData)
{
	m_objectData = _objectData;
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
		moveVec.x = -POINT_MOVE_SPEED * C_XINPUT::GetLAnalogXInput(POINT_PAD_ID);
		moveVec.z = -POINT_MOVE_SPEED * C_XINPUT::GetLAnalogYInput(POINT_PAD_ID);

		if (C_XINPUT::GetButtanInputRep(POINT_PAD_ID, XINPUT_BUTTON_DPAD_UP))
		{
			m_pos.y += POINT_MOVE_SPEED;
		}
		else if (C_XINPUT::GetButtanInputRep(POINT_PAD_ID, XINPUT_BUTTON_DPAD_DOWN))
		{
			m_pos.y -= POINT_MOVE_SPEED;
		}
	}
	else
	{
		if (C_INPUT::IsInputRep(KEY_INPUT_UP))
		{
			moveVec.z -= POINT_MOVE_SPEED;
		}
		if (C_INPUT::IsInputRep(KEY_INPUT_DOWN))
		{
			moveVec.z += POINT_MOVE_SPEED;
		}
		if (C_INPUT::IsInputRep(KEY_INPUT_LEFT))
		{
			moveVec.x -= POINT_MOVE_SPEED;
		}
		if (C_INPUT::IsInputRep(KEY_INPUT_RIGHT))
		{
			moveVec.x += POINT_MOVE_SPEED;
		}
		if (C_INPUT::IsInputRep(KEY_INPUT_RSHIFT))
		{
			moveVec.y += POINT_MOVE_SPEED;
		}
		if (C_INPUT::IsInputRep(KEY_INPUT_RCONTROL))
		{
			moveVec.y -= POINT_MOVE_SPEED;
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

	m_pos = VAdd(m_pos, moveVec);

	c_camManager.Step(m_camPos, m_pos, m_camRot.y, 1);
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