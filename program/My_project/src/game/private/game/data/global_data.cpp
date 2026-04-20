#include "game/data/global_data.h"



C_GLOBAL_DATA* C_GLOBAL_DATA::m_instance = nullptr;

C_GLOBAL_DATA* C_GLOBAL_DATA::GetInstace()
{
	if (m_instance == nullptr)
	{
		m_instance = new C_GLOBAL_DATA;
	}

	return m_instance;
}

void C_GLOBAL_DATA::DeleteInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

void C_GLOBAL_DATA::Init()
{
	//プレイヤーデータの初期化
	ResetPlayerData();

	//エネミーデータの初期化
	t_enemyData.hp_max = 50;
	t_enemyData.hp = 50;
	t_enemyData.att = 5;
	t_enemyData.def = 5;
	t_enemyData.attSpd = 5;

	//プレイデータの初期化
	t_playData.score = 0;
	t_playData.stageNum = 1;
	t_playData.killenemy = 0;
	t_playData.getitem = 0;
	t_playData.time = 0;
	t_playerData.isStop = false;
	t_playerData.isGoal = false;
	t_playerData.isRespawn = false;


	//ステージデータの初期化
	t_stageData.stage_index = 0;


}

void C_GLOBAL_DATA::DrawDebug()
{
	//DrawFormatString(16, 64, GetColor(255, 255, 255), "Hp = %d", t_playerData.hp);
}

void C_GLOBAL_DATA::ResetPlayerData()
{
	//プレイヤーデータの初期化
	t_playerData.hp_max = MAX_HP;
	t_playerData.hp = MAX_HP;
	t_playerData.stm_max = MAX_STM;
	t_playerData.stm = MAX_STM;
	t_playerData.att = ATT;
	t_playerData.def = DEF;
	t_playerData.attSpd = ATTSPD;
	t_playerData.isStop = false;
	t_playerData.isGoal = false;
}