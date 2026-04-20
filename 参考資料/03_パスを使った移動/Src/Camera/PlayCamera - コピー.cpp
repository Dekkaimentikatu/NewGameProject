#include "PlayCamera.h"
#include <math.h>
#include "../input/inputkey.h"

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
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vFocus, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
	memset(&m_vCamRot, 0, sizeof(VECTOR));
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
void CPlayCamera::Init(VECTOR vPos, VECTOR vFocus, VECTOR vUp)
{
	m_vPos = vPos;
	m_vFocus = vFocus;
	m_vUp = vUp;
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
void CPlayCamera::Step(VECTOR vFocus, float fRot)
{

	const float fRotSpd = 1.0f;

	if (CInputKey::IsPushKeyLaw(KEY_INPUT_RIGHT))
	{
		m_vCamRot.y += DEG_TO_RAD(fRotSpd);
	}
	if (CInputKey::IsPushKeyLaw(KEY_INPUT_LEFT))
	{
		m_vCamRot.y -= DEG_TO_RAD(fRotSpd);
	}
	if (CInputKey::IsPushKeyLaw(KEY_INPUT_UP))
	{
		m_vCamRot.x -= DEG_TO_RAD(fRotSpd);
	}
	if (CInputKey::IsPushKeyLaw(KEY_INPUT_DOWN))
	{
		m_vCamRot.x += DEG_TO_RAD(fRotSpd);
	}

	// カメラはプレイヤーに追従
	VECTOR	vCamDist = { 0.0f, 0.0f, 50.0f };
	VECTOR	vPlayerPos = vFocus;
	vPlayerPos.y += 5.0f;	// ちょっと上にあげる
	MATRIX	mMat1, mMat2;
	// 回転行列を利用してカメラ位置設定
	mMat1 = MGetTranslate(vCamDist);
	mMat2 = MGetRotX(m_vCamRot.x);
	mMat1 = MMult(mMat1, mMat2);
	mMat2 = MGetRotY(m_vCamRot.y);
	mMat1 = MMult(mMat1, mMat2);
	vCamDist = VGet(mMat1.m[3][0], mMat1.m[3][1], mMat1.m[3][2]);
	vCamDist = VAdd(vPlayerPos, vCamDist);
	m_vPos = vCamDist;
	m_vFocus = vPlayerPos;
}

//-------------------------------
//		更新処理
//-------------------------------
void CPlayCamera::Update()
{
	// DxLibの方にカメラを更新
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vFocus, m_vUp);
}

