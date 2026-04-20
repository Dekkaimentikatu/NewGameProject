#pragma once

#include <list>
#include <math.h>

#include "lib/collision.h"

#include "game/base/manager_base.h"

class C_COLLISION_MANAGER
{
private:

	//床との衝突フラグ
	static bool isHitFloor;

	//壁との衝突フラグ
	static bool isHitWall;

	//オブジェクトの判定用プール
	static list<C_OBJECT_BASE*> m_objectPool;

	//プレイヤーとエネミーの当たり判定
	static void PlayerToEnemy(C_OBJECT_BASE* _player, C_OBJECT_BASE* enemy);

	//プレイヤーとブロックの当たり判定
	static void PlayerToBlock(C_OBJECT_BASE* _player, C_OBJECT_BASE* _block);

	//プレイヤーとアイテムの当たり判定
	static void PlayerToFlag(C_OBJECT_BASE* _player, C_OBJECT_BASE* _flag);

	//エネミーとエネミーの当たり判定
	static void EnemyToEnemy(C_OBJECT_BASE* _enemy1, C_OBJECT_BASE* _enemy2);

	//エネミーとブロックの当たり判定
	static void EnemyToBlock(C_OBJECT_BASE* _enemy, C_OBJECT_BASE* _block);

public:

	//当たり判定処理
	static void CollisionCalc();

	//オブジェクト追加
	static void AddObject(C_OBJECT_BASE* _object) { m_objectPool.push_back(_object); }

	//終了処理
	static void Exit();


};
