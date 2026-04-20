#include "Player.h"
#include <math.h>
#include "../Input/Inputkey.h"


#define	ANIM_SPD			( 0.5f )	// アニメ再生速度
#define PL_RADIUS			( 3.0f )	// プレイヤーの半径
#define WALK_SPEED			( 0.5f )	// 歩き速度
#define RUN_SPEED			( 2.0f )	// 走り速度
#define GRAVITY				( 0.1f )	// 重力

//　アニメーションの数だけ準備
enum{
	PLSTATE_DEFAULT,	// デフォルト(基本的に使用しない)
	PLSTATE_WALK,		// 歩き
	PLSTATE_RUN,		// 走り
	PLSTATE_WAIT,		// 待機
	PLSTATE_DOWN,		// しゃがみ
	PLSTATE_DOWNATTACK,	// しゃがみ攻撃
	PLSTATE_ATTACK1,	// 立ち攻撃1
	PLSTATE_ATTACK2,	// 立ち攻撃2

	PLSTATE_NUM
};

//------------------------------
//		コンストラクタ
//------------------------------
Player::Player() : m_camRot({ 0.0f, 0.0f, 0.0f }), m_gravity(0.0f)
{
}


//------------------------------
//		デストラクタ
//------------------------------
Player::~Player()
{
}


//------------------------------
//		データ読み込み
//------------------------------
void	Player::LoadData()
{
	Model::LoadModel("Model/Char/char.pmd");
}


//------------------------------
//		初期設定セット
//------------------------------
void	Player::Reset()
{
	// 初期値をセット
	VECTOR	start = { 0.0f, 10.0f, 0.0f };
	VECTOR	zero = { 0.0f, 0.0f, 0.0f };
	Model::SetPosition(start);
	Model::SetRot(zero);

	Model::RequestLoop(PLSTATE_WAIT, ANIM_SPD);
}


//------------------------------
//		更新処理
//------------------------------
void	Player::Step()
{
	// モーションに合わせて行動を変える
	switch (Model::GetAnimID())
	{
	case PLSTATE_DEFAULT:
		// デフォルト
		Model::RequestLoop(PLSTATE_WAIT, ANIM_SPD);
		break;
	case PLSTATE_WALK:
		// 歩き
		ExecWalk();
		break;
	case PLSTATE_RUN:
		// 走り
		ExecRun();
		break;
	case PLSTATE_WAIT:
		// 待機
		ExecWait();
		break;
	case PLSTATE_DOWN:
		// しゃがみ
		ExecDown();
		break;
	case PLSTATE_DOWNATTACK:
		// しゃがみ攻撃
		ExecDownAttack();
		break;
	case PLSTATE_ATTACK1:
		// 立ち攻撃1
		ExecAttack1();
	case PLSTATE_ATTACK2:
		// 立ち攻撃2
		ExecAttack2();
		break;
	}

	// 重力更新
	UpdateGravity();
	// アニメーション更新
	Model::UpdateAnim();
}


//------------------------------
//		更新処理
//------------------------------
void	Player::Update()
{
	Model::Update();
}


//------------------------------
//		描画処理
//------------------------------
void	Player::Draw()
{
	Model::Draw();
	if(IsAttack())
		DrawSphere3D(GetAttackPos(), 5.0f, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}


//------------------------------
//		現在位置に座標加算
//------------------------------
void	Player::ReflectCollision(VECTOR addVec)
{
	// オールゼロなら何もしない
	if (addVec.x == 0.0f && addVec.y == 0.0f && addVec.z == 0.0f) return;

	VECTOR	pos = Model::GetPosition();
	pos = VAdd(pos, addVec);
	m_gravity = 0.0f;
	Model::SetPosition(pos);
}


//------------------------------
//		当たり判定の中心位置取得
//------------------------------
VECTOR	Player::GetCenter()
{
	VECTOR	center = Model::GetPosition();
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
//		攻撃中か判定
//------------------------------
bool	Player::IsAttack()
{
	// 現在のアニメーションIDを取得
	int state = Model::GetAnimID();
	// 指定されたアニメーションの時だけ攻撃とみなす
	if (state == PLSTATE_DOWNATTACK
		|| state == PLSTATE_ATTACK1
		|| state == PLSTATE_ATTACK2)
	{
		return true;
	}
	return false;
}


//------------------------------
//		攻撃した座標を取得
//------------------------------
VECTOR	Player::GetAttackPos()
{
	VECTOR pos = Model::GetPosition();
	VECTOR rot = Model::GetRot();
	VECTOR dir;
	//　当たり判定をプレイヤー前方へ移動させるための距離
	float len = -5.0f;	

	// プレイヤーの角度にあわせて回転させる
	dir.x = sinf(rot.y) * len;
	dir.z = cosf(rot.y) * len;
	// 地面に球の中心が来るので、上に上げる
	dir.y = GetRadius();

	pos = VAdd(pos, dir);

	return pos;
}


//------------------------------
//		歩き処理
//------------------------------
void	Player::ExecWalk()
{
	// 以下歩き中に行う事ができる行為
	// 優先順位に注意！

	// 通常攻撃
	if (InputKey::IsPushKeyTrg(KEY_INPUT_Z))
	{
		Model::RequestEndLoop(PLSTATE_ATTACK1, ANIM_SPD);
	}
	// しゃがみ
	else if(InputKey::IsPushKeyLaw(KEY_INPUT_X))
	{
		Model::RequestLoop(PLSTATE_DOWN, ANIM_SPD);
	}
	// 歩き・走り
	else
	{
		VECTOR spd = GetSpeed();
		// 移動していないようであれば待機へ
		if (spd.x == 0.0f && spd.y == 0.0f && spd.z == 0.0f)
		{
			Model::RequestLoop(PLSTATE_WAIT, ANIM_SPD);
		}
		else
		{
			// シフトキーを押していたら走りへ
			if (InputKey::IsPushKeyLaw(KEY_INPUT_LSHIFT))
			{
				Model::RequestLoop(PLSTATE_RUN, ANIM_SPD);
				spd = VScale(spd, RUN_SPEED);
			}
			// 何も無ければ歩きを維持
			else
			{
				spd = VScale(spd, WALK_SPEED);
			}
			CalcSpeed(spd);
		}
	}
}


//------------------------------
//		走り処理
//------------------------------
void	Player::ExecRun()
{
	// 以下走り中に行う事ができる行為
	// 優先順位に注意！

	// 通常攻撃
	if (InputKey::IsPushKeyTrg(KEY_INPUT_Z))
	{
		Model::RequestEndLoop(PLSTATE_ATTACK1, ANIM_SPD);
	}
	// しゃがみ
	else if (InputKey::IsPushKeyLaw(KEY_INPUT_X))
	{
		Model::RequestLoop(PLSTATE_DOWN, ANIM_SPD);
	}
	// 歩き・走り
	else
	{
		VECTOR spd = GetSpeed();
		// 移動していないようであれば待機へ
		if (spd.x == 0.0f && spd.y == 0.0f && spd.z == 0.0f)
		{
			Model::RequestLoop(PLSTATE_WAIT, ANIM_SPD);
		}
		else
		{
			// シフトキーを押していたら走りを維持
			if (InputKey::IsPushKeyLaw(KEY_INPUT_LSHIFT))
			{
				spd = VScale(spd, RUN_SPEED);
			}
			// 何も無ければ歩きへ
			else
			{
				Model::RequestLoop(PLSTATE_WALK, ANIM_SPD);
				spd = VScale(spd, WALK_SPEED);
			}
			CalcSpeed(spd);
		}
	}
}


//------------------------------
//		待機処理
//------------------------------
void	Player::ExecWait()
{
	// 以下待機中に行う事ができる行為
	// 優先順位に注意！

	// 通常攻撃
	if (InputKey::IsPushKeyTrg(KEY_INPUT_Z))
	{
		Model::RequestEndLoop(PLSTATE_ATTACK1, ANIM_SPD);
	}
	// しゃがみ
	else if (InputKey::IsPushKeyLaw(KEY_INPUT_X))
	{
		Model::RequestLoop(PLSTATE_DOWN, ANIM_SPD);
	}
	// 歩き・走り
	else
	{
		VECTOR spd = GetSpeed();
		if (spd.x != 0.0f || spd.y != 0.0f || spd.z != 0.0f)
		{
			// シフトキーを押していたら走りを維持
			if (InputKey::IsPushKeyLaw(KEY_INPUT_LSHIFT))
			{
				Model::RequestLoop(PLSTATE_RUN, ANIM_SPD);
				spd = VScale(spd, RUN_SPEED);
			}
			// 何も無ければ歩きへ
			else
			{
				Model::RequestLoop(PLSTATE_WALK, ANIM_SPD);
				spd = VScale(spd, WALK_SPEED);
			}
			CalcSpeed(spd);
		}
	}
}


//------------------------------
//		しゃがみ処理
//------------------------------
void	Player::ExecDown()
{
	// しゃがみ
	if (InputKey::IsPushKeyLaw(KEY_INPUT_X))
	{
		// しゃがみ中はしゃがみ攻撃に派生する
		if (InputKey::IsPushKeyTrg(KEY_INPUT_Z))
		{
			Model::RequestEndLoop(PLSTATE_DOWNATTACK, ANIM_SPD);
		}
	}
	else
	{
		VECTOR spd = GetSpeed();
		if (spd.x != 0.0f || spd.y != 0.0f || spd.z != 0.0f)
		{
			// シフトキーを押していたら走りを維持
			if (InputKey::IsPushKeyLaw(KEY_INPUT_LSHIFT))
			{
				Model::RequestLoop(PLSTATE_RUN, ANIM_SPD);
				spd = VScale(spd, RUN_SPEED);
			}
			// 何も無ければ歩きへ
			else
			{
				Model::RequestLoop(PLSTATE_WALK, ANIM_SPD);
				spd = VScale(spd, WALK_SPEED);
			}
			CalcSpeed(spd);
		}
		else
		{
			// 待機へ
			Model::RequestLoop(PLSTATE_WAIT, ANIM_SPD);
		}
	}
}


//------------------------------
//		しゃがみ攻撃処理
//------------------------------
void	Player::ExecDownAttack()
{
	// しゃがみ攻撃が終わってから次へ
	if (Model::IsEndAnim() == false) return;

	// しゃがみ
	if (InputKey::IsPushKeyLaw(KEY_INPUT_X))
	{
		Model::RequestLoop(PLSTATE_DOWN, ANIM_SPD);
	}
	// 歩き・走り
	else
	{
		VECTOR spd = GetSpeed();
		if (spd.x != 0.0f || spd.y != 0.0f || spd.z != 0.0f)
		{
			// シフトキーを押していたら走りを維持
			if (InputKey::IsPushKeyLaw(KEY_INPUT_LSHIFT))
			{
				Model::RequestLoop(PLSTATE_RUN, ANIM_SPD);
				spd = VScale(spd, RUN_SPEED);
			}
			// 何も無ければ歩きへ
			else
			{
				Model::RequestLoop(PLSTATE_WALK, ANIM_SPD);
				spd = VScale(spd, WALK_SPEED);
			}
			CalcSpeed(spd);
		}
		else
		{
			// 待機へ
			Model::RequestLoop(PLSTATE_WAIT, ANIM_SPD);
		}
	}
}


//------------------------------
//		立ち攻撃1処理
//------------------------------
void	Player::ExecAttack1()
{
	// 8フレーム以降は次の攻撃へキャンセル可能
	if(Model::GetAnimFrm() >= 8.0f)
	{
		if (InputKey::IsPushKeyTrg(KEY_INPUT_Z))
		{
			Model::RequestEndLoop(PLSTATE_ATTACK2, ANIM_SPD);
			return;
		}
	}

	// 攻撃が終わってから次へ
	if (Model::IsEndAnim() == false) return;

	// しゃがみ
	if (InputKey::IsPushKeyLaw(KEY_INPUT_X))
	{
		Model::RequestLoop(PLSTATE_DOWN, ANIM_SPD);
	}
	// 歩き・走り
	else
	{
		VECTOR spd = GetSpeed();
		if (spd.x != 0.0f || spd.y != 0.0f || spd.z != 0.0f)
		{
			// シフトキーを押していたら走りを維持
			if (InputKey::IsPushKeyLaw(KEY_INPUT_LSHIFT))
			{
				Model::RequestLoop(PLSTATE_RUN, ANIM_SPD);
				spd = VScale(spd, RUN_SPEED);
			}
			// 何も無ければ歩きへ
			else
			{
				Model::RequestLoop(PLSTATE_WALK, ANIM_SPD);
				spd = VScale(spd, WALK_SPEED);
			}
			CalcSpeed(spd);
		}
		else
		{
			// 待機へ
			Model::RequestLoop(PLSTATE_WAIT, ANIM_SPD);
		}
	}
}


//------------------------------
//		立ち攻撃2処理
//------------------------------
void	Player::ExecAttack2()
{
	// 攻撃が終わってから次へ
	if (Model::IsEndAnim() == false) return;

	// しゃがみ
	if (InputKey::IsPushKeyLaw(KEY_INPUT_X))
	{
		Model::RequestLoop(PLSTATE_DOWN, ANIM_SPD);
	}
	// 歩き・走り
	else
	{
		VECTOR spd = GetSpeed();
		if (spd.x != 0.0f || spd.y != 0.0f || spd.z != 0.0f)
		{
			// シフトキーを押していたら走りを維持
			if (InputKey::IsPushKeyLaw(KEY_INPUT_LSHIFT))
			{
				Model::RequestLoop(PLSTATE_RUN, ANIM_SPD);
				spd = VScale(spd, RUN_SPEED);
			}
			// 何も無ければ歩きへ
			else
			{
				Model::RequestLoop(PLSTATE_WALK, ANIM_SPD);
				spd = VScale(spd, WALK_SPEED);
			}
			CalcSpeed(spd);
		}
		else
		{
			// 待機へ
			Model::RequestLoop(PLSTATE_WAIT, ANIM_SPD);
		}
	}
}


//------------------------------
//		十字キーによる移動方向取得
//------------------------------
VECTOR	Player::GetSpeed()
{
	bool	isMove = false;

	// プレイヤー移動
	VECTOR	plSpd = { 0.0f, 0.0f, 0.0f };
	float	spd = 1.0f;

	if (InputKey::IsPushKeyLaw(KEY_INPUT_D))
	{
		plSpd.x -= spd;
	}
	if (InputKey::IsPushKeyLaw(KEY_INPUT_A))
	{
		plSpd.x += spd;
	}
	if (InputKey::IsPushKeyLaw(KEY_INPUT_W))
	{
		plSpd.z -= spd;
	}
	if (InputKey::IsPushKeyLaw(KEY_INPUT_S))
	{
		plSpd.z += spd;
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
	}

	return plSpd;
}


//------------------------------
//		速度をプレイヤーに反映させる
//------------------------------
void	Player::CalcSpeed(VECTOR speed)
{
	// 速度を加算
	VECTOR playerPos = Model::GetPosition();
	playerPos = VAdd(playerPos, speed);
	// 移動速度からY軸回転角度を取得
	float rotY = atan2f(-speed.x, -speed.z);

	Model::SetPosition(playerPos);
	Model::SetRot(VGet(0.0f, rotY, 0.0f));
}


//------------------------------
//		重力更新
//------------------------------
void	Player::UpdateGravity()
{
	VECTOR playerPos = Model::GetPosition();
	m_gravity -= GRAVITY;
	playerPos.y += m_gravity;
	Model::SetPosition(playerPos);
}