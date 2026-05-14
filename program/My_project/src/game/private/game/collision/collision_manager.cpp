#include "game/collision/collision_manager.h"
#include "game/data/global_data.h"

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
	VECTOR center = { 0 };	//当たり判定の中心を格納する変数
	VECTOR moveVec = { 0 };	//ブロックの移動
	float radius = 0; //当たり判定の半径を格納する変数
	float len = 0; //めり込んだ距離を格納する変数
	MV1_COLL_RESULT_POLY_DIM col;
	C_GLOBAL_DATA* globalData = C_GLOBAL_DATA::GetInstace();

	center = _player.lock()->GetCenter();
	radius = static_cast<float>(_player.lock()->GetRedius());

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

		//壁との当たり判定
		if (col.Dim[i].Normal.y < 0.7f && col.Dim[i].Normal.y > -0.7f)
		{
			_player.lock()->HitCalcWall();
		}
		//天井との当たり判定
		else if (col.Dim[i].Normal.y == -1.0f)
		{
			_player.lock()->HitCalcCeiling();
		}
		//床との当たり判定
		else if (col.Dim[i].Normal.y != -1.0f)
		{
			_player.lock()->HitCalc();
			_block.lock()->HitCalc();
		}

		break;
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

	_player.lock()->AddPos(result);


	//if (_block->GetIsAttack())
	//{
	//	_player->DamageCalc(_block->GetAtt());
	//}

	MV1CollResultPolyDimTerminate(col);
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
			if ((*itr1).lock()->GetObjectType() == (*itr2).lock()->GetObjectType()) continue;

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