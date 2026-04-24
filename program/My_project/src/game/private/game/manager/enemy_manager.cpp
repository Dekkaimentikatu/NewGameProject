#include "game/manager/enemy_manager.h"
#include "game/collision/collision_manager.h"
#include "effekseer/effekseer.h"
#include "lib/3Dhndlmanager.h"

void C_ENEMY_MANAGER::Init()
{
	c_actorArray.clear();

	m_targetPos = { 0 };

	c_globalData = C_GLOBAL_DATA::GetInstace();
}

void C_ENEMY_MANAGER::LoadAnSync()
{
	C_3D_HNDL_MANAGER* instance = C_3D_HNDL_MANAGER::GetInstance();
	instance->Load3DModel(ENEMY_MODEL_PATH);
}

void C_ENEMY_MANAGER::LoadSync()
{
	C_ENEMY* enemy = nullptr;
	C_OBJECT_BASE::T_OBJECT_DATA tmp = {0};

	int eff1 = CEffekseerCtrl::LoadData("data/effect/ToonHit.efk");
	int eff2 = CEffekseerCtrl::LoadData("data/effect/FireWorks.efk");

	for (auto itr = c_globalData->GetEnemySpawnPointList()->begin();
		itr != c_globalData->GetEnemySpawnPointList()->end(); ++itr)
	{
		enemy = new C_ENEMY;
		enemy->Init();
		tmp.initPos = (*itr).pos;
		tmp.modelScale = (*itr).scale;
		tmp.modelRot = (*itr).rot;
		tmp.moveLen = 0;
		enemy->Request(tmp);
		enemy->SetEffectHndl(eff1, 0);
		enemy->SetEffectHndl(eff2, 1);
		enemy->Load();
		c_actorArray.push_back(enemy);
	}

	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		C_COLLISION_MANAGER::AddObject(*itr);
		C_COLLISION_MANAGER::AddActor(*itr);
	}
}

void C_ENEMY_MANAGER::Step()
{
	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		(*itr)->Step();
	}
}

void C_ENEMY_MANAGER::Update()
{
	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		if((*itr)->GetIsActive())(*itr)->Update();
	}
}

void C_ENEMY_MANAGER::Draw()
{
	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		if ((*itr)->GetIsActive())(*itr)->Draw();
	}
}

void C_ENEMY_MANAGER::Exit()
{
	C_3D_HNDL_MANAGER* instance = C_3D_HNDL_MANAGER::GetInstance();
	instance->Delete3DModel(ENEMY_MODEL_PATH);

	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		(*itr)->Exit();
		delete (*itr);
	}
	c_globalData->GetEnemySpawnPointList()->clear();
	c_actorArray.clear();
}

void C_ENEMY_MANAGER::SetTargetPos(VECTOR _targetPos)
{
	m_targetPos = _targetPos;
}

bool C_ENEMY_MANAGER::GetIsEnd()
{
	for (auto itr = c_actorArray.begin(); itr != c_actorArray.end(); ++itr)
	{
		if((*itr)->GetIsActive())return false;
	}

	return true;
}