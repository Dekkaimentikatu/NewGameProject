#pragma once

#include <DxLib.h>

//点と四角の当たり判定
// dotPos		:	点の座標
// squarePos	:	四角形の中心座標
// width		:	四角形の横幅
// height		:	四角形の縦幅
// @return		:	true=当たった　false=当たっていない

class C_COLLISION
{
public:
	static bool CheckHitDotToSquare(VECTOR dotPos, VECTOR squarePos, int width, int height);
	static bool CheckHitSquareToSquare(VECTOR S_squarePos, VECTOR E_squarePos, int S_width, int S_height, int E_width, int E_height);
	static bool CheckHitCircleToCircle(VECTOR S_circlePos, VECTOR E_cleclePos, int S_redius, int E_redius);

	static bool CheckHitBoxToBox(VECTOR pos1, VECTOR size1, VECTOR pos2, VECTOR size2);
	static bool CheckHitSphereToSphere(VECTOR S_circlePos, VECTOR E_cleclePos, int S_redius, int E_redius);

};

