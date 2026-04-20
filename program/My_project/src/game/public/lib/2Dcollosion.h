#pragma once
#ifndef _2D_COLLOSION_H_
#define _2D_COLLOSION_H_



#include <DxLib.h>
#include <vector>
#include "mymath.h"

//点と四角の当たり判定
// dotPos		:	点の座標
// squarePos	:	四角形の中心座標
// width		:	四角形の横幅
// height		:	四角形の縦幅
// @return		:	true=当たった　false=当たっていない


class COLLOSION_2D
{
public:
	static bool CheckHitDotToDot(VECTOR dotPos1, VECTOR dotPos2);
	static bool CheckHitDotToSquare2D(VECTOR dotPos, VECTOR squarePos, int width, int height);
	static bool CheckHitDotToSquare2D(VECTOR dotPos, VECTOR vertexPos1, VECTOR vertexPos2, VECTOR vertexPos3, 
									VECTOR vertexPos4, int width, int height);
	static bool CheckHitSquareToSquare2D(VECTOR S_squarePos, VECTOR E_squarePos, int S_width, int S_height, int E_width, int E_height);
	static bool CheckHitCircleToCircle2D(VECTOR S_circlePos, VECTOR E_cleclePos, int S_redius, int E_redius);
};
#endif _2D_COLLOSION_H_

