#include "lib/2Dcollosion.h"

bool COLLOSION_2D::CheckHitDotToDot(VECTOR dotPos1, VECTOR dotPos2)
{
	if (dotPos1.x == dotPos2.x && dotPos1.y == dotPos2.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool COLLOSION_2D::CheckHitDotToSquare2D(VECTOR dotPos, VECTOR squarePos, int width, int height)
{
	//四角形の上下左右それぞれの座標を計算する
	float up = squarePos.y - height * 0.5f;
	float down = squarePos.y + height * 0.5f;
	float left = squarePos.x - width * 0.5f;
	float right = squarePos.x + width * 0.5f;

	//4つの端をそれぞれチェックして、すべての条件を満たしたらヒット！
	if (dotPos.x >= left && dotPos.x <= right
		&& dotPos.y >= up && dotPos.y <= down)
	{
		return true;
	}
	else return false;
}

bool COLLOSION_2D::CheckHitDotToSquare2D(VECTOR dotPos, VECTOR vertexPos1, VECTOR vertexPos2, VECTOR vertexPos3,
	VECTOR vertexPos4, int width, int height)
{
	VECTOR vec1 = MYMATH::VecCreate(vertexPos2, vertexPos1);
	VECTOR vec2 = MYMATH::VecCreate(vertexPos3, vertexPos2);
	VECTOR vec3 = MYMATH::VecCreate(vertexPos4, vertexPos3);
	VECTOR vec4 = MYMATH::VecCreate(vertexPos1, vertexPos4);

	VECTOR vecP1 = MYMATH::VecCreate(dotPos, vertexPos1);
	VECTOR vecP2 = MYMATH::VecCreate(dotPos, vertexPos2);
	VECTOR vecP3 = MYMATH::VecCreate(dotPos, vertexPos3);
	VECTOR vecP4 = MYMATH::VecCreate(dotPos, vertexPos4);

	float C1 = MYMATH::VecCrose2D(vec1, vecP1);
	float C2 = MYMATH::VecCrose2D(vec2, vecP2);
	float C3 = MYMATH::VecCrose2D(vec3, vecP3);
	float C4 = MYMATH::VecCrose2D(vec4, vecP4);

	return (C1 > 0 || C1 < 0) && (C2 > 0 || C2 < 0) && (C3 > 0 || C3 < 0) && (C4 > 0 || C4 < 0) ? true:false;
}

bool COLLOSION_2D::CheckHitSquareToSquare2D(VECTOR S_squarePos, VECTOR E_squarePos, int S_width, int S_height, int E_width, int E_height)
{

	//弾の当たり判定
	float S_up = S_squarePos.y - S_height * 0.5f;
	float S_down = S_squarePos.y + S_height * 0.5f;
	float S_left = S_squarePos.x - S_width * 0.5f;
	float S_right = S_squarePos.x + S_width * 0.5f;
	//敵の当たり判定
	float E_up = E_squarePos.y - E_height * 0.5f;
	float E_down = E_squarePos.y + E_height * 0.5f;
	float E_left = E_squarePos.x - E_width * 0.5f;
	float E_right = E_squarePos.x + E_width * 0.5f;
	//判定
	if (S_left <= E_right && S_right >= E_left
		&& S_up <= E_down && S_down >= E_up)
	{
		return true;
	}
	else return false;
}

bool COLLOSION_2D::CheckHitCircleToCircle2D(VECTOR S_circlePos, VECTOR E_cleclePos, int S_redius, int E_redius)
{
	//半径Aの2乗+半径Bの2乗
	float addredius = (float)(S_redius * S_redius) + (float)(E_redius * E_redius);
	//距離Xの2乗
	float distance_X = (float)(E_cleclePos.x - S_circlePos.x) * (float)(E_cleclePos.x - S_circlePos.x);
	//距離Yの2乗
	float distance_Y = (float)(E_cleclePos.y - S_circlePos.y) * (float)(E_cleclePos.y - S_circlePos.y);
	//判定
	if ((distance_X + distance_Y) < addredius)
	{
		return true;
	}
	else return false;
}