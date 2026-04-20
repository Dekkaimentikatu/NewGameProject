#pragma once
#include <math.h>
#include <DxLib.h>

float GetLen2D(float X1, float X2, float Y1, float Y2);

//座標にベクトルを足す
VECTOR VecAdd2D(VECTOR pos, VECTOR add);

//座標からベクトルを引く
VECTOR VecSub2D(VECTOR pos, VECTOR sub);

//ベクトルの生成
VECTOR VecCreate2D(VECTOR endPos, VECTOR startPos);

//ベクトルの長さを取得
float GetVecLength2D(VECTOR Vec);

//ベクトルを正規化
VECTOR VecNorm2D(VECTOR Vec, float len);

//ベクトルのスカラー倍
VECTOR VecScale2D(VECTOR Vec, float scale);

VECTOR VecDivision2D(VECTOR Vec, float scale);

//ベクトルの内積の計算
float VecDot2D(VECTOR vec1, VECTOR vec2);

//2Dの外積の計算
float VecCrose2D(VECTOR vec1, VECTOR vec2);