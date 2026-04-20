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
enum {
	STATE_LOOT,		// ルート巡回
	STATE_CHACE,	// 追いかける

	STATE_NUM
};

//------------------------------
//		コンストラクタ
//------------------------------
Enemy::Enemy() : m_rootHndl(-1), m_rootID(0), m_state(STATE_LOOT)
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
	// ルート情報のみが入ったモデルデータをロード
	if (m_rootHndl == -1)
	{
		m_rootHndl = MV1LoadModel("Model/Bg/Model/root.x");
	}

	Reset();
}


//------------------------------
//		初期設定セット
//------------------------------
void	Enemy::Reset()
{
	// スケールを表示ステージとあわせる
	MV1SetScale(m_rootHndl, VGet(0.05f, 0.05f, 0.05f));

	//最初の位置を取得、そこに配置する
	VECTOR start = MV1GetFramePosition(m_rootHndl, ROOT_ID[0]);
	Model::SetPosition(start);
	//0番目の位置にキャラクターを設定したので、次の目的地は1
	m_rootID = 1;

	// 敵の初期行動を設定
	m_state = STATE_LOOT;
	// 歩きアニメーションを再生
	Model::RequestLoop(1, ANIM_SPD);
}


//------------------------------
//		更新処理
//------------------------------
void	Enemy::Calc(VECTOR playerPos)
{	
	switch (m_state)
	{
	//ルートを巡回する
	case STATE_LOOT:
		MoveRoot();
		if (IsNearTarget(playerPos, 50.0f))
		{
			// 敵の初期行動を設定
			m_state = STATE_CHACE;
		}
		break;
	//ターゲットを追いかける
	case STATE_CHACE:
		ChaceTarget(playerPos);
		if (!IsNearTarget(playerPos, 100.0f))
		{
			// 敵の初期行動を設定
			m_state = STATE_LOOT;
		}
		break;
	}

	// 重力更新
	Player::UpdateGravity();
	// アニメーション更新
	Model::UpdateAnim();

}


//------------------------------
//		ルートを歩く
//------------------------------
void Enemy::MoveRoot()
{
	//次の目的地の座標取得
	VECTOR targetPos = MV1GetFramePosition(m_rootHndl, ROOT_ID[m_rootID]);
	//自分の現在座標
	VECTOR pos = Model::GetPosition();
	//目的地に向けてのベクトルを計算
	VECTOR dir = VSub(targetPos, pos);
	//目的地までの距離を取得
	float len = VSize(dir);

	//目的地までの距離が一定範囲内
	if (len <= 1.5f)
	{
		//目的地まで一気に移動
		Model::SetPosition(targetPos);
		//目的地を次の場所へ(ループさせる)
		m_rootID = (m_rootID + 1) % ROOT_NUM;
	}
	//目的地までまだ距離がある
	else
	{
		//高さは無視して正規化
		dir.y = 0;
		dir = VNorm(dir);
		//移動速度分の長さに変更
		dir = VScale(dir, WALK_SPEED);
		//上記計算結果を現在座標に加算するといい感じに!
		pos = VAdd(pos, dir);
		Model::SetPosition(pos);
	}

	//進行方向を向かせる
	float rotY = atan2f(-dir.x, -dir.z);
	Model::SetRot(VGet(0.0f, rotY, 0.0f));

}


//------------------------------
//		ターゲットを追いかける
//------------------------------
void Enemy::ChaceTarget(VECTOR targetPos)
{
	//自分の現在座標
	VECTOR pos = Model::GetPosition();
	//目的地に向けてのベクトルを計算
	VECTOR dir = VSub(targetPos, pos);
	//高さは無視して正規化
	dir.y = 0;
	dir = VNorm(dir);
	//移動速度分の長さに変更
	dir = VScale(dir, WALK_SPEED);
	//キャラクターを計算した結果の方向に移動
	pos = VAdd(pos, dir);
	Model::SetPosition(pos);
	//進行方向を向かせる
	float rotY = atan2f(-dir.x, -dir.z);
	Model::SetRot(VGet(0.0f, rotY, 0.0f));
}


//------------------------------
//		ターゲットが近くにいるかを判定
//------------------------------
bool Enemy::IsNearTarget(VECTOR targetPos, float radius)
{
	//二点間の距離を調べる
	VECTOR pos = Model::GetPosition();
	VECTOR dir = VSub(targetPos, pos);
	float len = VSquareSize(dir);
	//引数で指定された範囲内か銅貨を返す
	if (len < radius * radius)return true;
	else return false;
}
