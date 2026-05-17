#include "game/collision/collision_manager.h"
#include "collision/3Dcollision.h"
#include "game/data/global_data.h"
#include "debugdraw/debug_draw.h"

bool C_COLLISION_MANAGER::isHitFloor = false;

bool C_COLLISION_MANAGER::isHitWall = false;

list<weak_ptr<C_OBJECT_BASE>> C_COLLISION_MANAGER::m_objectPool;

list<weak_ptr<C_ACTOR_BASE>> C_COLLISION_MANAGER::m_actorPool;

void C_COLLISION_MANAGER::CollisionPlayerToEnemy(weak_ptr<C_OBJECT_BASE> _player, weak_ptr<C_OBJECT_BASE> _enemy)
{
	C_GLOBAL_DATA* globalData = C_GLOBAL_DATA::GetInstace();

	//生存フラグが折れているなら次の要素へ
	if (!_player.lock()->GetIsActive())return;
	if (!_enemy.lock()->GetIsActive())return;

	//当たり判定
	if (C_COLLISION::CheckHitSphereToSphere(_player.lock()->GetPos(), _enemy.lock()->GetPos(),
		_player.lock()->GetRedius(), _enemy.lock()->GetRedius()))
	{

		//アクターの座標の差を取得
		VECTOR vec = VSub(_enemy.lock()->GetPos(), _player.lock()->GetPos());
		float len = VSize(vec);

		//座標の差を正規化
		vec = VNorm(vec);

		//めり込んだ距離を計算
		len = (_enemy.lock()->GetRedius() + _player.lock()->GetRedius()) - len;

		//移動ベクトルにめり込んだ距離を乗算
		vec = VScale(vec, len);

		//押し戻しベクトルを座標に加算
		if (globalData->GetPlayerData()->isStop)
		{
			vec = VScale(vec, -1.0f);
			_player.lock()->AddPos(vec);
		}
		else _enemy.lock()->AddPos(vec);

	}
}

void C_COLLISION_MANAGER::CollisionPlayerToBlock(weak_ptr<C_OBJECT_BASE> _player, weak_ptr<C_OBJECT_BASE> _block)
{
	//生存フラグが折れているなら次の要素へ
	if (!_player.lock()->GetIsActive())return;
	if (!_block.lock()->GetIsActive())return;

	VECTOR HitPos = { 0 };	//ポリゴンとの最近点を格納する変数
	VECTOR result = { 0 };	//リザルトを格納する変数
	VECTOR center1 = { 0 };	//当たり判定の中心を格納する変数
	VECTOR Pcenter = { 0 };
	VECTOR center2 = { 0 };	//当たり判定の中心を格納する変数
	VECTOR Size1 = { 0 };	//当たり判定の中心を格納する変数
	VECTOR Size2 = { 0 };	//当たり判定の中心を格納する変数
	VECTOR moveVec = { 0 };	//ブロックの移動
	float radius1 = 0; //当たり判定の半径を格納する変数
	float radius2 = 0; //当たり判定の半径を格納する変数
	float len = 0; //めり込んだ距離を格納する変数
	//重力処理を行うか
	bool IsGravity = true;
	//動く床と当たったか
	bool IsMovingPlatform = false;
	MV1_COLL_RESULT_POLY_DIM col;
	C_GLOBAL_DATA* globalData = C_GLOBAL_DATA::GetInstace();

	center1 = _player.lock()->GetCenter();
	radius1 = static_cast<float>(_player.lock()->GetRedius());
	Size1 = VScale(_player.lock()->GetScale(), 100);
	Pcenter = _player.lock()->GetPPos();
	center2 = _block.lock()->GetCenter();
	Size2 = VScale(_block.lock()->GetScale(), 400.0f);
	radius2 = static_cast<float>(_block.lock()->GetRedius());

	C_DEBUG_DRAW::DrawBox3DWire(VSub(center2, VScale(Size2, 0.5f)), VAdd(center2, VScale(Size2, 0.5f)), GetColor(0, 255, 0));

	if (!C_COLLISION::CheckHitBoxToBox(center1, Size1, center2, Size2))return;

	float ObjectUP = center1.y + Size1.y * 0.5f;
	//下方向
	float ObjectDown = center1.y - Size1.y * 0.5f;
	//左方向
	float ObjectLeft = center1.x - Size1.x * 0.5f;
	//右方向
	float ObjectRight = center1.x + Size1.x * 0.5f;
	//前方向
	float ObjectFlont = center1.z - Size1.z * 0.5f;
	//奥方向
	float ObjectBack = center1.z + Size1.z * 0.5f;
	//前フレーム
	//上方向
	float PrevObjectUp = Pcenter.y + Size1.y * 0.5f;
	//下方向
	float PrevObjectDown = Pcenter.y;
	//足場
	//上方向
	float PlatformUp = center2.y + Size2.y * 0.5f;
	//下方向
	float PlatformDown = center2.y - Size2.y * 0.5f;
	//左方向
	float PlatformLeft = center2.x - Size2.x * 0.5f;
	//右方向
	float PlatformRight = center2.x + Size2.x * 0.5f;
	//前方向
	float PlatformFlont = center2.z - Size2.z * 0.5f;
	//奥方向
	float PlatformBack = center2.z + Size2.z * 0.5f;

	//押し戻し方向設定
	VECTOR PushVec = { 0 };
	//着地
	if (PrevObjectDown >= PlatformUp) {
		//押し戻し量計算
		//上方向
		float PushUp = PlatformUp - ObjectDown;
		//押し戻し方向再設定
		PushVec = VGet(0.0f, PushUp, 0.0f);
		//重力処理を行わない
		IsGravity = false;
		//重力をリセット
		_player.lock()->HitCalc();
		_block.lock()->HitCalc();
	}
	//天井ヒット
	else if (PrevObjectUp <= PlatformDown) {
		//押し戻し量計算
		//下方向
		float PushDown = PlatformDown - ObjectUP;
		//押し戻し方向再設定
		PushVec = VGet(0.0f, PushDown, 0.0f);
		_player.lock()->HitCalcCeiling();
	}
	else {
		//押し戻し量計算
		//左方向
		float PushLeft = PlatformRight - ObjectLeft;
		//右方向
		float PushRight = PlatformLeft - ObjectRight;
		//前方向
		float PushFront = PlatformBack - ObjectFlont;
		//奥方向
		float PushBack = PlatformFlont - ObjectBack;

		//最も押し戻し量の小さい方向を探す
		//角方向の値を絶対値に変換
		//左方向
		float PushLeftAbs = fabsf(PushLeft);
		//右方向
		float PushRightAbs = fabsf(PushRight);
		//前方向
		float PushFrontAbs = fabsf(PushFront);
		//奥方向
		float PushBackAbs = fabsf(PushBack);

		//一旦上方向が最も小さいと仮定する
		float MinPush = PushLeftAbs;
		//押し戻し方向再設定
		PushVec = VGet(PushLeft, 0.0f, 0.0f);
		//右方向と比較
		//小さければ
		if (PushRightAbs < MinPush) {
			//最小を更新
			MinPush = PushRightAbs;
			//押し戻し方向再設定
			PushVec = VGet(PushRight, 0.0f, 0.0f);
		}
		//前方向と比較
		//小さければ
		if (PushFrontAbs < MinPush) {
			//最小を更新
			MinPush = PushFrontAbs;
			//押し戻し方向再設定
			PushVec = VGet(0.0f, 0.0f, PushFront);
		}
		//奥方向と比較
		//小さければ
		if (PushBackAbs < MinPush) {
			//最小を更新
			MinPush = PushBackAbs;
			//押し戻し方向再設定
			PushVec = VGet(0.0f, 0.0f, PushBack);
		}

		_player.lock()->HitCalcWall();
	}

	//リザルトにブロックの移動量を加算する
	if (_block.lock()->GetMoveVec().x > moveVec.x &&
		_block.lock()->GetMoveVec().y > moveVec.y &&
		_block.lock()->GetMoveVec().z > moveVec.z)
	{
		moveVec = _block.lock()->GetMoveVec();
	}
	else
	{
		moveVec = VAdd(moveVec, _block.lock()->GetMoveVec());
	}

	PushVec = VAdd(PushVec, moveVec);

	_player.lock()->AddPos(PushVec);

	//for (int i = 0; i < col.HitNum; i++)
	//{

	//	//ポリゴンとの最近点を取得
	//	HitPos = col.Dim[i].HitPosition;

	//	//めり込んだ距離を求める
	//	len = VSize(VSub(HitPos, center1));

	//	//半径からめり込んだ距離を減算する
	//	len = radius1 - len;

	//	//リザルトに結果を加算する
	//	if (VScale(col.Dim[i].Normal, len).x > result.x &&
	//		VScale(col.Dim[i].Normal, len).y > result.y &&
	//		VScale(col.Dim[i].Normal, len).z > result.z)
	//	{
	//		result = VScale(col.Dim[i].Normal, len);
	//	}
	//	else
	//	{
	//		result = VAdd(result, VScale(col.Dim[i].Normal, len));
	//	}

	//	//壁との当たり判定
	//	if (col.Dim[i].Normal.y < 0.7f && col.Dim[i].Normal.y > -0.7f)
	//	{
	//		_player.lock()->HitCalcWall();
	//	}
	//	//天井との当たり判定
	//	else if (col.Dim[i].Normal.y == -1.0f)
	//	{
	//		_player.lock()->HitCalcCeiling();
	//	}
	//	//床との当たり判定
	//	else if (col.Dim[i].Normal.y != -1.0f)
	//	{
	//		_player.lock()->HitCalc();
	//		_block.lock()->HitCalc();
	//	}

	//	break;
	//}



	//result = VAdd(result, moveVec);

	//_player.lock()->AddPos(result);


	////if (_block->GetIsAttack())
	////{
	////	_player->DamageCalc(_block->GetAtt());
	////}

	//MV1CollResultPolyDimTerminate(col);
}

void C_COLLISION_MANAGER::CollisionPlayerToFlag(weak_ptr<C_OBJECT_BASE> _player, weak_ptr<C_OBJECT_BASE> _flag)
{
	//生存フラグが折れているなら次の要素へ
	if (!_player.lock()->GetIsActive())return;

	if (C_COLLISION::CheckHitSphereToSphere(_player.lock()->GetPos(), _flag.lock()->GetPos(),
		_player.lock()->GetRedius(), _flag.lock()->GetRedius()))
	{
		_flag.lock()->HitCalc();
	}
}

void C_COLLISION_MANAGER::CollisionEnemyToEnemy(weak_ptr<C_OBJECT_BASE> _enemy1, weak_ptr<C_OBJECT_BASE> _enemy2)
{
	//生存フラグが折れているなら次の要素へ
	if (!_enemy1.lock()->GetIsActive())return;
	if (!_enemy2.lock()->GetIsActive())return;

	//当たり判定
	if (C_COLLISION::CheckHitSphereToSphere(_enemy1.lock()->GetPos(), _enemy2.lock()->GetPos(),
		_enemy1.lock()->GetRedius(), _enemy2.lock()->GetRedius()))
	{
		//アクターの座標の差を取得
		VECTOR vec = VSub(_enemy2.lock()->GetPos(), _enemy1.lock()->GetPos());
		vec.y = 0.0f;
		float len = VSize(vec);

		//座標の差を正規化
		vec = VNorm(vec);

		//めり込んだ距離を計算
		len = (_enemy2.lock()->GetRedius() + _enemy1.lock()->GetRedius()) - len;

		//移動ベクトルにめり込んだ距離を乗算
		vec = VScale(vec, len);

		//押し戻しベクトルを座標に加算
		_enemy2.lock()->AddPos(vec);
	}
}

void C_COLLISION_MANAGER::CollisionEnemyToBlock(weak_ptr<C_OBJECT_BASE> _enemy, weak_ptr<C_OBJECT_BASE> _block)
{
	VECTOR HitPos = { 0 };	//ポリゴンとの最近点を格納する変数
	VECTOR result = { 0 };	//リザルトを格納する変数
	VECTOR center = { 0 };	//当たり判定の中心を格納する変数
	VECTOR moveVec = { 0 };	//ブロックの移動
	float radius = 0; //当たり判定の半径を格納する変数
	float len = 0; //めり込んだ距離を格納する変数
	MV1_COLL_RESULT_POLY_DIM col;
	C_GLOBAL_DATA* globalData = C_GLOBAL_DATA::GetInstace();


	//生存フラグが折れているなら次の要素へ
	if (!_enemy.lock()->GetIsActive())return;
	if (!_block.lock()->GetIsActive())return;

	center = _enemy.lock()->GetCenter();
	radius = static_cast<float>(_enemy.lock()->GetRedius());

	if (_block.lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_STATIC)
	{
		if (C_COLLISION::CheckHitSphereToSphere(_enemy.lock()->GetPos(), _block.lock()->GetPos(),
			_enemy.lock()->GetRedius(), _block.lock()->GetRedius()))
		{
			_block.lock()->HitCalc();
		}
		return;
	}

	col = MV1CollCheck_Sphere(_block.lock()->GetModelHndle(), -1, center, radius);

	if (col.HitNum <= 0)return;

	for (int i = 0; i < col.HitNum; i++)
	{
		//ポリゴンとの最近点を取得
		HitPos = col.Dim[i].HitPosition;

		//めり込んだ距離を求める
		len = VSize(VSub(HitPos, center));

		//半径からめり込んだ距離を減算する
		len = radius - len;

		//リザルトに結果を加算する
		if (VScale(col.Dim[i].Normal, len).x > result.x &&
			VScale(col.Dim[i].Normal, len).y > result.y &&
			VScale(col.Dim[i].Normal, len).z > result.z)
		{
			result = VScale(col.Dim[i].Normal, len);
		}
		else
		{
			result = VAdd(result, VScale(col.Dim[i].Normal, len));
		}
	}

	//リザルトに結果を加算する
	if (_block.lock()->GetMoveVec().x > result.x &&
		_block.lock()->GetMoveVec().y > result.y &&
		_block.lock()->GetMoveVec().z > result.z)
	{
		moveVec = _block.lock()->GetMoveVec();
	}
	else
	{
		moveVec = VAdd(moveVec, _block.lock()->GetMoveVec());
	}

	result = VAdd(result, moveVec);

	_enemy.lock()->AddPos(result);

	MV1CollResultPolyDimTerminate(col);
}

void C_COLLISION_MANAGER::AttackPlayerToEnemy(weak_ptr<C_ACTOR_BASE> _player, weak_ptr<C_ACTOR_BASE> _enemy)
{
	//マネージャー1の攻撃判定
	if (_player.lock()->GetIsAttack() &&
		C_COLLISION::CheckHitSphereToSphere(_player.lock()->GetAttackPos(), _enemy.lock()->GetPos(),
			_player.lock()->GetAttackRedius(), _enemy.lock()->GetRedius()))
	{
		//ノックバックの速度の設定
		_enemy.lock()->SetKonckBackSpeed(_player.lock()->GetPos());

		//当たり判定処理
		_enemy.lock()->DamageCalc(_player.lock()->GetAtt());
	}

	//マネージャー2の攻撃判定
	if (_enemy.lock()->GetIsAttack() &&
		C_COLLISION::CheckHitSphereToSphere(_enemy.lock()->GetAttackPos(), _player.lock()->GetCenter(),
			_enemy.lock()->GetAttackRedius(), _player.lock()->GetRedius()))
	{
		_player.lock()->DamageCalc(_enemy.lock()->GetAtt());
	}
}

void C_COLLISION_MANAGER::EraseObject(list <weak_ptr<C_OBJECT_BASE>>::iterator _objectPool)
{
	if (_objectPool->expired() || !(*_objectPool).lock()->GetIsActive())
	{
		_objectPool = m_objectPool.erase(_objectPool);
	}
	else
	{
		++_objectPool;
	}
}

void C_COLLISION_MANAGER::EraseActor(list <weak_ptr<C_ACTOR_BASE>>::iterator _actorPool)
{
	if (_actorPool->expired() || !(*_actorPool).lock()->GetIsActive())
	{
		_actorPool = m_actorPool.erase(_actorPool);
	}
	else
	{
		++_actorPool;
	}
}

//当たり判定処理
void C_COLLISION_MANAGER::CollisionCalc()
{
	//関数ポインタを作成
	void (*Calc[])(weak_ptr<C_OBJECT_BASE>, weak_ptr<C_OBJECT_BASE>) = { C_COLLISION_MANAGER::CollisionPlayerToEnemy, C_COLLISION_MANAGER::CollisionPlayerToBlock,
		C_COLLISION_MANAGER::CollisionPlayerToFlag, C_COLLISION_MANAGER::CollisionEnemyToEnemy, C_COLLISION_MANAGER::CollisionEnemyToBlock };

	int funkIndex = 0;

	//マネージャー1の配列の要素数だけforループを回す
	for (auto itr1 = m_objectPool.begin(); itr1 != m_objectPool.end(); ++itr1)
	{
		//マネージャー2の配列の要素数だけforループを回す
		for (auto itr2 = m_objectPool.begin(); itr2 != m_objectPool.end(); ++itr2)
		{
			//同じ要素同士なら次の要素へ
			if ((*itr1).lock() == (*itr2).lock())continue;

			//どのタイプのオブジェクトが参照されているか
			if ((*itr1).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_PLAYER &&
				(*itr2).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_ENEMY)
			{
				funkIndex = 0;
			}
			else if ((*itr1).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_PLAYER &&
				(*itr2).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK)
			{
				funkIndex = 1;
			}
			else if ((*itr1).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_PLAYER &&
				(*itr2).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_FLAG)
			{
				funkIndex = 2;
			}
			else if ((*itr1).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_ENEMY &&
				(*itr2).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_ENEMY)
			{
				funkIndex = 3;
			}
			else if ((*itr1).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_ENEMY &&
				(*itr2).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK)
			{
				funkIndex = 4;
			}
			else
			{
				continue;
			}

			//コールバック関数
			Calc[funkIndex]((*itr1), (*itr2));

			/*EraseObject(itr2);*/
		}

		/*EraseObject(itr1);*/
	}

	for (auto itr1 = m_actorPool.begin(); itr1 != m_actorPool.end(); ++itr1)
	{
		for (auto itr2 = m_actorPool.begin(); itr2 != m_actorPool.end(); ++itr2)
		{
			if ((*itr1).lock() == (*itr2).lock())continue;
			if ((*itr1).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_PLAYER &&
				(*itr2).lock()->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_ENEMY)
			{
				AttackPlayerToEnemy((*itr1), (*itr2));
			}

			/*EraseActor(itr2);*/
		}

		/*EraseActor(itr1);*/

	}
}

void C_COLLISION_MANAGER::Exit()
{
	m_objectPool.clear();
}