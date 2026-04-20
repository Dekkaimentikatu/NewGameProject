#include "Field.h"
#include <math.h>


//------------------------------
//		コンストラクタ
//------------------------------
Field::Field() : m_hndl(-1), m_isHitFlag(false)
{
}


//------------------------------
//		デストラクタ
//------------------------------
Field::~Field()
{
	if (m_hndl != -1)
	{
		MV1TerminateCollInfo(m_hndl);	//コリジョン情報破棄
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}
}


//------------------------------
//		データ読み込み
//------------------------------
void	Field::LoadData()
{
	m_hndl = MV1LoadModel("Model/Bg/Model/ネオＵＫシティ.x");
}


//------------------------------
//		データセット
//------------------------------
void	Field::Set()
{
	MV1SetScale(m_hndl, VGet(10.0f, 10.0f, 10.0f));
	MV1SetupCollInfo(m_hndl);	// コリジョン情報構築
}


//------------------------------
//		当たり判定
//------------------------------
VECTOR	Field::HitCheck(VECTOR center, float radius)
{
	VECTOR	out = { 0.0f, 0.0f, 0.0f };	//　物体が背景にめり込んだ距離
	m_isHitFlag = false;

	MV1_COLL_RESULT_POLY_DIM	res;	// 当たり判定結果格納構造体
	res = MV1CollCheck_Sphere(m_hndl, -1, center, radius);	// 当たり判定結果格納

	if (res.HitNum != 0) m_isHitFlag = true;
	// 当たったポリゴンの数だけ繰返す
	for (int i = 0; i < res.HitNum; i++)
	{
		//	ヒットしたポリゴンとヒットした物体のめり込んだ距離を求める
		VECTOR	sub = VSub(res.Dim[i].HitPosition, center);
		float	len = VSize(sub);
		len = radius - len;
		// めり込んだ距離分だけ外に押し出す　押し出す方向は法線の方向
		VECTOR	line = VScale(res.Dim[i].Normal, len);
		out = VAdd(out, line);
	}
	// 当たり判定結果を破棄する
	MV1CollResultPolyDimTerminate(res);

	return out;
}


//------------------------------
//		当たり判定
//------------------------------
VECTOR	Field::HitCheck(VECTOR start, VECTOR end)
{
	VECTOR	out = end;

	MV1_COLL_RESULT_POLY	res;	// 当たり判定結果格納構造体
	res = MV1CollCheck_Line(m_hndl, -1, start, end);	// 当たり判定結果格納

	// 障害物があった場合
	if (res.HitFlag == 1)
	{
		// 障害物とあたった場所へ移動
		out = res.HitPosition;
		// 上方向へ押し出す距離を計算し、加算する
		VECTOR v = VSub(end, res.HitPosition);
		float f = VSize(v);
		out.y += f;
	}
	

	return out;
}


//------------------------------
//		描画処理
//------------------------------
void	Field::Draw()
{
	MV1DrawModel(m_hndl);
	if (m_isHitFlag)
		DrawFormatString(32, 32, GetColor(255, 255, 255), "ヒット！！");
}