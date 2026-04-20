#include "game/collision/collision_manager.h"
#include "game/data/global_data.h"

bool C_COLLISION_MANAGER::isHitFloor = false;

bool C_COLLISION_MANAGER::isHitWall = false;

list<C_OBJECT_BASE*> C_COLLISION_MANAGER::m_objectPool;

void C_COLLISION_MANAGER::PlayerToEnemy(C_OBJECT_BASE* _player, C_OBJECT_BASE* _enemy)
{
	C_GLOBAL_DATA* globalData = C_GLOBAL_DATA::GetInstace();

	//生存フラグが折れているなら次の要素へ
	if (!_player->GetIsActive())return;
	if (!_enemy->GetIsActive())return;

	//当たり判定
	if (C_COLLISION::CheckHitSphereToSphere(_player->GetPos(), _enemy->GetPos(),
		_player->GetRedius(), _enemy->GetRedius()))
	{

		//アクターの座標の差を取得
		VECTOR vec = VSub(_enemy->GetPos(), _player->GetPos());
		float len = VSize(vec);

		//座標の差を正規化
		vec = VNorm(vec);

		//めり込んだ距離を計算
		len = (_enemy->GetRedius() + _player->GetRedius()) - len;

		//移動ベクトルにめり込んだ距離を乗算
		vec = VScale(vec, len);

		//押し戻しベクトルを座標に加算
		if (globalData->GetPlayerData()->isStop)
		{
			vec = VScale(vec, -1.0f);
			_player->AddPos(vec);
		}
		else _enemy->AddPos(vec);

	}

	//マネージャー1の攻撃判定
	//if (_player->GetIsAttack() &&
	//	C_COLLISION::CheckHitSphereToSphere(_player->GetAttackPos(), _enemy->GetPos(),
	//		_player->GetAttackRedius(), _enemy->GetRedius()))
	//{
	//	//ノックバックの速度の設定
	//	_enemy->SetKonckBackSpeed(_player->GetPos());

	//	//当たり判定処理
	//	_enemy->DamageCalc(_player->GetAtt());
	//}

	////マネージャー2の攻撃判定
	//if (_enemy->GetIsAttack() &&
	//	C_COLLISION::CheckHitSphereToSphere(_enemy->GetAttackPos(), _player->GetCenter(),
	//		_enemy->GetAttackRedius(), _player->GetRedius()))
	//{
	//	_player->DamageCalc(_enemy->GetAtt());
	//}
}

void C_COLLISION_MANAGER::PlayerToBlock(C_OBJECT_BASE* _player, C_OBJECT_BASE* _block)
{
	//生存フラグが折れているなら次の要素へ
	if (!_player->GetIsActive())return;
	if (!_block->GetIsActive())return;

	VECTOR HitPos = { 0 };	//ポリゴンとの最近点を格納する変数
	VECTOR result = { 0 };	//リザルトを格納する変数
	VECTOR center = { 0 };	//当たり判定の中心を格納する変数
	VECTOR moveVec = { 0 };	//ブロックの移動
	float radius = 0; //当たり判定の半径を格納する変数
	float len = 0; //めり込んだ距離を格納する変数
	MV1_COLL_RESULT_POLY_DIM col;
	C_GLOBAL_DATA* globalData = C_GLOBAL_DATA::GetInstace();

	center = _player->GetCenter();
	radius = static_cast<float>(_player->GetRedius());

	col = MV1CollCheck_Sphere(_block->GetModelHndle(), -1, center, radius);

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
			_player->HitCalcWall();
		}
		//天井との当たり判定
		else if (col.Dim[i].Normal.y == -1.0f)
		{
			_player->HitCalcCeiling();
		}
		//床との当たり判定
		else if (col.Dim[i].Normal.y != -1.0f)
		{
			_player->HitCalc();
			_block->HitCalc();
		}


		break;
	}

	//リザルトに結果を加算する
	if (_block->GetMoveVec().x > result.x &&
		_block->GetMoveVec().y > result.y &&
		_block->GetMoveVec().z > result.z)
	{
		moveVec = _block->GetMoveVec();
	}
	else
	{
		moveVec = VAdd(moveVec, _block->GetMoveVec());
	}

	result = VAdd(result, moveVec);

	_player->AddPos(result);


	//if (_block->GetIsAttack())
	//{
	//	_player->DamageCalc(_block->GetAtt());
	//}

	MV1CollResultPolyDimTerminate(col);
}

void C_COLLISION_MANAGER::PlayerToFlag(C_OBJECT_BASE* _player, C_OBJECT_BASE* _flag)
{
	//生存フラグが折れているなら次の要素へ
	if (!_player->GetIsActive())return;

	if (C_COLLISION::CheckHitSphereToSphere(_player->GetPos(), _flag->GetPos(),
		_player->GetRedius(), _flag->GetRedius()))
	{
		_flag->HitCalc();
	}
}

void C_COLLISION_MANAGER::EnemyToEnemy(C_OBJECT_BASE* _enemy1, C_OBJECT_BASE* _enemy2)
{
	//生存フラグが折れているなら次の要素へ
	if (!_enemy1->GetIsActive())return;
	if (!_enemy2->GetIsActive())return;

	//当たり判定
	if (C_COLLISION::CheckHitSphereToSphere(_enemy1->GetPos(), _enemy2->GetPos(),
		_enemy1->GetRedius(), _enemy2->GetRedius()))
	{
		//アクターの座標の差を取得
		VECTOR vec = VSub(_enemy2->GetPos(), _enemy1->GetPos());
		vec.y = 0.0f;
		float len = VSize(vec);

		//座標の差を正規化
		vec = VNorm(vec);

		//めり込んだ距離を計算
		len = (_enemy2->GetRedius() + _enemy1->GetRedius()) - len;

		//移動ベクトルにめり込んだ距離を乗算
		vec = VScale(vec, len);

		//押し戻しベクトルを座標に加算
		_enemy2->AddPos(vec);
	}
}

void C_COLLISION_MANAGER::EnemyToBlock(C_OBJECT_BASE* _enemy, C_OBJECT_BASE* _block)
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
	if (!_enemy->GetIsActive())return;
	if (!_block->GetIsActive())return;

	center = _enemy->GetCenter();
	radius = static_cast<float>(_enemy->GetRedius());

	if (_block->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_STATIC)
	{
		if (C_COLLISION::CheckHitSphereToSphere(_enemy->GetPos(), _block->GetPos(),
			_enemy->GetRedius(), _block->GetRedius()))
		{
			_block->HitCalc();
		}
		return;
	}

	col = MV1CollCheck_Sphere(_block->GetModelHndle(), -1, center, radius);

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
	if (_block->GetMoveVec().x > result.x &&
		_block->GetMoveVec().y > result.y &&
		_block->GetMoveVec().z > result.z)
	{
		moveVec = _block->GetMoveVec();
	}
	else
	{
		moveVec = VAdd(moveVec, _block->GetMoveVec());
	}

	result = VAdd(result, moveVec);

	_enemy->AddPos(result);

	MV1CollResultPolyDimTerminate(col);
}

//当たり判定処理
void C_COLLISION_MANAGER::CollisionCalc()
{
	//関数ポインタを作成
	void (*Calc[])(C_OBJECT_BASE*, C_OBJECT_BASE*) = { C_COLLISION_MANAGER::PlayerToEnemy, C_COLLISION_MANAGER::PlayerToBlock,
		C_COLLISION_MANAGER::PlayerToFlag, C_COLLISION_MANAGER::EnemyToEnemy, C_COLLISION_MANAGER::EnemyToBlock };

	int funkIndex = 0;

	//マネージャー1の配列の要素数だけforループを回す
	for (auto itr1 = m_objectPool.begin(); itr1 != m_objectPool.end(); ++itr1)
	{
		//マネージャー2の配列の要素数だけforループを回す
		for (auto itr2 = m_objectPool.begin(); itr2 != m_objectPool.end(); ++itr2)
		{
			//同じ要素同士なら次の要素へ
			if ((*itr1) == (*itr2))continue;

			//どのタイプのオブジェクトが参照されているか
			if ((*itr1)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_PLAYER &&
				(*itr2)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_ENEMY)
			{
				funkIndex = 0;
			}
			else if ((*itr1)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_PLAYER &&
				(*itr2)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK)
			{
				funkIndex = 1;
			}
			else if ((*itr1)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_PLAYER &&
				(*itr2)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_FLAG)
			{
				funkIndex = 2;
			}
			else if ((*itr1)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_ENEMY &&
				(*itr2)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_ENEMY)
			{
				funkIndex = 3;
			}
			else if ((*itr1)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_ENEMY &&
				(*itr2)->GetObjectType() == C_OBJECT_BASE::OBJECT_TYPE_BLCOK)
			{
				funkIndex = 4;
			}
			else
			{
				continue;
			}

			//コールバック関数
			Calc[funkIndex]((*itr1), (*itr2));

			//参照した要素の生存フラグが折れているならリストから削除する
			//if (!(*itr2)->GetIsActive())
			//{
			//	m_objectList.erase(itr2);
			//	if (itr2 != m_objectList.begin())
			//	{
			//		--itr2;
			//	}
			//	continue;
			//}
		}

		//参照した要素の生存フラグが折れているならリストから削除する
		//if (!(*itr1)->GetIsActive())
		//{
		//	m_objectList.erase(itr1);
		//	if (itr1 != m_objectList.begin())
		//	{
		//		--itr1;
		//	}
		//	continue;
		//}
	}
}

void C_COLLISION_MANAGER::Exit()
{
	m_objectPool.clear();
}