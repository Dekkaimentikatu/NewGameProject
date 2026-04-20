#pragma once

#include <DxLib.h>
#include <math.h>
#include "lib/xinput.h"
#include "lib/input.h"

class C_CAMERA_BASE_VECTOR
{
protected:

	//座標
	VECTOR m_pos;
	//回転
	VECTOR m_rot;
	//注視点
	VECTOR m_focus;
	//カメラの上方向
	VECTOR m_up;

public:

	//コンストラクタ
	C_CAMERA_BASE_VECTOR(VECTOR _pos = { 0 }, VECTOR _rot = { 0 }, VECTOR _focus = { 0 }, VECTOR _up = { 0 }):
	m_pos(_pos), m_rot(_rot), m_focus(_focus), m_up(_up){}

	//デストラクタ
	virtual ~C_CAMERA_BASE_VECTOR() {}

	//カメラの初期化
	virtual void Init(VECTOR _pos, VECTOR _focus, VECTOR _up);

	//カメラの終了処理
	virtual void Exit();

	//更新処理
	virtual void Step(VECTOR _focus, VECTOR _pos,float _rot, int _padID) = 0;
	//更新確定処理
	virtual void Update() = 0;


	// 視点取得
	VECTOR GetPosition()const { return m_pos; }
	// 視点設定
	void SetPosition(VECTOR pos) { m_pos = pos; }
	// 注視点取得
	VECTOR GetFocus()const { return m_focus; }
	// アップベクトル取得
	VECTOR GetUpvec()const { return m_up; }
	// カメラ角度取得
	VECTOR GetCameraRot()const { return m_rot; }

	virtual int GetCameraState() = 0;

};

class C_CAMERA_BASE_MATRIX
{
protected:

	//座標
	MATRIX m_pos;
	//回転
	MATRIX m_rot;
	//注視点
	MATRIX m_focus;
	//カメラの上方向
	MATRIX m_up;

public:

	enum Dir
	{
		X,
		Y,
		Z,
	};

	//コンストラクタ
	C_CAMERA_BASE_MATRIX(MATRIX _pos = { 0 }, MATRIX _rot = { 0 }, MATRIX _focus = { 0 }, MATRIX _up = { 0 }) :
		m_pos(_pos), m_rot(_rot), m_focus(_focus), m_up(_up) {
	}

	//デストラクタ
	virtual ~C_CAMERA_BASE_MATRIX() {}

	//カメラの初期化
	virtual void Init(VECTOR _pos, VECTOR _focus, VECTOR _up);

	//カメラの終了処理
	virtual void Exit();

	//更新処理
	virtual void Step(VECTOR _focus, VECTOR _pos, float _rot, int _padID) = 0;
	//更新確定処理
	virtual void Update() = 0;


	// 視点取得
	MATRIX GetPosition()const { return m_pos; }
	// 視点設定
	void SetPosition(MATRIX pos) { m_pos = pos; }
	// 注視点取得
	MATRIX GetFocus()const { return m_focus; }
	// アップベクトル取得
	MATRIX GetUpvec()const { return m_up; }
	// カメラ角度取得
	MATRIX GetCameraRot()const { return m_rot; }

	virtual int GetCameraState() = 0;
};