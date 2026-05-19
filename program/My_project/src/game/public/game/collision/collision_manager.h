#pragma once

#include <list>
#include <thread>
#include <math.h>

#include "collision/3Dcollision.h"

#include "game/base/manager_base.h"

class C_COLLISION_MANAGER
{
private:

	static C_COLLISION_MANAGER* m_instance;

	//床との衝突フラグ
	static bool isHitFloor;

	//壁との衝突フラグ
	static bool isHitWall;

	//オブジェクトの判定用プール
	static list<weak_ptr<C_OBJECT_BASE>> m_objectPool;

	static vector<thread> m_collisionThread;

	//プレイヤーとエネミーの当たり判定
	static void CollisionPlayerToEnemy(weak_ptr<C_OBJECT_BASE> _player, weak_ptr<C_OBJECT_BASE> enemy);

	//プレイヤーとブロックの当たり判定
	static void CollisionPlayerToBlock(weak_ptr<C_OBJECT_BASE> _player, weak_ptr<C_OBJECT_BASE> _block);

	//プレイヤーとアイテムの当たり判定
	static void CollisionPlayerToFlag(weak_ptr<C_OBJECT_BASE> _player, weak_ptr<C_OBJECT_BASE> _flag);

	//エネミーとエネミーの当たり判定
	static void CollisionEnemyToEnemy(weak_ptr<C_OBJECT_BASE> _enemy1, weak_ptr<C_OBJECT_BASE> _enemy2);

	//エネミーとブロックの当たり判定
	static void CollisionEnemyToBlock(weak_ptr<C_OBJECT_BASE> _enemy, weak_ptr<C_OBJECT_BASE> _block);

	//アクターの判定用プール
	static list<weak_ptr<C_ACTOR_BASE>> m_actorPool;

	//プレイヤーとエネミーの攻撃判定
	static void AttackPlayerToEnemy(weak_ptr<C_ACTOR_BASE> _player, weak_ptr<C_ACTOR_BASE> _enemy);

	static void EraseObject(list<weak_ptr<C_OBJECT_BASE>>::iterator _objectPool);

	static void EraseActor(list <weak_ptr<C_ACTOR_BASE>>::iterator _actorPool);

public:

	//当たり判定処理
	static void CollisionCalc();

	//オブジェクト追加
	static void AddObject(weak_ptr<C_OBJECT_BASE> _object) { m_objectPool.push_back(_object); }

	//アクター追加
	static void AddActor(weak_ptr<C_ACTOR_BASE> _actor) { m_actorPool.push_back(_actor); }

	//終了処理
	static void Exit();


};
