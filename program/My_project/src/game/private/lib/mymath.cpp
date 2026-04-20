#include "lib/mymath.h"

float MYMATH::GetLen(float X1, float X2, float Y1, float Y2)
{
	float 	len;
	len = sqrtf((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1));
	return len;
}

//座標にベクトルを足す
VECTOR MYMATH::VecAdd(VECTOR pos, VECTOR add)
{
	pos.x += add.x;
	pos.y += add.y;
	pos.z += add.z;

	return pos;
}

//ベクトルの生成
VECTOR MYMATH::VecCreate(VECTOR endPos, VECTOR startPos)
{
	VECTOR res;

	res.x = endPos.x - startPos.x;
	res.y = endPos.y - startPos.y;
	res.z = endPos.z - startPos.z;

	return res;
}

//ベクトルの長さを取得
float MYMATH::GetVecLength(VECTOR Vec)
{
	float len;
	len = sqrtf((Vec.x) * (Vec.x) + (Vec.y) * (Vec.y) + (Vec.z) * (Vec.z));
	return len;
}

//ベクトルを正規化
VECTOR MYMATH::VecNorm(VECTOR Vec, float len)
{
	VECTOR res;
	res.x = Vec.x / len;
	res.y = Vec.y / len;
	res.z = Vec.z / len;
	return res;
}

//ベクトルのスカラー倍
VECTOR MYMATH::VecScale(VECTOR Vec, float scale)
{
	VECTOR res;
	res.x = Vec.x * scale;
	res.y = Vec.y * scale;
	res.z = Vec.z * scale;
	return res;
}

//ベクトルの内積の計算
float MYMATH::VecDot(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);

	return ret;
}

//2Dの外積の計算
float MYMATH::VecCrose2D(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = vec1.x * vec2.y - vec2.x * vec1.y;

	return ret;
}

//3Dの外積の計算
VECTOR MYMATH::VecCrose(VECTOR vec1, VECTOR vec2)
{
	VECTOR ret;

	VECTOR result;
	result.x = vec1.y * vec2.z - vec1.z * vec2.y;
	result.y = vec1.z * vec2.x - vec1.x * vec2.z;
	result.z = vec1.x * vec2.y - vec2.y * vec2.x;

	return result;

	return ret;
}

MATRIX MYMATH::GetIdentityMatrix()
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

MATRIX MYMATH::GetTranslateMatrix(float x, float y, float z)
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

MATRIX MYMATH::GetTranslateMatrix(VECTOR _vec)
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

MATRIX MYMATH::GetScaleMatrix(float x, float y, float z)
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

MATRIX MYMATH::GetScaleMatrix(VECTOR _vec)
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

MATRIX MYMATH::GetPitchMatrix(float angle)
{
	return GetIdentityMatrix();
}

MATRIX MYMATH::GetYawMatrix(float angle)
{
	return GetIdentityMatrix();
}

MATRIX MYMATH::GetRollMatrix(float angle)
{
	return GetIdentityMatrix();
}

MATRIX MYMATH::MatMult(MATRIX _mat1, MATRIX _mat2)
{
	return GetIdentityMatrix();
}

MATRIX MYMATH::MatTransform(MATRIX _mat, VECTOR _vec)
{
	return GetIdentityMatrix();
}

MATRIX MYMATH::MatTranspose(MATRIX _mat)
{
	return GetIdentityMatrix();
}