#pragma once
 
#include <DxLib.h>
#include <vector>
#include <list>
#include "game/base/object.h"
#include "game/base/actor.h"

#include "game/data/global_data.h"

using namespace std;

class C_OBJECT_MANAGER_BASE
{
protected:

	//オブジェクトのリスト
	list<C_OBJECT_BASE*> c_objectArray;

	//グローバルデータクラスのインスタンス取得用変数
	C_GLOBAL_DATA* c_globalData;

public:

	//コンストラクタ
	C_OBJECT_MANAGER_BASE(C_GLOBAL_DATA* _globalData = nullptr):
		c_globalData(_globalData) {}

	//デストラクタ
	virtual ~C_OBJECT_MANAGER_BASE() {}

	//初期化
	virtual void Init() = 0;

	//リソース読込
	virtual void LoadAnSync() = 0;

	//読込
	virtual void LoadSync() = 0;

	//更新
	virtual void Step() = 0;

	//更新確定
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;

	//終了
	virtual void Exit() = 0;

	//リスト取得
	inline list<C_OBJECT_BASE*>& GetArray()
	{
		return c_objectArray;
	}

	//リストの長さを取得
	inline int GetArrayLen()
	{
		return static_cast<int>(c_objectArray.size());
	}

};

class C_ACOTR_MANAGER_BASE
{
protected:

	//アクターのリスト
	list<C_ACTOR_BASE*> c_actorArray;

	//グローバルデータクラスのインスタンス取得用変数
	C_GLOBAL_DATA* c_globalData;

public:

	C_ACOTR_MANAGER_BASE(C_GLOBAL_DATA* _globalData = nullptr):
	c_globalData(_globalData){}
	virtual ~C_ACOTR_MANAGER_BASE() {}

	//初期化
	virtual void Init() = 0;
	
	//読込
	virtual void LoadSync() = 0;

	//リソース読込
	virtual void LoadAnSync() = 0;

	//更新
	virtual void Step() = 0;

	//更新確定
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;

	//終了
	virtual void Exit() = 0;

	//当たり判定処理
	virtual void HitCalc() {};

	//リスト取得
	inline list<C_ACTOR_BASE*>& GetArray()
	{
		return c_actorArray;
	}

	//リストの長さを取得
	inline int GetArrayLen()
	{
		return static_cast<int>(c_actorArray.size());
	}

};
