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
		MV1TerminateCollInfo(m_hndl);
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}
}


//------------------------------
//		データ読み込み
//------------------------------
void	Field::LoadData()
{
	m_hndl = MV1LoadModel("model/bg/model/ネオＵＫシティ(夜景)_Ver1.10.pmx");
	//コリジョン情報構築
	MV1SetupCollInfo(m_hndl);
}

//------------------------------
//		当たり判定
//------------------------------
VECTOR 	Field::HitCheck(VECTOR center, float radius)
{
	//押し戻し距離を呼び出し先に伝えるために使用
	VECTOR result = { 0.0f };
	MV1_COLL_RESULT_POLY_DIM col;
	VECTOR HitPos = { 0.0f };
	VECTOR Normal = { 0.0f };

	float len;

	//一旦当たっていない状態にしておく
	m_isHitFlag = false;
	//当たり判定を行い、その結果を構造体に格納
	col = MV1CollCheck_Sphere(m_hndl,-1,center,radius);

	//ポリゴンと当たっていた
	if (col.HitNum != 0)
	{
		//当たっていた時の処理

		//ヒットフラグを立てる
		m_isHitFlag = true;

		for (int i = 0; i < col.HitNum; i++)
		{
			//ポリゴンとの最近点を取得
			HitPos = col.Dim[i].HitPosition;

			//めり込んだ距離を求める
			len = VSize(VSub(HitPos, center));

			//半径からめり込んだ距離を減算する
			len = radius - len;

			//リザルトに結果を加算する
			if (VScale(col.Dim[i].Normal, len).x > result.x &&
				VScale(col.Dim[i].Normal, len).y > result.y &&
				VScale(col.Dim[i].Normal, len).z > result.z)
			{
				result = VScale(col.Dim[i].Normal, len);
			}
			else
			{
				result = VAdd(result, VScale(col.Dim[i].Normal, len));
			}

		}
	}

	MV1CollResultPolyDimTerminate(col);

	return result;
}

//------------------------------
//		描画処理
//------------------------------
void	Field::Draw()
{
	MV1DrawModel(m_hndl);
	if (m_isHitFlag)
		DrawFormatString(32, 32, GetColor(255, 255, 255), "Hit!");
}

