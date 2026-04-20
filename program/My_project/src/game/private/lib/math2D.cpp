#include "lib/math2D.h"

float GetLen2D(float X1, float X2, float Y1, float Y2)
{
	float 	len;
	len = sqrtf((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1));
	return len;
}

//座標にベクトルを足す
VECTOR VecAdd2D(VECTOR pos, VECTOR add)
{
	pos.x += add.x;
	pos.y += add.y;

	return pos;
}

VECTOR VecSub2D(VECTOR pos, VECTOR sub)
{
	VECTOR res;

	res.x = pos.x - sub.x;
	res.y = pos.y - sub.y;

	return res;
}

//ベクトルの生成
VECTOR VecCreate2D(VECTOR endPos, VECTOR startPos)
{
	VECTOR res;

	res.x = endPos.x - startPos.x;
	res.y = endPos.y - startPos.y;

	return res;
}

//ベクトルの長さを取得
float GetVecLength2D(VECTOR Vec)
{
	float len;
	len = sqrtf((Vec.x) * (Vec.x) + (Vec.y) * (Vec.y));
	return len;
}

//ベクトルを正規化
VECTOR VecNorm2D(VECTOR Vec, float len)
{
	VECTOR res;
	res.x = Vec.x / len;
	res.y = Vec.y / len;
	return res;
}

//ベクトルのスカラー倍
VECTOR VecScale2D(VECTOR Vec, float scale)
{
	VECTOR res;
	res.x = Vec.x * scale;
	res.y = Vec.y * scale;
	return res;
}

VECTOR VecDivision2D(VECTOR Vec, float scale)
{
	VECTOR res;
	res.x = Vec.x / scale;
	res.y = Vec.y / scale;
	return res;
}

//ベクトルの内積の計算
float VecDot2D(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = (vec1.x * vec2.x) + (vec1.y * vec2.y);

	return ret;
}

//2Dの外積の計算
float VecCrose2D(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = vec1.x * vec2.y - vec2.x * vec1.y;

	return ret;
}