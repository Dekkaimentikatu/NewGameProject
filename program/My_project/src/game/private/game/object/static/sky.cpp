#include "game/object/static/sky.h"

void C_SKY::Init()
{
	//座標の初期化
	m_pos = VGet(0, 0, 0);
}

void C_SKY::Load()
{
	//モデル情報の読込
	m_pos = VGet(0, 0, 0);	//位置
	m_scale = VGet(16.0f, 16.0f, 16.0f);
	m_objectType = OBJECT_TYPE_STATIC;
	LoadModel("data/model/field/sky.mv1");
	UpdateModel();
}

void C_SKY::Step()
{
	//モデルの回転
	m_modelRota = VAdd(m_modelRota, VGet(0, 0.0001f, 0));
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