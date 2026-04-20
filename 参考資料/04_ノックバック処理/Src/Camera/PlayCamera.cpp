#include "PlayCamera.h"
#include <math.h>
#include "../Input/Inputkey.h"

//	定義関連------------------------------
#define DEG_TO_RAD( a )		( a * DX_PI_F / 180.0f )

static const float CAMERA_LENGTH = 60.0f;		// 注視点から視点までの距離
static const float CAMERA_OFFSET_Y = 30.0f;		// 視点の高さ
//----------------------------------------


//-------------------------------
//		コンストラクタ
//-------------------------------
CPlayCamera::CPlayCamera()
{
	// ひとまず初期化をしておく
	memset(&m_pos, 0, sizeof(VECTOR));
	memset(&m_focus, 0, sizeof(VECTOR));
	memset(&m_up, 0, sizeof(VECTOR));
	memset(&m_camRot, 0, sizeof(VECTOR));
}


//-------------------------------
//		デストラクタ
//-------------------------------
CPlayCamera::~CPlayCamera()
{
}


//-------------------------------
//		初期化
//-------------------------------
void CPlayCamera::Init(VECTOR pos, VECTOR focus, VECTOR up)
{
	m_pos = pos;
	m_focus = focus;
	m_up = up;
}


//-------------------------------
//		終了処理
//-------------------------------
void CPlayCamera::Exit()
{
	// 実は今回何もやる事はない
}


//-------------------------------
//		毎フレーム呼ぶ処理
//-------------------------------
void CPlayCamera::Step(VECTOR focus, float rot)
{
#if 0
	static const float MAXLEN = 50.0f;		// 必ず離しておきたい距離

	// 今のカメラの位置からキャラクターまでの方向ベクトルを取得
	VECTOR dir = VSub(m_pos, focus);
	dir.y = 0.0f;			// 今回高さは固定なので無視

	// 一度長さを正規化し、離しておいてほしい距離を掛算する
	dir = VNorm(dir);
	dir = VScale(dir, MAXLEN);

	// ターゲットの位置に先ほどの結果を加算する
	m_pos = VAdd(focus, dir);

	m_focus = focus;
	// 視点・注視点の高さを上に移動させる
	m_focus.y += 1.0f;
	m_pos.y = focus.y += 25.0f;
	// カメラの方向ベクトルを元にY軸回転角度を求める
	m_camRot.y = atan2f(dir.x, dir.z);


#else
	static const float MAXLEN = 80.0f;		// これより距離が離れると移動開始
	static const float MAXLEN2 = 100.0f;		// これ以上は離れさせない
	static const float MINLEN = 60.0f;		// これより距離が近づくと移動開始
	static const float MINLEN2 = 40.0f;		// これ以上は近づけさせない
	static const float CAM_MOVE_SPEED = 0.5f;	// カメラの移動速度
	VECTOR temp, speed;

	// カメラの回転(今回は簡易用で遊びを持たせない)
	// 今回の回転は進行方向の外積をとって回転させる方法
	if(CheckHitKey(KEY_INPUT_RIGHT))
	{
		VECTOR v1, v2;
		v1 = VGet(0.0f, 1.0f, 0.0f);
		v2 = VSub(m_pos, focus);
		speed = VCross(v1, v2);
		speed = VNorm(speed);
		speed = VScale(speed, 2.0f);
		m_pos = VAdd(m_pos, speed);
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		VECTOR v1, v2;
		v1 = VGet(0.0f, 1.0f, 0.0f);
		v2 = VSub(m_pos, focus);
		speed = VCross(v2, v1);
		speed = VNorm(speed);
		speed = VScale(speed, 2.0f);
		m_pos = VAdd(m_pos, speed);
	}

	// 今のカメラの位置から注視点に向けての方向ベクトルを取得
	VECTOR dir = VSub(m_pos, focus);
	dir.y = 0.0f;			// 今回高さは固定なので無視

	float len = VSize(dir);	// 注視点までの距離を取得
	dir = VNorm(dir);			// 方向ベクトルを正規化

	// 一定以上距離が離れた
	if (len > MAXLEN)
	{
		// 本来の到達地点を計算
		temp = VScale(dir, MAXLEN);
		temp = VAdd(focus, temp);
		// 現在位置から本来の到達地点への方向ベクトル取得
		temp = VSub(temp, m_pos);
		temp.y = 0.0f;
		temp = VNorm(temp);
		// 本来の到達地点に向けて移動させる
		temp = VScale(temp, CAM_MOVE_SPEED);
		m_pos = VAdd(m_pos, temp);

		// 移動後の距離が最大距離を越えていたら、強制的に長さ変更
		temp = VSub(m_pos, focus);
		temp.y = 0.0f;
		if (VSquareSize(temp) > MAXLEN2 * MAXLEN2)
		{
			temp = VNorm(temp);
			temp = VScale(temp, MAXLEN2);
			m_pos = VAdd(focus, temp);
		}
	}
	// 一定以内の距離に近づいた
	else if (len < MINLEN)
	{
		// 本来の到達地点を計算
		temp = VScale(dir, MINLEN);
		temp = VAdd(focus, temp);
		// 現在位置から本来の到達地点への方向ベクトル取得
		temp = VSub(temp, m_pos);
		temp.y = 0.0f;
		temp = VNorm(temp);
		// 本来の到達地点に向けて移動させる
		temp = VScale(temp, CAM_MOVE_SPEED);
		m_pos = VAdd(m_pos, temp);

		// 移動後の距離が最小距離を越えていたら、強制的に長さ変更
		temp = VSub(m_pos, focus);
		temp.y = 0.0f;
		if (VSquareSize(temp) < MINLEN2 * MINLEN2)
		{
			temp = VNorm(temp);
			temp = VScale(temp, MINLEN2);
			m_pos = VAdd(focus, temp);
		}
	}

	m_focus = focus;
	m_focus.y += 3.0f;
	m_pos.y = focus.y += 40.0f;
	m_camRot.y = atan2f(dir.x, dir.z);
#endif

}

//-------------------------------
//		更新処理
//-------------------------------
void CPlayCamera::Update()
{
	// DxLibの方にカメラを更新
	SetCameraPositionAndTargetAndUpVec(m_pos, m_focus, m_up);
}

