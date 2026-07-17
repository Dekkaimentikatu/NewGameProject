#include "../public/math/mymath.h"
#include <compare>

float C_MY_MATH::GetLen(float X1, float X2, float Y1, float Y2)
{
	float 	len;
	len = sqrtf((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1));
	return len;
}

//整数の除算を切り捨てで行う
int C_MY_MATH::FloorDiv(int a, int b)
{
	auto d = div(a, b);

	if (d.rem != 0 &&
		((d.rem < 0) != (b < 0)))
	{
		--d.quot;
	}

	return d.quot;
}

//整数の剰余を計算する
int C_MY_MATH::Mod(int a, int b)
{
	auto d = div(a, b);

	if (d.rem != 0 &&
		((d.rem < 0) != (b < 0)))
	{
		d.rem += b;
	}

	return d.rem;
}

//座標にベクトルを足す
VECTOR C_MY_MATH::VecAdd(VECTOR pos, VECTOR add)
{
	pos.x += add.x;
	pos.y += add.y;
	pos.z += add.z;

	return pos;
}

//ベクトルの生成
VECTOR C_MY_MATH::VecCreate(VECTOR endPos, VECTOR startPos)
{
	VECTOR res;

	res.x = endPos.x - startPos.x;
	res.y = endPos.y - startPos.y;
	res.z = endPos.z - startPos.z;

	return res;
}

//ベクトルの長さを取得
float C_MY_MATH::GetVecLength(VECTOR Vec)
{
	float len;
	len = sqrtf((Vec.x) * (Vec.x) + (Vec.y) * (Vec.y) + (Vec.z) * (Vec.z));
	return len;
}

//ベクトルを正規化
VECTOR C_MY_MATH::VecNorm(VECTOR Vec, float len)
{
	VECTOR res;
	res.x = Vec.x / len;
	res.y = Vec.y / len;
	res.z = Vec.z / len;
	return res;
}

//ベクトルのスカラー倍
VECTOR C_MY_MATH::VecScale(VECTOR Vec, float scale)
{
	VECTOR res;
	res.x = Vec.x * scale;
	res.y = Vec.y * scale;
	res.z = Vec.z * scale;
	return res;
}

//ベクトルの内積の計算
float C_MY_MATH::VecDot(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);

	return ret;
}

//2Dの外積の計算
float C_MY_MATH::VecCrose2D(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = vec1.x * vec2.y - vec2.x * vec1.y;

	return ret;
}

//3Dの外積の計算
VECTOR C_MY_MATH::VecCrose(VECTOR vec1, VECTOR vec2)
{
	VECTOR ret;

	VECTOR result;
	result.x = vec1.y * vec2.z - vec1.z * vec2.y;
	result.y = vec1.z * vec2.x - vec1.x * vec2.z;
	result.z = vec1.x * vec2.y - vec2.y * vec2.x;

	return result;

	return ret;
}

MATRIX C_MY_MATH::GetIdentityMatrix()
{
	MATRIX mat;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (row == col)
			{

				mat.m[row][col] = 1.0f;
			}
			else
			{
				mat.m[row][col] = 0.0f;
			}
		}
	}

	return mat;
}

MATRIX C_MY_MATH::GetTranslateMatrix(float x, float y, float z)
{
	MATRIX mat;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (row == col)
			{

				mat.m[row][col] = 1.0f;
			}
			else if (col == 3)
			{
				switch (row)
				{
				case 0:
					mat.m[row][col] = x;
					break;
				case 1:
					mat.m[row][col] = y;
					break;
				case 2:
					mat.m[row][col] = z;
					break;
				}
			}
			else
			{
				mat.m[row][col] = 0.0f;
			}
		}
	}

	return mat;
}

MATRIX C_MY_MATH::GetTranslateMatrix(VECTOR _vec)
{
	MATRIX mat;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (row == col)
			{

				mat.m[row][col] = 1.0f;
			}
			else if (col == 3)
			{
				switch (row)
				{
				case 0:
					mat.m[row][col] = _vec.x;
					break;
				case 1:
					mat.m[row][col] = _vec.y;
					break;
				case 2:
					mat.m[row][col] = _vec.z;
					break;
				}
			}
			else
			{
				mat.m[row][col] = 0.0f;
			}
		}
	}

	return mat;
}

MATRIX C_MY_MATH::GetScaleMatrix(float x, float y, float z)
{
	MATRIX mat;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (row == col)
			{
				switch (row)
				{
				case 0:
					mat.m[row][col] = x;
					break;
				case 1:
					mat.m[row][col] = y;
					break;
				case 2:
					mat.m[row][col] = z;
					break;
				case 3:
					mat.m[row][col] = 1.0f;
					break;
				}
			}
			else
			{
				mat.m[row][col] = 0.0f;
			}
		}
	}

	return mat;
}

MATRIX C_MY_MATH::GetScaleMatrix(VECTOR _vec)
{
	MATRIX mat;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (row == col)
			{
				switch (row)
				{
				case 0:
					mat.m[row][col] = _vec.x;
					break;
				case 1:
					mat.m[row][col] = _vec.y;
					break;
				case 2:
					mat.m[row][col] = _vec.z;
					break;
				}
			}
		}
	}

	return mat;
}

MATRIX C_MY_MATH::GetPitchMatrix(float angle)
{
	return GetIdentityMatrix();
}

MATRIX C_MY_MATH::GetYawMatrix(float angle)
{
	return GetIdentityMatrix();
}

MATRIX C_MY_MATH::GetRollMatrix(float angle)
{
	return GetIdentityMatrix();
}

MATRIX C_MY_MATH::MatMult(MATRIX _mat1, MATRIX _mat2)
{
	return GetIdentityMatrix();
}

MATRIX C_MY_MATH::MatTransform(MATRIX _mat, VECTOR _vec)
{
	return GetIdentityMatrix();
}

MATRIX C_MY_MATH::MatTranspose(MATRIX _mat)
{
	return GetIdentityMatrix();
}