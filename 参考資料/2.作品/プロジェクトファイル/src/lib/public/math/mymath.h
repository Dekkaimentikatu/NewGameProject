#pragma once
#include <math.h>
#include <DxLib.h>

class MYMATH
{
public:

	static float GetLen(float X1, float X2, float Y1, float Y2);

	//座標にベクトルを足す
	static VECTOR VecAdd(VECTOR pos, VECTOR add);

	//ベクトルの生成
	static VECTOR VecCreate(VECTOR endPos, VECTOR startPos);

	//ベクトルの長さを取得
	static float GetVecLength(VECTOR Vec);

	//ベクトルを正規化
	static VECTOR VecNorm(VECTOR Vec, float len);

	//ベクトルのスカラー倍
	static VECTOR VecScale(VECTOR Vec, float scale);

	//ベクトルの内積の計算
	static float VecDot(VECTOR vec1, VECTOR vec2);

	//2Dの外積の計算
	static float VecCrose2D(VECTOR vec1, VECTOR vec2);

	//3Dの外積の計算
	static VECTOR VecCrose(VECTOR vec1, VECTOR vec2);


	static MATRIX GetIdentityMatrix();

	static MATRIX GetTranslateMatrix(float x, float y, float z);

	static MATRIX GetTranslateMatrix(VECTOR _vec);

	static MATRIX GetScaleMatrix(float x, float y, float z);

	static MATRIX GetScaleMatrix(VECTOR _vec);

	static MATRIX GetPitchMatrix(float angle);

	static MATRIX GetYawMatrix(float angle);

	static MATRIX GetRollMatrix(float angle);

	static MATRIX MatMult(MATRIX _mat1, MATRIX _mat2);

	static MATRIX MatTransform(MATRIX _mat, VECTOR _vec);

	static MATRIX MatTranspose(MATRIX _mat);

};

