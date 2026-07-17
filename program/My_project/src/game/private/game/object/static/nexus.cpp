#include "game/object/static/nexus.h"
#include "hndlmanager/3Dhndlmanager.h"

void C_NEXUS::Init()
{
	//座標の初期化
	m_pos = VGet(0, 0, 0);
}

void C_NEXUS::Request(T_OBJECT_DATA _objectData)
{
	//モデル情報のリクエスト
	m_objectData = _objectData;
}

void C_NEXUS::Load()
{
	C_3D_HNDL_MANAGER* instace = C_3D_HNDL_MANAGER::GetInstance();
	m_modelHndl = instace->Get3DModelHndl(NEXUS_MODEL_PATH);
	m_isActive = true;
	m_hp = 100;
	m_redius = 10;
	//モデル情報の読込
	m_pos = VGet(0.0f, 70.0f, 0.0f);	//位置
	m_objectData.modelScale = VGet(1.0f, 1.0f, 1.0f);
	m_objectType = OBJECT_TYPE_BLCOK;
	UpdateModel();
	c_globalData = C_GLOBAL_DATA::GetInstace();
	c_globalData->SetTargetPos(m_pos);
	SetUpCollInfo();

}

void C_NEXUS::Step()
{
	//モデルの回転
	if (m_hp < 0)m_isActive = false;
}

void C_NEXUS::Update()
{
	//モデル情報の更新
	UpdateModel();
	UpdateCollInfo();
}

void C_NEXUS::Draw()
{
	//モデル描画
	if(m_isActive)DrawModel();
}

void C_NEXUS::Exit()
{
	//モデル情報の削除
	DeleteModel();
}

void C_NEXUS::HitCalc()
{

}