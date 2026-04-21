#pragma once

#include "camera.h"
#include "game/data/global_data.h"

constexpr float COM_SPEED_MAX = 10.0f;
constexpr float COM_MOVE_TIME = 10.0f;

class C_PALYER_CAMERA_VEC : public C_CAMERA_BASE_VECTOR
{
public:

	//カメライベントの状態
	enum CAMERA_EVENT_STATE
	{
		CAM_EVENT_START,
		CAM_EVENT_PLAYWAIT,
		CAM_EVENT_PLAY,
		CAM_EVENT_RSPAWN,
		CAM_EVENT_GOAL,

		CAM_EVENT_NUM,
	};

private:

	enum CAMERA_STATE
	{
		CAMERA_STATE_PLAYER,
		CAMERA_STATE_TARGET,

		CAMERA_STATE_NUM,
	};

	float m_speed;

	float m_moveTime;

	bool m_isTarget;

	VECTOR m_comPoint;

	VECTOR m_center;

	CAMERA_STATE m_state;

	CAMERA_EVENT_STATE m_eventState;

	void CamMoveStart();

	void CamMovePlayWait();

	void CamMovePlay();

	void CamMoveRespawn();

	void CamMoveGoal();

public:

	//コンストラクタ
	C_PALYER_CAMERA_VEC(float _speed = 0.0f, float _moveTime = 0.0f, bool _isTarget = false,
		VECTOR _comPoint = { 0 }, VECTOR _center = { 0 }, CAMERA_STATE _state = CAMERA_STATE_NUM,
		CAMERA_EVENT_STATE _eventState = CAM_EVENT_NUM):
		m_speed(_speed), m_moveTime(_moveTime), m_center(_comPoint), m_isTarget(_isTarget),
		m_comPoint(_comPoint), m_state(_state), m_eventState(_eventState){}

	//デストラクタ
	~C_PALYER_CAMERA_VEC() {}

	//カメラの初期化
	void Init(VECTOR _pos, VECTOR _focus, VECTOR _up);

	//カメラの初期化
	void Init(VECTOR _pos, VECTOR _focus, VECTOR _up, CAMERA_EVENT_STATE _state);

	//カメラの終了処理
	void Exit();

	//更新処理
	void Step(VECTOR _focus, VECTOR _pos, float _rot, int _padID);
	//更新確定処理
	void Update();

	//リスポーン処理
	void Respwan(VECTOR _pos, VECTOR _focus, VECTOR _up);

	//プレイヤーカメラ処理
	void PlayerCameraCalc(VECTOR _pos, float _rot, int _padID);

	void PlayerCameraCalcMat(VECTOR _center, float _rot, int _padID);

	//ターゲットカメラ処理
	void TargetCameraCalc(VECTOR _focus, VECTOR _pos, float _rot, int _padID);

	//
	void ChangeCameraState();

	VECTOR GetCameraRot() { return m_rot; }

	void SetCameraRot(VECTOR _rot) { m_rot = _rot; }

	int GetCameraState() { return m_state; }

	void SetIsTarget(bool _isTarget) { m_isTarget = _isTarget; }

	CAMERA_EVENT_STATE GetEventState() const { return m_eventState; }

	void SetEventState(CAMERA_EVENT_STATE _eventState) { m_eventState = _eventState; }

};

//class C_PALYER_CAMERA_MAT : public C_CAMERA_BASE_MATRIX
//{
//	enum CAMERA_STATE
//	{
//		CAMERA_STATE_PLAYER,
//		CAMERA_STATE_TARGET,
//
//		CAMERA_STATE_NUM,
//	};
//
//
//
//private:
//
//	float m_speed;
//
//	float m_moveTime;
//
//	bool m_isTarget;
//
//	MATRIX m_comPoint;
//
//	CAMERA_STATE m_state;
//
//public:
//
//	//コンストラクタ
//	C_PALYER_CAMERA_MAT(float _speed = 0.0f, float _moveTime = 0.0f, bool _isTarget = false,
//		MATRIX _comPoint = { 0 }, CAMERA_STATE _state = CAMERA_STATE_NUM) :
//		m_speed(_speed), m_moveTime(_moveTime), m_isTarget(_isTarget),
//		m_comPoint(_comPoint), m_state(_state) {
//	}
//
//	//デストラクタ
//	~C_PALYER_CAMERA_MAT() {}
//
//	//カメラの初期化
//	void Init(VECTOR _pos, VECTOR _focus, VECTOR _up);
//
//	//カメラの終了処理
//	void Exit();
//
//	//更新処理
//	void Step(VECTOR _focus, VECTOR _pos, float _rot, int _padID);
//	//更新確定処理
//	void Update();
//
//	//プレイヤーカメラ処理
//	void PlayerCameraCalc(VECTOR _pos, float _rot, int _padID);
//
//	void PlayerCameraCalcMat(VECTOR _center, float _rot, int _padID);
//
//	//ターゲットカメラ処理
//	void TargetCameraCalc(VECTOR _focus, VECTOR _pos, float _rot, int _padID);
//
//	//
//	void ChangeCameraState();
//
//};

