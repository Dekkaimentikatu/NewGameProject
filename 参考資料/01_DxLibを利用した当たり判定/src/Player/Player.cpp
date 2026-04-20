#include "Player.h"
#include <math.h>
#include "../Input/InputKey.h"


#define DEG_TO_RAD( a )		( a * DX_PI_F / 180.0f )
#define	ANIM_SPD			( 1.0f )
#define PL_RADIUS			( 3.0f )
#define GRAVITY				( 0.09f )
#define	JUMP_POW			( 3.0f )

enum {
	PLSTATE_DEFAULT,	// デフォルト
	PLSTATE_WALK,		// 歩き

	PLSTATE_NUM
};

//------------------------------
//		コンストラクタ
//------------------------------
Player::Player() : m_gravity(0.0f), m_hndl(-1), m_state(PLSTATE_DEFAULT),
m_animIndex(-1)
{
	m_camRot = VGet(0.0f, 0.0f, 0.0f);
}


//------------------------------
//		デストラクタ
//------------------------------
Player::~Player()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}
}


//------------------------------
//		データ読み込み
//------------------------------
void	Player::LoadData()
{
	m_hndl = MV1LoadModel("model/char/char.pmd");
}


//------------------------------
//		初期設定セット
//------------------------------
void	Player::Reset()
{
	// 初期値をセット
	VECTOR	start = { 0.0f, 10.0f, 0.0f };
	VECTOR	zero = { 0.0f, 0.0f, 0.0f };
	MV1SetPosition(m_hndl, start);
	MV1SetRotationXYZ(m_hndl, zero);
	m_camRot = zero;
	m_gravity = 0.0f;

	RequestAnim(PLSTATE_DEFAULT);
}


//------------------------------
//		更新処理
//------------------------------
void	Player::Calc()
{
	// モーションに合わせて行動を変える
	switch (m_state)
	{
	case PLSTATE_DEFAULT:
		CalcJump();
		if (CalcMove())
		{
			RequestAnim(PLSTATE_WALK);
			m_state = PLSTATE_WALK;
		}
		break;
	case PLSTATE_WALK:
		CalcJump();
		if (!CalcMove())
		{
			RequestAnim(PLSTATE_DEFAULT);
			m_state = PLSTATE_DEFAULT;
		}
		break;
	}

	// アニメーション更新
	float	totalAnimTime = MV1GetAttachAnimTotalTime(m_hndl, m_animIndex);
	m_animCnt += ANIM_SPD;
	if (m_animCnt >= totalAnimTime) m_animCnt = 0.0f;
	MV1SetAttachAnimTime(m_hndl, m_animIndex, m_animCnt);
}


//------------------------------
//		カメラ処理
//------------------------------
void	Player::CalcCamera()
{
	const float rotSpd = 1.0f;

	if (InputKey::IsPushKeyLaw(KEY_INPUT_RIGHT))
	{
		m_camRot.y += DEG_TO_RAD(rotSpd);
	}
	if (InputKey::IsPushKeyLaw(KEY_INPUT_LEFT))
	{
		m_camRot.y -= DEG_TO_RAD(rotSpd);
	}
	if (InputKey::IsPushKeyLaw(KEY_INPUT_UP))
	{
		m_camRot.x -= DEG_TO_RAD(rotSpd);
	}
	if (InputKey::IsPushKeyLaw(KEY_INPUT_DOWN))
	{
		m_camRot.x += DEG_TO_RAD(rotSpd);
	}

	// カメラはプレイヤーに追従
	VECTOR	camDist = { 0.0f, 0.0f, 50.0f };
	VECTOR	playerPos = MV1GetPosition(m_hndl);
	playerPos.y += 5.0f;	// ちょっと上にあげる
	MATRIX	mat1, mat2;
	// 回転行列を利用してカメラ位置設定
	mat1 = MGetTranslate(camDist);
	mat2 = MGetRotX(m_camRot.x);
	mat1 = MMult(mat1, mat2);
	mat2 = MGetRotY(m_camRot.y);
	mat1 = MMult(mat1, mat2);
	camDist = VGet(mat1.m[3][0], mat1.m[3][1], mat1.m[3][2]);
	camDist = VAdd(playerPos, camDist);
	SetCameraPositionAndTarget_UpVecY(camDist, playerPos);
}


//------------------------------
//		描画処理
//------------------------------
void	Player::Draw()
{
	MV1DrawModel(m_hndl);
	DrawSphere3D(GetCenter(), GetRadius(), 32, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}


//------------------------------
//		現在位置に座標加算
//------------------------------
void	Player::ReflectCollision(VECTOR addVec)
{
	// オールゼロなら何もしない
	if (addVec.x == 0.0f && addVec.y == 0.0f && addVec.z == 0.0f) return;

	VECTOR	pos = MV1GetPosition(m_hndl);
	pos = VAdd(pos, addVec);
	MV1SetPosition(m_hndl, pos);
	m_gravity = 0.0f;	// とりあえず物体にぶつかったら重力を0に
}


//------------------------------
//		当たり判定の中心位置取得
//------------------------------
VECTOR	Player::GetCenter()
{
	VECTOR	center = MV1GetPosition(m_hndl);
	center.y += PL_RADIUS;
	return center;
}


//------------------------------
//		当たり判定の半径取得
//------------------------------
float	Player::GetRadius()
{
	return PL_RADIUS;
}


//------------------------------
//		描画処理
//------------------------------
void	Player::RequestAnim(int animID)
{

	if (m_animIndex != -1)
	{
		MV1DetachAnim(m_hndl, m_animIndex);
	}
	m_animIndex = MV1AttachAnim(m_hndl, animID);
	m_animCnt = 0.0f;
}


//------------------------------
//		移動処理
//------------------------------
bool	Player::CalcMove()
{
	bool	isMove = false;

	// プレイヤー移動
	VECTOR	playerPos = MV1GetPosition(m_hndl);
	VECTOR	plSpd = { 0.0f, 0.0f, 0.0f };
	float	fSpd = 1.0f;

	if (InputKey::IsPushKeyLaw(KEY_INPUT_D))
	{
		plSpd.x -= fSpd;
	}
	if (InputKey::IsPushKeyLaw(KEY_INPUT_A))
	{
		plSpd.x += fSpd;
	}
	if (InputKey::IsPushKeyLaw(KEY_INPUT_W))
	{
		plSpd.z -= fSpd;
	}
	if (InputKey::IsPushKeyLaw(KEY_INPUT_S))
	{
		plSpd.z += fSpd;
	}

	// 移動しているようであれば更新
	if (plSpd.x != 0.0f || plSpd.z != 0.0f)
	{
		// 速度を正規化
		plSpd = VNorm(plSpd);
		// 回転行列を利用してカメラ位置設定
		MATRIX	mat1, mat2;
		mat1 = MGetTranslate(plSpd);
		mat2 = MGetRotY(m_camRot.y);
		mat1 = MMult(mat1, mat2);
		plSpd = VGet(mat1.m[3][0], mat1.m[3][1], mat1.m[3][2]);
		playerPos = VAdd(playerPos, plSpd);
		// 移動速度からY軸回転角度を取得
		float rotY = atan2f(-plSpd.x, -plSpd.z);
		MV1SetRotationXYZ(m_hndl, VGet(0.0f, rotY, 0.0f));

		isMove = true;
	}

	// 重力値更新 封印しておきます
	m_gravity -= GRAVITY;
	playerPos.y += m_gravity;

	MV1SetPosition(m_hndl, playerPos);

	return isMove;
}


//------------------------------
//		ジャンプ処理
//------------------------------
bool	Player::CalcJump()
{
	bool	isResult = false;

	// とりあえず封印

	if (InputKey::IsPushKeyTrg(KEY_INPUT_SPACE))
	{
		m_gravity = JUMP_POW;
		isResult = true;
	}

	return isResult;
}