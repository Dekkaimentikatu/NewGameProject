#include "game/collision/collision_manager.h"
#include "game/data/global_data.h"
#include "game/voxel/voxel_world.h"

using namespace std;

C_COLLISION_MANAGER* C_COLLISION_MANAGER::m_instance = nullptr;

C_COLLISION_MANAGER* C_COLLISION_MANAGER::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new C_COLLISION_MANAGER();
	}
	return m_instance;
}

void C_COLLISION_MANAGER::DeleteInstance()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

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
	//if (_player.lock()->GetIsAttack() &&
	//	C_COLLISION::CheckHitSphereToSphere(_player.lock()->GetAttackPos(), _enemy.lock()->GetPos(),
	//		_player.lock()->GetAttackRedius(), _enemy.lock()->GetRedius()))
	//{
	//	//ノックバックの速度の設定
	//	_enemy.lock()->SetKonckBackSpeed(_player.lock()->GetPos());

	//	//当たり判定処理
	//	_enemy.lock()->DamageCalc(_player.lock()->GetAtt());
	//}

	////マネージャー2の攻撃判定
	//if (_enemy.lock()->GetIsAttack() &&
	//	C_COLLISION::CheckHitSphereToSphere(_enemy.lock()->GetAttackPos(), _player.lock()->GetCenter(),
	//		_enemy.lock()->GetAttackRedius(), _player.lock()->GetRedius()))
	//{
	//	_player.lock()->DamageCalc(_enemy.lock()->GetAtt());
	//}
}

void C_COLLISION_MANAGER::CollisionActorToVoxel(std::weak_ptr<C_ACTOR_BASE> _actor)
{
	if (!_actor.lock()->GetIsActive())return;

	//チャンクの座標
	T_CHUNK_POS chunkPos = { 0 };

	VECTOR p_pos = { 0 }, v_pos = { 0 };
	float p_size = 0.0f, v_size = 0.0f;

	//playerの中心座標を取得
	p_pos = _actor.lock()->GetCenter();
	//playerの半径を取得
	p_size = _actor.lock()->GetRedius();

	//チャンクのどこにいるか
	if (p_pos.x > 0) chunkPos.x = 1;
	else if (p_pos.x < 0) chunkPos.x = -1;
	if (p_pos.z > 0) chunkPos.z = 1;
	else if (p_pos.z < 0) chunkPos.z = -1;

	//中心にいるなら当たり判定をしない
	if (chunkPos.x == 0 || chunkPos.z == 0)return;

	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{

				if (c_voxelWorldCopy.lock()->GetChunk(chunkPos).lock()->GetVoxel(x, y, z)->GetVoxelType() ==
					C_VOXEL::AIR)continue;

				//ボクセルの中心座標
				v_pos = c_voxelWorldCopy.lock()->GetChunk(chunkPos).lock()->GetVoxel(x, y, z)->GetPos();
				//ボクセルのサイズ
				v_size = BLOCK_SIZE;

				//最近点
				VECTOR closest = { 0 };

				//当たり判定
				if (!C_COLLISION::CheckHitAABBToSphere(p_pos, p_size, v_pos, v_size, closest))continue;

				//最近点と座標の差を計算
				VECTOR diff = VSub(p_pos, closest);

				//差の２乗
				float distSq = VSquareSize(diff);

				//法線
				VECTOR normal = { 0 };

				//押し戻しベクトル
				VECTOR push = { 0 };

				if (distSq > 0.0f)
				{
					//平方根に直す
					float dist = std::sqrt(distSq);

					if (dist > p_size)break;

					//法線を計算
					normal = VGet(diff.x / dist,
						diff.y / dist,
						diff.z / dist);

					//めり込んだ距離を計算
					float penetration = p_size - dist;

					//押し戻しベクトルを生成
					push = VScale(normal, penetration);
					_actor.lock()->HitCalc();
					//押し戻し処理
					_actor.lock()->AddPos(push);
					return;
				}

				//ボクセルの上座標
				VECTOR AABBMax = VGet(v_pos.x + v_size * 0.5f,
					v_pos.y + v_size * 0.5f,
					v_pos.z + v_size * 0.5f);

				//ボクセルの下座標
				VECTOR AABBMin = VGet(v_pos.x - v_size * 0.5f,
					v_pos.y - v_size * 0.5f,
					v_pos.z - v_size * 0.5f);

				//左方向のめり込んだ距離
				float left = p_pos.x - AABBMin.x;
				//右方向のめり込んだ距離
				float right = AABBMax.x - p_pos.x;

				//下方向のめり込んだ距離
				float down = p_pos.y - AABBMin.y;
				//上方向のめり込んだ距離
				float up = AABBMax.y - p_pos.y;

				//前方向のめり込んだ距離
				float back = p_pos.z - AABBMin.z;
				//後方向のめり込んだ距離
				float front = AABBMax.z - p_pos.z;

				//ボックス内にどれだけめり込んでいるか
				//一旦左方向に押し戻すと仮定する
				float minDist = left;
				normal = VGet(-1.0f, 0.0f, 0.0f);

				//前の値より大きければ右方向に変更
				if (right < minDist)
				{
					minDist = right;
					normal = VGet(1.0f, 0.0f, 0.0f);
				}

				//前の値より大きければ下方向に変更
				if (down < minDist)
				{
					minDist = down;
					normal = VGet(0.0f, -1.0f, 0.0f);
				}

				//前の値より大きければ上方向に変更
				if (up < minDist)
				{
					minDist = up;
					normal = VGet(0.0f, 1.0f, 0.0f);
				}

				//前の値より大きければ後方向に変更
				if (back < minDist)
				{
					minDist = back;
					normal = VGet(0.0f, 0.0f, 1.0f);
				}

				//前の値より大きければ前方向に変更
				if (front < minDist)
				{
					minDist = front;
					normal = VGet(0.0f, 0.0f, -1.0f);
				}

				//押し戻しベクトルを生成
				push = VScale(normal, p_size + minDist);
				_actor.lock()->HitCalc();
				_actor.lock()->AddPos(push);
				return;
			}
		}
	}
}

void C_COLLISION_MANAGER::EraseObject(list <weak_ptr<C_OBJECT_BASE>>::iterator& _objectPool)
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

void C_COLLISION_MANAGER::EraseActor(list <weak_ptr<C_ACTOR_BASE>>::iterator& _actorPool)
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

	int funkIndex = -1;

	//マネージャー1の配列の要素数だけforループを回す
	for (auto itr1 = m_objectPool.begin(); itr1 != m_objectPool.end(); ++itr1)
	{
		//マネージャー2の配列の要素数だけforループを回す
		for (auto itr2 = m_objectPool.begin(); itr2 != m_objectPool.end(); ++itr2)
		{
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

			//コールバック関数
			if (funkIndex != -1)Calc[funkIndex]((*itr1), (*itr2));
		}
	}

	for (auto itr = m_actorPool.begin(); itr != m_actorPool.end(); ++itr)
	{
		//ボクセルとの当たり判定
		CollisionActorToVoxel((*itr));
	}

	//攻撃判定
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
		}
	}

	for (auto itr = m_objectPool.begin(); itr != m_objectPool.end();)
	{
		EraseObject(itr);
	}

	for (auto itr = m_actorPool.begin(); itr != m_actorPool.end();)
	{
		EraseActor(itr);
	}
}

void C_COLLISION_MANAGER::Exit()
{
	m_objectPool.clear();
}