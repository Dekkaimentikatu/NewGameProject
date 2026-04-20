#include "game/base/object.h"

void C_OBJECT_BASE::Init()
{
	m_pos = { 0 };		//座標

	m_modelRota = { 0 };		//回転

	m_scale = { 0 };	//拡大率

	m_size = { 0 };		//各方向の大きさ

	m_modelHndl = -1;	//モデルハンドル

	m_isActive = false;	//生存フラグ
}

void C_OBJECT_BASE::Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl)
{
	//リクエスト処理
	m_pos = m_startPos = _pos;
	m_scale = _scale;
	m_modelRota = _rotation;
	//DuplicateModel(_modelHndl);
}

int C_OBJECT_BASE::GetAtt()
{
	return m_att;
}