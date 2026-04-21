#include "game/object/static/sky.h"
#include "lib/3Dhndlmanager.h"

void C_SKY::Init()
{
	//座標の初期化
	m_pos = VGet(0, 0, 0);
}

void C_SKY::Request(T_OBJECT_DATA _objectData)
{
	//モデル情報のリクエスト
	m_objectData = _objectData;
}

void C_SKY::Load()
{
	C_3D_HNDL_MANAGER* instace = C_3D_HNDL_MANAGER::GetInstance();
	m_modelHndl = instace->Get3DModelHndl(SKY_MODEL_PATH);
	//モデル情報の読込
	m_pos = VGet(0, 0, 0);	//位置
	m_objectData.modelScale = VGet(16.0f, 16.0f, 16.0f);
	m_objectType = OBJECT_TYPE_STATIC;
	UpdateModel();
}

void C_SKY::Step()
{
	//モデルの回転
	m_objectData.modelRot = VAdd(m_objectData.modelRot, VGet(0, 0.0001f, 0));
}

void C_SKY::Update()
{	
	//モデル情報の更新
	UpdateModel();
}

void C_SKY::Draw()
{
	//モデル描画
	DrawModel();
}

void C_SKY::Exit()
{
	//モデル情報の削除
	DeleteModel();
}

void C_SKY::HitCalc()
{

}