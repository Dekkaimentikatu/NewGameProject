#include "game/manager/player_manager.h"
#include "game/actor/player/player.h"
#include "game/collision/collision_manager.h"
#include "lib/3Dhndlmanager.h"

void C_PLAYER_MANAGER::Init()
{
	//listの初期化
	c_actorArray.clear();

	//カメラの初期化

	//ターゲットのインデックスの初期化
	m_targetPosListIndex = 0;
}

void C_PLAYER_MANAGER::LoadAnSync()
{
	C_3D_HNDL_MANAGER* incetanse = C_3D_HNDL_MANAGER::GetInstance();
	//プレイヤーモデルの読込
	incetanse->Load3DModel("data/model/player/character-human.mv1");
	incetanse->Load3DModel("data/model/player/weapon-sword.mv1");
}

void C_PLAYER_MANAGER::LoadSync()
{
	c_globalData = C_GLOBAL_DATA::GetInstace();

	//プレイヤーの初期化
	C_PLAYER* player = nullptr;
	player = new C_PLAYER();

	//listにInstanceを追加
	c_actorArray.push_back(player);

	//プレイヤーの初期化
	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		(*itr)->Init();
		(*itr)->DuplicateModel(m_modelHndl);
		(*itr)->Load();
		C_COLLISION_MANAGER::AddObject(*itr);
		c_globalData->GetPlayerData()->pos = (*itr)->GetPos();
	}
}

void C_PLAYER_MANAGER::Step()
{
	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		(*itr)->Step();

	}
}

void C_PLAYER_MANAGER::Step(VECTOR _camRota)
{
	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		(*itr)->SetCameraRota(_camRota);
		(*itr)->Step();
	}
}

void C_PLAYER_MANAGER::Update()
{
	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		(*itr)->Update();
	}

}

void C_PLAYER_MANAGER::Draw()
{
	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

void C_PLAYER_MANAGER::DebugDraw()
{
	/*DrawFormatString(10, 40, GetColor(0, 0, 0), "Rot:%f", m_debugRot);*/
}

void C_PLAYER_MANAGER::Exit()
{
	//モデルの破棄　
	MV1DeleteModel(m_modelHndl);

	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		(*itr)->Exit();
		delete (*itr);
	}

	C_3D_HNDL_MANAGER* incetanse = C_3D_HNDL_MANAGER::GetInstance();
	incetanse->Load3DModel("data/model/player/character-human.mv1");
	incetanse->Load3DModel("data/model/player/weapon-sword.mv1");

	c_actorArray.clear();

	c_cameraManager.Exit();


}

void C_PLAYER_MANAGER::ReflectCollision(VECTOR addVec)
{
	auto itr = c_actorArray.begin();
	if (addVec.x == 0.0f && addVec.y == 0.0f && addVec.z == 0.0f) return;

	VECTOR	pos = (*itr)->GetPos();
	pos = VAdd(pos, addVec);
	MV1SetPosition((*itr)->GetModelHndle(), pos);
}

void C_PLAYER_MANAGER::HitCalc()
{

}

