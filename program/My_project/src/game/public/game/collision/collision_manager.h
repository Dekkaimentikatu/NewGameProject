#pragma once

#include <list>
#include <thread>
#include <math.h>

#include "collision/3Dcollision.h"
#include "game/base/manager_base.h"

class C_VOXEL_WORLD;

class C_COLLISION_MANAGER
{
private:

	//コンストラクタ
	C_COLLISION_MANAGER() {};
	//デストラクタ
	~C_COLLISION_MANAGER() {};

	//スレッドセーフ処理
	C_COLLISION_MANAGER(const C_COLLISION_MANAGER&);
	C_COLLISION_MANAGER& operator=(const C_COLLISION_MANAGER&) = delete;

	//インスタンス
	static C_COLLISION_MANAGER* m_instance;

	//オブジェクトの判定用プール
	std::list<std::weak_ptr<C_OBJECT_BASE>> m_objectPool;

	//プレイヤーとエネミーの当たり判定
	static void CollisionPlayerToEnemy(std::weak_ptr<C_OBJECT_BASE> _player, std::weak_ptr<C_OBJECT_BASE> enemy);

	//プレイヤーとブロックの当たり判定
	static void CollisionPlayerToBlock(std::weak_ptr<C_OBJECT_BASE> _player, std::weak_ptr<C_OBJECT_BASE> _block);

	//プレイヤーとアイテムの当たり判定
	static void CollisionPlayerToFlag(std::weak_ptr<C_OBJECT_BASE> _player, std::weak_ptr<C_OBJECT_BASE> _flag);

	//エネミーとエネミーの当たり判定
	static void CollisionEnemyToEnemy(std::weak_ptr<C_OBJECT_BASE> _enemy1, std::weak_ptr<C_OBJECT_BASE> _enemy2);

	//エネミーとブロックの当たり判定
	static void CollisionEnemyToBlock(std::weak_ptr<C_OBJECT_BASE> _enemy, std::weak_ptr<C_OBJECT_BASE> _block);

	//アクターの判定用プール
	std::list<std::weak_ptr<C_ACTOR_BASE>> m_actorPool;

	//プレイヤーとエネミーの攻撃判定
	void AttackPlayerToEnemy(std::weak_ptr<C_ACTOR_BASE> _player, std::weak_ptr<C_ACTOR_BASE> _enemy);

	//ワールドのコピー
	std::weak_ptr<C_VOXEL_WORLD> c_voxelWorldCopy;

	//アクターとボクセル
	void AttackActorToObject(std::weak_ptr<C_ACTOR_BASE> _actor, std::weak_ptr<C_OBJECT_BASE> _object);

	//アクターとボクセル
	void CollisionActorToVoxel(std::weak_ptr<C_ACTOR_BASE> _actor);
	void CollisionLayToVoxel();

	//オブジェクトの削除
	void EraseObject(std::list<std::weak_ptr<C_OBJECT_BASE>>::iterator &_objectPool);

	//アクターの削除
	void EraseActor(std::list <std::weak_ptr<C_ACTOR_BASE>>::iterator &_actorPool);

public:

	//インスタンスを取得
	static C_COLLISION_MANAGER* GetInstance();

	//インスタンスを削除
	static void DeleteInstance();

	//実行処理
	void CollisionCalc();

	//オブジェクト追加
	void AddObject(std::weak_ptr<C_OBJECT_BASE> _object) { m_objectPool.push_back(_object); }

	//アクター追加
	void AddActor(std::weak_ptr<C_ACTOR_BASE> _actor) { m_actorPool.push_back(_actor); }

	//ボクセルを登録
	void CopyVoxelWorld(std::weak_ptr<C_VOXEL_WORLD> _voxelWorldOrigin) { c_voxelWorldCopy = _voxelWorldOrigin; }

	//終了処理
	void Exit();
};
