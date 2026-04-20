#include "Enemy.h"
#include <math.h>


#define	ANIM_SPD			( 0.5f )	// アニメ再生速度
#define PL_RADIUS			( 3.0f )	// プレイヤーの半径
#define WALK_SPEED			( 0.5f )	// 歩き速度
#define GRAVITY				( 0.1f )	// 重力

// ルート番号
static const int ROOT_ID[] = { 1, 2, 3, 4, 5, 6 };
// ルートの個数
static const int ROOT_NUM = 6;

//　敵の移動タイプ
enum{
	STATE_LOOT,		// ルート巡回
	STATE_CHACE,	// 追いかける
	STATE_BACK,		// ノックバック中

	STATE_NUM
};

//------------------------------
//		コンストラクタ
//------------------------------
Enemy::Enemy() : m_speed({ 0.0f, 0.0f, 0.0f }), m_rootHndl(-1),
m_rootID(0), m_state(0)
{

}


//------------------------------
//		デストラクタ
//------------------------------
Enemy::~Enemy()
{
}


//------------------------------
//		ロード
//------------------------------
void	Enemy::LoadData()
{
	Player::LoadData();
	if (m_rootHndl == -1)
	{
		m_rootHndl = MV1LoadModel("Model/Bg/Model/root.x");
	}
}


//------------------------------
//		初期設定セット
//------------------------------
void	Enemy::Reset()
{
	// スケールを表示ステージとあわせる
	MV1SetScale(m_rootHndl, VGet(0.05f, 0.05f, 0.05f));
	// 初期値をセット
	// パスの0番目をスタート位置とする
	VECTOR	start = MV1GetFramePosition(m_rootHndl, ROOT_ID[0]);
	VECTOR	zero = { 0.0f, 0.0f, 0.0f };
	Model::SetPosition(start);
	Model::SetRot(zero);
	// 0番目のルートに配置したので、次の目的地は1
	m_rootID = 1;
	// 敵の最初の行動を設定
	m_state = STATE_LOOT;

	// 歩きアニメーションを再生
	Model::RequestLoop(1, ANIM_SPD);
}


//------------------------------
//		更新処理
//------------------------------
void	Enemy::Step(VECTOR playerPos)
{
	switch (m_state)
	{
	case STATE_LOOT:
		// ルート通りに移動
		MoveRoot(playerPos);
		break;
	case STATE_CHACE:
		// ターゲットを追いかける
		ChaceTarget(playerPos);
		break;
	case STATE_BACK:
		//ノックバック処理
		MoveBack();
		break;
	}
	// 重力更新
	Player::UpdateGravity();
	// アニメーション更新
	Model::UpdateAnim();
}


//------------------------------
//		ヒットした後の処理
//------------------------------
void	Enemy::HitCalc(VECTOR speed)
{
	//エネミーの状態を変更
	m_state = STATE_BACK;

	//ノックバックベクトルを更新
	m_speed = speed;
}


//------------------------------
//		ルートを歩く
//------------------------------
void	Enemy::MoveRoot(VECTOR playerPos)
{
	// 次の目的地の座標取得
	VECTOR targetPos = MV1GetFramePosition(m_rootHndl, ROOT_ID[m_rootID]);
	// 自分の座標取得
	VECTOR pos = GetPosition();
	// 目的地へのベクトル取得
	VECTOR dir = VSub(targetPos, pos);
	// 目的地までの距離を取得
	float len = VSize(dir);

	// 目的地までの距離が一定範囲内なら
	if (len < 1.5f)
	{
		// 直接目的地をセット
		SetPosition(targetPos);
		// 目的地を一つ次へ
		m_rootID = (m_rootID + 1) % ROOT_NUM;
	}
	else
	{
		// いったん正規化して
		dir.y = 0.0f;
		dir = VNorm(dir);
		// 実際の移動速度に変更
		dir = VScale(dir, WALK_SPEED);
		// 速度を加算してキャラクターにセット
		pos = VAdd(pos, dir);
		SetPosition(pos);
	}

	// 進行方向を向かせる(これは便利なので関数化しておいてもいいかも)
	float rot = atan2f(-dir.x, -dir.z);
	SetRot(VGet(0.0f, rot, 0.0f));

	// 一定範囲内に入れば、追いかける行動へ
	if (IsNearTarget(playerPos, 50.0f) == true)
	{
		m_state = STATE_CHACE;
	}
	
}


//------------------------------
//		ターゲットを追いかける
//------------------------------
void	Enemy::ChaceTarget(VECTOR playerPos)
{
	// 自分の座標取得
	VECTOR pos = GetPosition();
	// 目的地へのベクトル取得
	VECTOR dir = VSub(playerPos, pos);
	// いったん正規化して
	dir.y = 0.0f;
	dir = VNorm(dir);
	// 実際の移動速度に変更
	dir = VScale(dir, WALK_SPEED);
	// 速度を加算してキャラクターにセット
	pos = VAdd(pos, dir);
	SetPosition(pos);

	// 進行方向を向かせる
	float rot = atan2f(-dir.x, -dir.z);
	SetRot(VGet(0.0f, rot, 0.0f));

	// 一定範囲から離れたら、次の行動へ
	if (IsNearTarget(playerPos, 100.0f) == false)
	{
		m_state = STATE_LOOT;
	}
}


//------------------------------
//		ノックバック
//------------------------------
void	Enemy::MoveBack()
{
	VECTOR pos = GetPosition();

	//ノックバックの移動ベクトルを計算
	pos = VAdd(pos, m_speed);
	Model::SetPosition(pos);

	//ノックバックを徐々に減衰させる
	m_speed = VScale(m_speed, 0.9f);

	//一定速度よりも遅くなったらノックバック終了
	if (VSize(m_speed) < 0.1f)
	{
		m_state = STATE_CHACE;
	}
}


//------------------------------
//		ターゲットが近くにいるか判定
//------------------------------
bool	Enemy::IsNearTarget(VECTOR playerPos, float radius)
{
	// 自分の座標取得
	VECTOR pos = GetPosition();
	// 目的地へのベクトル取得
	VECTOR dir = VSub(playerPos, pos);
	// 2点間の距離を調べる
	float len = VSize(dir);
	// 引数で指定された範囲内かで戻り値を決める
	if (len < radius) return true;
	else return false;
}
