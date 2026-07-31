#pragma once

#include <DxLib.h>
#include <list>

using namespace std;

constexpr int MAX_HP = 100;
constexpr int MAX_STM = 250;
constexpr int ATT = 20;
constexpr int DEF = 10;
constexpr int ATTSPD = 10;

class C_GLOBAL_DATA
{
public:

	//プレイヤーデータ
	typedef struct 
	{
		int hp_max;	//最大体力
		int hp;		//体力
		int stm_max;	//最大スタミナ
		int stm;	//スタミナ
		int att;	//攻撃力
		int def;	//防御力
		int attSpd;	//攻撃速度
		int movSpd;	//移動速度
		bool isStop;	//停止フラグ
		bool isGoal;	//
		bool isRespawn;	//リスポーンフラグ
		VECTOR pos;	//プレイヤーの位置
	}T_PLAYER_DATA;

	//エネミーデータ
	typedef struct
	{
		int hp_max;	//最大体力
		int hp;		//体力
		int att;	//攻撃力
		int def;	//防御力
		int attSpd;	//攻撃速度
	}T_ENEMY_DATA;

	//プレイデータ
	typedef struct
	{
		int stageNum;	//ステージナンバー
		int killenemy;	//倒した敵の数
		int getitem;	//取ったアイテムの数
		int time;		//クリアタイム
		int score;		//スコア
	}T_PLAY_DATA;

	typedef struct
	{
		int stage_index;	//ステージの番号
	}T_STAGE_DATA;

	typedef struct
	{
		VECTOR GoalPos;	//ゴールの位置
		VECTOR StartPos;	//スタートの位置
		float m_startRot;
	}T_FLAG_DATA;

	typedef struct
	{
		VECTOR pos;	//アイテムの位置
		VECTOR rot;	//アイテムの回転
		VECTOR scale;	//アイテムの大きさ
	}T_ENEMY_SPOWN;

private:

	C_GLOBAL_DATA() = default;
	~C_GLOBAL_DATA() = default;

	C_GLOBAL_DATA(const C_GLOBAL_DATA& other);
	C_GLOBAL_DATA& operator= (const C_GLOBAL_DATA& other);

	T_PLAYER_DATA t_playerData;

	T_ENEMY_DATA t_enemyData;

	T_PLAY_DATA t_playData;

	T_STAGE_DATA t_stageData;

	T_FLAG_DATA t_flagData;

	list<T_ENEMY_SPOWN> m_enemySpawnPointList;

	static C_GLOBAL_DATA* m_instance;

public:

	static C_GLOBAL_DATA* GetInstace();

	static void DeleteInstance();

	void Init();

	T_PLAYER_DATA* GetPlayerData() { return &t_playerData; }

	T_ENEMY_DATA* GetEnemyData() { return &t_enemyData; }

	T_PLAY_DATA* GetPlayData() { return &t_playData; }

	T_STAGE_DATA* GetStageData() { return &t_stageData; };

	T_FLAG_DATA* GetFlagData() { return &t_flagData; };

	list<T_ENEMY_SPOWN>* GetEnemySpawnPointList() { return &m_enemySpawnPointList; }

	void SetPlayerData(T_PLAYER_DATA* _playerData) { t_playerData = *_playerData; }

	void ResetPlayerData();

	void SetEnemyData(T_ENEMY_DATA _enemyData) { t_enemyData = _enemyData; }

	void SetPlayData(T_PLAY_DATA _playData) { t_playData = _playData; }

	void DrawDebug();

};

