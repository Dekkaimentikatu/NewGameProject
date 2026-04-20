#include "game/camera/player_camera.h"
#include "lib/input_config.h"
#include "lib/2Ddirection/easing/easing.h"
#include "lib/fade.h"
#include "game/data/global_data.h"



//カメラの初期化
void C_PALYER_CAMERA_VEC::Init(VECTOR _pos, VECTOR _focus, VECTOR _up)
{
	m_pos = _pos;
	m_focus = _focus;
	m_up = _up;
	m_speed = 0.0f;
	m_moveTime = 0.0f;
	m_state = CAMERA_STATE_PLAYER;
	m_eventState = CAM_EVENT_START;
	m_comPoint = m_pos;
	m_rot.y = DX_PI_F * 180.0f / 180.0f;

	CamMoveStart();
	Update();
}

//リスポーン処理
void C_PALYER_CAMERA_VEC::Respwan(VECTOR _pos, VECTOR _focus, VECTOR _up)
{
	m_pos = _pos;
	m_focus = _focus;
	m_up = _up;
	m_speed = 0.0f;
	m_moveTime = 0.0f;
	m_state = CAMERA_STATE_PLAYER;
	m_eventState = CAM_EVENT_PLAY;
	m_comPoint = m_pos;
	m_rot.y = DX_PI_F * 180.0f / 180.0f;
}

//カメラの終了処理
void C_PALYER_CAMERA_VEC::Exit()
{

}

//更新処理
void C_PALYER_CAMERA_VEC::Step(VECTOR _focus, VECTOR _pos, float _rot, int _padID)
{
	//キーコンフィグを利用した入力に変更する
	//else if部分を削除する
	if (C_XINPUT::GetButtanInputTrg(DX_INPUT_PAD1, XINPUT_BUTTON_RIGHT_THUMB) || !m_isTarget) {

		ChangeCameraState();
	}

	switch (m_state)
	{
	case C_PALYER_CAMERA_VEC::CAMERA_STATE_PLAYER:
		PlayerCameraCalcMat(_pos, _rot, _padID);
		break;
	case C_PALYER_CAMERA_VEC::CAMERA_STATE_TARGET:
		TargetCameraCalc(_focus, _pos, _rot, _padID);
		break;
	}

	VECTOR vec = VSub(m_comPoint, m_pos);
	float len = VSize(vec);
	vec = VNorm(vec);
	vec = VScale(vec, m_speed);

	m_pos = VAdd(m_pos, vec);

	if (len < COM_SPEED_MAX)
	{
		m_speed = 0.0f;
		m_pos = m_comPoint;
		m_moveTime = 0.0f;
	}
}

//
void C_PALYER_CAMERA_VEC::CamMoveStart()
{
	m_center = { 0 };
	m_rot.y += 0.01f;
	m_rot.x = -15.0f;

	VECTOR offset = { 0.0f, 20.0f, 800.0f };

	MATRIX RotY = MGetRotY(m_rot.y);
	MATRIX RotX = MGetRotX(m_rot.x);
	MATRIX Mult = MMult(RotX, RotY);

	offset = VTransform(offset, Mult);

	m_pos = VAdd(m_center, offset);

	//注視点にプレイヤーの座標を代入
	m_focus = m_center;
	//注視点の高さを調整
	m_focus.y += 30.0f;

	if (m_rot.y > DX_PI_F * 2.0f)
	{
		m_eventState = CAM_EVENT_PLAYWAIT;
		m_rot.y = DX_PI_F * 180.0f / 180.0f;
		m_rot.x = DX_PI_F * -25.0f / 180.0f;
	}
}

//
void C_PALYER_CAMERA_VEC::CamMovePlayWait()
{

}

//
void C_PALYER_CAMERA_VEC::CamMovePlay()
{
	if (C_XINPUT::GetConnectPad(DX_INPUT_PAD1))
	{
		m_rot.x += 0.05f * C_INPUT_CONFIG::IsStickInput(C_INPUT_CONFIG::COM_ROT_UD);
		m_rot.y += 0.05f * C_INPUT_CONFIG::IsStickInput(C_INPUT_CONFIG::COM_ROT_LR);
	}
	else
	{
		//キーコンフィグを利用した入力に変更する
		if (C_INPUT_CONFIG::IsButtanInputRep(C_INPUT_CONFIG::COM_ROT_L))	//左回転処理
		{
			m_rot.y += 0.05f;
		}
		else if (C_INPUT_CONFIG::IsButtanInputRep(C_INPUT_CONFIG::COM_ROT_R))	//右回転処理
		{
			m_rot.y -= 0.05f;
		}

		//キーコンフィグを利用した入力に変更する
		if (C_INPUT_CONFIG::IsButtanInputRep(C_INPUT_CONFIG::COM_ROT_U))	//左回転処理
		{
			m_rot.x += 0.05f;
		}
		else if (C_INPUT_CONFIG::IsButtanInputRep(C_INPUT_CONFIG::COM_ROT_D))	//右回転処理
		{
			m_rot.x -= 0.05f;
		}
	}

	float limitMax = DX_PI_F * 30.0f / 180.0f;
	float limitMin = DX_PI_F * 70.0f / 180.0f;

	if (m_rot.x > limitMax)
	{
		m_rot.x = limitMax;
	}
	else if (m_rot.x < -limitMin)
	{
		m_rot.x = -limitMin;
	}

	VECTOR offset = { 0.0f, 20.0f, 80.0f };

	MATRIX RotY = MGetRotY(m_rot.y);
	MATRIX RotX = MGetRotX(m_rot.x);
	MATRIX Mult = MMult(RotX, RotY);

	offset = VTransform(offset, Mult);

	m_pos = VAdd(m_center, offset);

	//注視点にプレイヤーの座標を代入
	m_focus = m_center;
	//注視点の高さを調整
	m_focus.y += 30.0f;
}

//
void C_PALYER_CAMERA_VEC::CamMoveRespawn()
{
	VECTOR vec = { 0 };

	return ;
}

//
void C_PALYER_CAMERA_VEC::CamMoveGoal()
{
	C_GLOBAL_DATA* globalData = C_GLOBAL_DATA::GetInstace();
	C_GLOBAL_DATA::T_FLAG_DATA* flagData = globalData->GetFlagData();

	m_center = flagData->GoalPos;

	m_speed += 5.0f;

	if (m_speed > 180.0f)
	{
		m_eventState = CAM_EVENT_NUM;
	}

	VECTOR offset = { 0.0f, 20.0f, 80.0f};

	MATRIX RotY = MGetRotY(m_rot.y);

	offset = VTransform(offset, RotY);

	m_pos = VAdd(m_center, offset);

	//注視点にプレイヤーの座標を代入
	m_focus = m_center;
	//注視点の高さを調整
	m_focus.y += m_speed;
}

//
void C_PALYER_CAMERA_VEC::ChangeCameraState()
{
	switch (m_state)
	{
	case C_PALYER_CAMERA_VEC::CAMERA_STATE_PLAYER:
		if (m_isTarget)m_state = CAMERA_STATE_TARGET;
		break;
	case C_PALYER_CAMERA_VEC::CAMERA_STATE_TARGET:
		m_state = CAMERA_STATE_PLAYER;
		break;
	}
}

//プレイヤーカメラ処理
void C_PALYER_CAMERA_VEC::PlayerCameraCalc(VECTOR _pos, float _rot, int _padID)
{
	const float MAX_LEN_NEAR = 70.0f;		//最大移動距離
	const float MAX_LEN_FAR = 80.0f;		//最大制限距離
	const float MIN_LEN_NEAR = 60.0f;		//最小移動距離
	const float MIN_LEN_FAR = 50.0f;		//最小制限距離

	//注視点にプレイヤーの座標を代入
	m_focus = _pos;
	//注視点の高さを調整
	m_focus.y += 30.0f;

	if (C_INPUT_CONFIG::IsButtanInputRep(C_INPUT_CONFIG::COM_ROT_L))	//左回転処理
	{
		//外積計算用のベクトル
		VECTOR v1 = { 0.0f, 1.0f, 0.0f };
		//現在の座標とプレイヤー座標の差
		VECTOR v2 = VSub(m_comPoint, m_focus);
		//ベクトルの外積で方向ベクトルを算出
		VECTOR speed = VCross(v1, v2);

		//移動ベクトルを正規化
		speed = VNorm(speed);
		//移動ベクトルを移動速度でスカラー倍する
		speed = VScale(speed, 2.0f);
		//座標に加算する
		m_comPoint = VAdd(m_comPoint, speed);
	}
	else if (C_INPUT_CONFIG::IsButtanInputRep(C_INPUT_CONFIG::COM_ROT_R))	//右回転処理
	{
		//外積計算用のベクトル
		VECTOR v1 = { 0.0f, 1.0f, 0.0f };
		//現在の座標とプレイヤー座標の差
		VECTOR v2 = VSub(m_comPoint, m_focus);
		//ベクトルの外積で方向ベクトルを算出
		VECTOR speed = VCross(v2, v1);

		//移動ベクトルを正規化
		speed = VNorm(speed);
		//移動ベクトルを移動速度でスカラー倍する
		speed = VScale(speed, 2.0f);
		//座標に加算する
		m_comPoint = VAdd(m_comPoint, speed);
	}

	//現在の座標からプレイヤーの座標を減算して方向ベクトルを算出
	VECTOR dir = VSub(m_comPoint, m_focus);
	//高さを0にする/今回のプログラムでは高さを考慮しない
	dir.y = 0;

	//方向ベクトルの長さを算出
	float len = VSize(dir);
	//方向ベクトルを正規化
	dir = VNorm(dir);

	//方向ベクトルの長さが最大移動距離よりも大きいとき
	if (len > MAX_LEN_NEAR)
	{
		//方向ベクトルを最大移動距離でスカラー倍
		dir = VScale(dir, MAX_LEN_NEAR);

		//プレイヤーの座標とスカラー倍した方向ベクトルを加算
		VECTOR tmpPos = VAdd(m_focus, dir);
		//加算した結果から現在の座標を減算
		VECTOR tmpDir = VSub(tmpPos, m_comPoint);
		//高さを0にする
		tmpDir.y = 0.0f;
		//計算結果を正規化
		tmpDir = VNorm(tmpDir);

		//カメラの移動速度を徐々に速くする
		if (m_moveTime < COM_MOVE_TIME)m_moveTime++;
		else if (m_moveTime > COM_MOVE_TIME)m_moveTime = COM_MOVE_TIME;

		m_speed = C_EASING::EasingInCubic(m_moveTime, COM_MOVE_TIME, COM_SPEED_MAX, 0.0f);
		if (m_speed > COM_SPEED_MAX)m_speed = COM_SPEED_MAX;

		//計算結果をカメラの移動速度でスカラー倍
		tmpDir = VScale(tmpDir, m_speed);
		//現在の座標に計算結果を加算
		m_comPoint = VAdd(m_comPoint, tmpDir);

		//現在の座標からプレイヤーの座標を減算
		tmpDir = VSub(m_comPoint, m_focus);
		//高さを0にする
		tmpDir.y = 0.0f;

		//ベクトルの長さの２乗が最大制限距離の２乗よりも大きい時
		if (VSquareSize(tmpDir) > MAX_LEN_FAR * MAX_LEN_FAR)
		{
			//計算結果を正規化
			tmpDir = VNorm(tmpDir);
			//計算結果を最大制限距離でスカラー倍
			tmpDir = VScale(tmpDir, MAX_LEN_FAR);
			//現在の座標にプレイヤーの座標と計算結果の和を代入
			m_comPoint = VAdd(m_focus, tmpDir);
		}
	}
	//方向ベクトルの長さが最小移動距離よりも小さいとき
	else if (len < MIN_LEN_NEAR)
	{
		//方向ベクトルを最小移動距離でスカラー倍
		dir = VScale(dir, MIN_LEN_NEAR);

		//プレイヤーの座標とスカラー倍した方向ベクトルを加算
		VECTOR tmpPos = VAdd(m_focus, dir);
		//加算した結果から現在の座標を減算
		VECTOR tmpDir = VSub(tmpPos, m_comPoint);
		//高さを0にする
		tmpDir.y = 0.0f;
		//計算結果を正規化
		tmpDir = VNorm(tmpDir);

		//カメラの移動速度を徐々に速くする
		if (m_moveTime < COM_MOVE_TIME)m_moveTime++;
		else if (m_moveTime > COM_MOVE_TIME)m_moveTime = COM_MOVE_TIME;

		m_speed = C_EASING::EasingInCubic(m_moveTime, COM_MOVE_TIME, COM_SPEED_MAX, 0.0f);
		if (m_speed > COM_SPEED_MAX)m_speed = COM_SPEED_MAX;

		//計算結果をカメラの移動速度でスカラー倍
		tmpDir = VScale(tmpDir, m_speed);
		//現在の座標に計算結果を加算
		m_comPoint = VAdd(m_comPoint, tmpDir);

		//現在の座標からプレイヤーの座標を減算
		tmpDir = VSub(m_comPoint, m_focus);
		//高さを0にする
		tmpDir.y = 0.0f;

		//ベクトルの長さの２乗が最小制限距離の２乗よりも大きい時
		if (VSquareSize(tmpDir) < MIN_LEN_FAR * MIN_LEN_FAR)
		{
			//計算結果を正規化
			tmpDir = VNorm(tmpDir);
			//計算結果を最小制限距離でスカラー倍
			tmpDir = VScale(tmpDir, MIN_LEN_FAR);
			//現在の座標にプレイヤーの座標と計算結果の和を代入
			m_comPoint = VAdd(m_focus, tmpDir);
		}
	}
	else
	{
		//カメラの移動速度を初期化
		if (m_moveTime > 0.0f)m_moveTime--;
		if (m_speed < 0.0f) m_speed = 0.0f;
	}


	//座標の高さに注視点の高さと補正値の和を代入
	m_comPoint.y = m_focus.y + 10.0f;
	//座標から注視点の座標を引いて方向ベクトルを取得
	dir = VSub(m_comPoint, m_focus);
	//方向ベクトルのXとZの成分でアークタンジェント関数からカメラのY軸の角度を算出
	m_rot.y = atan2f(dir.x, dir.z);
}

void C_PALYER_CAMERA_VEC::PlayerCameraCalcMat(VECTOR _center, float _rot, int _padID)
{
	m_center = _center;

	void (C_PALYER_CAMERA_VEC:: * stateFunc[])() = {
	& C_PALYER_CAMERA_VEC::CamMoveStart,
	& C_PALYER_CAMERA_VEC::CamMovePlayWait,
	& C_PALYER_CAMERA_VEC::CamMovePlay,
	& C_PALYER_CAMERA_VEC::CamMoveRespawn,
	& C_PALYER_CAMERA_VEC::CamMoveGoal,
	& C_PALYER_CAMERA_VEC::CamMoveGoal,
	};

	(this->*stateFunc[m_eventState])();
}

//ターゲットカメラ処理
void C_PALYER_CAMERA_VEC::TargetCameraCalc(VECTOR _focus, VECTOR _pos, float _rot, int _padID)
{
	//
	m_focus = _focus;
	m_focus.y += 25.0f;

	//
	m_comPoint = _pos;

	//
	VECTOR vec = VSub(m_comPoint, m_focus);
	float len = VSize(vec);
	vec = VNorm(vec);

	//
	vec = VScale(vec, 50.0f);
	m_comPoint = VAdd(m_comPoint, vec);

	//
	m_comPoint.y += 50.0f;

	//
	if (m_comPoint.y < 20.0f)
	{
		m_comPoint.y = 20.0f;
	}

	//
	m_rot.y = atan2f(vec.x, vec.z);

	//カメラの移動速度を徐々に速くする
	if (m_moveTime < COM_MOVE_TIME)m_moveTime++;
	else if (m_moveTime > COM_MOVE_TIME)m_moveTime = COM_MOVE_TIME;

	m_speed = C_EASING::EasingInCubic(m_moveTime, COM_MOVE_TIME, COM_SPEED_MAX, 0.0f);
	if (m_speed > COM_SPEED_MAX)m_speed = COM_SPEED_MAX;
}

//更新確定処理
void C_PALYER_CAMERA_VEC::Update()
{
	// DxLibの方にカメラを更新
	SetCameraPositionAndTargetAndUpVec(m_pos, m_focus, m_up);
}