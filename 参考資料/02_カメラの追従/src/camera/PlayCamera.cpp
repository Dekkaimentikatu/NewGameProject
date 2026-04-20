#include "PlayCamera.h"
#include <math.h>
#include "../Input/InputKey.h"

//	定義関連------------------------------
#define DEG_TO_RAD( a )		( a * DX_PI_F / 180.0f )

static const float CAMERA_LENGTH = 60.0f;		// 注視点から視点までの距離
static const float CAMERA_OFFSET_Y = 30.0f;		// 視点の高さ
//----------------------------------------


//-------------------------------
//		コンストラクタ
//-------------------------------
PlayCamera::PlayCamera()
{
	// ひとまず初期化をしておく
	memset(&m_pos, 0, sizeof(VECTOR));
	memset(&m_focus, 0, sizeof(VECTOR));
	memset(&m_up, 0, sizeof(VECTOR));
	memset(&m_camRot, 0, sizeof(VECTOR));
	m_camRot.x = -0.2f;
}


//-------------------------------
//		デストラクタ
//-------------------------------
PlayCamera::~PlayCamera()
{
}


//-------------------------------
//		初期化
//-------------------------------
void PlayCamera::Init(VECTOR pos, VECTOR focus, VECTOR up)
{
	m_pos = pos;
	m_focus = focus;
	m_up = up;
}


//-------------------------------
//		終了処理
//-------------------------------
void PlayCamera::Exit()
{
	// 実は今回何もやる事はない
}


//-------------------------------
//		毎フレーム呼ぶ処理
//-------------------------------
void PlayCamera::Step(VECTOR focus, float rot)
{
	const float MAX_LEN_NEAR = 50.0f;		//最大移動距離
	const float MAX_LEN_FAR = 60.0f;		//最大制限距離
	const float MIN_LEN_NEAR = 40.0f;		//最小移動距離
	const float MIN_LEN_FAR = 30.0f;		//最小制限距離
	const float CAM_MOVE_SPEED = 0.5f;		//移動速度

	if (CheckHitKey(KEY_INPUT_LEFT))	//左回転処理
	{
		//外積計算用のベクトル
		VECTOR v1 = { 0.0f, 1.0f, 0.0f };
		//現在の座標とプレイヤー座標の差
		VECTOR v2 = VSub(m_pos, focus);
		//ベクトルの外積で方向ベクトルを算出
		VECTOR speed = VCross(v1, v2);

		//移動ベクトルを正規化
		speed = VNorm(speed);
		//移動ベクトルを移動速度でスカラー倍する
		speed = VScale(speed, 2.0f);
		//座標に加算する
		m_pos = VAdd(m_pos, speed);
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))	//右回転処理
	{
		//外積計算用のベクトル
		VECTOR v1 = { 0.0f, 1.0f, 0.0f };
		//現在の座標とプレイヤー座標の差
		VECTOR v2 = VSub(m_pos, focus);
		//ベクトルの外積で方向ベクトルを算出
		VECTOR speed = VCross(v2, v1);

		//移動ベクトルを正規化
		speed = VNorm(speed);
		//移動ベクトルを移動速度でスカラー倍する
		speed = VScale(speed, 2.0f);
		//座標に加算する
		m_pos = VAdd(m_pos, speed);
	}

	//現在の座標からプレイヤーの座標を減算して方向ベクトルを算出
	VECTOR dir = VSub(m_pos, focus);
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
		VECTOR tmpPos = VAdd(focus, dir);
		//加算した結果から現在の座標を減算
		VECTOR tmpDir = VSub(tmpPos, m_pos);
		//高さを0にする
		tmpDir.y = 0.0f;
		//計算結果を正規化
		tmpDir = VNorm(tmpDir);

		//計算結果をカメラの移動速度でスカラー倍
		tmpDir = VScale(tmpDir, CAM_MOVE_SPEED);
		//現在の座標に計算結果を加算
		m_pos = VAdd(m_pos, tmpDir);

		//現在の座標からプレイヤーの座標を減算
		tmpDir = VSub(m_pos, focus);
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
			m_pos = VAdd(focus, tmpDir);
		}
	}
	//方向ベクトルの長さが最小移動距離よりも小さいとき
	else if (len < MIN_LEN_NEAR)
	{
		//方向ベクトルを最小移動距離でスカラー倍
		dir = VScale(dir, MIN_LEN_NEAR);

		//プレイヤーの座標とスカラー倍した方向ベクトルを加算
		VECTOR tmpPos = VAdd(focus, dir);
		//加算した結果から現在の座標を減算
		VECTOR tmpDir = VSub(tmpPos, m_pos);
		//高さを0にする
		tmpDir.y = 0.0f;
		//計算結果を正規化
		tmpDir = VNorm(tmpDir);

		//計算結果をカメラの移動速度でスカラー倍
		tmpDir = VScale(tmpDir, CAM_MOVE_SPEED);
		//現在の座標に計算結果を加算
		m_pos = VAdd(m_pos, tmpDir);

		//現在の座標からプレイヤーの座標を減算
		tmpDir = VSub(m_pos, focus);
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
			m_pos = VAdd(focus, tmpDir);
		}
	}

	//注視点にプレイヤーの座標を代入
	m_focus = focus;
	//注視点の高さを調整
	m_focus.y += 15.0f;
	//座標の高さに注視点の高さと補正値の和を代入
	m_pos.y = m_focus.y + 25.0f;
	//座標から注視点の座標を引いて方向ベクトルを取得
	dir = VSub(m_pos, m_focus);
	//方向ベクトルのXとZの成分でアークタンジェント関数からカメラのY軸の角度を算出
	m_camRot.y = atan2f(dir.x, dir.z);


}

//-------------------------------
//		更新処理
//-------------------------------
void PlayCamera::Update()
{
	// DxLibの方にカメラを更新
	SetCameraPositionAndTargetAndUpVec(m_pos, m_focus, m_up);
}

