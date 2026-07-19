#include "game/base/object.h"
#include "hndlmanager/3Dhndlmanager.h"
#include "hndlmanager/2Dhndlmanager.h"

C_OBJECT_BASE::C_OBJECT_BASE()
{
	Init();
}

void C_OBJECT_BASE::Init()
{
	//HP
	m_hp = 0;

	//HP最大値
	m_hpMax = 0;

	//グローバルデータクラスのインスタンス取得用変数
	c_globalData = nullptr;

	//オブジェクト情報
	m_objectData = {};

	//座標
	m_pos = {};

	//移動ベクトル
	m_moveVec = {};

	//オブジェクトの分類
	m_objectType = OBJECT_TYPE_STATIC;

	//当たり判定の半径
	m_redius = 0.0f;

	//3Dモデルのハンドル
	m_modelHndl = 0;

	//エフェクトのハンドル
	m_effHndl = 0;

	//生存フラグ
	m_isActive = false;
}