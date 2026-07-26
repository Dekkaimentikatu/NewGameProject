#include "../public/collision/3Dcollision.h"
#include <algorithm>

//箱同士の当たり判定
bool C_COLLISION::CheckHitBoxToBox(VECTOR pos1, VECTOR size1, VECTOR pos2, VECTOR size2)
{
	float up1 = pos1.y - size1.y * 0.5f;
	float down1 = pos1.y + size1.y * 0.5f;
	float left1 = pos1.x - size1.x * 0.5f;
	float right1 = pos1.x + size1.x * 0.5f;
	float front1 = pos1.z - size1.z * 0.5f;
	float back1 = pos1.z + size1.z * 0.5f;

	float up2 = pos2.y - size2.y * 0.5f;
	float down2 = pos2.y + size2.y * 0.5f;
	float left2 = pos2.x - size2.x * 0.5f;
	float right2 = pos2.x + size2.x * 0.5f;
	float front2 = pos2.z - size2.z * 0.5f;
	float back2 = pos2.z + size2.z * 0.5f;

	if (left1 <= right2 && right1 >= left2
		&& up1 <= down2 && down1 >= up2
		&& front1 <= back2 && back1 >= front2)
	{
		return true;
	}
	else return false;
}

bool C_COLLISION::CheckHitBoxToCapsule(VECTOR _boxPos, VECTOR _boxSize, VECTOR _capPos1, VECTOR _capPos2, float _capRedius)
{
	return true;
}

//球同士の当たり判定
bool C_COLLISION::CheckHitSphereToSphere(VECTOR S_circlePos, VECTOR E_cleclePos, int S_redius, int E_redius)
{
	//半径Aの2乗+半径Bの2乗
	float addredius = static_cast<float>((S_redius + E_redius) * (S_redius + E_redius));
	//距離Xの2乗
	float distance_X = (E_cleclePos.x - S_circlePos.x) * (E_cleclePos.x - S_circlePos.x);
	//距離Yの2乗
	float distance_Y = (E_cleclePos.y - S_circlePos.y) * (E_cleclePos.y - S_circlePos.y);
	//距離Zの2乗
	float distance_Z = (E_cleclePos.z - S_circlePos.z) * (E_cleclePos.z - S_circlePos.z);
	//判定
	if ((distance_X + distance_Y + distance_Z) < addredius)
	{
		return true;
	}
	else return false;
}

//AABBと球の当たり判定
bool C_COLLISION::CheckHitAABBToSphere(VECTOR _sphereCenter, float _sphereRedius, VECTOR _AABBMax, VECTOR _AABBMin)
{
	//AABB上の球心に最も近い点を求める
	float closestX = std::clamp(_sphereCenter.x, _AABBMin.x, _AABBMax.x);
	float closestY = std::clamp(_sphereCenter.y, _AABBMin.y, _AABBMax.y);
	float closestZ = std::clamp(_sphereCenter.z, _AABBMin.z, _AABBMax.z);

	//最近接点と球心の距離の二乗を計算
	float dx = closestX - _sphereCenter.x;
	float dy = closestY - _sphereCenter.y;
	float dz = closestZ - _sphereCenter.z;
	float distSq = dx * dx + dy * dy + dz * dz;

	//距離が半径以下なら衝突
	return distSq <= (_sphereRedius * _sphereRedius);
}

//AABBと球の当たり判定
bool C_COLLISION::CheckHitAABBToSphere(VECTOR _sphereCenter, float _sphereRedius, VECTOR _AABBPos, float _AABBSize, VECTOR& _closest)
{
	VECTOR AABBMax = { _AABBPos.x + _AABBSize * 0.5f, _AABBPos.y + _AABBSize * 0.5f, _AABBPos.z + _AABBSize * 0.5f };
	VECTOR AABBMin = { _AABBPos.x - _AABBSize * 0.5f, _AABBPos.y - _AABBSize * 0.5f, _AABBPos.z - _AABBSize * 0.5f };

	//AABB上の球心に最も近い点を求める
	float closestX = std::clamp(_sphereCenter.x, AABBMin.x, AABBMax.x);
	float closestY = std::clamp(_sphereCenter.y, AABBMin.y, AABBMax.y);
	float closestZ = std::clamp(_sphereCenter.z, AABBMin.z, AABBMax.z);

	//最近点を格納
	_closest = VGet(closestX, closestY, closestZ);

	//最近接点と球心の距離の二乗を計算
	float dx = closestX - _sphereCenter.x;
	float dy = closestY - _sphereCenter.y;
	float dz = closestZ - _sphereCenter.z;
	float distSq = VSquareSize(VGet(dx, dy, dz));

	//距離が半径以下なら衝突
	return distSq <= (_sphereRedius * _sphereRedius);
}

bool C_COLLISION::CheckHitOBBToSphere(VECTOR _sphereCenter, float _sphereredius, T_OBB _OBB)
{
	return true;
}

bool C_COLLISION::CheckHitAABBToLine(VECTOR _lineStart, VECTOR _lineEnd, VECTOR _AABBPos, 
									float _AABBSize, float& _hitTMin, float& _hitTMax, VECTOR& _hitPos)
{
	//線分の方向ベクトルを計算
	VECTOR dir = VSub(_lineStart, _lineEnd);

	//AABBの最大座標と最小座標を計算
	VECTOR AABBMax = { _AABBPos.x + _AABBSize * 0.5f, _AABBPos.y + _AABBSize * 0.5f, _AABBPos.z + _AABBSize * 0.5f };
	VECTOR AABBMin = { _AABBPos.x - _AABBSize * 0.5f, _AABBPos.y - _AABBSize * 0.5f, _AABBPos.z - _AABBSize * 0.5f };

	_hitTMin = 0.0f;
	_hitTMax = 1.0f;
	_hitPos = { 0 };

	//線分とAABBの交差判定
	for (int axis = 0; axis < 3; axis++)
	{
		float s;
		float d;
		float minB;
		float maxB;

		//軸ごとの線分の始点と方向ベクトル、AABBの最小座標と最大座標を取得
		switch (axis)
		{
		case 0:
			s = _lineStart.x;
			d = dir.x;
			minB = AABBMin.x;
			maxB = AABBMax.x;
			break;

		case 1:
			s = _lineStart.y;
			d = dir.y;
			minB = AABBMin.y;
			maxB = AABBMax.y;
			break;

		default:
			s = _lineStart.z;
			d = dir.z;
			minB = AABBMin.z;
			maxB = AABBMax.z;
			break;
		}

		//線分がこの軸に平行かどうかを判定
		if (std::abs(d) < 1e-6f)
		{
			//線分がこの軸に平行
			if (s < minB || s > maxB)
				return false;

			continue;
		}

		//線分がこの軸に平行でない場合、交差する可能性がある
		float invD = 1.0f / d;

		//t1とt2を計算して、tMinとtMaxを更新
		float t1 = (minB - s) * invD;
		float t2 = (maxB - s) * invD;

		//t1とt2の順序を入れ替える
		if (t1 > t2)std::swap(t1, t2);

		//tMinとtMaxを更新
		_hitTMin = (std::max)(_hitTMin, t1);
		_hitTMax = (std::min)(_hitTMax, t2);

		//tMinがtMaxを超えた場合、交差しない
		if (_hitTMin > _hitTMax)
			return false;
	}
	//交差点の座標を計算
	_hitPos = VAdd(_lineStart, VScale(dir, _hitTMin));

	return true;
}